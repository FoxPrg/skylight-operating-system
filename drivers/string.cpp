#include "string.h"

const int8_t stringConversionNumbers[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

void StringFromSigned(
	decimal_t value,
	byte_t notation,
	pint8_t buffer
) {
	if (value < 0) {
		*buffer = '-';
		value = -value;
		StringFromUnsigned(value, notation, buffer + 1);
	}
	else StringFromUnsigned(value, notation, buffer);
}

void StringFromUnsigned(
	size_t value,
	byte_t notation,
	pint8_t buffer
) {
	puint8_t buffcopy = (puint8_t)buffer;
	size_t copy = value;
	size_t length = 0;

	do {
		copy /= notation;
		++length;
	} while(copy);

	buffcopy[length] = 0;
	buffcopy += length - 1;

	for (; length; length--) {
		*buffcopy = stringConversionNumbers[value % notation];
		value /= notation;
		--buffcopy;
	}
}