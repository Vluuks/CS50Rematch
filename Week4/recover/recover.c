/*
    recover.c
    CS50x "Rematch" 2018

    Recovers JPG images from a given .raw file. Assumes JPG files start with
    a certain pattern of bits, and after the first has started the rest is
    laid out back to back with no other things inbetween.

*/

#include <stdio.h>
#include <cs50.h>
#include <stdint.h>

// constants
typedef uint8_t  BYTE;
#define FILENAME_LENGTH 8
#define CHUNK_SIZE 512

int main(int argc, char* argv[]) {

    // verify correct usage
    if(argc != 2) {
        fprintf(stderr, "Usage: ./recover file.raw");
        return 1;
    }

    // open file and verify
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // prepare for filename generation
    int jpgcount = 0;
    char filename[FILENAME_LENGTH];

    // define size of buffer
    BYTE buffer[CHUNK_SIZE];
    FILE *img;

    // as long as there input of CHUNK_SIZE
    while(fread(buffer, CHUNK_SIZE, 1, inptr) != 0) {

        // check if first 4 bytes match the new JPG pattern
        if(buffer[0] == 0xff && buffer[1] == 0xd8 &&
           buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {

            // close previous if it was open
            if(jpgcount != 0) {
                fclose(img);
            }

            // make new file name
            sprintf(filename, "%03i.jpg", jpgcount++);

            // open file and verify this
            img = fopen(filename, "w");
            if(img == NULL) {
                fprintf(stderr, "Could not open file.");
                return 3;
            }

            // write 512 to file
            fwrite(&buffer, CHUNK_SIZE, 1, img);
        }

        // if not, continue writing current jpg
        else if (jpgcount != 0) {
            fwrite(&buffer, CHUNK_SIZE, 1, img);
        }
    }

    // close raw file
    fclose(inptr);
}