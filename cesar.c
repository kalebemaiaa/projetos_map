#include <cs50.h>
#include <stdio.h>
#include <string.h>

char alphabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char alphabetoMaior[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int power(int x, int y) // NAO ESTAVA FUNCIONANDO O POW DA MATH.H ENT IMPLEMENTEI ESSA DAQUI; -> PEGUEI NA INTERNET E APARENTEMENTE FUNCIONA;
{
	if (y > 0)
		return power(x, --y) * x;
	else
		return 1;
}

bool only_digits(char string[]) // VERIFICA SE SÃO APENAS NUMEROS E SE ENCONTRAR ALGUM OUTRO TIPO DE CHAR RETORNA 0 E PARA DE RODAR. SE NAO ENCONTRAR CHAR ALPHABETO RETORNA 1
{
	for (int i = 0, n = strlen(string); i < n; i++)
	{
		if (string[i] > 57 || string[i] < 48)
		{
			return 0;
		}
	}
	return 1;
}

int StringToNumber(char string[]) // FUNÇÃO PARA TRANSFORMA UMA STRING, JA VERIFICADA COMO NUMEROS, EM UM NUMERO
{
	int long levarDeVolta = 0;
	for (int i = 0, n = strlen(string); i < n; i++)
	{
		int atual = string[i] - '0'; // CHAR ATUAL COMO INT
		int expoente = n - i - 1;	 // EXPOENTE DO 10.
		double potencia = power(10, expoente);
		int numero = atual * potencia;
		levarDeVolta += numero;
	}
	return levarDeVolta;
}

int makeIndex(int key, int indexAlphabeto) // SE É UMA LETRA COMO 'Z' QUE RECEBE +13 DE INDEX, COMECA A CONTAR DO A;
{
	if (indexAlphabeto + key > 25)
	{
		return key - (26 - indexAlphabeto);
	}
	else
	{
		return key + indexAlphabeto;
	}
}

int makeKey(int key) // BASICAMENTE -> SE O NUMERO PASSADO FOR MAIOR QUE 26 A NOVA CHAVE SERA O RESTO DE SUA DIVISAO POR 26.
{
	if (key > 26)
	{
		return key % 26;
	}
	else
	{
		return key;
	}
}

char criptografando(int key, char string[])
{
	char palavra[strlen(string) - 1];
	for (int i = 0, n = strlen(string); i < n; i++) // PERCORRE A STRING PASSADA
	{
		if ((string[i] > 90 || string[i] < 65) && (string[i] < 97 || string[i] > 122)) // SE NAO FOR UMA LETRA ->  PALAVRA[i] = STR$ING[i]
		{
			palavra[i] = string[i];
		}
		else
		{
			for (int k = 0, length = strlen(alphabeto); k < length; k++) // PRECORRE O ALFABETO
			{
				int index = makeIndex(makeKey(key), k);
				if (string[i] == alphabeto[k]) // VE SE É MINUSCULA
				{
					palavra[i] = alphabeto[index];
				}
				else if (string[i] == alphabetoMaior[k]) // VE SE É MAISCULA
				{
					palavra[i] = alphabetoMaior[index];
				}
			}
		}
	}
	printf("\nciphertext: %s\n", palavra); // PRINTA A SAIDA DESAJADA !!OBS: AO DIGITAR POUCAS LETRAS, COMO 'a', RETORNA ALGO ESTRANHO;
}

int main(int argc, string argv[])
{
	if (argc != 2 || !only_digits(argv[1]))
	{
		printf("\nUsage:\t./cesar key\n");
		return 1;
	}
	string textToRotate = get_string("plaintext:  ");
	criptografando(StringToNumber(argv[1]), textToRotate);
	return 0;
}
