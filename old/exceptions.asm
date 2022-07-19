[bits 32]
[extern FinalExceptionHandler]

%macro set_exception_handler_no_error	1
[global ExceptionHandler%+%1]
ExceptionHandler%+%1:
	push byte 0
	push %1
	jmp ExceptionCommonHandler
%endmacro
%macro set_exception_handler_error	1
[global ExceptionHandler%+%1]
ExceptionHandler%+%1:
	push %1
	jmp ExceptionCommonHandler
%endmacro

set_exception_handler_no_error	0
set_exception_handler_no_error	1
set_exception_handler_no_error	2
set_exception_handler_no_error	3
set_exception_handler_no_error	4
set_exception_handler_no_error	5
set_exception_handler_no_error	6
set_exception_handler_no_error	7
set_exception_handler_error	8
set_exception_handler_no_error	9
set_exception_handler_error	10
set_exception_handler_error	11
set_exception_handler_error	12
set_exception_handler_error	13
set_exception_handler_error	14
set_exception_handler_no_error	15
set_exception_handler_no_error	16
set_exception_handler_error	17
set_exception_handler_no_error	18
set_exception_handler_no_error	19
set_exception_handler_no_error	20
set_exception_handler_error	21
set_exception_handler_no_error	22
set_exception_handler_no_error	23
set_exception_handler_no_error	24
set_exception_handler_no_error	25
set_exception_handler_no_error	26
set_exception_handler_no_error	27
set_exception_handler_no_error	28
set_exception_handler_error	29
set_exception_handler_error	30
set_exception_handler_no_error	31

ExceptionCommonHandler:
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
	call FinalExceptionHandler
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret