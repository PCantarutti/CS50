#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int num_letras(string texto);
int num_palavras(string texto);
int num_frases(string texto);
int grade_level(int index);

int main(void)
{
    // Prompt the user for some text
    string texto = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letras = num_letras(texto);
    int palavras = num_palavras(texto);
    int frases = num_frases(texto);

    // Compute the Coleman-Liau index
    float L = (float) letras / palavras * 100;
    float S = (float) frases / palavras * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    double round(double index);

    // Print the grade level
    printf("index: %.2f\n", index);
    grade_level((int) round(index));
}

int num_letras(string texto)
{
    int contagem = 0;
    for (int i = 0, n = strlen(texto); i < n; i++)
    {
        char c = texto[i];
        if (isalpha(c))
        {
            contagem++;
        }
    }
    return contagem;
}

int num_palavras(string texto)
{
    int contagem = 1;
    for (int i = 0, n = strlen(texto); i < n; i++)
    {
        if (texto[i] == ' ')
        {
            contagem++;
        }
    }
    return contagem;
}

int num_frases(string texto)
{
    int contagem = 0;
    for (int i = 0, n = strlen(texto); i < n; i++)
    {
        if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?')
        {
            contagem++;
        }
    }
    return contagem;
}

int grade_level(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return 0;
}
