#ifndef GDT_H
#define GDT_H

#include "../common/typedefs.h"

#define GDT_ACCESS_ACCESSED		0x01
#define GDT_ACCESS_READ_WRITE	0x02
#define GDT_ACCESS_CONFIRMING	0x04
#define GDT_ACCESS_EXECUTABLE	0x08
#define GDT_ACCESS_NOT_SYSTEM	0x10
#define GDT_ACCESS_USER			0x60
#define GDT_ACCESS_PRESENT		0x80

#define GDT_FLAG_LONG_MODE		0x02
#define GDT_FLAG_PROTECTED_MODE	0x04
#define GDT_FLAG_GRANULARITY	0x08

typedef struct PACKED {
	uint16_t	LimitLow;
	uint32_t	BaseLow		:24;
	uint8_t		Access;
	uint8_t		LimitHigh	:4;
	uint8_t		Flags		:4;
	uint8_t		BaseHigh;
} GDT_ENTRY, *PGDT_ENTRY;

typedef struct PACKED {
	uint16_t	Size;
	PGDT_ENTRY	Table;
} GDT_REGISTER, *PGDT_REGISTER;

void SetGDTEntry(PGDT_ENTRY Table, size_t Index, uint32_t Limit, uint32_t Base, uint8_t Access, uint8_t Flags);
void SetGDTRegister(PGDT_REGISTER Register, PGDT_ENTRY Table, size_t EntriesCount);
void LoadGDTRegister(PGDT_REGISTER Register);

#endif