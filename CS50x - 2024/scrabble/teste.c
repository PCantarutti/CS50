#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void soma_pontos(string pergunta, int pontos[], int *player);
void to_lowercase(string s);
void vencedor(int player1, int player2);

int main(void)
{
    // Mapeamento de pontos para cada letra do alfabeto
    int pontos[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int player1 = 0;
    int player2 = 0;

    string pergunta1 = get_string("Player 1: ");
    string pergunta2 = get_string("Player 2: ");

    to_lowercase(pergunta1);
    to_lowercase(pergunta2);

    soma_pontos(pergunta1, pontos, &player1);
    soma_pontos(pergunta2, pontos, &player2);

    vencedor(player1, player2);
}

// Função para transformar a string em minúsculas
void to_lowercase(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = tolower(s[i]);
    }
}

// Função para somar pontos para um jogador
void soma_pontos(string pergunta, int pontos[], int *player)
{
    for (int i = 0, n = strlen(pergunta); i < n; i++)
    {
        char c = pergunta[i];
        if (isalpha(c))  // Verifica se o caractere é uma letra
        {
            *player += pontos[c - 'a'];  // Calcula o índice e soma os pontos
        }
    }
}

void vencedor(int player1, int player2)
{
    if (player1 == player2)
    {
        printf("TIE\n");
    }
    else if (player1 > player2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}
