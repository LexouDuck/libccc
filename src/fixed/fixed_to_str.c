
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/format.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_CONVERT_FIXED_TO_STR(BITS) \
inline t_char*	Q##BITS##_ToString(t_q##BITS number)	\
{														\
	return (String_Format(								\
		SF_S##BITS".("SF_S##BITS"/"SF_S##BITS")",		\
		(t_s##BITS)Q##BITS##_IntegerPart(number),		\
		(t_s##BITS)Q##BITS##_FractionPart(number),		\
		(t_s##BITS)(FIXED_DENOMINATOR))					\
	);													\
}														\

DEFINEFUNC_CONVERT_FIXED_TO_STR(16)
DEFINEFUNC_CONVERT_FIXED_TO_STR(32)
DEFINEFUNC_CONVERT_FIXED_TO_STR(64)
#ifdef __int128
DEFINEFUNC_CONVERT_FIXED_TO_STR(128)
#endif
