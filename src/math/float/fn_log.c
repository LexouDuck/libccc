
#include "libccc/memory.h"
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FLOAT_LOGN(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_LogN(t_f##BITS x, t_f##BITS n) \
{ \
	if (n == E) \
		return (F##BITS##_Ln(x)); \
	else if (n == 2.) \
		return (F##BITS##_Log2(x)); \
	else if (n == 10.) \
		return (F##BITS##_Log10(x)); \
	else \
		return (F##BITS##_Ln(x) / F##BITS##_Ln(n)); \
} \

DEFINEFUNC_FLOAT_LOGN(32)
DEFINEFUNC_FLOAT_LOGN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LOGN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LOGN(128)
#endif
