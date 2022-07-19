#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "idt.h"

class ExceptionsManager {
	public:
	static void Initialize(word_t codeSegment);
	static void SetHandler(size_t index, InterruptHandler_t handler);
	static InterruptHandler_t GetHandler(size_t index);
	private:
	static InterruptHandler_t m_handlers[32];
};

#endif