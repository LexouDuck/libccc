
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"



#define DEFINEFUNC_FIXED(BITS) \
inline t_q##BITS	Q##BITS(												\
	t_s64 part_integer,														\
	t_u64 part_fraction,													\
	t_u64 denominator)														\
{																			\
	t_q##BITS result = 0;													\
	if (part_fraction == denominator)	part_integer += 1;					\
	else if (part_fraction > denominator)	return (0);						\
	if (part_integer >= FIXED_MAX_INTEGERPART)								\
		part_integer = (FIXED_MAX_INTEGERPART - 1);							\
	result = ((t_q##BITS)part_integer << FIXED_BITS_FRACTIONPART);			\
	result |= (part_fraction * FIXED_MAX_FRACTIONPART) / denominator;		\
	return (result);														\
}

#define DEFINEFUNC_FIXED_FROMINT(BITS) \
inline t_q##BITS	Q##BITS##_FromInt(t_s##BITS number)						\
{																			\
	if (number > (Q##BITS##_MAX >> FIXED_BITS_FRACTIONPART))	return (Q##BITS##_MAX);	\
	if (number < (Q##BITS##_MIN >> FIXED_BITS_FRACTIONPART))	return (Q##BITS##_MIN);	\
	return ((t_q##BITS)number << FIXED_BITS_FRACTIONPART);					\
}

#define DEFINEFUNC_FIXED_FROMFLOAT(BITS) \
inline t_q##BITS	Q##BITS##_FromFloat(t_f64 number)						\
{																			\
	if (number > (Q##BITS##_MAX >> FIXED_BITS_FRACTIONPART))	return (Q##BITS##_MAX);	\
	if (number < (Q##BITS##_MIN >> FIXED_BITS_FRACTIONPART))	return (Q##BITS##_MIN);	\
	return (																\
		((t_q##BITS)Math_Truncate(number) << FIXED_BITS_FRACTIONPART) |		\
		((t_q##BITS)Math_Mod(number, 1) & (FIXED_MASK_FRACTIONPART))		\
	);																		\
}



#define DEFINEFUNC_FIXED_INTEGERPART(BITS) \
inline t_q##BITS	Q##BITS##_IntegerPart(t_q##BITS number)					\
{																			\
	return (number >> FIXED_BITS_FRACTIONPART);								\
}

#define DEFINEFUNC_FIXED_FRACTIONPART(BITS) \
inline t_q##BITS	Q##BITS##_FractionPart(t_q##BITS number)				\
{																			\
	return (number & (FIXED_MASK_FRACTIONPART));							\
}

#define DEFINEFUNC_FIXED_ROUNDED(BITS) \
inline t_q##BITS	Q##BITS##_Rounded(t_q##BITS number)						\
{																			\
	t_q##BITS fraction = Q##BITS##_FractionPart(number);					\
	if (fraction < FIXED_MAX_FRACTIONPART / 2)								\
		return (number - fraction);											\
	else return (number + (FIXED_MAX_FRACTIONPART - fraction));				\
}



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
}



DEFINEFUNC_FIXED(16)
DEFINEFUNC_FIXED_FROMINT(16)
DEFINEFUNC_FIXED_FROMFLOAT(16)

DEFINEFUNC_FIXED_INTEGERPART(16)
DEFINEFUNC_FIXED_FRACTIONPART(16)
DEFINEFUNC_FIXED_ROUNDED(16)

DEFINEFUNC_FIXED_ADD(16)
DEFINEFUNC_FIXED_SUB(16)
DEFINEFUNC_FIXED_MUL(16)
DEFINEFUNC_FIXED_DIV(16)



DEFINEFUNC_FIXED(32)
DEFINEFUNC_FIXED_FROMINT(32)
DEFINEFUNC_FIXED_FROMFLOAT(32)

DEFINEFUNC_FIXED_INTEGERPART(32)
DEFINEFUNC_FIXED_FRACTIONPART(32)
DEFINEFUNC_FIXED_ROUNDED(32)

DEFINEFUNC_FIXED_ADD(32)
DEFINEFUNC_FIXED_SUB(32)
DEFINEFUNC_FIXED_MUL(32)
DEFINEFUNC_FIXED_DIV(32)



DEFINEFUNC_FIXED(64)
DEFINEFUNC_FIXED_FROMINT(64)
DEFINEFUNC_FIXED_FROMFLOAT(64)

DEFINEFUNC_FIXED_INTEGERPART(64)
DEFINEFUNC_FIXED_FRACTIONPART(64)
DEFINEFUNC_FIXED_ROUNDED(64)

DEFINEFUNC_FIXED_ADD(64)
DEFINEFUNC_FIXED_SUB(64)
DEFINEFUNC_FIXED_MUL(64)
DEFINEFUNC_FIXED_DIV(64)



#ifdef __int128
DEFINEFUNC_FIXED(128)
DEFINEFUNC_FIXED_FROMINT(128)
DEFINEFUNC_FIXED_FROMFLOAT(128)

DEFINEFUNC_FIXED_INTEGERPART(128)
DEFINEFUNC_FIXED_FRACTIONPART(128)
DEFINEFUNC_FIXED_ROUNDED(128)

DEFINEFUNC_FIXED_ADD(128)
DEFINEFUNC_FIXED_SUB(128)
DEFINEFUNC_FIXED_MUL(128)
DEFINEFUNC_FIXED_DIV(128)
#endif
