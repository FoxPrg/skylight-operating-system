#ifndef IDT_H
#define IDT_H

#include "typedefs.h"

#define IDT_FLAG_GATE_TASK		0x05
#define IDT_FLAG_GATE_INT16		0x06
#define IDT_FLAG_GATE_TRAP16	0x07
#define IDT_FLAG_GATE_INT32		0x0e
#define IDT_FLAG_GATE_TRAP32	0x0f

#define IDT_FLAG_DPL_KERNEL		0x00
#define IDT_FLAG_DPL_USER		0x60
#define IDT_FLAG_PRESENT		0x80

typedef struct DeclareAttribute(packed) {
	word_t	Size;
	dword_t	Offset;
} InterruptDescriptorTableRegister_t, *PInterruptDescriptorTableRegister_t;

typedef struct DeclareAttribute(packed) {
	word_t	OffsetLow;
	word_t	SegmentSelector;
	byte_t	Reserved;
	byte_t	Flags;
	word_t	OffsetHigh;
} InterruptDescriptorTableEntry_t, *PInterruptDescriptorTableEntry_t;

typedef struct DeclareAttribute(packed) {
	dword_t	GSegment;
	dword_t	FSegment;
	dword_t	ExtendedSegment;
	dword_t	DataSegment;
	dword_t	DestinationIndex;
	dword_t	SourceIndex;
	dword_t	BasePointer;
	dword_t	StackPointer;			//	Read-only!
	dword_t	BaseRegister;
	dword_t	DataRegister;
	dword_t	CountRegister;
	dword_t	AccumulatorRegister;
	dword_t	InterruptIndex;
	dword_t	ErrorCode;
	dword_t	InstructionPointer;
	dword_t	CodeSegment;
	dword_t	FlagsRegister;
	dword_t	UserStackPointer;
	dword_t	UserStackSelector;
} InterruptHandlerRegisters_t, *PInterruptHandlerRegisters_t;
typedef void (*InterruptHandler_t)(PInterruptHandlerRegisters_t);

extern InterruptDescriptorTableRegister_t idtSelectedRegister;
extern PInterruptDescriptorTableEntry_t idtSelectedTable;
extern size_t idtSelectedLength;

void SelectIdt(
	PInterruptDescriptorTableEntry_t pInterruptDescriptorTable,
	size_t length
);

void InitializeIdtEntry(
	size_t index,
	void (*dispatcher)(),
	word_t segmentSelector,
	byte_t flags
);

#define LoadIdt()	DeclareAssembly("lidt %0"::"m"(idtSelectedRegister))

#endif