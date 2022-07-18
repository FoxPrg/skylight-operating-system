#include "skylight.h"

GlobalDescriptorTableEntry_t gdt[3];
GlobalDescriptorTableRegister_t gdtRegister;

InterruptDescriptorTableEntry_t idt[256];
InterruptDescriptorTableRegister_t idtRegister;

extern "C" void SkylightEntry(PMemoryDescriptor_t table, size_t length) {
	Terminal::PrintFormat("Loading GDT...\t");
	GlobalDescriptorTableManager::Select(gdt, sizeof(gdt)/sizeof(gdt[0]));
	GlobalDescriptorTableManager::SetEntry(0, 0, 0, 0, 0);						//	null descriptor
	GlobalDescriptorTableManager::SetEntry(1, 0xffff, 0, GDT_ACCESS_READ_WRITE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_SYSTEM | GDT_ACCESS_PRESENT, 
		GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);						//	code
	GlobalDescriptorTableManager::SetEntry(2, 0xffff, 0, GDT_ACCESS_READ_WRITE | GDT_ACCESS_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);						//	data
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

	Memory::Select(table, length);

	Terminal::PrintFormat("[%ebSUCCESS%ee]\r\nRegions (%u):\r\n", TERMINAL_COLOR_LIME, length);
	PMemoryDescriptor_t pdecsr;
	for (size_t i = 0; i < length; i++) {
		pdecsr = Memory::GetDescriptor(i);
		Terminal::PrintFormat("\tAddress: %eb0x%X%ee\tLength: %eb0x%X%ee\tType: %eb%u%ee\r\n",
			TERMINAL_COLOR_AZURE, (size_t)pdecsr->Address, TERMINAL_COLOR_AZURE, (size_t)pdecsr->Length, TERMINAL_COLOR_AZURE, (size_t)pdecsr->Type);
	}

	DeclareAssembly("jmp .");

	Terminal::PrintFormat("Actions completed. Shutting down...\r\n");
	AdvancedPowerAndConfigurationInterface::Shutdown();
}