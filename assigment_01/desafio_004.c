#include <stdio.h>
#include <string.h>

char numerosCartao[16],somaTotalStringy[3];
int i,somaDosPares, somaDobrada, somaTotal, somaDosImpares,k,controle;


int isNumber(char string[])
{
    for (i = 0; i < strlen(string); i++)
    {
        int charInEvidence = (int)string[i];
        if (charInEvidence < 48 || charInEvidence > 57)
        {
            return 0;
        }
    }
}

int main(void)
{
    do{
        printf("\nDigite o numero do cartao com no maximo 16 digitos:");
        scanf("%s",&numerosCartao);
    }while(!isNumber(numerosCartao)||strlen(numerosCartao)>16||strlen(numerosCartao)<13);
    somando(numerosCartao);
}

int verificaBandeira(char string[])
{
    printf("\nENTROU NA VERIFICABANDEIRA!");
    switch (string[0])
    {
    case 51:
        printf("\n-->American Express");
        break;
    case 53:
        printf("\n-->MasterCard");
        break;
    case 52:
        printf("\n-->Visa");
        break;
    default:
        printf("\n-->Invalid!");
        break;
    }
}

int somando(char string[])
{
    for (i = 0; i < strlen(string); i++)
    {
        int atual = string[i] - '0';
        if (i % 2 == 0)
        {
            if (atual > 4)
            {
                char stringfyNumber[4];
                sprintf(stringfyNumber, "%d", atual * 2);
                for(k=0;k<strlen(stringfyNumber);k++){
                    int numberAtual = stringfyNumber[k] - '0';
                    controle += numberAtual;
                }
                somaDobrada += controle;
            }
            else
            {
                somaDosPares += atual * 2;
            }
        }
        else
        {
            somaDosImpares += atual;
        }
    }
    somaTotal = controle+somaDosPares + somaDosImpares;
    sprintf(somaTotalStringy, "%d", somaTotal);
    if(somaTotalStringy[strlen(somaTotalStringy)-1]=='0'){
        verificaBandeira(string);
    }
}
