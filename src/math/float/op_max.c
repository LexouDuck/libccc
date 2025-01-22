
#include "libccc.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_MAX(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Max(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR((F##BITS##_IsNaN(x) || F##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
	{ return F##BITS##_ERROR; } \
	return (x > y ? x : y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_MAX(16)
#endif
DEFINEFUNC_FLOAT_MAX(32)

DEFINEFUNC_FLOAT_MAX(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_MAX(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_MAX(128)
#endif
