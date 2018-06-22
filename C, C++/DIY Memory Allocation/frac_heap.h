/* File: frac_heap.h */
/* Author: Adrianne Santinor */ 
/* Date: 04/12/18 */
/* Description: header file for fraction heap in Project 5 */

#include <stdio.h>
#include <stdlib.h>

typedef struct fracs {
  signed char sign;
  unsigned int numerator;
  unsigned int denominator;
} fraction;

/* called once before any other function */
void init_heap();

/* returns memory address of a fraction in global array */
/* if out of free fraction structs to allocate, return NULL */
unsigned int new_frac();

/* takes memory address of a fraction and removes it */
/* zeroes out sign and numerator */
/* error checks and displays message when it occurs */
void del_frac(fraction *remove);

/* print out contents of array */
void dump_heap();