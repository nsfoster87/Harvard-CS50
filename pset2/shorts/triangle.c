#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    float a = get_float("Side 1: ");
    float b = get_float("Side 2: ");
    float c = get_float("Side 3: ");
    if (valid_triangle(a, b, c))
    {
        printf("Valid triangle\n");
    }
    else
    {
        printf("Not a valid triangle\n");
    }
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    else if (a + b <= c || a + c <= b || b + c <= a)
    {
        return false;
    }
    else
    {
        return true;
    }
}