#include "gdt.h"

VOID InitializeGdtEntry(
	PGLOBAL_DESCRIPTOR_TABLE_ENTRY pEntry,
	DWORD32 dwLimit,
	DWORD32 dwBase,
	BYTE bAccess,
	BYTE bFlags
) {
	pEntry->LimitLow = (WORD)((SIZE_T)dwLimit & 0xffff);
	pEntry->BaseLow = (DWORD32)((SIZE_T)dwBase & 0xffffff);
	pEntry->Access = bAccess;
	pEntry->LimitHigh = (BYTE)((SIZE_T)dwLimit >> 16) & 0x0f;
	pEntry->Flags = bFlags;
	pEntry->BaseHigh = (BYTE)((dwBase >> 24) & 0xff);
}

VOID InitializeGdtRegister(
	PGLOBAL_DESCRIPTOR_TABLE_REGISTER pRegister,
	PGLOBAL_DESCRIPTOR_TABLE_ENTRY pTable,
	SIZE_T szLength
) {
	pRegister->Size = sizeof(GLOBAL_DESCRIPTOR_TABLE_ENTRY) * szLength - 1;
	pRegister->Offset = (DWORD)pTable;
}

VOID LoadGdtRegister(
	PGLOBAL_DESCRIPTOR_TABLE_REGISTER pRegister
) {
	DeclareAssembly("lgdt %0"::"m"(*pRegister));
}