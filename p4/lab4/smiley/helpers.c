#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int ir = 0; ir < height; ir++)
    {
        for (int jc = 0; jc < width; jc++)
        {
            if (image[ir][jc].rgbtBlue == 0 && image[ir][jc].rgbtGreen == 0 && image[ir][jc].rgbtRed == 0)
            {
                image[ir][jc].rgbtBlue = 22;
                image[ir][jc].rgbtGreen = 86;
                image[ir][jc].rgbtRed = 91;
            }
        }
    }
}
