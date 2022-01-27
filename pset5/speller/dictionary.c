// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10003199;

// Hash table
node *table[N];

// dictionary size
unsigned int dictionary_size = 0;

void destroy(node *head);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashindex = hash(word);
    node *traverse = table[hashindex];
    while (traverse != NULL)
    {
        if (strcasecmp(word, traverse->word) == 0)
        {
            return true;
        }
        else
        {
            traverse = traverse->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash Function adapted from:
    // https://cp-algorithms.com/string/string-hashing.html
    // 8/26/2020
    const int p = 31;
    const int m = N;
    long long hash_value = 0;
    long long p_pow = 1;
    for (int i = 0, wordlength = strlen(word); i < wordlength; i++)
    {
        if (word[i] == '\'')
        {
            hash_value = (hash_value + ('z' - 'a' + 1) * p_pow) % m;
        }
        else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            hash_value = (hash_value + (word[i] - 'A' + 1) * p_pow) % m;
        }
        else
        {
            hash_value = (hash_value + (word[i] - 'a' + 1) * p_pow) % m;
        }
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictionaryfile = fopen(dictionary, "r");
    if (dictionaryfile == NULL)
    {
        return false;
    }

    // Scan for words in file
    char word[LENGTH + 1];
    while (fscanf(dictionaryfile, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word into node->word
        strcpy(n->word, word);

        // Store the hash of the word and use it as the index for the linked list
        unsigned int hashindex = hash(word);

        // Point node->next at the first item in the linked list
        n->next = table[hashindex];

        // Point the head of the list at the new node
        table[hashindex] = n;

        // Increment dictionary size
        dictionary_size++;
    }
    fclose(dictionaryfile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(table[i]);
        }
    }
    return true;
}

// Recursively destroys a linked list
void destroy(node *head)
{
    if (head != NULL)
    {
        destroy(head->next);
    }
    free(head);
}