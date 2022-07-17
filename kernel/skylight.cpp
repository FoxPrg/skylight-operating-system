#include "skylight.h"

GlobalDescriptorTableEntry_t gdt[3];
GlobalDescriptorTableRegister_t gdtRegister;

InterruptDescriptorTableEntry_t idt[256];
InterruptDescriptorTableRegister_t idtRegister;

extern "C" void SkylightEntry(
	PMemoryDescriptor_t table,
	size_t length,
	size_t descriptorSize
) {
	Terminal::PrintFormat("Loading GDT...\t");
	GlobalDescriptorTableManager::Select(gdt, sizeof(gdt)/sizeof(gdt[0]));
	GlobalDescriptorTableManager::SetEntry(0, 0, 0, 0, 0);
	GlobalDescriptorTableManager::SetEntry(1, 0xffff, 0, 0x9a, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	GlobalDescriptorTableManager::SetEntry(2, 0xffff, 0, 0x92, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	GlobalDescriptorTableManager::Load();

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nLoading IDT, exception handlers...\t",	TERMINAL_COLOR_LIME);
	InterruptDescriptorTableManager::Select(idt, sizeof(idt)/sizeof(idt[0]));
	InterruptDescriptorTableManager::Load();

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nLoading exception handlers...\t", TERMINAL_COLOR_LIME);
	ExceptionsManager::Initialize(KERNEL_CODE_SEGMENT);

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nMasking & remapping & loading hardware interrupts...\t", TERMINAL_COLOR_LIME);
	HardwareInterruptsManager::Initialize(KERNEL_CODE_SEGMENT);

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nInitializing PIT...\t", TERMINAL_COLOR_LIME);
	ProgrammableIntervalTimer::Initialize();

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nParsing ACPI tables...\t", TERMINAL_COLOR_LIME);
	if (!AdvancedPowerAndConfigurationInterface::Initialize()) {
		Terminal::PrintFormat("[%ebFAILED%ee]\r\n", TERMINAL_COLOR_RED);
		DeclareAssembly("jmp .");
	}
	
	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nInitializing MDT...\t", TERMINAL_COLOR_LIME);

	Memory::Select(table, descriptorSize, length);
	Memory::Exclude(IVT_BEGIN, IVT_LENGTH);
	Memory::Exclude(BDA_BEGIN, BDA_LENGTH);
	Memory::Exclude(KERNEL_BEGIN, KERNEL_LENGTH);
	Memory::Exclude((size_t)table, (length + 2) * descriptorSize);
	Memory::Exclude(EBDA_BEGIN, EBDA_LENGTH);
	Memory::Exclude(ISA_HOLE_BEGIN, ISA_HOLE_LENGTH);

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\n", TERMINAL_COLOR_LIME);

	DeclareAssembly("jmp .");

	Terminal::PrintFormat("Actions completed. Shutdown...\r\n");
	AdvancedPowerAndConfigurationInterface::Shutdown();
}