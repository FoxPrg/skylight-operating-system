#include "exceptions.h"

extern "C" {
	void ExceptionHandler0();
	void ExceptionHandler1();
	void ExceptionHandler2();
	void ExceptionHandler3();
	void ExceptionHandler4();
	void ExceptionHandler5();
	void ExceptionHandler6();
	void ExceptionHandler7();
	void ExceptionHandler8();
	void ExceptionHandler9();
	void ExceptionHandler10();
	void ExceptionHandler11();
	void ExceptionHandler12();
	void ExceptionHandler13();
	void ExceptionHandler14();
	void ExceptionHandler15();
	void ExceptionHandler16();
	void ExceptionHandler17();
	void ExceptionHandler18();
	void ExceptionHandler19();
	void ExceptionHandler20();
	void ExceptionHandler21();
	void ExceptionHandler22();
	void ExceptionHandler23();
	void ExceptionHandler24();
	void ExceptionHandler25();
	void ExceptionHandler26();
	void ExceptionHandler27();
	void ExceptionHandler28();
	void ExceptionHandler29();
	void ExceptionHandler30();
	void ExceptionHandler31();

	void FinalExceptionHandler(PInterruptHandlerRegisters_t registers) {
		InterruptHandler_t handler = ExceptionsManager::GetHandler(registers->InterruptIndex);
		if (handler) handler(registers);
	}
}

InterruptHandler_t ExceptionsManager::m_handlers[32];

void ExceptionsManager::Initialize(word_t codeSegment) {
	InterruptDescriptorTableManager::SetEntry(0, ExceptionHandler0, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(1, ExceptionHandler1, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(2, ExceptionHandler2, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(3, ExceptionHandler3, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(4, ExceptionHandler4, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(5, ExceptionHandler5, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(6, ExceptionHandler6, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(7, ExceptionHandler7, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(8, ExceptionHandler8, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(9, ExceptionHandler9, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(10, ExceptionHandler10, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(11, ExceptionHandler11, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(12, ExceptionHandler12, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(13, ExceptionHandler13, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(14, ExceptionHandler14, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(15, ExceptionHandler15, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(16, ExceptionHandler16, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(17, ExceptionHandler17, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(18, ExceptionHandler18, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(19, ExceptionHandler19, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(20, ExceptionHandler20, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(21, ExceptionHandler21, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(22, ExceptionHandler22, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(23, ExceptionHandler23, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(24, ExceptionHandler24, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(25, ExceptionHandler25, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(26, ExceptionHandler26, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(27, ExceptionHandler27, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(28, ExceptionHandler28, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(29, ExceptionHandler29, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(30, ExceptionHandler30, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(31, ExceptionHandler31, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
}

void ExceptionsManager::SetHandler(size_t index, InterruptHandler_t handler) {
	m_handlers[index] = handler;
}

InterruptHandler_t ExceptionsManager::GetHandler(size_t index) {
	return m_handlers[index];
}