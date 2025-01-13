
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_FIXED_INF
#define DEFINEFUNC_FIXED_ISINF(BITS) \
_INLINE() \
t_bool	Q##BITS##_IsInf(t_q##BITS x) \
{ \
	return (x == +Q##BITS##_INF || x == -Q##BITS##_INF); \
} \

#else
#define DEFINEFUNC_FIXED_ISINF(BITS) \
_INLINE() \
t_bool	Q##BITS##_IsInf(t_q##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_FIXED_ISINF(16)
DEFINEFUNC_FIXED_ISINF(32)
DEFINEFUNC_FIXED_ISINF(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ISINF(128)
#endif
