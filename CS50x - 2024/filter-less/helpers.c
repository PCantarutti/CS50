#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop em todos os pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Faz a média de vermelho, verde e azul
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int media = round((r + g + b) / 3.0);

            // Atualiza os valores dos pixels
            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Compute sepia values
            float sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            float sepiaGreen =
                round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            float sepiaBlue =
                round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

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

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - j - 1];

            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred_image[height][width];

    for (int col = 0; col < height; col++)
    {
        for (int row = 0; row < width; row++)
        {

            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;
            double divider = 0;

            for (int y = col - 1; y <= col + 1; y++)
            {
                for (int x = row - 1; x <= row + 1; x++)
                {
                    // If a pixel is within a valid range
                    if ((y >= 0 && y < height) && (x >= 0 && x < width))
                    {
                        sumRed = image[y][x].rgbtRed + sumRed;
                        sumGreen = image[y][x].rgbtGreen + sumGreen;
                        sumBlue = image[y][x].rgbtBlue + sumBlue;
                        divider++;
                    }
                }
            }

            blurred_image[col][row].rgbtRed = round((sumRed / divider));
            blurred_image[col][row].rgbtGreen = round((sumGreen / divider));
            blurred_image[col][row].rgbtBlue = round((sumBlue / divider));
        }
    }

    // Overwrite the orinal image with the blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred_image[i][j].rgbtBlue;
        }
    }

    return;
}
