#include "helpers.h"
#include <math.h>

RGBTRIPLE calculate_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

RGBTRIPLE calculate_Gx_Gy(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
int sobel(float gx, float gy);
float gxblue(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
float gyblue(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
float gxgreen(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
float gygreen(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
float gxred(int row, int column, int height, int width, RGBTRIPLE image[height][width]);
float gyred(int row, int column, int height, int width, RGBTRIPLE image[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through the rows
    for (int i = 0; i < height; i++)
    {
        // iterate through the pixels in each row
        for (int j = 0; j < width; j++)
        {
            // change rgb values to avg of r, b, and g values for grayscale effect
            int pixel_avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = pixel_avg;
            image[i][j].rgbtGreen = pixel_avg;
            image[i][j].rgbtRed = pixel_avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE placeholder[height][width];

    for (int i = 0; i < height; i++)
    {
        // put reversed image into a placeholder array
        for (int j = 0, k = width - 1; j < width; j++, k--)
        {
            placeholder[i][j] = image[i][k];
        }
        // put placeholder image into actual image
        for (int m = 0; m < width; m++)
        {
            image[i][m] = placeholder[i][m];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE placeholder[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            placeholder[i][j] = calculate_blur(i, j, height, width, image);
        }
    }

    // copy the placeholder image into the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = placeholder[i][j];
        }
    }
    return;
}

RGBTRIPLE calculate_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    float pixel_number;
    int sum_blue, sum_red, sum_green;
    RGBTRIPLE pixel;
    if (i == 0)
    {
        if (j == 0) // Top Left Corner
        {
            pixel_number = 4.00;
            sum_blue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            sum_red = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
            sum_green = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
        }
        else if (j == width - 1) // Top Right Corner
        {
            pixel_number = 4.00;
            sum_blue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
            sum_red = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed;
            sum_green = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
        }
        else // Top Edge
        {
            pixel_number = 6.00;
            sum_blue = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
            sum_blue += image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            sum_red = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
            sum_red += image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
            sum_green = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
            sum_green += image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
        }
    }
    else if (i == height - 1)
    {
        if (j == 0) // Bottom Left Corner
        {
            pixel_number = 4.00;
            sum_blue = image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
            sum_red = image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
            sum_green = image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
        }
        else if (j == width - 1) // Bottom Right Corner
        {
            pixel_number = 4.00;
            sum_blue = image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue;
            sum_red = image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed;
            sum_green = image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen;
        }
        else // Bottom Edge
        {
            pixel_number = 6.00;
            sum_blue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
            sum_blue += image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
            sum_red = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
            sum_red += image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
            sum_green = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
            sum_green += image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
        }
    }
    else if (j == 0) // Left Edge Uncornered
    {
        pixel_number = 6.00;
        sum_blue = image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue;
        sum_blue += image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
        sum_red = image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed;
        sum_red += image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
        sum_green = image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen;
        sum_green += image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
    }
    else if (j == width - 1) // Right Edge Uncornered
    {
        pixel_number = 6.00;
        sum_blue = image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue;
        sum_blue += image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue;
        sum_red = image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed;
        sum_red += image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed;
        sum_green = image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen;
        sum_green += image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen;
    }
    else // All Center Pixels
    {
        pixel_number = 9.00;
        sum_blue = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
        sum_blue += image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue;
        sum_blue += image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
        sum_red = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
        sum_red += image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed;
        sum_red += image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
        sum_green = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
        sum_green += image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen;
        sum_green += image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
    }

    pixel.rgbtBlue = round(sum_blue / pixel_number);
    pixel.rgbtGreen = round(sum_green / pixel_number);
    pixel.rgbtRed = round(sum_red / pixel_number);

    return pixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE placeholder[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            placeholder[i][j] = calculate_Gx_Gy(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = placeholder[i][j];
        }
    }
    return;
}


RGBTRIPLE calculate_Gx_Gy(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    pixel.rgbtBlue = sobel(gxblue(row, column, height, width, image), gyblue(row, column, height, width, image));
    pixel.rgbtGreen = sobel(gxgreen(row, column, height, width, image), gygreen(row, column, height, width, image));
    pixel.rgbtRed = sobel(gxred(row, column, height, width, image), gyred(row, column, height, width, image));
    return pixel;
}

int sobel(float gx, float gy)
{
    int final = round(sqrt(gx * gx + gy * gy));
    if (final > 255)
    {
        final = 255;
    }
    return final;
}

float gxblue(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_right, center_left, center_right, bottom_left, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_right = 0;

        if (column == 0)
        {
            center_left = 0;
            bottom_left = 0;
            center_right = 2 * image[row][column + 1].rgbtBlue;
            bottom_right = image[row + 1][column + 1].rgbtBlue;
        }
        else if (column == width - 1)
        {
            center_right = 0;
            bottom_right = 0;
            center_left = -2 * image[row][column - 1].rgbtBlue;
            bottom_left = -1 * image[row + 1][column - 1].rgbtBlue;
        }
        else
        {
            center_left = -2 * image[row][column - 1].rgbtBlue;
            center_right = 2 * image[row][column + 1].rgbtBlue;
            bottom_left = -1 * image[row + 1][column - 1].rgbtBlue;
            bottom_right = image[row + 1][column + 1].rgbtBlue;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_left = 0;

        if (column == 0)
        {
            top_left = 0;
            center_left = 0;
            top_right = image[row - 1][column + 1].rgbtBlue;
            center_right = 2 * image[row][column + 1].rgbtBlue;
        }
        else if (column == width - 1)
        {
            top_right = 0;
            center_right = 0;
            top_left = -1 * image[row - 1][column - 1].rgbtBlue;
            center_left = -2 * image[row][column - 1].rgbtBlue;
        }
        else
        {
            top_right = image[row - 1][column + 1].rgbtBlue;
            center_right = 2 * image[row][column + 1].rgbtBlue;
            top_left = -1 * image[row - 1][column - 1].rgbtBlue;
            center_left = -2 * image[row][column - 1].rgbtBlue;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        center_left = 0;
        bottom_left = 0;
        top_right = image[row - 1][column + 1].rgbtBlue;
        center_right = 2 * image[row][column + 1].rgbtBlue;
        bottom_right = image[row + 1][column + 1].rgbtBlue;
    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        center_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtBlue;
        center_left = -2 * image[row][column - 1].rgbtBlue;
        bottom_left = -1 * image[row + 1][column -1].rgbtBlue;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtBlue;
        center_left = -2 * image[row][column - 1].rgbtBlue;
        bottom_left = -1 * image[row + 1][column -1].rgbtBlue;
        top_right = image[row - 1][column + 1].rgbtBlue;
        center_right = 2 * image[row][column + 1].rgbtBlue;
        bottom_right = image[row + 1][column + 1].rgbtBlue;
    }

    return top_left + top_right + center_left + center_right + bottom_left + bottom_right;
}

float gyblue(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_center, top_right, bottom_left, bottom_center, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_center = 0;
        top_right = 0;

        if (column == 0) // Top Left Corner
        {
            bottom_left = 0;
            bottom_center = 2 * image[row + 1][column].rgbtBlue;
            bottom_right = image[row + 1][column + 1].rgbtBlue;
        }
        else if (column == width - 1) // Top Right Corner
        {
            bottom_right = 0;
            bottom_left = image[row + 1][column - 1].rgbtBlue;
            bottom_center = 2 * image[row + 1][column].rgbtBlue;
        }
        else // Top Edge Uncornered
        {
            bottom_left = image[row + 1][column - 1].rgbtBlue;
            bottom_center = 2 * image[row + 1][column].rgbtBlue;
            bottom_right = image[row + 1][column + 1].rgbtBlue;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_center = 0;
        bottom_left = 0;

        if (column == 0) // Bottom Left Corner
        {
            top_left = 0;
            top_center = -2 * image[row - 1][column].rgbtBlue;
            top_right = -1 * image[row - 1][column + 1].rgbtBlue;
        }
        else if (column == width - 1) // Bottom Right Corner
        {
            top_right = 0;
            top_center = -2 * image[row - 1][column].rgbtBlue;
            top_left = -1 * image[row - 1][column - 1].rgbtBlue;
        }
        else // Bottom Edge Uncornered
        {
            top_left = -1 * image[row - 1][column - 1].rgbtBlue;
            top_center = -2 * image[row - 1][column].rgbtBlue;
            top_right = -1 * image[row - 1][column + 1].rgbtBlue;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        bottom_left = 0;
        top_center = -2 * image[row - 1][column].rgbtBlue;
        top_right = -1 * image[row - 1][column + 1].rgbtBlue;
        bottom_center = 2 * image[row + 1][column].rgbtBlue;
        bottom_right = image[row + 1][column + 1].rgbtBlue;

    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtBlue;
        top_center = -2 * image[row - 1][column].rgbtBlue;
        bottom_left = image[row + 1][column - 1].rgbtBlue;
        bottom_center = 2 * image[row + 1][column].rgbtBlue;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtBlue;
        top_center = -2 * image[row - 1][column].rgbtBlue;
        top_right = -1 * image[row - 1][column + 1].rgbtBlue;
        bottom_left = image[row + 1][column - 1].rgbtBlue;
        bottom_center = 2 * image[row + 1][column].rgbtBlue;
        bottom_right = image[row + 1][column + 1].rgbtBlue;
    }

    return top_left + top_center + top_right + bottom_left + bottom_center + bottom_right;
}

float gxgreen(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_right, center_left, center_right, bottom_left, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_right = 0;

        if (column == 0)
        {
            center_left = 0;
            bottom_left = 0;
            center_right = 2 * image[row][column + 1].rgbtGreen;
            bottom_right = image[row + 1][column + 1].rgbtGreen;
        }
        else if (column == width - 1)
        {
            center_right = 0;
            bottom_right = 0;
            center_left = -2 * image[row][column - 1].rgbtGreen;
            bottom_left = -1 * image[row + 1][column - 1].rgbtGreen;
        }
        else
        {
            center_left = -2 * image[row][column - 1].rgbtGreen;
            center_right = 2 * image[row][column + 1].rgbtGreen;
            bottom_left = -1 * image[row + 1][column - 1].rgbtGreen;
            bottom_right = image[row + 1][column + 1].rgbtGreen;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_left = 0;

        if (column == 0)
        {
            top_left = 0;
            center_left = 0;
            top_right = image[row - 1][column + 1].rgbtGreen;
            center_right = 2 * image[row][column + 1].rgbtGreen;
        }
        else if (column == width - 1)
        {
            top_right = 0;
            center_right = 0;
            top_left = -1 * image[row - 1][column - 1].rgbtGreen;
            center_left = -2 * image[row][column - 1].rgbtGreen;
        }
        else
        {
            top_right = image[row - 1][column + 1].rgbtGreen;
            center_right = 2 * image[row][column + 1].rgbtGreen;
            top_left = -1 * image[row - 1][column - 1].rgbtGreen;
            center_left = -2 * image[row][column - 1].rgbtGreen;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        center_left = 0;
        bottom_left = 0;
        top_right = image[row - 1][column + 1].rgbtGreen;
        center_right = 2 * image[row][column + 1].rgbtGreen;
        bottom_right = image[row + 1][column + 1].rgbtGreen;
    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        center_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtGreen;
        center_left = -2 * image[row][column - 1].rgbtGreen;
        bottom_left = -1 * image[row + 1][column -1].rgbtGreen;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtGreen;
        center_left = -2 * image[row][column - 1].rgbtGreen;
        bottom_left = -1 * image[row + 1][column -1].rgbtGreen;
        top_right = image[row - 1][column + 1].rgbtGreen;
        center_right = 2 * image[row][column + 1].rgbtGreen;
        bottom_right = image[row + 1][column + 1].rgbtGreen;
    }

    return top_left + top_right + center_left + center_right + bottom_left + bottom_right;
}

float gygreen(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_center, top_right, bottom_left, bottom_center, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_center = 0;
        top_right = 0;

        if (column == 0) // Top Left Corner
        {
            bottom_left = 0;
            bottom_center = 2 * image[row + 1][column].rgbtGreen;
            bottom_right = image[row + 1][column + 1].rgbtGreen;
        }
        else if (column == width - 1) // Top Right Corner
        {
            bottom_right = 0;
            bottom_left = image[row + 1][column - 1].rgbtGreen;
            bottom_center = 2 * image[row + 1][column].rgbtGreen;
        }
        else // Top Edge Uncornered
        {
            bottom_left = image[row + 1][column - 1].rgbtGreen;
            bottom_center = 2 * image[row + 1][column].rgbtGreen;
            bottom_right = image[row + 1][column + 1].rgbtGreen;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_center = 0;
        bottom_left = 0;

        if (column == 0) // Bottom Left Corner
        {
            top_left = 0;
            top_center = -2 * image[row - 1][column].rgbtGreen;
            top_right = -1 * image[row - 1][column + 1].rgbtGreen;
        }
        else if (column == width - 1) // Bottom Right Corner
        {
            top_right = 0;
            top_center = -2 * image[row - 1][column].rgbtGreen;
            top_left = -1 * image[row - 1][column - 1].rgbtGreen;
        }
        else // Bottom Edge Uncornered
        {
            top_left = -1 * image[row - 1][column - 1].rgbtGreen;
            top_center = -2 * image[row - 1][column].rgbtGreen;
            top_right = -1 * image[row - 1][column + 1].rgbtGreen;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        bottom_left = 0;
        top_center = -2 * image[row - 1][column].rgbtGreen;
        top_right = -1 * image[row - 1][column + 1].rgbtGreen;
        bottom_center = 2 * image[row + 1][column].rgbtGreen;
        bottom_right = image[row + 1][column + 1].rgbtGreen;

    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtGreen;
        top_center = -2 * image[row - 1][column].rgbtGreen;
        bottom_left = image[row + 1][column - 1].rgbtGreen;
        bottom_center = 2 * image[row + 1][column].rgbtGreen;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtGreen;
        top_center = -2 * image[row - 1][column].rgbtGreen;
        top_right = -1 * image[row - 1][column + 1].rgbtGreen;
        bottom_left = image[row + 1][column - 1].rgbtGreen;
        bottom_center = 2 * image[row + 1][column].rgbtGreen;
        bottom_right = image[row + 1][column + 1].rgbtGreen;
    }

    return top_left + top_center + top_right + bottom_left + bottom_center + bottom_right;
}

float gxred(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_right, center_left, center_right, bottom_left, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_right = 0;

        if (column == 0)
        {
            center_left = 0;
            bottom_left = 0;
            center_right = 2 * image[row][column + 1].rgbtRed;
            bottom_right = image[row + 1][column + 1].rgbtRed;
        }
        else if (column == width - 1)
        {
            center_right = 0;
            bottom_right = 0;
            center_left = -2 * image[row][column - 1].rgbtRed;
            bottom_left = -1 * image[row + 1][column - 1].rgbtRed;
        }
        else
        {
            center_left = -2 * image[row][column - 1].rgbtRed;
            center_right = 2 * image[row][column + 1].rgbtRed;
            bottom_left = -1 * image[row + 1][column - 1].rgbtRed;
            bottom_right = image[row + 1][column + 1].rgbtRed;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_left = 0;

        if (column == 0)
        {
            top_left = 0;
            center_left = 0;
            top_right = image[row - 1][column + 1].rgbtRed;
            center_right = 2 * image[row][column + 1].rgbtRed;
        }
        else if (column == width - 1)
        {
            top_right = 0;
            center_right = 0;
            top_left = -1 * image[row - 1][column - 1].rgbtRed;
            center_left = -2 * image[row][column - 1].rgbtRed;
        }
        else
        {
            top_right = image[row - 1][column + 1].rgbtRed;
            center_right = 2 * image[row][column + 1].rgbtRed;
            top_left = -1 * image[row - 1][column - 1].rgbtRed;
            center_left = -2 * image[row][column - 1].rgbtRed;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        center_left = 0;
        bottom_left = 0;
        top_right = image[row - 1][column + 1].rgbtRed;
        center_right = 2 * image[row][column + 1].rgbtRed;
        bottom_right = image[row + 1][column + 1].rgbtRed;
    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        center_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtRed;
        center_left = -2 * image[row][column - 1].rgbtRed;
        bottom_left = -1 * image[row + 1][column -1].rgbtRed;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtRed;
        center_left = -2 * image[row][column - 1].rgbtRed;
        bottom_left = -1 * image[row + 1][column -1].rgbtRed;
        top_right = image[row - 1][column + 1].rgbtRed;
        center_right = 2 * image[row][column + 1].rgbtRed;
        bottom_right = image[row + 1][column + 1].rgbtRed;
    }

    return top_left + top_right + center_left + center_right + bottom_left + bottom_right;
}

float gyred(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    float top_left, top_center, top_right, bottom_left, bottom_center, bottom_right;

    if (row == 0) // Top Edge
    {
        top_left = 0;
        top_center = 0;
        top_right = 0;

        if (column == 0) // Top Left Corner
        {
            bottom_left = 0;
            bottom_center = 2 * image[row + 1][column].rgbtRed;
            bottom_right = image[row + 1][column + 1].rgbtRed;
        }
        else if (column == width - 1) // Top Right Corner
        {
            bottom_right = 0;
            bottom_left = image[row + 1][column - 1].rgbtRed;
            bottom_center = 2 * image[row + 1][column].rgbtRed;
        }
        else // Top Edge Uncornered
        {
            bottom_left = image[row + 1][column - 1].rgbtRed;
            bottom_center = 2 * image[row + 1][column].rgbtRed;
            bottom_right = image[row + 1][column + 1].rgbtRed;
        }
    }
    else if (row == height - 1) // Bottom Edge
    {
        bottom_right = 0;
        bottom_center = 0;
        bottom_left = 0;

        if (column == 0) // Bottom Left Corner
        {
            top_left = 0;
            top_center = -2 * image[row - 1][column].rgbtRed;
            top_right = -1 * image[row - 1][column + 1].rgbtRed;
        }
        else if (column == width - 1) // Bottom Right Corner
        {
            top_right = 0;
            top_center = -2 * image[row - 1][column].rgbtRed;
            top_left = -1 * image[row - 1][column - 1].rgbtRed;
        }
        else // Bottom Edge Uncornered
        {
            top_left = -1 * image[row - 1][column - 1].rgbtRed;
            top_center = -2 * image[row - 1][column].rgbtRed;
            top_right = -1 * image[row - 1][column + 1].rgbtRed;
        }
    }
    else if (column == 0) // Left Edge
    {
        top_left = 0;
        bottom_left = 0;
        top_center = -2 * image[row - 1][column].rgbtRed;
        top_right = -1 * image[row - 1][column + 1].rgbtRed;
        bottom_center = 2 * image[row + 1][column].rgbtRed;
        bottom_right = image[row + 1][column + 1].rgbtRed;

    }
    else if (column == width - 1) // Right Edge
    {
        top_right = 0;
        bottom_right = 0;
        top_left = -1 * image[row - 1][column - 1].rgbtRed;
        top_center = -2 * image[row - 1][column].rgbtRed;
        bottom_left = image[row + 1][column - 1].rgbtRed;
        bottom_center = 2 * image[row + 1][column].rgbtRed;
    }
    else // All pixels in the center
    {
        top_left = -1 * image[row - 1][column - 1].rgbtRed;
        top_center = -2 * image[row - 1][column].rgbtRed;
        top_right = -1 * image[row - 1][column + 1].rgbtRed;
        bottom_left = image[row + 1][column - 1].rgbtRed;
        bottom_center = 2 * image[row + 1][column].rgbtRed;
        bottom_right = image[row + 1][column + 1].rgbtRed;
    }

    return top_left + top_center + top_right + bottom_left + bottom_center + bottom_right;
}