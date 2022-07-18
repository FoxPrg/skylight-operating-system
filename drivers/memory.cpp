#include "memory.h"

PMemoryDescriptor_t Memory::m_table;
size_t Memory::m_count;

void Memory::Select(PMemoryDescriptor_t table, size_t count) {
	m_table = table;
	m_count = count;
}

void Memory::Exclude(size_t start, size_t length) {
	const size_t ex_end = start + length;
	size_t end;

	for (size_t i = 0; i < m_count; i++) {
		end = m_table[i].Address + m_table[i].Length;
		if (m_table[i].Address >= start && end <= ex_end) m_table[i].Type = MEMORY_DESCRIPTOR_TYPE_RESERVED;
		else if (m_table[i].Address < start && end > ex_end) {
			m_table[m_count].Address = ex_end;
			m_table[m_count].Length = end - ex_end;
			m_table[m_count].Type = m_table[i].Type;
			m_table[i].Length = start - m_table[i].Address;
			++m_count;
		}
		else if (m_table[i].Address <= start && end > start && end <= ex_end) m_table[i].Length = end - m_table[i].Address;
		else if (m_table[i].Address >= start && m_table[i].Address <= ex_end && end >= ex_end) {
			m_table[i].Address = ex_end;
			m_table[i].Length = end - ex_end;
		}
	}
}

size_t Memory::GetDescriptorsCount() {
	return m_count;
}

PMemoryDescriptor_t Memory::GetDescriptor(size_t index) {
	return &m_table[index];
}

void Memory::Copy(void *destination, const void *source, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = ((pbyte_t)source)[i];
}

void Memory::Set(void *destination, const byte_t value, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = value;
}