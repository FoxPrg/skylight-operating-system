#ifndef PAGING_H
#define PAGING_H

#include "typedefs.h"

#define PAGING_FLAG_PRESENT			1
#define PAGING_FLAG_READ_WRITE		2
#define PAGING_FLAG_USER			4
#define PAGING_FLAG_WRITE_THROUGH	8
#define PAGING_FLAG_CACHE_DISABLED	16
#define PAGING_FLAG_SIZE_EXTENSION	128

class Paging {
	public:
	static void Initialize(void* tables, void* directory);
	static void Enable();
	static void MapPages(size_t physicalAddress, size_t index, size_t count, dword_t flags);
	static void MapTables(size_t index, size_t count, dword_t flags);
	private:
	static pdword_t m_pages;
	static pdword_t m_tables;
};

#endif