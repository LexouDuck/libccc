
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_ADD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Add(t_u##BITS a, t_u##BITS b) \
{ \
	if CCCERROR((a > U##BITS##_MAX - b), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS, U##BITS##_MAX) } \
	return (a + b); \
} \

DEFINEFUNC_UINT_ADD(8)
DEFINEFUNC_UINT_ADD(16)
DEFINEFUNC_UINT_ADD(32)
DEFINEFUNC_UINT_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ADD(128)
#endif



#define DEFINEFUNC_SINT_ADD(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Add(t_s##BITS a, t_s##BITS b) \
{ \
	if (a && b && SGN(a) == SGN(b)) \
	{ \
		if CCCERROR((a > S##BITS##_MAX - b), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS, S##BITS##_MAX) } \
		if CCCERROR((a < S##BITS##_MIN - b), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS, S##BITS##_MIN) } \
	} \
	return (a + b); \
} \

DEFINEFUNC_SINT_ADD(8)
DEFINEFUNC_SINT_ADD(16)
DEFINEFUNC_SINT_ADD(32)
DEFINEFUNC_SINT_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ADD(128)
#endif

/*
(+) + (+) = [0, +2N] => (a > MAX - b)
(+) + (-) = [-N, +N]
(-) + (+) = [-N, +N]
(-) + (-) = [-2N, 0] => (a < MIN - b)
*/
