#include <stdio.h> 
#include <math.h>
#include <cs50.h>

int main(void) {

    long long ccnumber = 0;
    int lastnumber = 0;
    int product = 0;
    int sum = 0;
        
    printf("Please insert CC number:\n");
    ccnumber = get_long_long();
    
    // if 13 digit card starting with 4 max (VISA)
    if(5000000000000 > ccnumber && ccnumber >= 4000000000000) {

        int ccnumber_array[13];

        for(int i = 0; i < 13; i++) {
            
            lastnumber = ccnumber%10;
            ccnumber_array[12-i] = lastnumber; // fills array from back to front so in the end numbers are in good order
            ccnumber /= 10;
        }
        
        
        for(int j = 0; j < 13; j++) {
        
            //printf("%i", ccnumber_array[j]);
        
            // if indexnumber of array is uneven
            if(j%2 != 0) {
                // multiply every other digit by 2
                product = ccnumber_array[j] * 2;
                
                // if more than 2 number take last and add to 1st
                if(product > 9)
                    sum += product%10 + 1;
                // else just add as is
                else
                    sum += product;
            }
            
            // if indexnumber is even
            else
                sum += ccnumber_array[j];
        }
        
        if(sum%10 == 0)
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    
    
    // if 15 digit card starting with 34 to 37 (AMEX)
    else if(380000000000000 > ccnumber && ccnumber >= 340000000000000) {
        
        int ccnumber_array[15];
        
        for(int i = 0; i < 15; i++){
            
            lastnumber = ccnumber%10;
            ccnumber_array[14-i] = lastnumber; // fills array from back to front so in the end numbers are in good order
            ccnumber /= 10;
        }
        
        for(int j = 0; j < 15; j++){

            // if indexnumber of array is uneven
            if(j%2 != 0){
                // multiply every other digit by 2
                product = ccnumber_array[j] * 2;
                
                // if more than 2 number take last and add to 1st
                if(product > 9)
                    sum += product%10 + 1;
                // else just add as is
                else
                    sum += product;
            }
            
            // if indexnumber is even
            else
                sum += ccnumber_array[j];
        }
        
        if(sum%10 == 0)
            printf("AMEX\n");
        else
            printf("INVALID\n");        
        
    }
    
    // if 16 digit card starting with 4 (VISA)
    else if(5000000000000000 > ccnumber && ccnumber >= 4000000000000000){

        int ccnumber_array[16];
    
        for(int i = 0; i < 16; i++){
            
            lastnumber = ccnumber%10;
            ccnumber_array[15-i] = lastnumber; // fills array from back to front so in the end numbers are in good order
            ccnumber /= 10;
        }

        for(int j = 0; j < 16; j++){
            
            // if indexnumber of array is even
            if(j%2 == 0){
                // multiply every other digit by 2
                product = ccnumber_array[j] * 2;
                
                // if more than 2 number take last and add to 1st
                if(product > 9)
                    sum += product%10 + 1;
                // else just add as is
                else
                    sum += product;
            }
            
            // if indexnumber is uneven
            else
                sum += ccnumber_array[j];
        }
        
        if(sum%10 == 0)
            printf("VISA\n");
        else
            printf("INVALID\n");           
    }
    
        // if 16 digit card starting with 51 to 55 (MC)
    else if(5600000000000000 > ccnumber && ccnumber >= 5100000000000000){

        int ccnumber_array[16];
    
        for(int i = 0; i < 16; i++){
            
            lastnumber = ccnumber%10;
            ccnumber_array[15-i] = lastnumber; // fills array from back to front so in the end numbers are in good order
            ccnumber /= 10;
        }

        for(int j = 0; j < 16; j++){
            
            //printf("%i", ccnumber_array[j]);
        
            // if indexnumber of array is even
            if(j%2 == 0){
                // multiply every other digit by 2
                product = ccnumber_array[j] * 2;
                
                // if more than 2 number take last and add to 1st
                if(product > 9)
                    sum += product%10 + 1;
                // else just add as is
                else
                    sum += product;
            }
            
            // if indexnumber is uneven
            else
                sum += ccnumber_array[j];
        }
        
        if(sum%10 == 0)
            printf("MASTERCARD\n");
        else
            printf("INVALID\n");           
    }
    // if the number has an invalid amount of numbers or starts with the wrong sequence it can never be valid
    else
        printf("INVALID\n");
        
    return 0;
    
}