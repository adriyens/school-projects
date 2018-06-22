/* File: test1.c */
/* Author: Adrianne Santinor */
/* Date: 04/12/18 */
/* Description: This file tests that new_frac() properly prints out an error message when 
 *	all free blocks are filled */

#include <time.h>
#include "frac_heap.h"

/* creates a fraction with random values */
fraction *rand_frac(int randnums[]){
  fraction *rfunc;
  int rsign, rnum, rden;
  
  /* generate random values for fractions */
  rsign = rand() % 2;
  rnum = randnums[rand() % 19];
  rden = randnums[rand() % 19];
    
  rfunc = new_frac();
    
  /* if rand() generates 1, sign is negative, otherwise it's positive */
  if (rsign > 0){
    rfunc->sign = -1;
  }
  else {
    rfunc->sign = 1;
  }
    
  rfunc->numerator = rnum;
  rfunc->denominator = rden;
  
  return rfunc;
}

int main(){
  /* array of fraction pointers */
  fraction *fptrs[20];
  /* array of random integers to populate fractions with */
  int randnums[20];
  /* counter variables */
  int i, j;
  
  /* this ensures that i get the same random numbers each time i run the program */
  srand(529680128);
  
  init_heap();
  
  /* generates random ints 1-500 for randnums array i'm gonna use for my fraction ptrs */
  for (i = 0; i < 20; i++){
    randnums[i] = (rand() + 1) % 501;
  }
  
  for (j = 0; j < 20; j++){
    fptrs[j] = rand_frac(randnums);
  }
  
  /* should be full when dumped */
  dump_heap();
  
  fraction *invalid;
  
  /* should put out an error saying memory array is full */
  invalid = new_frac();
  
  return 0;
}