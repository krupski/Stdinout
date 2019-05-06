//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.h - connect various character devices to standard streams
//  Copyright (c) 2014, 2019 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 6 May 2019
//
//  This library is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef STD_IN_OUT_H
#define STD_IN_OUT_H

#include <stdio.h>
#include "Print.h"

static Print *_stream_ptr0; // stdin
static Print *_stream_ptr1; // stdout
static Print *_stream_ptr2; // stderr

class STDINOUT
{
	public:
		void open (Print &);
		void open (Print &, Print &);
		void open (Print &, Print &, Print &);
		void close (void);
	private:
		static int _getchar0 (FILE *); // char read for stdin
		static int _putchar1 (char, FILE *); // char write for stdout
		static int _putchar2 (char, FILE *); // char write for stderr
};

extern STDINOUT STDIO; // Expose STDIO object

#endif // #ifndef STD_IN_OUT_H

// end of Stdinout.h
