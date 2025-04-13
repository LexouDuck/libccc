
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_octonion	Octonion_Add(s_octonion const* o1, s_octonion const* o2)
{
	return ((s_octonion)
	{
		.s = o1->s + o2->s,
		.i = o1->i + o2->i,
		.j = o1->j + o2->j,
		.k = o1->k + o2->k,
		.l = o1->l + o2->l,
		.m = o1->m + o2->m,
		.n = o1->n + o2->n,
		.o = o1->o + o2->o,
	});
}

#ifdef __cplusplus
s_octonion	operator + (s_octonion const o1, s_octonion const o2)
{
	return Octonion_Add(o1, o2);
}
#endif
