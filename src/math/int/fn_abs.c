
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_ABS(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Abs(t_u##BITS x) \
{ \
	return (x); \
} \

DEFINEFUNC_UINT_ABS(8)
DEFINEFUNC_UINT_ABS(16)
DEFINEFUNC_UINT_ABS(32)
DEFINEFUNC_UINT_ABS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ABS(128)
#endif



#define DEFINEFUNC_SINT_ABS(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Abs(t_s##BITS x) \
{ \
	if CCCERROR((x == S##BITS##_ERROR), ERROR_MATHDOMAIN, NULL) \
		return (S##BITS##_ERROR); \
	return (x < 0 ? -x : +x); \
} \

DEFINEFUNC_SINT_ABS(8)
DEFINEFUNC_SINT_ABS(16)
DEFINEFUNC_SINT_ABS(32)
DEFINEFUNC_SINT_ABS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ABS(128)
#endif

/*
abs(+) = [0, +N]
abs(-) = [0, +N]
*/
