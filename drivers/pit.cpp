#include "pit.h"

size_t pitTicksCount = 0;

void PitInitialize() {
	PitSetPhase(PIT_TICKS_PER_SECOND);
	InitializeHardwareInterruptHandler(PIT_HARDWARE_INTERRUPT_OFFSET, PitInterruptHandler);
}

void PitSetPhase(
	size_t frequency
) {
	word_t divisor = (word_t)(PIT_HARDWARE_FREQUENCY / frequency);
	PortsWriteByte(PIT_PORT_COUNTER_0, divisor & 0xff);
	PortsWriteByte(PIT_PORT_COUNTER_0, (divisor & 0xff00) >> 16);
}

void PitSleep(
	size_t ticks
) {
	size_t endCount = pitTicksCount + ticks;
	while (pitTicksCount < endCount) {}
}

void PitInterruptHandler(
	PInterruptHandlerRegisters_t pRegisters
) {
	++pitTicksCount;
	PicSendEndOfInterrupt(pRegisters->InterruptIndex - 32);
}