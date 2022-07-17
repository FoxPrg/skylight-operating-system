#include "gdt.h"

GlobalDescriptorTableRegister_t gdtSelectedRegister;
PGlobalDescriptorTableEntry_t gdtSelectedTable;
size_t gdtSelectedLength;

void SelectGdt(
	PGlobalDescriptorTableEntry_t pGlobalDescriptorTableEntry,
	size_t length
) {
	gdtSelectedRegister.Size = sizeof(GlobalDescriptorTableEntry_t) * length - 1;
	gdtSelectedRegister.Offset = (dword_t)pGlobalDescriptorTableEntry;
	gdtSelectedTable = pGlobalDescriptorTableEntry;
	gdtSelectedLength = length;
}

void InitializeGdtEntry(
	size_t index,
	dword_t limit,
	dword_t base,
	byte_t access,
	byte_t flags
) {
	gdtSelectedTable[index].LimitLow = (word_t)((size_t)limit & 0xffff);
	gdtSelectedTable[index].BaseLow = (dword_t)((size_t)base & 0xffffff);
	gdtSelectedTable[index].Access = access;
	gdtSelectedTable[index].LimitHigh = (byte_t)((size_t)limit >> 16) & 0x0f;
	gdtSelectedTable[index].Flags = flags;
	gdtSelectedTable[index].BaseHigh = (byte_t)((base >> 24) & 0xff);
}