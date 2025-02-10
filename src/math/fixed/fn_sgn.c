
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_SGN(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Sgn(t_q##BITS x) \
{ \
	if CCCERROR(Q##BITS##_IsNaN(x), ERROR_MATHDOMAIN, NULL) \
		return ((t_q##BITS){ 0 }); \
	return (t_q##BITS){ (t_s##BITS)(x._ == 0 ? 0 : (x._ < 0 ? -Q##BITS##_DENOM : +Q##BITS##_DENOM)) }; \
} \

DEFINEFUNC_FIXED_SGN(8)
DEFINEFUNC_FIXED_SGN(16)
DEFINEFUNC_FIXED_SGN(32)
DEFINEFUNC_FIXED_SGN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_SGN(128)
#endif
