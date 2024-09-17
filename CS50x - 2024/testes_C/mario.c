#include <stdio.h>
#include <cs50.h>

void print_space(int espaço);
void print_row(int largura);

int main(void)
{
    int altura;
    do
    {
        altura = get_int("Altura: ");
    }
    while(altura < 1 || altura > 8);

    for (int i = 0; i < altura; i++)
    {
        print_space(altura - 1 - i);
        print_row(i + 1);
    }
}

void print_space(int espaço)
{
    for (int h = 0; h < espaço; h++)
    {
        printf(" ");
    }
}

void print_row(int largura)
{
    for (int j = 0; j < largura; j++)
    {
        printf("#");
    }
    printf("\n");
}
