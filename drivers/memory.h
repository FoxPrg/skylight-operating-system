#ifndef MEMORY_H
#define MEMORY_H

#include "typedefs.h"

void MemoryCopy(
	void* pvDestination,
	const void* cpvSource,
	size_t szCount
);

void MemorySet(
	void* pvDestination,
	const byte_t cbValue,
	size_t szCount
);

#endif