#include "string.h"

const char String::m_conversionBuffer[16] = {
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

void String::FromUnsigned(size_t value, byte_t base, char* buffer) {
	size_t copy = value;
	size_t length = 0;

	do {
		copy /= base;
		++length;
	} while(copy != 0);

	buffer[length] = 0;

	for (size_t i = 0; i < length; i++) {
		buffer[length - i - 1] = m_conversionBuffer[value % base];
		value /= base;
	}
}