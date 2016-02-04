//////////////////////////////////////////////////////////////////////////////
//
//  Stdinout.cpp - connect various character devices to standard streams
//  Copyright (c) 2014, 2016 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 26 January 2016
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

// connect stdio to all devices
void STDINOUT::open (Stream &iostr)
{
	open (iostr, iostr, iostr);
}

// connect stdin to input device, stdout and stderr to output device
void STDINOUT::open (Stream &inpstr, Stream &outstr)
{
	open (inpstr, outstr, outstr);
}

// connect each stream to it's own device
void STDINOUT::open (Stream &inpstr, Stream &outstr, Stream &errstr)
{
	close(); // close any that may be open

	if (&inpstr) { // open stdin
		stdin = fdevopen (NULL, getchar0);
		stream_ptr0 = &inpstr;
	}

	if (&outstr) { // open stdout
		stdout = fdevopen (putchar1, NULL);
		stream_ptr1 = &outstr;
	}

	if (&errstr) { // open stderr
		stderr = fdevopen (putchar2, NULL);
		stream_ptr2 = &errstr;
	}
}

// return stream connected to FILE (i.e. stdin, stdout or stderr).
Stream &STDINOUT::getStream (FILE *fp)
{
	FILE *f[] = { stdin, stdout, stderr, }; // file pointers
	Stream *s[] = { stream_ptr0, stream_ptr1, stream_ptr2, }; // stream pointers
	uint8_t x = (sizeof (f) / sizeof (*f)); // pointer count

	while (x--) { // scan through them
		if (f[x] == fp) { // if stdio matches...
			return *s[x]; // ...return it's pointer
		}
	}

	stream_null = NULL; // no match found...
	return *stream_null; // ...so return null
}

// disconnect stdio from stream(s)
void STDINOUT::close (void)
{
	if (stdin) { // close stdin
		fclose (stdin);
		stdin = NULL;
		stream_ptr0 = NULL;
	}

	if (stdout) { // close stdout
		fclose (stdout);
		stdout = NULL;
		stream_ptr1 = NULL;
	}

	if (stderr) { // close stderr
		fclose (stderr);
		stderr = NULL;
		stream_ptr2 = NULL;
	}
}

// Function that scanf and related will use to read a char from stdin
int STDINOUT::getchar0 (FILE *fp)
{
	while (! (stream_ptr0->available())); // wait until a character is available...
	return (stream_ptr0->read()); // ...then grab it and return
}

// function that printf and related will use to write a char to stdout
// auto-add a CR to a LF
int STDINOUT::putchar1 (char c, FILE *fp)
{
	if (c == '\n') { // \n sends crlf
		putchar1 ((char) '\r', fp);
	}
	stream_ptr1->write (c); // send one character to device
	return 0;
}

// function that printf and related will use to write a char to stderr
// auto-add a CR to a LF
int STDINOUT::putchar2 (char c, FILE *fp)
{
	if (c == '\n') { // \n sends crlf
		putchar2 ((char) '\r', fp);
	}
	stream_ptr2->write (c); // send one character to device
	return 0;
}

STDINOUT STDIO; // Preinstantiate STDIO object

// end of stdinout.cpp
