#include "pit.h"

size_t ProgrammableIntervalTimer::m_ticksCount = 0;

void ProgrammableIntervalTimer::Initialize() {
	SetFrequency(PIT_TICKS_PER_SECOND);
	HardwareInterruptsManager::SetHandler(PIT_HARDWARE_INTERRUPT_OFFSET, Handler);
}

void ProgrammableIntervalTimer::SetFrequency(size_t frequency) {
	word_t divisor = (word_t)(PIT_HARDWARE_FREQUENCY / frequency);
	InputOutputManager::WriteByte(PIT_PORT_COUNTER_0, divisor & 0xff);
	InputOutputManager::WriteByte(PIT_PORT_COUNTER_0, (divisor & 0xff00) >> 16);
}

void ProgrammableIntervalTimer::Sleep(size_t ticksCount) {
	size_t stopTicksCount = m_ticksCount + ticksCount;
	while (m_ticksCount < stopTicksCount) {}
}

void ProgrammableIntervalTimer::Handler(PInterruptHandlerRegisters_t registers) {
	m_ticksCount++;
	ProgrammableInterruptController::EndOfInterrupt(registers->InterruptIndex - 32);
}