#include "helpers.h"
#include <math.h>

int valueSaturation(float n)
{
    if( n > 255 )
    {
        return 255;
    }
    else{
        return round(n);
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0 ; j < width; j++)
        {
            int media = round((image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtBlue = media;
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
            int originalRed = image[i][j].rgbtRed, originalGreen = image[i][j].rgbtGreen, originalBlue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            image[i][j].rgbtRed = valueSaturation(sepiaRed);
            image[i][j].rgbtGreen = valueSaturation(sepiaGreen);
            image[i][j].rgbtBlue = valueSaturation(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            int auxRed = image[i][j].rgbtRed, auxBlue = image[i][j].rgbtBlue, auxGreen = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][width-1-j].rgbtRed = auxRed;

            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][width-1-j].rgbtGreen = auxGreen;

            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][width-1-j].rgbtBlue = auxBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int auxHeight = height + 2 , auxWidth = width + 2;
    RGBTRIPLE imageAux[auxHeight][auxWidth];

    for(int i = 0; i<auxHeight; i++)
    {
        for(int j = 0; j< auxWidth; j++)
        {
            if( i == 0 || i == auxHeight - 1 || j == 0 || j == auxWidth - 1)
            {
                imageAux[i][j].rgbtRed = 0;
                imageAux[i][j].rgbtGreen = 0;
                imageAux[i][j].rgbtBlue = 0;
            }
            else
            {
                imageAux[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
                imageAux[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                imageAux[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            }
        }
    }

    for(int i = 1; i< auxHeight - 1; i++)
    {
        for(int j = 1 ; j < auxWidth - 1; j++)
        {
            int somaRed = imageAux[i-1][j-1].rgbtRed + imageAux[i-1][j].rgbtRed + imageAux[i-1][j+1].rgbtRed + imageAux[i][j-1].rgbtRed + imageAux[i][j].rgbtRed + imageAux[i][j+1].rgbtRed + imageAux[i+1][j-1].rgbtRed + imageAux[i+1][j].rgbtRed + imageAux[i+1][j+1].rgbtRed;
            int somaGreen = imageAux[i-1][j-1].rgbtGreen + imageAux[i-1][j].rgbtGreen + imageAux[i-1][j+1].rgbtGreen + imageAux[i][j-1].rgbtGreen + imageAux[i][j].rgbtGreen + imageAux[i][j+1].rgbtGreen + imageAux[i+1][j-1].rgbtGreen + imageAux[i+1][j].rgbtGreen + imageAux[i+1][j+1].rgbtGreen;
            int somaBlue = imageAux[i-1][j-1].rgbtBlue + imageAux[i-1][j].rgbtBlue + imageAux[i-1][j+1].rgbtBlue + imageAux[i][j-1].rgbtBlue + imageAux[i][j].rgbtBlue + imageAux[i][j+1].rgbtBlue + imageAux[i+1][j-1].rgbtBlue + imageAux[i+1][j].rgbtBlue + imageAux[i+1][j+1].rgbtBlue;
            int count = 9;

            if((i == 1 && (j != 1 && j != auxWidth - 2)) || (i == auxHeight - 2 && (j != 1 && j != auxWidth - 2)) || (j == 1 && (i != 1 && i != auxHeight - 2)) || (j == auxWidth - 2 && (i != 1 && i != auxHeight - 2)))
            {
                count -= 3;
            }
            else if((i == 1 && (j == 1 || j == auxWidth - 2)) || (i == auxHeight - 2 && (j == 1 || j == auxWidth - 2)))
            {
                count -= 5;
            }

            int mediaRed = somaRed / count;
            int mediaGreen = somaGreen / count;
            int mediaBlue = somaBlue / count;

            if(i > 0 && i < auxHeight - 1 && j > 0 && j < auxWidth - 1)
            {
                image[i-1][j-1].rgbtRed = mediaRed;
                image[i-1][j-1].rgbtGreen = mediaGreen;
                image[i-1][j-1].rgbtBlue = mediaBlue;
            }
        }
    }
    return;
}