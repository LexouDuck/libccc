
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_SUB(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Sub(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((x < y), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MIN) } \
	return (x - y); \
} \

DEFINEFUNC_UINT_SUB(8)
DEFINEFUNC_UINT_SUB(16)
DEFINEFUNC_UINT_SUB(32)
DEFINEFUNC_UINT_SUB(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_SUB(128)
#endif



#define DEFINEFUNC_SINT_SUB(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Sub(t_s##BITS x, t_s##BITS y) \
{ \
	if (x && y && SGN(x) != SGN(y)) \
	{ \
		if CCCERROR((x > S##BITS##_MAX + y), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MAX) } \
		if CCCERROR((x < S##BITS##_MIN + y), ERROR_RESULTRANGE, NULL) \
		{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, S##BITS##_MIN) } \
	} \
	return (x - y); \
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
(+) - (-) = [0, +2N] => (x > MAX + y)
(-) - (+) = [-2N, 0] => (x < MIN + y)
(-) - (-) = [-N, +N]
*/
