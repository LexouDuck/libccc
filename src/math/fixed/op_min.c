
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MIN(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Min(t_q##BITS a, t_q##BITS b) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(a) || Q##BITS##_IsNaN(b)), ERROR_NANARGUMENT, NULL) \
	{ return Q##BITS##_ERROR; } \
	return (a < b ? a : b); \
} \

DEFINEFUNC_FIXED_MIN(16)
DEFINEFUNC_FIXED_MIN(32)
DEFINEFUNC_FIXED_MIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MIN(128)
#endif
