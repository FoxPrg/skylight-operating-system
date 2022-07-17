[bits 16]
[org 0x7c00]

%define MAIN_BOOT_ADDRESS	0x0a00

_start:
	jmp 0x0000:_entry		;	load real mode code segment
_entry:
	cli						;	disable hardware interrupts
	mov ax, 0x0000			;	load real mode segment registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov bp, 0x7c00			;	load stack top and base pointer
	mov sp, bp
	sti						;	enable hardware interrupts
	cld						;	clear direction flag
_main:
	mov ax, 0x0003			;	set default video mode
	int 0x10

	mov ax, 0x1003			;	disable blinking bit
	mov bx, 0x0000
	int 0x10

	mov ah, 0x01			;	disable cursor
	mov ch, 0x3f
	int 0x10

	mov ax, 0x0200 + ((_main_boot_end - _main_boot_start + 511) & ~511) / 512
	mov cx, 0x0002
	mov dh, 0x00
	mov bx, MAIN_BOOT_ADDRESS
	int 0x13

	mov bp, MAIN_BOOT_ADDRESS
	mov sp, bp
	jnc MAIN_BOOT_ADDRESS
	int 0x19
	jmp $

times 0x1fe - $ + $$ db 0
dw 0xaa55

_main_boot_start:
incbin "main-boot.bin"
_main_boot_end:

_kernel_start:
incbin "../build/bin/kernel.bin"
_kernel_end: