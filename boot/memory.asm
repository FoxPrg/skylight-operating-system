;	Input:
;	es:di - table address
;	Output:
;	es:di - filled table
;	si - entries count
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
	memory_get_map_loop:

		cmp cl, 0x18
		jl memory_get_map_loop_next
		mov eax, [di+0x14]							;	if it's bad memory
		and eax, 0x00000001
		test eax, eax
		jnz memory_get_map_loop_next

		mov dword [di+0x10], 0x00000002				;	mark as reserved
	memory_get_map_loop_next:
		add di, 0x14
		inc si

		mov eax, 0x0000e820
		mov ecx, 0x00000018
		int 0x15
		jc memory_get_map_end

		test ebx, ebx
		jnz memory_get_map_loop
	memory_get_map_end:
		pop di
		pop ebx
		pop edx
		pop ecx
		pop eax
		ret

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