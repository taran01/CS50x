#include <cs50.h>
#include <stdio.h>

int get_length(long n);

int main(void)
{
    // asking for card number
    long number = get_long("Number: ");

    // count length
    int length = get_length(number);

    // check if length is valid
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 1;
    }

    // performing checksum
    long x = number;
    int sum1 = 0;
    int sum2 = 0;
    int mod1;
    int mod2;
    int d1;
    int d2;

    do
    {
        // remove last digit and add to sum1
        mod1 = x % 10;
        x = x / 10;
        sum1 = sum1 + mod1;

        // remove second last digit
        mod2 = x % 10;
        x = x / 10;

        // double second last digit and add individual digits to sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    }
    while (x > 0);

    int total = sum1 + sum2;

    // check Luhn Algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // get starting 2 digits
    long start = number;
    do
    {
        start = start / 10;
    }
    while (start >= 100);


    // check digits for card name
    if ((start / 10 == 5) && (start % 10 > 0 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// returns the length of numbers
int get_length(long n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        count++;
    }
    return count;
}