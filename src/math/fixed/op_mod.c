
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_MOD(BITS) \
inline t_q##BITS	Q##BITS##_Mod(t_q##BITS a, t_q##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (Q##BITS##_ERROR);)	\
	return ((a * FIXED_DENOMINATOR) % b);							\
} // TODO fix this and test



DEFINEFUNC_FIXED_MOD(16)

DEFINEFUNC_FIXED_MOD(32)

DEFINEFUNC_FIXED_MOD(64)

#if LIBCONFIG_USE_128BIT
DEFINEFUNC_FIXED_MOD(128)
#endif
