#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Verificar o argumento de linha de comando
    if (argc != 2)
    {
        printf("Uso correto: ./recover (nome do arquivo de imagem)\n");
        return 1;
    }

    // Abrir o arquivo de cartão de memória
    FILE *cartao = fopen(argv[1], "r");
    if (cartao == NULL)
    {
        printf("Não foi possível abrir %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    FILE *imagem = NULL;
    char filename[8];
    int contagem = 0;

    // Ler o cartão de memória bloco por bloco
    while (fread(buffer, sizeof(BYTE), 512, cartao) == 512)
    {
        // Verificar se é o início de um novo JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Se já estamos processando uma imagem, fechá-la
            if (imagem != NULL)
            {
                fclose(imagem);
            }

            // Criar um novo arquivo JPEG
            sprintf(filename, "%03i.jpg", contagem);
            imagem = fopen(filename, "w");
            if (imagem == NULL)
            {
                printf("Não foi possível criar o arquivo %s\n", filename);
                return 1;
            }

            contagem++;
        }

        // Se já começamos a processar uma imagem, escrever no arquivo
        if (imagem != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, imagem);
        }
    }

    // Fechar quaisquer arquivos abertos
    if (imagem != NULL)
    {
        fclose(imagem);
    }
    printf("Fotos recuperadas: %i\n", contagem);
    fclose(cartao);

    return 0;
}
