// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define TABLE_SIZE 8192

// Prototypes
void testeroni();
unsigned long hash(const char* word);

// Create the node struct
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// Hash table etc.
node* hashtable[TABLE_SIZE];
unsigned int dict_size = 0;


// Returns true if word is in dictionary else false
bool check(const char *word) {

    int bucket = hash(word);

    node* current = hashtable[bucket];

    // if you use current->next then if there is only one
    // or it is the last it will never go inside
    while(current != NULL) {

        // printf("checking: %s\n", current->word);
        if(strcasecmp(word, current->word) == 0) {
            return true;
        }

        // return !strcasecmp(word, current->word);

        // move on to the next node
        current = current->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) {
    // open file
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL) {
        return false;
    }

    char new_word[LENGTH + 1];

    // read file line by line
    while(fscanf(infile, "%s", new_word) != EOF) {

        // allocate memory for a new node
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL) {
            unload();
            return false;
        }

        // insert the word into the new node
		strcpy((new_node->word), new_word);

		// determine bucket
		int bucket = hash(new_word);

		// insert into appropriate linked list
		// stores the pointer that was in head (pointing to 1st element)
		// inside the new node's next value, since it will now become 2nd element
		// after the new_node.
		new_node->next = hashtable[bucket];

		// then we can set the head to the new node since we know that now it contains
		// a link to the previous 1st, now 2nd node because of the line before.
		hashtable[bucket] = new_node;
		dict_size++;

    }

    // testeroni();
    fclose(infile);
    return true;
}

/*
    Returns number of words in dictionary if loaded else 0 if not yet loaded
*/
unsigned int size(void) {
    // TODO
    return dict_size;
}

/*
    Unloads dictionary from memory, returning true if successful else false
*/
bool unload(void) {
    for(int i = 0; i < TABLE_SIZE; i++) {

        node* cursor = hashtable[i];

        while(cursor != NULL) {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }

    return true;
}

/*
    Hash function from: http://www.cse.yorku.ca/~oz/hash.html
    It needs to generate the same bucket for both lower/uppercase
    words and combinations thereof, hence the tolower() call.
*/
unsigned long hash(const char* word) {

    unsigned long hash = 5381;

    for(int i = 0; i < strlen(word); i++) {
        hash = ((hash << 5) + hash) + tolower(word[i]);
    }

    return hash % TABLE_SIZE;
}

void testeroni() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%s\n", hashtable[i]->word);
    }
}