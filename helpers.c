#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            int media = (image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue)/3;
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
    for(int i = 0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            if(sepiaRed>255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if(sepiaGreen>255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if(sepiaBlue>255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j = 0;j < width/2;j++)
        {
            int auxRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width-j].rgbtRed;
            image[i][width-j].rgbtRed = auxRed;

            int auxGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
            image[i][width-j].rgbtGreen = auxGreen;

            int auxBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
            image[i][width-j].rgbtBlue = auxBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageAux[height][width];
    for (int i = 0;i < height; i++ ){
        for (int a = 0; a < width ; a++){
            int mediaRed;
            int mediaGreen;
            int mediaBlue;

            if(a==0 && i == 0)
            {
                mediaRed = (image[i][a].rgbtRed + image[i][a+1].rgbtRed  + image[i+1][a].rgbtRed  + image[i+1][a+1].rgbtRed)/4 ;
                mediaGreen = (image[i][a].rgbtGreen + image[i][a+1].rgbtGreen  + image[i+1][a].rgbtGreen  + image[i+1][a+1].rgbtGreen)/4 ;
                mediaBlue = (image[i][a].rgbtBlue + image[i][a+1].rgbtBlue  + image[i+1][a].rgbtBlue  + image[1+i][1+a].rgbtBlue)/4 ;
            }
            else if(a == 0 && i == height - 1)
            {
                mediaRed = (image[i][a].rgbtRed + image[i][a+1].rgbtRed  + image[i-1][a].rgbtRed  + image[i-1][a+1].rgbtRed)/4 ;
                mediaGreen = (image[i][a].rgbtGreen + image[i][a+1].rgbtGreen  + image[i-1][a].rgbtGreen  + image[i-1][a+1].rgbtGreen)/4 ;
                mediaBlue = (image[i][a].rgbtBlue + image[i][a+1].rgbtBlue  + image[i-1][a].rgbtBlue  + image[i-1][a+1].rgbtBlue)/4 ;
            }
            else if(a == width - 1 && i == 0)
            {
                mediaRed = (image[i][a].rgbtRed + image[i][a-1].rgbtRed  + image[i+1][a].rgbtRed  + image[i+1][a-1].rgbtRed)/4 ;
                mediaGreen = (image[i][a].rgbtGreen + image[i][a-1].rgbtGreen  + image[i+1][a].rgbtGreen  + image[i+1][a-1].rgbtGreen)/4 ;
                mediaBlue = (image[i][a].rgbtBlue + image[i][a-1].rgbtBlue  + image[i+1][a].rgbtBlue  + image[i+1][a-1].rgbtBlue)/4 ;
            }
            else if(a == width - 1 && i == height - 1)
            {
                mediaRed = (image[i][a].rgbtRed + image[i][a-1].rgbtRed  + image[i-1][a].rgbtRed  + image[i-1][a-1].rgbtRed)/4 ;
                mediaGreen = (image[i][a].rgbtGreen + image[i][a-1].rgbtGreen  + image[i-1][a].rgbtGreen  + image[i-1][a-1].rgbtGreen)/4 ;
                mediaBlue = (image[i][a].rgbtBlue + image[i][a-1].rgbtBlue  + image[i-1][a].rgbtBlue  + image[i-1][a-1].rgbtBlue)/4 ;
            }

            else if(a == 0 && i != 0 && i != height - 1)
            {
                mediaRed = (image[i-1][a].rgbtRed+image[i-1][a+1].rgbtRed+image[i][a].rgbtRed+image[i][a+1].rgbtRed+image[i+1][a].rgbtRed+image[i+1][a+1].rgbtRed)/6;
                mediaGreen = (image[i-1][a].rgbtGreen+image[i-1][a+1].rgbtGreen+image[i][a].rgbtGreen+image[i][a+1].rgbtGreen+image[i+1][a].rgbtGreen+image[i+1][a+1].rgbtGreen)/6;
                mediaBlue = (image[i-1][a].rgbtBlue+image[i-1][a+1].rgbtBlue+image[i][a].rgbtBlue+image[i][a+1].rgbtBlue+image[i+1][a].rgbtBlue+image[i+1][a+1].rgbtBlue)/6;
            }
            else if(a == width - 1 && i != 0 && i != height - 1)
            {
                mediaRed = (image[i-1][a-1].rgbtRed+image[i-1][a].rgbtRed+image[i][a-1].rgbtRed+image[i][a].rgbtRed+image[i+1][a-1].rgbtRed+image[i+1][a].rgbtRed)/6;
                mediaGreen = (image[i-1][a-1].rgbtGreen+image[i-1][a].rgbtGreen+image[i][a-1].rgbtGreen+image[i][a].rgbtGreen+image[i+1][a-1].rgbtGreen+image[i+1][a].rgbtGreen)/6;
                mediaBlue = (image[i-1][a-1].rgbtBlue+image[i-1][a].rgbtBlue+image[i][a-1].rgbtBlue+image[i][a].rgbtBlue+image[i+1][a-1].rgbtBlue+image[i+1][a].rgbtBlue)/6;
            }
            else if(i == 0 && a != 0 && a != width - 1)
            {
                mediaRed = (image[i][a-1].rgbtRed+image[i][a].rgbtRed+image[i][a+1].rgbtRed+image[i+1][a-1].rgbtRed+image[i+1][a].rgbtRed+image[i+1][a+1].rgbtRed)/6;
                mediaGreen = (image[i][a-1].rgbtGreen+image[i][a].rgbtGreen+image[i][a+1].rgbtGreen+image[i+1][a-1].rgbtGreen+image[i+1][a].rgbtGreen+image[i+1][a+1].rgbtGreen)/6;
                mediaBlue = (image[i][a-1].rgbtBlue+image[i][a].rgbtBlue+image[i][a+1].rgbtBlue+image[i+1][a-1].rgbtBlue+image[i+1][a].rgbtBlue+image[i+1][a+1].rgbtBlue)/6;
            }
            else if(i == height - 1  && a != 0 && a != width - 1)
            {
                mediaRed = (image[i-1][a-1].rgbtRed+image[i-1][a].rgbtRed+image[i-1][a+1].rgbtRed+image[i][a-1].rgbtRed+image[i][a].rgbtRed+image[i][a+1].rgbtRed)/6;
                mediaGreen = (image[i-1][a-1].rgbtGreen+image[i-1][a].rgbtGreen+image[i-1][a+1].rgbtGreen+image[i][a-1].rgbtGreen+image[i][a].rgbtGreen+image[i][a+1].rgbtGreen)/6;
                mediaBlue = (image[i-1][a-1].rgbtBlue+image[i-1][a].rgbtBlue+image[i-1][a+1].rgbtBlue+image[i][a-1].rgbtBlue+image[i][a].rgbtBlue+image[i][a+1].rgbtBlue)/6;
            }
            else
            {
                mediaRed = (image[i-1][a-1].rgbtRed+image[i-1][a].rgbtRed+image[i-1][a+1].rgbtRed+image[i][a-1].rgbtRed+image[i][a].rgbtRed+image[i][a+1].rgbtRed+image[i+1][a-1].rgbtRed+image[i+1][a].rgbtRed+image[i+1][a+1].rgbtRed)/9;
                mediaGreen = (image[i-1][a-1].rgbtGreen+image[i-1][a].rgbtGreen+image[i-1][a+1].rgbtGreen+image[i][a-1].rgbtGreen+image[i][a].rgbtGreen+image[i][a+1].rgbtGreen+image[i+1][a-1].rgbtGreen+image[i+1][a].rgbtGreen+image[i+1][a+1].rgbtGreen)/9;
                mediaBlue = (image[i-1][a-1].rgbtBlue+image[i-1][a].rgbtBlue+image[i-1][a+1].rgbtBlue+image[i][a-1].rgbtBlue+image[i][a].rgbtBlue+image[i][a+1].rgbtBlue+image[i+1][a-1].rgbtBlue+image[i+1][a].rgbtBlue+image[i+1][a+1].rgbtBlue)/9;
            }

            imageAux[i][a].rgbtRed = mediaRed;
            imageAux[i][a].rgbtGreen = mediaGreen;
            imageAux[i][a].rgbtBlue = mediaBlue;

        }
    }
    for(int i = 0 ; i<height; i++)
    {
        for(int a = 0 ; a< width; a++)
        {
            image[i][a].rgbtRed = imageAux[i][a].rgbtRed;
            image[i][a].rgbtGreen = imageAux[i][a].rgbtGreen;
            image[i][a].rgbtBlue = imageAux[i][a].rgbtBlue;
        }
    }
    return;
}
