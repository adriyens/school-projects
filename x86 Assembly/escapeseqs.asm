;; File: proj2.asm
;; Author: Adrianne Santinor
;; Date: 02/23/18
;; Description: Converts escape sequences in user-input to their ASCII code equivalent 

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

input: db "Enter string: "             ; user prompt
len1: equ $-input                      ; length of first message

original: db "Original: "              ; original string label
len2: equ $-original                   ; length of second message

converted: db "Convert: "              ; converted string label
len3: equ $-converted

err1: db "Error: unknown escape sequence ", 0xa
len4: equ $-err1

err2: db "Error: octal value overflow ", 0xa
len5: equ $-err2

;; indices correspond to alphabet with table[0] = a
table: db 007o, 010o, -1, -1, -1, 014o, -1, -1, -1, -1, -1, -1, -1, 012o, -1, -1, -1, 015o, -1, 011o, -1, 013o, -1, -1, -1, -1

[SECTION .bss]
;;; Here we declare uninitialized data. We're reserving space (and
;;; potentially associating names with that space) that our code
;;; will use as it executes. Think of these as "global variables"

buf: resb BUFLEN                     ; buffer for read
newstr: resb BUFLEN                  ; converted string
esc: resb BUFLEN                     ; escape sequence
readlen: resb 4                      ; storage for the length of string we read
esc1: resb 1                         
esc2: resb 1
esc3: resb 1
octal: resb 1                        ; octal value

[SECTION .text]

global _start                   ; make start global so ld can find it

_start:                         ; the program actually starts here
        ;; prompt for user input
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, input
        mov edx, len1
        int 80H

        ;; read user input
        mov eax, SYSCALL_READ
        mov ebx, STDIN
        mov ecx, buf
        mov edx, BUFLEN
        sub edx, 1                    ;; make sure buffer length is less than BUFLEN
        mov [ecx + edx], byte 0       ;; manually null-terminates user-input string ???
        int 80H

        ;; remember how many characters we read
        mov [readlen], eax
        ;; error check user input???

        ;; loop over all characters
        mov esi, buf
        mov edi, newstr

.loop:
        mov bh, [esi]                ;; grab the next letter
        cmp bh, '\'                  ;; compare to backslash
        je .escape                   ;; if it's a '\' call handle_ESC
        jne .lettercomplete
        
.escape:
        mov [edi], bh                ;; put '\' into converted string
        call .handle_ESC             ;; handle escape sequence
        inc esi                      ;; handled esc sequence so point to next char
        inc edi
        cmp [esi], byte 0            ;; compare to null-terminating character
        je .done
        jne .loop
     
;; escape sequence loop
;; checks characters to validate whether they're a valid escape sequence
.handle_ESC:
        inc esi                      ;; look at char after '\'
        mov bh, [esi]                ;; grab next letter
        cmp bh, 'a'
        jl .octal
        cmp bh, 'z'
        jl .letter
       
;; yea this dont work
.octal:
        inc esi
        mov [octal], byte 0          ;; keep track of value
        mov cl, 2                    ;; loop counter
        mov dl, 8                    ;; octal multiplier
        
.octalloop:
        sub bh, '0'                  ;; convert char to num
        mov al, [octal]
        mul dl                       ;; multiply value (ah) x 8
        mov bl, bh                   ;; move char into lower 8 bits of bx
        mov bh, 0                    ;; reset bh
        add ax, bx                   ;; (val * 8) + char
        mov [octal], al 
        mov bh, [esi]                ;; grab next char
        inc esi                      ;; point to next char
        cmp bh, '0'                  ;; compare it to 0
        jl .octalval                 ;; break out of loop if not octal
        cmp bh, '7'
        jg .octalval                 
        dec cl
        cmp cl, 0
        jne .octalloop               ;; loop
        
.octalval: 
        cmp cl, 0                    ;; if entire loop executes only dec once
        je .dec
        sub esi, 2                   ;; otherwise we gotta do it twice
        jmp .checkoverflow
.dec:
        dec esi
.checkoverflow:
        cmp ah, 0                    ;; check for overflow
        je .overflow
        mov dx, [octal]
        mov [edi], dx                ;; put value into converted string
        jmp .yeet                    ;; return

;; THIS WORKS!!!
.letter:
        cmp bh, 'z'
        jg .error
        cmp bh, 'a'
        jl .error
        movzx edx, byte [esi]        ;; put whatever esi's pointing at into eax
        sub edx, byte 'a'
        mov ebx, table
        mov bh, [ebx + edx]          ;; indexed addressing
        cmp bh, -1
        je .error
        mov [edi], bh                ;; make it new value
        jmp .yeet                    ;; return
        
.error: 
        cmp bh, '\'                  ;; double backslashes are okay
        jne .unknown
        jmp .yeet
        
.unknown:
        call .e1
        mov [edi], byte '\'
        jmp .yeet
        
.overflow:
        call .e2
        mov [edi], byte '\'
        jmp .yeet        

.yeet: 
        ret

.lettercomplete:
        ;; store the letter and go on to the next one
        mov [edi], bh
        inc edi
        inc esi
        cmp [esi], byte 0
        je .done
        jne .loop
        
.e1:
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, err1
        mov edx, len4
        int 80H
        ret
        
.e2:
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, err2
        mov edx, len5
        int 80H
        ret

.done:
        ;; print the original string message
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, original
        mov edx, len2
        int 80H

        ;; print the original string
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, buf
        mov edx, [readlen]
        int 80H

        ;; print the converted string message
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, converted
        mov edx, len3
        int 80H

        ;; print the converted string
        mov eax, SYSCALL_WRITE
        mov ebx, STDOUT
        mov ecx, newstr
        mov edx, [readlen]
        int 80H

        ;; and we're done!
        jmp .end

.end:
        ;; call sys_exit to finish things off
        mov eax, SYSCALL_EXIT   ; sys_exit syscall
        mov ebx, 0              ; no error
        int 80H                 ; kernel interrupt
