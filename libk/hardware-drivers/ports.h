#ifndef PORTS_H
#define PORTS_H

#include "../common/typedefs.h"

void PortsWriteByte(uint16_t Port, uint8_t Value);
void PortsWriteWord(uint16_t Port, uint16_t Value);
void PortsWriteLong(uint16_t Port, uint32_t Value);
uint8_t PortsReadByte(uint16_t Port);
uint16_t PortsReadWord(uint16_t Port);
uint32_t PortsReadLong(uint16_t Port);

#endif