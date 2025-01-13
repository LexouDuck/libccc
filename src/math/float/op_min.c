
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_MIN(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Min(t_f##BITS a, t_f##BITS b) \
{ \
	if CCCERROR((F##BITS##_IsNaN(a) || F##BITS##_IsNaN(b)), ERROR_NANARGUMENT, NULL) \
	{ return F##BITS##_ERROR; } \
	return (a < b ? a : b); \
} \

DEFINEFUNC_FLOAT_MIN(32)
DEFINEFUNC_FLOAT_MIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_MIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_MIN(128)
#endif
