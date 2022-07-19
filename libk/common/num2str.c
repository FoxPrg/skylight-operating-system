#include "num2str.h"

char g_Num2StrConversionBuffer[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'	
};

void StringFromUInt64(uint64_t Value, uint8_t Base, puint8_t Buffer) {
	uint64_t valueCopy = Value;
	size_t length = 0;

	do {
		valueCopy /= Base;
		++length;
	} while(valueCopy != 0);

	Buffer[length] = 0;

	for (size_t i = 0; i < length; i++) {
		Buffer[length - i - 1] = g_Num2StrConversionBuffer[Value % Base];
		Value /= Base;
	}
}

void StringFromInt64(int64_t Value, uint8_t Base, puint8_t Buffer) {
	if (Value < 0) {
		*Buffer = '-';
		Value = -Value;
		StringFromUInt64(Value, Base, Buffer + 1);
	}
	else StringFromUInt64(Value, Base, Buffer);
}