/*
    dictionary.c 
    CS50x "Rematch" 2018

    Loads a dictionary from a given text file into a data structure, in this case a hash table with
    a linked list behind every index. The hash is determined based on the word (case insensitive) by
    the djb2 hash function (http://www.cse.yorku.ca/~oz/hash.html). Check performs a check on each word
    in a text file, hashing it then comparing it against each word in the respective bucket's linked
    list. Finally, memory used to store the linked list is freed up.

    Compiler settings were adjusted to promote speed. Average performance 0.10 s on La La Land. I have
    no clue if that is fast or not but since my first try three years ago took at least 20 seconds I'll 
    roll with it.
*/

#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h> // strcasecmp is in this one

#include "dictionary.h"

#define TABLE_SIZE 8192

// prototypes
void testeroni();
unsigned long hash(const char* word);

/* 
    The node struct, node is mentioned on the first line because
    the struct itself contains it so the name needs to be known
    before that, rather than just at the end.
*/
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// Hash table etc.
node* hashtable[TABLE_SIZE];
unsigned int dict_size = 0;


/*
    Returns true if word is in dictionary else false. Takes a word, hashes
    it and then traverses the bucket's linked list to see if there is a 
    matching word inside. Case insensitive due to among other things strcasecmp. 
*/
bool check(const char *word) {

    int bucket = hash(word);
    node* current = hashtable[bucket];

    // if you use current->next, then if there is only one
    // or it is the last it will never go inside the while
    while(current != NULL) {

        if(strcasecmp(word, current->word) == 0) {
            return true;
        }

        // move on to the next node
        current = current->next;
    }

    return false;
}

/* 
    Loads dictionary into memory, returning true if successful else false.
    Uses a hash table with linked lists for each index in the table. 
*/
bool load(const char *dictionary) {
    // open file
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL) {
        return false;
    }

    // read file line by line
    char new_word[LENGTH + 1];
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

    fclose(infile);
    return true;
}

/*
    Returns number of words in dictionary if loaded else 0 if not yet loaded
*/
unsigned int size(void) {
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

/*
    Prints contents of 1st node of each hashtable index. Can be used for
    a small check to see if words are inserted at the very least. And if
    the first word is the last one in the dictionary (if collision), since
    we enter things at the front of the list rather than at the back.
*/
void testeroni() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("%s\n", hashtable[i]->word);
    }
}