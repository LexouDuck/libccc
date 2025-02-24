
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_GCD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_GCD(t_u##BITS x, t_u##BITS y) \
{ \
	if (x && y) \
		while ((x %= y) && (y %= x)); \
	return (x | y); \
} \

DEFINEFUNC_UINT_GCD(8)
DEFINEFUNC_UINT_GCD(16)
DEFINEFUNC_UINT_GCD(32)
DEFINEFUNC_UINT_GCD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_GCD(128)
#endif



#define DEFINEFUNC_SINT_GCD(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_GCD(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR( \
		!LIBCONFIG_SINT_INF && \
		!LIBCONFIG_SINT_NAN && \
		((x == S##BITS##_MIN && y == -1) || (x == -1 && y == S##BITS##_MIN)), ERROR_RESULTRANGE, \
		"cannot perform modulo with -1 and t_s"#BITS" minimum value (" SF_S##BITS ")", S##BITS##_MIN) \
		return (1); \
	if (x && y) \
		while ((x %= y) && (y %= x)); \
	return (x | y); \
} \

DEFINEFUNC_SINT_GCD(8)
DEFINEFUNC_SINT_GCD(16)
DEFINEFUNC_SINT_GCD(32)
DEFINEFUNC_SINT_GCD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_GCD(128)
#endif
