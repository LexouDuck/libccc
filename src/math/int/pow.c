
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_SINT_POW(BITS) \
t_s##BITS	S##BITS##_Pow(t_s##BITS x, t_s##BITS y)	\
{													\
	/* exponentiation by squares */					\
	t_sint result = 1;								\
	while (TRUE)									\
	{												\
		if (y & 1)									\
			result *= x;							\
		y >>= 1;									\
		if (y == 0)									\
			break;									\
		x *= x;										\
	}												\
    return result;									\
}

DEFINEFUNC_SINT_POW(8)
DEFINEFUNC_SINT_POW(16)
DEFINEFUNC_SINT_POW(32)
DEFINEFUNC_SINT_POW(64)
#if LIBCONFIG_USE_128BIT
DEFINEFUNC_SINT_POW(128)
#endif
