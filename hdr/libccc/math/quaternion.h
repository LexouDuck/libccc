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



//!@doc Returns the given quaternion `q`, raised to the given real `power` (principal branch)
/*!
**	Computed as `exp(power * log(q))`, using the principal branch of the logarithm.
**	When the given quaternion `q` is a negative real number, the `i` axis is used by convention.
*/
//!@{
s_quaternion				Quaternion_Pow(s_quaternion const* q, t_float power);
#define c_quatpow			Quaternion_Pow
#define Quaternion_Power	Quaternion_Pow
//!@}

//!@doc Returns the square root of the given quaternion (principal branch)
//!@{
s_quaternion					Quaternion_Root2(s_quaternion const* q);
#define c_quatsqrt				Quaternion_Root2
#define c_quatroot2				Quaternion_Root2
#define Quaternion_SqRt			Quaternion_Root2
#define Quaternion_SquareRoot	Quaternion_Root2
//!@}

//!@doc Returns the cube root of the given quaternion (principal branch)
//!@{
s_quaternion					Quaternion_Root3(s_quaternion const* q);
#define c_quatcbrt				Quaternion_Root3
#define c_quatroot3				Quaternion_Root3
#define Quaternion_CbRt			Quaternion_Root3
#define Quaternion_CubeRoot		Quaternion_Root3
//!@}

//!@doc Returns the n-th root of the given quaternion (principal branch)
//!@{
s_quaternion					Quaternion_RootN(s_quaternion const* q, t_u8 n);
#define c_quatnrt				Quaternion_RootN
#define c_quatrootn				Quaternion_RootN
#define Quaternion_NRt			Quaternion_RootN
#define Quaternion_NRoot		Quaternion_RootN
//!@}



/*============================================================================*\
||                      Quaternion: exponentiation functions                  ||
\*============================================================================*/

//!@doc Returns the argument (angle) `θ` of the given quaternion, in the range `[0, PI]`
/*!
**	The argument is the angle of the polar form of the quaternion: `q = |q| * exp(n * θ)`,
**	where `n` is the unit vector part of `q`. It is computed as `atan2(|v|, q.s)`,
**	where `|v|` is the norm of the vector (imaginary) part of `q`.
*/
//!@{
t_float						Quaternion_Arg(s_quaternion const* q);
#define c_quatarg			Quaternion_Arg
#define Quaternion_Argument	Quaternion_Arg
#define Quaternion_Angle	Quaternion_Arg
//!@}

// TODO quatproj

//!@doc Returns the exponential function applied to the given quaternion: `e^q`
//!@{
s_quaternion					Quaternion_Exp(s_quaternion const* q);
#define c_quatexp				Quaternion_Exp
#define Quaternion_Exponential	Quaternion_Exp
//!@}

//!@doc Returns the natural logarithm of the given quaternion (principal branch)
/*!
**	When the given quaternion `q` is a negative real number, the `i` axis is used by convention.
*/
//!@{
s_quaternion					Quaternion_Log(s_quaternion const* q);
#define c_quatlog				Quaternion_Log
#define c_quatln				Quaternion_Log
#define Quaternion_Ln			Quaternion_Log
#define Quaternion_NaturalLog	Quaternion_Log
//!@}



/*============================================================================*\
||                      Quaternion: trigonometry functions                    ||
\*============================================================================*/

//!@doc Returns the cosine of the given quaternion
//!@{
s_quaternion				Quaternion_Cos(s_quaternion const* q);
#define c_quatcos			Quaternion_Cos
#define Quaternion_Cosine	Quaternion_Cos
//!@}

//!@doc Returns the sine of the given quaternion
//!@{
s_quaternion				Quaternion_Sin(s_quaternion const* q);
#define c_quatsin			Quaternion_Sin
#define Quaternion_Sine		Quaternion_Sin
//!@}

//!@doc Returns the tangent of the given quaternion
//!@{
s_quaternion				Quaternion_Tan(s_quaternion const* q);
#define c_quattan			Quaternion_Tan
#define Quaternion_Tangent	Quaternion_Tan
//!@}

//!@doc Returns the arc-cosine of the given quaternion (inverse of the cos function)
//!@{
s_quaternion					Quaternion_ArcCos(s_quaternion const* q);
#define c_quatacos				Quaternion_ArcCos
#define Quaternion_Cos_1		Quaternion_ArcCos
#define Quaternion_ArcCosine	Quaternion_ArcCos
//!@}

//!@doc Returns the arc-sine of the given quaternion (inverse of the sin function)
//!@{
s_quaternion					Quaternion_ArcSin(s_quaternion const* q);
#define c_quatasin				Quaternion_ArcSin
#define Quaternion_Sin_1		Quaternion_ArcSin
#define Quaternion_ArcSine		Quaternion_ArcSin
//!@}

//!@doc Returns the arc-tangent of the given quaternion (inverse of the tan function)
//!@{
s_quaternion					Quaternion_ArcTan(s_quaternion const* q);
#define c_quatatan				Quaternion_ArcTan
#define Quaternion_Tan_1		Quaternion_ArcTan
#define Quaternion_ArcTangent	Quaternion_ArcTan
//!@}

//!@doc Returns the hyperbolic cosine of the given quaternion
//!@{
s_quaternion							Quaternion_CosH(s_quaternion const* q);
#define c_quatcosh						Quaternion_CosH
#define Quaternion_Cos_H				Quaternion_CosH
#define Quaternion_Cosine_Hyperbolic	Quaternion_CosH
//!@}

//!@doc Returns the hyperbolic sine of the given quaternion
//!@{
s_quaternion							Quaternion_SinH(s_quaternion const* q);
#define c_quatsinh						Quaternion_SinH
#define Quaternion_Sin_H				Quaternion_SinH
#define Quaternion_Sine_Hyperbolic		Quaternion_SinH
//!@}

//!@doc Returns the hyperbolic tangent of the given quaternion
//!@{
s_quaternion							Quaternion_TanH(s_quaternion const* q);
#define c_quattanh						Quaternion_TanH
#define Quaternion_Tan_H				Quaternion_TanH
#define Quaternion_Tangent_Hyperbolic	Quaternion_TanH
//!@}

//!@doc Returns the inverse hyperbolic cosine of the given quaternion (inverse of the cosh function)
//!@{
s_quaternion							Quaternion_InvCosH(s_quaternion const* q);
#define c_quatacosh						Quaternion_InvCosH
#define Quaternion_Cos_1_H				Quaternion_InvCosH
#define Quaternion_InvCosine_Hyperbolic	Quaternion_InvCosH
//!@}

//!@doc Returns the inverse hyperbolic sine of the given quaternion (inverse of the sinh function)
//!@{
s_quaternion							Quaternion_InvSinH(s_quaternion const* q);
#define c_quatasinh						Quaternion_InvSinH
#define Quaternion_Sin_1_H				Quaternion_InvSinH
#define Quaternion_InvSine_Hyperbolic	Quaternion_InvSinH
//!@}

//!@doc Returns the inverse hyperbolic tangent of the given quaternion (inverse of the tanh function)
//!@{
s_quaternion								Quaternion_InvTanH(s_quaternion const* q);
#define c_quatatanh							Quaternion_InvTanH
#define Quaternion_Tan_1_H					Quaternion_InvTanH
#define Quaternion_InvTangent_Hyperbolic	Quaternion_InvTanH
//!@}

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
