#include "tty.h"

WORD ttyCursorPosition = 0;
BYTE ttySelectedColor = TTY_COLOR_GRAY;
PBYTE ttyBuffer = (PBYTE)TTY_BUFFER_ADDRESS;

VOID TtySelectColor(
	BYTE bColor
) {
	ttySelectedColor = bColor;
}

VOID TtyPutChar(
	const CHAR ccCharacter
) {
	if (ttyCursorPosition >= TTY_SIZE) {
		MemoryCopy(ttyBuffer, (PVOID)((SIZE_T)ttyBuffer + TTY_WIDTH_SIZE), TTY_SIZE - TTY_WIDTH_SIZE);
		MemorySet((PVOID)((SIZE_T)ttyBuffer + TTY_SIZE - TTY_WIDTH_SIZE), 0, TTY_WIDTH_SIZE);
		ttyCursorPosition = TTY_SIZE - TTY_WIDTH_SIZE;
	}

	ttyBuffer[ttyCursorPosition++] = ccCharacter;
	ttyBuffer[ttyCursorPosition++] = ttySelectedColor;
}

VOID TtyPutString(
	const char* cpString
) {
	for (SIZE_T i = 0; cpString[i]; i++) {
		if (cpString[i] == '\t') ttyCursorPosition += (TTY_TAB_LENGTH << 1) - (ttyCursorPosition & (TTY_TAB_LENGTH << 1));
		else if (cpString[i] == '\v') ttyCursorPosition += TTY_WIDTH_SIZE << 2;
		else if (cpString[i] == '\r') ttyCursorPosition -= ttyCursorPosition % TTY_WIDTH_SIZE;
		else if (cpString[i] == '\n') ttyCursorPosition += TTY_WIDTH_SIZE;
		else if (cpString[i] == '\b') --i;
		else TtyPutChar(cpString[i]);
	}
}

VOID TtyPrintFormat(
	const char* cpFormat,
	...
) {
	BYTE bSelectedColor = ttySelectedColor;
	PSIZE_T pArgument = (PSIZE_T)((SIZE_T)&cpFormat + sizeof(PCHAR));
	for (SIZE_T i = 0; cpFormat[i]; i++) {
		if (cpFormat[i] == '%') {
			++i;
			if (cpFormat[i] == '%') TtyPutChar('%');
			else if (cpFormat[i] == 'c') TtyPutChar(*(PCHAR)pArgument++);
			else if (cpFormat[i] == 's') TtyPutString((PCHAR)pArgument++);
			else if (cpFormat[i] == 'e') {
				++i;
				if (cpFormat[i] == 'b') ttySelectedColor = (BYTE)*pArgument++;
				else if (cpFormat[i] == 'e') ttySelectedColor = bSelectedColor;
			}
		}
		else if (cpFormat[i] == '\t') ttyCursorPosition += (TTY_TAB_LENGTH << 1) - (ttyCursorPosition & (TTY_TAB_LENGTH << 1));
		else if (cpFormat[i] == '\v') ttyCursorPosition += TTY_WIDTH_SIZE << 2;
		else if (cpFormat[i] == '\r') ttyCursorPosition -= ttyCursorPosition % TTY_WIDTH_SIZE;
		else if (cpFormat[i] == '\n') ttyCursorPosition += TTY_WIDTH_SIZE;
		else if (cpFormat[i] == '\b') --i;
		else TtyPutChar(cpFormat[i]);
	}
	ttySelectedColor = bSelectedColor;
}