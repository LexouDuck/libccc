
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
s_complex	Complex_Mul(s_complex const* z1, s_complex const* z2)
{
	s_complex result;
	t_float tmp1;
	t_float tmp2;

	tmp1 = z1->re * z2->re;
	tmp2 = z1->im * z2->im;
	result.re = tmp1 - tmp2;
	result.im = (z1->re + z1->im) * (z2->re + z2->im) - (tmp1 + tmp2);
	return (result);
}
