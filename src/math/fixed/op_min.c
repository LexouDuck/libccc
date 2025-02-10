
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MIN(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Min(t_q##BITS x, t_q##BITS y) \
{ \
	if CCCERROR(Q##BITS##_IsNaN(x) && Q##BITS##_IsNaN(y), ERROR_NANARGUMENT, NULL) \
		return (Q##BITS##_ERROR); \
	else if CCCERROR(Q##BITS##_IsNaN(x), ERROR_NANARGUMENT, NULL)	return (y); \
	else if CCCERROR(Q##BITS##_IsNaN(y), ERROR_NANARGUMENT, NULL)	return (x); \
	return (x._ < y._ ? x : y); \
} \

DEFINEFUNC_FIXED_MIN(8)
DEFINEFUNC_FIXED_MIN(16)
DEFINEFUNC_FIXED_MIN(32)
DEFINEFUNC_FIXED_MIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MIN(128)
#endif
