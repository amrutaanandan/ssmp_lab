.model small
.data
.stack
.code
mov ax, 0
mov dx, ax
add dx, 48
mov ah, 02h
int 21h
mov bx, 1
mov dx, bx
add dx, 48
mov ah, 02h
int 21h
mov cx, 0005h
xor ax, ax
jmp l1

l1: add ax, bx
mov dx, ax
add dx, 48
mov ah, 02h
int 21h
mov ah, 0h
sub al, 30h
xor dx, dx
mov dx, ax
mov ax, bx
mov bx, dx
xor dx, dx
dec cx
jnz l1

.exit
end
