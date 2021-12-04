
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_SINT_ABS(BITS) \
inline t_s##BITS	S##BITS##_Abs(t_s##BITS a)			\
{														\
	return (ABS(a));									\
}

/*
abs(+) = [0, +N]
abs(-) = [0, +N]
*/



DEFINEFUNC_SINT_ABS(8)

DEFINEFUNC_SINT_ABS(16)

DEFINEFUNC_SINT_ABS(32)

DEFINEFUNC_SINT_ABS(64)

#if LIBCONFIG_USE_128BIT
DEFINEFUNC_SINT_ABS(128)
#endif
