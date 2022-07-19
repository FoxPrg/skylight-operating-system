#include "idt.h"

void SetIDTEntry(PIDT_ENTRY Table, size_t Index, uint32_t Base, uint16_t CodeSegment, uint8_t Flags) {
	Table[Index].BaseLow = (uint16_t)(Base & 0xffff);
	Table[Index].CodeSegment = CodeSegment;
	Table[Index].Reserved = 0;
	Table[Index].Flags = Flags;
	Table[Index].BaseHigh = (uint16_t)((Base >> 16) & 0xffff);
}

void SetIDTRegister(PIDT_REGISTER Register, PIDT_ENTRY Table, size_t EntriesCount) {
	Register->Size = EntriesCount * sizeof(IDT_ENTRY) - 1;
	Register->Table = Table;
}

void LoadIDTRegister(PIDT_REGISTER Register) {
	ASSEMBLY("lidt %0"::"m"(*Register));
}