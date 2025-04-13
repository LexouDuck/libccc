
#include "libccc/math/octonion.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_octonion	Octonion(
	t_float s,
	t_float i,
	t_float j,
	t_float k,
	t_float l,
	t_float m,
	t_float n,
	t_float o)
{
	return ((s_octonion)
	{
		.s = s,
		.i = i,
		.j = j,
		.k = k,
		.l = l,
		.m = m,
		.n = n,
		.o = o,
	});
}



s_octonion*	Octonion_New(
	t_float s,
	t_float i,
	t_float j,
	t_float k,
	t_float l,
	t_float m,
	t_float n,
	t_float o)
{
	s_octonion* result;

	result = (s_octonion*)Memory_Allocate(sizeof(s_octonion));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->s = s;
	result->i = i;
	result->j = j;
	result->k = k;
	result->l = l;
	result->m = m;
	result->n = n;
	result->o = o;
	return (result);
}
