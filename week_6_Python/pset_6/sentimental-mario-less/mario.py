# TODO
# While loop to get height but in case of ValueError continue the loop
while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        continue
    if 1 <= height <= 8:
        break

for i in range(height):
    for j in range(height - (i + 1)):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print()