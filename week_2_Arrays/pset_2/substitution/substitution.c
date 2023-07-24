#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char change_text(char a, string k);

int main(int argc, string argv[])
{
    // For single cmd line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // Convert argument to key variable
    string key = argv[1];

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        key[i] = tolower(key[i]);
    }

    //  Check key for total length of 26 letters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check key for only alphabetic chars
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check key for repeated characters
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    // Done with key

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    // Convert plaintext to ciphertext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = change_text(plaintext[i], key);
        printf("%c", c);
    }
    printf("\n");
    return 0;
}

char change_text(char a, string k)
{
    int ptxt = a;
    if (!isalpha(a))
    {
        return ptxt;
    }
    else if (isupper(a))
    {
        ptxt = ptxt - 'A';
        ptxt = toupper(k[ptxt]);
    }
    else if (islower(a))
    {
        ptxt = ptxt - 'a';
        ptxt = tolower(k[ptxt]);
    }

    return ptxt;
}