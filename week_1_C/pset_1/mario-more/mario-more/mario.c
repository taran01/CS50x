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

    //printing #s
    for (int i = 0; i < height; i++)
    {
        for (int k = 1; k < height - i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}