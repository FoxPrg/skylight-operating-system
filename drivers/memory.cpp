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

void Memory::Initialize() {
	Align();
	Sort();
	RemoveUseless();
	Merge();
}

void Memory::Sort() {
	MemoryDescriptor_t tmp;
	for (size_t i = 0; i < m_count; i++) {
		for (size_t j = i + 1; j < m_count; j++) {
			if (m_table[j].Address < m_table[i].Address) {
				tmp = m_table[i];
				m_table[i] = m_table[j];
				m_table[j] = tmp;
			}
		}
	}
}

void Memory::Align() {
	for (size_t i = 0; i < m_count; i++) {
		m_table[i].Address = AlignUp(m_table[i].Address, MEMORY_PAGE_SIZE);
		m_table[i].Length = AlignDown(m_table[i].Length, MEMORY_PAGE_SIZE);
		if (!m_table[i].Length) {
			for (size_t j = i + 1; j < m_count; j++) m_table[j - 1] = m_table[j];
			--m_count;
			--i;
		}
	}
}

void Memory::RemoveUseless() {
	for (size_t i = 0; i < m_count; i++) if (!m_table[i].Length) RemoveByIndex(i--);
}

void Memory::RemoveByIndex(size_t index) {
	for (size_t j = index + 1; j < m_count; j++) m_table[j - 1] = m_table[j];
	--m_count;
}

void Memory::Merge() {
	for (unsigned int i = 0; i < m_count - 1; i++) {
        if (m_table[i].Address + m_table[i].Length == m_table[i + 1].Address && m_table[i].Type == m_table[i + 1].Type) {
            m_table[i].Length = m_table[i + 1].Address + m_table[i + 1].Length - m_table[i].Address;
			RemoveByIndex(i + 1);
            --i;
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