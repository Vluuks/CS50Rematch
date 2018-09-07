#include <stdio.h>
#include <unistd.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

#define _XOPEN_SOURCE
#define LETTERS 52
#define PW_LENGTH 5
#define SALT_LENGTH 2

// performs hash attempt and compare
bool check(char* salt, char* hash, char* attempt) {
    char* new_hash = crypt(attempt, salt);
    if(strcmp(hash, new_hash) == 0) {
        printf("%s\n", attempt);
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {

    // validate user input
    if(argc != 2) {
        printf("Usage: ./crack hash");
        return 1;
    }

    // keep as array to avoid ASCII math
    const char letters[LETTERS] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    // obtain salt
    string hash = argv[1];
    char salt[SALT_LENGTH + 1];
    sprintf(salt, "%c%c", hash[0], hash[1]);
    printf("Salt: %s\n", salt);

    // array for password attempts
    char arr[PW_LENGTH + 1];
    
    // one character
    arr[1] = '\0';
    for(int i = 0; i < LETTERS; i++) {
        arr[0] = letters[i];

        if(check(salt, hash, arr)) {
            return 0;
        }
    }

    // two characters
    arr[2] = '\0';
    for(int k = 0; k < LETTERS; k++) {

        // set first letter
        arr[0] = letters[k];

        // iterate over possible second letters
        for(int l = 0; l < LETTERS; l++) {
            arr[1] = letters[l];

            if(check(salt, hash, arr)) {
                return 0;
            }
        }
    }

    // three characters
    arr[3] = '\0';
    for(int k = 0; k < LETTERS; k++) {

        // set first letter
        arr[0] = letters[k];

        // iterate over possible second letters
        for(int l = 0; l < LETTERS; l++) {
            arr[1] = letters[l];

            // iterate over possible third letters
            for(int m = 0; m < LETTERS; m++) {
                arr[2] = letters[m];

                if(check(salt, hash, arr)) {
                    return 0;
                }
            }
        }
    }

    // four characters
    arr[4] = '\0';
    for(int k = 0; k < LETTERS; k++) {

        // set first letter
        arr[0] = letters[k];

        // iterate over possible second letters
        for(int l = 0; l < LETTERS; l++) {
            arr[1] = letters[l];

            // iterate over possible third letters
            for(int m = 0; m < LETTERS; m++) {
                arr[2] = letters[m];

                // iterate over possible fourth letters
                for(int n = 0; n < LETTERS; n++) {
                    arr[3] = letters[n];

                    if(check(salt, hash, arr)) {
                        return 0;
                    }
                }
            }
        }
    }

    // five characters
    arr[5] = '\0';
    for(int k = 0; k < LETTERS; k++) {
        arr[0] = letters[k];

        // iterate over possible second letters
        for(int l = 0; l < LETTERS; l++) {
            arr[1] = letters[l];

            // iterate over possible third letters
            for(int m = 0; m < LETTERS; m++) {
                arr[2] = letters[m];

                // iterate over possible fourth letters
                for(int n = 0; n < LETTERS; n++) {
                    arr[3] = letters[n];

                    // iterate over possible fifth letters
                    for(int o = 0; o < LETTERS; o++) {
                        arr[4] = letters[o];

                        if(check(salt, hash, arr)) {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("Sorry, could not crack the hashed password.");
    return 0;
}