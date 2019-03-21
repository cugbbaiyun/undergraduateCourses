data segment
	array	dw 4,78,34,100,5ah,6b3h,1,0f234h,6,10
	n		dw 10
	max		dw ?
data ends

code segment
	assume cs:code,ds:data
start:
	mov ax,data
	mov ds,ax

	mov cx,n
	mov bx,0
	mov ax,array[bx]
findmax:
	cmp ax,array[bx]
	jae repq
	mov ax,array[bx]
repq:
	add bx,2
	dec cx
	ja findmax
	mov max,ax
	
	mov bx,ax

	mov ch,4
sbits:
	mov cl,4
	rol bx,cl
	mov al,bl
	and al,0fh
	add al,30h
	cmp al,3ah
	jl output
	add al,7h

output:
	mov dl,al
	mov ah,02h
	int 21h
	dec ch
	jnz sbits

	mov ax,4c00h
	int 21h
code ends 
	end start
