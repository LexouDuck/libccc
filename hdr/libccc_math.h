/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_math.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_H
#define __LIBCCC_MATH_H
/*! @file libccc_math.h
**	This header defines the common standard math functions and macro defines.
**	@addtogroup libccc_math
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#ifndef ABS			//! Expands to the absolute value of 'x'
#define ABS(x)		((x) < 0 ? -(x) : (x))
#endif

#ifndef SIGN		//! Expands to +1 or -1 according to the sign of 'x'
#define SIGN(x)		((x) < 0 ? -1 : +1)
#endif

#ifndef MIN			//!	Expands to the minimum value of 'x' and 'y'
#define MIN(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef MAX			//! Expands to the maximum value of 'x' and 'y'
#define MAX(x, y)	((x) < (y) ? (y) : (x))
#endif



#ifndef INFINITY		//! Define the floating-point infinity value: use -INFINITY for negative inf
#define INFINITY		(1. / 0.)
#endif
#ifndef IS_INFINITY		//! Checks if the given 'x' is either +INFINITY or -INFINITY
#define IS_INFINITY(x)	((x) == INFINITY || (x) == -INFINITY)
#endif

#ifndef NAN				//! Define the floating-point "not a number" value.
#define NAN				(0. / 0.)
#endif
#ifndef IS_NAN			//! Checks if the given 'x' has a "not a number" value.
#define IS_NAN(x)		((x) != (x))
#endif

/*!
**	This very small float is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable kind of operation,
**	so it's often better to do (ABS(x - y) <= FLOAT_BIAS) to check for equality.
*/
#define FLOAT_BIAS		(1.0e-10)

//	TODO document this
#define SAMPLE_NB		(1024)



/*
**	Various relevant mathematical constants - these are used to speed up
**	our fast approximate versions of some fundamental algorithms and functions.
*/
#define QUARTER_PI		DIV_PI_4						//!< Alias for DIV_PI_4
#define HALF_PI			DIV_PI_2						//!< Alias for DIV_PI_2
#define DIV_PI_4		(t_float)(0x1.921FB54442D18p-1)	//!< Quarter of pi (PI / 4):		
#define DIV_PI_2		(t_float)(0x1.921FB54442D18p+0)	//!< Half of pi (PI / 2):			
#define PI				(t_float)(0x1.921FB54442D18p+1)	//!< A circle's periphery, pi:		3.141592653589793238462643383279502884197169399375105820974...
#define TAU 			(t_float)(0x1.921FB54442D18p+2)	//!< Double pi (PI * 2):			6.283185307179586476925286766559005768394338798750211641949...
#define INV_PI			(t_float)(0x1.45F306DC9C883p-2)	//!< Inverse of pi (1 / PI):		0.318309886183790671537767526745028724068919291480912897495...
#define INV_TAU			(t_float)(0x1.45F306DC9C883p-3)	//!< Inverse of tau (1 / (PI * 2)):	0.159154943091895335768883763372514362034459645740456448747...

#define E				(t_float)(0x1.5BF0A8B145769p+1)	//!< The exponential number, e:		2.718281828459045235360287471352662497757247093699959574966...
#define LN_2			(t_float)(0x1.62E42FEFA39EFp-1)	//!< The natural logarithm of 2:	0.693147180559945309417232121458176568075500134360255254120...
#define LN_10			(t_float)(0x1.26BB1BBB55516p+1)	//!< The natural logarithm of 10:	2.302585092994045684017991454684364207601101488628772976033...

#define SQRT_2			(t_float)(0x1.6A09E667F3BCDp+0)	//!< The square root of 2:	1.414213562373095048801688724209698078569671875376948073176...
#define INV_SQRT_2		(t_float)(0x1.6A09E667F3BCDp-1)	//!< The inverse square root of 2:	1 / SQRT_2
#define SQRT_3			(t_float)(0x1.BB67AE8584CAAp+0)	//!< The square root of 3:	1.732050807568877293527446341505872366942805253810380628055...
#define INV_SQRT_3		(t_float)(0x1.279A74590331Cp-1)	//!< The inverse square root of 3:	1 / SQRT_3
#define SQRT_5			(t_float)(0x1.1E3779B97F4A7p+1)	//!< The square root of 5:	2.236067977499789696409173668731276235440618359611525724270...
#define INV_SQRT_5		(t_float)(0x1.C9F25C5BFEDD9p-2)	//!< The inverse square root of 5:	1 / SQRT_5



//! The type of function which takes one real number and outputs one real number
typedef		t_float	(*f_real_function)(t_float x);
//! The type of function which takes two real numbers and outputs one real number
typedef		t_float	(*f_real_operator)(t_float x, t_float y);



/*
** ************************************************************************** *|
**                     Classical Real Number Operations                       *|
** ************************************************************************** *|
*/

//! Returns the base-2 exponent of 'x', as an integer
t_s32						Math_GetExp(t_float x);
#define c_getexp			Math_GetExp
#define Math_GetExponent	Math_GetExp

//! Returns the absolute value of 'x' (makes 'x' positive)
t_float						Math_Abs(t_float x);
#define c_fabs				Math_Abs
#define Math_AbsoluteValue	Math_Abs

//! Returns the division remainder of 'x' divided by 'y'
t_float						Math_Mod(t_float x, t_float y);
#define c_fmod				Math_Mod
#define Math_Modulo			Math_Mod

//! Returns the value of 'x', rounded to the nearest integer
t_float						Math_Round(t_float x);
#define c_round			Math_Round
#define Math_FloatRound		Math_Round

//! Returns the value of 'x', rounded towards 0
t_float						Math_Truncate(t_float x);
#define c_trunc			Math_Truncate
#define Math_FloatTrunc		Math_Truncate

//! Returns the value of 'x', rounded to the superior integer
t_float						Math_Floor(t_float x);
#define c_floor			Math_Floor
#define Math_FloatFloor		Math_Floor

//! Returns the value of 'x', rounded to the inferior integer
t_float						Math_Ceiling(t_float x);
#define c_ceil				Math_Ceiling
#define Math_FloatCeiling	Math_Ceiling



//! Returns the value of 'x' to the power of 'y' (float)
t_float						Math_Pow(t_float x, t_float y);
#define c_pow				Math_Pow
#define Math_Power			Math_Pow

//! Returns the value of 'x' to the power of 'n' (integer)
t_float						Math_Pow_N(t_float x, t_int n);
#define c_pow_n			Math_Pow_N
#define Math_Power_N		Math_Pow_N

//! Returns the square root of 'x' (inverse of power of 2)
t_float						Math_SqRt(t_float x);
#define c_sqrt				Math_SqRt
#define Math_SquareRoot		Math_SqRt

//! Returns the cubic root of 'x' (inverse of power of 3)
t_float						Math_CbRt(t_float x);
#define c_cbrt				Math_CbRt
#define Math_CubicRoot		Math_CbRt

//! Returns the n-ic root of 'x' (inverse of power of 'n')
t_float						Math_NRt(t_float x, t_u8 n);
#define c_nrt				Math_NRt
#define Math_NRoot			Math_NRt



//! Returns the exponential function's value for 'x'
t_float							Math_Exp(t_float x);
#define c_exp					Math_Exp
#define Math_Exponential		Math_Exp

//! Returns the natural logarithm of 'x'
t_float							Math_Ln(t_float x);
#define c_ln					Math_Ln
#define Math_NaturalLogarithm	Math_Ln

//! Returns the binary (base-2) logarithm of 'x'
t_float							Math_Log_2(t_float x);
#define c_lg					Math_Log_2
#define Math_Logarithm_Base2	Math_Log_2

//! Returns the decimal (base-10) logarithm of 'x'
t_float							Math_Log_10(t_float x);
#define c_log					Math_Log_10
#define Math_Logarithm_Base10	Math_Log_10

//! Returns the base-'n' logarithm of 'x'
t_float							Math_Log_N(t_float x, t_float n);
#define c_logn					Math_Log_N
#define Math_Logarithm_BaseN	Math_Log_N




//! Returns the cosine of 'x' (horizontal trigonometry coordinate)
t_float								Math_Cos(t_float x);
#define c_cos						Math_Cos
#define Math_Cosine					Math_Cos

//! Returns the sine of 'x' (vertical trigonometry coordinate)
t_float								Math_Sin(t_float x);
#define c_sin						Math_Sin
#define Math_Sine					Math_Sin

//! Returns the tangent of 'x' (trigonometry tangent line)
t_float								Math_Tan(t_float x);
#define c_tan						Math_Tan
#define Math_Tangent				Math_Tan

//! Returns the arc-cosine of 'x' (inverse of the cos function)
t_float								Math_ArcCos(t_float x);
#define c_acos						Math_ArcCos
#define Math_InvCosine				Math_ArcCos
#define Math_Cos_1					Math_ArcCos

//! Returns the arc-sine of 'x' (inverse of the sin function)
t_float								Math_ArcSin(t_float x);
#define c_asin						Math_ArcSin
#define Math_InvSine				Math_ArcSin
#define Math_Sin_1					Math_ArcSin

//! Returns the arc-tangent of 'x' (inverse of the tan function)
t_float								Math_ArcTan(t_float x);
#define c_atan						Math_ArcTan
#define Math_InvTangent				Math_ArcTan



//! Returns the arc-tangent of ('y' / 'x'), used to find an angle
t_float								Math_ArcTan2(t_float y, t_float x);
#define c_atan2					Math_ArcTan2
#define Math_ArcTangent_YoverX		Math_ArcTan2



//! Returns the hyperbolic cosine of 'x'
t_float								Math_CosH(t_float x);
#define c_cosh						Math_CosH
#define Math_Cosine_Hyperbolic		Math_CosH

//! Returns the hyperbolic sine of 'x'
t_float								Math_SinH(t_float x);
#define c_sinh						Math_SinH
#define Math_Sine_Hyperbolic		Math_SinH

//! Returns the hyperbolic tangent of 'x'
t_float								Math_TanH(t_float x);
#define c_tanh						Math_TanH
#define Math_Tangent_Hyperbolic		Math_TanH

//! Returns the hyperbolic arc-cosine of 'x' (inverse of the cosh function)
t_float								Math_InvCosH(t_float x);
#define c_acosh					Math_InvCosH
#define Math_InvCosine_Hyperbolic	Math_InvCosH

//! Returns the hyperbolic arc-sine of 'x' (inverse of the sinh function)
t_float								Math_InvSinH(t_float x);
#define c_asinh					Math_InvSinH
#define Math_InvSine_Hyperbolic		Math_InvSinH

//! Returns the hyperbolic arc-tangent of 'x' (inverse of the tanh function)
t_float								Math_InvTanH(t_float x);
#define c_atanh					Math_InvTanH
#define Math_InvTangent_Hyperbolic	Math_InvTanH



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



#if (LIBCCCCONFIG_FAST_APPROX_MATH == 0)

	#ifdef _FLOAT_32_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##f(x, y)); }
	#endif

	#ifdef _FLOAT_64_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME(x, y)); }
	#endif

	#ifdef _FLOAT_80_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##l(x, y)); }
	#endif

	#ifdef _FLOAT_128_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##q(x, y)); }
	#endif

#endif

/*
** ************************************************************************** *|
**                            Float Type Definitions                          *|
** ************************************************************************** *|
*/

/*!
**	This union type is used in several math function implementations,
**	to manipulate float bits directly with bitwise operators.
*/
typedef union	u_float_cast_
{
	t_float		value_float;
#ifdef _FLOAT_32_
	t_s32		value_int;
#endif
#ifdef _FLOAT_64_
	t_s64		value_int;
#endif
#ifdef _FLOAT_80_
	t_s64[2]	value_int;
#endif
#ifdef _FLOAT_128_
	t_s64[2]	value_int;
#endif
}				u_float_cast;

/*
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
#define F32_SIGNED			(0x80000000)	//!< A 32-bit floating-point number's sign bit (bitmask)
#define F32_EXPONENT_BIAS	(127)			//!< A 32-bit floating-point number's exponent bias offset
#define F32_EXPONENT		(0x7F800000)	//!< A 32-bit floating-point number's exponent bit region (bitmask)
#define F32_EXPONENT_ZERO	(0x3F800000)	//!< A 32-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F32_EXPONENT_BITS	(8)				//!< A 32-bit floating-point number's amount of bits dedicated to the exponent
#define F32_MANTISSA		(0x007FFFFF)	//!< A 32-bit floating-point number's mantissa bit region (bitmask)
#define F32_MANTISSA_SIGNED	(0x807FFFFF)	//!< A 32-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F32_MANTISSA_BITS	(23)			//!< A 32-bit floating-point number's amount of bits dedicated to the mantissa
#define F32_INIT_VALUE		(0x1.p-23)		//!< A 32-bit floating-point number's value if all bits are zero

/*
**	IEEE 754 64-bit floating point double-precision bitwise macros
*/
#define F64_SIGNED			(0x8000000000000000)	//!< A 64-bit floating-point number's sign bit (bitmask)
#define F64_EXPONENT_BIAS	(1023)					//!< A 64-bit floating-point number's exponent bias offset
#define F64_EXPONENT		(0x7FF0000000000000)	//!< A 64-bit floating-point number's exponent bit region (bitmask)
#define F64_EXPONENT_ZERO	(0x3FF0000000000000)	//!< A 64-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F64_EXPONENT_BITS	(11)					//!< A 64-bit floating-point number's amount of bits dedicated to the exponent
#define F64_MANTISSA		(0x000FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa bit region (bitmask)
#define F64_MANTISSA_SIGNED	(0x800FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F64_MANTISSA_BITS	(52)					//!< A 64-bit floating-point number's amount of bits dedicated to the mantissa
#define F64_INIT_VALUE		(0x1.p-52)				//!< A 64-bit floating-point number's value if all bits are zero

/*
**	x86 80-bit floating point extended precision bitwise macros
*/
#define F80_SIGNED			(0x80000000000000000000L)	//!< A 80-bit floating-point number's sign bit (bitmask)
#define F80_EXPONENT_BIAS	(16383)						//!< A 80-bit floating-point number's exponent bias offset
#define F80_EXPONENT		(0x7FFF0000000000000000L)	//!< A 80-bit floating-point number's exponent bit region (bitmask)
#define F80_EXPONENT_ZERO	(0x3FFF0000000000000000L)	//!< A 80-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F80_EXPONENT_BITS	(15)						//!< A 80-bit floating-point number's amount of bits dedicated to the exponent
#define F80_MANTISSA		(0x0000FFFFFFFFFFFFFFFFL)	//!< A 80-bit floating-point number's mantissa bit region (bitmask)
#define F80_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFL)	//!< A 80-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F80_MANTISSA_BITS	(64)						//!< A 80-bit floating-point number's amount of bits dedicated to the mantissa
#define F80_INIT_VALUE		(0x1.p-64)					//!< A 80-bit floating-point number's value if all bits are zero

/*
**	IEEE 754 128-bit floating point quadruple-precision bitwise macros
*/
#define F128_SIGNED				(0x80000000000000000000000000000000L)	//!< A 128-bit floating-point number's sign bit (bitmask)
#define F128_EXPONENT_BIAS		(16383)									//!< A 128-bit floating-point number's exponent bias offset
#define F128_EXPONENT			(0x7FFF0000000000000000000000000000L)	//!< A 128-bit floating-point number's exponent bit region (bitmask)
#define F128_EXPONENT_ZERO		(0x3FFF0000000000000000000000000000L)	//!< A 128-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F128_EXPONENT_BITS		(15)									//!< A 128-bit floating-point number's amount of bits dedicated to the exponent
#define F128_MANTISSA			(0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL)	//!< A 128-bit floating-point number's mantissa bit region (bitmask)
#define F128_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL)	//!< A 128-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F128_MANTISSA_BITS		(112)									//!< A 128-bit floating-point number's amount of bits dedicated to the mantissa
#define F128_INIT_VALUE			(0x1.p-112)								//!< A 128-bit floating-point number's value if all bits are zero



/*
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_, etc) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/

#ifdef _FLOAT_32_
	#define FLOAT_SIGNED			F32_SIGNED
	#define FLOAT_EXPONENT_BIAS		F32_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F32_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F32_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F32_EXPONENT_BITS
	#define FLOAT_MANTISSA			F32_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F32_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F32_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F32_INIT_VALUE
#endif

#ifdef _FLOAT_64_
	#define FLOAT_SIGNED			F64_SIGNED
	#define FLOAT_EXPONENT_BIAS		F64_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F64_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F64_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F64_EXPONENT_BITS
	#define FLOAT_MANTISSA			F64_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F64_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F64_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F64_INIT_VALUE
#endif

#ifdef _FLOAT_80_
	#define FLOAT_SIGNED			F80_SIGNED
	#define FLOAT_EXPONENT_BIAS		F80_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F80_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F80_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F80_EXPONENT_BITS
	#define FLOAT_MANTISSA			F80_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F80_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F80_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F80_INIT_VALUE
#endif

#ifdef _FLOAT_128_
	#define FLOAT_SIGNED			F128_SIGNED
	#define FLOAT_EXPONENT_BIAS		F128_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F128_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F128_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F128_EXPONENT_BITS
	#define FLOAT_MANTISSA			F128_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F128_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F128_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F128_INIT_VALUE
#endif



/*! @} */
HEADER_END
#endif
