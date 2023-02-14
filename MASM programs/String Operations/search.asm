.model small
.data
text db "Hello World$"
msg1 db "Enter character to search: $"
msg2 db "Character Found$"
msg3 db "Character Not Found$"
.code
mov ax, @data
mov ds, ax

lea dx, msg1  ;print msg1
mov ah, 09h
int 21h

mov ah, 01h
int 21h

mov bl, al  ;storing read value in bl

xor dx, dx
mov dl, 10
mov ah, 02h
int 21h

lea si, text
mov al, '$' ;string termination character

l1: 
	cmp bl, [si]  ;compare read character to character in string
	jz l3 ;if found
	cmp al, [si]  ;compare if current character == '$' (end of string)
	jz l2 ;if end of string
	inc si
	jmp l1

l2: lea dx, msg3  ;print character not found
mov ah, 09h
int 21h
.exit

l3: lea dx, msg2  ;print character found
mov ah, 09h
int 21h
.exit
end
