
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



s_complex	Complex_Proj(s_complex const* z)
{
	if (Float_IsInf(z->re) || Float_IsInf(z->im))
	{
		return ((s_complex)
		{
			.re = (t_float)INFINITY,
			.im = Float_CopySign(0., z->im),
		});
	}
	return (*z);
}
