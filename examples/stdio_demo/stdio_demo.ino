////////////////////////////////////////////////////////////////////////////////
//
//  stdio_demo.ino - How to use the Stdinout library
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

// not needed by the library - just for the demo only
#include "memoryFree.h"

// these vars are just for the demo - the library does not need them
int a = 2; // demo
int b = 5; // numbers
int c = (a + b); // sum of them

int mem_before; //
int mem_after;  // for reporting memory usage
int mem_used;   //

void setup (void)
{
	Serial.begin (115200);

	while (!Serial); // wait for serial device to appear (Leonardo type boards only)

	STDIO.open (Serial); // connect the standard IO streams to "Serial"

	// this is the original "Arduino hard way" to print things
	Serial.println(); // just a new line
	Serial.print ("The hard way..."); // first part of the string
	Serial.println(); // next line
	Serial.print ("The sum of "); // next part of the string
	Serial.print ((int) a); // first number
	Serial.print (" and "); // string
	Serial.print ((int) b); // next number
	Serial.print (" is "); // string
	Serial.print ((int) c); // sum of a and b
	Serial.println(); // new line

	// this is our new, easy way to do it
	printf ("\r\nThe easy way...\r\nThe sum of %d and %d is %d\r\n", a, b, (a + b));


	// get a copy of the stream connected to standard io
	Stream &str = STDIO.getStream (stdout);

	// print using one, then the other
	Serial.print ("\r\nPrinted using Serial.print()\r\n");
	str.print ("\r\nPrinted using str.print()\r\n");

	// ram usage when STDIO is active
	mem_before = freeMemory();

	// print result
	Serial.print ("\r\nFree memory before STDIO close: ");
	Serial.print ((int) mem_before);
	Serial.print (" bytes\r\n");

	// disconnect the standard streams if you want to
	// (not required, but frees about 48 bytes of SRAM)
	STDIO.close();

	// ram usage after STDIO is closed
	mem_after = freeMemory();
	// calculate difference
	mem_used = (mem_after - mem_before);

	// print result
	Serial.print ("\r\nFree memory after STDIO close: ");
	Serial.print ((int) mem_after);
	Serial.print (" bytes\r\n");

	// print difference
	Serial.print ("\r\nMemory used by Stdinout: ");
	Serial.print ((int) mem_used);
	Serial.print (" bytes\r\n");

}

void loop (void)
{
	// nothing
}
