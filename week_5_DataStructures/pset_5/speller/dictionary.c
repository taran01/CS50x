// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int no_of_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h = hash(word);
    if (search(table[h], word))
    {
        return true;
    }
    return false;
    // for (node *p = table[h]; p != NULL; p = p->next)
    // {
    //     if (strcasecmp(p->word, word) == 0)
    //     {
    //         return true;
    //     }
    // }
    // return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    //Read strings from file
    char word[LENGTH + 1];
    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;
        int h = hash(word);
        n->next = table[h];
        table[h] = n;
        no_of_words++;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return no_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // node *cursor = table[i];
        // node *tmp = table[i];
        // while (cursor != NULL)
        // {
        //     cursor = table[i]->next;
        //     free(tmp);
        //     tmp = table[i]->next;
        // }
        free_table(table[i]);
    }
    return true;
}

// Search function
bool search(node *p, const char *s)
{
    node *cursor = p;
    if (cursor == NULL)
    {
        return false;
    }
    else if (strcasecmp(cursor->word, s) == 0)
    {
        return true;
    }
    else
    {
        return search(p->next, s);
    }
    return true;
}

void free_table(node *p)
{
    if (p == NULL)
    {
        return;
    }

    free_table(p->next);

    free(p);
}