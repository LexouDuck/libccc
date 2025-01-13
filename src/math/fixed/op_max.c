
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MAX(BITS) \
_INLINE() \
t_q##BITS	Q##BITS##_Max(t_q##BITS a, t_q##BITS b) \
{ \
	if CCCERROR((Q##BITS##_IsNaN(a) || Q##BITS##_IsNaN(b)), ERROR_NANARGUMENT, NULL) \
	{ return Q##BITS##_ERROR; } \
	return (a > b ? a : b); \
} \

DEFINEFUNC_FIXED_MAX(16)
DEFINEFUNC_FIXED_MAX(32)
DEFINEFUNC_FIXED_MAX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_MAX(128)
#endif
