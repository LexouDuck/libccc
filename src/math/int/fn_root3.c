
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE


#define DEFINEFUNC_UINT_ROOT3(BITS) \
t_u##BITS	U##BITS##_Root3(t_u##BITS x) \
{ \
	t_sint s; \
	t_u##BITS y; \
	t_u##BITS b; \
	y = 0; \
	for (s = (BITS - 1); s >= 0; s -= 3) \
	{ \
		y += y; \
		b = 3 * y * ((t_u##BITS) y + 1) + 1; \
		if ((x >> s) >= b) \
		{ \
			x -= b << s; \
			y++; \
		} \
	} \
	return y; \
} \

DEFINEFUNC_UINT_ROOT3(8)
DEFINEFUNC_UINT_ROOT3(16)
DEFINEFUNC_UINT_ROOT3(32)
DEFINEFUNC_UINT_ROOT3(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINT_ROOT3(128)
#endif



#define DEFINEFUNC_SINT_ROOT3(BITS) \
t_s##BITS	S##BITS##_Root3(t_s##BITS x) \
{ \
	if (x == S##BITS##_MIN) \
		return (0); \
	if (x == 0) \
		return (0); \
	/* Handle negative numbers by working with absolute values */ \
	t_bool neg = x < 0; \
	t_u##BITS abs_n = neg ? -x : x; \
	t_u##BITS low = 0, high = abs_n, mid; \
	t_uintmax cube; \
	/* Binary search for cube root */ \
	while (low <= high) \
	{ \
		mid = (low + high) / 2; \
		cube = (t_uintmax)mid * (t_uintmax)mid * (t_uintmax)mid; \
		if (cube == abs_n) \
			return (neg ? -mid : mid); \
		else if (cube < abs_n) \
			low = mid + 1; \
		else \
			high = mid - 1; \
	} \
	/* In case no perfect cube is found, return the floor of the cube root */ \
	return (neg ? -high : high); \
} \

DEFINEFUNC_SINT_ROOT3(8)
DEFINEFUNC_SINT_ROOT3(16)
DEFINEFUNC_SINT_ROOT3(32)
DEFINEFUNC_SINT_ROOT3(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ROOT3(128)
#endif
