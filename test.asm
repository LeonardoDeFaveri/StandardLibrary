%include "./standardlib.inc"

section .data
    filename db "./file.txt", 0
    msg     db "prova", 10
    delay   dq 5, 500000000

section .bss
    temp    resb 100

section .text
    global _start:

    _start:
    sleep delay

    exit