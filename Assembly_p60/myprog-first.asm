section .data
	message:	db 'Top notch assembly!', 10
	messagelen:	equ $-message

section .text
	global _start	; Where the program should begin

_start:
	mov eax, 4	; OS call to print string
	mov ebx, 1	; Print to stdout
	mov ecx, message
	mov edx, messagelen
	int 80h		; Call kernel

	mov eax, 1	; OS call to end app
	mov ebx, 0
	int 80h		; Call kernel

