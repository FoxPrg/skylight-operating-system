#include "idt.h"

VOID InitializeIdtEntry(
	PINTERRUPT_DESCRIPTOR_TABLE_ENTRY pEntry,
	SIZE_T szOffset,
	WORD wSegSel,
	BYTE bFlags
) {
	pEntry->OffsetLow = (WORD)((SIZE_T)szOffset & 0xffff);
	pEntry->SegmentSelector = wSegSel;
	pEntry->Reserved = 0;
	pEntry->Flags = bFlags;
	pEntry->OffsetHigh = (WORD)(((SIZE_T)szOffset >> 16) & 0xffff);
}

VOID InitializeIdtRegister(
	PINTERRUPT_DESCRIPTOR_TABLE_REGISTER pRegister,
	PINTERRUPT_DESCRIPTOR_TABLE_ENTRY pTable,
	SIZE_T szLength
) {
	pRegister->Size = sizeof(INTERRUPT_DESCRIPTOR_TABLE_ENTRY) * szLength - 1;
	pRegister->Offset = (DWORD)pTable;
}

VOID LoadIdtRegister(
	PINTERRUPT_DESCRIPTOR_TABLE_REGISTER pRegister
) {
	DeclareAssembly("lidt %0"::"m"(*pRegister));
}