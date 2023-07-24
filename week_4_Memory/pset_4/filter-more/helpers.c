#include "helpers.h"
#include <math.h>
#include <stdio.h>

float bigger(float n);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            // For Corners

            if (i == 0 && j == 0) // Top left
            {
                RGBTRIPLE avg[] = {copy[i][j], copy[i][j + 1], copy[i + 1][j], copy[i + 1][j + 1]};

                float red[4];
                float green[4];
                float blue[4];

                // For Gx values

                for (int k = 0, g = 0; k < 2; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = 0; k < 2; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 2; k < 4; k++, g -= 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));

            }
            else if (i == 0 && j == (width - 1)) // Top right
            {
                RGBTRIPLE avg[] = {copy[i][j - 1], copy[i][j], copy[i + 1][j - 1], copy[i + 1][j]};

                float red[4];
                float green[4];
                float blue[4];

                // For Gx values

                for (int k = 0, g = -2; k < 2; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = -1; k < 4; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = 0; k < 2; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 1; k < 4; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
            else if (i == (height - 1) && j == 0) // Bottom left
            {
                RGBTRIPLE avg[] = {copy[i - 1][j], copy[i - 1][j + 1], copy[i][j], copy[i][j + 1]};

                float red[4];
                float green[4];
                float blue[4];

                // For Gx values

                for (int k = 0, g = 0; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = -2; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
            else if (i == (height - 1) && j == (width - 1)) // Bottom right
            {
                RGBTRIPLE avg[] = {copy[i - 1][j - 1], copy[i - 1][j], copy[i][j - 1], copy[i][j]};

                float red[4];
                float green[4];
                float blue[4];

                // For Gx values

                for (int k = 0, g = -1; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = -2; k < 4; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = -1; k < 2; k++, g -= 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 4; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }

            // For Edges

            else if (i == 0 && 0 < j < (width - 1)) // Top edge
            {
                RGBTRIPLE avg[] = {copy[i][j - 1], copy[i][j], copy[i][j + 1], copy[i + 1][j - 1], copy[i + 1][j], copy[i + 1][j + 1]};

                float red[6];
                float green[6];
                float blue[6];

                // For Gx values

                for (int k = 0, g = -2; k < 3; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 3, g = -1; k < 6; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = 0; k < 6; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 1, g = 0; k < 6; k += 3, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 6; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
            else if (i == (height - 1) && 0 < j < (width - 1)) // Bottom edge
            {
                RGBTRIPLE avg[] = {copy[i - 1][j - 1], copy[i - 1][j], copy[i - 1][j + 1], copy[i][j - 1], copy[i][j], copy[i][j + 1]};

                float red[6];
                float green[6];
                float blue[6];

                // For Gx values

                for (int k = 0, g = -1; k < 3; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 3, g = -2; k < 6; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = -1; k < 6; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 1, g = -2; k < 6; k += 3, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = -1; k < 6; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
            else if (j == 0 && 0 < i < (height - 1)) // Left edge
            {
                RGBTRIPLE avg[] = {copy[i - 1][j], copy[i - 1][j + 1], copy[i][j], copy[i][j + 1], copy[i + 1][j], copy[i + 1][j + 1]};

                float red[6];
                float green[6];
                float blue[6];

                // For Gx values

                for (int k = 0, g = 0; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 4, g = 0; k < 6; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = -2; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 4, g = 2; k < 6; k++, g -= 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
            else if (j == (width - 1) && 0 < i < (height - 1)) // Right edge
            {
                RGBTRIPLE avg[] = {copy[i - 1][j - 1], copy[i - 1][j], copy[i][j - 1], copy[i][j], copy[i + 1][j - 1], copy[i + 1][j]};

                float red[6];
                float green[6];
                float blue[6];

                // For Gx values

                for (int k = 0, g = -1; k < 2; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = -2; k < 4; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 4, g = -1; k < 6; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // For Gy values

                for (int k = 0, g = -1; k < 2; k++, g -= 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = 0; k < 4; k++)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 4, g = 1; k < 6; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 6; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }

            // For middle

            else
            {
                RGBTRIPLE avg[] = {copy[i - 1][j - 1], copy[i - 1][j], copy[i - 1][j + 1], copy[i][j - 1], copy[i][j], copy[i][j + 1], copy[i + 1][j - 1], copy[i + 1][j], copy[i + 1][j + 1]};

                float red[9];
                float green[9];
                float blue[9];

                // For Gx values
                for (int k = 0, g = -1; k < 3; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 3, g = -2; k < 6; k++, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 6, g = -1; k < 9; k++, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }


                float GxR = 0;
                float GxG = 0;
                float GxB = 0;

                for (int k = 0; k < 9; k++)
                {
                    GxR += red[k];
                    GxG += green[k];
                    GxB += blue[k];
                }

                // Gy values
                for (int k = 0, g = -1; k < 9; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 1, g = -2; k < 9; k += 3, g += 2)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }
                for (int k = 2, g = -1; k < 9; k += 3, g += 1)
                {
                    red[k] = avg[k].rgbtRed * g;
                    green[k] = avg[k].rgbtGreen * g;
                    blue[k] = avg[k].rgbtBlue * g;
                }

                float GyR = 0;
                float GyG = 0;
                float GyB = 0;

                for (int k = 0; k < 9; k++)
                {
                    GyR += red[k];
                    GyG += green[k];
                    GyB += blue[k];
                }

                float sobelR = sqrt(pow(GxR, 2) + pow(GyR, 2));
                float sobelG = sqrt(pow(GxG, 2) + pow(GyG, 2));
                float sobelB = sqrt(pow(GxB, 2) + pow(GyB, 2));

                image[i][j].rgbtRed = (int) round(bigger(sobelR));
                image[i][j].rgbtGreen = (int) round(bigger(sobelG));
                image[i][j].rgbtBlue = (int) round(bigger(sobelB));
            }
        }
    }
}

float bigger(float n)
{
    if (n > 255)
    {
        return 255;
    }
    return n;
}