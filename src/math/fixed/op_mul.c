
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MUL(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Mul(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR((Memory_GetMSB(Q##BITS##_Abs(x)._) + Memory_GetMSB(Q##BITS##_Abs(y)._) >= BITS), ERROR_RESULTRANGE, NULL) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (Q##BITS##_Sgn(x) == Q##BITS##_Sgn(y)) ? Q##BITS##_MAX : Q##BITS##_MIN) \
	} \
	return (t_q##BITS){ (t_s##BITS)((x._ * y._) / Q##BITS##_DENOM) }; \
} \
// TODO fix this and test

DEFINEFUNC_FIXED_MUL(8)
DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MUL(128)
#endif

#ifdef __cplusplus
t_q8	operator * (t_q8   x, t_q8   y)	{ return Q8_Mul(x, y); }
t_q16	operator * (t_q16  x, t_q16  y)	{ return Q16_Mul(x, y); }
t_q32	operator * (t_q32  x, t_q32  y)	{ return Q32_Mul(x, y); }
t_q64	operator * (t_q64  x, t_q64  y)	{ return Q64_Mul(x, y); }
#if LIBCONFIG_USE_INT128
t_q128	operator * (t_q128 x, t_q128 y)	{ return Q128_Mul(x, y); }
#endif
#endif
