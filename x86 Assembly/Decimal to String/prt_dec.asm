;;; File: prt_dec.asm
;;; Author: Adrianne Santinor
;;; Date: 03/20/18
;;; Description: Converts an unsigned 32-bit integer on the stack to a string output

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT 1
%define SYSCALL_READ 3
%define SYSCALL_WRITE 4
%define BUFLEN 256

[SECTION .bss]
remains: resb BUFLEN            ;; to store remainders from division
decimal: resb BUFLEN            ;; number to be converted
readlen: resb 4                 ;; length of string

[SECTION .text]
global prt_dec

prt_dec:
    xor ecx, ecx                ;; clear the ecx register
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    mov eax, [esp + 28]         ;; 4 bytes for each push and the eip
    mov esi, remains            ;; point esi to remains buffer
    mov edi, decimal            ;; point edi to converted buffer
    mov ebx, 10                 ;; used for division
    
divide:
    xor edx, edx                ;; clear out edx since remainder will be stored in there
    div ebx                     ;; divide by 10
    add dl, '0'                 ;; convert to ascii equivalent of decimal number
    mov [esi], dl               ;; put that into the string
    inc esi                     ;; point to next spot in buffer
    inc ecx                     ;; for keeping track of string length
    cmp eax, 0                  ;; checks if there's anything left to divide into
    jne divide                  ;; if it's not zero then keep dividing
    mov [readlen], ecx          ;; put number of chars into length of string
    
output:
    dec esi                     ;; go back from extra step forward in divide loop
    mov al, [esi]               ;; put char that esi's currently pointing at into al
    mov [edi], al               ;; put that char into converted string
    inc edi                     ;; point to next spot of converted buffer
    loop output                 ;; loop through entire string
  
;; print out converted decimal string
print:
    mov eax, SYSCALL_WRITE
    mov ebx, STDOUT
    mov ecx, decimal
    mov edx, [readlen]
    int 80h
    
;; return saved values into their original registers 
 done:                           
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    
    ret