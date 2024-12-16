
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MUL(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Mul(t_q##BITS a, t_q##BITS b) \
{ \
	return ((a * b) / FIXED_DENOMINATOR); \
} \
// TODO fix this and test

DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MUL(128)
#endif
