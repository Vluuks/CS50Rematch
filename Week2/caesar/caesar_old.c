#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]) {

    // Checks presence of command line argument
    if (argc != 2) {
        printf("Please provide a key.\n");
        return 1;
    }

    // Checks if given key is positive and that it's a number
    int key = atoi(argv[1]);
    if (key < 1) {
        printf("Please provide a positive integer to use as a cipher key.\n");
        return 1;
    }

    else {
        // prompts user for plaintext
        string input = get_string();

        if (input != NULL) {
            for(int i = 0, n = strlen(input); i < n; i++) {
                // converts uppercase letters
                if (isupper(input[i]) && isalpha(input[i])) {
                    int letterup = ((input[i] - 65) + key) % 26;
                    letterup = letterup + 65;
                    printf("%c", letterup);
                }
                // converts lowercase letters
                else if (islower(input[i]) && isalpha(input[i])) {
                    int letterlow = ((input[i] - 97) + key) % 26;
                    letterlow = letterlow + 97;
                    printf("%c", letterlow);
                }
                // leaves non letters unaffected
                else{
                    printf("%c", input[i]);
                }
            }
            printf("\n");
        }
    }

    return 0;
}

