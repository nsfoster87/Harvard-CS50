from sys import argv
from cs50 import SQL

if len(argv) != 2:
    print("Incorrect Usage: Enter a house name")
    exit()

db = SQL("sqlite:///students.db")
house = argv[1]
sql = 'SELECT * FROM "students" '
sql += 'WHERE house = (%s) '
sql += 'ORDER BY last, first'
val = (house)
for row in db.execute(sql, val):
    first = row['first']
    middle = row['middle']
    last = row['last']
    year = row['birth']
    if middle != None:
        print(f"{first} {middle} {last}, born {year}")
    else:
        print(f"{first} {last}, born {year}")