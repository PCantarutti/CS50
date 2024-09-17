#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function to count letters, words, and sentences
void count_text(string texto, int *letras, int *palavras, int *frases);

int main(void)
{
    // Prompt the user for some text
    string texto = get_string("Text: ");

    // Initialize counters
    int letras = 0, palavras = 0, frases = 0;

    // Count the number of letters, words, and sentences in the text
    count_text(texto, &letras, &palavras, &frases);

    // Compute the Coleman-Liau index
    float L = (float) letras / palavras * 100;
    float S = (float) frases / palavras * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // Print the counts and the Coleman-Liau index
    printf("index: %.2f\n", index);

    // Print the grade level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

void count_text(string texto, int *letras, int *palavras, int *frases)
{
    *palavras = 1; // Start with 1 to account for the last word
    for (int i = 0, n = strlen(texto); i < n; i++)
    {
        if (isalpha(texto[i]))
        {
            (*letras)++;
        }
        else if (isspace(texto[i]))
        {
            (*palavras)++;
        }
        else if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?')
        {
            (*frases)++;
        }
    }
}
