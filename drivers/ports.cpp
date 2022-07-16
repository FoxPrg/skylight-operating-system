#include "ports.h"

VOID PortsWriteByte(
	WORD wPort,
	BYTE bValue
) {
	DeclareAssembly("out %0, %1"::"a"(bValue), "d"(wPort));
}

VOID PortsWriteWord(
	WORD wPort,
	WORD wValue
) {
	DeclareAssembly("out %0, %1"::"a"(wValue), "d"(wPort));
}

VOID PortsWriteDword(
	WORD wPort,
	DWORD dwValue
) {
	DeclareAssembly("out %0, %1"::"a"(dwValue), "d"(wPort));
}

BYTE PortsReadByte(
	WORD wPort
) {
	BYTE bValue;
	DeclareAssembly("in %1, %0":"=r"(bValue):"d"(wPort));
	return bValue;
}

WORD PortsReadWord(
	WORD wPort
) {
	WORD wValue;
	DeclareAssembly("in %1, %0":"=r"(wValue):"d"(wPort));
	return wValue;
}

DWORD PortsReadDword(
	WORD wPort
) {
	DWORD dwValue;
	DeclareAssembly("in %1, %0":"=r"(dwValue):"d"(wPort));
	return dwValue;
}