#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "idt.h"

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
}

extern InterruptHandler_t exceptionHandlers[32];

void InitializeExceptions(
	word_t codeSegment
);

void InitializeExceptionHandler(
	size_t index,
	InterruptHandler_t exceptionHandler
);

extern "C" void FinalExceptionHandler(
	PInterruptHandlerRegisters_t pRegisters
);

#endif