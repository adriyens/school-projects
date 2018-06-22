/* File: test2.c */
/* Author: Adrianne Santinor */
/* Date: 04/12/18 */
/* Description: This file tests del_frac() to make sure it works properly */

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
  int i, j, k, l;
  
  /* this ensures that i get the same random numbers each time i run the program */
  srand(447933897);
  
  init_heap();
  
  /* generates random ints 1-500 for randnums array i'm gonna use for my fraction ptrs */
  for (i = 0; i < 20; i++){
    randnums[i] = (rand() + 1) % 501;
  }
  
  /* populate everything */
  for (j = 0; j < 20; j++){
    fptrs[j] = rand_frac(randnums);
  }
  
  dump_heap();
  
  /* now delete everything */
  for (k = 19; k >= 0; k--){
    del_frac(fptrs[k]);
  }
  
  dump_heap();
  
  /* see if error-checking works */
  fraction *invalid;
  invalid = 12; 
  
  del_frac(invalid);
  
  /* these lines shouldn't run bc the above line should cause program to exit */
  fraction *invisible[10];
  
  for (l = 0; l < 10; l++){
    invisible[l] = rand_frac(randnums);
  }
  
  dump_heap();
  
  return 0;
}