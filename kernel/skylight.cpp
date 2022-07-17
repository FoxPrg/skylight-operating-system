#include "skylight.h"

GlobalDescriptorTableEntry_t gdt[3];
GlobalDescriptorTableRegister_t gdtRegister;

InterruptDescriptorTableEntry_t idt[256];
InterruptDescriptorTableRegister_t idtRegister;

extern "C" void SkylightEntry() {
	TtyPrintFormat("Loading GDT...\t", TTY_COLOR_YELLOW);
	SelectGdt(gdt, sizeof(gdt)/sizeof(gdt[0]));
	InitializeGdtEntry(0, 0, 0, 0, 0);
	InitializeGdtEntry(1, 0xffff, 0, 0x9a, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	InitializeGdtEntry(2, 0xffff, 0, 0x92, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	LoadGdt();

	TtyPrintFormat("[%ebSUCCESS%ee]\r\n\tSize: 0x%X  Offset: 0x%X\r\nLoading IDT, exception handlers...\t",	
		TTY_COLOR_LIME, gdtSelectedRegister.Size + 1, gdtSelectedRegister.Offset);
	SelectIdt(idt, sizeof(idt)/sizeof(idt[0]));
	LoadIdt();

	TtyPrintFormat("[%ebSUCCESS%ee]\r\n\tSize: 0x%X  Offset: 0x%X\r\nLoading exception handlers...\t",
		TTY_COLOR_LIME, idtSelectedRegister.Size + 1, idtSelectedRegister.Offset);
	InitializeExceptions(KERNEL_CODE_SEGMENT);

	TtyPrintFormat("[%ebSUCCESS%ee]\r\nMasking & remapping & loading hardware interrupts...\t", TTY_COLOR_LIME);
	InitializeHardwareInterrupts(KERNEL_CODE_SEGMENT);

	TtyPrintFormat("[%ebSUCCESS%ee]\r\nInitializing PIT...\t", TTY_COLOR_LIME);
	PitInitialize();

	TtyPrintFormat("[%ebSUCCESS%ee]\r\nParsing ACPI tables...\t", TTY_COLOR_LIME);
	if (!AcpiInitialize()) {
		TtyPrintFormat("[%ebFAILED%ee]\r\n", TTY_COLOR_RED);
		DeclareAssembly("jmp .");
	}
	
	TtyPrintFormat("[%ebSUCCESS%ee]\r\n\tSMI command port: 0x%X\r\n", TTY_COLOR_LIME, acpiSmiCommandPort);

	DeclareAssembly("jmp .");
}