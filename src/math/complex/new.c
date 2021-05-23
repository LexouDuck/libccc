
#include "libccc/math/complex.h"
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_complex*	Complex_New(t_float re, t_float im)
{
	s_complex* result;

	result = (s_complex*)Memory_Alloc(sizeof(s_complex));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	result->re = re;
	result->im = im;
	return (result);
}
