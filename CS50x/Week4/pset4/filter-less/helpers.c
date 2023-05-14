#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate grayscale value using formula:
            float gray = (image[i][j].rgbtRed / 3.0) + (image[i][j].rgbtGreen / 3.0)
                         + (image[i][j].rgbtBlue / 3.0);

            // Round up the grayscale value to the nearest integer using the ceil function
            int roundedGray = round(gray);

            // Set all color channels to grayscale value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = roundedGray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate new values for each color channel using provided formulas
            float sepiaRed = (0.393 * image[i][j].rgbtRed)
                             + (0.769 * image[i][j].rgbtGreen)
                             + (0.189 * image[i][j].rgbtBlue);

            float sepiaGreen = (0.349 * image[i][j].rgbtRed)
                               + (0.686 * image[i][j].rgbtGreen)
                               + (0.168 * image[i][j].rgbtBlue);

            float sepiaBlue = (0.272 * image[i][j].rgbtRed)
                              + (0.534 * image[i][j].rgbtGreen)
                              + (0.131 * image[i][j].rgbtBlue);

            // Set each color channel to the calculated value
            // or to 255 if the value is greater than 255
            image[i][j].rgbtRed = (round(sepiaRed) > 255) ? 255 : round(sepiaRed);
            image[i][j].rgbtGreen = (round(sepiaGreen) > 255) ? 255 : round(sepiaGreen);
            image[i][j].rgbtBlue = (round(sepiaBlue) > 255) ? 255 : round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row of the image
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel in the row, up tothe center of the row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel at
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary 2D array to store the sum of the values of the pixels in the 3x3 grid
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0.0;
            float sumGreen = 0.0;
            float sumBlue = 0.0;
            float count = 0.0;

            // Loop through 3x3 grid centered on current pixel
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Check if the current pixel is within the bounds of the image
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        sumRed  += (image[i + k][j + l].rgbtRed);
                        sumGreen += (image[i + k][j + l].rgbtGreen);
                        sumBlue += (image[i + k][j + l].rgbtBlue);
                        count++;
                    }
                }
            }

            temp[i][j].rgbtRed = round(sumRed / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtBlue = round(sumBlue / count);
        }
    }

    // Copy values from temp array back to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] =  temp[i][j];
        }
    }
}