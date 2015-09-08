#include <stdio.h>
#include <stdlib.h>
#include "arr.h"
int main(int argc, char* argv[])
{
    FILE* fp;
    unsigned short width, height;
    unsigned short i, j;
    unsigned long img;
    sscanf(argv[1], "%hu", &width);
    sscanf(argv[2], "%hu", &height);
    fp = fopen("a.api", "wb");
    fwrite(&width, sizeof(unsigned short), 1, fp);
    fwrite(&height, sizeof(unsigned short), 1, fp);
    for(j = 0; j < height; j++)
        for(i = 0; i < width; i++)
        {
            img = *((unsigned long*)gImage_arr + i + j * width);
            fwrite(&img, sizeof(unsigned long), 1, fp);
        }
    fclose(fp);
    return 0;
}
