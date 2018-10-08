// https://reference.cs50.net/stdio/fseek super useful! 
// takes a file pointer, an offset and a position from where to apply said offset

// in in ptr, skip 4 bytes ahead from current position
fseek(inptr, 4, SEEK_CUR);

// in outptr, skip bitmapinfoheader bytes forward, relative to your current position
// sizeof returns the size in bytes. So this is useful when you want to skip over a full block
// like with the structs! 
fseek(outptr, sizeof(BITMAPINFOHEADER), SEEK_CUR);

// from the end, go back one pixel = 3 bytes (24 bits)
// notice the - which means we are going back instead of forward
fseek(outptr, -(sizeof(RGBTRIPLE)), SEEK_END);

// by default, the file pointer goes forward, in line with the things you read or write

SEEK_SET // relative to the start of the file
SEEK_END // relative to the end of the file

