#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cash;
    int coin = 0;
    do
    {
        cash = get_int("Change owed: ");
    }
    while (cash < 0);

    if (cash >= 25)
        do
        {
            coin++;
            cash -= 25;
        }
        while (cash >= 25);

    if (cash >= 10)
        do
        {
            coin++;
            cash -= 10;
        }
        while (cash >= 10);

    if (cash >= 5)
        do
        {
            coin++;
            cash -= 5;
        }
        while (cash >= 5);

    if (cash >= 1)
        do
        {
            coin++;
            cash -= 1;
        }
        while (cash >= 1);

    printf("%i\n", coin);
}
