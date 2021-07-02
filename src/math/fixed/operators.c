
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"

#include LIBCONFIG_ERROR_INCLUDE



#define DEFINEFUNC_FIXED_ADD(BITS) \
inline t_q##BITS	Q##BITS##_Add(t_q##BITS a, t_q##BITS b)	\
{															\
	t_s##BITS i1 = (a / FIXED_DENOMINATOR);					\
	t_s##BITS i2 = (b / FIXED_DENOMINATOR);					\
	HANDLE_ERROR(RESULTRANGE, (i2 > 0) && (i1 > (Q##BITS##_MAX / FIXED_DENOMINATOR) - i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MAX))	\
	HANDLE_ERROR(RESULTRANGE, (i2 < 0) && (i1 < (Q##BITS##_MIN / FIXED_DENOMINATOR) - i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MIN))	\
	return (a + b);											\
}



#define DEFINEFUNC_FIXED_SUB(BITS) \
inline t_q##BITS	Q##BITS##_Sub(t_q##BITS a, t_q##BITS b)	\
{															\
	t_s##BITS i1 = (a / FIXED_DENOMINATOR);					\
	t_s##BITS i2 = (b / FIXED_DENOMINATOR);					\
	HANDLE_ERROR(RESULTRANGE, (i2 < 0) && (i1 > (Q##BITS##_MAX / FIXED_DENOMINATOR) + i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MAX))	\
	HANDLE_ERROR(RESULTRANGE, (i2 > 0) && (i1 < (Q##BITS##_MIN / FIXED_DENOMINATOR) + i2), LIBCONFIG_ERROR_HANDLEOVERFLOW(Q##BITS##_MIN))	\
	return (a - b);											\
}



#define DEFINEFUNC_FIXED_MUL(BITS) \
inline t_q##BITS	Q##BITS##_Mul(t_q##BITS a, t_q##BITS b)	\
{															\
	return ((a * b) / FIXED_DENOMINATOR);					\
} // TODO fix this and test



#define DEFINEFUNC_FIXED_DIV(BITS) \
inline t_q##BITS	Q##BITS##_Div(t_q##BITS a, t_q##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (Q##BITS##_ERROR);)	\
	return ((a * FIXED_DENOMINATOR) / b);							\
} // TODO fix this and test



#define DEFINEFUNC_FIXED_MOD(BITS) \
inline t_q##BITS	Q##BITS##_Mod(t_q##BITS a, t_q##BITS b)			\
{																	\
	HANDLE_ERROR(MATHDOMAIN, (b == 0), return (Q##BITS##_ERROR);)	\
	return ((a * FIXED_DENOMINATOR) % b);							\
} // TODO fix this and test



DEFINEFUNC_FIXED_ADD(16)
DEFINEFUNC_FIXED_SUB(16)
DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_DIV(16)
DEFINEFUNC_FIXED_MOD(16)

DEFINEFUNC_FIXED_ADD(32)
DEFINEFUNC_FIXED_SUB(32)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_DIV(32)
DEFINEFUNC_FIXED_MOD(32)

DEFINEFUNC_FIXED_ADD(64)
DEFINEFUNC_FIXED_SUB(64)
DEFINEFUNC_FIXED_MUL(64)
DEFINEFUNC_FIXED_DIV(64)
DEFINEFUNC_FIXED_MOD(64)

#ifdef __int128
DEFINEFUNC_FIXED_ADD(128)
DEFINEFUNC_FIXED_SUB(128)
DEFINEFUNC_FIXED_MUL(128)
DEFINEFUNC_FIXED_DIV(128)
DEFINEFUNC_FIXED_MOD(128)
#endif
