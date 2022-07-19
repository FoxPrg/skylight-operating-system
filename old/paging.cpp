#include "paging.h"

pdword_t Paging::m_pages;
pdword_t Paging::m_tables;

void Paging::Initialize(void* tables, void* directory) {
	m_pages = (pdword_t)tables;
	m_tables = (pdword_t)directory;
	DeclareAssembly("mov %0, %%cr3"::"r"(m_tables));
}

void Paging::Enable() {
	DeclareAssembly(
		"mov %cr0, %eax;"
		"or $0x80000000, %eax;"
		"mov %eax, %cr0"
	);
}

void Paging::MapPages(size_t physicalAddress, size_t index, size_t count, dword_t flags) {
	for (size_t i = index; i < index + count; i++) m_pages[i] = (dword_t)(((physicalAddress + ((i - index) << 12)) & 0xfffff000) | (flags & 0xfff));
}

void Paging::MapTables(size_t index, size_t count, dword_t flags) {
	for (size_t i = index; i < index + count; i++) m_tables[i] = (dword_t)(((dword_t)&m_pages[i << 12] & 0xfffff000) | (flags & 0xfff));
}