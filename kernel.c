#include <stdio.h>

void main(void) {
    const char *str = "Kernel Runs";
    /* A memória de vídeo começa no endereço 0xb8000 */
    char *vidptr = (char*)0xb8000;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int screensize;

    /* Este loop limpa a tela
     * Existem 25 linhas e 80 colunas; cada elemento ocupa 2 bytes */
    screensize = 80 * 25 * 2;
    while (j < screensize) {
        /* Caracter em branco */
        vidptr[j] = ' ';
        /* Byte de atributo */
        vidptr[j+1] = 0x07;
        j = j + 2;
    }

    j = 0;

    /* Este loop escreve a string na memória de vídeo */
    while (str[j] != '\0') {
        /* O caractere em ASCII */
        vidptr[i] = str[j];
        /* Byte de atributo: dá ao caractere fundo preto e texto cinza claro */
        vidptr[i+1] = 0x07;
        ++j;
        i = i + 2;
    }

    return;
}