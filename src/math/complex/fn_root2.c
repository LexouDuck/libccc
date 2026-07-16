
#include "libccc/math/complex.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_complex	Complex_Root2(s_complex const* z)
{
	return (Complex_Pow(z, 0.5));
}
