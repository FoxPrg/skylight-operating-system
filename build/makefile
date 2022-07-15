target=i386
asm=nasm
cpp=$(target)-elf-g++
emu=qemu-system-$(target)
out=skylight.bin

cpp-sources=$(shell find ../source -name "*.cpp")
asm-sources=$(shell find ../source -name "*.asm")
cpp-objects=$(cpp-sources:.cpp=-cpp.o)
asm-objects=$(asm-sources:.asm=-asm.o)

compile-flags=-std=c++17 -m32 -ffreestanding -nostdlib -O0 -Wall -Wextra -fno-exceptions -fno-rtti -I ../include
link-flags=-m32 -ffreestanding -O0 -nostdlib -T $(target)/link.ld
run-flags=-drive format=raw,file=$(target)/$(out) -m 2G -monitor stdio

all:
	@if [ "$(strip $(asm-sources))" != "" ];\
	then $(MAKE) $(asm-objects);\
	fi
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
	$(cpp) $^ $(link-flags) -o $(target)/$@.bin

boot:
	$(asm) -fbin ../boot/main-boot.asm -o $(target)/main-boot.bin
	$(asm) -fbin ../boot/pre-boot.asm -o $(target)/$(out)

run:
	$(emu) $(run-flags)

clean:
	rm -rf *.bin **/*.bin $(cpp-objects) $(asm-objects)