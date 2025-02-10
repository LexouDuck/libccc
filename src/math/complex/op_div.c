
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Div(s_complex const* z1, s_complex const* z2)
{
	s_complex c;
	t_float tmp;

	tmp = 1. / ((z2->re * z2->re) + (z2->im * z2->im));
	c.re = +z2->re * tmp;
	c.im = -z2->im * tmp;
	return (Complex_Mul(z1, &c));
}
