#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // declare dollars variable to hold user input
    float dollars;
    
    // get user input
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    
    // convert dollars to cents and store as integer
    int cents = round(dollars * 100);
    
    // create a variable to store total number of coins
    int coins = 0;
    
    coins += cents / 25;
    printf("%i quarters\n", cents / 25);
    cents %= 25;
    coins += cents / 10;
    printf("%i dimes\n", cents / 10);
    cents %= 10;
    coins += cents / 5;
    printf("%i nickels\n", cents / 5);
    cents %= 5;
    printf("%i pennies\n", cents);
    coins += cents;
    
    // print the total minimun number of coins
    printf("Minimum number of coins: %i\n", coins);
}