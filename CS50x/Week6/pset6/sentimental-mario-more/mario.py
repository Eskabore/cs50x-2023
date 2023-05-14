# Author: Eskabore
# Purpose: Printing a pyramid with a gap in between
# Language: Python

from cs50 import get_int


def main():

    # Prompt user for height of the Pyramid
    height = get_int("Enter a number between 1 to 8: ")
    while height < 1 or height > 8:
        height = get_int("Type an integer between 1 to 8: ")

    # Outer loop used to point to current row
    for i in range(1, height+1):
        # Inner loop printing left-aligned spaces
        for j in range(height, i, -1):
            print(" ", end="")
        # Inner loop printing left-aligned pyramid
        for k in range(1, i+1):
            print("#", end="")
        # Print gap
        print("  ", end="")
        # Inner loop printing right-aligned pyramid
        for i in range(1, i+1):
            print("#", end="")
        # Insert a new line
        print()


if __name__ == "__main__":
    main()
