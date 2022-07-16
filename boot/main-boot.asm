[bits 16]
[org 0xa00]

_start:
	call cpu_enable_a20_line
	call cpu_switch_big_unreal_mode

	mov ax, 0x0001
	mov cx, 0x0002 + ((_end - _start + 511) & ~511) / 512
	mov dh, 0x00
	mov bx, _end
	call disk_read_sectors									;	read kernel header:	0x00 - entry,	0x04 - size

	push edx
	push ebx
	mov eax, [_end + 4]
	mov ebx, 0x00000200
	call memory_align_address

	mov edx, 0x00000000
	div ebx
	pop ebx
	pop edx

	call disk_read_sectors

	push word [_end+5]
	pop es
	mov di, [_end+4]
	add di, _end
	call memory_get_map

	and edi, 0x0000ffff
	mov ax, di
	push es
	pop di
	shl edi, 4
	add di, ax
	and ecx, 0x000000ff
	and esi, 0x0000ffff

	mov eax, _jumping_to_kernel
	mov [cpu_switch_protected_mode_address], eax
	call cpu_switch_protected_mode

_jumping_to_kernel:
	[bits 32]
	push ecx				;	size of entry
	push esi				;	entries count
	push edi				;	address of map
	call [_end]
	jmp $
	[bits 16]


%include "cpu.asm"
%include "disk.asm"
%include "memory.asm"

times 512 - $ + $$ db 0
_end: