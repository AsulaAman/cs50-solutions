#include "helpers.h"
#include <math.h>

int lesser(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green and blue
            float average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = (int) average;
            image[i][j].rgbtGreen = (int) average;
            image[i][j].rgbtBlue = (int) average;
        }
    }

    return;
}
// to apply greyscale, run: ./filter -g infile.bmp out.bmp

// Convert image to sepia
// For each pixel, the sepia color values should be calculated based on the original color values
// per the below:
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// Return the lesser of the two values capped at 255

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Apply lesser function
            int sepiaRed =
                lesser(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int sepiaGreen =
                lesser(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int sepiaBlue =
                lesser(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Loop over all pixels
    for (int j = 0; j < width / 2; j++)
    {
        for (int i = 0; i < height; i++)
        {
            // Swap pixels
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Create a function to get the average pixel of a given pixel and its neighbours
RGBTRIPLE get_average_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed = 0, sumGreen = 0, sumBlue = 0;
    float counter = 0;

    // Loop through the neighbouring pixels
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int new_row = row + i, new_col = col + j;

            // Check bounds
            if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width)
            {
                // Update the sum
                sumRed += image[new_row][new_col].rgbtRed;
                sumGreen += image[new_row][new_col].rgbtGreen;
                sumBlue += image[new_row][new_col].rgbtBlue;
                counter++;
            }
        }
    }

    // Compute the average and return
    return (RGBTRIPLE){.rgbtRed = round((float) sumRed / counter),
                       .rgbtGreen = round((float) sumGreen / counter),
                       .rgbtBlue = round((float) sumBlue / counter)};
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = get_average_pixel(i, j, height, width, copy);
        }
    }
}
