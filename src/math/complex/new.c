
#include "libccc/math/complex.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
s_complex	Complex(t_float re, t_float im)
{
	return ((s_complex)
	{
		.re = re,
		.im = im,
	});
}



s_complex*	Complex_New(t_float re, t_float im)
{
	s_complex* result;

	result = (s_complex*)Memory_Allocate(sizeof(s_complex));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->re = re;
	result->im = im;
	return (result);
}
