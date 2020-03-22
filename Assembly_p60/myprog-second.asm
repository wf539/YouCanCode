section .data
	nofilesmsg:	db 'No filenames given - exiting',10
	nofileslen:	equ $-nofilesmsg

section .text
	global _start

_start:
	pop edi		; Get argument count from stack
	pop ebx		; Get first arg (prog name)
	pop ebx		; Second arg (filename)

	cmp edi, 1	; More than first argument?
	jg createfile	; If so, jump ahead

	mov eax, 4	; If not, print message...
	mov ebx, 1
	mov ecx, nofilesmsg
	mov edx, nofileslen
	int 80h

	jmp finish	; ...and jump to exit

createfile:
	mov eax, 8	; Kernel 'create file' rou                             ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �����������                  