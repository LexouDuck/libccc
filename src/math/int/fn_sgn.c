
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_SINT_SGN(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Sgn(t_s##BITS a) \
{ \
	if CCCERROR((a == S##BITS##_ERROR), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (a == 0 ? 0 : (a < 0 ? -1 : +1)); \
} \

DEFINEFUNC_SINT_SGN(8)
DEFINEFUNC_SINT_SGN(16)
DEFINEFUNC_SINT_SGN(32)
DEFINEFUNC_SINT_SGN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_SGN(128)
#endif
