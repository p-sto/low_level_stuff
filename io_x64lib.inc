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



