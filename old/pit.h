#ifndef PIT_H
#define PIT_H

#include "hardware_interrupts.h"

#define PIT_HARDWARE_INTERRUPT_OFFSET	0

#define PIT_PORT_COUNTER_0				0x40
#define PIT_PORT_COMMAND				0x43

#define PIT_COMMAND_BINARY				0x00
#define PIT_COMMAND_BCD					0x01

#define PIT_COMMAND_MODE_3				0x06
#define PIT_COMMAND_READ_WRITE_BOTH		0x30
#define PIT_COMMAND_SELECT_COUNTER_0	0x00

#define PIT_HARDWARE_FREQUENCY			1193180

#define PIT_TICKS_PER_SECOND			1000

class ProgrammableIntervalTimer {
	public:
	static void Initialize();
	static void SetFrequency(size_t frequency);
	static void Sleep(size_t ticksCount);
	static void Handler(PInterruptHandlerRegisters_t registers);
	private:
	static size_t m_ticksCount;
};

#endif