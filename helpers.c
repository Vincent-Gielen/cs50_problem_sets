#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            int sum = blue + green + red;

            int average = round(sum / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            int newBlue = round((red * .272) + (green * .534) + (blue * .131));
            if (newBlue > 255)
                newBlue = 255;
            int newGreen = round((red * .349) + (green * .686) + (blue * .168));
            if (newGreen > 255)
                newGreen = 255;
            int newRed = round((red * .393) + (green * .769) + (blue * .189));
            if (newRed > 255)
                newRed = 255;

            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
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
            int blue1 = image[i][j].rgbtBlue;
            int green1 = image[i][j].rgbtGreen;
            int red1 = image[i][j].rgbtRed;

            int newArray = width - j - 1;

            image[i][j].rgbtBlue = image[i][newArray].rgbtBlue;
            image[i][j].rgbtGreen = image[i][newArray].rgbtGreen;
            image[i][j].rgbtRed = image[i][newArray].rgbtRed;

            image[i][newArray].rgbtBlue = blue1;
            image[i][newArray].rgbtGreen = green1;
            image[i][newArray].rgbtRed = red1;
        }
    }
    return;
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

            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            double amount = 0.0;

            for (int row = i - 1; row <= i + 1; row++)
            {
                if (row < height && row >= 0)
                {
                    for (int array = j - 1; array <= j + 1; array++)
                    {
                        if (array < width && array >= 0)
                        {
                            sumBlue += copy[row][array].rgbtBlue;
                            sumGreen += copy[row][array].rgbtGreen;
                            sumRed += copy[row][array].rgbtRed;
                            amount++;
                        }
                    }
                }
            }

            int averageBlue = round(sumBlue / amount);
            int averageGreen = round(sumGreen / amount);
            int averageRed = round(sumRed / amount);

            image[i][j].rgbtBlue = averageBlue;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtRed = averageRed;
        }
    }

    return;
}
