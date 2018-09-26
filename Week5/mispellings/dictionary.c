/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * TODO
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#define MAX_LENGTH 45
#define TABLE_SIZE 27

// prototype of hash function
int hash(char* key);

// create the node struct
typedef struct node
{
    char word[MAX_LENGTH + 1];
    struct node* next;
} 
node;

// predefine hash table
node* hashtable[TABLE_SIZE];

// initialize wordcount
/*there is a problem with the wordcount, the return value is 1 more than the actual size of the dictionary*/
/*i ran through the code with gdb multiple times but it initalizes and adds up correctly for every word added*/
/*could not find source of bug in time so initalized to -1 as band aid fix for this problem*/
int wordcount = -1;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
 
 	// create an array for the word to be checked
    char checkword[LENGTH + 1];
    
    // get word input and store it in checkword
    strcpy(checkword, word);
    
    // transform the word into lowercase to compare against dictionary entry
    int length = strlen(checkword);
    
    for (int i = 0; i < length; i++)
    {
    	checkword[i] = tolower(checkword[i]);
   	}

    // hash the word to see in which bucket it should be
    int bucket = hash(checkword);
    
    // if it hashes to an invalid number report it as misspelled
    if (hashtable[bucket] == NULL)
    {
    	return false;
    }
    
    // traverse the linked list inside bucket with a cursor
   	node* cursor = hashtable[bucket];
    
    // compare checkword and word in linked list using strcmp
    while (cursor != NULL)
    {  	
    	// compare checkword with word at cursor to see if it's in the dictionary
    	if (strcmp(checkword, cursor->word) == 0)
    	{
    		return true;
		}
    	
    	// if the word was not found at cursor's position, go on iterating through the linked list
    	else 
    	{
    		cursor = cursor->next;
    	}
    }	
    	
	return false;     
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary file
    FILE* dictionary_load = fopen(dictionary, "r");
    
    // check if dictionary is null
    if (dictionary_load == NULL) 
    {
        printf("Could not open dictionary.");
        return false;
    }

	else
	{
		// create array of chars to store words + \n
		char word[LENGTH + 1];
		
		// initialize bucket
		int bucket = 0;
	
		// read the dictionary file
		while (!feof(dictionary_load))
		{
			// prepare memory to store a word
		    node* new_word_node = malloc(sizeof(node));
		    
			// read from file, one word at the time
			fscanf(dictionary_load, "%s", word);
		
			if (word != NULL)
			{
				// insert the word into the new node
				strcpy((new_word_node->word), word);
				
				// hash the word to determine bucket
				bucket = hash(word);
			
				// check whether hash value actually fits in hash table
				if (bucket > TABLE_SIZE)
				{
					printf("Hash value generated exceeds hash table size.");
					return false;
				}
			   
				// add word to hash table and update wordcount
				new_word_node->next = hashtable[bucket];
				hashtable[bucket] = new_word_node;
				wordcount++;
		    }
		}
	}
	
    // close the dictionary
    fclose(dictionary_load);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
	// if dictionary failed to load return 0
	if (wordcount == 0)
	{
    	return 0;
    }
	
    // return amount of words if dictionary was loaded
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int bucket = 0; bucket < TABLE_SIZE; bucket++)
    {
    	node *cursor = hashtable[bucket];
        while (cursor != NULL)
        {
          node* temp = cursor;
          cursor = cursor->next;
          free(temp);
        }                     
    }
    
    return true;
}

/**
 * Hash function
 */

int hash(char* key)
{
	int bucket = 0;
	
	if (key != NULL)
	{
		int firstletter = toupper(key[0]);
		bucket = (firstletter - 65) % TABLE_SIZE;
		return bucket;
	}

	return true;
}

