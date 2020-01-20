%include "io_x64lib.inc"

section .text:
	global _start

section .data:
	text: db 'Hello, World', 10, 0

_start:
	mov rax, text
	call	_print	

	EXIT 0

_print:
	push 	rax
	mov 	rbx, 0	
_printloop:
	inc	rax
	inc	rbx		; rbx is used to count lenght of string
	mov	cl, [rax]	; cl is 8-bit part of rcx
	cmp	cl, 0
	jne	_printloop

	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	pop	rsi
	mov	rdx, rbx
	syscall

	ret


