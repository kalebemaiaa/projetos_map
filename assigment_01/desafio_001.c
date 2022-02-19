#include <stdio.h>

int heigth,i, k, j;

//---->>Falta fazer um verificador de alphanumeric!

void imprimindo(int value)
{
	for (k = 0; k < value; k++)
	{
		for (j = value-1; j > k; j--)
		{
			printf(" ");
		}
		for (i = 0; i <= k; i++)
		{
			printf("#");
		}
		printf("\n");
	}
}

int main(void)
{
	do
	{
		printf("\nDigite a altura da piramide:");
		scanf("%i", &heigth);
	} while (heigth <= 0 || heigth > 8);

	imprimindo(heigth);
	return 0;
}
