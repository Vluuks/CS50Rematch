#include <cs50.h>
#include <stdio.h>
#include <strings.h>

int main(void) {

    string a = "HEY ALLEMAAL";
    string b = "hey allemaal";

    printf("%i", strcasecmp(a, b));
}