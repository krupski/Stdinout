//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.h - connect various character devices to standard streams
//  Copyright (c) 2014, 2017 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 07 June 2017
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

#include <Stream.h>

static Stream *_stream_ptr0 = NULL; // stdin stream pointer (using Stream)
static Print  *_stream_ptr1 = NULL; // stdout stream pointer (using Print)
static Print  *_stream_ptr2 = NULL; // stderr stream pointer (using Print)

class STDINOUT
{
	public: // main functions
		void open (Print &);
		void open (Print &, Print &);
		void open (Print &, Print &, Print &);
		void close (void);
		Print &getStream (FILE *);
	private: // internal functions
		#define _array_size(a)(sizeof(a)/sizeof(*a))
		static int _getchar0 (FILE *); // char read for stdin
		static int _putchar1 (char, FILE *); // char write for stdout
		static int _putchar2 (char, FILE *); // char write for stderr
	public: // virtual functions
		virtual size_t write (uint8_t) { return 0; }
		virtual int available (void) { return 0; }
		virtual int read (void) { return 0; }
};

extern STDINOUT STDIO; // Expose STDIO object

#endif // #ifndef STD_IN_OUT_H

// end of Stdinout.h
