#ifndef MEMORY_H
#define MEMORY_H

#include "typedefs.h"

#define MEMORY_REGION_TYPE_USABLE		1
#define MEMORY_REGION_TYPE_RESERVED		2
#define MEMORY_REGION_TYPE_RECLAIMABLE	3
#define MEMORY_REGION_TYPE_NVS			4
#define MEMORY_REGION_TYPE_BAD			5
#define MEMORY_REGION_MINIMAL_SIZE		(MEMORY_FRAME_SIZE + sizeof(FrameDescriptor_t))
#define MEMORY_FRAME_SIZE				0x1000
#define MEMORY_FRAME_ATTRIBUTE_BUSY		1

typedef struct DeclareAttribute(packed) {
	qword_t	Address;
	qword_t	Length;
	dword_t	Type;
} MemoryRegion_t, *PMemoryRegion_t;

typedef struct {
	size_t	Address;
	dword_t	Attributes;
	size_t	Count;
} FrameDescriptor_t, *PFrameDescriptor_t;

class Memory {
	public:
	static void Select(PMemoryRegion_t table, size_t count);
	static void Exclude(size_t start, size_t length);
	static void RemoveByIndex(size_t index);
	static void Initialize();

	static void* Allocate(size_t count);
	static bool Free(void *memory);

	static size_t GetRegionsCount();
	static PMemoryRegion_t GetRegion(size_t index);

	static void Copy(void *destination, const void *source, size_t count);
	static void Set(void *destination, const byte_t value, size_t count);
	private:
	static PMemoryRegion_t m_table;
	static size_t m_count;
};

#endif