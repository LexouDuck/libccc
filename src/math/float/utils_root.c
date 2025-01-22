
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH

#elif LIBCONFIG_USE_CCC_MATH



/* Some lookup tables for fast newton method initial guess */
#define DEFINEDATA_FLOAT_SQRT(BITS) \
static const t_f##BITS	f##BITS##_powers_pos[] = \
{ \
	SQRT_2, \
	(t_f##BITS)0x1.0p+1, \
	(t_f##BITS)0x1.0p+2, \
	(t_f##BITS)0x1.0p+4, \
	(t_f##BITS)0x1.0p+8, \
	(t_f##BITS)0x1.0p+16, \
	(t_f##BITS)0x1.0p+32, \
	(t_f##BITS)0x1.0p+64, \
	(t_f##BITS)0x1.0p+128, \
	(t_f##BITS)0x1.0p+256, \
	(t_f##BITS)0x1.0p+512, \
	(t_f##BITS)0x1.0p+1024, \
	(t_f##BITS)0x1.0p+2048, \
	(t_f##BITS)0x1.0p+4096, \
	(t_f##BITS)0x1.0p+8192, \
	(t_f##BITS)INFINITY \
}; \
static const t_f##BITS	f##BITS##_powers_neg[] = \
{ \
	INV_SQRT_2, \
	(t_f##BITS)0x1.0p-1, \
	(t_f##BITS)0x1.0p-2, \
	(t_f##BITS)0x1.0p-4, \
	(t_f##BITS)0x1.0p-8, \
	(t_f##BITS)0x1.0p-16, \
	(t_f##BITS)0x1.0p-32, \
	(t_f##BITS)0x1.0p-64, \
	(t_f##BITS)0x1.0p-128, \
	(t_f##BITS)0x1.0p-256, \
	(t_f##BITS)0x1.0p-512, \
	(t_f##BITS)0x1.0p-1024, \
	(t_f##BITS)0x1.0p-2048, \
	(t_f##BITS)0x1.0p-4096, \
	(t_f##BITS)0x1.0p-8192, \
	(t_f##BITS)0. \
}; \

#if LIBCONFIG_USE_FLOAT16
DEFINEDATA_FLOAT_SQRT(16)
#endif
DEFINEDATA_FLOAT_SQRT(32)

DEFINEDATA_FLOAT_SQRT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEDATA_FLOAT_SQRT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEDATA_FLOAT_SQRT(128)
#endif



#define DEFINEFUNC_FLOAT_ROOT2PN(BITS, EXTRA) \
t_f##BITS	__root2pN_f##BITS(t_s32 n) \
{ \
	if (n > 0 && (n >> 11)) \
		return (INFINITY); \
	const t_f##BITS* powers = f##BITS##_powers_pos; \
	if (n == 0) \
		return (1.); \
	else if (n < 0) \
	{ \
		n = -n; \
		powers = f##BITS##_powers_neg; \
	} \
	t_f##BITS result = 1.; \
	if (n & 0x0001) { result *= powers[0x0]; } \
	if (n & 0x0002) { result *= powers[0x1]; } \
	if (n & 0x0004) { result *= powers[0x2]; } \
	if (n & 0x0008) { result *= powers[0x3]; } \
	if (n & 0x0010) { result *= powers[0x4]; } \
	if (n & 0x0020) { result *= powers[0x5]; } \
	if (n & 0x0040) { result *= powers[0x6]; } \
	if (n & 0x0080) { result *= powers[0x7]; } \
	if (n & 0x0100) { result *= powers[0x8]; } \
	if (n & 0x0200) { result *= powers[0x9]; } \
	EXTRA \
	return (result); \
}

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_ROOT2PN(16,
	if (n & 0x0400) { result *= powers[0xA]; }
)
#endif
DEFINEFUNC_FLOAT_ROOT2PN(32,
	if (n & 0x0400) { result *= powers[0xA]; }
)
DEFINEFUNC_FLOAT_ROOT2PN(64,
	if (n & 0x0400) { result *= powers[0xA]; }
)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ROOT2PN(80,
	if (n & 0x0400) { result *= powers[0xA]; }
	if (n & 0x0800) { result *= powers[0xB]; }
	if (n & 0x1000) { result *= powers[0xC]; }
	if (n & 0x2000) { result *= powers[0xD]; }
	if (n & 0x4000) { result *= powers[0xE]; }
)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ROOT2PN(128,
	if (n & 0x0400) { result *= powers[0xA]; }
	if (n & 0x0800) { result *= powers[0xB]; }
	if (n & 0x1000) { result *= powers[0xC]; }
	if (n & 0x2000) { result *= powers[0xD]; }
	if (n & 0x4000) { result *= powers[0xE]; }
)
#endif



#else

const t_u16 __rsqrt_tab[128] =
{
	0xB451,0xB2F0,0xB196,0xB044,0xAEF9,0xADB6,0xAC79,0xAB43,
	0xAA14,0xA8EB,0xA7C8,0xA6AA,0xA592,0xA480,0xA373,0xA26B,
	0xA168,0xA06A,0x9F70,0x9E7B,0x9D8A,0x9C9D,0x9BB5,0x9AD1,
	0x99F0,0x9913,0x983A,0x9765,0x9693,0x95C4,0x94F8,0x9430,
	0x936B,0x92A9,0x91EA,0x912E,0x9075,0x8FBE,0x8F0A,0x8E59,
	0x8DAA,0x8CFE,0x8C54,0x8BAC,0x8B07,0x8A64,0x89C4,0x8925,
	0x8889,0x87EE,0x8756,0x86C0,0x862B,0x8599,0x8508,0x8479,
	0x83EC,0x8361,0x82D8,0x8250,0x81C9,0x8145,0x80C2,0x8040,
	0xFF02,0xFD0E,0xFB25,0xF947,0xF773,0xF5AA,0xF3EA,0xF234,
	0xF087,0xEEE3,0xED47,0xEBB3,0xEA27,0xE8A3,0xE727,0xE5B2,
	0xE443,0xE2DC,0xE17A,0xE020,0xDECB,0xDD7D,0xDC34,0xDAF1,
	0xD9B3,0xD87B,0xD748,0xD61A,0xD4F1,0xD3CD,0xD2AD,0xD192,
	0xD07B,0xCF69,0xCE5B,0xCD51,0xCC4A,0xCB48,0xCA4A,0xC94F,
	0xC858,0xC764,0xC674,0xC587,0xC49D,0xC3B7,0xC2D4,0xC1F4,
	0xC116,0xC03C,0xBF65,0xBE90,0xBDBE,0xBCEF,0xBC23,0xBB59,
	0xBA91,0xB9CC,0xB90A,0xB84A,0xB78C,0xB6D0,0xB617,0xB560,
};

#endif
