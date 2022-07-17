#include "memory.h"

PMemoryDescriptor_t Memory::m_table;
size_t Memory::m_descriptorSize;
size_t Memory::m_count;

void Memory::Select(PMemoryDescriptor_t table, size_t descriptorSize, size_t count) {
	m_table = table;
	m_descriptorSize = descriptorSize;
	m_count = count;
}

void Memory::Exclude(size_t start, size_t length) {
	const size_t ex_end = start + length;
	size_t end;
	PMemoryDescriptor_t pointer = (PMemoryDescriptor_t)&m_table[0], pAdditional;
	for (size_t i = 0; i < m_count; i++) {
		end = pointer->Address + pointer->Length;
		if (pointer->Address >= start && end <= ex_end) pointer->Type = MEMORY_DESCRIPTOR_TYPE_RESERVED;
		else if (pointer->Address < start && end > ex_end) {
			pAdditional = (PMemoryDescriptor_t)((size_t)m_table + m_descriptorSize * m_count);

			pAdditional->Address = ex_end;
			pAdditional->Length = end - ex_end;
			pAdditional->Type = pointer->Type;
			if (m_descriptorSize >= sizeof(MemoryDescriptor_t)) pAdditional->ExtendedFlags = pointer->ExtendedFlags;

			pointer->Length = start - pointer->Address;

			++m_count;
		}
		else if (pointer->Address <= start && end > start && end <= ex_end) pointer->Length = end - pointer->Address;
		else if (pointer->Address >= start && pointer->Address <= ex_end && end >= ex_end) {
			pointer->Address = ex_end;
			pointer->Length = end - ex_end;
		}

		pointer = (PMemoryDescriptor_t)((size_t)pointer + m_descriptorSize);
	}
}

void Memory::Copy(void *destination, const void *source, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = ((pbyte_t)source)[i];
}

void Memory::Set(void *destination, const byte_t value, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = value;
}