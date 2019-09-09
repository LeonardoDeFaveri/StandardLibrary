SYS_READ        equ 0
SYS_WRITE       equ 1
SYS_OPEN        equ 2
SYS_CLOSE       equ 3
SYS_POLL        equ 7
SYS_LSEEK       equ 8
SYS_IOCTL       equ 16
SYS_NANOSLEEP   equ 35
SYS_EXIT        equ 60

STDIN           equ 0
STDOUT          equ 1
STDERR          equ 2

O_RDONLY        equ 0
O_WRONLY        equ 1
O_RDWR          equ 2
O_CREAT         equ 64
O_APPEND        equ 1024
O_DIRECTORY     equ 65535
O_PATH          equ 2097152
O_TMPFILE       equ 4194304

SEEK_SET        equ 0           ;Riposiziona l'offset partendo dall'inizio del file
SEEK_CUR        equ 1           ;Riposiziona l'offset partendo dalla posizione attuale del cursore nel file
SEEK_END        equ 2           ;Riposiziona l'offset partendodalla fine del file

ICANON          equ 2            
ECHO            equ 8
TCGETS          equ 21505       ;Attributo per ottenere la struttura
TCPUTS          equ 21506       ;Attributo per inviare la struttura

section .bss
    __stty    resb 12       ;Dimensione dlla struttura termios - 60 byte
    __slflag  resb 4        ;__slflag si trova al quarto posto in memoria dopo 3 gruppi da 4 byte
    __srest   resb 44

    __tty     resb 12
    __lflag   resb 4
    __brest   resb 44

section .data
    __fd      dd 0
    __sym     db 1


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

;printChar
;stampa un solo carattere a schermo senza adndare a capo.
;
;@param char carattere da stampare
%macro printChar 1
    mov     rax, SYS_WRITE
    mov     rdi, STDOUT
    mov     rsi, %1
    mov     rdx, 1
    syscall
%endmacro

;print
;Stampa una stringa a schermo senza andare a capo.
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
;Stampa una stringa a schermo e va a capo.
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

;ReadChar
;Legge un carattere da tastiera.
;
;@return carattere letto (r11).
%macro readChar 0
    call %%setnoncan
    call %%poll
    call %%setcan
    jmp %%end

    %%setnoncan:      
        push    __stty
        call    %%tcgetattr
        push    __tty
        call    %%tcgetattr
        and     dword[__lflag], (~ICANON)
        and     dword[__lflag], (~ECHO)
        call    %%tcsetattr
        add     rsp, 16
        ret

    %%setcan:
        push    __stty
        call    %%tcsetattr
        add     rsp, 8
        ret

    %%tcgetattr:
        mov     rdx, qword[rsp+8]
        push    rax
        push    rbx
        push    rcx
        push    rdi
        push    rsi
        mov     rax, SYS_IOCTL
        mov     rdi, 0
        mov     rsi, TCGETS
        syscall
        pop     rsi
        pop     rdi
        pop     rcx
        pop     rbx
        pop     rax
        ret

    %%tcsetattr:
        mov     rdx, qword[rsp+8]
        push    rax
        push    rbx
        push    rcx
        push    rdi
        push    rsi
        mov     rax, SYS_IOCTL
        mov     rdi, 0
        mov     rsi, TCPUTS
        syscall
        pop     rsi
        pop     rdi
        pop     rcx
        pop     rbx
        pop     rax
        ret

    %%poll:   
        nop
        push    rbx
        push    rcx
        push    rdx
        push    rdi
        push    rsi
        mov     rax, SYS_POLL
        mov     rdi, __fd       ;Puntatore alla struttura
        mov     rsi, 1          ;Numero di Thread
        mov     rdx, 10000      ;Tempo di attesa massimo
        syscall
        ;Controlla che il valore restituito sia 0
        test    rax, rax
        jz      %%e
        ;Se ci sono dati, fa una chiamata a SYS_READ
        mov     rax, 0
        mov     rdi, 0
        mov     rsi, __sym   
        mov     rdx, 1
        syscall
        xor     rax, rax
        mov     al, byte[__sym]    ;Restituisce il codice del carattere se è stato letto.
    %%e:     
        pop     rsi
        pop     rdi
        pop     rdx
        pop     rcx
        pop     rbx
        ret

    %%end:
        mov     r11, __sym
%endmacro


;read
;Permettere di ricevere in input da tastiera una stringa di lunghezza definita.
;
;@param string stringa dove salvare i caratteri letti
;@param int numero di caratteri che si possono leggere.
;           Bisogna comunque lasciare sempre un byte per il carattere di terminazione.
%macro read 2
    mov     rax, SYS_READ
    mov     rdi, STDIN
    mov     rsi, %1
    mov     rdx, %2
    syscall
%endmacro

;readInt
;Permette di ricevere in input dalla tastiera un numero intero.
;
;@param string stringa dove salvare i caratteri letti.
;@param int numero di caratteri che si possono leggere.
;           Bisogna comunque lasciare sempre un byte per il carattere di terminazione.
;@return int numero letto (r11)
%macro readInt 2
    read %1, %2
    stringToInt %1
%endmacro

;fileOpen
;Apre un file così che sia possibile interagire con esso.
;
;@param string nome o percorso del file da aprire
;@param int flag da applicare al file.
;@param octal permessi per il file.
;@return int file descriptor (r11)
%macro fileOpen 3
    push    rax

    mov     rax, SYS_OPEN
    mov     rdi, %1
    mov     rsi, %2
    mov     rdx, %3
    syscall

    mov     r11, rax
    pop rax
%endmacro

;filePrint
;Permette di scrivere del testo su un file, senza andare a capo.
;
;@param int file descriptor del file su cui scrivere.
;@param string  testo da scrivere.
%macro filePrint 2
    getLength %2

    mov     rax, SYS_WRITE
    mov     rdi, %1
    mov     rsi, %2
    mov     rdx, r11
    syscall
%endmacro

;filePrintLine
;Permette di scrivere del testo su un file e andare a capo.
;
;@param int file descriptor del file su cui scrivere.
;@param string  testo da scrivere.
%macro filePrintLine 2
    getLength %2
    inc     r11

    mov     rax, SYS_WRITE
    mov     rdi, %1
    mov     rsi, %2
    mov     rdx, r11
    syscall
%endmacro

;fileRead
;Permette di leggere dei caratteri da un file.
;
;@param int file descriptor del file dal quale leggere.
;@param string stringa dove salvare i caratteri letti.
;@param int numero di caratteri da leggere.
;            Bisogna comunque lasciare sempre un byte per il carattere di terminazione.
;@return int numero di caratteri letti (r11).
%macro fileRead 3
    mov     rax, SYS_READ
    mov     rdi, %1
    mov     rsi, %2
    mov     rdx, %3
    syscall

    mov     r11, rax
%endmacro

;fileClose
;Chiude un file aperto.
;
;@param int file descriptor del file da chiudere.
%macro fileClose 1
    mov     rax, SYS_CLOSE
    mov     rdi, %1
    syscall
%endmacro

;fileGetOffset
;Restituisce l'attuale posizione del cursore al'interno del file.
;
;@param int file descriptor del file del quale ottenere l'offset.
;@return int offset (r11).
%macro fileGetOffset 1
    mov     rax, SYS_LSEEK
    mov     rdi, %1
    mov     rsi, 0
    mov     rdx, SEEK_CUR
    syscall

    mov     r11, rax
%endmacro

;fileMoveToBeginning
;Sposta il cursore all'inizio del file.
;
;@param int file descriptor del file del quale spostare il cursore.
;@return int offset (r11).
%macro fileMoveToBeginning 1
    mov     rax, SYS_LSEEK
    mov     rdi, %1
    mov     rsi, 0
    mov     rdx, SEEK_SET
    syscall

    mov     r11, rax
%endmacro

;fileMoveToEnd
;Sposta il cursore alla fine del file.
;
;@param int file descriptor del file del quale spostare il cursore.
;@return int offset (r11).
%macro fileMoveToEnd 1
    mov     rax, SYS_LSEEK
    mov     rdi, %1
    mov     rsi, 0
    mov     rdx, SEEK_END
    syscall

    mov     r11, rax
%endmacro

;sleep
;Mette in pausa l'esecuzione del programma per una certa quantità di tempo.
;
;@param timespec tempo di pausa.
%macro sleep 1
    mov     rax, SYS_NANOSLEEP
    mov     rdi, %1
    mov     rsi, 0
    syscall
%endmacro

;sleep
;Mette in pausa l'esecuzione del programma per una certa quantità di tempo.
;
;@param timespec tempo di pausa.
;@param timespec tempo rimanente di pausa.
%macro sleep 2
    mov     rax, SYS_NANOSLEEP
    mov     rdi, %1
    mov     rsi, %2
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