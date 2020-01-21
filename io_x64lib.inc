; io_x64lib.inc
; library containing macros and definitions for basic IO functions implementations for nasm
; author: Pawel Stoworowicz
; contact: pawel.stoworowicz@gmail.com

; --- System calls mappings

SYS_WRITE	equ 1
SYS_EXIT	equ 60


; --- Descriptors mappings

STDIN		equ 0
STDOUT		equ 1
STDERR		equ 2


; --- File operations mappings



; --- macros

%macro EXIT 1
	mov	rax, SYS_EXIT
	mov	rdi, %1
	syscall 
%endmacro

; calcultes lenght of string including null and return value in rax
%macro GETSTRLEN 1		; first arg is reference to string
	mov	rax, %1
	mov	rbx, 0		; counter set to 0	
%%loop:
	inc	rbx
	inc	rax
	mov	cl, [rax]	; copy 1 byte of rax adress to cl
	cmp	cl, 0
	jne	%%loop	
	mov	rax, rbx
	
%endmacro

%macro PRINT 2	; arg1: text to be printed, arg2: register with lenght of a text

        mov     rax, SYS_WRITE
        mov     rdi, STDOUT
        mov     rsi, %1
	mov	rdx, %2
        syscall

%endmacro


