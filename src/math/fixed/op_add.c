
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ADD(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Add(t_q##BITS a, t_q##BITS b) \
{ \
	t_s##BITS i1 = (a / FIXED_DENOMINATOR); \
	t_s##BITS i2 = (b / FIXED_DENOMINATOR); \
	if CCCERROR((i2 > 0) && (i1 > (Q##BITS##_MAX / FIXED_DENOMINATOR) - i2), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MAX); } \
	if CCCERROR((i2 < 0) && (i1 < (Q##BITS##_MIN / FIXED_DENOMINATOR) - i2), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, Q##BITS##_MIN); } \
	return (a + b); \
} \

DEFINEFUNC_FIXED_ADD(16)
DEFINEFUNC_FIXED_ADD(32)
DEFINEFUNC_FIXED_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ADD(128)
#endif

/*
#ifdef __cplusplus
t_q16	operator + (t_q16	x, t_q16	y)	{ return Q16_Add(x, y); }
t_q32	operator + (t_q32	x, t_q32	y)	{ return Q32_Add(x, y); }
t_q64	operator + (t_q64	x, t_q64	y)	{ return Q64_Add(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator + (t_q128	x, t_q128	y)	{ return Q128_Add(x, y); }
#endif
#endif
*/
