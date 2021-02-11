
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"



#define DEFINEFUNC_CONVERT_FIXED_TO_STR(BITS) \
inline char*	Q##BITS##_ToString(t_q##BITS number)			\
{																\
	return (String_Format(										\
		FORMAT_S##BITS".("FORMAT_U##BITS"/"FORMAT_U##BITS")",	\
		(t_s##BITS)Fixed_IntegerPart(number),					\
		(t_s##BITS)Fixed_FractionPart(number),					\
		(t_s##BITS)1 << LIBCONFIG_BITS_FIXED_FRACTIONPART)		\
	);															\
}																\

DEFINEFUNC_CONVERT_FIXED_TO_STR(16)
DEFINEFUNC_CONVERT_FIXED_TO_STR(32)
DEFINEFUNC_CONVERT_FIXED_TO_STR(64)
#ifdef __int128
DEFINEFUNC_CONVERT_FIXED_TO_STR(128)
#endif
