/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/quaternion.h                 |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_QUATERNION_H
#define __LIBCCC_MATH_QUATERNION_H
/*!@group{libccc_math_quaternion,34,libccc/math/quaternion.h}
**
**	This header defines types and functions for quaternion arithmetic.
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

//!@doc A struct to store quaternion values
/*!
**	@nonstd
**
**	The four parts of the quaternion are stored as two fields in the struct.
*/
//!@{
typedef struct quaternion
{
	t_float		s;	//!< The S value of this quaternion
	t_float		i;	//!< The I value of this quaternion
	t_float		j;	//!< The J value of this quaternion
	t_float		k;	//!< The K value of this quaternion
}				s_quaternion;
TYPEDEF_ALIAS(	s_quaternion, QUATERNION, STRUCT)
//!@}

//!	A quaternion value of zero (both real and imaginary parts are zero)
#define QUATERNION_NULL	(s_quaternion){ \
	.s = 0., \
	.i = 0., \
	.j = 0., \
	.k = 0., \
}

//! A quaternion used to represent error returns (all terms are NAN)
#define QUATERNION_ERROR	(s_quaternion){ \
	.s = NAN, \
	.i = NAN, \
	.j = NAN, \
	.k = NAN, \
}



/*============================================================================*\
||                         Quaternion Number Operations                       ||
\*============================================================================*/

//!@doc Returns a quaternion struct, with the given component parts
//!@{
s_quaternion			Quaternion(t_float s, t_float i, t_float j, t_float k);
#define c_quat			Quaternion
//!@}

//!@doc Allocates a new quaternion struct, with the given component parts
//!@{
_MALLOC()
s_quaternion*			Quaternion_New(t_float s, t_float i, t_float j, t_float k);
#define c_quatnew		Quaternion_New
//!@}



/*============================================================================*\
||                       Quaternion: comparison operations                    ||
\*============================================================================*/

//!@doc Returns TRUE if the two given quaternions are equal
//!@{
t_bool					Quaternion_Equals(s_quaternion const* q1, s_quaternion const* q2);
#define c_quatequ		Quaternion_Equals
//!@}



/*============================================================================*\
||                         Quaternion: unary operators                        ||
\*============================================================================*/

//!@doc Returns the norm `|q|` of the given quaternion `q` (its distance from zero)
//!@{
t_float						Quaternion_Norm(s_quaternion const* q);
#define c_quatnorm			Quaternion_Norm
#define c_quatabs			Quaternion_Norm
#define Quaternion_Abs		Quaternion_Norm
#define Quaternion_Absolute	Quaternion_Norm
#define Quaternion_Modulus	Quaternion_Norm
//!@}

//!@doc Returns the conjugate of the given quaternion (inverts the sign of its imaginary part)
//!@{
s_quaternion				Quaternion_Conjugate(s_quaternion const* q);
#define c_quatconj			Quaternion_Conjugate
#define Quaternion_Conj		Quaternion_Conjugate
//!@}

//!@doc Returns the inverse of the given quaternion (conjugate / (norm squared))
//!@{
s_quaternion				Quaternion_Inverse(s_quaternion const* q);
#define c_quatinv			Quaternion_Inverse
#define Quaternion_Inv		Quaternion_Inverse
//!@}

//!@doc Returns the normalized version of the given quaternion (each term divided by its norm)
//!@{
s_quaternion				Quaternion_Normalize(s_quaternion const* q);
#define c_quatnormal		Quaternion_Normalize
#define c_quatnormalize		Quaternion_Normalize
#define Quaternion_Normal	Quaternion_Normalize
//!@}



/*============================================================================*\
||                         Quaternion: binary operators                       ||
\*============================================================================*/

//!@doc Returns the result of the addition of the two given quaternions
//!@{
s_quaternion				Quaternion_Add(s_quaternion const* q1, s_quaternion const* q2);
#define c_quatadd			Quaternion_Add
//!@}

//!@doc Returns the result of the subtraction of the two given quaternions
//!@{
s_quaternion				Quaternion_Sub(s_quaternion const* q1, s_quaternion const* q2);
#define c_quatsub			Quaternion_Sub
#define Quaternion_Subtract	Quaternion_Sub
//!@}

//!@doc Returns the result of the multiplication of the two given quaternions
//!@{
s_quaternion				Quaternion_Mul(s_quaternion const* q1, s_quaternion const* q2);
#define c_quatmul			Quaternion_Mul
#define Quaternion_Multiply	Quaternion_Mul
//!@}

//!@doc Returns the result of the divide of the two given quaternions
//!@{
s_quaternion				Quaternion_Div(s_quaternion const* q1, s_quaternion const* q2);
#define c_quatdiv			Quaternion_Div
#define Quaternion_Divide	Quaternion_Div
//!@}

// TODO quatmod



// TODO quatpow
// TODO quatsqrt
// TODO quatcbrt
// TODO quatnrt



/*============================================================================*\
||                      Quaternion: exponentiation functions                  ||
\*============================================================================*/

// TODO quatarg
// TODO quatproj

// TODO quatexp
// TODO quatlog



/*============================================================================*\
||                      Quaternion: trigonometry functions                    ||
\*============================================================================*/

// TODO quatcos
// TODO quatsin
// TODO quattan
// TODO quatacos
// TODO quatasin
// TODO quatatan

// TODO quatcosh
// TODO quatsinh
// TODO quattanh
// TODO quatacosh
// TODO quatasinh
// TODO quatatanh

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
