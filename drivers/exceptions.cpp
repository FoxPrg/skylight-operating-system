#include "exceptions.h"

InterruptHandler_t exceptionHandlers[32];

void InitializeExceptions(
	word_t codeSegment
) {
	InitializeIdtEntry(0, ExceptionHandler0, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(1, ExceptionHandler1, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(2, ExceptionHandler2, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(3, ExceptionHandler3, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(4, ExceptionHandler4, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(5, ExceptionHandler5, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(6, ExceptionHandler6, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(7, ExceptionHandler7, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(8, ExceptionHandler8, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(9, ExceptionHandler9, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(10, ExceptionHandler10, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(11, ExceptionHandler11, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(12, ExceptionHandler12, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(13, ExceptionHandler13, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(14, ExceptionHandler14, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(15, ExceptionHandler15, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(16, ExceptionHandler16, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(17, ExceptionHandler17, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(18, ExceptionHandler18, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(19, ExceptionHandler19, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(20, ExceptionHandler20, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(21, ExceptionHandler21, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(22, ExceptionHandler22, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(23, ExceptionHandler23, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(24, ExceptionHandler24, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(25, ExceptionHandler25, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(26, ExceptionHandler26, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(27, ExceptionHandler27, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(28, ExceptionHandler28, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(29, ExceptionHandler29, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(30, ExceptionHandler30, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(31, ExceptionHandler31, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
}

void InitializeExceptionHandler(
	size_t index,
	InterruptHandler_t exceptionHandler
) {
	exceptionHandlers[index] = exceptionHandler;
}

extern "C" void FinalExceptionHandler(
	PInterruptHandlerRegisters_t pRegisters
) {
	if (exceptionHandlers[pRegisters->InterruptIndex]) exceptionHandlers[pRegisters->InterruptIndex](pRegisters);
}