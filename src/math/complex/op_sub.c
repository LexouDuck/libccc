
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Sub(s_complex const* z1, s_complex const* z2)
{
	return ((s_complex)
	{
		.re = z1->re - z2->re,
		.im = z1->im - z2->im,
	});
}

#ifdef __cplusplus
s_complex	operator - (s_complex const x, s_complex const y)
{
	return Complex_Sub(x, y);
}
#endif
