# Shell file to compile code
set -e
# assemble boot.s file
as --32 boot.s -o boot.o

# compile kernel.c file
gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile vga.c file
gcc -m32 -c vga.c -o vga.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile bitmap.c file
gcc -m32 -c bitmap.c -o bitmap.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile utils.c file
gcc -m32 -c utils.c -o utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# compile pong.c file
gcc -m32 -c pong.c -o pong.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra

# linking all the object files to amogOS.bin
ld -m elf_i386 -T linker.ld kernel.o vga.o boot.o bitmap.o utils.o pong.o -o amogOS.bin -nostdlib

# check amogOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot amogOS.bin

# building the iso file
mkdir -p isodir/boot/grub
cp amogOS.bin isodir/boot/amogOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o amogOS.iso isodir

# run it in qemu
qemu-system-x86_64 -cdrom amogOS.iso
