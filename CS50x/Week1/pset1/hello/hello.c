/*
* Author: Eskabore
* Language C
* Purpose: 1.Request user name
* 2. Return greeting with name
*/
#include <stdio.h>
#include <cs50.h>

/* Request user name & return greeting with value name */
int main(void)
{
    /* Request user to type in name */
    string name = get_string("What's your name?\n");
    /* Greet user with value 'name' */
    printf("hello, %s\n", name);
}