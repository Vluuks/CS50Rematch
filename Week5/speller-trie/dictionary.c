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


// lazy apotrophe solution
#define ARRAY_SIZE 33

/*
    This is a piece of art. No just kidding. Gives back 0 for the apostrophe and
    6~ onward for the letters.
*/
int make_index(char c) {
    return ((tolower(c) - 'a') % 26) + 6;
}


// Prototypes
void testeroni();

/*
    The node contains whether this letter is also the last letter of an existing word,
    and an array of node pointers which, if they exist, in turn contain the same information.
    The letter's location is inferred from the array index where ' = 0 and there are a few
    empty spots, then a = 6. This is to avoid an if statement to check for an apostrophe
    since that would be false in almost all the cases. In this way it just maps to an
    index directly.
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

    // printf("Checking: %s\n", word);

    // iterate over the letters in the word, starting at root
    node* cursor = root;
    for(int i = 0; i < strlen(word); i++) {

        // get index for letter
        // char c = tolower(word[i]);
        int index = make_index(word[i]);

        // printf("Checking: %c\n", c);

        // check child of cursor for that letter
        cursor = cursor->children[index];

        // if particular child exists and it is also the last letter
        if(cursor != NULL) {

            if(i == strlen(word) - 1) {
                return cursor->is_word;
            }

        }

        // this can perhaps be removed later on but now here for understanding
        // if it does not even exist, it can never be right
        else {
            // printf("FALSE: %c does not exist as child.\n", word[i]);
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

        // get reference in the root
        node* current = root;

        // iterate over letters in word
        for(int i = 0; i < strlen(new_word); i++) {

            // if the node at that location does not exist yet
            // (meaning we haven't constructed a word in this fashion)
            int index = make_index(new_word[i]);
            if(current->children[index] == NULL) {

                // allocate memory for a new node at the current location in the trie
                // which is a particular child inside the children array
                current->children[index] = malloc(sizeof(node));

                // verify that it succeeded
                if(current == NULL) {
                    unload();
                    return false;
                }
            }

            // once we can be sure that it exists
            node* temp = current->children[index];

            // set it to true if last character
            if(i == strlen(new_word) - 1) {
                // printf("Last char, setting true: %c . \n", new_word[i]);
                temp->is_word = true;
            }

            // move on to next, setting current to the one we  just created
            current = temp;
        }

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
    return dict_size;
}

/*
    Unloads dictionary from memory, returning true if successful else false
*/
bool unload(void) {

    return true;
}

/*
    Prints through very ineffective means the contents of the child indices of
    the first 3 letters of a word.
*/
void testeroni() {
    for(int i = 0; i < 33; i++) {

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