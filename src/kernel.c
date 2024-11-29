#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define FB_WIDTH  80
#define FB_HEIGHT 25
#define FB_DEPTH  2
#define FB_SIZE (FB_WIDTH * FB_HEIGHT * FB_DEPTH)

void main(void) {
    const char *str = "Kernel Runs";
    char *framebuffer;
    int fb = open("/dev/fb0", O_RDWR);
    if (fb == -1) {
        perror("Error opening framebuffer");
        return;
    }

    framebuffer = (char*)mmap(NULL, FB_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
    if (framebuffer == MAP_FAILED) {
        perror("Error mapping framebuffer");
        close(fb);
        return;
    }

    unsigned int i = 0;
    unsigned int j = 0;

    /* Limpar a tela */
    while (j < FB_SIZE) {
        framebuffer[j] = ' ';       // Caracter vazio
        framebuffer[j+1] = 0x07;    // Cor do texto (preto com texto cinza claro)
        j = j + 2;
    }

    j = 0;

    /* Escrever a string */
    while (str[j] != '\0') {
        framebuffer[i] = str[j];   // Caracter em ASCII
        framebuffer[i+1] = 0x07;   // Cor do texto
        ++j;
        i = i + 2;
    }

    munmap(framebuffer, FB_SIZE);
    close(fb);
}
