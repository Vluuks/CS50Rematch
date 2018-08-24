#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void) {

    printf("Number:");
    string ccno = get_string();
    int sum = 0;

// American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
// American Express numbers all start with 34 or 37;
// MasterCard numbers all start with 51, 52, 53, 54, or 55; and Visa numbers all start with 4.
    // check types



    // get length and first two numbers then cast to int
    // wtf is this even
    int len = strlen(ccno);

    // 3 because needs space for the null terminator
    char tmp_str[3];
    sprintf(tmp_str, "%c%c", ccno[0], ccno[1]);
    int first_two = atoi(tmp_str);

    string type;

    // AMEX
    if(len == 15 && (first_two == 34 || first_two == 37)) {
        type = "AMEX\n";
    }
    // VISA
    else if((len == 16 || len == 13) && ccno[0] == '4') {
        type = "VISA\n";
    }
    // MC
    else if(len == 16 && (first_two <= 55 && first_two >= 51)) {
        type = "MASTERCARD\n";
    }
    else {
        printf("INVALID\n");
        return 0;
    }


    for(int i = 0; i < len; i++) {

        // make digit from char (atoi is for strings only?)
        int digit = ccno[i] - '0';

        // every other digit
        if(i % 2 != 0) {
            // multiply by 2
            int prod = digit * 2;

            // if the product is 10 or higher, split and add
            if(prod > 9) {
                // can also do plus 1 but tmp/10 is always 1? idk what is better anyway
                prod = (prod % 10) + prod / 10;
            }
            // add to total
            sum += prod;
        }
        else {
            sum += digit;
        }

    }

    if(sum % 10 == 0) {
        printf("%s", type);
    }
    else {
        printf("INVALID\n");
    }

    return 0;
}