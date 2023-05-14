# Author: Eskabore
# Purpose: buiding a left-aligned pyramid
# Language: Python

from cs50 import get_int


def main():
    # Prompt user for input & built Pyramid
    height = get_int("Enter number between 1 to 8: ")
    while height < 1 or height > 8:
        height = get_int("Type an integer between 1 to 8: ")

    # Draw a right-aligned pyramid based on input value
    for i in range(1, height+1):
        # Inner loop that displays the 'columns' or 'spaces'
        for j in range(height, i, -1):
            print(" ", end="")
        for k in range(1, i+1):
            print("#", end="")
        print()


if __name__ == "__main__":
    main()

