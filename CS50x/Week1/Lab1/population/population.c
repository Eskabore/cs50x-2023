/*
* Author: Eskabore
* Purpose: Print number of years for llama population to reach end end size
* Language: C
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Prompt for start size and validate input
    int start_size;

    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size and validate input
    int end_size;

    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach threshold
    int num_years = 0;

    // Update the counter of years at each iteration
    for (int i = start_size; i < end_size; i += (i / 3) - (i / 4))
    {
        num_years++;
    }

    // Print number of years
    printf("Years: %i\n", num_years);
}
