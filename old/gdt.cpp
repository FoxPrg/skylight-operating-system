#include "gdt.h"

GlobalDescriptorTableRegister_t gdtSelectedRegister;
PGlobalDescriptorTableEntry_t gdtSelectedTable;
size_t gdtSelectedLength;

GlobalDescriptorTableRegister_t GlobalDescriptorTableManager::m_register;
PGlobalDescriptorTableEntry_t GlobalDescriptorTableManager::m_table;
size_t GlobalDescriptorTableManager::m_length;

void GlobalDescriptorTableManager::Select(PGlobalDescriptorTableEntry_t table, size_t length) {
	m_register.Size = sizeof(GlobalDescriptorTableEntry_t) * length - 1;
	m_register.Offset = (dword_t)table;
	m_table = table;
	m_length = length;
}

void GlobalDescriptorTableManager::SetEntry(size_t index, dword_t limit, dword_t base, byte_t access, byte_t flags) {
	m_table[index].LimitLow = (word_t)((size_t)limit & 0xffff);
	m_table[index].BaseLow = (dword_t)((size_t)base & 0xffffff);
	m_table[index].Access = access;
	m_table[index].LimitHigh = (byte_t)((size_t)limit >> 16) & 0x0f;
	m_table[index].Flags = flags;
	m_table[index].BaseHigh = (byte_t)((base >> 24) & 0xff);
}

void GlobalDescriptorTableManager::Load() {
	DeclareAssembly("lgdt %0"::"m"(m_register));
}