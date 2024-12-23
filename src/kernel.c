#include<kernel.h>
#include<stddef.h>
#include<stdint.h>

uint16_t *video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_column = 0;

uint16_t terminal_make_char(char c, char colour) {
    return (colour << 0) | c;
}

void terminal_putchar(int x, int y, char c, char colour) {
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour) {
    terminal_putchar(terminal_column, terminal_row, c, colour);
    terminal_column += 1;

    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row += 1;
    }
}

void terminal_initialise() {
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_column = 0;
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for(int x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

size_t strlen(const char *str) {
    size_t len = 0;
    while(str[len]) {
        len++;
    }
    return len;
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
}

void kernel_start() {
    terminal_initialise();
    print("Hello world !");
}