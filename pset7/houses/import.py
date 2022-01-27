from sys import argv
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) != 2:
    print("Incorrect Usage: Please include csv file")
    exit()

with open(argv[1]) as file:
    reader = csv.DictReader(file)

    for row in reader:
        name = row["name"]
        fullname = name.split()
        firstname = fullname[0]
        if len(fullname) > 2:
            middlename = fullname[1]
            lastname = fullname[2]
        else:
            middlename = None
            lastname = fullname[1]
        house = row["house"]
        birth = row["birth"]
        sql = "INSERT INTO students "
        sql += "(first, middle, last, house, birth) "
        sql += "VALUES (%s, %s, %s, %s, %s);"
        val = (firstname, middlename, lastname, house, birth)
        db.execute(sql, val)