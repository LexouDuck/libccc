
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ABS(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Abs(t_q##BITS x) \
{ \
	if CCCERROR(Q##BITS##_IsNaN(x), ERROR_MATHDOMAIN, NULL) \
		return (Q##BITS##_ERROR); \
	return (t_q##BITS){ (t_s##BITS)((x._ < 0) ? -x._ : +x._) }; \
} \

DEFINEFUNC_FIXED_ABS(8)
DEFINEFUNC_FIXED_ABS(16)
DEFINEFUNC_FIXED_ABS(32)
DEFINEFUNC_FIXED_ABS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ABS(128)
#endif

/*
abs(+) = [0, +N]
abs(-) = [0, +N]
*/
