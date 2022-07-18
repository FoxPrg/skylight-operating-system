#include "8042.h"

void Controller8042::WaitInput() {
	byte_t status;
	do {
		status = InputOutputManager::ReadByte(CONTROLLER_8042_PORT_STATUS);
	} while(status & CONTROLLER_8042_STATUS_INPUT);
}

void Controller8042::Reset() {
	WaitInput();
	InputOutputManager::WriteByte(CONTROLLER_8042_PORT_COMMAND, CONTROLLER_8042_COMMAND_WRITE_OUTPUT);
	WaitInput();
	InputOutputManager::WriteByte(CONTROLLER_8042_PORT_DATA, CONTROLLER_8042_COMMAND_RESET);
}