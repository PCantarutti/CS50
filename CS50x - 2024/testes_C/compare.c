#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *x = get_string("Oque é X? ");
    char *y = get_string("Oque é y? ");

    if (strcmp(x, y) == 0)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }
}
