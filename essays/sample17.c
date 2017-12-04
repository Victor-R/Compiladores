#include <stdio.h>

float a;
int a_asm;

int main()
{
	a = 2.71828;

	a_asm = *( (int *) &a);

	printf("%u\n", a_asm);

	return 0;
}