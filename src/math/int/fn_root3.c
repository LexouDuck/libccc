
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE


#define DEFINEFUNC_UINT_ROOT3(BITS) \
t_u##BITS	U##BITS##_Root3(t_u##BITS x) \
{ \
	int s; \
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
	if CCCERROR((x < 0), ERROR_MATHDOMAIN, NULL)\
		return (S##BITS##_ERROR); \
	int s; \
	t_s##BITS y; \
	t_s##BITS b; \
	y = 0; \
	for (s = (BITS - 1); s >= 0; s -= 3) \
	{ \
		y += y; \
		b = 3 * y * ((t_s##BITS) y + 1) + 1; \
		if ((x >> s) >= b) \
		{ \
			x -= b << s; \
			y++; \
		} \
	} \
	return y; \
} \

DEFINEFUNC_SINT_ROOT3(8)
DEFINEFUNC_SINT_ROOT3(16)
DEFINEFUNC_SINT_ROOT3(32)
DEFINEFUNC_SINT_ROOT3(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINT_ROOT3(128)
#endif
