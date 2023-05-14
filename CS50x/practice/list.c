#include <stdlib.h>
#include <stdio.h>

int main (void)
{
    // Dynamically allocate an array of size 3
    int *list = malloc(3 * sizeof(int));
    // Don't do int list = [3];

    if (list == NULL)
    {
        printf("%i\n", list[1]);
        return 1;
    }

    // Assign 3 numbers to that array
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    // *list  =  1; *(list + 1) = 2...


    // Time passes and I want to add some space to the array :-/

    // Resize old array to be of size 4
    int *tmp = realloc(list, 4 * sizeof(int));

    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    // Add fourth number to the array
    tmp[3] = 4;


    // Attribute new location to list. Remember new array
    list = tmp;

    // Print new array
    for (int i = 0; i < 4; i++)
    {
    printf("%i\n", list[i]);
    }

    // Free new array
    free(list);
    return 0;
}