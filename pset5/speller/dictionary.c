// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#define MULTIPLIER (37)

int word_number = 0;

// Represents a node in a hash table (STRUCT NODES)
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (might want to increase this N value)
const unsigned int N = 100000;

// Hash table
    // In a Hash table is a linked list: every node has a value and pointer to the next node (char word [length+1] and struct node *next).
node *table[N];

// Returns true if word is in dictionary, else false (CHECK FUNCTION), CASE INSENSITIVE
bool check(const char *word)
{
    // TODO
    // 1. Hash word to obtain hash value
    // Credits to Jason C: https://www.youtube.com/watch?v=qPz_Mr69yE0&list=PLhQjrBD2T382T4b6jjwX_qbU23E_Unwcz&index=5
    //
    char s[strlen(word) + 1];

    for (int i = 0; i < strlen(word); i++)
    {
        s[i] = tolower(word[i]);
    }

    s[strlen(word)] = '\0';

    int hash_value = hash(s);

    // 2. Access linked list at that index in the hash table

    // 3. Transverse linked list, 1 node at a time, looking for the word with the function (strcasecmp) that returns true if found
        // head -> bat -> book -> banana
        // Set a variable "cursor" which is 1st initially a pointer to the 1st element of the linked list at 'bat'
        // strcasecmp, if false, then move to the next element of the linked list
        // cursor = cursor -> next;
        // Keep moving this cursor until you get NULL, checking each node for the word.
    for (node *tmp_cursor = table[hash_value]; tmp_cursor != NULL; tmp_cursor = tmp_cursor -> next)
    {
        if (strcasecmp(tmp_cursor -> word, s) == 0)
        {
            return true;
        }
        else if (strcasecmp(tmp_cursor -> word, s) != 0)
        {
            return false;
        }
    }
    return false;
}

// Hashes word to a number (HASH FUNCTION)
// Credits: https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
unsigned int hash(const char *word)
{
    // TODO
    // 1. Takes a word as input: alphabetical chars and possibly apostrophes

    // 2. Output: Outputs a number corresponding to which "bucket of array" to store the word in. Numerical index between 0 and N - 1, recursive. Value of N is declared in line 17.
    // 3. Deterministic (i.e. if I have an input, then I should get the same output)
        // We will need to decide the on the value of N. Larger N means more buckets (the length of our array and also the possible values our hash can return),
            // Data is also spread apart more, potentially faster search time
        // So the array lies between 0 and N - 1. If the function ends up with a value >= than N, you can take the value of % N to get a value in the appropriate range.
        // Can google out existing hash functions, but have to cite it.
            // Example:
                // First letter
                // First two letters
                // Math using all letters

    unsigned long h;
    unsigned const char *us;
    us = (unsigned const char *) word;
    h = 0;
    while (*us != '\0')
    {
        h = h * MULTIPLIER + *us;
        us++;
    }
    return h % N ;

}

// Loads dictionary into memory(hashtable), returning true if successful, else false (LOAD FUNCTION)
// bool is true if all the data is able to be loaded into the hash table, false if memory.alloc is not there or file cannot be opened.
bool load(const char *dictionary)
{
    // 1. Open the dictionary file. Use fopen function, remember to check if return value is NULL.
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        return false;
    }

    char *word_buffer = malloc(sizeof(char) * (LENGTH + 1));
    if (word_buffer == NULL)
    {
        return false;
    }

    // 2. Read strings from the dictionary file one at a time. fscanf(file, "%s", word) where fscanf will return EOF once it reaches the end of the file.
    while (fscanf(dictionary_file, "%s", word_buffer) != EOF)
    {
        // 3. Create a new node for each word. Use malloc, remember to check if return value is NULL. Copy word into node using strcpy.
            // In order to have more rows of link list, we need to allocate memory: node *n = malloc(sizeof(node));
            // To store data into the node, strcpy(n -> word, "Hello");
            // If we don't know what to set the pointer to, then n ->next = NULL;

        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            free(word_node);
            return false;
        }

        strcpy(word_node -> word, word_buffer);
        word_number++;

        // 4. Hash word to create hash value number to put into our array of linked lists. Call upon the hash function, the function takes a string and returns an index.
        int temp_hash_index = hash(word_buffer);

        // 5. Insert node into hash table at that location.
            // E.g. head -> bat -> book -> banana && new_node -> blue
                // 1) Set "blue" from "new node -> blue" to "blue -> bat -> book - > banana" 2) && then set from "head -> bat -> .." to "head -> blue -> bat..."
        word_node -> next = table[temp_hash_index];

        table[temp_hash_index] = word_node;

    }

    fclose(dictionary_file);
    free(word_buffer);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded (SIZE FUNCTION)
unsigned int size(void)
{
    // TODO
    // 1. Iterate every single link list available OR as we are loading the hash tables we could somehow keep track the no. of words added in the dictionary so far.
    return word_number;
}

// Unloads dictionary from memory, returning true if successful, else false (UNLOAD FUNCTION)
bool unload(void)
{
    // TODO
    // head -> bat -> book -> banana, cursor (also a tmp) -> bat -> book -> banana
    // 1. Create a variable tmp to point at the node (i.e. bat) the cursor is pointing.
    // 2. Move the cursor to the next element in the linked list (book) before we free tmp free(tmp);
    // 3. Repeat this process.

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }

    return true;

}
