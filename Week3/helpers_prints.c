// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

#define COMP_OCTAVE 4
#define COMP_NOTE 'A'
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
    return atoi("FUCK YOU");
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    printf("%s\n", note);

    // grab the right octave
    int len = strlen(note);
    int octave = note[(len + 1) / 2] - '0';
    printf("Current octave: %i\n", octave);

    // calculate initial distance based on octave
    int distance = (octave - COMP_OCTAVE) * 12;
    printf("Notes away from A4 (just octave based): %i\n", distance);
    // get the amount of white keys within octave
    int note_letter = note[0] - 'A';
    printf("ASCII: %i\n", note_letter);

    // correct the octave based location
    //                   KEY    A  B   C   D   E   F   G
    //                 INDEX    0  1,  2,  3,  4,  5,  6
    int sharp_corrections[] = { 0, 2, -9, -7, -5, -4, -2};
    int distance_correction = sharp_corrections[note_letter];
    printf("Correction within octave: %i\n", distance_correction);

    // make corrections if the note itself is a sharp or flat
    if(len == 3) {
        if(note[1] == '#') {
            distance_correction++;
        }
        else {
            distance_correction--;
        }
    }
    printf("Correction within octave after checking if note itself is sharp/flat: %i\n", distance_correction);

    // calculate how far a key is from A4
    distance += distance_correction;

    printf("Applied corrections total: %i\n", distance_correction);
    printf("Final distance: %i\n", distance);

    // apply math to get frequency
    float freq = pow(2.0, distance / (float) 12) * (float) 440;
    printf("%.6f\n", freq);

    return round(freq);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return !strlen(s);
}
