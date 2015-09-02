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
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fstream>
#include <sstream>

#ifdef _WIN32
#   include <windows.h>
#   define unlink DeleteFileA
#   ifdef _MSC_VER
#       define snprintf _snprintf
#   endif
#endif

#ifdef __GNUC__
#include <unistd.h>
#endif

#include "getopt.h"
#include "tempname.h"
#include "tokenizer.hpp"

#include "../../libsiedler2/src/libsiedler2.h"
#include "../../libendian/src/libendian.h"
#include "../../libendian/src/endianess.h"

int usage(int argc, char* argv[])
{
    printf("Usage: %s -s script.scs -f source.lst -t destination.lst", argv[0]);

    return EXIT_FAILURE;
}

void myexit()
{
    //printf("Press enter to exit\n");
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

    printf("Starting samplerate conversion\n\n");
    printf("Input file: \"%s\"\n", from);
    printf("Output file: \"%s\"\n", to);
    printf("using Script: \"%s\"\n\n", scs);

    libsiedler2::ArchivInfo input, output;
    if(libsiedler2::Load(from, &input) != 0)
    {
        printf("Can't open input file \"%s\"\n", from);
        return EXIT_FAILURE;
    }

    std::ifstream in(scs);
    if(in.fail())
    {
        printf("Can't open script file \"%s\"\n", scs);
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
            printf("Script error on line  \"%d\": frequency unparseable or null\n", linenr, nr, frequency);
            return EXIT_FAILURE;
        }*/

        if(number == "copy")
        {
            printf("Copying item %d at line \"%d\"\n", frequency, linenr);
            output.pushC(input.get(frequency));
            continue;
        }

        libsiedler2::ArchivItem* item = input.get(nr);
        if(frequency == 0 || item == NULL || number == "empty")
        {
            printf("Inserting empty item at line \"%d\"\n", linenr);
            output.pushC(NULL);
            continue;
        }

        if(item->getBobType() != libsiedler2::BOBTYPE_SOUND)
        {
            printf("Script error on line  \"%d\": item %d does not exist or is not a sound\n", linenr, nr);
            return EXIT_FAILURE;
        }

        libsiedler2::ArchivItem_Sound_Wave* wave = dynamic_cast<libsiedler2::ArchivItem_Sound_Wave*>(item);
        if(!wave)
        {
            printf("Script error on line  \"%d\": item %d is not a wave-sound\n", linenr, nr);
            return EXIT_FAILURE;
        }

        char file[256];
        if(!tempname(file, 256))
        {
            printf("Can't find first temporary filename for conversion?\n");
            return EXIT_FAILURE;
        }
        //strncat(file, ".wav", 256);

        char file2[256];
        if(!tempname(file2, 256))
        {
            printf("Can't find second temporary filename for conversion?\n");
            return EXIT_FAILURE;
        }
        //strncat(file2, ".wav", 256);

        FILE* tmp = fopen(file, "wb");
        if(!tmp)
        {
            printf("Can't write to temporary file \"%s\" - disk full?\n", file);
            return EXIT_FAILURE;
        }

        unsigned char* data = new unsigned char[wave->getLength()];
        memcpy(data, wave->getData(), wave->getLength());
        unsigned short bitrate = 8;
#if BYTE_ORDER == BIG_ENDIAN
        frequency = libendian::swap_i(frequency);
        bitrate = libendian::swap_us(bitrate);
#endif
        memcpy(&data[24], &frequency, 4);
        memcpy(&data[28], &frequency, 4);
        memcpy(&data[34], &bitrate, 2);

        if(fwrite(data, 1, wave->getLength(), tmp) != wave->getLength())
        {
            printf("Can't write to temporary file \"%s\" - write failed\n", file);
            return EXIT_FAILURE;
        }
        fflush(tmp);
        fclose(tmp);

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
        cmd << "\"" << file << "\" ";
        cmd << "\"" << file2 << "\" ";

        unlink(file2);

        if(system(cmd.str().c_str()) != 0)
        {
            printf("Resampling failed, using original item\n");
            strcpy(file2, file);
            //return EXIT_FAILURE;
        }

        FILE* tmp2 = fopen(file2, "rb");
        if(!tmp2)
        {
            printf("Can't open temporary file \"%s\" for reading\n", file2);
            return EXIT_FAILURE;
        }
        fseek(tmp2, 0, SEEK_END);
        unsigned int length = (unsigned int)ftell(tmp2);
        fseek(tmp2, 0, SEEK_SET);

        libsiedler2::ArchivItem_Sound_Wave result;
        if(result.load(tmp2, length) != 0)
        {
            printf("Can't read from temporary file \"%s\"\n", file2);
            return EXIT_FAILURE;
        }
        fclose(tmp2);

        unlink(file);
        unlink(file2);

        output.pushC(&result);
    }
    in.close();

    if(libsiedler2::loader::WriteLST(to, NULL, &output) != 0)
    {
        printf("Conversion failed - was not able to save results to \"%s\"\n", to);
        return EXIT_FAILURE;
    }

    printf("Conversion successful\n\n");

    return EXIT_SUCCESS;
}
