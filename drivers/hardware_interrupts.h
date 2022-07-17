#ifndef HARDWARE_INTERRUPTS_H
#define HARDWARE_INTERRUPTS_H

#include "idt.h"
#include "pic.h"

extern "C" {
	void HardwareInterruptHandler0();
	void HardwareInterruptHandler1();
	void HardwareInterruptHandler2();
	void HardwareInterruptHandler3();
	void HardwareInterruptHandler4();
	void HardwareInterruptHandler5();
	void HardwareInterruptHandler6();
	void HardwareInterruptHandler7();
	void HardwareInterruptHandler8();
	void HardwareInterruptHandler9();
	void HardwareInterruptHandler10();
	void HardwareInterruptHandler11();
	void HardwareInterruptHandler12();
	void HardwareInterruptHandler13();
	void HardwareInterruptHandler14();
	void HardwareInterruptHandler15();
};

extern InterruptHandler_t hardwareInterruptHandlers[16];

void InitializeHardwareInterrupts(
	word_t codeSegment
);

void InitializeHardwareInterruptHandler(
	size_t index,
	InterruptHandler_t hardwareInterruptHandler
);

extern "C" void FinalHardwareInterruptHandler(
	PInterruptHandlerRegisters_t pRegisters
);

#endif