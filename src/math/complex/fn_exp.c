
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Exp(s_complex const* z)
{
	t_float	exp_re = Float_Exp(z->re);
	return ((s_complex)
	{
		.re = exp_re * Float_Cos(z->im),
		.im = exp_re * Float_Sin(z->im),
	});
}
