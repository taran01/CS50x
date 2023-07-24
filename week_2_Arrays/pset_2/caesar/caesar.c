#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(char a, int k);

int main(int argc, string argv[])
{
    // Check for only 1 cmd line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check every character in argv[1] is digit
    string s = argv[1];
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert string argv[1] to int (KEY)
    int key = atoi(s);

    // Get plaintext from user
    string plaintext = get_string("Plaintext:  ");

    // Convert each character in Plaintext to Ciphertext
    printf("Ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = rotate(plaintext[i], key);
        printf("%c", c);
    }
    printf("\n");
}

// Function to convert text
char rotate(char a, int k)
{
    int pi = (int)a;
    int ci = a;

    if (!isalpha(a))
    {
        return pi;
    }
    else if (isupper(a))
    {
        pi = pi - 'A';
        ci = (pi + k) % 26;
        ci = ci + 'A';
    }
    else if (islower(a))
    {
        pi = pi - 'a';
        ci = (pi + k) % 26;
        ci = ci + 'a';
    }

    return ci;
}