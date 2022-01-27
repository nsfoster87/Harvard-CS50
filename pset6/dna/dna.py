from sys import argv

# Check for correct number of command-line arguments
if len(argv) != 3:
    print("Incorrect Usage")
    exit()

# Open files
try:
    csvhandle = open(argv[1])
    txthandle = open(argv[2])
except:
    print("Cannot open files")
    exit()

# Create a two dimensional array from the csv file
people = []
for line in csvhandle:
    people.append(line.strip().split(','))
sequences = people.pop(0)
del sequences[0]

# Count the longest STR run for each given sequence
dna = txthandle.read()
s_t_rs = []
for sequence in sequences:
    maxcounter = 0
    foundindex = dna.find(sequence)
    while foundindex < len(dna):
        counter = 0
        while dna[foundindex:foundindex+len(sequence)] == sequence:
            counter += 1
            foundindex += len(sequence)
        if counter > maxcounter:
            maxcounter = counter
        if dna[foundindex:].find(sequence) == -1:
            break
        foundindex += dna[foundindex:].find(sequence)
    s_t_rs.append(maxcounter)

# Compare the STRs to each person, and remove the person if no match
index = 0
while index < len(s_t_rs):
    person = 0
    while person < len(people):
        if s_t_rs[index] != int(people[person][index + 1]):
            del people[person]
            continue
        person += 1
    index += 1

# Print results
if len(people) == 0:
    print("No match")
else:
    print(people[0][0])