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

;stringToInt
;Converte una stringa contenente solo cifre in un numero intero.
;Se nella stringa non sono presenti solo cifre viene terminata l'esecuzion
;del programma con il codice di errore: 100.
;
;@param string stringa da convertire.
;@return int valore convertito (r11).

%macro stringToInt 1
    mov     r8, %1
    mov     rax, 1          ;rax:   peso di ogni cifra
    mov     r10, 10         ;r10:   passo per aumentare/diminuire il peso delle cire

%%extractDigits:
    mov     r12b, [r8]
    inc     r8
    cmp     r12, 10
    je      %%initCalculation
    
    sub     r12, 48

    cmp     r12, 0
    jl      %%NaN_Error
    cmp     r12, 9
    jg      %%NaN_Error

    push    r12
    mul     r10
    jmp     %%extractDigits

%%initCalculation:
    mov     r11, 0
    div     r10
    mov     r13, rax
    mov     r14, rax

%%calculateInt:
    pop     r8
    div     r13
    mul     r8
    add     r11, rax
    
    cmp     r13, 1
    je      %%end

    mov     rax, r13
    div     r10
    mov     r13, rax
    mov     rax, r14
    jmp     %%calculateInt

%%NaN_Error:
    exit 100

%%end:
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

;read
;Permettere di ricevere in input da tastiera una stringa di lunghezza definita.
;
;@param string stringa dove salvare i caratteri letti
;@param int numero di caratteri che si possono leggere.
;           bisogna comunque lasciare sempre un byte per il carattere di terminazione.

%macro read 2
    mov     rax, SYS_READ
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, %2
    syscall
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

;section .data
;    msg db "14563", 10

;section .bss
;    tmp    resb 8
;section .text
;    global _start

;_start:
;    stringToInt msg
;    printLine tmp
;    exit