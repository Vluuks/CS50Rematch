// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
// int duration(string fraction)
// {
//     char some[2];
//     some[0] = fraction[0];
//     some[1] = '\0';
//     int ffs_some = atoi(some);

//     char eights[2];
//     eights[0] = fraction[2];
//     eights[1] = '\0';
//     int ffs_eights = atoi(eights);

//     if(ffs_some > 1) {
//         return ffs_some;
//     }
//     else {
//         switch(ffs_eights) {
//             case 8: return 1;
//             case 4: return 2;
//             case 2: return 4;
//         }
//     }
//     return atoi("FUCK YOU");
// }

int duration(string fraction)
{
    if(fraction[0] - '0' > 1) {
        return fraction[0] - '0';
    }
    else {
        switch(fraction[2] - '0') {
            case 8: return 1;
            case 4: return 2;
            case 2: return 4;
        }
    }
    return atoi("WHY IS CASTING A CHAR TO AN INT SO WEIRD");
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    printf("%s", note);
    return 0;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return !strlen(s);
}
