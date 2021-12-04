
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE

// TODO: handle overflows

#define DEFINEFUNC_UINT_POW(BITS) \
t_u##BITS	U##BITS##_Pow(t_u##BITS a, t_u##BITS b)	\
{													\
	/* exponentiation by squares */					\
	t_u##BITS result = 1;							\
	while (TRUE)									\
	{												\
		if (b & 1)									\
			result *= a;							\
		b >>= 1;									\
		if (b == 0)									\
			break;									\
		a *= a;										\
	}												\
    return result;									\
}

#define DEFINEFUNC_SINT_POW(BITS) \
t_s##BITS	S##BITS##_Pow(t_s##BITS a, t_s##BITS b)	\
{													\
	/* exponentiation by squares */					\
	t_s##BITS result = 1;							\
	while (TRUE)									\
	{												\
		if (b & 1)									\
			result *= a;							\
		b >>= 1;									\
		if (b == 0)									\
			break;									\
		a *= a;										\
	}												\
    return result;									\
}

/*
(+) * (+) = [0, +aᵇ] => ()
(-) * (+) = [-aᵇ, 0] => ()
(+) * (-) = [-aᵇ, 0] => ()
(-) * (-) = [0, +aᵇ] => ()
*/



DEFINEFUNC_UINT_POW(8)
DEFINEFUNC_SINT_POW(8)

DEFINEFUNC_UINT_POW(16)
DEFINEFUNC_SINT_POW(16)

DEFINEFUNC_UINT_POW(32)
DEFINEFUNC_SINT_POW(32)

DEFINEFUNC_UINT_POW(64)
DEFINEFUNC_SINT_POW(64)

#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_POW(128)
DEFINEFUNC_SINT_POW(128)
#endif
