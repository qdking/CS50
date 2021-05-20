#include "helpers.h"
#include "cs50.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

/*typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // Outer loop: for each row
    {
        for (int j = 0; j < width; j++) // Inner loop: for each column (going in the > direction)
        {
            // /3 is a float number division formula
            int average_colours = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = average_colours;
            image[i][j].rgbtGreen = average_colours;
            image[i][j].rgbtRed = average_colours;
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

            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Red
            if (round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            }

            // Green
            if (round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            }

            // Blue
            if (round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temporary_red;
    int temporary_green;
    int temporary_blue;

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            temporary_red = image[i][j].rgbtRed;
            temporary_green = image[i][j].rgbtGreen;
            temporary_blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temporary_red;
            image[i][width - j - 1].rgbtGreen = temporary_green;
            image[i][width - j - 1].rgbtBlue = temporary_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int red_sum[height][width];
    int green_sum[height][width];
    int blue_sum[height][width];
    int number_of_cells[height][width];

    // Totalling the sum of values and calculating the average:
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // image[][] cannot be used directly in this += loop because the consequent values will be referenced wrongly and change. Use rgb_sum instead.
            // number_of_cells and rgb_sum should be turnedd to zero because their initial values could be memory garbage values.
            number_of_cells[i][j] = 0;
            red_sum[i][j] = 0;
            green_sum[i][j] = 0;
            blue_sum[i][j] = 0;

            for (int row_search = - 1 ; row_search < 2 ; row_search++) // Map out and search the available neighbouring cells/pixels
            {
                for (int column_search = - 1 ; column_search < 2 ; column_search++)
                {
                    if ((i + row_search >= 0) && (i + row_search <= height - 1) && (j + column_search >= 0)
                        && (j + column_search <= width - 1)) // Rejects cells that are out of range.
                    {
                        red_sum[i][j] += image[i + row_search][j + column_search].rgbtRed;
                        green_sum[i][j] += image[i + row_search][j + column_search].rgbtGreen;
                        blue_sum[i][j] += image[i + row_search][j + column_search].rgbtBlue;
                        number_of_cells[i][j]++;
                    }
                }
            }
        }
    }

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            // Calculating the average values per 2D array index in the loop
            image[i][j].rgbtRed = round((float)red_sum[i][j] / (float)number_of_cells[i][j]);
            image[i][j].rgbtGreen = round((float)green_sum[i][j] / (float)number_of_cells[i][j]);
            image[i][j].rgbtBlue = round((float)blue_sum[i][j] / (float)number_of_cells[i][j]);
        }
    }

    return;
}
