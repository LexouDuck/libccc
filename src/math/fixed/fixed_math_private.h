/*============================================================================*\
||                                            ______________________________  ||
||  fixed_math_private.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/\ /  /_/ / | ||
||                                           | /___/\/_/ /___-'\   \____/\  | ||
|| Copyright: LexouDuck & libccc contributors|  \____/\__/\____-'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

/*
**	This is a private header, used only by the `libccc/math/fixed` sources.
**	It contains helper functions to perform exact (integer-only) fixed-point
**	math, without going through floating-point numbers:
**	- full-width unsigned multiplication (giving a 2-word `(hi,lo)` result)
**	- 2-word by 1-word unsigned division (with overflow reporting)
**	- 2-word unsigned integer square root
**	- a base-2 exponential core (with a Q62 constants table, accurate to ~2⁻⁵⁶)
**	- a base-2 logarithm core (bit-by-bit, accurate to a few units of 2⁻⁵⁴)
**	All exponents/logarithms are exchanged in signed "q54" format, i.e. an
**	`s64` amounting to `value * 2^54`, which leaves ample headroom for any
**	fixed-point type configuration while keeping ~16 significant digits.
**
**	The helpers are defined for "word" sizes of 64 and (if available) 128 bits,
**	so that every `t_q(8|16|32|64)` function can promote its operands to 64-bit
**	words without needing 128-bit compiler support, and `t_q128` (which only
**	exists when `LIBCONFIG_USE_INT128` is set) can use 128-bit words.
*/

#ifndef __LIBCCC_MATH_FIXED_PRIVATE_H
#define __LIBCCC_MATH_FIXED_PRIVATE_H

#include "libccc.h"
#include "libccc/fixed.h"



//! Get the absolute value of a `t_s{BITS}` raw fixed-point value, as an unsigned `t_u{WB}` word (safe even for the minimum representable integer)
#define __FIXEDMATH_UABS(BITS, WB, V) \
	((V) < 0 \
		? (t_u##WB)(t_u##BITS)(0 - (t_u##BITS)(V)) \
		: (t_u##WB)(t_u##BITS)(V))



#define DEFINEFUNC_FIXEDMATH_HELPERS(WB) \
/*! Returns the index of the most significant set bit of `v` (with `v != 0`) */ \
static inline \
t_u8	__fixedmath_msb_##WB(t_u##WB v) \
{ \
	t_u8	result = 0; \
	while ((v >>= 1) != 0) \
		++result; \
	return (result); \
} \
 \
/*! Full multiplication: `(*hi,*lo) = a * b`, exact over 2 words */ \
static inline \
void	__fixedmath_umul_##WB(t_u##WB a, t_u##WB b, t_u##WB* hi, t_u##WB* lo) \
{ \
	t_u##WB const	mask = ((t_u##WB)1 << (WB / 2)) - 1; \
	t_u##WB const	a0 = (a & mask);	t_u##WB const	a1 = (a >> (WB / 2)); \
	t_u##WB const	b0 = (b & mask);	t_u##WB const	b1 = (b >> (WB / 2)); \
	t_u##WB const	p00 = a0 * b0; \
	t_u##WB const	p01 = a0 * b1; \
	t_u##WB const	p10 = a1 * b0; \
	t_u##WB const	p11 = a1 * b1; \
	t_u##WB const	mid = (p00 >> (WB / 2)) + (p01 & mask) + (p10 & mask); \
	*lo = (mid << (WB / 2)) | (p00 & mask); \
	*hi = p11 + (p01 >> (WB / 2)) + (p10 >> (WB / 2)) + (mid >> (WB / 2)); \
} \
 \
/*! Division of a 2-word value `(hi,lo)` by a 1-word value `d` (`d != 0`), returns the quotient (sets `*overflow` if it does not fit in one word) */ \
static inline \
t_u##WB	__fixedmath_udiv_##WB(t_u##WB hi, t_u##WB lo, t_u##WB d, t_bool* overflow) \
{ \
	if (hi >= d) \
	{ \
		*overflow = TRUE; \
		return (~(t_u##WB)0); \
	} \
	*overflow = FALSE; \
	if (hi == 0) \
		return (lo / d); \
	t_u##WB	q = 0; \
	t_u##WB	r = hi; \
	for (t_sint i = WB - 1; i >= 0; --i) \
	{	/* restoring bitwise division: the `carry` guard handles `r >= 2^(WB-1)` before the shift */ \
		t_u##WB const carry = (r >> (WB - 1)); \
		r = (r << 1) | ((lo >> i) & 1); \
		if (carry || r >= d) \
		{ \
			r -= d; \
			q |= ((t_u##WB)1 << i); \
		} \
	} \
	return (q); \
} \
 \
/*! Integer square root: returns `floor(sqrt(hi * 2^WB + lo))` (always fits in one word) */ \
static inline \
t_u##WB	__fixedmath_usqrt_##WB(t_u##WB hi, t_u##WB lo) \
{ \
	t_u##WB const	umax = ~(t_u##WB)0; \
	t_bool	overflow; \
	if (hi == 0 && lo == 0) \
		return (0); \
	if (hi >= umax - 1) \
	{	/* handle the largest inputs separately, so the Newton iteration below never needs a guess wider than one word */ \
		if (hi == umax - 1 && lo == 0) \
			return (umax - 1); \
		return (umax); \
	} \
	t_u8 const	length = (hi != 0) /* total bit length of the 2-word value */ \
		? (t_u8)(WB + __fixedmath_msb_##WB(hi) + 1) \
		: (t_u8)(__fixedmath_msb_##WB(lo) + 1); \
	t_u8 const	exponent = (length + 1) / 2; \
	/* initial guess: the smallest power of 2 which is >= sqrt(N), clamped to one word */ \
	t_u##WB	x0 = (exponent >= WB) ? umax : ((t_u##WB)1 << exponent); \
	/* Heron/Newton iteration: every iterate stays >= isqrt(N) > hi, so the division can never overflow */ \
	t_u##WB	q  = __fixedmath_udiv_##WB(hi, lo, x0, &overflow); \
	t_u##WB	x1 = (x0 >> 1) + (q >> 1) + (x0 & q & 1); \
	while (x1 < x0) \
	{ \
		x0 = x1; \
		q  = __fixedmath_udiv_##WB(hi, lo, x0, &overflow); \
		x1 = (x0 >> 1) + (q >> 1) + (x0 & q & 1); \
	} \
	return (x0); \
} \

DEFINEFUNC_FIXEDMATH_HELPERS(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXEDMATH_HELPERS(128)
#endif



/*
**	Table of `round(2^(2^-k) * 2^62)` for `k` in `[1, 54]` (index 0 is unused),
**	used by the base-2 exponential core below to compute `2^f` for a fractional
**	`f` in `[0, 1)`, one bit of `f` at a time.
*/
static const t_u64	__fixedmath_exp2_table[55] =
{
	0,
	0x5A827999FCEF3242, 0x4C1BF828C6DC54B8, 0x45CAE0F1F545EB74, 0x42D561B3E6243D8B,
	0x4166C34C5615D0EC, 0x40B268F9DE0183BA, 0x4058F6A7ECCCD5B6, 0x402C6BE96AF2FB58,
	0x4016321B687027A8, 0x400B18178BA33B14, 0x40058BCE410147E8, 0x4002C5D7BFF71DAE,
	0x400162E807EE7E5B, 0x4000B1730DF6A524, 0x400058B9497B8152, 0x40002C5C955DD701,
	0x4000162E46D6F26C, 0x40000B1722757B1B, 0x4000058B90FD3E0C, 0x400002C5C86F3F26,
	0x40000162E433C79B, 0x400000B17218EDD0, 0x40000058B90C3969, 0x4000002C5C860D55,
	0x400000162E4302D3, 0x4000000B17218074, 0x400000058B90BFFD, 0x40000002C5C85FEF,
	0x4000000162E42FF4, 0x40000000B17217F9, 0x4000000058B90BFC, 0x400000002C5C85FE,
	0x40000000162E42FF, 0x400000000B17217F, 0x40000000058B90BF, 0x4000000002C5C85F,
	0x400000000162E42F, 0x4000000000B17217, 0x400000000058B90B, 0x40000000002C5C85,
	0x4000000000162E42, 0x40000000000B1721, 0x4000000000058B90, 0x400000000002C5C8,
	0x40000000000162E4, 0x400000000000B172, 0x40000000000058B9, 0x4000000000002C5C,
	0x400000000000162E, 0x4000000000000B17, 0x400000000000058B, 0x40000000000002C5,
	0x4000000000000162, 0x40000000000000B1,
};

//! `log2(e) * 2^54`, rounded to nearest
#define __FIXEDMATH_LOG2E_Q54	((t_s64)0x005C551D94AE0BF8)
//! `log2(10) * 2^54`, rounded to nearest
#define __FIXEDMATH_LOG2_10_Q54	((t_s64)0x00D49A784BCD1B8B)
//! `ln(2) * 2^62`, rounded to nearest
#define __FIXEDMATH_LN2_Q62		((t_s64)0x2C5C85FDF473DE6B)
//! `log10(2) * 2^62`, rounded to nearest
#define __FIXEDMATH_LOG10_2_Q62	((t_s64)0x134413509F79FEF3)



#define DEFINEFUNC_FIXEDMATH_EXP2_LOG2(WB) \
/*! \
**	Base-2 exponential core: computes `trunc(2^(e / 2^54) * denom)`, i.e. the \
**	raw (unsigned) fixed-point value of `2^e` for a signed q54 exponent `e`. \
**	Sets `*overflow` (and returns `max_raw`) if the true (untruncated) result \
**	exceeds `max_raw` (the largest finite raw value), which matches the \
**	saturation behavior of the `Q*_FromF64` conversion functions. \
*/ \
static inline \
t_u##WB	__fixedmath_exp2_##WB(t_s64 e_q54, t_u##WB denom, t_u##WB max_raw, t_bool* overflow) \
{ \
	/* split `e = n + f` with `n` integer and `f` in `[0, 1)` (arithmetic shift right rounds toward -inf) */ \
	t_s64 const	n = (e_q54 >> 54); \
	t_u64 const	f = ((t_u64)e_q54 & (((t_u64)1 << 54) - 1)); \
	*overflow = FALSE; \
	/* compute `2^f` as a Q62 value in `[2^62, 2^63)`, one bit of `f` at a time */ \
	t_u64	acc = ((t_u64)1 << 62); \
	for (t_u8 k = 1; k <= 54; ++k) \
	{ \
		if ((f >> (54 - k)) & 1) \
		{ \
			t_u64	hi; \
			t_u64	lo; \
			__fixedmath_umul_64(acc, __fixedmath_exp2_table[k], &hi, &lo); \
			acc = (hi << 2) | (lo >> 62); \
		} \
	} \
	/* the result is `acc * denom * 2^(n - 62)`, computed exactly over 2 words */ \
	t_u##WB	phi; \
	t_u##WB	plo; \
	__fixedmath_umul_##WB((t_u##WB)acc, denom, &phi, &plo); \
	t_s64 const	shift = 62 - n; \
	if (shift <= 0) \
	{	/* shift left, checking for overflow */ \
		t_s64 const	ls = -shift; \
		if (phi != 0 || ls >= WB || plo > (max_raw >> ls)) \
		{ \
			*overflow = TRUE; \
			return (max_raw); \
		} \
		return (plo << ls); \
	} \
	if (shift >= 2 * WB) \
		return (0); \
	t_bool	fraction; \
	if (shift >= WB) \
	{ \
		fraction = (plo != 0 || (shift > WB && (phi & (((t_u##WB)1 << (shift - WB)) - 1)) != 0)); \
		plo = (phi >> (shift - WB)); \
		phi = 0; \
	} \
	else \
	{ \
		fraction = ((plo & (((t_u##WB)1 << shift) - 1)) != 0); \
		plo = (plo >> shift) | (phi << (WB - shift)); \
		phi >>= shift; \
	} \
	if (phi != 0 || plo > max_raw || (plo == max_raw && fraction)) \
	{ \
		*overflow = TRUE; \
		return (max_raw); \
	} \
	return (plo); \
} \
 \
/*! \
**	Base-2 logarithm core: computes `log2(v)` for an integer `v >= 1`, as a \
**	signed q54 value (always in `[0, WB * 2^54)`), accurate to a few units of \
**	2^-54 (the fractional bits are computed by repeated squaring in Q62). \
*/ \
static inline \
t_s64	__fixedmath_log2_##WB(t_u##WB v) \
{ \
	t_u8 const	m = __fixedmath_msb_##WB(v); \
	t_u64	mant; /* the mantissa of `v`, as a Q62 value in `[2^62, 2^63)` */ \
	if (m <= 62) \
		mant = (t_u64)(v << (62 - m)); \
	else \
		mant = (t_u64)(v >> (m - 62)); \
	t_u64	frac = 0; \
	for (t_u8 k = 0; k < 54; ++k) \
	{ \
		t_u64	hi; \
		t_u64	lo; \
		__fixedmath_umul_64(mant, mant, &hi, &lo); \
		mant = (hi << 2) | (lo >> 62); \
		frac <<= 1; \
		if (mant >= ((t_u64)1 << 63)) \
		{ \
			frac |= 1; \
			mant >>= 1; \
		} \
	} \
	return (((t_s64)m << 54) | (t_s64)frac); \
} \

DEFINEFUNC_FIXEDMATH_EXP2_LOG2(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXEDMATH_EXP2_LOG2(128)
#endif



#endif
