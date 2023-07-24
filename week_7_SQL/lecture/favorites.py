import csv


with open("Hogwarts.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        favorite = row["House"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

def get_value(house):
    return counts[house]

for favorite in sorted(counts, key=lambda house: counts[house], reverse=True):
    print(f"{favorite}: {counts[favorite]}")