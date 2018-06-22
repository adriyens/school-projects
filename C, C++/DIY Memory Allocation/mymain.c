#include "frac_heap.h"

int main(){

	fraction *shit;
	shit = new_frac();
	
	shit->sign = '+';
	shit->denominator = 3;
	shit->numerator = 1;
	
	fraction *fuck;
	fuck = new_frac();
	
	fuck->sign = '-';
	fuck->numerator = 1;
	fuck->denominator = 2; 
	
	return 0;
}