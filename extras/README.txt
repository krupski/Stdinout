////////////////////////////////////////////////////////////////////////////////
//
//  README.txt - Documentation for Stdinout library
//  Copyright (c) 2014, 2015 Roger A. Krupski <rakrupski@verizon.net>
//
//  Last update: 10 January 2015
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
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
  (Before you begin: if you do not know what standard IO streams are, read
  the section "STANDARD STREAMS EXPLAINED" at the bottom first).
////////////////////////////////////////////////////////////////////////////////


//_____________________________________________________________________________________
//                                                                     FUNCTION SUMMARY

  STDIO.open (device); // where "device" can be Serial, LCD or other character device.
  STDIO.close (); // close previously opened stream. Returns 48-some bytes to Arduino.
  STDIO.getStream (stream); // returns the device connected to stream.

//_____________________________________________________________________________________
//                                                               WHAT THIS LIBRARY DOES

Although the GNU C compiler used by the Arduino development environment provides the
ability to use the standard IO streams, these are not setup by default. Additionally,
the coding to implement standard IO streams is rather cumbersome and therefore either
unknown to most Arduino users or simply not bothered with.

As a result, most Arduino users are forced to build up a simple line of text using
multiple "Serial.print" lines. This is tedious, error prone and requires several
edits to get it right (ever forget the space between text and a variable?)

More advanced users may define a generic buffer, then use "sprintf" to build their
string in the buffer "printf style", then print the whole finished string using
"Serial.print (buffer)".

But wouldn't it be even nicer if you could just use "printf" directly?

Well, you can. This library makes using the standard IO streams as easy as possible,
as well as providing the ability to connect almost any device (serial port, LCD
display, etc..) to the standard IO streams.


//_____________________________________________________________________________________
//                                                                        HOW TO USE IT

After importing this library into your Arduino system, you need to do the following
things in order to use it:

(1) Include the library in your sketch using "#include <Stdinout.h>" (see example
    code).

(2) Connect a device to the standard IO streams using the STDIO.open () function
    (again, see the example code).

(3) Use "printf", "fprintf", "scanf", "getchar", "fgetc", etc... as shown in any
    C/C++ documentation.

(4) Although you do not need to close the standard IO streams after you have used them
    you may if you wish. Additionally, if you wish to connect something else to the
    standard IO streams, you do NOT need to close the first one before opening the
    next one. If you are finished printing entirely, then you should call STDIO.close()
    because it will release around 40 to 48 bytes of SRAM buffer back to Arduino.

(5) The "STDIO.open(xxx)" function automatically closes any previously opened streams
    before opening a new one. For example, if you use the my modified LiquidCrystal library
    which supports streams, you can simply "STDIO.open (LCD)" to disconnect the standard
    IO streams from what they were connected to before (probably Serial) and then connect
    them to the LCD device. Now, "printf" calls will be displayed on the LCD screen
    instead of the serial terminal!

(6) (Just a note): The "STDIO" object is preinstantiated, so all you need to do
    is use it. The object is preinstantiated because unlike other libraries, you
    will never need more than one. FYI, "Serial" is another preinstantiated object.

(7) You can connect several different devices to the standard streams. For example, you
    can connect stdin to the serial port and stdout to an lcd display, like this:
    STDIO.open (Serial, LCD); // assuming that LCD is already instantiated and supports
    streams (FYI, the stock Arduino Liquid Crystal library does NOT, but mine DOES).
    You can even send data to stdout and stderr separately. For example, to read stdin
    data from the serial port, write stdout to an lcd and write stderr to a different
    lcd device (again, assuming they are already instantiated and support streams), use:
    STDIO.open (Serial, LCD1, LCD2); // stdout goes to LCD1 and stderr goes to LCD2!

(8) The included demo program contains all the information you need to use this
    library. It's actually very simple to use, and the demo will tell you all that
    you need to know.

(9) Any of the following are legal and correct:

    STDIO.open (device); // connects stdin, stdout and stderr to "device".

    STDIO.open (device1, device2); // connects stdin to "device 1", both stdout and
    stderr to "device2".

    STDIO.open (device1, device2, device3); // connects stdin to "device1", stdout
    to "device2" and stderr to "device3".

    STDIO.open (device1, device2, device1); // connects stdin and stderr to "device1"
    and stdout to "device2".

    (any combination is acceptable).

//_____________________________________________________________________________________
//                                                           STANDARD STREAMS EXPLAINED

In most operating systems and code compilers, there exist several pre-defined
input and output streams to make printing text to devices and reading text from
devices easy. These are "Standard Input", "Standard Output" and "Standard Error".

For example, if a C program uses the "printf" function, it is sending it's data
to the Standard Output stream. Standard Output always exists. There is no need
to "open" the stream to print data.

Likewise, functions to get or scan data (getc, getchar, scanf) read the Standard
Input stream (which also always exists).

There exists another pre-defined stream called "Standard Error" which is an output
stream, but treated differently from Standard Output.

For example, if you do not wish to see what a program is printing, you can re-direct
it's output to a null device such as "/dev/null" or redirect it to a file for later
study. You do this by using the ">" symbol (example: myprogram > record.txt).

That example would run your program called "myprogram" and send it's screen output
to a file called "record.txt".

But what if your program printed an error message? You would never see it until you
read the "record.txt" file!

That's where the Standard Error stream comes in. Standard Error prints to the screen
normally, but if you re-direct Standard Output to null or a file, Standard Error will
STILL display on the screen.


//_____________________________________________________________________________________
//                                                                     LAST INSTRUCTION

ENJOY!!!

-- eof --
