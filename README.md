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
Calculates the number of characters of a string, but it doesen't include the line terminator character.

Parameters:

%1: string whose length must be calculated

Output:

-length: r11

<hr>
<b>print</b> <br>
Prints a string to the Standard Output, but it doesn't create a new line.

Parameters:

%1: string to print

Output:

-string: the string is printed to the screen (Standard Output)

<hr>
<b>printLine</b> <br>
Prints a string to the Standard Output and creates a new line.

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
<b>read</b> <br>
Reads a string of predefined length from the user's keyboard.

Parameters:

%1: variable where the string will be stored

%2: number of characters to read, it must be left a byte free for the termination character,
    or a Segmentation Error will be caused.

Output:

-string: variable passed as parameter

<hr>
<b>exit</b> <br>
Terminates the program.
If the macro gets receives a arameter it terminates the program with an error code, otherwise it terminates the
program with error code 0.

Parameters:

%1: error code (integer)

Output:

-The program is terminated. 

<hr>