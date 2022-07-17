#ifndef PIC_H
#define PIC_H

#include "ports.h"

#define PIC_PORT_MASTER_COMMAND				0x20
#define PIC_PORT_MASTER_DATA				0x21
#define PIC_PORT_SLAVE_COMMAND				0xa0
#define PIC_PORT_SLAVE_DATA					0xa1

#define PIC_COMMAND_READ_IRR				0x0a
#define PIC_COMMAND_READ_ISR				0x0b
#define PIC_COMMAND_END_OF_INTERRUPT		0x20

#define PIC_COMMAND_WORD_1_COMMAND_WORD_4	0x01
#define PIC_COMMAND_WORD_4_8086				0x01
#define PIC_COMMAND_WORD_1_INITIALIZE		0x10

#define PIC_COMMAND_MASTER_SLAVE_AT_IRQ_2	0x04
#define PIC_COMMAND_SLAVE_CASCADE_IDENTITY	0x02

void PicRemapVectors(
	byte_t bMaster,
	byte_t bSlave
);

void PicMask(
	byte_t bRoutine
);

void PicUnmask(
	byte_t bRoutine
);

void PicSendEndOfInterrupt(
	byte_t bRoutine
);

#define PicMaskAll()	PortsWriteByte(PIC_PORT_MASTER_DATA, 0xff); PortsWriteByte(PIC_PORT_SLAVE_DATA, 0xff);
#define PicUnmaskAll()	PortsWriteByte(PIC_PORT_MASTER_DATA, 0); PortsWriteByte(PIC_PORT_SLAVE_DATA, 0);

#endif