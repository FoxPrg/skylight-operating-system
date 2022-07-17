#include "tty.h"

word_t ttyCursorPosition = 0;
byte_t ttySelectedColor = TTY_COLOR_GRAY;
pbyte_t ttyBuffer = (pbyte_t)TTY_BUFFER_ADDRESS;

int8_t ttyConversionBuffer[66];

void TtySelectColor(
	byte_t bColor
) {
	ttySelectedColor = bColor;
}

void TtyPutChar(
	const char ccCharacter
) {
	if (ttyCursorPosition >= TTY_SIZE) {
		MemoryCopy(ttyBuffer, (void*)((size_t)ttyBuffer + TTY_WIDTH_SIZE), TTY_SIZE - TTY_WIDTH_SIZE);
		MemorySet((void*)((size_t)ttyBuffer + TTY_SIZE - TTY_WIDTH_SIZE), 0, TTY_WIDTH_SIZE);
		ttyCursorPosition = TTY_SIZE - TTY_WIDTH_SIZE;
	}

	ttyBuffer[ttyCursorPosition++] = ccCharacter;
	ttyBuffer[ttyCursorPosition++] = ttySelectedColor;
}

void TtyPutString(
	const char* cpString
) {
	for (size_t i = 0; cpString[i]; i++) {
		if (cpString[i] == '\t')  {
			word_t div_mod = ttyCursorPosition % (TTY_TAB_LENGTH << 1);
			if (!div_mod) ttyCursorPosition += (TTY_TAB_LENGTH << 1);
			else ttyCursorPosition += (TTY_TAB_LENGTH << 1) - div_mod;
		}
		else if (cpString[i] == '\v') ttyCursorPosition += TTY_WIDTH_SIZE << 2;
		else if (cpString[i] == '\r') ttyCursorPosition -= ttyCursorPosition % TTY_WIDTH_SIZE;
		else if (cpString[i] == '\n') ttyCursorPosition += TTY_WIDTH_SIZE;
		else if (cpString[i] == '\b') --i;
		else TtyPutChar(cpString[i]);
	}
}

void TtyPrintFormat(
	const char* cpFormat,
	...
) {
	byte_t bSelectedColor = ttySelectedColor;
	psize_t pArgument = (psize_t)((size_t)&cpFormat + sizeof(char*));
	byte_t notation;
	
	for (size_t i = 0; cpFormat[i]; i++) {
		if (cpFormat[i] == '%') {
			++i;
			if (cpFormat[i] == '%') TtyPutChar('%');
			else if (cpFormat[i] == 'c') TtyPutChar(*(char*)pArgument++);
			else if (cpFormat[i] == 's') TtyPutString((char*)pArgument++);
			else if (cpFormat[i] == 'e') {
				++i;
				if (cpFormat[i] == 'b') ttySelectedColor = (byte_t)*pArgument++;
				else if (cpFormat[i] == 'e') ttySelectedColor = bSelectedColor;
			}
			else if (cpFormat[i] == 'b' || cpFormat[i] == 'o' || cpFormat[i] == 'u' || cpFormat[i] == 'x') {
				if (cpFormat[i] == 'b') notation = 2;
				else if (cpFormat[i] == 'o') notation = 8;
				else if (cpFormat[i] == 'u') notation = 10;
				else if (cpFormat[i] == 'x') notation = 16;
				StringFromUnsigned((decimal_t)*pArgument++, notation, ttyConversionBuffer);
				TtyPutString(ttyConversionBuffer);
			}
			else if (cpFormat[i] == 'd') {
				StringFromSigned((decimal_t)*pArgument++, 10, ttyConversionBuffer);
				TtyPutString(ttyConversionBuffer);
			}
			else if (cpFormat[i] == 'X') {
				StringFromUnsigned((decimal_t)*pArgument++, 16, ttyConversionBuffer);
				for (size_t i = 0; ttyConversionBuffer[i]; i++)
					if (ttyConversionBuffer[i] >= 'a' && ttyConversionBuffer[i] <= 'f') ttyConversionBuffer[i] &= '_';
				TtyPutString(ttyConversionBuffer);
			}
		}
		else if (cpFormat[i] == '\t') {
			word_t div_mod = ttyCursorPosition % (TTY_TAB_LENGTH << 1);
			if (!div_mod) ttyCursorPosition += (TTY_TAB_LENGTH << 1);
			else ttyCursorPosition += (TTY_TAB_LENGTH << 1) - div_mod;
		}
		else if (cpFormat[i] == '\v') ttyCursorPosition += TTY_WIDTH_SIZE << 2;
		else if (cpFormat[i] == '\r') ttyCursorPosition -= ttyCursorPosition % TTY_WIDTH_SIZE;
		else if (cpFormat[i] == '\n') ttyCursorPosition += TTY_WIDTH_SIZE;
		else if (cpFormat[i] == '\b') --i;
		else TtyPutChar(cpFormat[i]);
	}
	ttySelectedColor = bSelectedColor;
}