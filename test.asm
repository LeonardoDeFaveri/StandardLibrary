%include "./standardlib.inc"

section .data
    msg     db "Ciao", 10

section .bss
    temp    resb 10

section .text
    global _start:

_start:
    readChar
    printChar r11
    exit