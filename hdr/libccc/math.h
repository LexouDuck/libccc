/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math.h                            |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_H
#define __LIBCCC_MATH_H
/*!@group{libccc_math,50,libccc/math.h}
**
**	This header defines the common standard math functions and macro defines.
**
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math}
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/tgmath}
*/

// TODO add PGCD/LCD() and PPCM/SCM() functions

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/math/constants.h"
#include "libccc/math/int.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Computes to the absolute value of `X` (ie: gives the positive equivalent of `X`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/abs}
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fabs}
**
**	- Math: @f$ {|x|} @f$
*/
#ifndef ABS
#define ABS(X)		((X) < 0 ? -(X) : (X))
#endif

//! Computes to `+1`, `-1` (or `0` if `(X) == 0`) according to the sign of `X`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/signbit} (differs)
**
**	- Math: @f$ {\frac{x}{|x|}} @f$
*/
#ifndef SIGN
#define SIGN(X)		((X) == 0 ? 0 : ((X) < 0 ? -1 : +1))
#endif

//! Checks if a value is negative (works for unsigned types, without causing tautology warnings)
/*!
**	This macro is useful to check if a value is negative, but its type (signed or unsigned) is not known.
**	In particular, the `char` and `enum` native C types are of unknown/undefined signage,
**	so this macro is useful to check that a value is positive, no matter the platform/environment.
**
**	- Math: @f$ {x < 0} @f$
*/
#ifndef ISNEG
#define ISNEG(X)	(!((X) > 0) && ((X) != 0))
#endif



//!	Expands to the minimum value between `X` and `Y` (the smaller of the two)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmin}
*/
#ifndef MIN
#define MIN(X, Y)	((X) < (Y) ? (X) : (Y))
#endif

//! Expands to the maximum value between `X` and `Y` (the larger of the two)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmax}
*/
#ifndef MAX
#define MAX(X, Y)	((X) < (Y) ? (Y) : (X))
#endif

//! Expands to a sequence of `Y` repetitive multiplications of `X` (ie: a compile-time `pow()` function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmax}
**
**	@param	X	The number to exponentiate (can be a value of any numeric type)
**	@param	Y	The exponent (must be an integer literal, in the range `[0,16]`)
*/
//!@{
#ifndef POW
#define POW(X, Y)		POW_##Y(X)
// TODO make more optimized with log2n method
#define POW_0(X)	(1)
#define POW_1(X)	(X)
#define POW_2(X)	(X * X)
#define POW_3(X)	(X * X * X)
#define POW_4(X)	(X * X * X * X)
#define POW_5(X)	(X * X * X * X * X)
#define POW_6(X)	(X * X * X * X * X * X)
#define POW_7(X)	(X * X * X * X * X * X * X)
#define POW_8(X)	(X * X * X * X * X * X * X * X)
#define POW_9(X)	(X * X * X * X * X * X * X * X * X)
#define POW_10(X)	(X * X * X * X * X * X * X * X * X * X)
#define POW_11(X)	(X * X * X * X * X * X * X * X * X * X * X)
#define POW_12(X)	(X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_13(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_14(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_15(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_16(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#endif
//!@}



#define MATH_DEFINE_FUNCTION(RETURN, BITS, NAME, CNAME, TYPE) \
	extern inline RETURN	 F##BITS##_##NAME(t_f##BITS a) \
	{																\
		return (__builtin_##CNAME##TYPE(a));						\
	}

#define MATH_DEFINE_OPERATOR_LOP(LOPERAND, BITS, NAME, CNAME, TYPE) \
	inline t_f##BITS	F##BITS##_##NAME(LOPERAND a, t_f##BITS b)	\
	{																\
		return (__builtin_##CNAME##TYPE(a, b));						\
	}

#define MATH_DEFINE_OPERATOR_ROP(ROPERAND, BITS, NAME, CNAME, TYPE) \
	inline t_f##BITS	F##BITS##_##NAME(t_f##BITS a, ROPERAND b)	\
	{																\
		return (__builtin_##CNAME##TYPE(a, b));						\
	}

#define MATH_DEFINE_OPERATOR_RET(RETURN, BITS, NAME, CNAME, TYPE) \
	inline RETURN	F##BITS##_##NAME(t_f##BITS a, t_f##BITS b)		\
	{																\
		return (__builtin_##CNAME##TYPE(a, b));						\
	}

#define MATH_DEFINE_REALFUNCTION(BITS, NAME, CNAME, TYPE) \
	extern inline t_f##BITS	F##BITS##_##NAME(t_f##BITS a) \
	{																\
		return (__builtin_##CNAME##TYPE(a));						\
	}

#define MATH_DEFINE_REALOPERATOR(BITS, NAME, CNAME, TYPE) \
	extern inline t_f##BITS	F##BITS##_##NAME(t_f##BITS a, t_f##BITS b) \
	{																\
		return (__builtin_##CNAME##TYPE(a, b));						\
	}

#define MATH_DEFINE_FUNCTION_F32(RETURN, NAME, CNAME)	MATH_DEFINE_FUNCTION(RETURN, 32, NAME, CNAME,f)
#define MATH_DEFINE_OPERATOR_LOP_F32(LOP,NAME, CNAME)	MATH_DEFINE_OPERATOR_LOP(LOP,32, NAME, CNAME,f)
#define MATH_DEFINE_OPERATOR_ROP_F32(ROP,NAME, CNAME)	MATH_DEFINE_OPERATOR_ROP(ROP,32, NAME, CNAME,f)
#define MATH_DEFINE_OPERATOR_RET_F32(RET,NAME, CNAME)	MATH_DEFINE_OPERATOR_RET(RET,32, NAME, CNAME,f)
#define MATH_DEFINE_REALFUNCTION_F32(    NAME, CNAME)	MATH_DEFINE_REALFUNCTION(    32, NAME, CNAME,f)
#define MATH_DEFINE_REALOPERATOR_F32(    NAME, CNAME)	MATH_DEFINE_REALOPERATOR(    32, NAME, CNAME,f)

#define MATH_DEFINE_FUNCTION_F64(RETURN, NAME, CNAME)	MATH_DEFINE_FUNCTION(RETURN, 64, NAME, CNAME,)
#define MATH_DEFINE_OPERATOR_LOP_F64(LOP,NAME, CNAME)	MATH_DEFINE_OPERATOR_LOP(LOP,64, NAME, CNAME,)
#define MATH_DEFINE_OPERATOR_ROP_F64(ROP,NAME, CNAME)	MATH_DEFINE_OPERATOR_ROP(ROP,64, NAME, CNAME,)
#define MATH_DEFINE_OPERATOR_RET_F64(RET,NAME, CNAME)	MATH_DEFINE_OPERATOR_RET(RET,64, NAME, CNAME,)
#define MATH_DEFINE_REALFUNCTION_F64(    NAME, CNAME)	MATH_DEFINE_REALFUNCTION(    64, NAME, CNAME,)
#define MATH_DEFINE_REALOPERATOR_F64(    NAME, CNAME)	MATH_DEFINE_REALOPERATOR(    64, NAME, CNAME,)

#if LIBCONFIG_USE_FLOAT80
#define MATH_DEFINE_FUNCTION_F80(RETURN, NAME, CNAME)	MATH_DEFINE_FUNCTION(RETURN, 80, NAME, CNAME,l)
#define MATH_DEFINE_OPERATOR_LOP_F80(LOP,NAME, CNAME)	MATH_DEFINE_OPERATOR_LOP(LOP,80, NAME, CNAME,l)
#define MATH_DEFINE_OPERATOR_ROP_F80(ROP,NAME, CNAME)	MATH_DEFINE_OPERATOR_ROP(ROP,80, NAME, CNAME,l)
#define MATH_DEFINE_OPERATOR_RET_F80(RET,NAME, CNAME)	MATH_DEFINE_OPERATOR_RET(RET,80, NAME, CNAME,l)
#define MATH_DEFINE_REALFUNCTION_F80(    NAME, CNAME)	MATH_DEFINE_REALFUNCTION(    80, NAME, CNAME,l)
#define MATH_DEFINE_REALOPERATOR_F80(    NAME, CNAME)	MATH_DEFINE_REALOPERATOR(    80, NAME, CNAME,l)
#else
#define MATH_DEFINE_FUNCTION_F80(RETURN, NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_LOP_F80(LOP,NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_ROP_F80(ROP,NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_RET_F80(RET,NAME, CNAME)	
#define MATH_DEFINE_REALFUNCTION_F80(    NAME, CNAME)	
#define MATH_DEFINE_REALOPERATOR_F80(    NAME, CNAME)	
#endif

#if LIBCONFIG_USE_FLOAT128
#define MATH_DEFINE_FUNCTION_F128(RETURN, NAME, CNAME)	MATH_DEFINE_FUNCTION(RETURN, 128,NAME, CNAME,q)
#define MATH_DEFINE_OPERATOR_LOP_F128(LOP,NAME, CNAME)	MATH_DEFINE_OPERATOR_LOP(LOP,128,NAME, CNAME,q)
#define MATH_DEFINE_OPERATOR_ROP_F128(ROP,NAME, CNAME)	MATH_DEFINE_OPERATOR_ROP(ROP,128,NAME, CNAME,q)
#define MATH_DEFINE_OPERATOR_RET_F128(RET,NAME, CNAME)	MATH_DEFINE_OPERATOR_RET(RET,128,NAME, CNAME,q)
#define MATH_DEFINE_REALFUNCTION_F128(    NAME, CNAME)	MATH_DEFINE_REALFUNCTION(    128,NAME, CNAME,q)
#define MATH_DEFINE_REALOPERATOR_F128(    NAME, CNAME)	MATH_DEFINE_REALOPERATOR(    128,NAME, CNAME,q)
#else
#define MATH_DEFINE_FUNCTION_F128(RETURN, NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_LOP_F128(LOP,NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_ROP_F128(ROP,NAME, CNAME)	
#define MATH_DEFINE_OPERATOR_RET_F128(RET,NAME, CNAME)	
#define MATH_DEFINE_REALFUNCTION_F128(    NAME, CNAME)	
#define MATH_DEFINE_REALOPERATOR_F128(    NAME, CNAME)	
#endif



#define MATH_DECL_FUNCTION(RETURN, NAME, CNAME) \
	MATH_DEFINE_FUNCTION_F32 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_FUNCTION_F64 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_FUNCTION_F80 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_FUNCTION_F128(RETURN, NAME, CNAME)	\

#define MATH_DECL_OPERATOR_LOP(LOPERAND, NAME, CNAME) \
	MATH_DEFINE_OPERATOR_LOP_F32 (LOPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_LOP_F64 (LOPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_LOP_F80 (LOPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_LOP_F128(LOPERAND, NAME, CNAME)	\

#define MATH_DECL_OPERATOR_ROP(ROPERAND, NAME, CNAME) \
	MATH_DEFINE_OPERATOR_ROP_F32 (ROPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_ROP_F64 (ROPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_ROP_F80 (ROPERAND, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_ROP_F128(ROPERAND, NAME, CNAME)	\

#define MATH_DECL_OPERATOR_RET(RETURN, NAME, CNAME) \
	MATH_DEFINE_OPERATOR_RET_F32 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_RET_F64 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_RET_F80 (RETURN, NAME, CNAME)	\
	MATH_DEFINE_OPERATOR_RET_F128(RETURN, NAME, CNAME)	\

#define MATH_DECL_REALFUNCTION(NAME, CNAME) \
	MATH_DEFINE_REALFUNCTION_F32 (NAME, CNAME)	\
	MATH_DEFINE_REALFUNCTION_F64 (NAME, CNAME)	\
	MATH_DEFINE_REALFUNCTION_F80 (NAME, CNAME)	\
	MATH_DEFINE_REALFUNCTION_F128(NAME, CNAME)	\

#define MATH_DECL_REALOPERATOR(NAME, CNAME) \
	MATH_DEFINE_REALOPERATOR_F32 (NAME, CNAME)	\
	MATH_DEFINE_REALOPERATOR_F64 (NAME, CNAME)	\
	MATH_DEFINE_REALOPERATOR_F80 (NAME, CNAME)	\
	MATH_DEFINE_REALOPERATOR_F128(NAME, CNAME)	\



#define DEFINE_GENERIC_MATH_FUNCTION(FUNCTION, X) \
	_Generic((X),	\
		t_u8:	 U8_   ##FUNCTION,	\
		t_u16:	 U16_  ##FUNCTION,	\
		t_u32:	 U32_  ##FUNCTION,	\
		t_u64:	 U64_  ##FUNCTION,	\
		t_u128:	 U128_ ##FUNCTION,	\
		t_uint:	 UInt_ ##FUNCTION,	\
		t_s8:	 S8_   ##FUNCTION,	\
		t_s16:	 S16_  ##FUNCTION,	\
		t_s32:	 S32_  ##FUNCTION,	\
		t_s64:	 S64_  ##FUNCTION,	\
		t_s128:	 S128_ ##FUNCTION,	\
		t_sint:	 SInt_ ##FUNCTION,	\
		t_q16:	 Q16_  ##FUNCTION,	\
		t_q32:	 Q32_  ##FUNCTION,	\
		t_q64:	 Q64_  ##FUNCTION,	\
		t_q128:	 Q128_ ##FUNCTION,	\
		t_fixed: Fixed_##FUNCTION,	\
		t_f32:	 F32_  ##FUNCTION,	\
		t_f64:	 F64_  ##FUNCTION,	\
		t_f80:	 F80_  ##FUNCTION,	\
		t_f128:	 F128_ ##FUNCTION,	\
		t_float: Float_##FUNCTION,	\
	)(X)

#define DEFINE_GENERIC_MATH_OPERATOR(FUNCTION, X, Y) \
	_Generic((X),	\
		t_u8:	 U8_   ##FUNCTION,	\
		t_u16:	 U16_  ##FUNCTION,	\
		t_u32:	 U32_  ##FUNCTION,	\
		t_u64:	 U64_  ##FUNCTION,	\
		t_u128:	 U128_ ##FUNCTION,	\
		t_uint:	 UInt_ ##FUNCTION,	\
		t_s8:	 S8_   ##FUNCTION,	\
		t_s16:	 S16_  ##FUNCTION,	\
		t_s32:	 S32_  ##FUNCTION,	\
		t_s64:	 S64_  ##FUNCTION,	\
		t_s128:	 S128_ ##FUNCTION,	\
		t_sint:	 SInt_ ##FUNCTION,	\
		t_q16:	 Q16_  ##FUNCTION,	\
		t_q32:	 Q32_  ##FUNCTION,	\
		t_q64:	 Q64_  ##FUNCTION,	\
		t_q128:	 Q128_ ##FUNCTION,	\
		t_fixed: Fixed_##FUNCTION,	\
		t_f32:	 F32_  ##FUNCTION,	\
		t_f64:	 F64_  ##FUNCTION,	\
		t_f80:	 F80_  ##FUNCTION,	\
		t_f128:	 F128_ ##FUNCTION,	\
		t_float: Float_##FUNCTION,	\
	)(X, Y)



/*
** ************************************************************************** *|
**                          Integer Rounding Operations                       *|
** ************************************************************************** *|
*/

//!@doc Returns the value of `x`, rounded to the nearest integer
/*!
**	- Math: @f$ {round{x}} @f$ or @f$ {\lfloor{x}\rceil} @f$
*/
//!@{
#define						Math_Round(X)		DEFINE_GENERIC_MATH_FUNCTION(Round, X)
#define c_round				Math_Round
//!@}

//!@doc Returns the value of `x`, rounded towards 0
/*!
**	- Math: @f$ {trunc{x}} @f$
*/
//!@{
#define						Math_Trunc(X)	DEFINE_GENERIC_MATH_FUNCTION(Truncate, X)
#define c_trunc				Math_Trunc
#define Math_Truncate		Math_Trunc
//!@}

//!@doc Returns the value of `x`, rounded to the superior integer
/*!
**	- Math: @f$ {floor{x}} @f$ or @f$ {\lfloor{x}\rfloor} @f$
*/
//!@{
#define						Math_Floor(X)		DEFINE_GENERIC_MATH_FUNCTION(Floor, X)
#define c_floor				Math_Floor
//!@}

//!@doc Returns the value of `x`, rounded to the inferior integer
/*!
**	- Math: @f$ {ceil{x}} @f$ or @f$ {\lceil{x}\rceil} @f$
*/
//!@{
#define						Math_Ceil(X)		DEFINE_GENERIC_MATH_FUNCTION(Ceiling, X)
#define c_ceil				Math_Ceil
#define Math_Ceiling		Math_Ceil
//!@}



/*
** ************************************************************************** *|
**                            Basic Math Operators                            *|
** ************************************************************************** *|
*/

//!@doc Returns the addition result of `x` and `y`
/*!
**	- Math: @f$ {x + y} @f$
*/
//!@{
#define						Math_Add(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Add, X, Y)
#define c_add				Math_Add
//!@}

//!@doc Returns the subtraction result of `x` by `y`
/*!
**	- Math: @f$ {x - y} @f$
*/
//!@{
#define						Math_Sub(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Sub, X, Y)
#define c_sub				Math_Sub
#define Math_Subtract		Math_Sub
//!@}

//!@doc Returns the multiplication result of `x` and `y`
/*!
**	- Math: @f$ {x \times y} @f$
*/
//!@{
#define						Math_Mul(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Mul, X, Y)
#define c_mul				Math_Mul
#define Math_Multiply		Math_Mul
//!@}

//!@doc Returns the quotient of euclidian division of `x` by `y`
/*!
**	- Math: @f$ {\frac{x}{y}} @f$
*/
//!@{
#define						Math_Div(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Div, X, Y)
#define c_div				Math_Div
#define Math_Divide			Math_Div
//!@}

//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	- Math: @f$ {x \mod y} @f$
*/
//!@{
#define						Math_Mod(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Mod, X, Y)
#define c_mod				Math_Mod
#define Math_Modulo			Math_Mod
//!@}

/*
** ************************************************************************** *|
**                            Arithmetic Operations                           *|
** ************************************************************************** *|
*/

//!@doc Returns the absolute value of `x` (makes `x` positive)
/*!
**	- Math: @f$ {|x|} @f$
*/
//!@{
#define						Math_Abs(X)		DEFINE_GENERIC_MATH_FUNCTION(Abs, X)
#define c_abs				Math_Abs
#define Math_AbsoluteValue	Math_Abs
//!@}



//!@doc Returns the value of `x` to the power of `y`
/*!
**	- Math: @f$ {x^y} @f$
*/
//!@{
#define						Math_Pow(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Pow, X, Y)
#define c_pow				Math_Pow
#define Math_Power			Math_Pow
//!@}

//!@doc Returns the value of `x` to the power of `n` (integer)
/*!
**	- Math: @f$ {x^n} @f$
*/
//!@{
#define						Math_IntPow(X, N);	DEFINE_GENERIC_MATH_OPERATOR(IntPow, X, N)
#define c_intpow			Math_IntPow
#define Math_IntPower		Math_IntPow
//!@}



//!@doc Returns the square root of `x` (inverse of power of 2)
/*!
**	- Math: @f$ {\sqrt{x}} @f$
*/
//!@{
#define						Math_Root2(X)	DEFINE_GENERIC_MATH_FUNCTION(Root2, X)
#define c_sqrt				Math_Root2
#define Math_SqRt			Math_Root2
#define Math_SquareRoot		Math_Root2
//!@}

//!@doc Returns the cubic root of `x` (inverse of power of 3)
/*!
**	- Math: @f$ {\sqrt[3]{x}} @f$
*/
//!@{
#define						Math_Root3(X)	DEFINE_GENERIC_MATH_FUNCTION(Root3, X)
#define c_cbrt				Math_Root3
#define Math_CbRt			Math_Root3
#define Math_CubeRoot		Math_Root3
//!@}

//!@doc Returns the power-n-ic root of `x` (inverse of power of `n`)
/*!
**	- Math: @f$ {\sqrt[n]{x}} @f$
*/
//!@{
#define						Math_RootN(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(RootN, X, Y)
#define c_nrt				Math_RootN
#define Math_NRt			Math_RootN
#define Math_NRoot			Math_RootN
//!@}

// TODO hypot: {\sqrt{x^2+y^2}}



/*
** ************************************************************************** *|
**                           Exponentiation Operations                        *|
** ************************************************************************** *|
*/

//!@doc Returns the exponential function's value for `x`
/*!
**	- Math: @f$ {e^x} @f$
*/
//!@{
#define							Math_Exp(X)		DEFINE_GENERIC_MATH_FUNCTION(Exp, X)
#define c_exp					Math_Exp
#define Math_Exponential		Math_Exp
//!@}

//!@doc Returns the natural logarithm of `x`
/*!
**	- Math: @f$ {\ln {x}} @f$
*/
//!@{
#define							Math_Ln(X)		DEFINE_GENERIC_MATH_FUNCTION(Ln, X)
#define c_ln					Math_Ln
#define Math_NaturalLogarithm	Math_Ln
//!@}

//!@doc Returns the binary (base-2) logarithm of `x`
/*!
**	- Math: @f$ {\log_{2} {x}} @f$
*/
//!@{
#define							Math_Log2(X)	DEFINE_GENERIC_MATH_FUNCTION(Log2, X)
#define c_lg					Math_Log2
#define c_log2					Math_Log2
#define Math_Logarithm_Base2	Math_Log2
//!@}

//!@doc Returns the decimal (base-10) logarithm of `x`
/*!
**	- Math: @f$ {\log_{10} {x}} @f$
*/
//!@{
#define							Math_Log10(X)	DEFINE_GENERIC_MATH_FUNCTION(Log10, X)
#define c_log					Math_Log10
#define c_log10					Math_Log10
#define Math_Logarithm_Base10	Math_Log10
//!@}

//!@doc Returns the base-`n` logarithm of `x`
/*!
**	- Math: @f$ {\log_{n} {x}} @f$
*/
//!@{
#define							Math_LogN(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(LogN, X, Y)
#define c_logn					Math_LogN
#define Math_Logarithm_BaseN	Math_LogN
//!@}



/*
** ************************************************************************** *|
**                           Trigonometric Operations                         *|
** ************************************************************************** *|
*/

//!@doc Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	- Math: @f$ {\cos {x}} @f$
*/
//!@{
#define						Math_Cos(X)		DEFINE_GENERIC_MATH_FUNCTION(Cos, X)
#define c_cos				Math_Cos
#define Math_Cosine			Math_Cos
//!@}

//!@doc Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	- Math: @f$ {\sin {x}} @f$
*/
//!@{
#define						Math_Sin(X)		DEFINE_GENERIC_MATH_FUNCTION(Sin, X)
#define c_sin				Math_Sin
#define Math_Sine			Math_Sin
//!@}

//!@doc Returns the tangent of `x` (trigonometry tangent line)
/*!
**	- Math: @f$ {\tan {x}} @f$
*/
//!@{
#define						Math_Tan(X)		DEFINE_GENERIC_MATH_FUNCTION(Tan, X)
#define c_tan				Math_Tan
#define Math_Tangent		Math_Tan
//!@}

//!@doc Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	- Math: @f$ {\cos^{-1} {x}} @f$
*/
//!@{
#define						Math_ArcCos(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcCos, X)
#define c_acos				Math_ArcCos
#define Math_Cos_1			Math_ArcCos
#define Math_InvCosine		Math_ArcCos
//!@}

//!@doc Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	- Math: @f$ {\sin^{-1} {x}} @f$
*/
//!@{
#define						Math_ArcSin(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcSin, X)
#define c_asin				Math_ArcSin
#define Math_Sin_1			Math_ArcSin
#define Math_InvSine		Math_ArcSin
//!@}

//!@doc Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	- Math: @f$ {\tan^{-1} {x}} @f$
*/
//!@{
#define						Math_ArcTan(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcTan, X)
#define c_atan				Math_ArcTan
#define Math_Tan_1			Math_ArcTan
#define Math_InvTangent		Math_ArcTan
//!@}



//!@doc Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	- Math: @f$ {\arctan(\frac{y}{x})} @f$, in the range @f$ {[-\pi;+\pi]} @f$
*/
//!@{
#define							Math_ArcTan2(Y, X)	DEFINE_GENERIC_MATH_FUNCTION(ArcTan2, Y, X)
#define c_atan2					Math_ArcTan2
#define Math_ArcTan_YoverX		Math_ArcTan2
#define Math_ArcTangent2		Math_ArcTan2
#define Math_ArcTangent_YoverX	Math_ArcTan2
//!@}



/*
** ************************************************************************** *|
**                           Hyperbolic Trigonometry                          *|
** ************************************************************************** *|
*/

//!@doc Returns the hyperbolic cosine of `x`
/*!
**	- Math: @f$ {\cosh {x}} @f$
*/
//!@{
#define								Math_CosH(X)	DEFINE_GENERIC_MATH_FUNCTION(CosH, X)
#define c_cosh						Math_CosH
#define Math_Cos_H					Math_CosH
#define Math_Cosine_Hyperbolic		Math_CosH
//!@}

//!@doc Returns the hyperbolic sine of `x`
/*!
**	- Math: @f$ {\sinh {x}} @f$
*/
//!@{
#define								Math_SinH(X)	DEFINE_GENERIC_MATH_FUNCTION(SinH, X)
#define c_sinh						Math_SinH
#define Math_Sin_H					Math_SinH
#define Math_Sine_Hyperbolic		Math_SinH
//!@}

//!@doc Returns the hyperbolic tangent of `x`
/*!
**	- Math: @f$ {\tanh {x}} @f$
*/
//!@{
#define								Math_TanH(X)	DEFINE_GENERIC_MATH_FUNCTION(TanH, X)
#define c_tanh						Math_TanH
#define Math_Tan_H					Math_TanH
#define Math_Tangent_Hyperbolic		Math_TanH
//!@}

//!@doc Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	- Math: @f$ {\cosh^{-1} {x}} @f$
*/
//!@{
#define								Math_InvCosH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvCosH, X)
#define c_acosh						Math_InvCosH
#define Math_Cos_1_H				Math_InvCosH
#define Math_InvCosine_Hyperbolic	Math_InvCosH
//!@}

//!@doc Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	- Math: @f$ {\sinh^{-1} {x}} @f$
*/
//!@{
#define								Math_InvSinH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvSinH, X)
#define c_asinh						Math_InvSinH
#define Math_Sin_1_H				Math_InvSinH
#define Math_InvSine_Hyperbolic		Math_InvSinH
//!@}

//!@doc Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	- Math: @f$ {\tanh^{-1} {x}} @f$
*/
//!@{
#define								Math_InvTanH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvTanH, X)
#define c_atanh						Math_InvTanH
#define Math_Tan_1_H				Math_InvTanH
#define Math_InvTangent_Hyperbolic	Math_InvTanH
//!@}



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



/*! @endgroup */
HEADER_END
#endif
