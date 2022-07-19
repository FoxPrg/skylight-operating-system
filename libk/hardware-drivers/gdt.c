#include "gdt.h"

void SetGDTEntry(PGDT_ENTRY Table, size_t Index, uint32_t Limit, uint32_t Base, uint8_t Access, uint8_t Flags) {
	Table[Index].LimitLow = (uint16_t)((size_t)Limit & 0xffff);
	Table[Index].BaseLow = (uint32_t)((size_t)Base & 0xffffff);
	Table[Index].Access = Access;
	Table[Index].LimitHigh = (uint8_t)((size_t)Limit >> 16) & 0x0f;
	Table[Index].Flags = Flags;
	Table[Index].BaseHigh = (uint8_t)((Base >> 24) & 0xff);
}

void SetGDTRegister(PGDT_REGISTER Register, PGDT_ENTRY Table, size_t EntriesCount) {
	Register->Size = EntriesCount * sizeof(GDT_ENTRY) - 1;
	Register->Table = Table;
}

void LoadGDTRegister(PGDT_REGISTER Register) {
	ASSEMBLY("lgdt %0"::"m"(*Register));
}