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
/*!@group{libccc_math_complex}
**
**	This header defines useful algebra and calculus types, and functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/complex}
**	@isostd{C,https://en.cppreference.com/w/c/numeric/tgmath}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#if LIBCONFIG_USE_STD_COMPLEX

	#if (!defined(__STDC__) || (__STDC_VERSION__ < __STDC_VERSION_C99__))
		#error "C ISO standard complex/imaginary types are not available for this C standard: "__STDC_VERSION__"L"
	#endif

	#ifndef __NOSTD__
		#include <complex.h>
	#else
		#error "Cannot use standard fixed-point library, __NOSTD__ macro is defined"
	#endif

	typedef _Complex	s_complex;
	TYPEDEF_ALIAS(		s_complex, COMPLEX, STRUCT)

	//!	A complex number value of zero (both real and imaginary parts are zero)
	/*!
	**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/complex}
	**	@isostd{C99,https://en.cppreference.com/w/c/numeric/complex/imaginary}
	**
	**	The two parts of the complex number are stored as two fields in the struct.
	*/
	#define COMPLEX_NULL	(0.0 + 0.0*I)

#else

	//! A struct to store complex/imaginary number values
	/*!
	**	@nonstd
	**
	**	The two parts of the complex number are stored as two fields in the struct.
	*/
	typedef struct complex
	{
		t_float		re;		//!< The "real" part of this complex number
		t_float		im;		//!< The "imaginary" part of this complex number
	}				s_complex;
	TYPEDEF_ALIAS(	s_complex, COMPLEX, STRUCT)

	//!	A complex number value of zero (both real and imaginary parts are zero)
	#define COMPLEX_NULL	(s_complex){ .re = 0, .im = 0 }

#endif



/*
** ************************************************************************** *|
**                          Complex Number Operations                         *|
** ************************************************************************** *|
*/

//! Returns a complex number struct, with the given 're' real part and 'im' imaginary part
s_complex				Complex(t_float re, t_float im);
#define c_cplx			Complex

//! Allocates a new complex number struct, with the given 're' real part and 'im' imaginary part
_MALLOC()
s_complex*				Complex_New(t_float re, t_float im);
#define c_cplxnew		Complex_New



/*
** ************************************************************************** *|
**                        Complex: comparison operations                      *|
** ************************************************************************** *|
*/

//! Returns TRUE if the two given complex numbers are equal
t_bool					Complex_Equals(s_complex const* z1, s_complex const* z2);
#define c_cplxequ		Complex_Equals



/*
** ************************************************************************** *|
**                          Complex: unary operators                          *|
** ************************************************************************** *|
*/

//! Returns the absolute value |z| of the given complex number 'z' (its distance from zero)
t_float					Complex_Abs(s_complex const* z1);
#define c_cplxabs		Complex_Abs
#define Complex_Modulus	Complex_Abs

//! Returns the conjugate of the given complex number (inverts the sign of its imaginary part)
s_complex				Complex_Conjugate(s_complex const* z1);
#define c_cplxconj		Complex_Conjugate
#define Complex_Conj	Complex_Conjugate



/*
** ************************************************************************** *|
**                          Complex: binary operators                         *|
** ************************************************************************** *|
*/

//! Returns the result of the addition of the two given complex numbers
s_complex					Complex_Add(s_complex const* z1, s_complex const* z2);
#define c_cplxadd			Complex_Add

//! Returns the result of the subtraction of the two given complex numbers
s_complex					Complex_Sub(s_complex const* z1, s_complex const* z2);
#define c_cplxsub			Complex_Sub
#define Complex_Subtract	Complex_Sub

//! Returns the result of the multiplication of the two given complex numbers
s_complex					Complex_Mul(s_complex const* z1, s_complex const* z2);
#define c_cplxmul			Complex_Mul
#define Complex_Multiply	Complex_Mul

//! Returns the result of the divide of the two given complex numbers
s_complex					Complex_Div(s_complex const* z1, s_complex const* z2);
#define c_cplxdiv			Complex_Div
#define Complex_Divide		Complex_Div

// TODO cplxmod



//! Returns the given complex number, to the power of 'n'
s_complex					Complex_Pow(s_complex const* z, t_u8 n);
#define c_cplxpow			Complex_Pow
#define Complex_Power		Complex_Pow

// TODO cplxsqrt
// TODO cplxcbrt
// TODO cplxnrt



/*
** ************************************************************************** *|
**                       Complex: exponentiation functions                    *|
** ************************************************************************** *|
*/

// TODO cplxarg
// TODO cplxproj

// TODO cplxexp
// TODO cplxlog



/*
** ************************************************************************** *|
**                       Complex: trigonometry functions                      *|
** ************************************************************************** *|
*/

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



/*
** ************************************************************************** *|
**                            Quaternion Operations                           *|
** ************************************************************************** *|
*/

//! A struct for storing quaternions
typedef struct quaternion
{
	t_float		s;		//!< The S value of this quaternion
	t_float		i;		//!< The I value of this quaternion
	t_float		j;		//!< The J value of this quaternion
	t_float		k;		//!< The K value of this quaternion
}					s_quaternion;
TYPEDEF_ALIAS(		s_quaternion, QUATERNION, STRUCT)



// TODO define, implement, document



/*! @endgroup */
HEADER_END
#endif
