//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.cpp - connect various character devices to standard streams
//  Copyright (c) 2014, 2016 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 03 August 2016
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

static Print *stream_ptr0 = NULL; // stdin stream pointer
static Print *stream_ptr1 = NULL; // stdout stream pointer
static Print *stream_ptr2 = NULL; // stderr stream pointer

// connect stdio to all devices
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

	if (stdin == NULL) { // open stdin
		stdin = fdevopen (NULL, getchar0);
		stream_ptr0 = &inpstr;
	}

	if (stdout == NULL) { // open stdout
		stdout = fdevopen (putchar1, NULL);
		stream_ptr1 = &outstr;
	}

	if (stderr == NULL) { // open stderr
		stderr = fdevopen (putchar2, NULL);
		stream_ptr2 = &errstr;
	}
}

// disconnect stdio from stream(s)
void STDINOUT::close (void)
{
	if (stderr) { // close stderr
		fclose (stderr);
		stderr = NULL;
		stream_ptr2 = NULL;
	}

	if (stdout) { // close stdout
		fclose (stdout);
		stdout = NULL;
		stream_ptr1 = NULL;
	}

	if (stdin) { // close stdin
		fclose (stdin);
		stdin = NULL;
		stream_ptr0 = NULL;
	}
}

// return stream connected to FILE (i.e. stdin, stdout or stderr).
Print &STDINOUT::getStream (FILE *fp)
{
	FILE *f[] = { NULL, stdin, stdout, stderr }; // file pointers
	Print *s[] = { NULL, stream_ptr0, stream_ptr1, stream_ptr2 }; // stream pointers
	int8_t x = (sizeof (f) / sizeof (*f)); // pointer count

	while (x--) { // scan through them
		if (f[x] == fp) { // if stdio matches...
			break; // ...return it's pointer
		}
	}
	if (x < 0) {
		x = 0; // found nothing, return NULL
	}
	return *s[x]; // if the loop finishes, return null
}

// Function that fgetc, fread, scanf and related
// will use to read a char from stdin
int STDINOUT::getchar0 (FILE *fp)
{
	if (fp == stdin) {
		while (! (stream_ptr0->available()));  // wait until a character is available...
		return (stream_ptr0->read());  // ...then grab it and return
	} else {
		return _FDEV_ERR;
	}
}

// function that printf and related will use to write
// a char to stdout and auto-add a CR to a LF
int STDINOUT::putchar1 (char c, FILE *fp)
{
	if (fp == stdout) {
		if (c == '\n') { // if linefeed
			stream_ptr1->write ((char) '\r'); // also send CR
		}
		stream_ptr1->write ((char) c);
		return 0;
	} else {
		return _FDEV_ERR;
	}
}

// function that printf and related will use to write
// a char to stdout and auto-add a CR to a LF
int STDINOUT::putchar2 (char c, FILE *fp)
{
	if (fp == stderr) {
		if (c == '\n') { // if linefeed
			stream_ptr2->write ((char) '\r'); // also send CR
		}
		stream_ptr2->write ((char) c);
		return 0;
	} else {
		return _FDEV_ERR;
	}
}

STDINOUT STDIO; // Preinstantiate STDIO object

// end of stdinout.cpp
