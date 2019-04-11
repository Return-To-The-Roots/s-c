// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

///////////////////////////////////////////////////////////////////////////////
// Systemheader

#include "libsiedler2/Archiv.h"
#include "libsiedler2/ArchivItem.h"
#include "libsiedler2/ArchivItem_Sound_Wave.h"
#include "libsiedler2/ErrorCodes.h"
#include "libsiedler2/enumTypes.h"
#include "libsiedler2/libsiedler2.h"
#include "libsiedler2/prototypen.h"
#include "libutil/StringConversion.h"
#include "libutil/System.h"
#include "libutil/Tokenizer.h"
#include "libutil/tmpFile.h"
#include <boost/filesystem.hpp>
#include <boost/nowide/args.hpp>
#include <boost/nowide/iostream.hpp>
#include <boost/program_options.hpp>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace bfs = boost::filesystem;
namespace bnw = boost::nowide;
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::string script, from, to;
    boost::nowide::args _(argc, argv);
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "Show help")("script,s", po::value<std::string>(&script)->required(), "Script (*.scs) to use")(
      "from,f", po::value<std::string>(&from)->required(), "Source.lst to read from")("to,t", po::value<std::string>(&to)->required(),
                                                                                      "Destination.lst to write to");

    po::variables_map options;
    po::store(po::parse_command_line(argc, argv, desc), options);
    po::notify(options);

    if(options.count("help"))
    {
        bnw::cout << desc;
        return EXIT_FAILURE;
    }

    bnw::cout << "Starting samplerate conversion\n" << std::endl;
    bnw::cout << "Input file: \"" << from << "\"" << std::endl;
    bnw::cout << "Output file: \"" << to << "\"" << std::endl;
    bnw::cout << "using Script: \"" << script << "\"\n" << std::endl;

    bfs::path resampleCommand = bfs::path(argv[0]).parent_path() / "s-c_resample";
#ifdef _WIN32
    resampleCommand.replace_extension(".exe");
#endif
    if(!bfs::exists(resampleCommand))
    {
        bnw::cerr << "Did not found resample utility at " << resampleCommand << std::endl;
        return EXIT_FAILURE;
    }

    libsiedler2::Archiv input, output;
    if(int ec = libsiedler2::Load(from, input))
    {
        bnw::cerr << "Can't open input file \"" << from << "\" " << libsiedler2::getErrorString(ec) << std::endl;
        return EXIT_FAILURE;
    }

    bnw::ifstream in(script);
    if(!in)
    {
        bnw::cerr << "Can't open script file \"" << script << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    int linenr = 0, emptylines = 0;
    std::string line;
    while(std::getline(in, line))
    {
        ++linenr;

        if(line.empty())
        {
            ++emptylines;
            if(emptylines > 100)
                break;
            continue;
        }
        emptylines = 0;

        if(line[0] == '#')
            continue;
        if(line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);

        Tokenizer token(line);

        std::string sNumber = token.next();
        if(sNumber == "empty")
        {
            bnw::cout << "Inserting empty item at line " << linenr << "" << std::endl;
            output.push(nullptr);
            continue;
        }

        int nr;
        if(!s25util::tryFromStringClassic(sNumber, nr))
        {
            bnw::cerr << "Script error on line  " << linenr << ": Cannot parse number '" << sNumber << "'" << std::endl;
            return EXIT_FAILURE;
        }
        libsiedler2::ArchivItem* item = input.get(nr);

        std::string sFrequency = token.next();
        // Allow empty items only on copy
        if((!item && sFrequency != "copy") || (item && item->getBobType() != libsiedler2::BOBTYPE_SOUND))
        {
            bnw::cerr << "Script error on line " << linenr << ": item " << nr << " does not exist or is not a sound" << std::endl;
            return EXIT_FAILURE;
        }

        if(sFrequency == "copy")
        {
            if(item)
            {
                bnw::cout << "Copying item " << nr << " at line " << linenr << "" << std::endl;
                output.pushC(*item);
            } else
            {
                bnw::cout << "Copying empty item " << nr << " at line " << linenr << "" << std::endl;
                output.push(nullptr);
            }
            continue;
        }

        uint32_t frequency;
        if(!s25util::tryFromStringClassic(sFrequency, frequency) || frequency == 0u)
        {
            bnw::cerr << "Script error on line  " << linenr << ": Cannot parse frequency '" << sFrequency << "'" << std::endl;
            return EXIT_FAILURE;
        }

        auto* wave = dynamic_cast<libsiedler2::ArchivItem_Sound_Wave*>(item);
        if(!wave)
        {
            bnw::cerr << "Script error on line " << linenr << ": item " << nr << " is not a wave-sound" << std::endl;
            return EXIT_FAILURE;
        }

        TmpFile tmp(".wav");
        if(!tmp.isValid())
        {
            bnw::cerr << "Can't write to temporary file - disk full?" << std::endl;
            return EXIT_FAILURE;
        }

        libsiedler2::WAV_Header header = wave->getHeader();
        uint16_t bitrate = 8;
        uint16_t blockAlign = header.numChannels * ((bitrate + 7) / 8);
        header.samplesPerSec = frequency;
        header.bytesPerSec = frequency * blockAlign;
        header.frameSize = blockAlign;
        header.bitsPerSample = bitrate;
        wave->setHeader(header);

        if(int ec = wave->write(tmp.getStream(), false))
        {
            bnw::cerr << "Can't write to temporary file \"" << tmp.filePath << "\" - write failed with " << libsiedler2::getErrorString(ec)
                      << std::endl;
            tmp.close();
            return EXIT_FAILURE;
        }
        tmp.close();

        TmpFile tmp2(".wav");
        if(!tmp2.isValid())
        {
            bnw::cerr << "Can't create 2nd temporary file" << std::endl;
            return EXIT_FAILURE;
        }
        tmp2.close();
        boost::filesystem::remove(tmp2.filePath);

        std::stringstream sArguments;
        sArguments << "-to 44100 ";
        sArguments << "\"" << tmp.filePath << "\" ";
        sArguments << "\"" << tmp2.filePath << "\" ";

        std::string convertedFilepath = tmp2.filePath;
        if(!System::execute(resampleCommand, sArguments.str()))
        {
            bnw::cerr << "Resampling failed, using original item" << std::endl;
            convertedFilepath = tmp.filePath;
        }

        libsiedler2::Archiv convArchiv;
        if(int ec = libsiedler2::Load(convertedFilepath, convArchiv))
        {
            bnw::cerr << "Reading converted file \"" << convertedFilepath << "\" failed with " << libsiedler2::getErrorString(ec)
                      << std::endl;
            return EXIT_FAILURE;
        }
        if(convArchiv.size() != 1 || convArchiv[0]->getBobType() != libsiedler2::BOBTYPE_SOUND)
        {
            bnw::cerr << "Unknown error eading converted file \"" << convertedFilepath << "\"" << std::endl;
            return EXIT_FAILURE;
        }
        output.push(convArchiv.release(0));
    }

    if(libsiedler2::loader::WriteLST(to, output) != 0)
    {
        bnw::cerr << "Conversion failed - was not able to save results to \"" << to << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Conversion successful\n" << std::endl;

    return EXIT_SUCCESS;
}
