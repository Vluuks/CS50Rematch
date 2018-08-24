#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[]) {

    int h;
    
    do {
        h = get_int();
    }
    while(h < 1 || h > 26);
    
    for(int i = 0; i < h; i++) {
        
        for(int j = 0; j < h - (i + 1); j++) {
            printf("_");
        }
        
        for(int k = 0; k < i + 1; k++) {
            printf("#");
        }
        
        printf("__");
        
        for(int k = 0; k < i + 1; k++) {
            printf("#");
        }
        
        for(int j = 0; j < h - (i + 1); j++) {
            printf("_");
        }
        
        printf("\n");
    }
}