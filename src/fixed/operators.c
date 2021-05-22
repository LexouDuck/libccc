
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/math/math.h"

#include LIBCONFIG_HANDLE_INCLUDE



#define DEFINEFUNC_FIXED_ADD(BITS) \
inline t_q##BITS	Q##BITS##_Add(t_q##BITS q1, t_q##BITS q2)	\
{																\
	t_s##BITS i1 = (q1 >> FIXED_BITS_FRACTIONPART);				\
	t_s##BITS i2 = (q2 >> FIXED_BITS_FRACTIONPART);				\
	if ((i2 > 0) && (i1 > Q##BITS##_MAX - i2))	return (Q##BITS##_MAX);	\
	if ((i2 < 0) && (i1 < Q##BITS##_MIN - i2))	return (Q##BITS##_MIN);	\
	return (q1 + q2);											\
}

#define DEFINEFUNC_FIXED_SUB(BITS) \
inline t_q##BITS	Q##BITS##_Sub(t_q##BITS q1, t_q##BITS q2)	\
{																\
	t_s##BITS i1 = (q1 >> FIXED_BITS_FRACTIONPART);				\
	t_s##BITS i2 = (q2 >> FIXED_BITS_FRACTIONPART);				\
	if ((i2 < 0) && (i1 > Q##BITS##_MAX + i2))	return (Q##BITS##_MAX);	\
	if ((i2 > 0) && (i1 < Q##BITS##_MIN + i2))	return (Q##BITS##_MIN);	\
	return (q1 - q2);											\
}

#define DEFINEFUNC_FIXED_MUL(BITS) \
inline t_q##BITS	Q##BITS##_Mul(t_q##BITS q1, t_q##BITS q2)	\
{																\
	t_s##BITS i1 = (q1 >> FIXED_BITS_FRACTIONPART);				\
	t_s##BITS i2 = (q2 >> FIXED_BITS_FRACTIONPART);				\
	if ((i1 == -1 && i2 == Q##BITS##_MIN) || (i1 > Q##BITS##_MAX / i2))	return (Q##BITS##_MAX);	\
	if ((i2 == -1 && i1 == Q##BITS##_MIN) || (i1 < Q##BITS##_MIN / i2))	return (Q##BITS##_MIN);	\
	return ((q1 * q2) >> FIXED_BITS_FRACTIONPART);				\
}

#define DEFINEFUNC_FIXED_DIV(BITS) \
inline t_q##BITS	Q##BITS##_Div(t_q##BITS q1, t_q##BITS q2)	\
{																\
	return ((q1 << FIXED_BITS_FRACTIONPART) / q2);				\
} // TODO fix this and test

#define DEFINEFUNC_FIXED_MOD(BITS) \
inline t_q##BITS	Q##BITS##_Mod(t_q##BITS q1, t_q##BITS q2)	\
{																\
	return ((q1 << FIXED_BITS_FRACTIONPART) % q2);				\
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
