// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define ARRAY_SIZE 27

// Prototypes
void testeroni();

/*
    The node contains whether this letter is also
    the last letter of an existing word, and an array of node pointers which,
    if they exist, in turn contain the same information.
*/
typedef struct node
{
    bool exists;
    struct node* children[ARRAY_SIZE];
    bool is_word;
}
node;

// root array and size
node* root;
unsigned int dict_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word) {

    printf("%s", word);
    // // if you use current->next then if there is only one
    // // or it is the last it will never go inside
    // while(current != NULL) {

    //     if(strcasecmp(word, current->word) == 0) {
    //         return true;
    //     }

    //     // move on to the next node
    //     current = current->next;
    // }

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

    // init root
    root = malloc(sizeof(node));

    // read file line by line (word by word)
    char new_word[LENGTH + 1];
    while(fscanf(infile, "%s", new_word) != EOF) {

        printf("%s", new_word);

        // get reference in the root
        node* current = root;
        //->children[tolower(new_word[0]) - 'a'];

        // iterate over letters in word
        for(int i = 0; i < strlen(new_word); i++) {

            printf("%c\n", new_word[i]);

            // if the node at that location does not exist yet
            // (meaning we haven't constructed a word in this fashion)
            int index = tolower(new_word[i]) - 'a';
            if(current->children[index] == NULL) {

                printf("making new node\n");

                // allocate memory for a new node
                // at the current location in the trie
                // which is a particular child
                current->children[index] = malloc(sizeof(node));

                if(current == NULL) {
                    unload();
                    return false;
                }

                node* bla = current->children[index];

                // move to next thing


            }

            // // if it's the last character, indicate that if you got until here
            // // the sequence of characters forms a word
            // if(i == strlen(new_word) - 1) {
            //     current->is_word = true;
            // }
            // // if it's not the last, create the node and go to next
            // else {

            //     // if it does exist, go to next letter in the word
            //     // inside the children array
            //     int index = tolower(new_word[i+1]) - 'a';
            //     printf("%i\n", index);
            //     current = current->children[tolower(new_word[i+1]) - 'a'];
            // }


        }

		dict_size++;

    }

    testeroni();
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

    return true;
}

/*
    Prints contents of 1st node of each hashtable index. Can be used for
    a small check to see if words are inserted at the very least. And if
    the first word is the last one in the dictionary (if collision), since
    we enter things at the front of the list rather than at the back.
*/
void testeroni() {
    for(int i = 0; i < 27; i++) {

        if(root->children[i] == NULL) {
            printf("%i NULL\n", i);
        }
        else {
            printf("%i exists\n", i);
        }
    }
}