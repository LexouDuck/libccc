
#include "libccc/math/complex.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_bool	Complex_Equals(s_complex const* z1, s_complex const* z2)
{
	return ((z1->re == z2->re) &&
			(z1->im == z2->im));
}
