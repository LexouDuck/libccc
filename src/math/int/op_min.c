
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MIN(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Min(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((U##BITS##_IsNaN(x) || U##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
	{ return U##BITS##_ERROR; } \
	return (x < y ? x : y); \
} \

DEFINEFUNC_UINT_MIN(8)
DEFINEFUNC_UINT_MIN(16)
DEFINEFUNC_UINT_MIN(32)
DEFINEFUNC_UINT_MIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MIN(128)
#endif



#define DEFINEFUNC_SINT_MIN(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Min(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((S##BITS##_IsNaN(x) || S##BITS##_IsNaN(y)), ERROR_NANARGUMENT, NULL) \
	{ return S##BITS##_ERROR; } \
	return (x < y ? x : y); \
} \

DEFINEFUNC_SINT_MIN(8)
DEFINEFUNC_SINT_MIN(16)
DEFINEFUNC_SINT_MIN(32)
DEFINEFUNC_SINT_MIN(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_MIN(128)
#endif
