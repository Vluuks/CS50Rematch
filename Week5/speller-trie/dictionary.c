/*
    dictionary.c
    CS50x "Rematch" 2018

    Loads a dictionary from a given text file into a data structure, in this case trie.

*/

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
    The node contains whether this letter is also the last letter of an existing word,
    and an array of node pointers which, if they exist, in turn contain the same information.
    The letter's location is inferred from the array index where a = 0 and z = 25. The apostrophe
    is stored in index 26.
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

/*
    Iterates over the letters in the word and checks for each letter
    if it also exists in the trie. If it's the last letter of the word,
    check if the trie also says that it's actually a word.
*/
bool check(const char *word) {

    printf("Checking: %s\n", word);

    // iterate over the letters in the word, starting at root
    node* cursor = root;
    for(int i = 0; i < strlen(word); i++) {

        // get index for letter
        char c = tolower(word[i]);
        int index = c - 'a';

        printf("Checking: %c\n", c);

        // check child of cursor for that letter
        cursor = cursor->children[index];

        // if particular child exists and it is also the last letter
        if(cursor != NULL) {

            if(i == strlen(word) - 1) {
                // return cursor->is_word;

                if(cursor->is_word){
                    printf("Correct! %s\n", word);
                    return true;
                }
                else {
                    return false;
                }
            }

        }

        // this can perhaps be removed later on but now here for understanding
        // if it does not even exist, it can never be right
        else {
            printf("FALSE: %c does not exist as child.\n", word[i]);
            return false;
        }

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

    // init root
    root = malloc(sizeof(node));

    // read file line by line (word by word)
    char new_word[LENGTH + 1];
    while(fscanf(infile, "%s", new_word) != EOF) {

        // printf("%s", new_word);

        // get reference in the root
        node* current = root;
        //->children[tolower(new_word[0]) - 'a'];

        // iterate over letters in word
        for(int i = 0; i < strlen(new_word); i++) {

            // printf("%c\n", new_word[i]);

            // if the node at that location does not exist yet
            // (meaning we haven't constructed a word in this fashion)
            int index = tolower(new_word[i]) - 'a';
            if(current->children[index] == NULL) {

                // printf("making new node\n");

                // allocate memory for a new node
                // at the current location in the trie
                // which is a particular child
                current->children[index] = malloc(sizeof(node));

                if(current == NULL) {
                    unload();
                    return false;
                }
            }

            // once we can be sure that it exists
            node* temp = current->children[index];

            // set it to true if last character
            if(i == strlen(new_word) - 1) {
                printf("Last char, setting true: %c . \n", new_word[i]);
                temp->is_word = true;
            }

            // move on to next
            current = temp;
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
            printf("%c NULL\n", i + 'a');
        }
        else {

            // the root's child exists at location i
            printf("%c exists\n", i + 'a');

            // now to check inside that particular child
            node* cursor = root->children[i];
            for(int j = 0; j < 27; j++) {

                // the cursor's child exists at location j
                if(cursor->children[j] != NULL) {

                    printf("%c 2nd tier exists\n", j + 'a');

                    // check if this child itself has children
                    node* cursor2 = cursor->children[j];
                    for(int k = 0; k < 27; k++) {

                        // 2rd tier children
                        if(cursor2->children[k] != NULL) {
                            printf("%c 3rd tier exists\n", k + 'a');
                        }
                    }
                }
            }
        }

        printf("-------\n");
    }
}