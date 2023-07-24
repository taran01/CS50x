#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //ask for height
    int height;
    do
    {
        height = get_int("height: ");
    }
    while (height < 1 || height > 8);

    //first loop for printing rows
    for (int i = 0; i < height; i++)
    {
        //second loop for printing spaces
        for (int k = 1; k < height - i; k++)
        {
            printf(" ");
        }

        //third loop for prinitng hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}