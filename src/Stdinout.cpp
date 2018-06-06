//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.cpp - connect various character devices to standard streams
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

#include "Stdinout.h"

// file pointers
FILE *_file_ptr[3];
// stream pointers
Print *_stream_ptr[3];
// NULL error pointers
Print *_null_stream;

// connect stdin, stdout and stderr to same device
void STDINOUT::open (Print &iostr)
{
	open (iostr, iostr, iostr);
}

// connect stdin to input device, stdout and stderr to output device
void STDINOUT::open (Print &inpstr, Print &outstr)
{
	open (inpstr, outstr, outstr);
}

// connect each stream to it's own device
void STDINOUT::open (Print &inpstr, Print &outstr, Print &errstr)
{
	close();  // close any that may be open

	// 0 == stdin
	_file_ptr[0] = fdevopen (NULL, _getchar0);
	_stream_ptr[0] = &inpstr;

	// 1 == stdout
	_file_ptr[1] = fdevopen (_putchar1, NULL);
	_stream_ptr[1] = &outstr;

	// 2 == stderr
	_file_ptr[2] = fdevopen (_putchar2, NULL);
	_stream_ptr[2] = &errstr;

	_null_stream = NULL;
}

// disconnect stdio from stream(s) & free memory
void STDINOUT::close (void)
{
	for (x = 0; x < 3; x++) { // do stdin, stdout & stderr
		fclose (_file_ptr[x]); // close all (frees memory)
		_file_ptr[x] = NULL; // invalidate pointer
		_stream_ptr[x] = NULL; // invalidate stream
	}
	_null_stream = NULL;
}

// return stream connected to FILE number (0, 1 or 2)
Print &STDINOUT::getStream (int _file_num)
{
	if ((_file_num < 0) || (_file_num > 2)) { // only std in/out/err allowed
		return *_null_stream; // illegal - return null
	} else {
		return *_stream_ptr[_file_num]; // return it's pointer
	}
}

// return stream connected to FILE pointer (stdin, stdout or stderr)
Print &STDINOUT::getStream (FILE *fp)
{
	for (x = 0; x < 3; x++) { // scan through them
		if (_file_ptr[x] == fp) { // if ptr matches...
			return *_stream_ptr[x]; // ...return it's stream pointer
		}
	}
	return *_null_stream; // fell through == error
}

// read a char from stdin
int STDINOUT::_getchar0 (FILE *fp)
{
	// 0 == stdin
	while (! (_stream_ptr[0]->available()));
	return _stream_ptr[0]->read();
}

// write a char to stdout
int STDINOUT::_putchar1 (char c, FILE *fp)
{
	// 1 == stdout
	return _stream_ptr[1]->print ((char) c);
}

// write a char to stderr
int STDINOUT::_putchar2 (char c, FILE *fp)
{
	// 2 == stderr
	return _stream_ptr[2]->print ((char) c);
}

STDINOUT STDIO; // Preinstantiate STDIO object

// end of stdinout.cpp
