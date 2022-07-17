#ifndef PORTS_H
#define PORTS_H

#include "typedefs.h"

void PortsWriteByte(
	word_t wPort,
	byte_t bValue
);

void PortsWriteWord(
	word_t wPort,
	word_t wValue
);

void PortsWriteDword(
	word_t wPort,
	dword_t dwValue
);

byte_t PortsReadByte(
	word_t wPort
);

word_t PortsReadWord(
	word_t wPort
);

dword_t PortsReadDword(
	word_t wPort
);

#endif