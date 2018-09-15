// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

#define COMP_OCTAVE 4

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
    return atoi("FUCK THIS");
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // grab the right octave
    int len = strlen(note);
    int octave = note[(len + 1) / 2] - '0';

    // calculate initial distance based on octave
    int distance = (octave - COMP_OCTAVE) * 12;

    // correct the octave based location
    // use note's alphahet index to make array function like dict
//                 KEY    A  B   C   D   E   F   G
//               INDEX    0  1,  2,  3,  4,  5,  6
    int corrections[] = { 0, 2, -9, -7, -5, -4, -2};
    int distance_correction = corrections[note[0] - 'A'];

    // make corrections if the note itself is a sharp or flat
    if(len == 3) {
        if(note[1] == '#') {
            distance_correction++;
        }
        else {
            distance_correction--;
        }
    }

    // calculate how far a key is from A4 and apply math
    distance += distance_correction;
    float freq = pow(2.0, distance / (float) 12) * (float) 440;
    return round(freq);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return !strlen(s);
}
