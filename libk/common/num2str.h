#ifndef NUM2STR_H
#define NUM2STR_H	//	number to string conversions

#include "typedefs.h"

/*===============================
Recommended buffer size: 65 bytes
===[64 bits + null-terminator]===
===============================*/

void StringFromUInt64(uint64_t Value, uint8_t Base, puint8_t Buffer);
void StringFromInt64(int64_t Value, uint8_t Base, puint8_t Buffer);

#endif