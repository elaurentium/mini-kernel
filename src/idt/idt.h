#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_desc {
    uint16_t offset_1; // Offset bits 15-0
    uint16_t selector; // Selector thats in our GDT
    uint8_t zero;     // Always 0
    uint8_t type_attr; 
    uint16_t offset_2; // Offset bits 31-16 
} __attribute__((packed));

struct idtr_desc {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init();

#endif 