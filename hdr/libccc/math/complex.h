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



// TODO cplxpow
// TODO cplxsqrt
// TODO cplxcbrt
// TODO cplxnrt



/*============================================================================*\
||                       Complex: exponentiation functions                    ||
\*============================================================================*/

// TODO cplxarg
// TODO cplxproj

// TODO cplxexp
// TODO cplxlog



/*============================================================================*\
||                       Complex: trigonometry functions                      ||
\*============================================================================*/

// TODO cplxcos
// TODO cplxsin
// TODO cplxtan
// TODO cplxacos
// TODO cplxasin
// TODO cplxatan

// TODO cplxcosh
// TODO cplxsinh
// TODO cplxtanh
// TODO cplxacosh
// TODO cplxasinh
// TODO cplxatanh

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
