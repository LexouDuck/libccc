/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/constants.h                  |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_CONSTANTS_H
#define __LIBCCC_MATH_CONSTANTS_H
/*!@group{libccc_math_constants}
** @{
**	This header defines the common standard math constants and macro defines.
**
**	@isostd{https://en.cppreference.com/w/c/numeric/math}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Various relevant mathematical constants.
**	Many of these constants are used to speed up the fast-approximate versions
**	of some fundamental algorithms and math functions.
*/

//! Alias for #DIV_PI_4
#define QUARTER_PI	DIV_PI_4
//! Alias for #DIV_PI_2
#define HALF_PI		DIV_PI_2

//! Mathematical constant: Quarter of pi (`PI / 4`)
/*!
**	- Math: @f$ {\frac{\pi}{4}} @f$
**	- Decimal: TODO
*/
#define DIV_PI_4		(0x1.921FB54442D18p-1)

//! Mathematical constant: Half of pi (`PI / 2`)
/*!
**	- Math: @f$ {\frac{\pi}{2}} @f$
**	- Decimal: TODO
*/
#define DIV_PI_2		(0x1.921FB54442D18p+0)

//! Mathematical constant: circle periphery from diameter, pi (`TAU / 2`)
/*!
**	- Math: @f$ {\pi} @f$
**	- Decimal: `3.141592653589793238462643383279502884197169399375105820974...`
*/
#define PI				(0x1.921FB54442D18p+1)

//! Mathematical constant: circle periphery from radius, tau (`2 * PI`)
/*!
**	- Math: @f$ {2\pi} @f$
**	- Decimal: `6.283185307179586476925286766559005768394338798750211641949...`
*/
#define TAU 			(0x1.921FB54442D18p+2)

//! Mathematical constant: Inverse of pi (`1 / pi`)
/*!
**	- Math: @f$ {\frac{1}{\pi}} @f$
**	- Decimal: `0.318309886183790671537767526745028724068919291480912897495...`
*/
#define INV_PI			(0x1.45F306DC9C883p-2)

//! Mathematical constant: Inverse of tau (`1 / tau`)
/*!
**	- Math: @f$ {\frac{1}{2\pi}} @f$
**	- Decimal: `0.159154943091895335768883763372514362034459645740456448747...`
*/
#define INV_TAU			(0x1.45F306DC9C883p-3)

// TODO INV_SQRT_PI
// TODO INV_SQRT_TAU



//! Mathematical constant: The exponential number, e (`exp(1)`), Euler's number
/*!
**	- Math: @f$ {e} @f$
**	- Decimal: `2.718281828459045235360287471352662497757247093699959574966...`
*/
#define E				(0x1.5BF0A8B145769p+1)

//! Mathematical constant: The natural logarithm of 2 (`ln(2)`)
/*!
**	- Math: @f$ {\ln {2}} @f$
**	- Decimal: `0.693147180559945309417232121458176568075500134360255254120...`
*/
#define LN_2			(0x1.62E42FEFA39EFp-1)

//! Mathematical constant: The natural logarithm of 10 (`ln(10)`)
/*!
**	- Math: @f$ {\ln {10}} @f$
**	- Decimal: `2.302585092994045684017991454684364207601101488628772976033...`
*/
#define LN_10			(0x1.26BB1BBB55516p+1)



//! Mathematical constant: The square root of 2 (`sqrt(2)`), the Pythagoras constant
/*!
**	- Math: @f$ {\sqrt{2}} @f$
**	- Decimal: `1.414213562373095048801688724209698078569671875376948073176...`
*/
#define SQRT_2			(0x1.6A09E667F3BCDp+0)

//! Mathematical constant: The inverse square root of 2 (`1 / sqrt(2)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{2}}} @f$
**	- Decimal: `0.7071067811865475244008443621048490392848359376884740365883398689...`
*/
#define INV_SQRT_2		(0x1.6A09E667F3BCDp-1)

//! Mathematical constant: The square root of 3 (`sqrt(3)`), the Theodorus constant
/*!
**	- Math: @f$ {\sqrt{3}} @f$
**	- Decimal: `1.732050807568877293527446341505872366942805253810380628055...`
*/
#define SQRT_3			(0x1.BB67AE8584CAAp+0)

//! Mathematical constant: The inverse square root of 3 (`1 / sqrt(3)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{3}}} @f$
**	- Decimal: `0.5773502691896257645091487805019574556476017512701268760186023264...`
*/
#define INV_SQRT_3		(0x1.279A74590331Cp-1)

//! Mathematical constant: The square root of 5 (`sqrt(5)`)
/*!
**	- Math: @f$ {\sqrt{5}} @f$
**	- Decimal: `2.236067977499789696409173668731276235440618359611525724270...`
*/
#define SQRT_5			(0x1.1E3779B97F4A7p+1)

//! Mathematical constant: The inverse square root of 5 (`1 / sqrt(5)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{5}}} @f$
**	- Decimal: `0.4472135954999579392818347337462552470881236719223051448541794490...`
*/
#define INV_SQRT_5		(0x1.C9F25C5BFEDD9p-2)



//! Mathematical constant: Phi, (`(1/2) * (1 + sqrt(5))`), the golden ratio
/*!
**	- Math: @f$ {\frac{1}{2}(1 + \sqrt{5})} @f$
**	- Decimal: `1.6180339887498948482045868343656381177203091798057628621354486227...`
*/
#define PHI				(1.6180339887498949025257388711906969547271728515625e0)



//! Mathematical constant: Cube root of 2 (`cbrt(2)`), the Delian constant
/*!
**	- Math: @f$ {\sqrt[3]{2}} @f$
**	- Decimal: `1.2599210498948731647672106072782283505702514647015079800819751121...`
*/
#define CBRT_2			(1.25992107391357421875e0)

//! Mathematical constant: Cube root of 3 (`cbrt(3)`)
/*!
**	- Math: @f$ {\sqrt[3]{3}} @f$
**	- Decimal: `1.4422495703074083823216383107801095883918692534993505775464161945...`
*/
#define CBRT_3			(1.442249570307408301772511549643240869045257568359375e0)



//! Mathematical constant: Gamma, the Euler–Mascheroni constant, the limiting difference between the harmonic series and the natural logarithm
/*!
**	- Math: @f$ {\gamma} = \lim_{n\to\infty} \biggl( -\ln{n} + \sum_{k=1}^n \frac{1}{k} \biggr) @f$
**	- Decimal: `0.5772156649015328606065120900824024310421593359399235988057672348...`
*/
#define EGAMMA			(0.57721566490153286060651209008240243104215933593992e0)

//! Mathematical constant: G, the Gauss constant, the reciprocal of the arithmetic–geometric mean of 1 and the square root of 2
/*!
**	- Math: @f$ G = \frac{2}{\pi} \int_{0}^{1} \frac{dx}{\sqrt{1 - x^4}) @f$
**	- Decimal: `0.8346268416740731862814297327990468089939930134903470024498273701...`
*/
#define GGAUSS			(0.834626841674073194354832594399340450763702392578125e0)



//! Mathematical constant: The bifurcation velocity, Feigenbaum's first constant, delta
/*!
**	- Math: @f$ {\delta } @f$
**	- Decimal: `4.669201609102990671853203820466...`
*/
#define FEIGENBAUM_DELTA	(4.669201609102990671853203820466e0)

//! Mathematical constant: The bifurcation ratio, Feigenbaum's second constant, alpha
/*!
**	- Math: @f$ {\alpha } @f$
**	- Decimal: `2.502907875095892822283902873218...`
*/
#define FEIGENBAUM_ALPHA	(4.669201609102990671853203820466e0)



/*! @} */
HEADER_END
#endif
