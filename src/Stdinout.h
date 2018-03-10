//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.h - connect various character devices to standard streams
//  Copyright (c) 2014, 2018 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 09 February 2018
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

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// file pointers
static FILE *_file_ptr[] = { NULL, NULL, NULL, NULL };
// stream pointers
static Print *_stream_ptr[] = { NULL, NULL, NULL, NULL };
// pointer count (should be 4!)
static uint8_t ptr_cnt = (sizeof(_file_ptr)/sizeof(*_file_ptr));

class STDINOUT
{
	public:
		void open (Print &);
		void open (Print &, Print &);
		void open (Print &, Print &, Print &);
		void close (void);
		Print &getStream (int);
		Print &getStream (FILE *);
	private:
		uint8_t x; // generic loop counter
		static int _getchar0 (FILE *); // char read for stdin
		static int _putchar1 (char, FILE *); // char write for stdout
		static int _putchar2 (char, FILE *); // char write for stderr
};

extern STDINOUT STDIO; // Expose STDIO object

#endif // #ifndef STD_IN_OUT_H

// end of Stdinout.h
