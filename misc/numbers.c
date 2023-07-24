#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int numbers[] = {6, 7, 1, 8, 4, 3, 2, 5};

    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 7; i++)
        {
            if (numbers[i] > numbers[i + 1])
            {
                int tmp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%i\n", numbers[i]);
    }
}