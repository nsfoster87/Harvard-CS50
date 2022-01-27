#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

char wrap_around(char c, int keyint, int ascii);

int main(int argc, string argv[])
{
    // if user doesn't input a key, print error message and quit
    if (argc != 2)
    {
        printf("Be sure to enter a valid encryption key!\n");
        return 1;
    }

    // iterate through the characters of the key argument
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        // if any character is not a decimal digit, print error message and quit
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }

    // prompt the user for a plaintext string
    string plaintext = get_string("plaintext: ");

    // convert the key from a string to an int
    int key = atoi(argv[1]);

    printf("ciphertext: ");

    // iterate through plaintext and convert each character then print it
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        char newletter;
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            newletter = wrap_around(plaintext[i], key, 65);

        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            newletter = wrap_around(plaintext[i], key, 97);
        }
        else
        {
            newletter = plaintext[i];
        }
        printf("%c", newletter);
    }

    printf("\n");
    return 0;
}

char wrap_around(char c, int keyint, int ascii)
{
    // calculate how the difference between char and 'a' or 'A'
    // add the key
    // take the remainder of the sum and 26 and add that to 'a' or 'A'
    char adjustedkey = c - ascii;
    return (keyint + adjustedkey) % 26 + ascii;
}