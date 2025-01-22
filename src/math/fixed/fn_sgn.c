
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_SGN(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Sgn(t_q##BITS a) \
{ \
	if CCCERROR((a._ == Q##BITS##_ERROR._), ERROR_MATHDOMAIN, NULL) \
		return (Q##BITS##_ERROR); \
	return (t_q##BITS){ (t_s##BITS)(a._ == 0 ? 0 : (a._ < 0 ? -1 : +1)) }; \
} \

DEFINEFUNC_FIXED_SGN(8)
DEFINEFUNC_FIXED_SGN(16)
DEFINEFUNC_FIXED_SGN(32)
DEFINEFUNC_FIXED_SGN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_SGN(128)
#endif
