;;; File: bookcmp.asm
;;; Author: Adrianne Santinor
;;; Date: 4/2/18
;;; Description: bookcmp subroutine to use in my C code to sort books. Compares publication years and titles to sort accordingly.

%define TITLE_OFFSET 0
%define AUTHOR_OFFSET 33
%define SUBJECT_OFFSET 54
%define YEAR_OFFSET 68

;; standard stuff
%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT 1
%define SYSCALL_READ 3
%define SYSCALL_WRITE 4

[SECTION .text]
global bookcmp
extern book1, book2

bookcmp:
  mov ebx, [book1]                      ;; put address of book1 into ebx
  mov ecx, [book2]                      ;; put address of book2 into ecx
  
  mov edi, [ebx + YEAR_OFFSET]          ;; point to year of book1
  mov esi, [ecx + YEAR_OFFSET]          ;; point to year of book2
    
year:
  cmp edi, esi                          ;; compare the years
  jl b1                                 ;; if book1's year is less than book2's year, make book1 the new min
  jg b2                                 ;; if book1's year is greater than book2's year, make book2 the new min
  je title                              ;; if they're the same year, sort by title
  jmp done
  
  jmp title                             ;; books have same years. compare titles now

title:
  mov edi, ebx                          ;; point to book1's title
  mov esi, ecx                          ;; point to book2's title
  mov dh, 32                            ;; counter for loop to iterate over book's title
  
titleloop:    
  mov ah, [edi]                         ;; grab char in book1's title
  mov al, [esi]                         ;; grab char in book2's title
  cmp ah, al                            ;; compare their ascii values
  jl b1                                 ;; if book1's title is before book2's in the alphabet, make that the min
  jg b2                                 ;; otherwise, book2 is the min
  inc edi                               ;; point to next char in book1's title
  inc esi                               ;; point to next char in book2's title
  dec dh                                ;; decrement counter
  cmp dh, 0                             ;; check that we're not at end of title
  jne titleloop                         ;; if not then loop
  jmp equal                             ;; otherwise, they're equal
  
b1: 
  mov eax, -1                           ;; indicate book1 is the min
  jmp done
  
b2: 
  mov eax, 1                            ;; indicate that book2 is the min
  jmp done
  
equal:
  mov eax, 0                            ;; indicate that book1 and book2 are equal
  jmp done
  
done:
  ret                                   ;; return back to sort_books.c
  