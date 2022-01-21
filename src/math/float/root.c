
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



/* Some lookup tables for fast newton method initial guess */
static const t_f32 f32_powers_pos[] =
{
	SQRT_2,
	(t_f32)0x1.0p+1,
	(t_f32)0x1.0p+2,
	(t_f32)0x1.0p+4,
	(t_f32)0x1.0p+8,
	(t_f32)0x1.0p+16,
	(t_f32)0x1.0p+32,
	(t_f32)0x1.0p+64,
	(t_f32)0x1.0p+128,
	(t_f32)0x1.0p+256,
	(t_f32)0x1.0p+512,
	INFINITY,
};
static const t_f32 f32_powers_neg[] =
{
	INV_SQRT_2,
	(t_f32)0x1.0p-1,
	(t_f32)0x1.0p-2,
	(t_f32)0x1.0p-4,
	(t_f32)0x1.0p-8,
	(t_f32)0x1.0p-16,
	(t_f32)0x1.0p-32,
	(t_f32)0x1.0p-64,
	(t_f32)0x1.0p-128,
	(t_f32)0x1.0p-256,
	(t_f32)0x1.0p-512,
	0.
};

static const t_f64 f64_powers_pos[] =
{
	SQRT_2,
	(t_f64)0x1.0p+1,
	(t_f64)0x1.0p+2,
	(t_f64)0x1.0p+4,
	(t_f64)0x1.0p+8,
	(t_f64)0x1.0p+16,
	(t_f64)0x1.0p+32,
	(t_f64)0x1.0p+64,
	(t_f64)0x1.0p+128,
	(t_f64)0x1.0p+256,
	(t_f64)0x1.0p+512,
	INFINITY,
};
static const t_f64 f64_powers_neg[] =
{
	INV_SQRT_2,
	(t_f64)0x1.0p-1,
	(t_f64)0x1.0p-2,
	(t_f64)0x1.0p-4,
	(t_f64)0x1.0p-8,
	(t_f64)0x1.0p-16,
	(t_f64)0x1.0p-32,
	(t_f64)0x1.0p-64,
	(t_f64)0x1.0p-128,
	(t_f64)0x1.0p-256,
	(t_f64)0x1.0p-512,
	(t_f64)0x1.0p-1024,
	0.
};

#if LIBCONFIG_USE_FLOAT80
static const t_f80 f80_powers_pos[] =
{
	SQRT_2,
	(t_f80)0x1.0p+1,
	(t_f80)0x1.0p+2,
	(t_f80)0x1.0p+4,
	(t_f80)0x1.0p+8,
	(t_f80)0x1.0p+16,
	(t_f80)0x1.0p+32,
	(t_f80)0x1.0p+64,
	(t_f80)0x1.0p+128,
	(t_f80)0x1.0p+256,
	(t_f80)0x1.0p+512,
	(t_f80)0x1.0p+1024,
	(t_f80)0x1.0p+2048,
	(t_f80)0x1.0p+4096,
	(t_f80)0x1.0p+8192,
	INFINITY,
};
static const t_f80 f80_powers_neg[] =
{
	INV_SQRT_2,
	(t_f80)0x1.0p-1,
	(t_f80)0x1.0p-2,
	(t_f80)0x1.0p-4,
	(t_f80)0x1.0p-8,
	(t_f80)0x1.0p-16,
	(t_f80)0x1.0p-32,
	(t_f80)0x1.0p-64,
	(t_f80)0x1.0p-128,
	(t_f80)0x1.0p-256,
	(t_f80)0x1.0p-512,
	(t_f80)0x1.0p-1024,
	(t_f80)0x1.0p-2048,
	(t_f80)0x1.0p-4096,
	(t_f80)0x1.0p-8192,
	0.
};
#endif

#if LIBCONFIG_USE_FLOAT128
static const t_f128 f128_powers_pos[] =
{
	SQRT_2,
	(t_f128)0x1.0p+1,
	(t_f128)0x1.0p+2,
	(t_f128)0x1.0p+4,
	(t_f128)0x1.0p+8,
	(t_f128)0x1.0p+16,
	(t_f128)0x1.0p+32,
	(t_f128)0x1.0p+64,
	(t_f128)0x1.0p+128,
	(t_f128)0x1.0p+256,
	(t_f128)0x1.0p+512,
	(t_f128)0x1.0p+1024,
	(t_f128)0x1.0p+2048,
	(t_f128)0x1.0p+4096,
	(t_f128)0x1.0p+8192,
	INFINITY,
};
static const t_f128 f128_powers_neg[] =
{
	INV_SQRT_2,
	(t_f128)0x1.0p-1,
	(t_f128)0x1.0p-2,
	(t_f128)0x1.0p-4,
	(t_f128)0x1.0p-8,
	(t_f128)0x1.0p-16,
	(t_f128)0x1.0p-32,
	(t_f128)0x1.0p-64,
	(t_f128)0x1.0p-128,
	(t_f128)0x1.0p-256,
	(t_f128)0x1.0p-512,
	(t_f128)0x1.0p-1024,
	(t_f128)0x1.0p-2048,
	(t_f128)0x1.0p-4096,
	(t_f128)0x1.0p-8192,
	0.
};
#endif



#define DEFINEFUNC_FLOAT_ROOT2PN(BITS) \
static t_f##BITS	F##BITS##_Root2_2pN(t_s32 n)				\
{																\
	if (n > 0 && (n >> 11))										\
		return (INFINITY);										\
	const t_f##BITS* powers = f##BITS##_powers_pos;				\
	if (n == 0)													\
		return (1.);											\
	else if (n < 0)												\
	{															\
		n = -n;													\
		powers = f##BITS##_powers_neg;							\
	}															\
	t_f##BITS result = 1.;										\
	if (n & 0x0001) { result *= powers[0x0]; }					\
	if (n & 0x0002) { result *= powers[0x1]; }					\
	if (n & 0x0004) { result *= powers[0x2]; }					\
	if (n & 0x0008) { result *= powers[0x3]; }					\
	if (n & 0x0010) { result *= powers[0x4]; }					\
	if (n & 0x0020) { result *= powers[0x5]; }					\
	if (n & 0x0040) { result *= powers[0x6]; }					\
	if (n & 0x0080) { result *= powers[0x7]; }					\
	if (n & 0x0100) { result *= powers[0x8]; } /* >= 64-bit */	\
	if (n & 0x0200) { result *= powers[0x9]; }					\
	if (n & 0x0400) { result *= powers[0xA]; }					\
	if (n & 0x0800) { result *= powers[0xB]; } /* >= 80-bit */	\
	if (n & 0x1000) { result *= powers[0xC]; }					\
	if (n & 0x2000) { result *= powers[0xD]; }					\
	if (n & 0x4000) { result *= powers[0xE]; }					\
	return (result);											\
}

DEFINEFUNC_FLOAT_ROOT2PN(32)
DEFINEFUNC_FLOAT_ROOT2PN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT2PN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT2PN(128)
#endif



#if 0
#define F32_FASTSQRT_CONSTANT	0x5F375A86			// from the Quake III source code
#define F64_FASTSQRT_CONSTANT	0x5FE6EB50C7B537A9	// from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
	/* Fast Inverse square root (from the Quake III source code) */
	u_float_cast result = { x };
	t_float x_2;
	x_2 = result.value_float * 0.5;
	result.value_int = FLOAT_FASTSQRT_CONSTANT - (result.value_int >> 1);
	// TODO handle extended precision types
	result.value_float = result.value_float * (1.5 - (x_2 * result.value_float * result.value_float)); // 1st iteration
	result.value_float = result.value_float * (1.5 - (x_2 * result.value_float * result.value_float)); // 2nd iteration, this can be removed
	return (result.value_float * x);
#endif

#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Root2, sqrt)
#else
#define DEFINEFUNC_FLOAT_ROOT2(BITS) \
t_f##BITS	F##BITS##_Root2(t_f##BITS x)							\
{																	\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)				\
	HANDLE_ERROR(MATHDOMAIN, (x < 0.), return (NAN);)				\
	/* Newton derivative approximation by iteration */				\
	static const t_s32	max_i = 4;									\
	t_s32	i;														\
	t_f##BITS	result;												\
	t_f##BITS	previous;											\
	if (IS_NAN(x) || x < 0.)										\
		return (NAN);												\
	if (x == 0.)													\
		return (0.);												\
	if (x == 1.)													\
		return (1.);												\
	i = F##BITS##_GetExp2(x);										\
	result = (i < 0 ? 0.75 : 1.25);									\
	result *= F##BITS##_Root2_2pN(i);								\
	previous = INFINITY;											\
	i = 0;															\
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX)			\
	{																\
		previous = result;											\
		result -= (result * result - x) / (2 * result);				\
		if (++i == max_i)											\
			break;													\
	}																\
	return (result);												\
}

DEFINEFUNC_FLOAT_ROOT2(32)
DEFINEFUNC_FLOAT_ROOT2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT2(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Root3, cbrt)
#else
#define DEFINEFUNC_FLOAT_ROOT3(BITS) \
t_f##BITS	F##BITS##_Root3(t_f##BITS x)							\
{																	\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)				\
	/* Newton derivative approximation by iteration */				\
	static const t_s32	max_i = 4;									\
	t_s32	i;														\
	t_f##BITS	square;												\
	t_f##BITS	result;												\
	t_f##BITS	previous;											\
	if (x == 0)														\
		return (0);													\
	if (F##BITS##_Abs(x) == 1.)										\
		return (SIGN(x));											\
	i = F##BITS##_GetExp2(x);										\
	result = SIGN(x) * (i < 0 ? 0.75 : 1.25);						\
	result *= F##BITS##_Root2_2pN(i * 2 / 3);						\
	previous = INFINITY;											\
	i = 0;															\
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX)			\
	{																\
		previous = result;											\
		square = result * result;									\
		result -= (result * square - x) / (3 * square);				\
		if (++i == max_i)											\
			break;													\
	}																\
	return (result);												\
}

DEFINEFUNC_FLOAT_ROOT3(32)
DEFINEFUNC_FLOAT_ROOT3(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT3(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT3(128)
#endif

#endif



#define DEFINEFUNC_FLOAT_ROOTN(BITS) \
t_f##BITS	F##BITS##_RootN(t_f##BITS x, t_u8 n)					\
{																	\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)				\
	HANDLE_ERROR(MATHDOMAIN, (n % 2 == 0 && x < 0), return (NAN);)	\
	/* Newton derivative approximation by iteration */				\
	static const t_s32	max_i = 4;									\
	t_s32	i;														\
	t_f##BITS	result;												\
	t_f##BITS	previous;											\
	t_f##BITS	power;												\
	if (n == 0)														\
		return (NAN);												\
	if (n == 1)														\
		return (x);													\
	if (x == 0)														\
		return (0);													\
	if (F##BITS##_Abs(x) == 1.)										\
		return (SIGN(x));											\
	i = F##BITS##_GetExp2(x);										\
	result = SIGN(x) * (i < 0 ? 1 : 1.25);							\
	result *= F##BITS##_Root2_2pN(i * 2 / (t_s32)n);				\
	previous = 0.;													\
	i = 0;															\
	n -= 1;															\
	while (F##BITS##_Abs(result - previous) > FLOAT_APPROX)			\
	{																\
		previous = result;											\
		power = result;												\
		for (t_u32 j = 1; j < n; ++j)								\
		{															\
			power *= result;										\
		}															\
		result -= (power * result - x) / ((n + 1) * power);			\
		if (++i == max_i)											\
			break;													\
	}																\
	return (result);												\
}

DEFINEFUNC_FLOAT_ROOTN(32)
DEFINEFUNC_FLOAT_ROOTN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOTN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOTN(128)
#endif
