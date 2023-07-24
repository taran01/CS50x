#include <cs50.h>
#include <stdio.h>

bool prime(int number, int max);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i, max))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number, int max)
{
    // TODO
    for (int i = 2; i <= max; i++)
    {
        if (i == number)
        {
            return true;
        }
        else if (number % i == 0)
        {
            return false;
        }
    }
    return false;
}
