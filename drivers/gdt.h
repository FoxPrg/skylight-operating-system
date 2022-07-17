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
	word_t	Size;
	dword_t	Offset;
} GlobalDescriptorTableRegister_t, *PGlobalDescriptorTableRegister_t;

typedef struct DeclareAttribute(packed) {
	word_t	LimitLow;
	dword_t	BaseLow		:24;
	byte_t	Access;
	byte_t	LimitHigh	:4;
	byte_t	Flags		:4;
	byte_t	BaseHigh;
} GlobalDescriptorTableEntry_t, *PGlobalDescriptorTableEntry_t;

class GlobalDescriptorTableManager {
	public:
	static void Select(PGlobalDescriptorTableEntry_t table, size_t length);
	static void SetEntry(size_t index, dword_t limit, dword_t base, byte_t access, byte_t flags);
	static void Load();
	private:
	static GlobalDescriptorTableRegister_t m_register;
	static PGlobalDescriptorTableEntry_t m_table;
	static size_t m_length;
};

#endif