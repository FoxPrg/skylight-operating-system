asm=nasm
cpp=$(target)-elf-g++
emu=qemu-system-x86_64
out=skylight.bin

cpp-sources=$(shell find ../drivers -name "*.cpp") $(shell find ../kernel -name "*.cpp")
asm-sources=$(shell find ../drivers -name "*.asm") $(shell find ../kernel -name "*.asm")
cpp-objects=$(cpp-sources:.cpp=-cpp.o)
asm-objects=$(asm-sources:.asm=-asm.o)

compile-flags=-std=c++17 -m32 -ffreestanding -nostdlib -O0 -Wall -Wextra -fno-exceptions -fno-rtti -I ../
link-flags=-m32 -ffreestanding -O0 -nostdlib -T link.ld -march=$(target)
run-flags=-drive format=raw,file=bin/$(out) -m 2G -monitor stdio

all:
	$(MAKE) $(asm-objects)
	$(MAKE) $(cpp-objects)
	$(MAKE) kernel
	$(MAKE) boot
	$(MAKE) run
	$(MAKE) clean

%-cpp.o:	%.cpp
	$(cpp) -c $< $(compile-flags) -o $@

%-asm.o:	%.asm
	$(asm) -felf32 $< -o $@

kernel:	$(cpp-objects) $(asm-objects)
	$(cpp) $^ $(link-flags) -o bin/$@.bin

boot:
	$(asm) -i../boot/ -fbin ../boot/main-boot.asm -o ../boot/main-boot.bin
	$(asm) -i../boot/ -fbin ../boot/pre-boot.asm -o bin/$(out)

run:
	$(emu) $(run-flags)

clean:
	rm -rf ../**/*.bin  ./**/*.bin *.bin $(cpp-objects) $(asm-objects) 