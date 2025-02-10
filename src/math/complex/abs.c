
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
t_float	Complex_Abs(s_complex const* z)
{
	return (Float_Root2((z->re * z->re) + (z->im * z->im)));
}
