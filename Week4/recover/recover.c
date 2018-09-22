#include <stdio.h>
#include <cs50.h>

int main(int argc, char* argv[]) {


    if(argc != 2) {
        fprintf(stderr, "Usage: ./recover file.raw");
        return 1;
    }

    // open file
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // find beginning
    // while not end of file


    unsigned char buffer[512];

    int jpgcount = 0;
    char filename[8];

    FILE *img;
    while(fread(buffer, 512, 1, inptr) != 0) {

        // check if first 4 bytes match the JPG pattern
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
            fwrite(&buffer, 512, 1, img);

        }

        else if (jpgcount != 0) {
            fwrite(&buffer, 512, 1, img);
        }


    }

    fclose(inptr);
    // open new

    // write 512 bytes until  new jpeg

    // if end of file stop

}