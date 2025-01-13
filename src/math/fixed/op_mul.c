
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MUL(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Mul(t_q##BITS a, t_q##BITS b) \
{ \
	if CCCERROR((Memory_GetMSB(Q##BITS##_Abs(a)) + Memory_GetMSB(Q##BITS##_Abs(b)) >= BITS), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_FIXED(Q##BITS, (Q##BITS##_Sgn(a) == Q##BITS##_Sgn(b)) ? Q##BITS##_MAX : Q##BITS##_MIN) } \
	return ((a * b) / FIXED_DENOMINATOR); \
} \
// TODO fix this and test

DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MUL(128)
#endif
