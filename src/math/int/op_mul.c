
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MUL(BITS) \
_INLINE() \
t_u##BITS	U##BITS##_Mul(t_u##BITS x, t_u##BITS y) \
{ \
	if CCCERROR((Memory_GetMSB(x) + Memory_GetMSB(y) >= BITS), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_UINT(U##BITS, U##BITS##_MAX) } \
	return (x * y); \
} \

DEFINEFUNC_UINT_MUL(8)
DEFINEFUNC_UINT_MUL(16)
DEFINEFUNC_UINT_MUL(32)
DEFINEFUNC_UINT_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MUL(128)
#endif



#define DEFINEFUNC_SINT_MUL(BITS) \
_INLINE() \
t_s##BITS	S##BITS##_Mul(t_s##BITS x, t_s##BITS y) \
{ \
	if CCCERROR((Memory_GetMSB(S##BITS##_Abs(x)) + Memory_GetMSB(S##BITS##_Abs(y)) >= BITS), ERROR_RESULTRANGE, NULL) \
	{ LIBCONFIG_ERROR_HANDLEOVERFLOW_SINT(S##BITS, (S##BITS##_Sgn(x) == S##BITS##_Sgn(y)) ? S##BITS##_MAX : S##BITS##_MIN) } \
	return (x * y); \
} \

DEFINEFUNC_SINT_MUL(8)
DEFINEFUNC_SINT_MUL(16)
DEFINEFUNC_SINT_MUL(32)
DEFINEFUNC_SINT_MUL(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_MUL(128)
#endif

/*
(+) * (+) = [0, +N²] => ()
(+) * (-) = [-N², 0] => ()
(-) * (+) = [-N², 0] => ()
(-) * (-) = [0, +N²] => ()
*/
