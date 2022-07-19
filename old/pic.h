#ifndef PIC_H
#define PIC_H

#include "io.h"

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

class ProgrammableInterruptController {
	public:
	static void Remap(byte_t masterOffset, byte_t slaveOffset);
	static void Mask(byte_t routine);
	static void Unmask(byte_t routine);
	static void EndOfInterrupt(byte_t routine);
	static void MaskAll();
	static void UnmaskAll();
};

#endif