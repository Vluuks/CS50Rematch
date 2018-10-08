typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;


typedef struct
{
    int number;
    string name;
    string course;
    int credits
} 
STUDENT;