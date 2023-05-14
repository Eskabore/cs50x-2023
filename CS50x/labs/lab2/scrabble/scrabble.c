// Author: Eskabore
// Purpose: determines the winner of a short scrabble-like game
// Language: CPP
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Lower case characters from 'a' to 'z' in ASCII decimal format
const char letterlower[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

// Upper case characters from 'A' to 'Z' in ASCII decimal format
const char letterupper[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

// Function prototype for compute_score()
int compute_score(string word);



int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else
    {
        printf("Tie!\n");
        return 0;
    }
}

// Function definition for compute_score()
int compute_score(string word)
{
    // Compute and return score for string
    int score = 0;

    // Loop through each character in the string
    for (int n = 0; n < strlen(word) ; n++)
    {
        // Check if character is upper case
        if (isupper(word[n]))
        {
            // Add points  to score based on charcter's position in the alphabet
            score = score + POINTS[(word[n] - 65)];
        }
        else if (islower(word[n]))
        {
            score = score + POINTS[(word[n] - 97)];
        }
        else
        {
            // Ignore non-alphabetic characters
            n += 1;
        }
    }

    // Returm final score
    return score;
}

