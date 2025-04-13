
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Inverse(s_complex const* z)
{
	t_float	norm_squared = (
		(z->re * z->re) +
		(z->im * z->im));
	if CCCERROR((norm_squared == 0.), ERROR_MATHDOMAIN,
		"cannot compute inverse of a zero complex")
		return (COMPLEX_ERROR);
	return ((s_complex)
	{
		.re = +z->re / norm_squared,
		.im = -z->im / norm_squared,
	});
}

#ifdef __cplusplus
s_complex	operator ! (s_complex const x)
{
	return Complex_Inverse(x);
}
#endif
