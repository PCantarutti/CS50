#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
    {
        string name;
        int rarity;
        string element;
    } character;

void personagens(int times);

int main(void)
{
    int times = get_int("Quantos personagens armazenar? ");
    if (times <= 0 || times > 5)
    {
        printf("tente novamente\n");
    }
    else
    {
        personagens(times);
    }
}

void personagens(int times)
{
    character characters[times];
    for (int i = 0; i < times; i++)
    {
        characters[i].name = get_string("Nome: ");
        characters[i].element = get_string("Elemento: ");

        do
        {
            characters[i].rarity = get_int("Raridade (4 ou 5): ");
        }
        while (characters[i].rarity < 4 || characters[i].rarity > 5);
    }

    printf("\n============================\n============================\n\n");
    for (int j = 0; j < times; j++)
    {
        printf("%s - %s - ", characters[j].name, characters[j].element);

        for (int k = 0; k < characters[j].rarity; k++)
        {
            printf("☆ ");
        }
        printf("\n");
    }
}
