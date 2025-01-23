
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_REM(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Rem(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(x) || Q##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	if CCCERROR((Q##BITS##_IsInf(x) || (y._ == 0.)), ERROR_MATHDOMAIN, NULL) \
		return (Q##BITS##_ERROR); \
	return (t_q##BITS){ (t_s##BITS)(x._ % y._) }; \
} \
// TODO fix this and test

DEFINEFUNC_FIXED_REM(8)
DEFINEFUNC_FIXED_REM(16)
DEFINEFUNC_FIXED_REM(32)
DEFINEFUNC_FIXED_REM(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_REM(128)
#endif

/*
#ifdef __cplusplus
t_q8	operator % (t_q8   x, t_q8   y)	{ return Q8_Rem(x, y); }
t_q16	operator % (t_q16  x, t_q16  y)	{ return Q16_Rem(x, y); }
t_q32	operator % (t_q32  x, t_q32  y)	{ return Q32_Rem(x, y); }
t_q64	operator % (t_q64  x, t_q64  y)	{ return Q64_Rem(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator % (t_q128 x, t_q128 y)	{ return Q128_Rem(x, y); }
#endif
#endif
*/
