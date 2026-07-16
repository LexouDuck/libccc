
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	tanh(a + bi) = (sinh(2a) + i*sin(2b)) / (cosh(2a) + cos(2b))
s_complex	Complex_TanH(s_complex const* z)
{
	t_float	denominator = Float_CosH(2. * z->re) + Float_Cos(2. * z->im);
	return ((s_complex)
	{
		.re = Float_SinH(2. * z->re) / denominator,
		.im = Float_Sin (2. * z->im) / denominator,
	});
}
