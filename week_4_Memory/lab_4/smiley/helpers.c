#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    for (int i = 0; i < height; i++) // For every row
    {
        for (int j = 0; j < width; j++) // For every column
        {
            // Check for black color then change color
            if (image[i][j].rgbtRed == 00 & image[i][j].rgbtGreen == 00 & image[i][j].rgbtBlue == 00)
            {
                image[i][j].rgbtRed = 0xff;
                image[i][j].rgbtGreen = 0x8c;
                image[i][j].rgbtBlue = 0x00;
            }
        }
    }
}
