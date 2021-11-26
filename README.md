# The Brainf*** Interpreter

## About

This repository contains the source code for a Brainf*** interpreter. The program will read from a file assuming it is written in the BF language. 
The BF program is given 30,000 memory cells that can go up to a value of 255.
By default, when outputting a cell value, the character for that code is output. For example, a cell with a value of 65 will output "A".
 
## Running the BFI

### Getting BFI

As of right now, the binary executable is not included in the repository while it is still being worked on. However, you can still
download and compile it on your machine. Just make sure you have a C++ compiler that supports C++11 and/or Makefiles.

At the top right of the repository, click ```Code``` and ```Download Zip```. Extract it to where you want. Open a terminal or command line and either compile
it yourself with your own flags, or use the ```Makefile``` included.

To compile using the ```Makefile```, simply type into the command line:

```make```

### Running BF Code

There are several files included in the ```test``` folder that contains simple BF code.
To run a BF file, type the following into a command line after compiling:

##### Windows:

```bfi.exe [-options] [filename]```
##### Unix:

```bfi [-options] [filename]```

Replacing ```[filename]``` with the name of the file you want to run.

#### Command Line Flags/Options

This BF Interpreter currently supports 3 options/flags for use while running BF Code. They are:

```-h --help```: Display information about the BFI and the available flags.

```-e --explicit```: This flag enables printing of both the integral value and the character value for a cell.
This option should be used for debugging, without the extra information that comes with the next flag.

```-d --debug```: This flag will display information about the current pointer, its cell value, and adjacent cell values, whenever an operation is performed.
It also displays the line of the current operation in the file running as ```[filename]:[line]:[column]```
Example debug output:

```
./example.bf:1:38 +
|...| ...
| 23| 9
|  1| 10 <-
|  0| 11
|...| ...
```
The cell's value is denoted by ```|```, and the pointer is denoted by the number next to the cell. The ```<-``` denotes where the program's current pointer is.

#### Errors/Exceptions

###### Out of Bounds

In this implementation of BF, pointers are not allowed to go below the minimum address (0) nor above the maximum address (30000).
Trying to do so will result in an Out of Bounds exception and the program will terminate with an exit code of 1.

###### Value Error

Since cell values are representative of ASCII characters, values cannot go below 0 or above 255. Trying to do so will result in a Value Error and 
terminate the program with an exit code of 1.

###### Syntax Error

There is not a lot of syntax in BF, so these error are rare. The only time a syntax error can occur is if one uses an end loop character "]" before
starting a loop with "[". A syntax error will terminate the program with an exit code of 1.

##### NOTE:

Since this is an interpreter, errors will only occur at Runtime (I.E. there are no compile errors).

### Actually Writing Brainf*** Code
BF code itself is rather simple, but requires a good bit of thinking, since it is not immediately clear what anything does.
This section will lay out all valid BF operations.

```+```: Adds 1 to the cell value the current pointer is at.

```-```: Subtracts 1 from the cell value the current pointer is at.

```>```: Adds 1 to the pointer (I.E. move pointer from cell 1 to cell 2).

```<```: Subtracts 1 from the pointer (I.E. move pointer from cell 2 to cell 1).

```.```: Output the value in the current pointer's cell.

```,```: Input a value to the current pointer's cell. NOTE: This will overwrite any value already stored in this pointer's cell.

Additionally, user input above 255 will be truncated to the first digit (I.E. input of 342 is truncated to 3). Currently, there is no
check for a value under 0.

```[```: Denotes the beginning of a loop.

```]```: Denotes the end of a loop. Loops will only exit when the current pointer's cell value is 0. As of right now, there is no check for infinite loops.

To comment, simply type your comment where you would like. Any character that is not one of the eight above will be ignored along with the rest of the line.
This is shown in the below example.

#### Example Program

This program displays Hello World! to the terminal/command line (taken from Wikipedia https://en.wikipedia.org/wiki/Brainfuck):

```
[ This program prints "Hello World!" and a newline to the screen, its
  length is 106 active command characters. [It is not the shortest.]

  This loop is an "initial comment loop", a simple way of adding a comment
  to a BF program such that you don't have to worry about any command
  characters. Any ".", ",", "+", "-", "<" and ">" characters are simply
  ignored, the "[" and "]" characters just have to be balanced. This
  loop and the commands it contains are ignored because the current cell
  defaults to a value of 0; the 0 value causes this loop to be skipped.
]
++++++++               Set Cell #0 to 8
[
    >++++               Add 4 to Cell #1; this will always set Cell #1 to 4
    [                   as the cell will be cleared by the loop
        >++             Add 2 to Cell #2
        >+++            Add 3 to Cell #3
        >+++            Add 3 to Cell #4
        >+              Add 1 to Cell #5
        <<<<-           Decrement the loop counter in Cell #1
    ]                   Loop until Cell #1 is zero; number of iterations is 4
    >+                  Add 1 to Cell #2
    >+                  Add 1 to Cell #3
    >-                  Subtract 1 from Cell #4
    >>+                 Add 1 to Cell #6
    [<]                 Move back to the first zero cell you find; this will
                        be Cell #1 which was cleared by the previous loop
    <-                  Decrement the loop Counter in Cell #0
]                       Loop until Cell #0 is zero; number of iterations is 8

The result of this is:
Cell no :   0   1   2   3   4   5   6
Contents:   0   0  72 104  88  32   8
Pointer :   ^

>>.                     Cell #2 has value 72 which is 'H'
>---.                   Subtract 3 from Cell #3 to get 101 which is 'e'
+++++++..+++.           Likewise for 'llo' from Cell #3
>>.                     Cell #5 is 32 for the space
<-.                     Subtract 1 from Cell #4 for 87 to give a 'W'
<.                      Cell #3 was set to 'o' from the end of 'Hello'
+++.------.--------.    Cell #3 for 'rl' and 'd'
>>+.                    Add 1 to Cell #5 gives us an exclamation point
>++.                    And finally a newline from Cell #6
```
## Features to be Implemented

- Currently, the debugging information can be a bit hard for new users to this interpreter to make sense of. Adding breakpoints in BF code and another flag for use of
breakpoints is a feature that is planned to be implemented.

- More features may be thought of as they arise.

## Current Features

Basically everything listed in the Flags section:

- One-pass file reading and interpretation
- Debugging information
- Explicit output of cell value and character representation

## Contributing

This project is open to contributers. Specifically, anyone willing to add additional information or clean debugging messages would be appreciated. 
Help with creating a much more well-rounded ```Makefile``` would also be appreciated.
If you have any ideas or have implemented a new feature, just issue a PR and it will be reviewed.

## Licensing

See the LICENSE file for licensing information. In short, this project uses the Apache 2.0 License.
