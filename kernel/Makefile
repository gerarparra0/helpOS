ARCH=x86_64-elf
BIN=$(ARCH)_kernel.elf

CFLAGS =-Wall -fpic -ffreestanding -fno-stack-protector -nostdinc -nostdlib -g
LDFLAGS =-nostdlib -nostartfiles -T link.ld

OBJ=kernel.o framebuffer.o system.o descriptors.o

$(BIN): $(OBJ)
	$(ARCH)-ld -r -b binary -o font.o font.psf
	$(ARCH)-ld $(LDFLAGS) $(OBJ) font.o -o $(BIN)
	$(ARCH)-objcopy --only-keep-debug $(BIN) debug.sym
	$(ARCH)-strip -s -K mmio -K fb -K bootboot -K environment $(BIN)


.c.o:
	$(ARCH)-gcc $(CFLAGS) -mno-red-zone -c $< -o $@

all: $(BIN)


clean:
	rm -f *.o *.elf *.sym
