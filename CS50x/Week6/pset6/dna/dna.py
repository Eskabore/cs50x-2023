# Author: Eskabore
# Purpose: Program identifies a person based on their DNA
# Language: Python


import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Error: Incorrect number of arguments. Usage: python dna.py data.csv sequence.txt")
        sys.exit()

    # Read database file into a variable
    database_filename = sys.argv[1]

    try:
        with open(database_filename, 'r') as database_file:
            reader = csv.reader(database_file)
            # Read the first row (column names)
            column_names = next(reader)
            # Read the rest of the rows (individuals)
            individuals = list(reader)
    except FileNotFoundError:
        print(f"Error: CSV file {database_filename} not found")
        sys.exit()

    # Read DNA sequence file into a variable
    dna_sequence_filename = sys.argv[2]

    try:
        with open(dna_sequence_filename, 'r') as dna_sequence_file:
            dna_sequence = dna_sequence_file.read()
    except FileNotFoundError:
        print(f"Error: DNA sequence file {dna_sequence_filename} not found")
        sys.exit()

    # Find longest match of each STR in DNA sequence
    str_matches = []
    for str in column_names[1:]:
        str_matches.append(longest_match(dna_sequence, str))

    # Check database for matching profiles
    for name, *strs in individuals:
        if str_matches == list(map(int, strs)):
            # The STR counts match, print the name of the matching individual
            print(name)
            sys.exit()

    # If we reach this point, it means that no individual had a matching STR count
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()