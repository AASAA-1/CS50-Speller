// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int words = 0;
// TODO: Choose number of buckets in hash table
// 26 for each letter of the alphabet ,and an extra array to process non-numbers into
const unsigned int N = 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false ,idk what I'm doing tbh
bool check(const char *word)
{
    node *head = table[hash(word)];
    for (int i = 0; i < words; i++)
    {
        if (strcasecmp(word, head->word) == 0)
        {
            return true;
        }
        if (head->next != NULL)
        {
            head = head->next;
        }
        else if (head->next == NULL)
        {
            break;
        }
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned int number = (toupper(word[0]) % N);
    if ((isalpha(word[0])) == 0)
    {
        //10 is the number unused by any of the alphabet letters ,and thus is where I put all non-letters.
        //A gives 11 ,counting up until Q which gives 26,then going back to 0 and counting up to 9 when Z is reached.
        return 10;
    }
    return number;
}
// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    FILE *a = fopen(dictionary, "r");
    if (a == NULL)
    {
        return false;
    }
    char b[LENGTH + 1];
    while ((fscanf(a, "%s", b)) != EOF)
    {
        node *u = malloc(sizeof(node));
        strcpy(u->word, b);
        u->next = table[hash(b)];
        table[hash(b)] = u;
        words++;
    }
    fclose(a);
    return true;
}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (words > 0)
    {
        return words;
    }
    return 0;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node* head = table[i];
        node* tmp = table[i];
        //somehow ,"while(head)" works ,but "while(head->next != NULL)" gives a core dump error ???
        //(either when followed up by
        while(head)
        {
            tmp = head ;
            head = head->next;
            free(tmp);
        }
    }
    return true;
}


