
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_UINT_INF
#define DEFINEFUNC_UINT_ISINF(BITS) \
_INLINE() \
t_bool	U##BITS##_IsInf(t_u##BITS x) \
{ \
	return (x == +U##BITS##_INF || x == -U##BITS##_INF); \
} \

#else
#define DEFINEFUNC_UINT_ISINF(BITS) \
_INLINE() \
t_bool	U##BITS##_IsInf(t_u##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_UINT_ISINF(8)
DEFINEFUNC_UINT_ISINF(16)
DEFINEFUNC_UINT_ISINF(32)
DEFINEFUNC_UINT_ISINF(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ISINF(128)
#endif



#if LIBCONFIG_SINT_INF
#define DEFINEFUNC_SINT_ISINF(BITS) \
_INLINE() \
t_bool	S##BITS##_IsInf(t_s##BITS x) \
{ \
	return (x == +S##BITS##_INF || x == -S##BITS##_INF); \
} \

#else
#define DEFINEFUNC_SINT_ISINF(BITS) \
_INLINE() \
t_bool	S##BITS##_IsInf(t_s##BITS x) \
{ \
	return (x ? FALSE : FALSE); \
} \

#endif

DEFINEFUNC_SINT_ISINF(8)
DEFINEFUNC_SINT_ISINF(16)
DEFINEFUNC_SINT_ISINF(32)
DEFINEFUNC_SINT_ISINF(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ISINF(128)
#endif
