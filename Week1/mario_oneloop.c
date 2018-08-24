#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[]) {

    int h;
    
    do {
        h = get_int();
    }
    while(h < 1 || h > 26);
    
    for(int i = 0; i < h; i++) {
        
        for(int j = 0; j < h + 1; j++) {
            
            if(j < (h - (i + 1))) {
            printf("_");
            }
            else if(j >= (h - (i + 1))) {
                printf("#");
            }
        }
        
        printf("\n");
    }
}