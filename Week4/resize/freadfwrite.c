int main(void) {

    FILE* in = fopen("in.txt", "r");

    if (in == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    FILE* out = fopen("out.txt", "w");

    char buffer[5];

    // read from infile to buffer
    while(fread(buffer, 5, 1, in) == 1)
    {
        // write from buffer to outfile
        fwrite(buffer, 5, 1, out);
    }

    fclose(in);
    fclose(out);

}