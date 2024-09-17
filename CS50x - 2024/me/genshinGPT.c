#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Definição da struct character
typedef struct
{
    string name;
    int rarity;
    string element;
} character;

// Declaração das funções
void personagens(int times);
character criar_personagem(void);
void exibir_personagem(character c);

int main(void)
{
    // Pergunta ao usuário quantos personagens deseja armazenar
    int times = get_int("Quantos personagens armazenar? ");
    if (times <= 0 || times > 5)
    {
        printf("Número inválido, tente novamente\n");
    }
    else
    {
        personagens(times);
    }
}

// Função para criar e armazenar os personagens
void personagens(int times)
{
    if (times <= 0 || times > 5)
    {
        printf("Número de personagens fora dos limites permitidos.\n");
        return;
    }

    character characters[times];
    for (int i = 0; i < times; i++)
    {
        characters[i] = criar_personagem();
    }

    printf("\n============================\n============================\n\n");
    for (int j = 0; j < times; j++)
    {
        exibir_personagem(characters[j]);
    }
}

// Função para criar um personagem
character criar_personagem(void)
{
    character c;
    c.name = get_string("Nome: ");
    c.element = get_string("Elemento: ");

    do
    {
        c.rarity = get_int("Raridade (4 a 5): ");
        if (c.rarity < 4 || c.rarity > 5)
        {
            printf("Raridade inválida, tente novamente.\n");
        }
    }
    while (c.rarity < 4 || c.rarity > 5);

    return c;
}

// Função para exibir as informações de um personagem
void exibir_personagem(character c)
{
    printf("%s - %s - ", c.name, c.element);

    for (int k = 0; k < c.rarity; k++)
    {
        printf("☆ ");
    }
    printf("\n");
}
