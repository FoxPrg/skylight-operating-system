#ifndef HARDWARE_INTERRUPTS_H
#define HARDWARE_INTERRUPTS_H

#include "idt.h"
#include "pic.h"

class HardwareInterruptsManager {
	public:
	static void Initialize(word_t codeSegment);
	static void SetHandler(size_t index, InterruptHandler_t handler);
	static InterruptHandler_t GetHandler(size_t index);
	private:
	static InterruptHandler_t m_handlers[16];
};

#endif