#include "terminal.h"

word_t Terminal::m_position = 0;
byte_t Terminal::m_color = TERMINAL_COLOR_GRAY;
pbyte_t Terminal::m_buffer = (pbyte_t)TERMINAL_BUFFER_ADDRESS;
char Terminal::m_conversionBuffer[66];

void Terminal::SetColor(byte_t color) {
	m_color = color;
}

void Terminal::PutChar(const char character) {
	if (m_position >= TERMINAL_SIZE) {
		Memory::Copy(m_buffer, (void*)((size_t)m_buffer + TERMINAL_WIDTH_SIZE), TERMINAL_SIZE - TERMINAL_WIDTH_SIZE);
		Memory::Set((void*)((size_t)m_buffer + TERMINAL_SIZE - TERMINAL_WIDTH_SIZE), 0, TERMINAL_WIDTH_SIZE);
		m_position = TERMINAL_SIZE - TERMINAL_WIDTH_SIZE;
	}

	m_buffer[m_position++] = character;
	m_buffer[m_position++] = m_color;
}

void Terminal::PutString(const char* str) {
	word_t div_mod;
	for (size_t i = 0; str[i]; i++) {
		if (str[i] == '\t')  {
			div_mod = m_position % (TERMINAL_TAB_LENGTH << 1);
			if (!div_mod) m_position += (TERMINAL_TAB_LENGTH << 1);
			else m_position += (TERMINAL_TAB_LENGTH << 1) - div_mod;
		}
		else if (str[i] == '\v') m_position += TERMINAL_WIDTH_SIZE << 2;
		else if (str[i] == '\r') m_position -= m_position % TERMINAL_WIDTH_SIZE;
		else if (str[i] == '\n') m_position += TERMINAL_WIDTH_SIZE;
		else if (str[i] == '\b') --i;
		else PutChar(str[i]);
	}
}

void Terminal::PrintFormat(const char* format, ...) {
	const byte_t color = m_color;
	psize_t pArgument = (psize_t)((size_t)&format + sizeof(char*));
	byte_t notation;
	
	for (size_t i = 0; format[i]; i++) {
		if (format[i] == '%') {
			++i;
			if (format[i] == '%') PutChar('%');
			else if (format[i] == 'c') PutChar(*(char*)pArgument++);
			else if (format[i] == 's') PutString((char*)pArgument++);
			else if (format[i] == 'e') {
				++i;
				if (format[i] == 'b') m_color = (byte_t)*pArgument++;
				else if (format[i] == 'e') m_color = color;
			}
			else if (format[i] == 'b' || format[i] == 'o' || format[i] == 'u' || format[i] == 'x') {
				if (format[i] == 'b') notation = 2;
				else if (format[i] == 'o') notation = 8;
				else if (format[i] == 'u') notation = 10;
				else if (format[i] == 'x') notation = 16;
				String::FromUnsigned((decimal_t)*pArgument++, notation, m_conversionBuffer);
				PutString(m_conversionBuffer);
			}
			else if (format[i] == 'd') {
				String::FromSigned((decimal_t)*pArgument++, 10, m_conversionBuffer);
				PutString(m_conversionBuffer);
			}
			else if (format[i] == 'X') {
				String::FromUnsigned((decimal_t)*pArgument++, 16, m_conversionBuffer);
				for (size_t i = 0; m_conversionBuffer[i]; i++)
					if (m_conversionBuffer[i] >= 'a' && m_conversionBuffer[i] <= 'f') m_conversionBuffer[i] &= '_';
				PutString(m_conversionBuffer);
			}
		}
		else if (format[i] == '\t') {
			word_t div_mod = m_position % (TERMINAL_TAB_LENGTH << 1);
			if (!div_mod) m_position += (TERMINAL_TAB_LENGTH << 1);
			else m_position += (TERMINAL_TAB_LENGTH << 1) - div_mod;
		}
		else if (format[i] == '\v') m_position += TERMINAL_WIDTH_SIZE << 2;
		else if (format[i] == '\r') m_position -= m_position % TERMINAL_WIDTH_SIZE;
		else if (format[i] == '\n') m_position += TERMINAL_WIDTH_SIZE;
		else if (format[i] == '\b') --i;
		else PutChar(format[i]);
	}
	m_color = color;
}