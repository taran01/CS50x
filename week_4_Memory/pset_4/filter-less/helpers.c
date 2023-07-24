#include "helpers.h"
#include <math.h>
#include <stdio.h>

int bigger(int a);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++) // Loop for every row
    {
        for (int j = 0; j < width; j++) // Loop for very column
        {
            // Image becomes grayscale by getting the avg of all three rgb colors for each pixel
            int avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            // Remember how round's return value is casted to int
            int sepiaRed = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtRed = bigger(sepiaRed);
            image[i][j].rgbtGreen = bigger(sepiaGreen);
            image[i][j].rgbtBlue = bigger(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // make sure to keep width = width / 2 cause we want to flip half the pixels
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy pixels from image to copy
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create sum and counter variables later to be used by avg
            float sumR = 0;
            float sumG = 0;
            float sumB = 0;
            float counter = 0;

            // For Corners

            if (i == 0 && j == 0) // Top left
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j + 1], copy[i + 1][j], copy[i + 1][j + 1]};

                for (int k = 0; k < 4; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (i == 0 && j == (width - 1)) // Top right
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j - 1], copy[i + 1][j], copy[i + 1][j - 1]};

                for (int k = 0; k < 4; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (i == (height - 1) && j == 0) // Bottom left
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i - 1][j], copy[i - 1][j + 1], copy[i][j + 1]};

                for (int k = 0; k < 4; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (i == (height - 1) && j == (width - 1)) // Bottom right
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j - 1], copy[i - 1][j], copy[i - 1][j - 1]};

                for (int k = 0; k < 4; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }

            // For Edges

            else if (i == 0 && 0 < j < (width - 1)) // Top edge
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j - 1], copy[i][j + 1], copy[i + 1][j], copy[i + 1][j - 1], copy[i + 1][j + 1]};

                for (int k = 0; k < 6; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (i == (height - 1) && 0 < j < (width - 1)) // Bottom edge
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j - 1], copy[i][j + 1], copy[i - 1][j], copy[i - 1][j - 1], copy[i - 1][j + 1]};

                for (int k = 0; k < 6; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (j == 0 && 0 < i < (height - 1)) // Left edge
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i - 1][j], copy[i + 1][j], copy[i][j + 1], copy[i - 1][j + 1], copy[i + 1][j + 1]};

                for (int k = 0; k < 6; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }
            else if (j == (width - 1) && 0 < i < (height - 1)) // Right edge
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i - 1][j], copy[i + 1][j], copy[i][j - 1], copy[i - 1][j - 1], copy[i + 1][j - 1]};

                for (int k = 0; k < 6; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }

            // For middle

            else
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j - 1], copy[i][j + 1], copy[i - 1][j], copy[i - 1][j - 1], copy[i - 1][j + 1], copy[i + 1][j], copy[i + 1][j - 1], copy[i + 1][j + 1]};

                for (int k = 0; k < 9; k++)
                {
                    sumR += avg[k].rgbtRed;
                    sumG += avg[k].rgbtGreen;
                    sumB += avg[k].rgbtBlue;
                    counter++;
                }
            }

            int averageR = (int) round(sumR / counter);
            int averageG = (int) round(sumG / counter);
            int averageB = (int) round(sumB / counter);

            image[i][j].rgbtRed = averageR;
            image[i][j].rgbtGreen = averageG;
            image[i][j].rgbtBlue = averageB;
        }
    }
}

int bigger(int a)
{
    if (a > 255)
    {
        return 255;
    }
    else
    {
        return a;
    }
}