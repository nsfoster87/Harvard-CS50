from cs50 import get_string
import re

text = get_string("Text: ")

sentences = re.split('[.!?] ', text)
sentencecount = len(sentences)

words = []
for sentence in sentences:
    words += sentence.split()
wordcount = len(words)

lettercount = 0;
for word in words:
    for letter in word:
        if letter >= 'a' and letter <= 'z':
            lettercount += 1
        elif letter >= 'A' and letter <= 'Z':
            lettercount += 1

# Coleman-Liau index: 0.0588 * L - 0.296 * S - 15.8 where
# L is the average number of letters per 100 words and
# S is the average number of sentences per 100 words
let = 100 * lettercount / wordcount
sen = 100 * sentencecount / wordcount
cole_liau = 0.0588 * let - 0.296 * sen - 15.8

grade = "Grade "
if cole_liau >= 16:
    grade += "16+"
elif cole_liau < 1:
    grade = "Before Grade 1"
else:
    grade += str(round(cole_liau))

print(grade)