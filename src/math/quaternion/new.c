
#include "libccc/math/quaternion.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
s_quaternion	Quaternion(t_float s, t_float i, t_float j, t_float k)
{
	return ((s_quaternion)
	{
		.s = s,
		.i = i,
		.j = j,
		.k = k,
	});
}



s_quaternion*	Quaternion_New(t_float s, t_float i, t_float j, t_float k)
{
	s_quaternion* result;

	result = (s_quaternion*)Memory_Allocate(sizeof(s_quaternion));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->s = s;
	result->i = i;
	result->j = j;
	result->k = k;
	return (result);
}
