%include "./standardlib.inc"

section .data
    msg      db "123456"

section .bss
    buffer resb 100

section .text
    global _start:

    _start:
        stringToInt msg
        printLineInt r11, buffer
        exit