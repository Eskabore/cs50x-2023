/**
* Program: Speller
* Purpose: Implements a dictionary's functionality
* Author: Jean-Luc KABORE-TURQUIN
* Source: Hash function referenced from OpenAI GPT Assistant
(https://openai.com/)
*/

#include <ctype.h>
#include <stdbool.h>

// Add `stdio.h` for EOF (End-of-Line) sentinel value, fscanf
#include <stdio.h>
// Add `stdlib.h` for memory allocation/free functions
#include <stdlib.h>
// Add `string.h` for strlen, strcpy
#include <string.h>

// Add `strings.h` for strcasecmp
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Set number of buckets to number of letters in longest word
const unsigned int N = 45;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lowercase[LENGTH + 1];
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lowercase[i] = tolower(word[i]);
    }
    lowercase[strlen(word)] = '\0';

    // Calculate hash value for word
    int index = hash(lowercase);

    // Search for word in hash table
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare word to node's word using case-insensitive comparison
        if (strcasecmp(lowercase, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //  Initialize hash value
    unsigned int hash = 0;

    // Sum ASCII values of each character in word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash += word[i];
    }

    // Return hash value modulo number of buckets
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy word into node
        strcpy(new_node->word, word);

        // Calculate hash value for word
        int index = hash(word);

        // Insert new node into hash table at calculated index
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close ddictionnary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Initialize count of words
    unsigned int count = 0;

    // Count number of words in each bucket
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free memory for each bucket
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            if (cursor != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
    }

    return true;
}
