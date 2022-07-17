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

extern size_t pitTicksCount;

void PitInitialize();

void PitSetPhase(
	size_t frequency
);

void PitSleep(
	size_t ticks
);

void PitInterruptHandler(
	PInterruptHandlerRegisters_t pRegisters
);

#endif