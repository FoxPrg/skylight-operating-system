#include "string.h"

char String::m_conversionBuffer[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

void String::FromSigned(decimal_t value, byte_t base, char* buffer) {
	if (value < 0) {
		*buffer = '-';
		value = -value;
		FromUnsigned(value, base, buffer + 1);
	}
	else FromSigned(value, base, buffer);
}

void String::FromUnsigned(decimal_t value, byte_t base, char* buffer) {
	puint8_t buffcopy = (puint8_t)buffer;
	size_t copy = value;
	size_t length = 0;

	do {
		copy /= base;
		++length;
	} while(copy);

	buffcopy[length] = 0;
	buffcopy += length - 1;

	for (; length; length--) {
		*buffcopy = m_conversionBuffer[value % base];
		value /= base;
		--buffcopy;
	}
}