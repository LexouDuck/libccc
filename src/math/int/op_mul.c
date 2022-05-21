
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_MUL(BITS) \
inline t_u##BITS	U##BITS##_Mul(t_u##BITS a, t_u##BITS b)				\
{																		\
	if CCCERROR((Memory_GetMSB(a) + Memory_GetMSB(b) >= BITS),			\
		ERROR_RESULTRANGE, NULL)										\
	{																	\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(U##BITS##_MAX)					\
	}																	\
	return (a * b);														\
}

#define DEFINEFUNC_SINT_MUL(BITS) \
inline t_s##BITS	S##BITS##_Mul(t_s##BITS a, t_s##BITS b)				\
{																		\
	if CCCERROR((Memory_GetMSB(ABS(a)) + Memory_GetMSB(ABS(b)) >= BITS),\
		ERROR_RESULTRANGE, NULL)										\
	{																	\
		LIBCONFIG_ERROR_HANDLEOVERFLOW(SIGN(a) == SIGN(b) ?				\
			S##BITS##_MAX : S##BITS##_MIN)								\
	}																	\
	return (a * b);														\
}

/*
(+) * (+) = [0, +N²] => ()
(+) * (-) = [-N², 0] => ()
(-) * (+) = [-N², 0] => ()
(-) * (-) = [0, +N²] => ()
*/



DEFINEFUNC_UINT_MUL(8)
DEFINEFUNC_SINT_MUL(8)

DEFINEFUNC_UINT_MUL(16)
DEFINEFUNC_SINT_MUL(16)

DEFINEFUNC_UINT_MUL(32)
DEFINEFUNC_SINT_MUL(32)

DEFINEFUNC_UINT_MUL(64)
DEFINEFUNC_SINT_MUL(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_MUL(128)
DEFINEFUNC_SINT_MUL(128)
#endif
