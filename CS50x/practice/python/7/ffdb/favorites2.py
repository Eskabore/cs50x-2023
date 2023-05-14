# This version uses DictReader(keys of a list)-> print key

import csv

# Open CSV file
with open("favorites.csv", 'r') as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file, printing each favorite
    for row in reader:
        print(row["language"])