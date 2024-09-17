#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_key(string s);
void cifra(string text, int key);

int main(int argc, string argv[])
{
    // Verifique se o programa foi executado com apenas um argumento de linha de comando
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Verifique se cada caractere em argv[1] é um dígito
    if (!is_valid_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converta argv[1] de uma `string` para uma `int`
    int key = atoi(argv[1]);

    // Se a chave for maior que 26, ajuste-a para estar dentro do alfabeto
    key = key % 26;

    // Solicite ao usuário o texto simples
    string text = get_string("plaintext: ");

    // Cifre o texto e imprima o texto cifrado
    cifra(text, key);

    return 0;
}

// Função para verificar se uma string é um inteiro válido
bool is_valid_key(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Função para cifrar o texto usando a cifra de César
void cifra(string text, int key)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            printf("%c", (c - base + key) % 26 + base);
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}
