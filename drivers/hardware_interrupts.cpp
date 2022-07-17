#include "hardware_interrupts.h"

InterruptHandler_t hardwareInterruptHandlers[16];

void InitializeHardwareInterrupts(
	word_t codeSegment
) {
	PicMaskAll();
	PicRemapVectors(32, 40);
	InitializeIdtEntry(32, HardwareInterruptHandler0, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(33, HardwareInterruptHandler1, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(34, HardwareInterruptHandler2, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(35, HardwareInterruptHandler3, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(36, HardwareInterruptHandler4, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(37, HardwareInterruptHandler5, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(38, HardwareInterruptHandler6, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(39, HardwareInterruptHandler7, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(40, HardwareInterruptHandler8, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(41, HardwareInterruptHandler9, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(42, HardwareInterruptHandler10, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(43, HardwareInterruptHandler11, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(44, HardwareInterruptHandler12, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(45, HardwareInterruptHandler13, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(46, HardwareInterruptHandler14, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(47, HardwareInterruptHandler15, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	DeclareAssembly("sti");
}

void InitializeHardwareInterruptHandler(
	size_t index,
	InterruptHandler_t hardwareInterruptHandler
) {
	if (hardwareInterruptHandler) PicUnmask(index);
	hardwareInterruptHandlers[index] = hardwareInterruptHandler;
}

extern "C" void FinalHardwareInterruptHandler(
	PInterruptHandlerRegisters_t pRegisters
) {
	size_t offset = pRegisters->InterruptIndex - 32;
	if (hardwareInterruptHandlers[offset]) hardwareInterruptHandlers[offset](pRegisters);
	else PicSendEndOfInterrupt(offset);
}