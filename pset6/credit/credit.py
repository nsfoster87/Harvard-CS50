from cs50 import get_int

cardnumber = get_int("Credit Card Number: ")
cardstring = str(cardnumber)
cardlength = len(cardstring)
cardtype = "INVALID"

# AMEX
if cardlength == 15:
    if cardstring[:2] == '34' or cardstring[:2] == '37':
        cardtype = "AMEX"
# VISA
elif cardstring[0] == '4':
    if cardlength == 13 or cardlength == 16:
        cardtype = "VISA"
# MASTERCARD
elif cardlength == 16:
    if int(cardstring[:2]) >= 51 and int(cardstring[:2]) <= 55:
        cardtype = "MASTERCARD"

# LUHN'S ALGORITHM:
# Multiply every other digit by 2 starting with second to last
# Add those products' digits together
# Add the sum of the remaining digits
# If the total % 10 == 0, card is valid
if cardtype != "INVALID":
    tally = 0
    index = cardlength - 2
    while index >= 0:
        digit = int(cardstring[index]) * 2
        if digit > 9:
            digit = digit // 10 + digit % 10
        tally += digit
        index -= 2
    index = cardlength - 1
    while index >= 0:
        tally += int(cardstring[index])
        index -= 2
    if tally % 10 != 0:
        cardtype = "INVALID"

print("Card Type:", cardtype)