#include <cs50.h>
#include <stdio.h>

void bubble_sort(int values[], int n);
void selection_sort(int values[], int n);

int main(void) {


    int array[] = {12, 6, 4, 3, 8, 2, 9};

    selection_sort(array, 7);
}

void selection_sort(int values[], int n) {

    // moving the comparison step
    // need something to compare against so
    // n - 2, meaning prelast
    for(int i = 0; i <= n - 2; i++) {

        int current_min_index = i;

        // iterate over the second half of the array
        // starting at the point after i hence
        // the initialization is at i + 1
        for(int j = i + 1; j < n; j++) {

            // check if some value is smaller than the value
            // we have stored as minimum
            if(values[j] < values[current_min_index]) {

                current_min_index = j;

                // this means that i now holds the lowest value
            }
        }

        // if we found something that is actually lower
        // so there is a new index that is holding the lowest number
        if(current_min_index != i) {

            // swap min index with i
                        // swap the value at j with the value at i
            int temp = values[i];
            values[i] = values[current_min_index];
            values[current_min_index] = temp;

        }

        printf("array");
        for(int k = 0; k < 7; k++) {
            printf("%i ", values[k]);
        }
        printf("\n");
    }

}

void bubble_sort(int values[], int n) {

    // this must me done multiple times
    int swaps;
    do {

        printf("N for this iteration: %i\n", n);
        swaps = 0;
        for(int i = 1; i < n; i++) {

            int b = values[i];
            int a = values[i - 1];

            // check if they are in order
            if (b < a) {
                // printf("swapping\n");
                // swap
                values[i] = a;
                values[i - 1] = b;
                swaps++;
            }

        }

        n -= 1;

        printf("array");
        for(int i = 0; i < 7; i++) {
            printf("%i ", values[i]);
        }
        printf("\n");

    } while(swaps > 0);
}