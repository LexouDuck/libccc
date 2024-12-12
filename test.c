#include <math.h>
#include <stdio.h>
#include <inttypes.h>
int main()
{
	union {float f; uint32_t i;} a;
	a.f = pow(2,-56);
	printf("%x = %f = %a\n", a.i, a.f, a.f);
}
