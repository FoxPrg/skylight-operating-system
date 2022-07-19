#include "pic.h"

void PICRemap(uint8_t MasterIndex, uint8_t SlaveIndex) {
	uint8_t masterMask = PortsReadByte(PIC_PORT_MASTER_DATA);
	uint8_t slaveMask = PortsReadByte(PIC_PORT_SLAVE_DATA);

	PortsWriteByte(PIC_PORT_MASTER_CMD, PIC_WORD_INITIALIZE | PIC_WORD_FOURTH_STEP_INITIALIZATION);
	PortsWriteByte(PIC_PORT_SLAVE_CMD, PIC_WORD_INITIALIZE | PIC_WORD_FOURTH_STEP_INITIALIZATION);
	PortsWriteByte(PIC_PORT_MASTER_DATA, MasterIndex);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, SlaveIndex);
	PortsWriteByte(PIC_PORT_MASTER_DATA, PIC_CMD_TELL_MASTER_ABOUT_SLAVE);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, PIC_CMD_TELL_SLAVE_CASCADE_IDENTITY);
	PortsWriteByte(PIC_PORT_MASTER_DATA, PIC_WORD_8086_MODE);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, PIC_WORD_8086_MODE);
	
	PortsWriteByte(PIC_PORT_MASTER_DATA, masterMask);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, slaveMask);
}

void PICMask(uint8_t LineIndex) {
	uint16_t port = PIC_PORT_MASTER_DATA;
	if (LineIndex >= 8) {
		port = PIC_PORT_SLAVE_DATA;
		LineIndex -= 8;
	}
	PortsWriteByte(port, PortsReadByte(port) | (1 << LineIndex));
}

void PICUnmask(uint8_t LineIndex) {
	uint16_t port = PIC_PORT_MASTER_DATA;
	if (LineIndex >= 8) {
		port = PIC_PORT_SLAVE_DATA;
		LineIndex -= 8;
	}
	PortsWriteByte(port, PortsReadByte(port) & ~(1 << LineIndex));
}

void PICMaskAll() {
	PortsWriteByte(PIC_PORT_MASTER_DATA, 0xff);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, 0xff);
}

void PICUnmaskAll() {
	PortsWriteByte(PIC_PORT_MASTER_DATA, 0);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, 0);
}