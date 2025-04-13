
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_octonion	Octonion_Conjugate(s_octonion const* o)
{
	return ((s_octonion)
	{
		.s = +o->s,
		.i = -o->i,
		.j = -o->j,
		.k = -o->k,
		.l = -o->l,
		.m = -o->m,
		.n = -o->n,
		.o = -o->o,
	});
}

#ifdef __cplusplus
s_octonion	operator ~ (s_octonion const o)
{
	return Octonion_Conjugate(o);
}
#endif
