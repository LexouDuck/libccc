
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_SUB(BITS) \
extern inline t_u##BITS	U##BITS##_Sub(t_u##BITS a, t_u##BITS b) \
{ \
	if CCCERROR((a < b), ERROR_RESULTRANGE, NULL) \
	{ \
		LIBCONFIG_ERROR_HANDLEOVERFLOW(0) \
	} \
	return (a - b); \
} \

DEFINEFUNC_UINT_SUB(8)
DEFINEFUNC_UINT_SUB(16)
DEFINEFUNC_UINT_SUB(32)
DEFINEFUNC_UINT_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_SUB(128)
#endif



#define DEFINEFUNC_SINT_SUB(BITS) \
extern inline t_s##BITS	S##BITS##_Sub(t_s##BITS a, t_s##BITS b) \
{ \
	if (a && b && SGN(a) != SGN(b)) \
	{ \
		if CCCERROR((a > S##BITS##_MAX + b), ERROR_RESULTRANGE, NULL) \
		{ \
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX) \
		} \
		if CCCERROR((a < S##BITS##_MIN + b), ERROR_RESULTRANGE, NULL) \
		{ \
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN) \
		} \
	} \
	return (a - b); \
} \

DEFINEFUNC_SINT_SUB(8)
DEFINEFUNC_SINT_SUB(16)
DEFINEFUNC_SINT_SUB(32)
DEFINEFUNC_SINT_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_SUB(128)
#endif

/*
(+) - (+) = [-N, +N]
(+) - (-) = [0, +2N] => (a > MAX + b)
(-) - (+) = [-2N, 0] => (a < MIN + b)
(-) - (-) = [-N, +N]
*/
