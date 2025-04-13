
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Conjugate(s_complex const* z)
{
	return ((s_complex)
	{
		.re = +z->re,
		.im = -z->im,
	});
}

#ifdef __cplusplus
s_complex	operator ~ (s_complex const x)
{
	return Complex_Conjugate(x);
}
#endif
