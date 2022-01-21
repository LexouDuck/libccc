
#include "libccc/int.h"
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_UINT_DIV(BITS) \
inline t_u##BITS	U##BITS##_Div(t_u##BITS a, t_u##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (U##BITS##_ERROR);)	\
	return (a / b);													\
}

#define DEFINEFUNC_SINT_DIV(BITS) \
inline t_s##BITS	S##BITS##_Div(t_s##BITS a, t_s##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (S##BITS##_ERROR);)	\
	return (a / b);													\
}

/*
(+) / (+) = [0, +N]
(+) / (-) = [-N, 0]
(-) / (+) = [-N, 0]
(-) / (-) = [0, +N]
*/



DEFINEFUNC_UINT_DIV(8)
DEFINEFUNC_SINT_DIV(8)

DEFINEFUNC_UINT_DIV(16)
DEFINEFUNC_SINT_DIV(16)

DEFINEFUNC_UINT_DIV(32)
DEFINEFUNC_SINT_DIV(32)

DEFINEFUNC_UINT_DIV(64)
DEFINEFUNC_SINT_DIV(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_DIV(128)
DEFINEFUNC_SINT_DIV(128)
#endif
