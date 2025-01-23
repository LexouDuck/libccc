
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_ADD(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Add(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((x > U##BITS##_MAX - y), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MAX) } \
	return (x + y); \
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
t_s##BITS	S##BITS##_Add(t_s##BITS x, t_s##BITS y) \
{ \
	if (x && y && SGN(x) == SGN(y)) \
	{ \
		if CCCERROR((x > S##BITS##_MAX - y), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX) } \
		if CCCERROR((x < S##BITS##_MIN - y), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MIN) } \
	} \
	return (x + y); \
} \

DEFINEFUNC_SINT_ADD(8)
DEFINEFUNC_SINT_ADD(16)
DEFINEFUNC_SINT_ADD(32)
DEFINEFUNC_SINT_ADD(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ADD(128)
#endif

/*
(+) + (+) = [0, +2N] => (x > MAX - y)
(+) + (-) = [-N, +N]
(-) + (+) = [-N, +N]
(-) + (-) = [-2N, 0] => (x < MIN - y)
*/
