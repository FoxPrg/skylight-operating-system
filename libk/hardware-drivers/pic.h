#ifndef PIC_H
#define PIC_H

#include "../common/typedefs.h"

#define PIC_PORT_MASTER_CMD						0x20
#define PIC_PORT_MASTER_DATA					0x21
#define PIC_PORT_SLAVE_CMD						0xa0
#define PIC_PORT_SLAVE_DATA						0xa1

#define PIC_CMD_EOI								0x20

#define PIC_WORD_FOURTH_STEP_INITIALIZATION		0x01
#define PIC_WORD_8086_MODE						0x01
#define PIC_WORD_INITIALIZE						0x10

#define PIC_CMD_TELL_SLAVE_CASCADE_IDENTITY		0x02
#define PIC_CMD_TELL_MASTER_ABOUT_SLAVE			0x04

void PICRemap(uint8_t MasterIndex, uint8_t SlaveIndex);
void PICMask(uint8_t LineIndex);
void PICUnmask(uint8_t LineIndex);
void PICMaskAll();
void PICUnmaskAll();

#endif