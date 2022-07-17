#ifndef STRING_H
#define STRING_H

#include "typedefs.h"

class String {
	public:
	static void FromSigned(decimal_t value, byte_t base, char* buffer);
	static void FromUnsigned(decimal_t value, byte_t base, char* buffer);
	private:
	static char m_conversionBuffer[16];
};

#endif