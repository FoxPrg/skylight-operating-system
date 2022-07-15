;	Input:
;	es:di - table address
;	Output:
;	es:di - filled table
;	si - entries count
;	cl - size of entry
memory_get_map:
	push eax
	push ecx
	push edx
	push ebx
	push di
	mov si, 0
	mov edx, 0x534d4150
	mov ebx, 0x00000000
	mov eax, 0x0000e820
	mov ecx, 0x00000018
	int 0x15
	jc memory_get_map_end
	inc si
	mov ch, 0
	add di, cx
	mov [memory_get_map_entry_size], cl
	memory_get_map_loop:
		mov eax, 0x0000e820
		mov ecx, 0x00000018
		int 0x15
		jc memory_get_map_end

		mov ch, 0
		add di, cx
		inc si

		test ebx, ebx
		jnz memory_get_map_loop
	memory_get_map_end:
		pop di
		pop ebx
		pop edx
		pop ecx
		pop eax
		mov cl, [memory_get_map_entry_size]
		ret
memory_get_map_entry_size:	db	0x00

;	Input:
;	eax - address
;	ebx - alignment
;	Output:
;	eax - aligned address
memory_align_address:
	push ebx
	dec ebx
	add eax, ebx
	not ebx
	and eax, ebx
	pop ebx
	ret