#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    string name = get_string();
    printf("%c", toupper(name[0]));

    // loop over the rest of the name
    for (int i = 0; i < strlen(name); i++) {

        // if char is space
        if(isblank(name[i])) {
            printf("%c", toupper(name[i + 1]));
        }
    }

    printf("\n");
    return 0;
}