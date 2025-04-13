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



// TODO octopow
// TODO octosqrt
// TODO octocbrt
// TODO octonrt



/*============================================================================*\
||                       Octonion: exponentiation functions                   ||
\*============================================================================*/

// TODO octoarg
// TODO octoproj

// TODO octoexp
// TODO octolog



/*============================================================================*\
||                       Octonion: trigonometry functions                     ||
\*============================================================================*/

// TODO octocos
// TODO octosin
// TODO octotan
// TODO octoacos
// TODO octoasin
// TODO octoatan

// TODO octocosh
// TODO octosinh
// TODO octotanh
// TODO octoacosh
// TODO octoasinh
// TODO octoatanh

// TODO add polar form operations



/*! @endgroup */
HEADER_END
#endif
