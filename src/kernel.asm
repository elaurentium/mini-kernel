    .global start
    .extern main            ; Definido no arquivo C

    .section .text
    .align 4
    .global _start

_start:
    mov sp, stack_space     ; Definir ponteiro de pilha (SP)
    bl main                ; Chamar a função kmain
    b .                     ; Loop infinito para interromper a execução

    .section .bss
stack_space:
    .skip 8192              ; 8KB para a pilha
