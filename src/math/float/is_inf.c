
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_ISINF(BITS) \
_INLINE() \
t_bool	F##BITS##_IsInf(t_f##BITS x) \
{ \
	return (F##BITS##_IsNaN(x - x) && !F##BITS##_IsNaN(x)); \
} \

DEFINEFUNC_FLOAT_ISINF(32)
DEFINEFUNC_FLOAT_ISINF(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ISINF(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ISINF(128)
#endif
