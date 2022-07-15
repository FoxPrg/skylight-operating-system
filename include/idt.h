#ifndef IDT_H
#define IDT_H

#include <typedefs.h>

#define IDT_FLAG_GATE_TASK		0x05
#define IDT_FLAG_GATE_INT16		0x06
#define IDT_FLAG_GATE_TRAP16	0x07
#define IDT_FLAG_GATE_INT32		0x0e
#define IDT_FLAG_GATE_TRAP32	0x0f

#define IDT_FLAG_DPL_KERNEL		0x00
#define IDT_FLAG_DPL_USER		0x60
#define IDT_FLAG_PRESENT		0x80

typedef struct DeclareAttribute(packed) {
	WORD	Size;
	DWORD	Offset;
} INTERRUPT_DESCRIPTOR_TABLE_REGISTER, *PINTERRUPT_DESCRIPTOR_TABLE_REGISTER;

typedef struct DeclareAttribute(packed) {
	WORD	OffsetLow;
	WORD	SegmentSelector;
	BYTE	Reserved;
	BYTE	Flags;
	WORD	OffsetHigh;
} INTERRUPT_DESCRIPTOR_TABLE_ENTRY, *PINTERRUPT_DESCRIPTOR_TABLE_ENTRY;

VOID InitializeIdtEntry(
	PINTERRUPT_DESCRIPTOR_TABLE_ENTRY pEntry,
	SIZE_T szOffset,
	WORD wSegSel,
	BYTE bFlags
);

VOID InitializeIdtRegister(
	PINTERRUPT_DESCRIPTOR_TABLE_REGISTER pRegister,
	PINTERRUPT_DESCRIPTOR_TABLE_ENTRY pTable,
	SIZE_T szLength
);

VOID LoadIdtRegister(
	PINTERRUPT_DESCRIPTOR_TABLE_REGISTER pRegister
);

#endif