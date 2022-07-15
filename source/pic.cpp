#include <pic.h>

VOID PicRemapVectors(
	BYTE bMaster,
	BYTE bSlave
) {
	BYTE bMasterMask = PortsReadByte(PIC_PORT_MASTER_DATA);
	BYTE bSlaveMask = PortsReadByte(PIC_PORT_SLAVE_DATA);

	PortsWriteByte(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_WORD_1_INITIALIZE | PIC_COMMAND_WORD_1_COMMAND_WORD_4);
	PortsWriteByte(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_WORD_1_INITIALIZE | PIC_COMMAND_WORD_1_COMMAND_WORD_4);
	PortsWriteByte(PIC_PORT_MASTER_DATA, bMaster);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, bSlave);
	PortsWriteByte(PIC_PORT_MASTER_DATA, PIC_COMMAND_MASTER_SLAVE_AT_IRQ_2);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, PIC_COMMAND_SLAVE_CASCADE_IDENTITY);
	PortsWriteByte(PIC_PORT_MASTER_DATA, PIC_COMMAND_WORD_4_8086);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, PIC_COMMAND_WORD_4_8086);
	
	PortsWriteByte(PIC_PORT_MASTER_DATA, bMasterMask);
	PortsWriteByte(PIC_PORT_SLAVE_DATA, bSlaveMask);
}

VOID PicMask(
	BYTE bRoutine
) {
	if (bRoutine < 8) PortsWriteByte(PIC_PORT_MASTER_DATA, PortsReadByte(PIC_PORT_MASTER_DATA) | (1 << bRoutine));
	else PortsWriteByte(PIC_PORT_SLAVE_DATA, PortsReadByte(PIC_PORT_SLAVE_DATA) | (1 << (bRoutine - 8)));
}

VOID PicUnmask(
	BYTE bRoutine
) {
	if (bRoutine < 8) PortsWriteByte(PIC_PORT_MASTER_DATA, PortsReadByte(PIC_PORT_MASTER_DATA) & ~(1 << bRoutine));
	else PortsWriteByte(PIC_PORT_SLAVE_DATA, PortsReadByte(PIC_PORT_SLAVE_DATA)  & ~(1 << (bRoutine - 8)));
}

VOID PicSendEndOfInterrupt(
	BYTE bRoutine
) {
	if (bRoutine >= 8) PortsWriteByte(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_END_OF_INTERRUPT);
	PortsWriteByte(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_END_OF_INTERRUPT);
}