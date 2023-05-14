// Author: Eskabore
// CS50 - Readability
// Purpose: Calculate the grade level needed to comprehend user's text input
// Language C

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau_index(int cl, int cw, int cs);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Call count_letters function with inputted text as argument. Function is stored into an 'int' variable
    int cl = count_letters(text);

    // Call count_words function with inputted text as argument. Function is stored into an 'int' variable
    int cw = count_words(text);

    // Call count_sentences function with inputted text as argument. Function  is stored into an 'int' variable
    int cs = count_sentences(text);

    // Call coleman_liau_index function and passes in 3 variables returning count of letters, words and sentences
    int cli = coleman_liau_index(cl, cw, cs);

    if (cli <= 1)
    {
        // Print following text if estimated grade matches early readers'
        printf("Before Grade 1\n");
    }
    else if (cli >= 16)
    {
        // Print following text if estimated grade matches experienced readers'
        printf("Grade 16+\n");
    }
    else
    {
        // Print text's grade level
        printf("Grade %i\n", cli);
    }
}

// Function  counts letters in text
int count_letters(string text)
{
    int n = strlen(text);
    char c[n];
    int i = 0;
    int count = 0;

    do
    {
        for (i = 0; i < n; i++)
        {
            c[i] = text[i];

            // Counter increments of 1 for every letter in text
            if (isalpha(c[i]) && !isspace(c[i]))
            {
                count++;
            }
        }
    }
    while (text[i] != '\0');

    return count;
}

// Function counts words in text
int count_words(string text)
{
    int count = 1;
    int temp = 0;
    int i = 0;
    int n = strlen(text);
    int c[n + 1];

    while (text[i] != '\0')
    {
        c[i] = text[i];

        // Counter increments after a ' '(space).
        if (isspace(c[i]))
        {
            count++;
        }
        i++;
    }
    return count;
}

// Function count sentences in text
int count_sentences(string text)
{
    int i = 0;
    int count = 0;
    int n = strlen(text);
    int c[n + 1];

    while (text[i] != '\0')
    {
        c[i] = text[i];
        // Counter increments when sentence ends
        if (c[i] == '.' || c[i] == '?' || c[i] == '!')
        {
            count++;
        }
        i++;
    }
    return count;
}

// Function takes the 3 counting variables as argument and calculate the 'Coleman-Liau Index'
int coleman_liau_index(int cl, int cw, int cs)
{
    double l = (float) cl / cw * 100;
    double s = (float) cs / cw * 100;

    int index = round((0.0588 * l) - (0.296 * s) - 15.8);


    return index;
}