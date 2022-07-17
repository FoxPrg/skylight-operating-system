#ifndef STRING_H
#define STRING_H

#include "typedefs.h"

void StringFromSigned(
	decimal_t value,
	byte_t notation,
	pint8_t buffer
);

void StringFromUnsigned(
	size_t value,
	byte_t notation,
	pint8_t buffer
);

#endif