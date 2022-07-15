;	Input:
;	ax - count
;	dh - head, dl - drive
;	cx - start cylinder and sector
;	es:bx - address
disk_read_sectors:
	push ax
	push cx
	push dx
	push bx
	push si
	push di

	mov di, ax

	disk_read_sectors_loop:
		dec di
		mov ax, 0x0201
		int 0x13
		add bx, 0x0200
	disk_read_sectors_loop_incremented_buffer:
		mov si, cx
		and si, 0x003f
		cmp si, 0x003f
		jl disk_read_sectors_loop_inc_sector
		cmp dh, 0xff
		jl disk_read_sectors_loop_inc_head
		cmp ch, 0xff
		jl disk_read_sectors_loop_inc_low_cylinder
		mov dh, 0x00
		and cl, 0xc0
		mov ch, 0x00
		add cl, 0x40
		jmp disk_read_sectors_loop_head_incremented_sector
	disk_read_sectors_loop_inc_low_cylinder:
		mov dh, 0x00
		and cl, 0xc0
		inc ch
		jmp disk_read_sectors_loop_head_incremented_sector
	disk_read_sectors_loop_inc_head:
		inc dh
		and cl, 0xc0
		jmp disk_read_sectors_loop_head_incremented_sector
	disk_read_sectors_loop_inc_sector:
		inc cl
	disk_read_sectors_loop_head_incremented_sector:
		test bx, bx
		jnz disk_read_sectors_loop_bx_incremented

		push es
		pop bx
		inc bx
		pop bx
		pop es
		mov bx, 0x0000
	disk_read_sectors_loop_bx_incremented:
		test di, di
		jnz disk_read_sectors_loop

	pop di
	pop si
	pop bx
	pop dx
	pop cx
	pop ax
	ret