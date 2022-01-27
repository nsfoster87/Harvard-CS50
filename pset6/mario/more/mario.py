from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

for row in range(height):
    for column in range(height):
        if column < height - row - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print("  ", end="")
    print("#" * (row + 1))