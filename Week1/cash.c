#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(int argc, char* argv[]) {

    float f;

    do {
        printf("HOE VEEL MUNTEN JONG");
        f = get_float();
    }
    while(f < 0);

    // cents
    int cents = (int) roundf(f*100);
    int coins = 0;

    // alternatively, cents >= 25 etc. but my brain's weird
    while(cents - 25 >= 0) {
        cents -= 25;
        coins++;
    }
    while(cents - 10 >= 0) {
        cents -= 10;
        coins++;
    }
    while(cents - 5 >= 0) {
        cents -= 5;
        coins++;
    }

    coins += cents;

    printf("%i\n", coins);
}