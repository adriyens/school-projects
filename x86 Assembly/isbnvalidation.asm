;;; File: proj1.asm
;;; Author: Adrianne Santinor
;;; Date: 02/14/2018
;;; Description: Takes in a 10-digit number and indicates whether it's a valid ISBN label or not.
;;; 				Heavily based on a sample code given to us by the professor.

%define STDIN 0
%define STDOUT 1
%define STDERR 2
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256

[SECTION .data]
;;; Here we declare initialized data. For example: messages, prompts,
;;; and numbers that we know in advance

msg1:   db "Enter 10 digit ISBN: "             ; user prompt
len1:   equ $-msg1                      ; length of first message

msg2:   db "This is a valid ISBN label.", 0xa          ; original string label
len2:   equ $-msg2                      ; length of second message

msg3:   db "This is NOT a valid ISBN label.", 0xa        ; converted string label
len3:   equ $-msg3

[SECTION .bss]
;;; Here we declare uninitialized data. We're reserving space (and
;;; potentially associating names with that space) that our code
;;; will use as it executes. Think of these as "global variables"

buf: resb BUFLEN                     ; buffer for read
newstr: resb BUFLEN                  ; converted string
readlen: resb 2                      ; storage for the length of string we read

[SECTION .text]

global _start                   ; make start global so ld can find it

_start:                         ; the program actually starts here
        ;; prompt for user input
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, msg1
        mov edx, len1
        int 80H

        ;; read user input
        mov eax, SYSCALL_READ
        mov ebx, STDIN
        mov ecx, buf
        mov edx, BUFLEN
        int 80H

        mov ah, [readlen]           ;; remember how many characters we read
        mov esi, buf                ;; loop over all characters
        mov al, 0                   ;; what i'm gonna use as sum4
        mov bl, 0                   ;; what i'm gonna use as t4
        mov ecx, 10                  ;; loop counter (i)
  
.loop:
        cmp ecx, 0                   ;; base case!!
        je .done

        ;; grab the next letter
        mov bh, [esi]

        ;; special case!! if there's an X in the label
        cmp bh, 88
        jne .normal
        mov bh, 10
        jmp .ecks
        
.normal:
        sub bh, '0'               ;; convert to number
.ecks:
        add bl, bh                ;; add t4 and a[i]
        cmp bl, 11                ;; cmp t4 and 11 and if it's less than skip the next line
        jl .less1
        sub bl, 11
.less1:
        add al, bl
        cmp al, 11                 ;; if sum4 is less than 11 jump out of loop (i.e. .less2)
        jl .less2
        sub al, 11               

.less2:
        add esi, 1
        sub ecx, 1               
        jmp .loop
        
.done:
        ;; gotta determine whether user-input is an ISBN or not
        cmp al, 0
        je .valid
        jne .invalid
        
.valid:
        ;; print that user-input is a valid ISBN
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, msg2
        mov edx, len2
        int 80H
        
        jmp .end

.invalid:
        ;; print that user-input is an invalid ISBN
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, msg3
        mov edx, len3
        int 80H

        ;; and we're done!
        jmp .end

.end:
        ;; call sys_exit to finish things off
        mov eax, SYSCALL_EXIT   ; sys_exit syscall
        mov ebx, 0              ; no error
        int 80H                 ; kernel interrupt
