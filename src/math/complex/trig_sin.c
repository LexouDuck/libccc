
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	sin(a + bi) = sin(a)*cosh(b) + i*cos(a)*sinh(b)
s_complex	Complex_Sin(s_complex const* z)
{
	return ((s_complex)
	{
		.re = Float_Sin(z->re) * Float_CosH(z->im),
		.im = Float_Cos(z->re) * Float_SinH(z->im),
	});
}
