#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Prompt user for input
    string input = get_string("Type message: ");

    // Iterate through each character in the inpput string
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        // Get the ASCII value of the current character
        int ascii = input[i];


        // Iterate through each bit in the ASCII value
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            // Get the j-th bit of the ASCII value
            int bit = (ascii >> j) & 1;

            // Print the corresponding bulb emoji for the bit
            print_bulb(bit);
        }

        // Print a new line between characters
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
