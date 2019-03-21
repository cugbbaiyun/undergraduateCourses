data segment 
	s1 db 'personal computer'
	s2 db 'personal computer'
	mess1 db 'match.$'
	mess2 db 'not match.$'
data ends

code segment
	assume cs:code,ds:data
start: 
	mov ax,data
	mov ds,ax
	mov es,ax

	lea si,s1
	lea di,s2
	mov cx,17
	cld
	repe cmpsb
	jz match

	lea dx,mess2
	jmp output 

match:
	lea dx,mess1
output:
	mov ah,09h
	int 21h

	mov ax,4c00h
	int 21h
code ends
	end start
