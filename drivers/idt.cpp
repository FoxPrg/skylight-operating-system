#include "idt.h"

InterruptDescriptorTableRegister_t idtSelectedRegister;
PInterruptDescriptorTableEntry_t idtSelectedTable;
size_t idtSelectedLength;

void SelectIdt(
	PInterruptDescriptorTableEntry_t pInterruptDescriptorTable,
	size_t length
) {
	idtSelectedRegister.Offset = (size_t)pInterruptDescriptorTable;
	idtSelectedRegister.Size = length * sizeof(InterruptDescriptorTableEntry_t) - 1;
	idtSelectedTable = pInterruptDescriptorTable;
	idtSelectedLength = length;
}

void InitializeIdtEntry(
	size_t index,
	void (*dispatcher)(),
	word_t segmentSelector,
	byte_t flags
) {
	idtSelectedTable[index].OffsetLow = (word_t)((size_t)dispatcher & 0xffff);
	idtSelectedTable[index].SegmentSelector = segmentSelector;
	idtSelectedTable[index].Reserved = 0;
	idtSelectedTable[index].Flags = flags;
	idtSelectedTable[index].OffsetHigh = (word_t)(((size_t)dispatcher >> 16) & 0xffff);
}