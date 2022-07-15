cpu_enable_a20_line:
	push ax
	push bx
	mov ax, 0x2403
	int 0x15
	jc cpu_enable_a20_line_end
	mov ax, 0x2401
	int 0x15
cpu_enable_a20_line_end:
	pop bx
	pop ax
	ret

cpu_switch_big_unreal_mode:
	push eax
	push bx
	cli
	push ds
	lgdt [__gdt_unreal]
	mov eax, cr0
	or al, 1
	mov cr0, eax
	jmp $+2
	mov bx, 0x08
	mov ds, bx
	and al, 0xfe
	mov cr0, eax
	pop ds
	sti
	pop bx
	pop eax
	ret

cpu_switch_protected_mode:
	cli
	lgdt [__gdt_protected]
	mov eax, cr0
	or al, 1
	mov cr0, eax
	jmp __gdt_protected_code-__gdt_protected_null:cpu_switch_protected_mode_switched
cpu_switch_protected_mode_switched:
	[bits 32]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp [cpu_switch_protected_mode_address]
	[bits 16]
cpu_switch_protected_mode_address:	dd 0

__gdt_unreal:
	dw __gdt_unreal_end - __gdt_unreal_null - 1
	dd __gdt_unreal_null
	__gdt_unreal_null:	dq 0
	__gdt_unreal_data:	dq 0xcf92000000ffff
	__gdt_unreal_end:

__gdt_protected:
	dw __gdt_protected_end - __gdt_protected_null - 1
	dd __gdt_protected_null
	__gdt_protected_null:	dq 0
	__gdt_protected_code:	dq 0xcf9a000000ffff
	__gdt_protected_data:	dq 0xcf92000000ffff
	__gdt_protected_end: