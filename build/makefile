asm=nasm
c=$(target)-elf-gcc
emu=qemu-system-x86_64
out=skylight.bin

c-sources=$(shell find ../libk -name "*.c") $(shell find ../libk -name "*.c")
asm-sources=$(shell find ../libk -name "*.asm") $(shell find ../libk -name "*.asm")
c-objects=$(c-sources:.c=-c.o)
asm-objects=$(asm-sources:.asm=-asm.o)

compile-flags=-std=c++17 -m32 -ffreestanding -nostdlib -O0 -Wall -Wextra -fno-exceptions -fno-rtti -I ../libk/
link-flags=-m32 -ffreestanding -O0 -nostdlib -T link.ld -march=$(target)
run-flags=-drive format=raw,file=bin/$(out) -m 2G -monitor stdio -d cpu_reset -D dbg.txt -accel hax

all:
	$(MAKE) build
	$(MAKE) run
	$(MAKE) clean

build:							# make build target=i686
	$(MAKE) $(asm-objects)
	$(MAKE) $(c-objects)
	$(MAKE) kernel
	$(MAKE) boot

%-c.o:	%.c
	$(c) -c $< $(compile-flags) -o $@

%-asm.o:	%.asm
	$(asm) -felf32 $< -o $@

kernel:	$(c-objects) $(asm-objects)
	$(c) $^ $(link-flags) -o bin/$@.bin

boot:
	$(asm) -i../boot/ -fbin ../boot/main-boot.asm -o ../boot/main-boot.bin
	$(asm) -i../boot/ -fbin ../boot/pre-boot.asm -o bin/$(out)

run:
	$(emu) $(run-flags)

clean:
	rm -rf dbg.txt ../**/*.bin  ./**/*.bin *.bin $(c-objects) $(asm-objects)