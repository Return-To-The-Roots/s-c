// $Id: getopt.h 7521 2011-09-08 20:45:55Z FloSoft $
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
#ifndef GETOPT_H_INCLUDED
#define GETOPT_H_INCLUDED

#ifdef _MSC_VER

#define no_argument			0
#define required_argument	1
#define optional_argument	2

struct option
{
	const char *name;
	int has_arg;
	int *flag;
	int val;
};

extern char *optarg;

extern "C" int getopt(int argc, char *const argv[], const char *optstring);
extern "C" int getopt_long (int argc, char *const argv[], const char *shortopts, const struct option *longopts, int *longind);

#else // _MSC_VER

#include <getopt.h>

#endif // !_MSC_VER

#endif // !GETOPT_H_INCLUDED
