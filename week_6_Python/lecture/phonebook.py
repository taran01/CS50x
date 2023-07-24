people = {
    "taran": "623-985-3802",
    "mom": "788-920-8641"
}

name = input("Name: ")
if name in people:
    number = people[name]
    print(f"Number: {number}")