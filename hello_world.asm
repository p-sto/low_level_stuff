%include "io_x64lib.inc"

section .text:
	global _start

section .data:
	text: db 'Hello, World', 10, 0

_start:
	GETSTRLEN text
	mov	rdx, rax
	PRINT text, rdx
	

	EXIT 0


