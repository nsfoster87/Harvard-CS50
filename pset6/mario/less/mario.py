from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for row in range(height):
    for column in range(height):
        if column < height - row - 1:
            print(" ", end="")
        else:
            print("#", end="")
    print()
