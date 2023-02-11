;division using external memory access
org 00h
	mov dptr, #4000h
	movx a, @dptr
	inc dptr
	movx a, @dptr
	inc dptr
	div ab
	end
