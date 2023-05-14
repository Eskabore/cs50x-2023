# Counts favorites using dictionary

import csv

# Open CSV file
with open("favorites.csv", 'r') as file:
    reader = csv.DictReader(file)

    # Counts
    counts = {}

    # Iterate over csv file, counting favorites
    for row in reader:
        favorite = row["language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# Print counts
for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")