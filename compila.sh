nasm -f elf64 -F DWARF -g test.asm -o object.o
ld object.o -o exe
if [ -e object.o ]
then
    rm object.o
fi