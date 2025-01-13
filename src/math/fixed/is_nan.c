
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_FIXED_NAN
#define DEFINEFUNC_FIXED_ISNAN(BITS) \
_INLINE() \
t_bool	Q##BITS##_IsNaN(t_q##BITS x) \
{ \
	return (x == Q##BITS##_NAN); \
} \

#else
#define DEFINEFUNC_FIXED_ISNAN(BITS) \
_INLINE() \
t_bool	Q##BITS##_IsNaN(t_q##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_FIXED_ISNAN(16)
DEFINEFUNC_FIXED_ISNAN(32)
DEFINEFUNC_FIXED_ISNAN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ISNAN(128)
#endif
