// Implements a dictionary's functionality

#include <cs50.h>
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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1215;
int words_in_dictionary = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    struct node *pointer = table[hash_value];

    while (pointer != NULL)
    {
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int length = strlen(word);
    int sum_of_letters = 0;
    for (int i = 0; i < length; i++)
    {
        sum_of_letters += toupper(word[i]) - 'A';
    }

    return (length + sum_of_letters) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table

        // Create space for new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        // Copy the word into the new node
        strcpy(new_node->word, word);
        // Hash the word to obtain its hash value
        int hash_value = hash(word);
        // Insert the new node into the hash table (using the index specified by its hash value)
        if (table[hash_value] == NULL)
        {
            table[hash_value] = new_node;
            new_node->next = NULL;
        }
        else
        {
            new_node->next = table[hash_value];
            table[hash_value] = new_node;
        }
        words_in_dictionary++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        struct node *pointer = table[i];

        while (pointer != NULL)
        {
            struct node *temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    return true;
}
