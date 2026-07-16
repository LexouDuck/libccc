
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_float	Complex_Arg(s_complex const* z)
{
	return (Float_ArcTan2(z->im, z->re));
}
