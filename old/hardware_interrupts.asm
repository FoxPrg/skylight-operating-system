[bits 32]
[extern FinalHardwareInterruptHandler]

%macro set_hardware_interrupt_handler	1
[global HardwareInterruptHandler%+%1]
HardwareInterruptHandler%+%1:
	push byte 0
	push %1+32
	jmp HardwareInterruptCommonHandler
%endmacro

set_hardware_interrupt_handler	0
set_hardware_interrupt_handler	1
set_hardware_interrupt_handler	2
set_hardware_interrupt_handler	3
set_hardware_interrupt_handler	4
set_hardware_interrupt_handler	5
set_hardware_interrupt_handler	6
set_hardware_interrupt_handler	7
set_hardware_interrupt_handler	8
set_hardware_interrupt_handler	9
set_hardware_interrupt_handler	10
set_hardware_interrupt_handler	11
set_hardware_interrupt_handler	12
set_hardware_interrupt_handler	13
set_hardware_interrupt_handler	14
set_hardware_interrupt_handler	15

HardwareInterruptCommonHandler:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp
	call FinalHardwareInterruptHandler
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret