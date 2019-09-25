<h1>StandardLibrary</h1>

<h2>This library provides some constants and some macros that carry out the most basic and important tasks.</h2>

<h3>CONSTANTS</h3>
SYS_READ    equ 0 <br>
SYS_WRITE   equ 1 <br>
SYS_EXIT    equ 60 <br>
<br>
STDOUT      equ 0 <br>
STDIN       equ 1 <br>
STDERR      equ 2 <br>

<h3>MACROS</h3>
<hr>
<b>getLength</b>  <br>
Calculates the number of characters of a string, but it doesn't include the line terminator character.

Parameters:

%1: string whose length must be calculated

Output:

-length: r11

<hr>
<b>printChar</b> <br>
Prints a charcter to the screen, without creating a new line.

Parameters:

%1: character to print

Output:

-char: the character is printed to the screen (Standard Output).

<hr>
<b>print</b> <br>
Prints a string to the screen, but it doesn't create a new line.

Parameters:

%1: string to print

Output:

-string: the string is printed to the screen (Standard Output)

<hr>
<b>printLine</b> <br>
Prints a string to the screen and creates a new line.

Parameters:

%1: string to print

Output:

-string: the string is printed to the screen (Standard Output)

<hr>
<b>printInt</b> <br>
Prints and integer to the screen, but it doesn't create a new line.
Parameters:

%1: number to print

%2: varable where the string will be stored

Output:

-string: variable passed as parameter, the string is printed to the screen (Standard Output)

<hr>
<b>printLineInt</b> <br>
Prints and integer to the screen and creates a new line.
Parameters:

%1: number to print

%2: varable where the string will be stored

Output:

-string: variable passed as parameter, the string is printed to the screen (Standard Output)

<hr>
<b>intToString</b> <br>
Converts an integer into a string.
In a 64bits architecture the max number it can convert is:18446744073709551615.

Parameters:

%1: number to convert

%2: varable where the string will be stored

Output:

-string: variable passed as parameter

<hr>
<b>stringToInt</b> <br>
Converts a string containing only digits into an integer number.
If the string contains other characters besides digits, the program execution
is stopped with error code: 100.
In a 64bits architecture the max string it can convert is:"18446744073709551615".

Parameters:

%1: string to be converted

Output:

-int: r11

<hr>
<b>readChar</b> <br>
Reads a character from the user's keyboard.

Output:

-char: r11

<hr>
<b>read</b> <br>
Reads a string of predefined length from the user's keyboard.

Parameters:

%1: variable where the string will be stored

%2: number of characters to read, it must be left a byte free for the termination character,
    or a Segmentation Error will be caused.

Output:

-string: variable passed as parameter

<hr>
<b>readInt</b> <br>
Reads an integer from the user keyboard.

Parameters:

%1: variable where the string will be stored

%2: number of characters to read, it must be left a byte free for the termination character,
    or a Segmentation Error will be caused.

Output:

-int: r11

<hr>
<b>fileOpen</b> <br>
Opens a file and returns its file descriptor.

Parameters:

%1: path of the file (string 0 terminated).

%2: value of the flag to use to open the file.
%3: octal value to indicates the file permissions.

Output:

-int r11

<hr>
<b>filePrint</b> <br>
Writes a line into a file, without creating a new line.

Parameters:

%1: file descriptor of the file in which write into.

%2: string to write into the file.

Output:

The string is printed into the file

<hr>
<b>filePrintLine</b> <br>
Writes a line into a file, and creates a new line.

Parameters:

%1: file descriptor of the file in which write into.

%2: string to write into the file.

Output:

The string is printed into the file

<hr>
<b>fileRead</b> <br>
Reads some characters from the file and return the number of characters read.

Paramters:

%1: file descriptor of the file from which read.

%2: variable where the string will be stored.

%3: number of characters to read, it should be left a byte free for the termination character.

Output:

-int r11

<hr>
<b>fileClose</b> <br>
Closes a file.

Paramters:

%1: file descriptor of the file to close.

Output:

-The file is closed.

<hr>
<b>fileGetOffset</b> <br>
Return the actual offset of the file cursor.

Parameters:

%1: file descriptor of the file.

Output:

-int r11

<hr>
<b>fileMoveToBeginning</b> <br>
Moves the file cursor to the beginning of the file, and returns the new offset.

Paramters:

%1: file descriptor of the file.

Output:

-int r11

<hr>
<b>fileMoveToEnd</b> <br>
Moves the file cursor to the end of the file, and returns the new offset.

Paramters:

%1: file descriptor of the file.

Output:

-int r11

<hr>
<b>sleep</b> <br>
It pauses the program execution from some time.

Paramters:

%1: timespec structure that indicates the pause length.

%2: timespec structure that holds the remaining pause time, but it is optional because it is usefull only
    when the pause can be stopped and is necessary to finish the pause after the pause break.

Output:

-The program execution stops for a while.

<hr>
<b>exit</b> <br>
Terminates the program.
If the macro receives a parameter it terminates the program with an error code, otherwise it terminates the
program with error code 0.

Parameters:

%1: error code (integer)

Output:

-The program is terminated. 

<hr>



<em>More info about the macros into the file standardlib.inc</em>
