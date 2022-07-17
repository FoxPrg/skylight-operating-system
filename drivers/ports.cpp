#include "ports.h"

void PortsWriteByte(
	word_t wPort,
	byte_t bValue
) {
	DeclareAssembly("out %0, %1"::"a"(bValue), "d"(wPort));
}

void PortsWriteWord(
	word_t wPort,
	word_t wValue
) {
	DeclareAssembly("out %0, %1"::"a"(wValue), "d"(wPort));
}

void PortsWriteDword(
	word_t wPort,
	dword_t dwValue
) {
	DeclareAssembly("out %0, %1"::"a"(dwValue), "d"(wPort));
}

byte_t PortsReadByte(
	word_t wPort
) {
	byte_t bValue;
	DeclareAssembly("in %1, %0":"=r"(bValue):"d"(wPort));
	return bValue;
}

word_t PortsReadWord(
	word_t wPort
) {
	word_t wValue;
	DeclareAssembly("in %1, %0":"=r"(wValue):"d"(wPort));
	return wValue;
}

dword_t PortsReadDword(
	word_t wPort
) {
	dword_t dwValue;
	DeclareAssembly("in %1, %0":"=r"(dwValue):"d"(wPort));
	return dwValue;
}