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

char rotate(char palavra, int k)
{
  if((palavra> 90 || palavra< 65) && (palavra< 97 || palavra> 122))
  {
    printf("%c", palavra);
  }
  else{
    for(int i=0, length=strlen(alphabeto);i<length;i++)
      {
        int chave = makeIndex(k,i);
        if(palavra==alphabeto[i])
        {
          printf("%c", alphabeto[chave]);
        }
        else if(palavra==alphabetoMaior[i])
        {
          printf("%c", alphabetoMaior[chave]);
        }
      }
  }
}

char criptografando(int key, char string[])
{
	char palavra[strlen(string)];
  int index = makeKey(key);
  printf("\nciphertext: ");
	for (int i = 0, n = strlen(string); i < n; i++) // PERCORRE A STRING PASSADA
	{
		rotate(string[i],index);
	}
  return 0;
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
