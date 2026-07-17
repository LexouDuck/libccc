
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/math/fixed.h"
#include "libccc/math/int.h"

#include LIBCONFIG_ERROR_INCLUDE



/*
**	A fixed-point value is prime if and only if it is a positive integer
**	(i.e. its raw value is a positive multiple of `DENOM`), and that integer
**	is prime (delegating to the integer `IsPrime` function).
*/

#define DEFINEFUNC_FIXED_ISPRIME(BITS) \
t_bool	Q##BITS##_IsPrime(t_q##BITS a) \
{ \
	if (Q##BITS##_IsNaN(a) || Q##BITS##_IsInf(a)) \
		return (FALSE); \
	if (a._ <= 0) \
		return (FALSE); \
	if (a._ % (t_s##BITS)Q##BITS##_DENOM != 0) \
		return (FALSE); \
	return (U##BITS##_IsPrime((t_u##BITS)(a._ / (t_s##BITS)Q##BITS##_DENOM))); \
} \

DEFINEFUNC_FIXED_ISPRIME(8)
DEFINEFUNC_FIXED_ISPRIME(16)
DEFINEFUNC_FIXED_ISPRIME(32)
DEFINEFUNC_FIXED_ISPRIME(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_ISPRIME(128)
#endif
