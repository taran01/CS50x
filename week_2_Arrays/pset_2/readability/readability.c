#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    // Get user input
    string text = get_string("Text: ");

    float letters = count_letters(text);
    printf("letters: %.0f\n", letters);

    float words = count_words(text);
    printf("words: %.0f\n", words);

    float sentences = count_sentences(text);
    printf("sentences: %.0f\n", sentences);

    // Calculate L & S
    float L = letters / words * 100;
    float S = sentences / words * 100;

    // Computing Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}

// Function to count letters
int count_letters(string text)
{
    int ltrs = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            ltrs++;
        }
    }
    return ltrs;
}

// Function to count words
int count_words(string text)
{
    int wrds = 1;

    if (strlen(text) < 1)
    {
        wrds = 0;
    }

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            wrds++;
        }
    }
    return wrds;
}

// Function to count sentences
int count_sentences(string text)
{
    int stencs = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            stencs++;
        }
    }
    return stencs;
}