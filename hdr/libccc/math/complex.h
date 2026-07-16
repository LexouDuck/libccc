/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/complex.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_COMPLEX_H
#define __LIBCCC_MATH_COMPLEX_H
/*!@group{libccc_math_complex,34,libccc/math/complex.h}
**
**	This header defines types and functions for complex number arithmetic.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/complex}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/tgmath}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

#if LIBCONFIG_USE_STD_COMPLEX

	#if (!defined(__STDC__) || (__STDC_VERSION__ < __STDC_VERSION_C99__))
		#error "C ISO standard complex/imaginary types are not available for this C standard: "__STDC_VERSION__"L"
	#endif

	#ifndef __NOSTD__
		#include <complex.h>
	#else
		#error "Cannot use standard fixed-point library, __NOSTD__ macro is defined"
	#endif

	//!@doc @isostd{C99,https://en.cppreference.com/w/c/numeric/complex/complex}
	/*!
	**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/complex}
	**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/imaginary}
	**
	**	The two parts of the complex number are stored as two fields in the struct.
	*/
	//!@{
	typedef _Complex	s_complex;
	TYPEDEF_ALIAS(		s_complex, COMPLEX, STRUCT)
	//!@}

	//!	A complex number value of zero (both real and imaginary parts are zero)
	#define COMPLEX_NULL	(0.0 + 0.0*I)

	//! A complex number used to represent error returns (all terms are NAN)
	#define COMPLEX_ERROR	(NAN + NAN*I)

#else

	//!@doc A struct to store complex/imaginary number values
	/*!
	**	@nonstd
	**
	**	The two parts of the complex number are stored as two fields in the struct.
	*/
	//!@{
	typedef struct complex
	{
		t_float		re;	//!< The "real" part of this complex number
		t_float		im;	//!< The "imaginary" part of this complex number
	}				s_complex;
	TYPEDEF_ALIAS(	s_complex, COMPLEX, STRUCT)
	//!@}

	//!	A complex number value of zero (both real and imaginary parts are zero)
	#define COMPLEX_NULL	(s_complex){ \
		.re = 0., \
		.im = 0., \
	}

	//! A complex number used to represent error returns (all terms are NAN)
	#define COMPLEX_ERROR	(s_complex){ \
		.re = NAN, \
		.im = NAN, \
	}

#endif



/*============================================================================*\
||                          Complex Number Operations                         ||
\*============================================================================*/

//!@doc Returns a complex number struct, with the given 're' real part and 'im' imaginary part
//!@{
s_complex				Complex(t_float re, t_float im);
#define c_cplx			Complex
//!@}

//!@doc Allocates a new complex number struct, with the given 're' real part and 'im' imaginary part
//!@{
_MALLOC()
s_complex*				Complex_New(t_float re, t_float im);
#define c_cplxnew		Complex_New
//!@}



/*============================================================================*\
||                        Complex: comparison operations                      ||
\*============================================================================*/

//!@doc Returns TRUE if the two given complex numbers are equal
//!@{
t_bool					Complex_Equals(s_complex const* z1, s_complex const* z2);
#define c_cplxequ		Complex_Equals
//!@}



/*============================================================================*\
||                          Complex: unary operators                          ||
\*============================================================================*/

//!@doc Returns the norm `|z|` of the given complex number `z` (its distance from zero)
//!@{
t_float						Complex_Norm(s_complex const* z);
#define c_cplxnorm			Complex_Norm
#define c_cplxabs			Complex_Norm
#define Complex_Abs			Complex_Norm
#define Complex_Absolute	Complex_Norm
#define Complex_Modulus		Complex_Norm
//!@}

//!@doc Returns the conjugate of the given complex number (inverts the sign of its imaginary part)
//!@{
s_complex					Complex_Conjugate(s_complex const* z);
#define c_cplxconj			Complex_Conjugate
#define Complex_Conj		Complex_Conjugate
//!@}

//!@doc Returns the inverse of the given complex number (conjugate / (norm squared))
//!@{
s_complex					Complex_Inverse(s_complex const* z);
#define c_cplxinv			Complex_Inverse
#define Complex_Inv			Complex_Inverse
//!@}

//!@doc Returns the normalized version of the given complex number (each term divided by its norm)
//!@{
s_complex					Complex_Normalize(s_complex const* z);
#define c_cplxnormal		Complex_Normalize
#define c_cplxnormalize		Complex_Normalize
#define Complex_Normal		Complex_Normalize
//!@}



/*============================================================================*\
||                          Complex: binary operators                         ||
\*============================================================================*/

//!@doc Returns the result of the addition of the two given complex numbers
//!@{
s_complex					Complex_Add(s_complex const* z1, s_complex const* z2);
#define c_cplxadd			Complex_Add
//!@}

//!@doc Returns the result of the subtraction of the two given complex numbers
//!@{
s_complex					Complex_Sub(s_complex const* z1, s_complex const* z2);
#define c_cplxsub			Complex_Sub
#define Complex_Subtract	Complex_Sub
//!@}

//!@doc Returns the result of the multiplication of the two given complex numbers
//!@{
s_complex					Complex_Mul(s_complex const* z1, s_complex const* z2);
#define c_cplxmul			Complex_Mul
#define Complex_Multiply	Complex_Mul
//!@}

//!@doc Returns the result of the divide of the two given complex numbers
//!@{
s_complex					Complex_Div(s_complex const* z1, s_complex const* z2);
#define c_cplxdiv			Complex_Div
#define Complex_Divide		Complex_Div
//!@}

// TODO cplxmod



//!@doc Returns the given complex number `z`, raised to the given real `power` (principal branch)
/*!
**	Computed as `exp(power * log(z))`, using the principal branch of the logarithm.
*/
//!@{
s_complex				Complex_Pow(s_complex const* z, t_float power);
#define c_cplxpow		Complex_Pow
#define Complex_Power	Complex_Pow
//!@}

//!@doc Returns the square root of the given complex number (principal branch)
//!@{
s_complex						Complex_Root2(s_complex const* z);
#define c_cplxsqrt				Complex_Root2
#define c_cplxroot2				Complex_Root2
#define Complex_SqRt			Complex_Root2
#define Complex_SquareRoot		Complex_Root2
//!@}

//!@doc Returns the cube root of the given complex number (principal branch)
//!@{
s_complex						Complex_Root3(s_complex const* z);
#define c_cplxcbrt				Complex_Root3
#define c_cplxroot3				Complex_Root3
#define Complex_CbRt			Complex_Root3
#define Complex_CubeRoot		Complex_Root3
//!@}

//!@doc Returns the n-th root of the given complex number (principal branch)
//!@{
s_complex						Complex_RootN(s_complex const* z, t_u8 n);
#define c_cplxnrt				Complex_RootN
#define c_cplxrootn				Complex_RootN
#define Complex_NRt				Complex_RootN
#define Complex_NRoot			Complex_RootN
//!@}



/*============================================================================*\
||                       Complex: exponentiation functions                    ||
\*============================================================================*/

//!@doc Returns the argument (angle) `θ` of the given complex number, in the range `(-PI, +PI]`
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/carg}
**
**	The argument is the angle of the polar form of the complex number: `z = |z| * exp(i * θ)`.
**	It is computed as `atan2(z.im, z.re)` (so, the argument of zero is zero).
*/
//!@{
t_float						Complex_Arg(s_complex const* z);
#define c_cplxarg			Complex_Arg
#define Complex_Argument	Complex_Arg
#define Complex_Angle		Complex_Arg
//!@}

//!@doc Returns the projection of the given complex number onto the Riemann sphere
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/cproj}
**
**	The result is equal to `z`, unless one of its parts is infinite, in which case
**	the result is `+INFINITY` for the real part, and `±0` for the imaginary part
**	(preserving the sign of the imaginary part of `z`).
*/
//!@{
s_complex						Complex_Proj(s_complex const* z);
#define c_cplxproj				Complex_Proj
#define Complex_Projection		Complex_Proj
//!@}

//!@doc Returns the exponential function applied to the given complex number: `e^z`
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/cexp}
*/
//!@{
s_complex						Complex_Exp(s_complex const* z);
#define c_cplxexp				Complex_Exp
#define Complex_Exponential		Complex_Exp
//!@}

//!@doc Returns the natural logarithm of the given complex number (principal branch)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/clog}
*/
//!@{
s_complex						Complex_Log(s_complex const* z);
#define c_cplxlog				Complex_Log
#define c_cplxln				Complex_Log
#define Complex_Ln				Complex_Log
#define Complex_NaturalLog		Complex_Log
//!@}



/*============================================================================*\
||                       Complex: trigonometry functions                      ||
\*============================================================================*/

//!@doc Returns the cosine of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/ccos}
*/
//!@{
s_complex					Complex_Cos(s_complex const* z);
#define c_cplxcos			Complex_Cos
#define Complex_Cosine		Complex_Cos
//!@}

//!@doc Returns the sine of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/csin}
*/
//!@{
s_complex					Complex_Sin(s_complex const* z);
#define c_cplxsin			Complex_Sin
#define Complex_Sine		Complex_Sin
//!@}

//!@doc Returns the tangent of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/ctan}
*/
//!@{
s_complex					Complex_Tan(s_complex const* z);
#define c_cplxtan			Complex_Tan
#define Complex_Tangent		Complex_Tan
//!@}

//!@doc Returns the arc-cosine of the given complex number (inverse of the cos function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/cacos}
*/
//!@{
s_complex					Complex_ArcCos(s_complex const* z);
#define c_cplxacos			Complex_ArcCos
#define Complex_Cos_1		Complex_ArcCos
#define Complex_ArcCosine	Complex_ArcCos
//!@}

//!@doc Returns the arc-sine of the given complex number (inverse of the sin function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/casin}
*/
//!@{
s_complex					Complex_ArcSin(s_complex const* z);
#define c_cplxasin			Complex_ArcSin
#define Complex_Sin_1		Complex_ArcSin
#define Complex_ArcSine		Complex_ArcSin
//!@}

//!@doc Returns the arc-tangent of the given complex number (inverse of the tan function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/catan}
*/
//!@{
s_complex					Complex_ArcTan(s_complex const* z);
#define c_cplxatan			Complex_ArcTan
#define Complex_Tan_1		Complex_ArcTan
#define Complex_ArcTangent	Complex_ArcTan
//!@}

//!@doc Returns the hyperbolic cosine of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/ccosh}
*/
//!@{
s_complex							Complex_CosH(s_complex const* z);
#define c_cplxcosh					Complex_CosH
#define Complex_Cos_H				Complex_CosH
#define Complex_Cosine_Hyperbolic	Complex_CosH
//!@}

//!@doc Returns the hyperbolic sine of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/csinh}
*/
//!@{
s_complex							Complex_SinH(s_complex const* z);
#define c_cplxsinh					Complex_SinH
#define Complex_Sin_H				Complex_SinH
#define Complex_Sine_Hyperbolic		Complex_SinH
//!@}

//!@doc Returns the hyperbolic tangent of the given complex number
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/ctanh}
*/
//!@{
s_complex							Complex_TanH(s_complex const* z);
#define c_cplxtanh					Complex_TanH
#define Complex_Tan_H				Complex_TanH
#define Complex_Tangent_Hyperbolic	Complex_TanH
//!@}

//!@doc Returns the inverse hyperbolic cosine of the given complex number (inverse of the cosh function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/cacosh}
*/
//!@{
s_complex							Complex_InvCosH(s_complex const* z);
#define c_cplxacosh					Complex_InvCosH
#define Complex_Cos_1_H				Complex_InvCosH
#define Complex_InvCosine_Hyperbolic	Complex_InvCosH
//!@}

//!@doc Returns the inverse hyperbolic sine of the given complex number (inverse of the sinh function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/casinh}
*/
//!@{
s_complex							Complex_InvSinH(s_complex const* z);
#define c_cplxasinh					Complex_InvSinH
#define Complex_Sin_1_H				Complex_InvSinH
#define Complex_InvSine_Hyperbolic	Complex_InvSinH
//!@}

//!@doc Returns the inverse hyperbolic tangent of the given complex number (inverse of the tanh function)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/catanh}
*/
//!@{
s_complex							Complex_InvTanH(s_complex const* z);
#define c_cplxatanh					Complex_InvTanH
#define Complex_Tan_1_H				Complex_InvTanH
#define Complex_InvTangent_Hyperbolic	Complex_InvTanH
//!@}

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
