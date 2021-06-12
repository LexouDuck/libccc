
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/format.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_TOSTR(BITS) \
inline t_char*	Q##BITS##_ToString(t_q##BITS number)	\
{														\
	return (String_Format(								\
		SF_S##BITS".("SF_S##BITS"/"SF_S##BITS")",		\
		(t_s##BITS)Q##BITS##_IntegerPart(number),		\
		(t_s##BITS)Q##BITS##_FractionPart(number),		\
		(t_s##BITS)(FIXED_DENOMINATOR))					\
	);													\
}														\

DEFINEFUNC_FIXED_TOSTR(16)
DEFINEFUNC_FIXED_TOSTR(32)
DEFINEFUNC_FIXED_TOSTR(64)
#ifdef __int128
DEFINEFUNC_FIXED_TOSTR(128)
#endif
