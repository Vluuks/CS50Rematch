#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {

    int shift;

    // Check arguments
    if(argc != 2) {
        printf("Provide one argument.");
        return 1;
    }
    else {
        shift = atoi(argv[1]) % 26;
        printf("Text to encrypt: ");
    }

    // Get user input
    string toConvert;
    int len;
    do {
        toConvert = get_string();
        len = strlen(toConvert);
    }
    while(len == 0);

    // Convert
    char converted[len + 1];
    for(int i = 0; i < len; i++) {

        char c = toConvert[i];
        if(islower(c)) {
            int alphaPlaceLower = c - 'a';
            int afterShiftLower = (alphaPlaceLower + shift) % 26;
            converted[i] = afterShiftLower + 'a';
        }
        else if(isupper(c)) {
            int alphaPlaceUpper = c - 'A';
            int afterShiftUpper = (alphaPlaceUpper + shift) % 26;
            converted[i] = afterShiftUpper + 'A';
        }
        else {
            converted[i] = c;
        }
    }

    // Output ciphertext
    printf("ciphertext: %s\n", converted);
    return 0;
}