#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);

    // Print required coins
    printf("Quarters: %i\n", quarters);
    printf("Dimes: %i\n", dimes);
    printf("Nickels: %i\n", nickels);
    printf("Pennies: %i\n", pennies);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    int quarters = 0;
    if (cents < 25)
    {
        return quarters;
    }

    for (int i = 0,  n = cents; n >= 25; i++)
    {
        quarters++;
        n -= 25;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;
    if (cents < 10)
    {
        return dimes;
    }

    for (int i = 0,  n = cents; n >= 10; i++)
    {
        dimes++;
        n -= 10;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;
    if (cents < 5)
    {
        return nickels;
    }

    for (int i = 0,  n = cents; n >= 5; i++)
    {
        nickels++;
        n -= 5;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;
    if (cents < 1)
    {
        return pennies;
    }

    for (int i = 0,  n = cents; n >= 1; i++)
    {
        pennies++;
        n -= 1;
    }
    return pennies;
}
