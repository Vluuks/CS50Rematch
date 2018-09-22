#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{    
    if (argc != 2)
    {
        printf("Please specify your key as an command line argument.\n");
        return 1;
    }
    
    for(int i = 0, n = strlen(argv[1]); i < n; i++)
    {    
        if (isdigit (argv[1][i]))
        {
            printf("Please construct a key using only alphabetical characters.\n");
            return 1;
        }
    }

    string input = get_string();
    int alpkey = 0;
        
    if (input != NULL)
    {                            
        string key = argv[1];
                    
        for(int i = 0, j = 0, n = strlen(input); i < n; i++)
        {            
            // check if upper or lowercase
            // convert ascii value of letter to alphabet value
            if (islower (key[j]))
            {
                alpkey = key[j] - 97;
            }
            
            else if (isupper (key[j]))
            {
                alpkey = key[j] - 65;
            }
                        
            // converts uppercase letters
            if (isupper(input[i]))
            {                                      
                int alfabetup = input[i] - 65;
                int letterup = (alfabetup + alpkey) % 26;
                letterup = letterup + 65;
                printf("%c", letterup);
                j = (j + 1) % (int) strlen(key);
            }
            
            // converts lowercase letters    
            else if (islower(input[i]))
            {
                int alfabetup = input[i] - 97;
                int letterup = (alfabetup + alpkey) % 26;
                letterup = letterup + 97;
                printf("%c", letterup);
                j = (j + 1) % (int) strlen(key);                   
            }
                       
            // leaves non alphabetical characters unchanged
            else         
            {
                printf("%c", input[i]);
            }                                
        }   
    }
            
    printf("\n");
    return 0;
}