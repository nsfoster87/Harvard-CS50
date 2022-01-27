from cs50 import get_float

while True:
    change = get_float("Change: ")
    if change >= 0:
        break

cents = int(change * 100)
coins = 0

while cents >= 25:
    coins += 1
    cents -= 25
while cents >= 10:
    coins += 1
    cents -= 10
while cents >= 5:
    coins += 1
    cents -= 5
while cents >= 1:
    coins += 1
    cents -= 1

print("Total Coins:", coins)