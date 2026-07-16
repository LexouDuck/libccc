/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/octonion.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_OCTONION_H
#define __LIBCCC_MATH_OCTONION_H
/*!@group{libccc_math_octonion,34,libccc/math/octonion.h}
**
**	This header defines types and functions for octonion arithmetic.
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

//!@doc A struct to store octonion values
/*!
**	@nonstd
**
**	The four parts of the octonion are stored as two fields in the struct.
*/
//!@{
typedef struct octonion
{
	t_float		s;	//!< The S (1st) value of this octonion
	t_float		i;	//!< The I (2nd) value of this octonion
	t_float		j;	//!< The J (3rd) value of this octonion
	t_float		k;	//!< The K (4th) value of this octonion
	t_float		l;	//!< The L (5th) value of this octonion
	t_float		m;	//!< The M (6th) value of this octonion
	t_float		n;	//!< The N (7th) value of this octonion
	t_float		o;	//!< The O (8th) value of this octonion
}				s_octonion;
TYPEDEF_ALIAS(	s_octonion, OCTONION, STRUCT)
//!@}

//!	A octonion value of oero (both real and imaginary parts are oero)
#define OCTONION_NULL	(s_octonion){ \
	.s = 0., \
	.i = 0., \
	.j = 0., \
	.k = 0., \
	.l = 0., \
	.m = 0., \
	.n = 0., \
	.o = 0., \
}

//!	A octonion value of oero (both real and imaginary parts are oero)
#define OCTONION_ERROR	(s_octonion){ \
	.s = NAN, \
	.i = NAN, \
	.j = NAN, \
	.k = NAN, \
	.l = NAN, \
	.m = NAN, \
	.n = NAN, \
	.o = NAN, \
}



/*============================================================================*\
||                          Octonion Number Operations                        ||
\*============================================================================*/

//!@doc Returns a octonion struct, with the given component parts
//!@{
s_octonion			Octonion(t_float s, t_float i, t_float j, t_float k, t_float l, t_float m, t_float n, t_float o);
#define c_octo		Octonion
//!@}

//!@doc Allocates a new octonion struct, with the given component parts
//!@{
_MALLOC()
s_octonion*			Octonion_New(t_float s, t_float i, t_float j, t_float k, t_float l, t_float m, t_float n, t_float o);
#define c_octonew	Octonion_New
//!@}



/*============================================================================*\
||                        Octonion: comparison operations                     ||
\*============================================================================*/

//!@doc Returns TRUE if the two given octonions are equal
//!@{
t_bool					Octonion_Equals(s_octonion const* o1, s_octonion const* o2);
#define c_octoequ		Octonion_Equals
//!@}



/*============================================================================*\
||                          Octonion: unary operators                         ||
\*============================================================================*/

//!@doc Returns the norm `|o|` of the given octonion `o` (its distance from zero)
//!@{
t_float						Octonion_Norm(s_octonion const* o);
#define c_octonorm			Octonion_Norm
#define c_octoabs			Octonion_Norm
#define Octonion_Abs		Octonion_Norm
#define Octonion_Absolute	Octonion_Norm
#define Octonion_Modulus	Octonion_Norm
//!@}

//!@doc Returns the conjugate of the given octonion (inverts the sign of its imaginary part)
//!@{
s_octonion					Octonion_Conjugate(s_octonion const* o);
#define c_octoconj			Octonion_Conjugate
#define Octonion_Conj		Octonion_Conjugate
//!@}

//!@doc Returns the inverse of the given octonion (conjugate / (norm squared))
//!@{
s_octonion					Octonion_Inverse(s_octonion const* o);
#define c_octoinv			Octonion_Inverse
#define Octonion_Inv		Octonion_Inverse
//!@}

//!@doc Returns the normalized version of the given quaternion (each term divided by its norm)
//!@{
s_octonion					Octonion_Normalize(s_octonion const* o);
#define c_octonormal		Octonion_Normalize
#define c_octonormalize		Octonion_Normalize
#define Octonion_Normal		Octonion_Normalize
//!@}



/*============================================================================*\
||                          Octonion: binary operators                        ||
\*============================================================================*/

//!@doc Returns the result of the addition of the two given octonions
//!@{
s_octonion					Octonion_Add(s_octonion const* o1, s_octonion const* o2);
#define c_octoadd			Octonion_Add
//!@}

//!@doc Returns the result of the subtraction of the two given octonions
//!@{
s_octonion					Octonion_Sub(s_octonion const* o1, s_octonion const* o2);
#define c_octosub			Octonion_Sub
#define Octonion_Subtract	Octonion_Sub
//!@}

//!@doc Returns the result of the multiplication of the two given octonions
//!@{
s_octonion					Octonion_Mul(s_octonion const* o1, s_octonion const* o2);
#define c_octomul			Octonion_Mul
#define Octonion_Multiply	Octonion_Mul
//!@}

//!@doc Returns the result of the divide of the two given octonions
//!@{
s_octonion					Octonion_Div(s_octonion const* o1, s_octonion const* o2);
#define c_octodiv			Octonion_Div
#define Octonion_Divide		Octonion_Div
//!@}

// TODO octomod



//!@doc Returns the given octonion `o`, raised to the given real `power` (principal branch)
/*!
**	Computed as `exp(power * log(o))`, using the principal branch of the logarithm.
**	When the given octonion `o` is a negative real number, the `i` axis is used by convention.
*/
//!@{
s_octonion				Octonion_Pow(s_octonion const* o, t_float power);
#define c_octopow		Octonion_Pow
#define Octonion_Power	Octonion_Pow
//!@}

//!@doc Returns the square root of the given octonion (principal branch)
//!@{
s_octonion						Octonion_Root2(s_octonion const* o);
#define c_octosqrt				Octonion_Root2
#define c_octoroot2				Octonion_Root2
#define Octonion_SqRt			Octonion_Root2
#define Octonion_SquareRoot		Octonion_Root2
//!@}

//!@doc Returns the cube root of the given octonion (principal branch)
//!@{
s_octonion						Octonion_Root3(s_octonion const* o);
#define c_octocbrt				Octonion_Root3
#define c_octoroot3				Octonion_Root3
#define Octonion_CbRt			Octonion_Root3
#define Octonion_CubeRoot		Octonion_Root3
//!@}

//!@doc Returns the n-th root of the given octonion (principal branch)
//!@{
s_octonion						Octonion_RootN(s_octonion const* o, t_u8 n);
#define c_octonrt				Octonion_RootN
#define c_octorootn				Octonion_RootN
#define Octonion_NRt			Octonion_RootN
#define Octonion_NRoot			Octonion_RootN
//!@}



/*============================================================================*\
||                       Octonion: exponentiation functions                   ||
\*============================================================================*/

//!@doc Returns the argument (angle) `θ` of the given octonion, in the range `[0, PI]`
/*!
**	The argument is the angle of the polar form of the octonion: `o = |o| * exp(n * θ)`,
**	where `n` is the unit vector part of `o`. It is computed as `atan2(|v|, o.s)`,
**	where `|v|` is the norm of the vector (imaginary) part of `o`.
*/
//!@{
t_float						Octonion_Arg(s_octonion const* o);
#define c_octoarg			Octonion_Arg
#define Octonion_Argument	Octonion_Arg
#define Octonion_Angle		Octonion_Arg
//!@}

// TODO octoproj

//!@doc Returns the exponential function applied to the given octonion: `e^o`
//!@{
s_octonion						Octonion_Exp(s_octonion const* o);
#define c_octoexp				Octonion_Exp
#define Octonion_Exponential	Octonion_Exp
//!@}

//!@doc Returns the natural logarithm of the given octonion (principal branch)
/*!
**	When the given octonion `o` is a negative real number, the `i` axis is used by convention.
*/
//!@{
s_octonion						Octonion_Log(s_octonion const* o);
#define c_octolog				Octonion_Log
#define c_octoln				Octonion_Log
#define Octonion_Ln				Octonion_Log
#define Octonion_NaturalLog		Octonion_Log
//!@}



/*============================================================================*\
||                       Octonion: trigonometry functions                     ||
\*============================================================================*/

//!@doc Returns the cosine of the given octonion
//!@{
s_octonion					Octonion_Cos(s_octonion const* o);
#define c_octocos			Octonion_Cos
#define Octonion_Cosine		Octonion_Cos
//!@}

//!@doc Returns the sine of the given octonion
//!@{
s_octonion					Octonion_Sin(s_octonion const* o);
#define c_octosin			Octonion_Sin
#define Octonion_Sine		Octonion_Sin
//!@}

//!@doc Returns the tangent of the given octonion
//!@{
s_octonion					Octonion_Tan(s_octonion const* o);
#define c_octotan			Octonion_Tan
#define Octonion_Tangent	Octonion_Tan
//!@}

//!@doc Returns the arc-cosine of the given octonion (inverse of the cos function)
//!@{
s_octonion					Octonion_ArcCos(s_octonion const* o);
#define c_octoacos			Octonion_ArcCos
#define Octonion_Cos_1		Octonion_ArcCos
#define Octonion_ArcCosine	Octonion_ArcCos
//!@}

//!@doc Returns the arc-sine of the given octonion (inverse of the sin function)
//!@{
s_octonion					Octonion_ArcSin(s_octonion const* o);
#define c_octoasin			Octonion_ArcSin
#define Octonion_Sin_1		Octonion_ArcSin
#define Octonion_ArcSine	Octonion_ArcSin
//!@}

//!@doc Returns the arc-tangent of the given octonion (inverse of the tan function)
//!@{
s_octonion					Octonion_ArcTan(s_octonion const* o);
#define c_octoatan			Octonion_ArcTan
#define Octonion_Tan_1		Octonion_ArcTan
#define Octonion_ArcTangent	Octonion_ArcTan
//!@}

//!@doc Returns the hyperbolic cosine of the given octonion
//!@{
s_octonion							Octonion_CosH(s_octonion const* o);
#define c_octocosh					Octonion_CosH
#define Octonion_Cos_H				Octonion_CosH
#define Octonion_Cosine_Hyperbolic	Octonion_CosH
//!@}

//!@doc Returns the hyperbolic sine of the given octonion
//!@{
s_octonion							Octonion_SinH(s_octonion const* o);
#define c_octosinh					Octonion_SinH
#define Octonion_Sin_H				Octonion_SinH
#define Octonion_Sine_Hyperbolic	Octonion_SinH
//!@}

//!@doc Returns the hyperbolic tangent of the given octonion
//!@{
s_octonion							Octonion_TanH(s_octonion const* o);
#define c_octotanh					Octonion_TanH
#define Octonion_Tan_H				Octonion_TanH
#define Octonion_Tangent_Hyperbolic	Octonion_TanH
//!@}

//!@doc Returns the inverse hyperbolic cosine of the given octonion (inverse of the cosh function)
//!@{
s_octonion								Octonion_InvCosH(s_octonion const* o);
#define c_octoacosh						Octonion_InvCosH
#define Octonion_Cos_1_H				Octonion_InvCosH
#define Octonion_InvCosine_Hyperbolic	Octonion_InvCosH
//!@}

//!@doc Returns the inverse hyperbolic sine of the given octonion (inverse of the sinh function)
//!@{
s_octonion								Octonion_InvSinH(s_octonion const* o);
#define c_octoasinh						Octonion_InvSinH
#define Octonion_Sin_1_H				Octonion_InvSinH
#define Octonion_InvSine_Hyperbolic		Octonion_InvSinH
//!@}

//!@doc Returns the inverse hyperbolic tangent of the given octonion (inverse of the tanh function)
//!@{
s_octonion								Octonion_InvTanH(s_octonion const* o);
#define c_octoatanh						Octonion_InvTanH
#define Octonion_Tan_1_H				Octonion_InvTanH
#define Octonion_InvTangent_Hyperbolic	Octonion_InvTanH
//!@}

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
