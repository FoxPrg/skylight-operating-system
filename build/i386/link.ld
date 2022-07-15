ENTRY(SkylightEntry)
OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)
SECTIONS {
	SkylightBegin = 0x0c00;
	. = SkylightBegin;

	.header : {
		LONG(SkylightEntry);					/*entry point*/
		LONG(SkylightEnd - SkylightBegin);		/*kernel length*/
	}

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