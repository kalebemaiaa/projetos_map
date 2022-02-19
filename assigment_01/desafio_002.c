#include <stdio.h>

int heigth, i, k, j;

//-->ladoDaIgualdade pode ser d = (<=) ou  e = (>)
void formatoPiramide(int start, int kindex, char ladoDaIgualdade)
{
    if (ladoDaIgualdade == 'd')
    {
        for (i = start; i <= kindex; i++)
        {
            printf("#");
        }
    }
    else if (ladoDaIgualdade == 'e')
    {
        for (i = start; i > kindex; i--)
        {
            printf(" ");
        }
    }
    else
    {
        for (i = start; i < kindex; i++)
        {
            printf(" ");
        }
    }
}

void imprimindo(int value)
{
    for (k = 0; k < 8; k++)
    {
        formatoPiramide(value - 1, k, 'e');
        formatoPiramide(0, k, 'd');
        formatoPiramide(0, 2, 'r');
        formatoPiramide(0, k, 'd');
        formatoPiramide(value - 1, k, 'e');
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