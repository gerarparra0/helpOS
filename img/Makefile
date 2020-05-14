# overall disk image size in megabytes (128M)
DISKSIZE=128
# boot partition size in kilobytes (16M) Note that smallest possible FAT32 is 33M
BOOTSIZE=16384
# boot partition FAT type (16 or 32)
BOOTTYPE=16
ARCH=x86_64-elf
DISK=disk-$(ARCH).img
OVMF=../ovmf/ovmf.fd

all: initrd.bin bootpart.bin

# compile the image creator
mkimg: mkimg.c
	gcc -ansi -pedantic -Wall -Wextra -g mkimg.c -o mkimg

# create an initial ram disk image with the kernel inside
initrd.bin: kernel
	mkdir initrd initrd/sys
	cp ../kernel/$(ARCH)_kernel.elf initrd/sys/core
	cd initrd && (find . | cpio -H hpodc -o | gzip > ../initrd.bin) && cd ..
	rm -r initrd

# assemble the boot partition
bootpart.bin: initrd.bin
	dd if=/dev/zero of=bootpart.bin bs=1024 count=$(BOOTSIZE)
	mkfs.vfat -F $(BOOTTYPE) -n "EFI System" bootpart.bin
	mkdir boot
	sudo /bin/mount -t vfat bootpart.bin boot -o rw,uid=1000,gid=1000
	mkdir boot/BOOTBOOT
	cp ../bootboot/bootboot.bin boot/BOOTBOOT/LOADER
	mkdir boot/EFI boot/EFI/BOOT
	cp ../bootboot/bootboot.efi boot/EFI/BOOT/BOOTX64.EFI

	/bin/echo -e "screen=800x600\nkernel=sys/core\n" >boot/BOOTBOOT/CONFIG
	cp initrd.bin boot/BOOTBOOT/INITRD
	sudo /bin/umount -f boot
	rm -r boot

# create hybrid disk / cdrom image or ROM image
disk: mkimg bootpart.bin
	./mkimg $(DISKSIZE) $(DISK)

initrd.rom: mkimg initrd.bin
	./mkimg rom

# test the disk image
rom: initrd.rom
	qemu-system-x86_64 -option-rom ../bootboot/bootboot.bin -option-rom initrd.rom -serial stdio

kernel:
	cd ../kernel && $(MAKE)

clean-kernel:
	cd ../kernel && $(MAKE) clean

efi: disk
	qemu-system-x86_64 -bios $(OVMF) -m 64 -drive file=$(DISK),format=raw -serial stdio

efi-debug: disk
	qemu-system-x86_64 -s -S -bios $(OVMF) -m 64 -drive file=$(DISK),format=raw -serial stdio

# clean up
clean: clean-kernel
	rm -f mkimg *.bin *.img *.rom
