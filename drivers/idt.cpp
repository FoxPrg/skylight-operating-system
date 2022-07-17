#include "idt.h"

InterruptDescriptorTableRegister_t InterruptDescriptorTableManager::m_register;
PInterruptDescriptorTableEntry_t InterruptDescriptorTableManager::m_table;
size_t InterruptDescriptorTableManager::m_length;

void InterruptDescriptorTableManager::Select(PInterruptDescriptorTableEntry_t table, size_t length) {
	m_register.Offset = (size_t)table;
	m_register.Size = length * sizeof(InterruptDescriptorTableEntry_t) - 1;
	m_table = table;
	m_length = length;
}

void InterruptDescriptorTableManager::SetEntry(size_t index, void (*dispatcher)(), word_t segmentSelector, byte_t flags) {
	m_table[index].OffsetLow = (word_t)((size_t)dispatcher & 0xffff);
	m_table[index].SegmentSelector = segmentSelector;
	m_table[index].Reserved = 0;
	m_table[index].Flags = flags;
	m_table[index].OffsetHigh = (word_t)(((size_t)dispatcher >> 16) & 0xffff);
}

void InterruptDescriptorTableManager::Load() {
	DeclareAssembly("lidt %0"::"m"(m_register));
}