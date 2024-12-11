
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
t_float	Complex_Abs(s_complex const* z)
{
	return (Float_Root2((z->re * z->re) + (z->im * z->im)));
}
