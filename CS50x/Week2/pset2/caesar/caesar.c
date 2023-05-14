// Author: Eskabore
// Purpose: Use Caesar's cypher  method to encrypt messages
// Language C
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Command-line argument inputted by user is stored into a 'string' variable
    string s = argv[1];

    // Ensure programm is run with a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }



    // Make sure every character in argv[1] is a digit
    if (only_digits(s) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

// Using integer entered by user

    // Convert 'argv[1]' or 's' variable  from a string to an int
    int key = atoi(s);

    // Returns an error message if user typed in a negative integer
    if (key < 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int n = key;

        // Prompt user for text
        printf("plaintext: ");
        string plaintext = get_string(" ");

        // Print ciphertext
        printf("ciphertext: ");

        // Loops through user's text and cipher every valid character
        for (int i = 0, j = strlen(plaintext); i < j; i++)
        {
            if (isalpha(plaintext[i]))
            {
                char ciphertext = plaintext[i];
                printf("%c", rotate(ciphertext, n));
            }
            else
            {
                char ciphertext = plaintext[i];
                printf("%c", ciphertext);
            }
        }
        printf("\n");
    }
    // Function main() returns 0
    return 0;
}


// Checks whether key entered by user is a digit, otherwise returns false
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Function encrypts messages by 'rotating' each letter 'c' by 'n' positions
char rotate(char c, int n)
{
    if (isupper(c))
    {
        return ((c - 'A' + n) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + n) % 26) + 'a';
    }
    else
    {
        return c;
    }
}