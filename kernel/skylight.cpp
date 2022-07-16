#include "skylight.h"

GLOBAL_DESCRIPTOR_TABLE_ENTRY gdt[3];
GLOBAL_DESCRIPTOR_TABLE_REGISTER gdtRegister;

INTERRUPT_DESCRIPTOR_TABLE_ENTRY idt[256];
INTERRUPT_DESCRIPTOR_TABLE_REGISTER idtRegister;

EXTERN_C VOID CpuExceptionHandler(PCPU_REQUEST_REGISTERS pRegisters) {
	((PBYTE)0xb8000)[pRegisters->InterruptIndex << 1] = 'A' + pRegisters->InterruptIndex;
}

EXTERN_C VOID CpuHardwareInterruptRequestHandler(PCPU_REQUEST_REGISTERS pRegisters) {
	((PBYTE)0xb8000)[pRegisters->InterruptIndex << 1] = 'a' + pRegisters->InterruptIndex - 32;
	PicSendEndOfInterrupt(pRegisters->InterruptIndex);
}

EXTERN_C VOID SkylightEntry() {
	TtyPrintFormat("Loading GDT...\t", TTY_COLOR_YELLOW);

	InitializeGdtEntry(&gdt[0], 0, 0, 0, 0);
	InitializeGdtEntry(&gdt[1], 0xffff, 0, 0x9a, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	InitializeGdtEntry(&gdt[2], 0xffff, 0, 0x92, GDT_FLAG_PROTECTED_MODE | GDT_FLAG_GRANULARITY);
	InitializeGdtRegister(&gdtRegister, gdt, sizeof(gdt)/sizeof(gdt[0]));
	LoadGdtRegister(&gdtRegister);

	TtyPrintFormat("%ebDONE%ee\r\nLoading IDT, exception handlers...\t", TTY_COLOR_LIME);

	InitializeIdtEntry(&idt[0], (SIZE_T)CpuExceptionStub0, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[1], (SIZE_T)CpuExceptionStub1, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[2], (SIZE_T)CpuExceptionStub2, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[3], (SIZE_T)CpuExceptionStub3, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[4], (SIZE_T)CpuExceptionStub4, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[5], (SIZE_T)CpuExceptionStub5, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[6], (SIZE_T)CpuExceptionStub6, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[7], (SIZE_T)CpuExceptionStub7, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[8], (SIZE_T)CpuExceptionStub8, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[9], (SIZE_T)CpuExceptionStub9, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[10], (SIZE_T)CpuExceptionStub10, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[11], (SIZE_T)CpuExceptionStub11, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[12], (SIZE_T)CpuExceptionStub12, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[13], (SIZE_T)CpuExceptionStub13, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[14], (SIZE_T)CpuExceptionStub14, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[15], (SIZE_T)CpuExceptionStub15, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[16], (SIZE_T)CpuExceptionStub16, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[17], (SIZE_T)CpuExceptionStub17, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[18], (SIZE_T)CpuExceptionStub18, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[19], (SIZE_T)CpuExceptionStub19, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[20], (SIZE_T)CpuExceptionStub20, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[21], (SIZE_T)CpuExceptionStub21, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[22], (SIZE_T)CpuExceptionStub22, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[23], (SIZE_T)CpuExceptionStub23, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[24], (SIZE_T)CpuExceptionStub24, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[25], (SIZE_T)CpuExceptionStub25, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[26], (SIZE_T)CpuExceptionStub26, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[27], (SIZE_T)CpuExceptionStub27, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[28], (SIZE_T)CpuExceptionStub28, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[29], (SIZE_T)CpuExceptionStub29, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[30], (SIZE_T)CpuExceptionStub30, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[31], (SIZE_T)CpuExceptionStub31, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtRegister(&idtRegister, idt, sizeof(idt)/sizeof(idt[0]));
	LoadIdtRegister(&idtRegister);

	TtyPrintFormat("%ebDONE%ee\r\nMasking & remapping hardware interrupts...\t", TTY_COLOR_LIME);

	PicMaskAll();
	PicRemapVectors(0x20, 0x28);

	TtyPrintFormat("%ebDONE%ee\r\nLoading hardware interrupt handlers...\t", TTY_COLOR_LIME);

	InitializeIdtEntry(&idt[32], (SIZE_T)CpuHardwareInterruptRequestStub0, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[33], (SIZE_T)CpuHardwareInterruptRequestStub1, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[34], (SIZE_T)CpuHardwareInterruptRequestStub2, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[35], (SIZE_T)CpuHardwareInterruptRequestStub3, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[36], (SIZE_T)CpuHardwareInterruptRequestStub4, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[37], (SIZE_T)CpuHardwareInterruptRequestStub5, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[38], (SIZE_T)CpuHardwareInterruptRequestStub6, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[39], (SIZE_T)CpuHardwareInterruptRequestStub7, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[40], (SIZE_T)CpuHardwareInterruptRequestStub8, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[41], (SIZE_T)CpuHardwareInterruptRequestStub9, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[42], (SIZE_T)CpuHardwareInterruptRequestStub10, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[43], (SIZE_T)CpuHardwareInterruptRequestStub11, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[44], (SIZE_T)CpuHardwareInterruptRequestStub12, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[45], (SIZE_T)CpuHardwareInterruptRequestStub13, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[46], (SIZE_T)CpuHardwareInterruptRequestStub14, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	InitializeIdtEntry(&idt[47], (SIZE_T)CpuHardwareInterruptRequestStub15, KERNEL_CODE_SEGMENT, IDT_FLAG_GATE_INT32 | IDT_FLAG_DPL_KERNEL | IDT_FLAG_PRESENT);
	DeclareAssembly("sti");

	TtyPrintFormat("%ebDONE%ee\r\n", TTY_COLOR_LIME);

	DeclareAssembly("jmp .");
}