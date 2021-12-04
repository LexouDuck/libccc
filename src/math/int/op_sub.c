
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_SUB(BITS) \
inline t_u##BITS	U##BITS##_Sub(t_u##BITS a, t_u##BITS b)	\
{															\
	HANDLE_ERROR(RESULTRANGE, (a < b),						\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(0))					\
	return (a - b);											\
}

#define DEFINEFUNC_SINT_SUB(BITS) \
inline t_s##BITS	S##BITS##_Sub(t_s##BITS a, t_s##BITS b)	\
{															\
	if (a && b && SIGN(a) != SIGN(b))						\
	{														\
		HANDLE_ERROR(RESULTRANGE, (a > S##BITS##_MAX + b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MAX))	\
		HANDLE_ERROR(RESULTRANGE, (a < S##BITS##_MIN + b),	\
			LIBCONFIG_ERROR_HANDLEOVERFLOW(S##BITS##_MIN))	\
	}														\
	return (a - b);											\
}

/*
(+) - (+) = [-N, +N]
(+) - (-) = [0, +2N] => (a > MAX + b)
(-) - (+) = [-2N, 0] => (a < MIN + b)
(-) - (-) = [-N, +N]
*/

DEFINEFUNC_UINT_SUB(8)
DEFINEFUNC_SINT_SUB(8)

DEFINEFUNC_UINT_SUB(16)
DEFINEFUNC_SINT_SUB(16)

DEFINEFUNC_UINT_SUB(32)
DEFINEFUNC_SINT_SUB(32)

DEFINEFUNC_UINT_SUB(64)
DEFINEFUNC_SINT_SUB(64)

#if LIBCONFIG_USE_128BIT
DEFINEFUNC_UINT_SUB(128)
DEFINEFUNC_SINT_SUB(128)
#endif
