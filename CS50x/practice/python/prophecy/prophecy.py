import csv

from cs50 import SQL

# Connect to database
db = SQL("sqlite:///roster.db")

# Open the CSV file and read the data
with open('students.csv', 'r') as f:
    rows = csv.reader(f)
    # skip the header row
    next(rows)
    # insert the data into the students table
    for row in rows:
        db.execute("INSERT INTO students (id, student_name, house, head) VALUES (?, ?, ?, ?)", row[0], row[1], row[2], row[3])

print(row)