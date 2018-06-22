;;; File: mytest3.asm
;;; Author: Adrianne Santinor
;;; Date: 3/21/18
;;; Description: Calls my prt_dec subroutine with a number to convert on the stack

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT 1
%define SYSCALL_READ 3
%define SYSCALL_WRITE 4

[SECTION .data]
lf: db 10

msg1: db " times "
len1: equ $ - msg1

msg2: db " divided by "
len2: equ $ - msg2

msg3: db " equals "
len3: equ $ - msg3

[SECTION .text]
global _start
extern prt_dec

_start:
		mov eax, 0xabcdef10								;; hexadecimal
		mov ebx, 0b10101111								;; binary
		mov edx, 0q1234567								;; octal
		mov edi, 0xdeadbeef								;; hexadecimal
		mov ebp, 0b10101011								;; binary
		
		push dword 0x0										;; pushes the number 0 onto the stack
		call prt_dec											;; prints out the number as a string "0"
		add esp, 4												;; points to next spot in buffer (32 bit numbers)
		call prt_lf												;; goes to next line
		
		push dword 0q77777777							;; pushes 16777215 onto stack
		call prt_dec											;; prints out number as a string
		add esp, 4
		call prt_lf
		
		push dword 0b11111111							;; pushes 255 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push eax													;; pushes 2882400016 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push ebx													;; pushes 175 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push edx													;; pushes 342391 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push edi													;; pushes 3735928559 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push ebp													;; pushes 171 onto stack
		call prt_dec
		add esp, 4
		call prt_lf
		
		push 16														;; pushes 16 onto stack (no new line this time)
		call prt_dec 
		add esp, 4
		
		;; prints out string " times "
		mov eax, SYSCALL_WRITE
		mov ebx, STDOUT
		mov ecx, msg1
		mov edx, len1
		int 80h
		
		push 9														;; pushes 9 onto stack (no new line)
		call prt_dec
		add esp, 4
		
		;; prints out string " equals "
		mov eax, SYSCALL_WRITE
		mov ebx, STDOUT
		mov ecx, msg3
		mov edx, len3
		int 80h
		
		push 144													;; pushes 144 onto stack
		call prt_dec
		add esp, 4
		call prt_lf												;; new line!!
		
		push 77
		call prt_dec
		add esp, 4
		
		mov eax, SYSCALL_WRITE
		mov ebx, STDOUT
		mov ecx, msg2
		mov edx, len2
		int 80h
		
		push 11
		call prt_dec
		add esp, 4
		
		mov eax, SYSCALL_WRITE
		mov ebx, STDOUT
		mov ecx, msg3
		mov edx, len3
		int 80h
		
		push 7
		call prt_dec
		add esp, 4
		call prt_lf
		
exit:
		mov eax, SYSCALL_EXIT
		mov ebx, 0
		int 80h
		
;; literally just puts next output onto a new line
prt_lf:
		push eax
		push ebx
		push ecx
		push edx
		
		mov eax, SYSCALL_WRITE
		mov ebx, STDOUT
		mov ecx, lf
		mov edx, 1
		int 80h
		
		pop edx
		pop ecx
		pop ebx
		pop eax
		
		ret