
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ADD(BITS) \
inline t_q##BITS	Q##BITS##_Add(t_q##BITS a, t_q##BITS b)	\
{															\
	t_s##BITS i1 = (a / FIXED_DENOMINATOR);					\
	t_s##BITS i2 = (b / FIXED_DENOMINATOR);					\
	HANDLE_ERROR(RESULTRANGE, (i2 > 0) && (i1 > (Q##BITS##_MAX / FIXED_DENOMINATOR) - i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MAX))	\
	HANDLE_ERROR(RESULTRANGE, (i2 < 0) && (i1 < (Q##BITS##_MIN / FIXED_DENOMINATOR) - i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MIN))	\
	return (a + b);											\
}



DEFINEFUNC_FIXED_ADD(16)

DEFINEFUNC_FIXED_ADD(32)

DEFINEFUNC_FIXED_ADD(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ADD(128)
#endif