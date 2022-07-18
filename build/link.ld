ENTRY(SkylightEntry)
OUTPUT_FORMAT(binary)
SECTIONS {
	SkylightBegin = 0x0c00;
	. = SkylightBegin;

	.header : {
		LONG(SkylightEntry);					/*entry point*/
		LONG(SkylightEnd - SkylightBegin);		/*kernel length*/
		LONG(StackTop);							/*stack top*/
	}

	. = ALIGN(4);
	StackBottom = .;
	.stack : {
		. = . + 16k;
	}
	. = ALIGN(4);
	StackTop = .;

	.text : {
		*(.text)
	}

	.data : {
		*(.data)
	}

	.rodata : {
		*(.rodata)
	}

	.bss : {
		*(.bss)
	}

	SkylightEnd = .;
}