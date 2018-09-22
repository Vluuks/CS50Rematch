#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

    printf("Number:");
    long ccno_long = get_long_long();

    // make string from long
    char ccno[20];
    sprintf(ccno, "%ld", ccno_long);

    // get length and first two numbers then cast to int
    int len = strlen(ccno);

    // get first two digits
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

    // if even, append 0 to start
    // space for terminator and 0
    char ccno_cp[len+2];
    if(len % 2 == 0) {
        ccno_cp[0] = '0';
        strcat(ccno_cp, ccno);
    }

    int sum = 0;
    for(int i = 0; i < strlen(ccno_cp); i++) {

        // make digit from char (atoi is for strings only?)
        int digit = ccno_cp[i] - '0';

        // if index is not even
        if(i % 2 != 0) {
            // multiply by 2
            int prod = digit * 2;

            // if the product is 10 or higher, split and add
            if(prod > 9) {
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