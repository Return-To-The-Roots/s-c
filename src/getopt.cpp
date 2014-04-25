// $Id: getopt.cpp 9360 2014-04-25 15:45:29Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
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
#include <stdio.h>
#include <string.h>

#include "getopt.h"

#ifdef _MSC_VER

int opterr = 1;
int optind = 1;
int optopt = 0;
char* optarg = NULL;

static int lastoptind = 0;

///////////////////////////////////////////////////////////////////////////////
/*
 *  The getopt() function parses the command line arguments.
 *
 *  @param[in] argc      argument count passed to @p main.
 *  @param[in] argv      argument array passed to @p main.
 *  @param[in] optstring list of option characters.
 *
 *  @return option character or @p -1 on failure/no option
 *
 *  @author FloSoft
 */
int getopt(int argc, char* const argv[], const char* optstring)
{
    int index = (optind > 1 || optind == lastoptind) ? optind : 0;

    if(index >= argc)
        return EOF;

    optarg = NULL;

    ++index;
    for(; index < argc; ++index)
    {
        if(argv[index][0] == '-')
        {
            // if '-' as argument, all following are non-arguments
            if(strlen(argv[index]) == 2)
            {
                for(; *optstring; ++optstring)
                {
                    if(argv[index][1] == *optstring)
                    {
                        if(*(optstring + 1) == ':')
                            optarg = argv[++index];

                        lastoptind = optind = index;
                        return *optstring;
                    }
                }
            }
        }
        optind = index;
        return EOF;
    }

    optind = 1;
    return EOF;
}

#endif // _MSC_VER
