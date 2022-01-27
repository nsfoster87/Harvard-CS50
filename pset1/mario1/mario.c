#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare height var for storing user input
    int height;
    
    // get a user input (1-8) and store it in height var
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // iterate through each row
    for (int i = 1; i < height + 1; i++)
    {
        // print first pyramid
        for (int j = height; j > 0; j--)
        {
            if (j > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        
        // print gap
        printf("  ");
        
        // print second pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        // new line
        printf("\n");
    }
}