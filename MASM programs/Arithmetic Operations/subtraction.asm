;MASM program for 16-bit subtraction

.model small
.data
.stack
.code
mov ax, @data
mov ds, ax
mov ax, 7779h
mov bx, 1234h
sub ax, bx
 
mov cx, 04h
mov dx, 0h
item: mov bx, 10h
div bx
push dx
dec cx
cmp cx, 0h
je update
xor dx, dx
;clear dx
jmp item
update: mov cx, 4
print1: cmp cx, 0
je exit
pop dx
cmp dx, 0ah
jge alpha
add dx, 48
jmp incre
alpha: add dx, 55
;55 in decimal
incre: mov ah, 02h
int 21h
dec cx
jmp print1
exit: mov ah, 4ch
int 21h
.exit
end
