/*
 * substitution.c
 *
 * Encrypts messages using a substitution cipher.
 *
 * Author: eskabore
 */

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Checks for valid number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Get key from command-line argument
    string key = argv[1];

    // Check if key is valid
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Checks if all characters in key are alphabetic and uniique
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Check if current character has been repeated in key
        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contaain repeated characters.\n");
                return 1;
            }
        }
    }

    // Prompt user for text
    string plaintext = get_string("plaintext: ");

    // Print ciphered text
    printf("ciphertext: ");
    // Function makes sure that command line argument entered  by user is a list of 26 letters
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Get index of current character in alphabet
            char c = tolower(plaintext[i]);
            int index = c - 'a';

            // Get corresponding character from key and preserve case
            if (isupper(plaintext[i]))
            {
                printf("%c", toupper(key[index]));
            }
            else
            {
                printf("%c", tolower(key[index]));
            }
        }
        else
        {
            // Output non-alphabetic characters unchanged
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return 0;
}