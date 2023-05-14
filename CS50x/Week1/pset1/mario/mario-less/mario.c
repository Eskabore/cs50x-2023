/*
* Author: Eskabore
* Purpose: building a right-aligned pyramid
* Language C
*/
#include <cs50.h>
#include <stdio.h>

/* Prompt user for input & built Pyramid */
int main(void)
{
    int height;

    /* Prompt user input until value is > 0 & < 9 */
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    /* Draw a right-aligned pyramid based on input value */
    for (int i = 1; i <= height; i++)
    {
        /* Inner loop that displays the 'columns' or 'spaces' */
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}