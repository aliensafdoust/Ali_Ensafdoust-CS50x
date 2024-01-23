#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int num1 = 0; num1 < height; num1++)
    {
        for (int num2 = 0; num2 < width; num2++)
        {
            int tot = round((image[num1][num2].rgbtBlue + image[num1][num2].rgbtGreen + image[num1][num2].rgbtRed) / 3.0);

            image[num1][num2].rgbtBlue = tot;
            image[num1][num2].rgbtGreen = tot;
            image[num1][num2].rgbtRed = tot;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int n1 = 0; n1 < height; n1++)
    {
        for (int n2 = 0; n2 < width; n2++)
        {
            int sepiaRed = round(0.393 * image[n1][n2].rgbtRed + 0.769 * image[n1][n2].rgbtGreen + 0.189 * image[n1][n2].rgbtBlue);
            int sepiaGreen = round(0.349 * image[n1][n2].rgbtRed + 0.686 * image[n1][n2].rgbtGreen + 0.168 * image[n1][n2].rgbtBlue);
            int sepiaBlue = round(0.272 * image[n1][n2].rgbtRed + 0.534 * image[n1][n2].rgbtGreen + 0.131 * image[n1][n2].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[n1][n2].rgbtBlue = sepiaBlue;
            image[n1][n2].rgbtGreen = sepiaGreen;
            image[n1][n2].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE n3[width / 2];

    for (int n1 = 0; n1 < height; n1++)
    {
        for (int n2 = 0; n2 < width / 2; n2++)
        {
            n3[n2] = image[n1][n2];
            image[n1][n2] = image[n1][width - n2 - 1];
            image[n1][width - n2 - 1] = n3[n2];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copping[height][width];

    for (int ch = 0; ch < height; ch++)
    {
        for (int cw = 0; cw < width; cw++)
        {
            copping[ch][cw] = image[ch][cw];
        }
    }

    for (int h1 = 0; h1 < height; h1++)
    {
        for (int w1 = 0; w1 < width; w1++)
        {
            float rd = 0, bue = 0, geen = 0;
            int count = 0;

            for (int t1 = -1; t1 < 2; t1++)
            {
                for (int t2 = -1; t2 < 2; t2++)
                {
                    if (h1 + t1 < 0 || h1 + t1 >= height || w1 + t2 < 0 || w1 + t2 >= width)
                    {
                        continue;
                    }
                    else
                    {
                        rd += copping[h1 + t1][w1 + t2].rgbtRed;
                        bue += copping[h1 + t1][w1 + t2].rgbtBlue;
                        geen += copping[h1 + t1][w1 + t2].rgbtGreen;
                        count += 1;
                    }
                }
            }
            image[h1][w1].rgbtRed = (int) round(rd / count);
            image[h1][w1].rgbtGreen = (int) round(geen / count);
            image[h1][w1].rgbtBlue = (int) round(bue / count);
        }
    }
}
