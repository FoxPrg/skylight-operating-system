[bits 32]
[extern CpuExceptionHandler]
[extern CpuHardwareInterruptRequestHandler]

%macro set_cpu_exception_stub_no_error	1
[global CpuExceptionStub%+%1]
CpuExceptionStub%+%1:
	push byte 0
	push %1
	jmp CpuCommonExceptionStub
%endmacro
%macro set_cpu_exception_stub_error	1
[global CpuExceptionStub%+%1]
CpuExceptionStub%+%1:
	push %1
	jmp CpuCommonExceptionStub
%endmacro
%macro set_cpu_interrupt_request_stub	1
[global CpuHardwareInterruptRequestStub%+%1]
CpuHardwareInterruptRequestStub%+%1:
	push byte 0
	push %1+32
	jmp CpuCommonHardwareInterruptRequestStub
%endmacro

set_cpu_exception_stub_no_error	0
set_cpu_exception_stub_no_error	1
set_cpu_exception_stub_no_error	2
set_cpu_exception_stub_no_error	3
set_cpu_exception_stub_no_error	4
set_cpu_exception_stub_no_error	5
set_cpu_exception_stub_no_error	6
set_cpu_exception_stub_no_error	7
set_cpu_exception_stub_error	8
set_cpu_exception_stub_no_error	9
set_cpu_exception_stub_error	10
set_cpu_exception_stub_error	11
set_cpu_exception_stub_error	12
set_cpu_exception_stub_error	13
set_cpu_exception_stub_error	14
set_cpu_exception_stub_no_error	15
set_cpu_exception_stub_no_error	16
set_cpu_exception_stub_error	17
set_cpu_exception_stub_no_error	18
set_cpu_exception_stub_no_error	19
set_cpu_exception_stub_no_error	20
set_cpu_exception_stub_error	21
set_cpu_exception_stub_no_error	22
set_cpu_exception_stub_no_error	23
set_cpu_exception_stub_no_error	24
set_cpu_exception_stub_no_error	25
set_cpu_exception_stub_no_error	26
set_cpu_exception_stub_no_error	27
set_cpu_exception_stub_no_error	28
set_cpu_exception_stub_error	29
set_cpu_exception_stub_error	30
set_cpu_exception_stub_no_error	31

set_cpu_interrupt_request_stub	0
set_cpu_interrupt_request_stub	1
set_cpu_interrupt_request_stub	2
set_cpu_interrupt_request_stub	3
set_cpu_interrupt_request_stub	4
set_cpu_interrupt_request_stub	5
set_cpu_interrupt_request_stub	6
set_cpu_interrupt_request_stub	7
set_cpu_interrupt_request_stub	8
set_cpu_interrupt_request_stub	9
set_cpu_interrupt_request_stub	10
set_cpu_interrupt_request_stub	11
set_cpu_interrupt_request_stub	12
set_cpu_interrupt_request_stub	13
set_cpu_interrupt_request_stub	14
set_cpu_interrupt_request_stub	15

CpuCommonExceptionStub:
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
	call CpuExceptionHandler
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

CpuCommonHardwareInterruptRequestStub:
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
	call CpuHardwareInterruptRequestHandler
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret