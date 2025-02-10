
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
	t_u##BITS result = 1; \
	/* exponentiation by squares */ \
	while (TRUE) \
	{ \
		if (y & 1) \
		{ \
			if CCCERROR((result * x < result), ERROR_RESULTRANGE, NULL) \
			{	LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MAX);	} \
			result *= x; \
		} \
		y >>= 1; \
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
	t_s##BITS result = 1; \
	if (y < 0) \
	{ \
		if CCCERROR((x == 0), ERROR_RESULTRANGE, \
			"zero cannot be raised to a negative power") \
			return (U##BITS##_ERROR); \
		return (1 / x); \
	} \
	/* exponentiation by squares */ \
	while (TRUE) \
	{ \
		if (y & 1) \
		{ \
			if CCCERROR((result * x < result), ERROR_RESULTRANGE, NULL) \
			{	LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(U##BITS, U##BITS##_MAX);	} \
			result *= x; \
		} \
		y >>= 1; \
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

/*
#ifdef __cplusplus
t_s8	operator ^ (t_s8   x, t_s8   y)	{ return S8_Pow(x, y); }
t_s16	operator ^ (t_s16  x, t_s16  y)	{ return S16_Pow(x, y); }
t_s32	operator ^ (t_s32  x, t_s32  y)	{ return S32_Pow(x, y); }
t_s64	operator ^ (t_s64  x, t_s64  y)	{ return S64_Pow(x, y); }
#if LIBCONFIG_USE_INT128
t_s128	operator ^ (t_s128 x, t_s128 y)	{ return S128_Pow(x, y); }
#endif
#endif
*/
