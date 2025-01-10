
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_SINT_ABS(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Abs(t_s##BITS a) \
{ \
	if CCCERROR((a == S##BITS##_ERROR), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (a < 0 ? -a : +a); \
} \

DEFINEFUNC_SINT_ABS(8)
DEFINEFUNC_SINT_ABS(16)
DEFINEFUNC_SINT_ABS(32)
DEFINEFUNC_SINT_ABS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ABS(128)
#endif

/*
abs(+) = [0, +N]
abs(-) = [0, +N]
*/
