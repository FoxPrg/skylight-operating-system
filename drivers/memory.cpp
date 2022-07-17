#include "memory.h"

void MemoryCopy(
	void* pvDestination,
	const void* cpvSource,
	size_t szCount
) {
	for (size_t i = 0; i < szCount; i++) ((pbyte_t)pvDestination)[i] = ((pbyte_t)cpvSource)[i];
}

void MemorySet(
	void* pvDestination,
	const byte_t cbValue,
	size_t szCount
) {
	for (size_t i = 0; i < szCount; i++) ((pbyte_t)pvDestination)[i] = cbValue;
}