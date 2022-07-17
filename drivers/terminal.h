#ifndef TERMINAL_H
#define TERMINAL_H

#include "memory.h"
#include "string.h"

#define TERMINAL_BUFFER_ADDRESS		0xb8000
#define TERMINAL_WIDTH				80
#define TERMINAL_WIDTH_SIZE			160
#define TERMINAL_HEIGHT				25
#define TERMINAL_SIZE				0xfa0
#define TERMINAL_TAB_LENGTH			4

#define TERMINAL_COLOR_BLACK			0
#define TERMINAL_COLOR_BLUE			1
#define TERMINAL_COLOR_GREEN			2
#define TERMINAL_COLOR_CYAN			3
#define TERMINAL_COLOR_RED			4
#define TERMINAL_COLOR_MAGENTA		5
#define TERMINAL_COLOR_BROWN			6
#define TERMINAL_COLOR_GRAY			7
#define TERMINAL_COLOR_IRIDIUM		8
#define TERMINAL_COLOR_AZURE			9
#define TERMINAL_COLOR_LIME			10
#define TERMINAL_COLOR_TURQUOIISE	11
#define TERMINAL_COLOR_RUBY			12
#define TERMINAL_COLOR_PURPLE		13
#define TERMINAL_COLOR_YELLOW		14
#define TERMINAL_COLOR_WHITE			15

class Terminal {
	public:
	static void SetColor(byte_t color);
	static void PutChar(const char character);
	static void PutString(const char* str);
	static void PrintFormat(const char* format, ...);
	private:
	static word_t m_position;
	static byte_t m_color;
	static pbyte_t m_buffer;
	static char m_conversionBuffer[66];
};

#endif