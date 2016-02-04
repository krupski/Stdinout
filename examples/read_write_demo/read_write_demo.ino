////////////////////////////////////////////////////////////////////////////////
//
//  read_write_demo.ino - How to use the Stdinout library
//  Copyright (c) 2014, 2016 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 02 February 2016
//
//  This library is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

// include the stdio library.
// note that the "STDIO" object is preinstantiated.
#include <Stdinout.h>

char buffer [64];
int len;
int limit = (sizeof (buffer) / sizeof (*buffer));

void setup (void)
{
	Serial.begin (115200);
	while (!Serial); // wait for serial device to appear (Leonardo type boards only)

	STDIO.open (Serial); // connect the standard IO streams to "Serial"
}

void loop (void)
{
	// print prompt
	fprintf (stdout, "\r\nPlease type something: ");
	// read user data & get character count
	len = readLine (buffer, limit);
	// echo typed data and get another line
	fprintf (stdout,
		"\r\n\r\nYou typed '%s'\r\nWhich contains %d of %d character%s\r\n",
		buffer, len, (limit - 1), (len == 1) ? "" : "s"
	);
	fprintf (stdout, "\r\nHexdump of your data:\r\n");
	hexdump (buffer);
}

// read a line from user into buffer, return char count
int readLine (char *buf, int limit)
{
	int ch;
	int ptr = 0;
	*buf = 0;

	while (1) {

		if ((ch = fgetc (stdin)) == EOF) {
			ptr = 0; // 0 length
			buf[ptr] = 0; // no data
			return EOF;
		}

		if (ch == '\r') {
			buf[ptr] = 0; // mark EOL
			return ptr; // return char count
		}

		if (ch == 0x08) { // backspace
			if (ptr > 0) { // if we CAN backspace....
				ptr--; // move pointer back
				buf[ptr] = 0; // invalidate char
				fprintf (stdout, "\b \b"); // erase char
			}

		} else {

			if ((ptr < (limit - 1)) && (isprint (ch))) { // if we have room...
				buf[ptr] = ch; // put char into buffer
				fputc (ch, stdout); // echo char
				ptr++; // move pointer up one
			}
		}
	}
}

void hexdump (const char *str)
{
	char buf [80];
	char *ptr;
	uint8_t c;
	size_t x, y, len;

	len = (strlen (str) + 1);

	for (x = 0; x < len; x += 16) {

		if ((x % 256) == 0) {
			fprintf (stdout, "\n        +0 +1 +2 +3 +4 +5 +6 +7  +8 +9 +A +B +C +D +E +F\n");
		}

		if ((x % 16) == 0) {
			ptr = buf;
			sprintf (ptr, "%06X ", x);
			ptr = (buf + strlen (buf));
		}

		for (y = 0; y < 16; y++) {
			c = str[ (x + y)];

			if ((y % 8) == 0) {
				sprintf (ptr, " ");
				ptr = (buf + strlen (buf));
			}

			if ((x + y) < len) {
				sprintf (ptr, "%02X ", c);

			} else {
				sprintf (ptr, "   ");
			}

			ptr = (buf + strlen (buf));
		}

		sprintf (ptr, " ");
		ptr = (buf + strlen (buf));

		for (y = 0; y < 16; y++) {
			c = str[ (x + y)];

			if ((x + y) < len) {
				sprintf (ptr, "%c", isprint (c) ? c : '.');

			} else {
				sprintf (ptr, " ");
			}

			ptr = (buf + strlen (buf));
		}

		fprintf (stdout, "%s\n", buf);
	}
}
