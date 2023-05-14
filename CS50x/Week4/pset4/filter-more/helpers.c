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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary 2D array to store the new image
    RGBTRIPLE temp[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Initialize temp array with all zeros
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = 0;
            temp[i][j].rgbtGreen = 0;
            temp[i][j].rgbtBlue = 0;
        }
    }

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Set all channels of the current pixel to 0
            int Gx_red = 0;
            int Gy_red = 0;
            int Gx_green = 0;
            int Gy_green = 0;
            int Gx_blue = 0;
            int Gy_blue = 0;


            // Compute Gx and Gy for the red, green and blue channels using the Sobel operator
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Check if current pixel is within the bounds of the image
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {

                        Gx_red += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        Gy_red += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];

                        Gx_green += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        Gy_green += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];

                        Gx_blue += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                        Gy_blue += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            // Compute the gradient magnitude for the red channel
            int gradient_magnitude_red = round(sqrt((Gx_red * Gx_red) + (Gy_red * Gy_red)));
            // Compute the gradient magnitude for the green channel
            int gradient_magnitude_green = round(sqrt((Gx_green * Gx_green) + (Gy_green * Gy_green)));
            // Compute the gradient magnitude for the blue channel
            int gradient_magnitude_blue = round(sqrt((Gx_blue * Gx_blue) + (Gy_blue * Gy_blue)));

            // Cap the gradient magnitude to 255
            // Set the red channel of the current pixel to the gradient magnitude
            temp[i][j].rgbtRed = gradient_magnitude_red > 255 ? 255 : gradient_magnitude_red;
            // Cap the gradient magnitude to 255
            // Set the green channel of the current pixel to the gradient magnitude
            temp[i][j].rgbtGreen = gradient_magnitude_green > 255 ? 255 : gradient_magnitude_green;
            // Cap the gradient magnitude to 255
            // Set the blue channel of the current pixel to the gradient magnitude
            temp[i][j].rgbtBlue = gradient_magnitude_blue > 255 ? 255 : gradient_magnitude_blue;
        }
    }

    // Copy values from temp array back to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}