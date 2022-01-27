#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // If one valid substitution key argument is not provided, quit program
    if (argc != 2)
    {
        printf("Please input a substitution key\n");
        return 1;
    }
    
    // If the substitution key does not have 26 letters, quit program
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    
    // Even though we know argv[1] length is 26, to avoid hardcoding:
    int keylength = strlen(argv[1]);
    
    // Make sure all of the characters are letters, else quit program
    for (int i = 0; i < keylength; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain only letters\n");
            return 1;
        }
        
        // for simplicity, convert the key to all lowercase
        argv[1][i] = tolower(argv[1][i]);
    }
    
    // Check for duplicate characters
    for (int i = 0; i < keylength; i++)
    {
        for (int j = 0; j < keylength; j++)
        {
            if (argv[1][i] == argv[1][j] && j != i)
            {
                printf("Key must use each letter only once\n");
                return 1;
            }
        }
    }

    // Get plaintext input from user
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // iterate through plaintext and print a new character using the key
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(argv[1][plaintext[i] - 65]));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", argv[1][plaintext[i] - 97]);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    
    printf("\n");
    return 0;
}