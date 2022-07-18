#ifndef MEMORY_H
#define MEMORY_H

#include "typedefs.h"

#define MEMORY_DESCRIPTOR_TYPE_USABLE		1
#define MEMORY_DESCRIPTOR_TYPE_RESERVED		2
#define MEMORY_DESCRIPTOR_TYPE_RECLAIMABLE	3
#define MEMORY_DESCRIPTOR_TYPE_NVS			4
#define MEMORY_DESCRIPTOR_TYPE_BAD			5

#define MEMORY_EXTENDED_FLAGS_USABLE		1

typedef struct DeclareAttribute(packed) {
	qword_t	Address;
	qword_t	Length;
	dword_t	Type;
} MemoryDescriptor_t, *PMemoryDescriptor_t;

class Memory {
	public:
	static void Select(PMemoryDescriptor_t table, size_t count);
	static void Exclude(size_t start, size_t length);
	static size_t GetDescriptorsCount();
	static PMemoryDescriptor_t GetDescriptor(size_t index);
	static void Copy(void *destination, const void *source, size_t count);
	static void Set(void *destination, const byte_t value, size_t count);
	private:
	static PMemoryDescriptor_t m_table;
	static size_t m_count;
};

#endif