
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MAX(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Max(t_u##BITS a, t_u##BITS b) \
{ \
	if CCCERROR((U##BITS##_IsNaN(a) || U##BITS##_IsNaN(b)), ERROR_NANARGUMENT, NULL) \
	{ return U##BITS##_ERROR; } \
	return (a > b ? a : b); \
} \

DEFINEFUNC_UINT_MAX(8)
DEFINEFUNC_UINT_MAX(16)
DEFINEFUNC_UINT_MAX(32)
DEFINEFUNC_UINT_MAX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MAX(128)
#endif



#define DEFINEFUNC_SINT_MAX(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Max(t_s##BITS a, t_s##BITS b) \
{ \
	if CCCERROR((S##BITS##_IsNaN(a) || S##BITS##_IsNaN(b)), ERROR_NANARGUMENT, NULL) \
	{ return S##BITS##_ERROR; } \
	return (a > b ? a : b); \
} \

DEFINEFUNC_SINT_MAX(8)
DEFINEFUNC_SINT_MAX(16)
DEFINEFUNC_SINT_MAX(32)
DEFINEFUNC_SINT_MAX(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_MAX(128)
#endif
