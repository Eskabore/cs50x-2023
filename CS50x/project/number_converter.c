/**
 * Title: Number Converter
 * Author: Eskabore
 * Purpose: Program converts a number between binary, decimal, and hexadecimal formats.
 * Language: C
*/

#include <stdio.h> // For input and output operations
#include <stdlib.h> // For strtol() function
#include <string.h> // For strlen() function
#include <ctype.h> // For tolower() function
#include <unistd.h> // For sleep() function
#include <time.h> // For time() function used in srand()


// Declare function prototypes
void decimal_to_binary(int n); // function to convert decimal to binary
void message_animation(); // funnction to display welcome and loading animation


int main(int argc, char *argv[])
{
    // Check if program has been run with any command line arguments
    if (argc != 1)
    {
        printf("Usage: %s Press 'enter'\n", argv[0]);
        return 1;
    }

    // Display welcome message and loading animation
    message_animation();

    char input_format;
    int number;

    // Prompt user to select input format
    printf("Select the input format (b for binary, d for decimal, h for hexadecimal): ");
    scanf("%c", &input_format);
    input_format = tolower(input_format);

    // Variable to store binary number entered as string
    char binary_str[32];

    // Based on input format, prompt user to enter number and convert input to integer
    switch (input_format)
    {
        case 'b':
            printf("Enter the binary number: ");
            scanf("%s", binary_str);
            number = strtol(binary_str, NULL, 2); // converts binary string to integer
            break;

        case 'd':
            printf("Enter the decimal number: ");
            scanf("%d", &number);
            break;

        case 'h':
            printf("Enter the hexadecimal number: ");
            scanf("%x", &number);
            break;

        default:
            printf("Invalid format: %c\n", input_format);
            return 1;
    }

    // Variable to store user selected output format
    char output_format;

    // Prompt user to select output format
    printf("Select the output format (b for binary, d for decimal, h for hexadecimal): ");
    scanf(" %c", &output_format);
    output_format = tolower(output_format);

    // Based on output format, display number in chosen format
    if (output_format == 'b')
    {
        decimal_to_binary(number);
        printf("\n");
    }
    else if (output_format == 'd')
    {
        printf("Decimal: %d\n", number);
    }
    else if (output_format == 'h')
    {
        printf("Hexadecimal: %x\n", number);
    }
    else
    {
        printf("Invalid format: %c\n", output_format);
        return 1;
    }

    return 0;
}

// Function to convert decimal number to binary
void decimal_to_binary(int n)
{
    int binaryNum[32];
    int i = 0;

    // While loop to convert the decimal number to binary
    while (n > 0)
    {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    printf("Binary: ");

    // Loop through the array in reverse order, printing each binary digit
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binaryNum[j]);
    }

}

// Function to display welcome and loading animation
void message_animation()
{
    srand(time(0));
    int num_loops = rand() % 3 + 1;

    // Print the welcome message
    printf("\n \t\t Welcome to the number converter");
    printf("\n \t\t     **** **** **** **** ****\n");
    printf("\t     (CS50's Final-Project - Jean-Luc Turquin)\n\n");

    // For-loop loops for the number of times determined by num_loops
    for (int i = 0; i < num_loops; i++)
    {
        printf("Loading");

        for (int j = 0; j < 3; j++)
        {
            // Print "." and flush the output buffer
            printf(".");
            fflush(stdout);
            sleep(1);
        }

        // Print a new line character to start the next loop on a new line
        printf("\n");
    }
}
// END of program