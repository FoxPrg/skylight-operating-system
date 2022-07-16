#include "memory.h"

VOID MemoryCopy(
	PVOID pvDestination,
	const PVOID cpvSource,
	SIZE_T szCount
) {
	for (SIZE_T i = 0; i < szCount; i++) ((PBYTE)pvDestination)[i] = ((PBYTE)cpvSource)[i];
}

VOID MemorySet(
	PVOID pvDestination,
	const BYTE cbValue,
	SIZE_T szCount
) {
	for (SIZE_T i = 0; i < szCount; i++) ((PBYTE)pvDestination)[i] = cbValue;
}