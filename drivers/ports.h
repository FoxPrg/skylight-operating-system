#ifndef PORTS_H
#define PORTS_H

#include "typedefs.h"

VOID PortsWriteByte(
	WORD wPort,
	BYTE bValue
);

VOID PortsWriteWord(
	WORD wPort,
	WORD wValue
);

VOID PortsWriteDword(
	WORD wPort,
	DWORD dwValue
);

BYTE PortsReadByte(
	WORD wPort
);

WORD PortsReadWord(
	WORD wPort
);

DWORD PortsReadDword(
	WORD wPort
);

#endif