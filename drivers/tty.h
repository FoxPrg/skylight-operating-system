#ifndef TTY_H
#define TTY_H

#include "memory.h"
#include "string.h"

#define TTY_BUFFER_ADDRESS		0xb8000
#define TTY_WIDTH				80
#define TTY_WIDTH_SIZE			160
#define TTY_HEIGHT				25
#define TTY_SIZE				0xfa0
#define TTY_TAB_LENGTH			4

#define TTY_COLOR_BLACK			0
#define TTY_COLOR_BLUE			1
#define TTY_COLOR_GREEN			2
#define TTY_COLOR_CYAN			3
#define TTY_COLOR_RED			4
#define TTY_COLOR_MAGENTA		5
#define TTY_COLOR_BROWN			6
#define TTY_COLOR_GRAY			7
#define TTY_COLOR_IRIDIUM		8
#define TTY_COLOR_AZURE			9
#define TTY_COLOR_LIME			10
#define TTY_COLOR_TURQUOIISE	11
#define TTY_COLOR_RUBY			12
#define TTY_COLOR_PURPLE		13
#define TTY_COLOR_YELLOW		14
#define TTY_COLOR_WHITE			15

extern word_t ttyCursorPosition;
extern byte_t ttySelectedColor;
extern pbyte_t ttyBuffer;

void TtySelectColor(
	byte_t bColor
);

void TtyPutChar(
	const char ccCharacter
);

void TtyPutString(
	const char* cpString
);

void TtyPrintFormat(
	const char* cpFormat,
	...
);

#endif