# Author: Eskabore
# Purpose: Computing aproximate grade level needed to comprehend some text
# Language: Python

import math
from cs50 import get_string


# Function to count number of letters in the text
def count_letters(text):
    count = 0
    for c in text:
        # Increment count if character is a letter
        # and not a space
        if c.isalpha() and c != ' ':
            count += 1
    return count


# Function to count number of letters in the text
def count_words(text):
    count = 1
    for c in text:
        # Increment count if character is a space
        if c == ' ':
            count += 1
    return count


# Function to count sentences in the text
def count_sentences(text):
    count = 0
    for c in text:
        # Increment count if character is a
        # sentence ending punctuation
        if c == '.' or c == '?' or c == '!':
            count += 1
    return count


# Function to calculate the Coleman-Liau Index
def coleman_liau_index(cl, cw, cs):
    # Calculate the average number of letters per 100 words
    l = (cl / cw) * 100
    # Calculate the average number of sentences per 100 words
    s = (cs / cw) * 100

    # Claculate the Coleman-Liau Index
    index = round((0.0588 * l) - (0.296 * s) - 15.8)
    return index


# Get text input from user
text = get_string("Text: ")

# Count number of letters, words, and sentences in text
cl = count_letters(text)
cw = count_words(text)
cs = count_sentences(text)

# Calculate the Coleman-Liau Index for the text
cli = coleman_liau_index(cl, cw, cs)

# Print the appropriate result based on the calculated grade level
if cli <= 1:
    print("Before Grade 1")
elif cli >= 16:
    print("Grade 16+")
else:
    print("Grade", cli)