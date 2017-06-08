//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.cpp - connect various character devices to standard streams
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

#include <Stdinout.h>

// connect stdin, stdout and stderr to same device
void STDINOUT::open (Print &iostream)
{
	open (iostream, iostream, iostream);
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

	stdin = fdevopen (NULL, _getchar0);
	_stream_ptr0 = (Stream *)(&inpstr);

	stdout = fdevopen (_putchar1, NULL);
	_stream_ptr1 = &outstr;

	stderr = fdevopen (_putchar2, NULL);
	_stream_ptr2 = &errstr;
}

// disconnect stdio from stream(s)
void STDINOUT::close (void)
{
	fclose (stdin);
	stdin = NULL;
	_stream_ptr0 = NULL;

	fclose (stdout);
	stdout = NULL;
	_stream_ptr1 = NULL;

	fclose (stderr);
	stderr = NULL;
	_stream_ptr2 = NULL;
}

// return stream connected to FILE (i.e. stdin, stdout or stderr).
Print &STDINOUT::getStream (FILE *fp)
{
	FILE *f[] = { NULL, stdin, stdout, stderr }; // file pointers
	Print *s[] = { NULL, _stream_ptr0, _stream_ptr1, _stream_ptr2 }; // stream pointers
	int8_t x = _array_size(f); // pointer count

	while (x--) { // scan through them
		if (f[x] == fp) { // if stdio matches...
			break; // ...return it's pointer
		}
	}

	if (x < 0) { // x == -1 if search fails
		x = 0; // found nothing, return s[0] (NULL)
	}

	return *s[x]; // if the loop finishes, return null
}

// Function that fgetc, fread, scanf and related
// will use to read a char from stdin
int STDINOUT::_getchar0 (FILE *fp)
{
	while (! (_stream_ptr0->available()));  // wait until a character is available...
	return (_stream_ptr0->read());  // ...then grab it and return
}

// function that printf and related will use to write
// a char to stdout and auto-add a CR to a LF
int STDINOUT::_putchar1 (char c, FILE *fp)
{
	if (c == '\n') { // if linefeed
		_stream_ptr1->write ((char) '\r'); // also send CR
	}
	_stream_ptr1->write ((char) c);
	return 0;
}

// function that printf and related will use to write
// a char to stderr and auto-add a CR to a LF
int STDINOUT::_putchar2 (char c, FILE *fp)
{
	if (c == '\n') { // if linefeed
		_stream_ptr2->write ((char) '\r'); // also send CR
	}
	_stream_ptr2->write ((char) c);
	return 0;
}

STDINOUT STDIO; // Preinstantiate STDIO object

// end of stdinout.cpp
