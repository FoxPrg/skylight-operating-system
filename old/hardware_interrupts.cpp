#include "hardware_interrupts.h"

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

	void FinalHardwareInterruptHandler(PInterruptHandlerRegisters_t registers) {
		size_t offset = registers->InterruptIndex - 32;
		InterruptHandler_t handler = HardwareInterruptsManager::GetHandler(offset);
		if (handler) handler(registers);
		else ProgrammableInterruptController::EndOfInterrupt(offset);
	}
}

InterruptHandler_t HardwareInterruptsManager::m_handlers[16];

void HardwareInterruptsManager::Initialize(word_t codeSegment) {
	ProgrammableInterruptController::MaskAll();
	ProgrammableInterruptController::Remap(32, 40);
	InterruptDescriptorTableManager::SetEntry(32, HardwareInterruptHandler0, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(33, HardwareInterruptHandler1, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(34, HardwareInterruptHandler2, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(35, HardwareInterruptHandler3, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(36, HardwareInterruptHandler4, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(37, HardwareInterruptHandler5, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(38, HardwareInterruptHandler6, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(39, HardwareInterruptHandler7, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(40, HardwareInterruptHandler8, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(41, HardwareInterruptHandler9, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(42, HardwareInterruptHandler10, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(43, HardwareInterruptHandler11, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(44, HardwareInterruptHandler12, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(45, HardwareInterruptHandler13, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(46, HardwareInterruptHandler14, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InterruptDescriptorTableManager::SetEntry(47, HardwareInterruptHandler15, codeSegment, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	DeclareAssembly("sti");
}

void HardwareInterruptsManager::SetHandler(size_t index, InterruptHandler_t handler) {
	m_handlers[index] = handler;
}

InterruptHandler_t HardwareInterruptsManager::GetHandler(size_t index) {
	return m_handlers[index];
}