#ifndef GDT_H
#define GDT_H

#include "typedefs.h"

#define GDT_ACCESS_READ_WRITE	0x02
#define GDT_ACCESS_DIRECTION	0x04
#define GDT_ACCESS_EXECUTABLE	0x08
#define GDT_ACCESS_SYSTEM		0x10
#define GDT_ACCESS_KERNEL		0x00
#define GDT_ACCESS_USER			0x60
#define GDT_ACCESS_PRESENT		0x80

#define GDT_FLAG_LONG_MODE		0x02
#define GDT_FLAG_REAL_MODE		0x00
#define GDT_FLAG_PROTECTED_MODE	0x04
#define GDT_FLAG_GRANULARITY	0x08

typedef struct DeclareAttribute(packed) {
	WORD	Size;
	DWORD	Offset;
} GLOBAL_DESCRIPTOR_TABLE_REGISTER, *PGLOBAL_DESCRIPTOR_TABLE_REGISTER;

typedef struct DeclareAttribute(packed) {
	WORD	LimitLow;
	DWORD32	BaseLow		:24;
	BYTE	Access;
	BYTE	LimitHigh	:4;
	BYTE	Flags		:4;
	BYTE	BaseHigh;
} GLOBAL_DESCRIPTOR_TABLE_ENTRY, *PGLOBAL_DESCRIPTOR_TABLE_ENTRY;

VOID InitializeGdtEntry(
	PGLOBAL_DESCRIPTOR_TABLE_ENTRY pEntry,
	DWORD32 dwLimit,
	DWORD32 dwBase,
	BYTE bAccess,
	BYTE bFlags
);

VOID InitializeGdtRegister(
	PGLOBAL_DESCRIPTOR_TABLE_REGISTER pRegister,
	PGLOBAL_DESCRIPTOR_TABLE_ENTRY pTable,
	SIZE_T szLength
);

VOID LoadGdtRegister(
	PGLOBAL_DESCRIPTOR_TABLE_REGISTER pRegister
);

#endif