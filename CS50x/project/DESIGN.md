# Design Document - Number Converter

## Introduction
The **Number Converter** is a program that allows users to convert numbers between different formats such as binary, decimal, and hexadecimal. The program was implemented in C language and uses standard libraries such as _stdio.h_, _stdlib.h_, _string.h_, and _ctype.h_.

## Program Flow
The program starts by displaying a welcome message and animation using the function `message_animation()`. The user is then prompted to select the input format for the number they wish to convert, using the `scanf` function to read the user's input. The input format can be 'b' for binary, 'd' for decimal or 'h' for hexadecimal.

The program then uses a switch statement to handle the user's input, and prompts the user to enter the number they wish to convert.
The `strtol` function is used to convert binary numbers entered as a string to decimal. the program then prompts the user to select the output format and uses, this time, if-else statements to handle the output.
The `decimal_to_binary` function is used to convert decimal numbers to binary.

## Error Handling

The program handles invalid input formats by displaying an error message and exiting the program.

## Optimization

The program uses an array to store the binary digits of the decimal number to be converted, in order to optimize the performance of the `decimal_to_binary` function.

## Implementation

The program is implemented in C language using standard libraries such as `stdio.h`, `stdlib.h`, `string.h`, and `ctype.h`.
The **main** function `int main(int argc, char* argv[])` is the entry point of the program. It first checks if the program is executed with any command-line arguments and if so, it prints a usage message and exits.

The program then calls the `message_animation()` function which dispays a welcome message and simulates a loading animation using the `sleep()` function from the `unistd,h` library. The number of loops for the animation is randomly generated using the `srand()` and `rand()` functions from the `time.h` library.

The user is then prompted to select the input format using the `scanf()` function.
The input format is then converted to lowercase using the `tolower()` function from the `ctype.h` library. Depending on the input format selected, the program uses `scanf()` function to read the input number in the appropriate format (binary, decimal, or hexadecimal) and converts it to decimal using the `strtol()` function from the `stdlib.h` library for binary input format.

The user is then prompted to select the output format and the program uses the `printf()` function to dislay the number in the selected format. **_In case of binary_** format, it calls the `decimal_to_binary()` function which converts the decimmal number to binary using a while loop and an array.

The program then exists with a status code of 0 indicating success and any other value (here 1) indicating failure.

## Design Decisions

The program was designed to be simple and user-friendly with a minimalistic approach.
For now, the program only supports three number bases (binary, decimal, and hexadecimal) to keep the complexity low. The program was also designed to handle only one input and one output format at a time.

The choice of C lanaguage for this program was due to its similarity with **Python** and built-in support for handling integers and characters. The use of standard libraries such as `stdio.h`, `stdlib.h`, `string.h`, and `ctype.h` made it easy to implement input/output operations, string manipulation and character conversions.

The program also uses the `unistd.h` library to stimulate the loading animation withthe `sleep()` function, and the `time.h` library to generate random numbersusing the `srand()` and `rand()` functions.

In conclusion, the design decisions taken in this program were based on simplicity, ease of use and maintainability, keeping in mind the scope of the project a the beginning of a new course that introduces programming with Python.