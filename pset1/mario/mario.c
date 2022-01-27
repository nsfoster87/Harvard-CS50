#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare height var to hold user input
    int height;
    
    // get user input and store it in height var
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // print the pyramid
    // iterate through each row
    for (int i = 1; i < height + 1; i++)
    {
        // for each row, iterate through each space in the current row
        for (int j = height; j > 0; j--)
        {
            // print " " counting down from j
            // when j equals row number (i) switch from " " to "#"
            if (j > i)
            { 
                printf(" ");
            }
            else 
            {
                printf("#");
            }
        }
        printf("\n");
    }
}