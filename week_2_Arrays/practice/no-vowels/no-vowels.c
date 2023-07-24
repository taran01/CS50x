// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string s);

int main(int argc, string argv[])
{
    // Check for only 2 arguments
    if (argc != 2)
    {
        printf("Invalid argument-count.\n");
        return 1;
    }

    // Replace the string with Replace function
    string s = argv[1];
    string replaced = replace(s);
    printf("%s\n", replaced);
}

// Replaces vowels with given values
string replace(string s)
{
    string x = s;

    // Get length of string
    int length = 0;
    for (int i = 0; x[i] != '\0'; i++)
    {
        length++;
    }

    // Check each letter for cases with switch
    for (int i = 0; i < length; i++)
    {
        switch (x[i])
        {
            case 'a':
                x[i] = '6';
                break;

            case 'e':
                x[i] = '3';
                break;

            case 'i':
                x[i] = '1';
                break;

            case 'o':
                x[i] = '0';
                break;

            default:
                break;
        }
    }

    // Return replaced string
    return x;
}