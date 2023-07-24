// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    string s = password;
    int length = strlen(s);

    int lower = 0;
    int upper = 0;
    int digit = 0;
    int symbol = 0;

    for (int i = 0; i < length; i++)
    {
        if (islower(s[i]))
        {
            lower++;
        }
        else if (isupper(s[i]))
        {
            upper++;
        }
        else if (isdigit(s[i]))
        {
            digit++;
        }
        else if (s[i] == '!' || s[i] == '$' || s[i] == '#')
        {
            symbol++;
        }
    }

    if (lower > 0 && upper > 0 && digit > 0 && symbol > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
