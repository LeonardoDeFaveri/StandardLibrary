SYS_READ    equ 0
SYS_WRITE   equ 1
SYS_EXIT    equ 60

STDOUT      equ 0
STDIN       equ 1
STDERR      equ 2

%macro getLength 1
    mov     r10, %1
    mov     r11, r10

%%begin:
    cmp     byte [r11], 10
    je      %%end
    inc     r11
    jmp     %%begin

%%end:
    sub     r11, r10
%endmacro

%macro print 1
    getLength %1

    mov     rax, SYS_WRITE
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, r11
    syscall
%endmacro

%macro printLine 1
    getLength %1
    inc     r11

    mov     rax, SYS_WRITE
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, r11
    syscall
%endmacro

%macro printInt 2
    intToString %1, %2
    print %2
%endmacro

%macro printLineInt 2
    intToString %1, %2
    printLine %2
%endmacro

%macro exit 0
    mov     rax, SYS_EXIT
    mov     rdi, 0
    syscall
%endmacro

%macro exit 1
    mov     rax, SYS_EXIT
    mov     rdi, %1
    syscall
%endmacro

%macro intToString 2
    mov     rax, %1
    mov     r11, %2
    mov     r12, 10

    push    r12

%%extractDigits:
    mov     rdx, 0
    div     r12
    add     rdx, 48

    push    rdx

    cmp     rax, 0
    jne     %%extractDigits

%%popDigits:
    pop     r10

    mov     [r11], r10b
    inc     r11
    mov     [r11], r11

    cmp     r10, 10
    jne     %%popDigits
    
%endmacro

section .data
    msg db "11111222223333344444555556666677777888889999900000", 10

section .bss
    tmp    resb 100
section .text
    global _start

_start:
    printLineInt 18446744073709551615, tmp

    exit