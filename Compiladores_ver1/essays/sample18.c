#include <stdio.h>
#include <stdlib.h>

double a;
int a_asm_lo;
int a_asm_hi;

int main()
{
	a = atof("2.1234");

	a_asm_lo = ( (int *) &a )[0];
	a_asm_hi = ( (int *) &a )[1];

	printf("%u\n %u\n", a_asm_lo, a_asm_hi);

	return 0;
}