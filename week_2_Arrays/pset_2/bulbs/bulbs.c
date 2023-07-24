#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get user input
    string text = get_string("Message: ");

    // Loop for each row
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        // Convert char to ascii number
        int n = text[i];

        // Make array of 8 bits
        int r[8];

        // Store remainder of each division to convert to binary
        for (int j = 0; j < 8; j++)
        {
            r[j] = n % 2;
            n = n / 2;
        }

        // Print bulbs in reverse order
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(r[j]);
        }
        printf("\n");

    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}