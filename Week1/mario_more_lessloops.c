#include <stdio.h>
#include <cs50.h>

// I am not responsible for brain damage sustained by reading this piece of garbage
int main(int argc, char* argv[]) {

    int h;
    
    do {
        h = get_int();
    }
    while(h < 1 || h > 26);
    
    for(int i = 0; i < h; i++) {
        
        for(int j = 0; j < h*2 + 2; j++) {
            
            // first part spaces
            if(j < h - (i + 1)) {
               printf("_"); 
            }
            // first part hashes
            else if(j >= h - (i + 1) && j < h) {
                printf("#");
            }
            // 2nd part hashes
            // j must be higher than or equal to h+2
            else if(j >= h + 2) {
                
                // hashes
                // h-(h-(i+1) equals to the amount of hashes to be printed
                // j-(h+2) is the index of the second part of the pyramid

                if(j - (h + 2) < h - (h - (i + 1))) {
                    printf("#");
                }
                else {
                    printf("_");
                }
            }
            else {
                printf("_");
            }
            
        }
        
        printf("\n");
    }
}