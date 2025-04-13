
#include "libccc/math/octonion.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_octonion	Octonion_Div(s_octonion const* o1, s_octonion const* o2)
{
	t_float divisor;

	divisor = 1. / (
		(o2->s * o2->s) +
		(o2->i * o2->i) +
		(o2->j * o2->j) +
		(o2->k * o2->k));
	return ((s_octonion)
	{
		.s = (o2->s * o1->s + o2->i * o1->i + o2->j * o1->j + o2->k * o1->k + o2->l * o1->l + o2->m * o1->m + o2->n * o1->n + o2->o * o1->o) * divisor,
		.i = (o2->s * o1->i - o2->i * o1->s - o2->j * o1->k + o2->k * o1->j - o2->l * o1->m + o2->m * o1->l + o2->n * o1->o - o2->o * o1->n) * divisor,
		.j = (o2->s * o1->j + o2->i * o1->k - o2->j * o1->s - o2->k * o1->i - o2->l * o1->n - o2->m * o1->o + o2->n * o1->l + o2->o * o1->m) * divisor,
		.k = (o2->s * o1->k - o2->i * o1->j + o2->j * o1->i - o2->k * o1->s - o2->l * o1->o + o2->m * o1->n - o2->n * o1->m + o2->o * o1->l) * divisor,
		.l = (o2->s * o1->l + o2->i * o1->m + o2->j * o1->n + o2->k * o1->o - o2->l * o1->s - o2->m * o1->i - o2->n * o1->j - o2->o * o1->k) * divisor,
		.m = (o2->s * o1->m - o2->i * o1->l + o2->j * o1->o - o2->k * o1->n + o2->l * o1->i - o2->m * o1->s + o2->n * o1->k - o2->o * o1->j) * divisor,
		.n = (o2->s * o1->n - o2->i * o1->o - o2->j * o1->l + o2->k * o1->m + o2->l * o1->j - o2->m * o1->k - o2->n * o1->s + o2->o * o1->i) * divisor,
		.o = (o2->s * o1->o + o2->i * o1->n - o2->j * o1->m - o2->k * o1->l + o2->l * o1->k + o2->m * o1->j - o2->n * o1->i - o2->o * o1->s) * divisor,
	});
}

#ifdef __cplusplus
s_octonion	operator / (s_octonion const o1, s_octonion const o2)
{
	return Octonion_Div(o1, o2);
}
#endif
