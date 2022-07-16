#ifndef MEMORY_H
#define MEMORY_H

#include "typedefs.h"

VOID MemoryCopy(
	PVOID pvDestination,
	const PVOID cpvSource,
	SIZE_T szCount
);

VOID MemorySet(
	PVOID pvDestination,
	const BYTE cbValue,
	SIZE_T szCount
);

#endif