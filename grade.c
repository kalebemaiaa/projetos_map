#include <stdio.h>
#include <string.h>
#include <cs50.c>

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123)) //SE ACHAR UMA LETRA ELE AUMENTA O COUNT
        {
            count += 1;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32) //SE ACHAR UM ESPAÇO EM BRANCO ELE AUMENTA O COUNT
        {
            count += 1;
        }
    }
    return count + 1;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')//SE ACHAR ESSES CHAR ELE AUMENTA O COUNT
        {
            count += 1;
        }
    }
    return count;
}

void grade(int size, string txt)
{
    int letras = count_letters(txt);
    int sentencas = count_sentences(txt);
    int palavras = count_words(txt);
    float S = sentencas / (float) palavras * 100;
    float L = letras / (float) palavras * 100;
    float IDX = ( 0.0588 * L - 0.296 * S - 15.8) ;
    if(IDX<1)
    {
        printf("\nGrade Before 1");
    }
    else if(IDX<17)
    {
        printf("\nGrade %.0f",IDX);
    }
    else{
        printf("\nGrade 16+");
    }
}

int main(int argc, char *argv[])
{

    FILE *fp = NULL;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error, um arquivo .txt deve ser passado.\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1)
    {
        // remove the \n from the end
        line[strcspn(line, "\n")] = '\0';

        // print info
        grade((int)strlen(line), line);
    }
    fclose(fp);
    return 0;
}
