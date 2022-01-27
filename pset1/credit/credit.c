#include <stdio.h>
#include <cs50.h>
#include <math.h>

// declare the function for checking card's validity
bool isCardValid(long cardNum, int length);

int main(void)
{
    // get the card number from user input
    long cardNumber = get_long("Card Number: ");

    // if cardNumber has 15 digits and starts with 34 or 37...(AMEX)
    if (cardNumber / 10000000000000 == 34 || cardNumber / 10000000000000 == 37)
    {
        if (isCardValid(cardNumber, 15))
        {
            printf("Card Type: AMEX\n");
        }
        else
        {
            printf("Card Type: INVALID\n");
        }
    }
    // if cardNumber is 13 digits and starts with 4...(VISA)
    else if (cardNumber / 1000000000000 == 4)
    {
        if (isCardValid(cardNumber, 13))
        {
            printf("Card Type: VISA\n");
        }
        else
        {
            printf("Card Type: INVALID\n");
        }
    }
    // if cardNumber is 16 digits and starts with 4...(VISA)
    else if (cardNumber / 1000000000000000 == 4)
    {
        if (isCardValid(cardNumber, 16))
        {
            printf("Card Type: VISA\n");
        }
        else
        {
            printf("Card Type: INVALID\n");
        }
    }
    // if cardNumber is 16 digits and starts with 51-55...(MASTERCARD)
    else if (cardNumber / 100000000000000 > 50 && cardNumber / 100000000000000 < 56)
    {
        if (isCardValid(cardNumber, 16))
        {
            printf("Card Type: MASTERCARD\n");
        }
        else
        {
            printf("Card Type: INVALID\n");
        }
    }
    else
    {
        printf("Card Type: INVALID\n");
    }
}

bool isCardValid(long cardNum, int length)
{
    int sum = 0;
        
    for (int i = 0; i < length; i += 2)
    {
        long first = pow(10, i);
        long second = pow(10, i + 1);
        long third = pow(10, i + 2);
        int oddDigit = cardNum % second / first;
        int evenDigit = cardNum % third / second * 2;
        
        // DEBUGGING
        printf("(%i) %i ", oddDigit, evenDigit);
        
        // add all the digits to 'sum'
        if (evenDigit > 9)
        {
            sum += evenDigit / 10 + evenDigit % 10;
        }
        else
        {
            sum += evenDigit;
        }
        sum += oddDigit;
    }
    
    // DEBUGGING
    printf("\nSum: %i\n", sum);
    
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}