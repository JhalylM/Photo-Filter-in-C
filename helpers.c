#include "helpers.h"
#include <math.h>

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width],
            int color_position);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        // Take average of red, green, and blue
        for (int j = 0; j < width; j++)
        {
            average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            RGBTRIPLE copy = image[i][j];
            // Compute sepia values
            float sepiaRed =
                round(.393 * copy.rgbtRed + .769 * copy.rgbtGreen + .189 * copy.rgbtBlue);
            float sepiaGreen =
                round(.349 * copy.rgbtRed + .686 * copy.rgbtGreen + .168 * copy.rgbtBlue);
            float sepiaBlue =
                round(.272 * copy.rgbtRed + .534 * copy.rgbtGreen + .131 * copy.rgbtBlue);

            // Update pixel with sepia values
            image[i][j].rgbtRed = fmin(sepiaRed, 255);
            image[i][j].rgbtBlue = fmin(sepiaBlue, 255);
            image[i][j].rgbtGreen = fmin(sepiaGreen, 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    int sum = 0;

    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                continue;
            }
            if (color_position == RED_COLOR)
            {
                sum += image[row][column].rgbtRed;
            }
            else if (color_position == GREEN_COLOR)
            {
                sum += image[row][column].rgbtGreen;
            }
            else
            {
                sum += image[row][column].rgbtBlue;
            }
            count++;
        }
    }
    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, RED_COLOR);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, BLUE_COLOR);
        }
    }
    return;
}
