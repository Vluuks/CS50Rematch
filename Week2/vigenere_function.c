#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int shiftChar(char casing, char c, char shift) {
    return casing + ((c - casing) + (shift - 'a')) % 26;
}

int main(int argc, char* argv[]) {

    string key;
    if(argc != 2) {
        printf("Provide one argument.");
        return 1;
    }
    else {
        key = argv[1];
        printf("Text to encrypt: ");
    }

    // check and standardize key
    int klen = strlen(key);
    for(int k = 0; k < klen; k++) {

        if(isalpha(key[k])) {
            key[k] = tolower(key[k]);
        }
        else {
            return 1;
        }
    }

    // get user input
    string message;
    int len;
    do {
        message = get_string();
        len = strlen(message);
    }
    while(len == 0);

    // iterate over input
    for(int i = 0, j = 0; i < len; i++, j++) {

        char c = message[i];
        if(islower(c)) {
            message[i] = shiftChar('a', c, key[j%klen]);
        }
        else if(isupper(c)) {
            message[i] = shiftChar('A', c, key[j%klen]);
        }
        else {
            j--;
        }
    }

    // output ciphertext
    printf("ciphertext: %s\n", message);
    return 0;
}