
#include "libccc/math/complex.h"
#include "libccc/math/math.h"



inline t_float	Complex_Abs(s_complex const* z)
{
	return (Math_SqRt((z->re * z->re) + (z->im * z->im)));
}
