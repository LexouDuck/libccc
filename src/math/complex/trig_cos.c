
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



//	cos(a + bi) = cos(a)*cosh(b) - i*sin(a)*sinh(b)
s_complex	Complex_Cos(s_complex const* z)
{
	return ((s_complex)
	{
		.re = +Float_Cos(z->re) * Float_CosH(z->im),
		.im = -Float_Sin(z->re) * Float_SinH(z->im),
	});
}
