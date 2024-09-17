#include <stdio.h>

int main(void)
{
    int call = 55;
    int *p = &call;

    printf("\nmostrando endereço do pointer: %p\n", &p);
    printf("pointer apontando endereço de outra variavel: %p\n\n", p);
    printf("pointer apontando para valor de outro endereço: %i\n\n", *p);
    printf("mostrando endereço de uma variavel: %p\n", &call);
}
