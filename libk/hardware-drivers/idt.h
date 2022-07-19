#ifndef IDT_H
#define IDT_H

#include "../common/typedefs.h"

#define IDT_GATE_TASK	0x05
#define IDT_GATE_INT16	0x06
#define IDT_GATE_TRAP16	0x07
#define IDT_GATE_INT32	0x0e
#define IDT_GATE_TRAP32	0x0f

#define IDT_USER		0x60
#define IDT_PRESENT		0x80

typedef struct PACKED {
	uint16_t	BaseLow;
	uint16_t	CodeSegment;
	uint8_t		Reserved;
	uint8_t		Flags;
	uint16_t	BaseHigh;
} IDT_ENTRY, *PIDT_ENTRY;

typedef struct PACKED {
	uint16_t	Size;
	PIDT_ENTRY	Table;
} IDT_REGISTER, *PIDT_REGISTER;

void SetIDTEntry(PIDT_ENTRY Table, size_t Index, uint32_t Base, uint16_t CodeSegment, uint8_t Flags);
void SetIDTRegister(PIDT_REGISTER Register, PIDT_ENTRY Table, size_t EntriesCount);
void LoadIDTRegister(PIDT_REGISTER Register);

#endif