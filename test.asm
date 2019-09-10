%include "./standardlib.inc"

section .data
    filename db "./file.txt", 0
    msg      db "Ciao",10, "come va?"

section .bss
    buffer resb 100

section .text
    global _start:

    _start:
        fileOpen filename, O_APPEND+O_RDWR, 0777o
        push    rax
        fileRead [rsp], buffer, 100
        filePrintLine [rsp], msg
        fileMoveToBeginning [rsp]
        fileRead [rsp], buffer, 100
        fileClose [rsp]
        printLine buffer
        exit