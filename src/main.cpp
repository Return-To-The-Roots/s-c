// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
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

#include "getopt.h"
#include "tokenizer.hpp"

#include "libsiedler2/src/libsiedler2.h"
#include "libutil/src/tmpFile.h"

#include <boost/filesystem.hpp>
#include <boost/endian/conversion.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

int usage(int argc, char* argv[])
{
    std::cerr << "Usage: " << argv[0] << " -s script.scs -f source.lst -t destination.lst" << std::endl;

    return EXIT_FAILURE;
}

void myexit()
{
    //std::cout << "Press enter to exit" << std::endl;
    //getc(stdin);
}

int main(int argc, char* argv[])
{
    int index;
    const char* from = NULL, *to = NULL, *scs = NULL;

    atexit(myexit);

    while((index = getopt(argc, argv, "s:f:t:")) != EOF)
    {
        switch(index)
        {
            case 's': // Pidfile
            {
                scs = optarg;
            } break;
            case 'f':
            {
                from = optarg;
            } break;
            case 't':
            {
                to = optarg;
            } break;
        }
    }

    if(!scs || !to || !from)
        return usage(argc, argv);

    std::cout << "Starting samplerate conversion\n" << std::endl;
    std::cout << "Input file: \"" << from << "\"" << std::endl;
    std::cout << "Output file: \"" << to << "\"" << std::endl;
    std::cout << "using Script: \"" << scs << "\"\n" << std::endl;

    libsiedler2::ArchivInfo input, output;
    if(libsiedler2::Load(from, input) != 0)
    {
        std::cerr << "Can't open input file \"" << from << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream in(scs);
    if(in.fail())
    {
        std::cerr << "Can't open script file \"" << scs << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    int linenr = 0, emptylines = 0;
    while(!in.eof())
    {
        std::string line;
        std::getline(in, line);
        ++linenr;

        if(line.length() == 0)
        {
            ++emptylines;
            if(emptylines > 100)
                break;
            continue;
        }
        emptylines = 0;

        if(line.at(0) == '#')
            continue;

        tokenizer token(line);

        std::string number = token.next();
        int nr = atoi(number.c_str());
        int frequency = atoi(token.next().c_str());

        /*if(frequency == 0)
        {
            std::cerr << "Script error on line  \"%d\": frequency unparseable or null\n", linenr, nr, frequency);
            return EXIT_FAILURE;
        }*/

        if(number == "copy")
        {
            std::cerr << "Copying item " << frequency << " at line " << linenr << "" << std::endl;
            output.pushC(*input.get(frequency));
            continue;
        }

        libsiedler2::ArchivItem* item = input.get(nr);
        if(frequency == 0 || item == NULL || number == "empty")
        {
            std::cerr << "Inserting empty item at line " << linenr << "" << std::endl;
            output.push(NULL);
            continue;
        }

        if(item->getBobType() != libsiedler2::BOBTYPE_SOUND)
        {
            std::cerr << "Script error on line " << linenr << ": item " << nr << " does not exist or is not a sound" << std::endl;
            return EXIT_FAILURE;
        }

        libsiedler2::ArchivItem_Sound_Wave* wave = dynamic_cast<libsiedler2::ArchivItem_Sound_Wave*>(item);
        if(!wave)
        {
            std::cerr << "Script error on line " << linenr << ": item " << nr << " is not a wave-sound" << std::endl;
            return EXIT_FAILURE;
        }

        std::ofstream tmp;
        std::string filePath = createTempFile(tmp, ".wav");
        if(!tmp)
        {
            std::cerr << "Can't write to temporary file \"" << filePath << "\" - disk full?" << std::endl;
            return EXIT_FAILURE;
        }

        std::vector<unsigned char> data = wave->getData();
        unsigned short bitrate = 8;
        boost::endian::native_to_little_inplace(frequency);
        boost::endian::native_to_little_inplace(bitrate);

        memcpy(&data[24], &frequency, 4);
        memcpy(&data[28], &frequency, 4);
        memcpy(&data[34], &bitrate, 2);

        if(!tmp.write(reinterpret_cast<char*>(&data.front()), data.size()))
        {
            std::cerr << "Can't write to temporary file \"" << filePath << "\" - write failed" << std::endl;
            tmp.close();
            boost::filesystem::remove(filePath);
            return EXIT_FAILURE;
        }
        tmp.close();

        std::string filePath2 = createTempFile(tmp, ".wav");
        if(!tmp)
        {
            std::cerr << "Can't create 2nd temporary file" << std::endl;
            boost::filesystem::remove(filePath);
            return EXIT_FAILURE;
        }
        tmp.close();
        boost::filesystem::remove(filePath2);

        std::stringstream cmd;
        std::string path = argv[0];
        size_t pos = path.find_last_of("/\\");
        cmd << path.substr(0, pos);

#ifdef _WIN32
        cmd << "\\s-c_resample.exe ";
#else
        cmd << "/s-c_resample ";
#endif

        cmd << "-to 44100 ";
        cmd << "\"" << filePath << "\" ";
        cmd << "\"" << filePath2 << "\" ";

        if(system(cmd.str().c_str()) != 0)
        {
            std::cerr << "Resampling failed, using original item" << std::endl;
            if(boost::filesystem::exists(filePath2))
                boost::filesystem::remove(filePath2);
            filePath2 = filePath;
        }else
            boost::filesystem::remove(filePath);

        std::ifstream tmp2(filePath2.c_str(), std::ios_base::binary);
        if(!tmp2)
        {
            std::cerr << "Can't open temporary file \"" << filePath2 << "\" for reading" << std::endl;
            boost::filesystem::remove(filePath2);
            return EXIT_FAILURE;
        }
        tmp2.seekg(0, std::ios_base::end);
        unsigned length = static_cast<unsigned>(tmp2.tellg());
        tmp2.seekg(0, std::ios_base::beg);

        libsiedler2::ArchivItem_Sound_Wave result;
        if(result.load(tmp2, length) != 0)
        {
            std::cerr << "Can't read from temporary file \"" << filePath2 << "\"" << std::endl;
            tmp2.close();
            boost::filesystem::remove(filePath2);
            return EXIT_FAILURE;
        }

        tmp2.close();
        boost::filesystem::remove(filePath2);

        output.pushC(result);
    }
    in.close();

    if(libsiedler2::loader::WriteLST(to, NULL, output) != 0)
    {
        std::cerr << "Conversion failed - was not able to save results to \"" << to << "\"" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Conversion successful\n" << std::endl;

    return EXIT_SUCCESS;
}
