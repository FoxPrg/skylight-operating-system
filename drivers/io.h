#ifndef PORTS_H
#define PORTS_H

#include "typedefs.h"

class InputOutputManager {
	public:
	static void WriteByte(word_t port, byte_t value);
	static void WriteWord(word_t port, word_t value);
	static void WriteDword(word_t port, dword_t value);
	static byte_t ReadByte(word_t port);
	static word_t ReadWord(word_t port);
	static dword_t ReadDword(word_t port);
};

#endif