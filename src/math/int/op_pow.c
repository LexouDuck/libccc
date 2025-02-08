
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE

// TODO: handle overflows

#define DEFINEFUNC_UINT_POW(BITS) \
t_u##BITS	U##BITS##_Pow(t_u##BITS x, t_u##BITS y) \
{ \
	/* exponentiation by squares */ \
	t_u##BITS result = 1; \
	while (TRUE) \
	{ \
		if (y & 1) \
		{ \
			if CCCERROR((result * x < result), ERROR_RESULTRANGE, NULL) \
				return (U##BITS##_MAX); \
			result *= x; \
		} \
		y = y >> 1; \
		if (y == 0) \
			break; \
		x *= x; \
	} \
	return result; \
} \

DEFINEFUNC_UINT_POW(8)
DEFINEFUNC_UINT_POW(16)
DEFINEFUNC_UINT_POW(32)
DEFINEFUNC_UINT_POW(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_POW(128)
#endif



#define DEFINEFUNC_SINT_POW(BITS) \
t_s##BITS	S##BITS##_Pow(t_s##BITS x, t_s##BITS y) \
{ \
	/* exponentiation by squares */ \
	t_s##BITS result = 1; \
	while (TRUE) \
	{ \
		if (y & 1) \
		{ \
			if CCCERROR((result * x < result), ERROR_RESULTRANGE, NULL) \
				return (U##BITS##_MAX); \
			result *= x; \
		} \
		y = y >> 1; \
		if (y == 0) \
			break; \
		x *= x; \
	} \
	return result; \
} \

DEFINEFUNC_SINT_POW(8)
DEFINEFUNC_SINT_POW(16)
DEFINEFUNC_SINT_POW(32)
DEFINEFUNC_SINT_POW(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_POW(128)
#endif

/*
(+) * (+) = [0, +xʸ] => ()
(-) * (+) = [-xʸ, 0] => ()
(+) * (-) = [-xʸ, 0] => ()
(-) * (-) = [0, +xʸ] => ()
*/
