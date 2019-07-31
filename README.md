This library provides some constants and some macros that carry out the most basic and important tasks.

MACRO
------------------------------------------------------------------------------------------------------------------
getLength

This macro calculates the number of characters of a string, but it doesen't include the line terminator character.

Parameters:

%1: string whose length must be calculated

Output:

-length: r11

------------------------------------------------------------------------------------------------------------------
print

This macro prints a string to the Standard Output, but it doesn't create a new line.

Parameters:

%1: string to print

Output:

-string: the string is printed to the scree 

------------------------------------------------------------------------------------------------------------------
printLine

This macro prints a string to the Standard Output and creates a new line.

Parameters:

%1: string to print

Output:

-string: the string is printed to the screen

------------------------------------------------------------------------------------------------------------------
exit

This macro terminates the program.
If the macro gets receives a arameter it terminates the program with an error code, otherwise it terminates the
program with error code 0.

Parameters:

%1: error code (integer)

Output:

-The program is terminated.

------------------------------------------------------------------------------------------------------------------
intToString

This macro converts an integer into a string.
In a 64bits architecture the max number it can convert is:18446744073709551615.

Parameters:

%1: number to convert

%2: varable where the string will be stored

Output:

-string: variable passed as parameter

------------------------------------------------------------------------------------------------------------------
printInt

This macro prints and integer to the screen, but it doesn't create a new line.
Parameters:

%1: number to print

%2: varable where the string will be stored

Output:

-string: variable passed as parameter, the string is printed to the screen

------------------------------------------------------------------------------------------------------------------
printLineInt

This macro prints and integer to the screen and creates a new line.
Parameters:

%1: number to print

%2: varable where the string will be stored

Output:

-string: variable passed as parameter, the string is printed to the screen
