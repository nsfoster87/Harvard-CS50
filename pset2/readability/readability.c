#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    // get input from the user
    string text = get_string("Text: ");

    // Use the Coleman-Liau formula and round to the nearest integer
    float letterAvg = (float) count_letters(text) / (float) count_words(text) * 100;
    float sentenceAvg = (float) count_sentences(text) / (float) count_words(text) * 100;
    float index = 0.0588 * letterAvg - 0.296 * sentenceAvg - 15.8;
    int grade = round(index);

    // print "Before Grade 1", "Grade X", or "Grade 16+"
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string s)
{
    int letters = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        // if the ASCII number at s[i] maps to a letter, increment letters
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string s)
{
    int words = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        // If the current character is a ' ' or end-of-sentence punctuation,
        // and the previous character is NOT end-of-sentence punctuation
        // (so as not to double count)...increment words
        if (s[i] == ' ' || s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            if (s[i - 1] != '.' && s[i - 1] != '!' && s[i - 1] != '?')
            {
                words++;
            }
        }
    }
    return words;
}

int count_sentences(string s)
{
    int sentences = 0;

    // if s[i] contains end-of-sentence punctuation, count it as a sentence
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}