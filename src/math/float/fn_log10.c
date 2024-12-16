
#include "libccc/memory.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Log10, log10)
#else
#define DEFINEFUNC_FLOAT_LOG10(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Log10(t_f##BITS x) \
{ \
	return (F##BITS##_Ln(x) / LN_10); \
} \

DEFINEFUNC_FLOAT_LOG10(32)
DEFINEFUNC_FLOAT_LOG10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOG10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOG10(128)
#endif

#endif
