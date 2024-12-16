
#include "libccc/math/complex.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Conjugate(s_complex const* z)
{
	return ((s_complex){ z->re, -z->im });
}
