# Number Converter

#### Video Demo: https://youtu.be/gTvI4iPJbEg

#### Description:
This program is a simple command-line utility that allows the user to convert
numbers between decimal, binary, and hexadecimal formats.
The program is written in **C** and uses standard librairies `stdio.h`, `stdlib.h`,
`string.h` and `ctype.h`. It also uses the `unistd.h` and `time.h` librairies to
add a loading animation and randomize the animation.

## Getting started

To run the program, you will need to have a C compiler installed on your computer.
The program can be compiled by running the command `gcc -o number_converter number_converter.c`
in the terminal.

Once the program is compiled, it can be run by entering `./number_converter`in the terminal.

## Using the program

When the program is run, it will display a welcome message and a loading animation.
  > The program uses `srand()` method to display 1 to 3 text animations randomly.
After the animation is complete, the program will promt the user to select the input format
for the number they wish to convert. The options are:
- `b` for binary
- `d` for decimal
- `h` for hexadecimal.

Once the input format is selected, the program will prompt the user to enter the number
they wish to convert.
If the user selects binary or hexadecimal, the number will be considered
a string.
If the user selects decimal, the number will be considered an integer.

After the number is entered, the program will prompt the user to select the output
format for the conversion. The options are the same as the input format:
- `b` for binary
- `d` for decimal
- `h` for hexadecimal.

Once the output format is selected, the program will display the converted number
and exit.

## Limitations

This program has few limitations that should be considered when using it:
* The program can only convert integers, not fractions or floating point numbers.
* The program does not check for invalid input, such as non-numeric
characters or numbers that are out of range for the chosen format.
* The program does not support additional number bases such as octal or base64.

## Future Work

There are several ways that this program could be improved in the future.
Some potential ideas include:
- [ ]  Adding support for additional number bases such as octal or base64.
- [ ] Allowing the user to enter a number in one format and convert it
to multiple formats at once.
- [ ] Implementing error checking for invalid input, such as non-numeric
characters or numbers that are out of range for the chosen format.
- [ ] Adding a GUI with options such as drop-down menus or buttons
to make the program more intuitive to use.-
- [ ] Implementing a feature to save the previous conversions made
by the user for easy access and tracking.
- [ ] Adding the ability to convert numbers to and from other
number systems such as Roman numerals or Mayan numerals.
-[ ] Implementing a feature to allow the user to input a number in a more
natural way, such as "one hundred" instead of "100".
- [ ] Implementing a feature that allows the user to input numbers in
different languages (i.e: arabic) and converts them to the desired format.
- [ ] Adding the ability to **perform arithmetic operations** on
numbers
- [ ] Adding a feature that allows the user to input fractions and convert
them to the desired format.

Overall, the number converter program is a useful tool for anyone who needs
to convert numbers between different formats.
With the addition of these features and improvements, the program will
become even more versatile and user-friendly.

If yu have any questions or feedback about **"Number Converter"**, please
feel free to contact me at jl.turquin@diffrenzz.com.