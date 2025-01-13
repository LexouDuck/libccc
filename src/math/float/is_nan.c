
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_ISNAN(BITS) \
_INLINE() \
t_bool	F##BITS##_IsNaN(t_f##BITS x) \
{ \
	return (x != x); \
} \

DEFINEFUNC_FLOAT_ISNAN(32)
DEFINEFUNC_FLOAT_ISNAN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ISNAN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ISNAN(128)
#endif
