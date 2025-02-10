
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Sub(s_complex const* z1, s_complex const* z2)
{
	s_complex result;

	result.re = z1->re - z2->re;
	result.im = z1->im - z2->im;
	return (result);
}
