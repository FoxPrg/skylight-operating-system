#include "io.h"

void InputOutputManager::WriteByte(word_t port, byte_t value) {
	DeclareAssembly("out %0, %1"::"a"(value), "d"(port));
}

void InputOutputManager::WriteWord(word_t port, word_t value) {
	DeclareAssembly("out %0, %1"::"a"(value), "d"(port));
}

void InputOutputManager::WriteDword(word_t port, dword_t value) {
	DeclareAssembly("out %0, %1"::"a"(value), "d"(port));
}

byte_t InputOutputManager::ReadByte(word_t port) {
	byte_t value;
	DeclareAssembly("in %1, %0":"=r"(value):"d"(port));
	return value;
}

word_t InputOutputManager::ReadWord(word_t port) {
	word_t value;
	DeclareAssembly("in %1, %0":"=r"(value):"d"(port));
	return value;
}

dword_t InputOutputManager::ReadDword(word_t port) {
	dword_t value;
	DeclareAssembly("in %1, %0":"=r"(value):"d"(port));
	return value;
}