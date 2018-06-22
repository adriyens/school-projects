/* File: test3.c */
/* Author: Adrianne Santinor */
/* Date: 04/12/18 */
/* Description: giant test of everything */

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
  int i, j, k, l, m, n, o, p;
  
  /* this ensures that i get the same random numbers each time i run the program */
  srand(258870937);
  
  init_heap();
  dump_heap();
  
  /* generates random ints 1-500 for randnums array i'm gonna use for my fraction ptrs */
  for (i = 0; i < 20; i++){
    randnums[i] = (rand() + 1) % 501;
  }
  
  /* populate everything */
  for (j = 0; j < 20; j++){
    fptrs[j] = rand_frac(randnums);
  }
  
  /* delete some stuff */
  for (k = 10; k > 4; k--){
    del_frac(fptrs[k]);
  }
  
  dump_heap();
  
  for (l = 5; l < 11; l++){
    fptrs[l] = rand_frac(randnums);
  }
  
  dump_heap();
  fraction *out_of_bounds;
  out_of_bounds = new_frac();
  
  for (m = 19; m >= 0; m-=3){
    del_frac(fptrs[m]);
  }
  
  dump_heap();
  
  for (n = 19; n >= 0; n--){
    del_frac(fptrs[n]);
  }
  
  out_of_bounds = -1;
  del_frac(out_of_bounds);
 
  for (o = 0; o < 14; o+=6){
    fptrs[o] = rand_frac(randnums);
  }
  
  for (p = 0; p < 20; p++){
    del_frac(fptrs[p]);
  }
 
  dump_heap();
  
  return 0;
}