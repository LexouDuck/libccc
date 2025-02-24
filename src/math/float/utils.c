
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH

#elif LIBCONFIG_USE_CCC_MATH

#else



#if LIBCONFIG_USE_FLOAT16
t_f16	__math_divzero_f16    (t_bool sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
t_f16	__math_invalid_f16    (t_f16  x)	{ return (x - x) / (x - x); }
t_f16	__math_overflow_f16   (t_f16  x)	{ return (INFINITY * x); }
t_f16	__math_underflow_f16  (t_f16  x)	{ return (0 * x); }
#endif
t_f32	__math_divzero_f32    (t_bool sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
t_f32	__math_invalid_f32    (t_f32  x)	{ return (x - x) / (x - x); }
t_f32	__math_overflow_f32   (t_f32  x)	{ return (INFINITY * x); }
t_f32	__math_underflow_f32  (t_f32  x)	{ return (0 * x); }

t_f64	__math_divzero_f64    (t_bool sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
t_f64	__math_invalid_f64    (t_f64  x)	{ return (x - x) / (x - x); }
t_f64	__math_overflow_f64   (t_f64  x)	{ return (INFINITY * x); }
t_f64	__math_underflow_f64  (t_f64  x)	{ return (0 * x); }
#if LIBCONFIG_USE_FLOAT80
t_f80	__math_divzero_f80    (t_bool sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
t_f80	__math_invalid_f80    (t_f80  x)	{ return (x - x) / (x - x); }
t_f80	__math_overflow_f80   (t_f80  x)	{ return (INFINITY * x); }
t_f80	__math_underflow_f80  (t_f80  x)	{ return (0 * x); }
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128	__math_divzero_f128   (t_bool sign)	{ return /*fp_barrierf*/(sign ? -1.0f : 1.0f) / 0.0f; }
t_f128	__math_invalid_f128   (t_f128 x)	{ return (x - x) / (x - x); }
t_f128	__math_overflow_f128  (t_f128 x)	{ return (INFINITY * x); }
t_f128	__math_underflow_f128 (t_f128 x)	{ return (0 * x); }
#endif


/*
**	Copyright (c) 2008 Stephen L. Moshier <steve@moshier.net>
**
**	Permission to use, copy, modify, and distribute this software for any
**	purpose with or without fee is hereby granted, provided that the above
**	copyright notice and this permission notice appear in all copies.
**
**	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
**	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
**	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
**	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
**	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
**	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
**	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
/*!
**	Evaluate polynomial
**
**	SYNOPSIS:
**		int N;
**		t_f80 x, y, coef[N+1], polevl[];
**
**		y = polevll( x, coef, N );
**
**	DESCRIPTION:
**		Evaluates polynomial of degree N:
**
**	y  =  C₀ + C₁ x + C₂ x^2 +...+ Cₙ x^n
**
**	Coefficients are stored in reverse order:
**
**	coef[0] = Cₙ , ..., coef[N] = C₀
**
**
**	SPEED:
**	In the interest of speed, there are no checks for out of bounds arithmetic.
**	This routine is used by most of the functions in the library.
**	Depending on available equipment features, the user may wish to rewrite the
**	program in microcode or assembly language.
**
*/

/*! Polynomial evaluator:
**	P[0] x^n  +  P[1] x^(n-1)  +  ...  +  P[n]
*/
#define DEFINEFUNC_FLOAT_POLYNOMIAL(BITS) \
t_f##BITS __polynomial_f##BITS(t_f##BITS x, const t_f##BITS* coefficients, int n) \
{ \
	t_f##BITS result; \
	result = *coefficients++; \
	do { result = result * x + *coefficients++; } while (--n); \
	return result; \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_POLYNOMIAL(16)
#endif
DEFINEFUNC_FLOAT_POLYNOMIAL(32)

DEFINEFUNC_FLOAT_POLYNOMIAL(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_POLYNOMIAL(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_POLYNOMIAL(128)
#endif

#endif
