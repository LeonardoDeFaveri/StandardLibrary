SYS_READ    equ 0
SYS_WRITE   equ 1
SYS_EXIT    equ 60

STDOUT      equ 0
STDIN       equ 1
STDERR      equ 2

;getLength
;Restituisce il numero di byte che compongono una 
;stringa senza includere il carattere di terminazione.
;
;@param string la stringa da stampare.
;@return lunghezza in byte della stringa (r11).
 
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

;print
;Stampa una stringa a nello Standard Output senza andare a capo.
;
;@param string stringa da stampare.
 
%macro print 1
    getLength %1

    mov     rax, SYS_WRITE
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, r11
    syscall
%endmacro

;printLine
;Stampa una stringa a nello Standard Output e va a capo.
;
;@param string stringa da stampare.
 
%macro printLine 1
    getLength %1
    inc     r11

    mov     rax, SYS_WRITE
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, r11
    syscall
%endmacro

;intToString
;Converte in stringa un valore intero.
;
;@param int valore intero da convertire.
;@param string variabile dove salvare la stringa risultante.
;@return string stringa raffigurante il valore intero (%2).
 
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

;printInt
;Stampa un valore intero nello Standard Output senza andare a capo.
;
;@param int valore da stampare.
;@param string stringa dove salvare il valore intero convertito in stringa.
 
%macro printInt 2
    intToString %1, %2
    print %2
%endmacro

;printLineInt
;Stampa un valore intero nello Standard Output e va a capo.
;
;@param int valore da stampare.
;@param string stringa dove salvare il valore intero convertito in stringa.
 
%macro printLineInt 2
    intToString %1, %2
    printLine %2
%endmacro

;exit
;Termina il programma quando tutto è andato a buon fine, 
;quindi restituisce 0 come codice di errore.
 
%macro exit 0
    mov     rax, SYS_EXIT
    mov     rdi, 0
    syscall
%endmacro

;exit
;Termina il programma restituiendo un codice di errore.
;
;@param int codice di errore da restituire.
 
%macro exit 1
    mov     rax, SYS_EXIT
    mov     rdi, %1
    syscall
%endmacro

section .data
    msg db "11111222223333344444555556666677777888889999900000", 10

section .bss
    tmp    resb 100
section .text
    global _start

_start:
    printLineInt 1234556, tmp
    exit