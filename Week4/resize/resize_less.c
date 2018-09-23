/*
    resize.c 
    CS50x "Rematch" 2018

    Resizes a BMP image (to a larger size) by a given factor. Resizing is done
    both horizontally and vertically by repeating scanlines as necessary.

    Version 1 with the extra loop and no array to store previous scanline. 

*/

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember factor and filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // make new headers
    BITMAPFILEHEADER bf_new = bf;
    BITMAPINFOHEADER bi_new = bi;

    // write new data to the BITMAPINFOHEADER
    bi_new.biWidth *= factor;
    bi_new.biHeight *= factor;
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE) % 4)) % 4;
    bi_new.biSizeImage = abs(bi_new.biHeight) * ((bi_new.biWidth * sizeof(RGBTRIPLE)) + padding_new);
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // write new data to the BITMAPFILEHEADER
    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // determine padding of old image for scanlines
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {

        // repeat vertically
        for(int z = 0; z < factor; z++) {

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++) {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // repeat k times for factor
                // this will increase the image size in horizontal sense
                for(int k = 0; k < factor; k++) {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // go back to beginning of line but only if we are not at the end
            // negative value to go back
            if(z < factor - 1) {
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }

            // write padding to end of this line in new file
            for (int k = 0; k < padding_new; k++) {
                fputc(0x00, outptr);
            }

        }

        // skip padding, if any and go to next line
        fseek(inptr, padding_old, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}