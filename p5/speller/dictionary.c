// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 7482;
int suc_wor = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h_value = hash(word);
    node *wo = table[h_value];

    while (wo != NULL)
    {
        if (strcasecmp(word, wo->word) == 0)
        {
            return true;
        }
        wo = wo->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long tot = 0;
    for (int pp = 0, n = strlen(word); pp < n; pp++)
    {
        tot = tot + tolower(word[pp]);
    }

    tot = tot % N;
    return tot;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictutinn = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
    }

    char nxword[LENGTH + 1];

    while (fscanf(dictutinn, "%s", nxword) != EOF)
    {
        node *lwo = malloc(sizeof(node));
        if (lwo == NULL)
        {
            return false;
        }
        strcpy(lwo->word, nxword);
        int h_value = hash(nxword);
        lwo->next = table[h_value];
        table[h_value] = lwo;
        ++suc_wor;
    }
    fclose(dictutinn);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return suc_wor;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int f = 0; f < N; f++)
    {
        node *fin = table[f];
        while (fin != NULL)
        {
            node *team = fin;
            fin = fin->next;
            free(team);
        }
        if (f == N - 1 && fin == NULL)
        {
            return true;
        }
    }
    return false;
}
