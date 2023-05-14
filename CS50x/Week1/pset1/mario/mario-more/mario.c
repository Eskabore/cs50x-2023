// Author: Eskabore
// Purpose: Printing a pyramid with a gap in between
// Language C
#include <cs50.h>
#include <stdio.h>

int main(void)


{

    int height;

    // Prompt user for height of the pyramid
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Outer loop used to point to current row
    for (int i = 1; i <= height; i++)
    {
        // Inner loop printing left-aligned spaces
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }

        // Inner loop printing left-aligned pyramid
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        // Print gap
        printf("  ");

        // Inner loop printing right-aligned pyramid
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }

        // Insert a new line
        printf("\n");
    }
}