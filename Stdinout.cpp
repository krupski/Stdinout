//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.cpp - connect various character devices to standard streams
//  Copyright (c) 2014, 2019 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 6 November 2019
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

#include "Stdinout.h"

// connect stdin, stdout and stderr to same device
void STDINOUT::open (Print &iostr)
{
	open (iostr, iostr, iostr);
}

// connect stdin to input device, stdout and stderr to output device
void STDINOUT::open (Print &instr, Print &outstr)
{
	open (instr, outstr, outstr);
}

// connect each stream to it's own device
void STDINOUT::open (Print &instr, Print &outstr, Print &errstr)
{
	close();

	stdin = fdevopen (0, _getchar0); // setup stdin
	_stream_ptr0 = &instr;

	stdout = fdevopen (_putchar1, 0); // setup stdout
	_stream_ptr1 = &outstr;

	stderr = fdevopen (_putchar2, 0); // setup stderr
	_stream_ptr2 = &errstr;
}

// disconnect stdio from stream(s) & free memory
void STDINOUT::close (void)
{
	fclose (stdin);
	stdin = (FILE *)(0);
	_stream_ptr0 = (Print *)(0);

	fclose (stdout);
	stdout = (FILE *)(0);
	_stream_ptr1 = (Print *)(0);

	fclose (stderr);
	stderr = (FILE *)(0);
	_stream_ptr2 = (Print *)(0);
}

// read a char from stdin
int STDINOUT::_getchar0 (FILE *fp)
{
	// 0: stdin
	while (! (_stream_ptr0->available()));
	return _stream_ptr0->read();
}

// write a char to stdout
int STDINOUT::_putchar1 (char c, FILE *fp)
{
	// 1: stdout
	return _stream_ptr1->print (c) == 0;
}

// write a char to stderr
int STDINOUT::_putchar2 (char c, FILE *fp)
{
	// 2: stderr
	return _stream_ptr2->print (c) == 0;
}

STDINOUT STDIO; // Preinstantiate STDIO object

// end of stdinout.cpp
