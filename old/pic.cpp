#include "pic.h"

void ProgrammableInterruptController::Remap(byte_t masterOffset, byte_t slaveOffset) {
	byte_t masterMask = InputOutputManager::ReadByte(PIC_PORT_MASTER_DATA);
	byte_t slaveMask = InputOutputManager::ReadByte(PIC_PORT_SLAVE_DATA);

	InputOutputManager::WriteByte(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_WORD_1_INITIALIZE | PIC_COMMAND_WORD_1_COMMAND_WORD_4);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_WORD_1_INITIALIZE | PIC_COMMAND_WORD_1_COMMAND_WORD_4);
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, masterOffset);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, slaveOffset);
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, PIC_COMMAND_MASTER_SLAVE_AT_IRQ_2);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, PIC_COMMAND_SLAVE_CASCADE_IDENTITY);
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, PIC_COMMAND_WORD_4_8086);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, PIC_COMMAND_WORD_4_8086);
	
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, masterMask);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, slaveMask);
}

void ProgrammableInterruptController::Mask(byte_t routine) {
	if (routine < 8) InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, InputOutputManager::ReadByte(PIC_PORT_MASTER_DATA) | (1 << routine));
	else InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, InputOutputManager::ReadByte(PIC_PORT_SLAVE_DATA) | (1 << (routine - 8)));
}

void ProgrammableInterruptController::Unmask(byte_t routine) {
	if (routine < 8) InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, InputOutputManager::ReadByte(PIC_PORT_MASTER_DATA) & ~(1 << routine));
	else InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, InputOutputManager::ReadByte(PIC_PORT_SLAVE_DATA)  & ~(1 << (routine - 8)));
}

void ProgrammableInterruptController::EndOfInterrupt(byte_t routine) {
	if (routine >= 8) InputOutputManager::WriteByte(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_END_OF_INTERRUPT);
	InputOutputManager::WriteByte(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_END_OF_INTERRUPT);
}

void ProgrammableInterruptController::MaskAll() {
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, 0xff);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, 0xff);
}

void ProgrammableInterruptController::UnmaskAll() {
	InputOutputManager::WriteByte(PIC_PORT_MASTER_DATA, 0);
	InputOutputManager::WriteByte(PIC_PORT_SLAVE_DATA, 0);
}