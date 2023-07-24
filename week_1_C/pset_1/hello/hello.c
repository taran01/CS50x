#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //ask user for name input
    string name = get_string("What's your name? ");

    //print user-input
    printf("hello, %s\n", name);
}