# Requirements Summary

1. The program should accept two command-line arguments: the **name of a CSV file** containing the STR counts for a **_list_** of individuals, and the **name of a text file** containing the DNA sequence to identify.
2. If the program is executed with the incorrect number of command-line arguments, it should _print_ an error message.
3. The program should _open_ the CSV file and _read_ its contents into memory, including the **column names** and the **individual STR counts**.
4. The program should _open_ the DNA sequence file and _read_ its contents into memory.
5. The program should compute the longest run of consecutive repeats of each STR in the DNA sequence using the `longest_match` function.
6. _If_ the STR counts for an individual match exactly with the DNA sequence, the program should _print_ the name of the matching individual.
7. _If_ the STR counts do not match exactly with any of the individuals in the CSV file, the program should _print_ "No match".