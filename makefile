# Makefile for MINUX
ENTRYPOINT = 0x30400

ENTRYOFFSET = 0x400

ASM = nasm
DASM = ndisasm
CC = gcc
LD = ld
ASMBFLAGS = -I boot/include/
ASMKFLAGS = -I include/ -f elf
CFLAGS = -I include/ -c -fno-builtin -m32 -std=c99 -fno-stack-protector
LDFLAGS = -s -Ttext $(ENTRYPOINT) -m elf_i386
DASMFLAGS = -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)


MINUXBOOT = boot/boot.bin boot/loader.bin
MINUXKERNEL = kernel.bin
OBJS = kernel/kernel.o kernel/start.o kernel/main.o lib/memory.o lib/putchar.o kernel/i8259.o kernel/global.o kernel/protect.o kernel/string.o kernel/shell.o kernel/clock.o kernel/syscall.o kernel/proc.o kernel/keyboard.o kernel/tty.o

.PHONY : everything final image clean realclean all buildimg

everything : $(MINUXBOOT) $(MINUXKERNEL)

all : realclean everything

final : all clean

image : final buildimg

clean :
	rm -f $(OBJS)

realclean :
	rm -f $(OBJS) $(MINUXBOOT) $(MINUXKERNEL)

buildimg :
	dd if=/dev/zero of=os.img bs=1024 count=1440 conv=notrunc
	dd if=boot/boot.bin of=os.img bs=512 count=1 conv=notrunc
	sudo mount -o loop os.img osdir/
	sudo cp -fv boot/loader.bin osdir/
	sudo cp -fv kernel.bin osdir/
	sudo umount osdir

boot/boot.bin : boot/boot.asm boot/include/load.inc boot/include/fat12.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

boot/loader.bin : boot/loader.asm boot/include/load.inc \
boot/include/fat12.inc boot/include/pm.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

$(MINUXKERNEL) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(MINUXKERNEL) $(OBJS)

kernel/kernel.o : kernel/kernel.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/start.o : kernel/start.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/global.h include/memory.h
	$(CC) $(CFLAGS) -o $@ $<

lib/memory.o : lib/memory.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/putchar.o : lib/putchar.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/i8259.o: kernel/i8259.c include/memory.h include/type.h include/const.h include/protect.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/protect.o: kernel/protect.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/global.o: kernel/global.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/string.o: kernel/string.c include/string.h
	$(CC) $(CFLAGS) -o $@ $<


kernel/shell.o: kernel/shell.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/main.o: kernel/main.c include/type.h include/const.h include/protect.h include/string.h include/proc.h include/global.h include/memory.h
	$(CC) $(CFLAGS) -o $@ $<

kernel/clock.o: kernel/clock.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/syscall.o: kernel/syscall.asm
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/proc.o:kernel/proc.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/keyboard.o:kernel/keyboard.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/tty.o:kernel/tty.c
	$(CC) $(CFLAGS) -o $@ $<

