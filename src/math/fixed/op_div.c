
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_DIV(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Div(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((y._ == 0), ERROR_MATHDOMAIN, NULL) \
		return (Q##BITS##_ERROR); \
	return (t_q##BITS){ (t_s##BITS)(x._ * Q##BITS##_DENOM / y._) }; \
} \
// TODO fix this and test

DEFINEFUNC_FIXED_DIV(8)
DEFINEFUNC_FIXED_DIV(16)
DEFINEFUNC_FIXED_DIV(32)
DEFINEFUNC_FIXED_DIV(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_DIV(128)
#endif

#ifdef __cplusplus
t_q8	operator / (t_q8   x, t_q8   y)	{ return Q8_Div(x, y); }
t_q16	operator / (t_q16  x, t_q16  y)	{ return Q16_Div(x, y); }
t_q32	operator / (t_q32  x, t_q32  y)	{ return Q32_Div(x, y); }
t_q64	operator / (t_q64  x, t_q64  y)	{ return Q64_Div(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator / (t_q128 x, t_q128 y)	{ return Q128_Div(x, y); }
#endif
#endif
