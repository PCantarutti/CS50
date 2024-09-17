// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
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
const unsigned int N = 50000;

// Hash table
node *table[N];

int contagem = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // returns true if found else return false.
    int index = hash(word);
    // make a cursor node which points to the head of the hash table
    node *cursor = table[index];
    // for loop to go through the list until the final node is reached.
    for (node *temp = cursor; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // for  this hash get the lengh of the string then we will sum the value of the characters.
    unsigned int hashvalue = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }
    return hashvalue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Abra o arquivo do dicionário
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Could not open\n");
        return false;
    }

    // Leia cada palavra no arquivo
    char wordlista[LENGTH + 1]; // Assume que as palavras têm até 45 caracteres

    while (fscanf(source, "%s", wordlista) != EOF)
    {
        contagem++;

        // Process the word (e.g., print it)
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return 1;
        }

        // Copia a palavra para o node
        strcpy(new_node->word, wordlista);
        new_node->next = NULL;

        // Calcula o índice na tabela hash
        unsigned int index = hash(wordlista);

        // if the index is not yet assigned, put the newest node at the head of this index.
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
        else
        {
            // makes the next the new head
            new_node->next = table[index];
            // head points to the new node.
            table[index] = new_node;
        }
    }
    // Adicione cada palavra na tabela hash

    // Feche o arquivo do dicionário
    printf("%i\n", contagem);
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return contagem;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
