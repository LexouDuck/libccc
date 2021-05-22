
#include "libccc/math/complex.h"
#include "libccc/math/math.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_float	Complex_Abs(s_complex const* z)
{
	return (Float_SqRt((z->re * z->re) + (z->im * z->im)));
}
