#include "ports.h"

void PortsWriteByte(uint16_t Port, uint8_t Value) {
	ASSEMBLY("out %0, %1"::"a"(Value), "d"(Port));
}

void PortsWriteWord(uint16_t Port, uint16_t Value) {
	ASSEMBLY("out %0, %1"::"a"(Value), "d"(Port));
}

void PortsWriteLong(uint16_t Port, uint32_t Value) {
	ASSEMBLY("out %0, %1"::"a"(Value), "d"(Port));
}

uint8_t PortsReadByte(uint16_t Port) {
	uint8_t value;
	ASSEMBLY("in %1, %0":"=r"(value):"d"(port));
	return value;
}

uint16_t PortsReadWord(uint16_t Port) {
	uint16_t value;
	ASSEMBLY("in %1, %0":"=r"(value):"d"(port));
	return value;
}

uint32_t PortsReadLong(uint16_t Port) {
	uint32_t value;
	ASSEMBLY("in %1, %0":"=r"(value):"d"(port));
	return value;
}