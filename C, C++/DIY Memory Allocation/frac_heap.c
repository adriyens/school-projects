/* File: frac_heap.c */
/* Author: Adrianne Santinor */
/* Date: 04/12/18 */
/* Description: DIY memory allocation using a global array */

#include "frac_heap.h"
#define ELEMENTS 20
#define OFFSET   12
#define MAGIC    346703962

/* global array used for memory allocation */
static fraction memory[ELEMENTS];

/* memory address of beginning of free block list */
static unsigned int beginning;

/* keep track of next free block */
int freeblock;

void init_heap(){
  /* counter variable */
  int i;
  
  /* have memory address of first free block initially be the start of memory array */
  beginning = &memory;
  freeblock = beginning;
  
  /* initialize everything in memory array */
  for (i = 0; i < ELEMENTS; i++){
    memory[i].sign = 0;
    memory[i].numerator = 0;
    memory[i].denominator = i+1;  
    
    if (i == ELEMENTS - 1){
      memory[i].sign = 0;
      memory[i].numerator = 0;
      memory[i].denominator = MAGIC; /*~*~* magic *~*~*/
    }
    
  }
  
}

unsigned int new_frac(){
  /* counter variable */
  int i;
  
  /* searches memory array for first instance of an empty block */
  for (i = 0; i < ELEMENTS; i++){
    if (memory[i].numerator == 0){
      freeblock = &memory[i];
      return freeblock;
    }
  }
  
  printf("No free blocks.\n\n");
  return NULL;
  
}

/* hardest one??? */
void del_frac(fraction *remove){
  /* use to calculate index remove is pointing at */
  unsigned int i;
  /* c doesn't like when i use &remove so i gotta explicitly change it to an int */
  unsigned int removeaddress;  
  int j;
  
  removeaddress = remove;
  
  /* index is difference of what remove's pointing at and the beginning of memory array
  *  also gotta account for offset
  */
  i = (removeaddress - beginning) / OFFSET;
  
  /* if fraction ptr is pointing to an index out of bounds, print error msg */
  if ((i > ELEMENTS - 1) || (i < 0)){
    printf("\nNot a valid memory location.\n");
    exit(1);
  }
  
  memory[i].sign = 0;
  memory[i].numerator = 0;
  
  for (j = 0; j < ELEMENTS; j++){
    /* looks for an empty block and ensures it's not the same one we're deleting */
    if ((memory[j].numerator == 0) && (i != j)){
      freeblock = &memory[j];
      memory[i].denominator = j;
      break;
    }
    /* janky coding */
    /* basically saying if next empty block's denominator is some garbage value over 20
     * make it the magic number lol */
    if ((memory[j].denominator > ELEMENTS - 1) && (memory[j].denominator != MAGIC) && (memory[j].numerator == 0)){
      memory[j].denominator = MAGIC;
    }
  }
  
  printf("Deleted block %u\n", i);
  
}

void dump_heap(){
  /* counter variable */
  int i; 
  
  printf("\n");
  
  for (i = 0; i < ELEMENTS; i++){
    printf("%d: %d(%u/%u) \n", i, memory[i].sign, memory[i].numerator, memory[i].denominator);
  }
  
  printf("\n");
  
}