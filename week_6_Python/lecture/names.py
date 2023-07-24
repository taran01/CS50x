import sys

names = ["bill", "charlie", "fred", "george", "ginny", "percy", "ron"]

name = input("Name: ")

if name in names:
    print("found")
    sys.exit(0)

print("not found")
sys.exit(1)