#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    fseek(input, 0, SEEK_CUR);
    printf("length of file is %li\n", ftell(input));

    // Read header
    // TODO #3
    WAVHEADER wh;
    fread(&wh, sizeof(WAVHEADER), 1, input);

    fseek(input, 0, SEEK_CUR);
    printf("length of file is %li\n", ftell(input));

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(wh))
    {
        fclose(input);
        printf("Unsupported file\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");

    // Write header to file
    // TODO #6
    fwrite(&wh, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    long block = get_block_size(wh);

    // Write reversed audio to file
    // TODO #8
    BYTE *buffer = malloc(sizeof(block));

    // fseek(input, 0, SEEK_END);
    // long end = ftell(input) / block;
    // printf("end is %li\n", end);

    fseek(input, -(1 * block), SEEK_END);
    printf("length of file is %li\n", ftell(input));

    while (fread(buffer, 1, block, input) == block && ftell(input) > 44)
    {
        fwrite(buffer, 1, block, output);
        fseek(input, -(2 * block), SEEK_CUR);
    }

    fseek(input, 0, SEEK_CUR);
    printf("length of file is %li\n", ftell(input));

    free(buffer);
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    return block_size;
}