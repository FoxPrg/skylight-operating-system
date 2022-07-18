#include "memory.h"

PMemoryRegion_t Memory::m_table;
size_t Memory::m_count;

void Memory::Select(PMemoryRegion_t table, size_t count) {
	m_table = table;
	m_count = count;
}

void Memory::Exclude(size_t start, size_t length) {
	const size_t ex_end = start + length;
	size_t end;

	for (size_t i = 0; i < m_count; i++) {
		end = m_table[i].Address + m_table[i].Length;
		if (m_table[i].Address >= start && end <= ex_end) m_table[i].Type = MEMORY_REGION_TYPE_RESERVED;
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

void Memory::RemoveByIndex(size_t index) {
	for (size_t j = index + 1; j < m_count; j++) m_table[j - 1] = m_table[j];
	--m_count;
}

void Memory::Initialize() {
	//	align && remove small
	for (size_t i = 0; i < m_count; i++) {
		m_table[i].Address = AlignUp(m_table[i].Address, MEMORY_FRAME_SIZE);
		m_table[i].Length = AlignDown(m_table[i].Length, MEMORY_FRAME_SIZE);
		if (m_table[i].Length < MEMORY_REGION_MINIMAL_SIZE) RemoveByIndex(i--);
	}

	//	sort
	MemoryRegion_t tmp;
	for (size_t i = 0; i < m_count; i++) {
		for (size_t j = i + 1; j < m_count; j++) {
			if (m_table[j].Address < m_table[i].Address) {
				tmp = m_table[i];
				m_table[i] = m_table[j];
				m_table[j] = tmp;
			}
		}
	}

	//	merge adjacent
	for (unsigned int i = 0; i < m_count - 1; i++) {
        if (m_table[i].Address + m_table[i].Length == m_table[i + 1].Address && m_table[i].Type == m_table[i + 1].Type) {
            m_table[i].Length = m_table[i + 1].Address + m_table[i + 1].Length - m_table[i].Address;
			RemoveByIndex(i + 1);
            --i;
        }
    }

	size_t frame_address, frame_target, frames_count;
	for (size_t i = 0; i < m_count; i++) {
		frame_address = m_table[i].Address;
		frame_target = m_table[i].Address + m_table[i].Length - MEMORY_FRAME_SIZE;
		frames_count = 0;

		while (frame_address < frame_target) {
			++frames_count;
			frame_address += sizeof(FrameDescriptor_t);
			frame_target -= MEMORY_FRAME_SIZE;
		}

		frame_target += MEMORY_FRAME_SIZE;
		m_table[i].Length = frames_count;

		if (m_table[i].Type == MEMORY_REGION_TYPE_USABLE) {
			PFrameDescriptor_t frames = (PFrameDescriptor_t)frame_target;
			size_t frame_target = AlignUp(m_table[i].Length * sizeof(FrameDescriptor_t), MEMORY_FRAME_SIZE);
			for (size_t i = 0; i < m_table[i].Length; i++) {
				frames[i].Address = frame_target;
				frames[i].Attributes = 0;
				frames[i].Count = 1;
			}
		}
	}
}

void* Memory::Allocate(size_t count) {
	count = AlignUp(count, MEMORY_FRAME_SIZE) / MEMORY_FRAME_SIZE;
	PFrameDescriptor_t frames;
	bool busy;

	for (size_t i = 0; i < m_count; i++) {
		if (m_table[i].Type == MEMORY_REGION_TYPE_USABLE && m_table[i].Length >= count) {
			frames = (PFrameDescriptor_t)m_table[i].Address;
			for (size_t j = 0; j < m_table[i].Length; j++) {
				busy = false;
				for (size_t k = j; k < j + count; k++) {
					if (frames[k].Attributes & MEMORY_FRAME_ATTRIBUTE_BUSY) {
						busy = true;
						break;
					}
				}
				if (!busy) {
					for (size_t k = j; k < j + count; k++) {
						frames[k].Attributes |= MEMORY_FRAME_ATTRIBUTE_BUSY;
						frames[k].Count = count;
					}
					return (void*)frames[j].Address;
				}
			}
		}
	}

	return nullptr;
}

bool Memory::Free(void *memory) {
	PFrameDescriptor_t frames;
	size_t count;

	for (size_t i = 0; i < m_count; i++) {
		if (m_table[i].Type == MEMORY_REGION_TYPE_USABLE) {
			frames = (PFrameDescriptor_t)m_table[i].Address;
			for (size_t j = 0; j < m_table[i].Length; j++) {
				if (frames[j].Address == (size_t)memory && frames[j].Attributes & MEMORY_FRAME_ATTRIBUTE_BUSY) {
					count = frames[j].Count;
					for (size_t k = j; k < j + count; k++) {
						frames[k].Attributes &= ~MEMORY_FRAME_ATTRIBUTE_BUSY;
						frames[k].Count = 1;
					}
					return true;
				}
			}
		}
	}

	return false;
}

size_t Memory::GetRegionsCount() {
	return m_count;
}

PMemoryRegion_t Memory::GetRegion(size_t index) {
	return &m_table[index];
}

void Memory::Copy(void *destination, const void *source, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = ((pbyte_t)source)[i];
}

void Memory::Set(void *destination, const byte_t value, size_t count) {
	for (size_t i = 0; i < count; i++) ((pbyte_t)destination)[i] = value;
}

void *operator new[](unsigned int s)
{
    return Memory::Allocate(s);
}

void operator delete[](void *p)
{
    Memory::Free(p);
}