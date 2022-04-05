#include "helpers.h"
#include <math.h>

int valueSaturation(float n)
{
	if (n > 255)
	{
		return 255;
	}
	else
	{
		return round(n);
	}
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	int media;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			media = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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
	float sepiaRed, sepiaGreen, sepiaBlue;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int originalRed = image[i][j].rgbtRed, originalGreen = image[i][j].rgbtGreen, originalBlue = image[i][j].rgbtBlue;

			sepiaRed = .393 *originalRed + .769 *originalGreen + .189 * originalBlue;
			sepiaGreen = .349 *originalRed + .686 *originalGreen + .168 * originalBlue;
			sepiaBlue = .272 *originalRed + .534 *originalGreen + .131 * originalBlue;

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
		for (int j = 0; j < width / 2; j++)
		{
			int auxRed = image[i][j].rgbtRed, auxBlue = image[i][j].rgbtBlue, auxGreen = image[i][j].rgbtGreen;

			image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
			image[i][width - 1 - j].rgbtRed = auxRed;

			image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
			image[i][width - 1 - j].rgbtGreen = auxGreen;

			image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
			image[i][width - 1 - j].rgbtBlue = auxBlue;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	/*
	Ideia:
	1º -> Fazer uma nova imagem com +2 de width e height, copiando a original e
	    colocando uma borda #000 nas laterais (totalmente preta);
	2º -> Fazer um loop pela nova imagem a partir do pixel height/width = 1 até height/width = total height/width - 1
	    e fazer a media ods pixeis em volta;
	3º -> Se o pixel atual estiver na lateral da imagem o denominador (da media) diminui 3;
	4º -> Se o pixel estiver num dos 4 quantos da imagem o denominador (da media) diminui 5;
	5º -> Copiar o resultado da media para a imagem original translocando -1 de width e heigth;
	obs: denominador assume o valor de 9 (caso geral);
	     auxHeigth e auxWidth sao as propriedades da nova imagem;
	*/
	RGBTRIPLE imageAux[auxHeight][auxWidth];

	int auxHeight = height + 2, auxWidth = width + 2;
	int somaRed, somaGreen, somaBlue;

	for (int i = 0; i < auxHeight; i++)
	{
		for (int j = 0; j < auxWidth; j++)
		{
			if (i == 0 || i == auxHeight - 1 || j == 0 || j == auxWidth - 1)
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

	for (int i = 1; i < auxHeight - 1; i++)
	{
		for (int j = 1; j < auxWidth - 1; j++)
		{
			float denominador = 9.0;
			/*
			Soma a coloração de todos pixels em volta e do elemento central;
			*/
			somaRed = imageAux[i - 1][j - 1].rgbtRed + imageAux[i - 1][j].rgbtRed + imageAux[i - 1][j + 1].rgbtRed + imageAux[i][j - 1].rgbtRed + imageAux[i][j].rgbtRed + imageAux[i][j + 1].rgbtRed + imageAux[i + 1][j - 1].rgbtRed + imageAux[i + 1][j].rgbtRed + imageAux[i + 1][j + 1].rgbtRed;
			somaGreen = imageAux[i - 1][j - 1].rgbtGreen + imageAux[i - 1][j].rgbtGreen + imageAux[i - 1][j + 1].rgbtGreen + imageAux[i][j - 1].rgbtGreen + imageAux[i][j].rgbtGreen + imageAux[i][j + 1].rgbtGreen + imageAux[i + 1][j - 1].rgbtGreen + imageAux[i + 1][j].rgbtGreen + imageAux[i + 1][j + 1].rgbtGreen;
			somaBlue = imageAux[i - 1][j - 1].rgbtBlue + imageAux[i - 1][j].rgbtBlue + imageAux[i - 1][j + 1].rgbtBlue + imageAux[i][j - 1].rgbtBlue + imageAux[i][j].rgbtBlue + imageAux[i][j + 1].rgbtBlue + imageAux[i + 1][j - 1].rgbtBlue + imageAux[i + 1][j].rgbtBlue + imageAux[i + 1][j + 1].rgbtBlue;
			/*
			Valida dois casos em que o denominador varia:
			1º -> Se ele esta na primeira ou ultima coluna/fileira e nao esta no canto;
			2º -> Se não, se ele é um dos pixels de interseção de cantos (4 cantos da imagem);
			*/
			if ((i == 1 && (j != 1 && j != auxWidth - 2)) || (i == auxHeight - 2 && (j != 1 && j != auxWidth - 2)) || (j == 1 && (i != 1 && i != auxHeight - 2)) || (j == auxWidth - 2 && (i != 1 && i != auxHeight - 2)))
			{
				denominador -= 3.0;
			}
			else if ((i == 1 && (j == 1 || j == auxWidth - 2)) || (i == auxHeight - 2 && (j == 1 || j == auxWidth - 2)))
			{
				denominador -= 5.0;
			}

			image[i - 1][j - 1].rgbtRed = round(somaRed / denominador);
			image[i - 1][j - 1].rgbtGreen = round(somaGreen / denominador);
			image[i - 1][j - 1].rgbtBlue = round(somaBlue / denominador);
		}
	}
	return;
}