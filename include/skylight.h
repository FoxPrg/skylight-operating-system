#ifndef SKYLIGHT_H
#define SKYLIGHT_H

#include <gdt.h>
#include <idt.h>
#include <pic.h>

#define KERNEL_CODE_SEGMENT		0x08

typedef struct DeclareAttribute(packed) {
	DWORD	GSegment;
	DWORD	FSegment;
	DWORD	ExtendedSegment;
	DWORD	DataSegment;
	DWORD	DestinationIndex;
	DWORD	SourceIndex;
	DWORD	BasePointer;
	DWORD	StackPointer;			//	Read-only!
	DWORD	BaseRegister;
	DWORD	DataRegister;
	DWORD	CountRegister;
	DWORD	AccumulatorRegister;
	DWORD	InterruptIndex;
	DWORD	ErrorCode;
	DWORD	InstructionPointer;
	DWORD	CodeSegment;
	DWORD	FlagsRegister;
	DWORD	UserStackPointer;
	DWORD	UserStackSelector;
} CPU_REQUEST_REGISTERS, *PCPU_REQUEST_REGISTERS;

EXTERN_C {
	VOID CpuExceptionStub0();
	VOID CpuExceptionStub1();
	VOID CpuExceptionStub2();
	VOID CpuExceptionStub3();
	VOID CpuExceptionStub4();
	VOID CpuExceptionStub5();
	VOID CpuExceptionStub6();
	VOID CpuExceptionStub7();
	VOID CpuExceptionStub8();
	VOID CpuExceptionStub9();
	VOID CpuExceptionStub10();
	VOID CpuExceptionStub11();
	VOID CpuExceptionStub12();
	VOID CpuExceptionStub13();
	VOID CpuExceptionStub14();
	VOID CpuExceptionStub15();
	VOID CpuExceptionStub16();
	VOID CpuExceptionStub17();
	VOID CpuExceptionStub18();
	VOID CpuExceptionStub19();
	VOID CpuExceptionStub20();
	VOID CpuExceptionStub21();
	VOID CpuExceptionStub22();
	VOID CpuExceptionStub23();
	VOID CpuExceptionStub24();
	VOID CpuExceptionStub25();
	VOID CpuExceptionStub26();
	VOID CpuExceptionStub27();
	VOID CpuExceptionStub28();
	VOID CpuExceptionStub29();
	VOID CpuExceptionStub30();
	VOID CpuExceptionStub31();

	VOID CpuHardwareInterruptRequestStub0();
	VOID CpuHardwareInterruptRequestStub1();
	VOID CpuHardwareInterruptRequestStub2();
	VOID CpuHardwareInterruptRequestStub3();
	VOID CpuHardwareInterruptRequestStub4();
	VOID CpuHardwareInterruptRequestStub5();
	VOID CpuHardwareInterruptRequestStub6();
	VOID CpuHardwareInterruptRequestStub7();
	VOID CpuHardwareInterruptRequestStub8();
	VOID CpuHardwareInterruptRequestStub9();
	VOID CpuHardwareInterruptRequestStub10();
	VOID CpuHardwareInterruptRequestStub11();
	VOID CpuHardwareInterruptRequestStub12();
	VOID CpuHardwareInterruptRequestStub13();
	VOID CpuHardwareInterruptRequestStub14();
	VOID CpuHardwareInterruptRequestStub15();
};

#endif