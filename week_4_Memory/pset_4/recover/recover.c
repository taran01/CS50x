#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512
FILE *img;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover *file\n");
        return 1;
    }

    // open input file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Invalid file\n");
        return 1;
    }

    BYTE *buffer = malloc(BLOCK_SIZE);
    char *filename = malloc(8 * sizeof(char));
    int fileno = 0;

    while (fread(buffer, 1, BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        // check for jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if its first jpeg
            if (fileno == 0)
            {
                sprintf(filename, "%03i.jpg", fileno);
                img = fopen(filename, "w");

                fwrite(buffer, 1, BLOCK_SIZE, img);
                fileno++;
            }
            // if already found close the previous one and make new jpeg
            else
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", fileno);
                img = fopen(filename, "w");

                fwrite(buffer, 1, BLOCK_SIZE, img);
                fileno++;
            }
        }
        // if no signatures found and already found a jpeg copy block to that img
        else if (fileno > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    free(buffer);
    free(filename);
    fclose(infile);
    fclose(img);
}