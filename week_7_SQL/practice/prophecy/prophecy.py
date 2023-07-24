import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # Add student name and id into students table in database
        db.execute("INSERT INTO students (id, name) VALUES (?, ?)", row["id"], row["student_name"])

        # Add house name and head into houses table in database
        db.execute("INSERT OR IGNORE INTO houses (house, head) VALUES (?, ?)", row["house"], row["head"])

        # Populate the assignments table
        db.execute("INSERT INTO assignments (student_id, house_name, head_name) VALUES (?, ?, ?)", row["id"], row["house"], row["head"])

    