#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/*
    Changes given character by "shift" steps by getting ASCII value
    and adjusting it, while maintaining casing.
*/
int shiftChar(char casing, char c, int shift) {
    return casing + ((c - casing) + shift) % 26;
}

int main(int argc, char* argv[]) {

    int shift;

    // Check and obtain shift, looping around alphabet
    if(argc != 2) {
        printf("Provide one argument.");
        return 1;
    }
    else {
        shift = atoi(argv[1]) % 26;
        printf("Text to encrypt: ");
    }

    // Get user's message
    string message;
    int len;
    do {
        message = get_string();
        len = strlen(message);
    }
    while(len == 0);

    // Adjust every alphabetic character in message as needed
    for(int i = 0; i < len; i++) {
        char c = message[i];
        if(islower(c)) {
            message[i] = shiftChar('a', c, shift);
        }
        else if(isupper(c)) {
            message[i] = shiftChar('A', c, shift);
        }
    }

    // Output ciphertext
    printf("ciphertext: %s\n", message);
    return 0;
}