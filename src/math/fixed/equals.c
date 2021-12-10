
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_EQUALS(BITS) \
inline t_bool	Q##BITS##_Equals(t_q##BITS a, t_q##BITS b)		\
{																\
	return (a == b);											\
}																\



#define DEFINEFUNC_FIXED_APPROX(BITS) \
t_bool	Q##BITS##_EqualsApprox(t_q##BITS a, t_q##BITS b)		\
{																\
	t_q##BITS abs_a = ABS(a);									\
	t_q##BITS abs_b = ABS(b);									\
	return (ABS(a - b) <= MAX(abs_a, abs_b) * FIXED_APPROX);	\
}																\



DEFINEFUNC_FIXED_EQUALS(16)
DEFINEFUNC_FIXED_APPROX(16)

DEFINEFUNC_FIXED_EQUALS(32)
DEFINEFUNC_FIXED_APPROX(32)

DEFINEFUNC_FIXED_EQUALS(64)
DEFINEFUNC_FIXED_APPROX(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_EQUALS(128)
DEFINEFUNC_FIXED_APPROX(128)
#endif
