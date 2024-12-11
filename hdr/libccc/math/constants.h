/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/constants.h                  |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_CONSTANTS_H
#define __LIBCCC_MATH_CONSTANTS_H
/*!@group{libccc_math_constants,55,libccc/math/constants.h}
**
**	This header defines the common standard math constants and macro defines.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math}
**
**	This file holds various relevant mathematical constants.
**	Many of these constants are used to speed up the fast-approximate versions
**	of some fundamental algorithms and math functions.
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
**	Basic fractions
*/

//! Mathematical constant: The inverse of 2, one half (`1 / 2`)
/*!
**	- Math: @f$ {\frac{1}{2}} @f$
**	- Decimal: `0.5`
*/
#define INV_2		(0.5e0L)

//! Mathematical constant: The inverse of 3, one third (`1 / 3`)
/*!
**	- Math: @f$ {\frac{1}{3}} @f$
**	- Decimal: `0.333333...`
*/
#define INV_3		(0.333333333333333333333333333333333333e0L)

//! Mathematical constant: The inverse of 4, one quarter (`1 / 4`)
/*!
**	- Math: @f$ {\frac{1}{4}} @f$
**	- Decimal: `0.25`
*/
#define INV_4		(0.25e0L)

//! Mathematical constant: The inverse of 5, one fifth (`1 / 5`)
/*!
**	- Math: @f$ {\frac{1}{5}} @f$
**	- Decimal: `0.5`
*/
#define INV_5		(0.2e0L)

//! Mathematical constant: The inverse of 6, one sixth (`1 / 6`)
/*!
**	- Math: @f$ {\frac{1}{6}} @f$
**	- Decimal: `0.1666666...`
*/
#define INV_6		(0.166666666666666666666666666666666667e0L)

//! Mathematical constant: The inverse of 7, one seventh (`1 / 7`)
/*!
**	- Math: @f$ {\frac{1}{7}} @f$
**	- Decimal: `0.142857...`
*/
#define INV_7		(0.142857142857142857142857142857142857e0L)



/*
**	Square roots
*/

//! Mathematical constant: The square root of 2 (`sqrt(2)`), the Pythagoras constant
/*!
**	- Math: @f$ {\sqrt{2}} @f$
**	- Decimal: `1.414213562373095048801688724209698078569671875376948073176679738...`
*/
#define SQRT_2			(0x1.6A09E667F3BCDp+0L)

//! Mathematical constant: The inverse square root of 2 (`1 / sqrt(2)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{2}}} @f$
**	- Decimal: `0.7071067811865475244008443621048490392848359376884740365883398689...`
*/
#define INV_SQRT_2		(0x1.6A09E667F3BCDp-1L)

//! Mathematical constant: The square root of 3 (`sqrt(3)`), the Theodorus constant
/*!
**	- Math: @f$ {\sqrt{3}} @f$
**	- Decimal: `1.732050807568877293527446341505872366942805253810380628055...`
*/
#define SQRT_3			(0x1.BB67AE8584CAAp+0L)

//! Mathematical constant: The inverse square root of 3 (`1 / sqrt(3)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{3}}} @f$
**	- Decimal: `0.5773502691896257645091487805019574556476017512701268760186023264...`
*/
#define INV_SQRT_3		(0x1.279A74590331Cp-1L)

//! Mathematical constant: The square root of 5 (`sqrt(5)`)
/*!
**	- Math: @f$ {\sqrt{5}} @f$
**	- Decimal: `2.236067977499789696409173668731276235440618359611525724270...`
*/
#define SQRT_5			(0x1.1E3779B97F4A7p+1L)

//! Mathematical constant: The inverse square root of 5 (`1 / sqrt(5)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{5}}} @f$
**	- Decimal: `0.4472135954999579392818347337462552470881236719223051448541794490...`
*/
#define INV_SQRT_5		(0x1.C9F25C5BFEDD9p-2L)

//! Mathematical constant: The square root of 7 (`sqrt(7)`)
/*!
**	- Math: @f$ {\sqrt{7}} @f$
**	- Decimal: `2.6457513110645905905016157536392604257102591830824501803683344592...`
*/
#define SQRT_7			(0x1.52A7FA9D2F8EAp+1L)

//! Mathematical constant: The inverse square root of 7 (`1 / sqrt(7)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{7}}} @f$
**	- Decimal: `0.3779644730092272272145165362341800608157513118689214543383334942...`
*/
#define INV_SQRT_7		(0x1.83091E6A7F7E7p-2L)



/*
**	Trigonometry
*/

//! Mathematical constant: circle periphery from diameter, pi `π` (`TAU / 2`)
/*!
**	- Math: @f$ {\pi} @f$
**	- Decimal: `3.141592653589793238462643383279502884197169399375105820974...`
*/
#define PI				(0x1.921FB54442D18p+1L)

//! Mathematical constant: circle periphery from radius, tau `τ` (`2 * PI`)
/*!
**	- Math: @f$ {2\pi} @f$
**	- Decimal: `6.283185307179586476925286766559005768394338798750211641949...`
*/
#define TAU 			(0x1.921FB54442D18p+2L)

//! Mathematical constant: Inverse of pi `1/π` (`1 / PI`)
/*!
**	- Math: @f$ {\frac{1}{\pi}} @f$
**	- Decimal: `0.318309886183790671537767526745028724068919291480912897495...`
*/
#define INV_PI			(0x1.45F306DC9C883p-2L)

//! Mathematical constant: Inverse of tau `1/τ` (`1 / TAU`)
/*!
**	- Math: @f$ {\frac{1}{2\pi}} @f$
**	- Decimal: `0.159154943091895335768883763372514362034459645740456448747...`
*/
#define INV_TAU			(0x1.45F306DC9C883p-3L)

//! Mathematical constant: Inverse of the square root of pi `1/√π` (`1 / sqrt(PI)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{\pi}}} @f$
**	- Decimal: `0.5641895835477562869480794515607725858440506293289988568440857217...`
*/
#define INV_SQRT_PI		(0.5641895835477562869480794515607725858440506293289988568440857217e0L)

//! Mathematical constant: Inverse of the square root of tau `1/√τ` (`1 / sqrt(TAU)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{2\pi}}} @f$
**	- Decimal: `0.3989422804014326779399460599343818684758586311649346576659258297...`
*/
#define INV_SQRT_TAU	(0.3989422804014326779399460599343818684758586311649346576659258297e0L)



//! Mathematical constant: Half of pi `π/2` (`PI / 2`)
/*!
**	- Math: @f$ {\frac{\pi}{2}} @f$
**	- Decimal: `1.5707963267948966192313216916397514420985846996875529104874722962...`
*/
#define DIV_PI_2	(0x1.921FB54442D18p+0L)
//! Alias for #DIV_PI_2
#define PI_HALF		DIV_PI_2

//! Mathematical constant: Third of pi `π/3` (`PI / 3`)
/*!
**	- Math: @f$ {\frac{\pi}{3}} @f$
**	- Decimal: `1.0471975511965977461542144610931676280657231331250352736583148641...`
*/
#define DIV_PI_3	(1.0471975511965977461542144610931676280657231331250352736583148641e0L)
//! Alias for #DIV_PI_3
#define PI_THIRD	DIV_PI_3

//! Mathematical constant: Quarter of pi `π/4` (`PI / 4`)
/*!
**	- Math: @f$ {\frac{\pi}{4}} @f$
**	- Decimal: `0.7853981633974483096156608458198757210492923498437764552437361481...`
*/
#define DIV_PI_4	(0x1.921FB54442D18p-1L)
//! Alias for #DIV_PI_4
#define PI_QUARTER	DIV_PI_4

//! Mathematical constant: Fifth of pi `π/5` (`PI / 5`)
/*!
**	- Math: @f$ {\frac{\pi}{5}} @f$
**	- Decimal: `0.6283185307179586476925286766559005768394338798750211641949889185...`
*/
#define DIV_PI_5	(0.6283185307179586476925286766559005768394338798750211641949889185e0L)
//! Alias for #DIV_PI_3
#define PI_FIFTH	DIV_PI_5



/*
**	Exponential & Logarithm
*/

//! Mathematical constant: The exponential number, e (`exp(1)`), Euler's number
/*!
**	- Math: @f$ {e} @f$
**	- Decimal: `2.718281828459045235360287471352662497757247093699959574966...`
*/
#define E				(0x1.5BF0A8B145769p+1L)

//! Mathematical constant: The exponential number, e (`exp(1)`), Euler's number
/*!
**	- Math: @f$ {e} @f$
**	- Decimal: `2.718281828459045235360287471352662497757247093699959574966...`
*/
#define INV_E			(0x1.5BF0A8B145769p+1L)

//! Mathematical constant: The natural logarithm of 2 (`ln(2)`)
/*!
**	- Math: @f$ {\ln {2}} @f$
**	- Decimal: `0.693147180559945309417232121458176568075500134360255254120...`
*/
#define LN_2			(0x1.62E42FEFA39EFp-1L)

//! Mathematical constant: The natural logarithm of 3 (`ln(3)`)
/*!
**	- Math: @f$ {\ln {3}} @f$
**	- Decimal: `1.098612288668109691395245236922525704647490557823...`
*/
#define LN_3			(1.098612288668109691395245236922525704647490557823e0L)

//! Mathematical constant: The natural logarithm of 5 (`ln(5)`)
/*!
**	- Math: @f$ {\ln {5}} @f$
**	- Decimal: `1.609437912434100374600759333226187639525601354269...`
*/
#define LN_5			(1.609437912434100374600759333226187639525601354269e0L)

//! Mathematical constant: The natural logarithm of 7 (`ln(7)`)
/*!
**	- Math: @f$ {\ln {7}} @f$
**	- Decimal: `1.945910149055313305105352743443179729637084729582...`
*/
#define LN_7			(1.945910149055313305105352743443179729637084729582e0L)

//! Mathematical constant: The natural logarithm of 10 (`ln(10)`)
/*!
**	- Math: @f$ {\ln {10}} @f$
**	- Decimal: `2.302585092994045684017991454684364207601101488628772976033...`
*/
#define LN_10			(0x1.26BB1BBB55516p+1L)



/*
**	Other constants
*/

//! Mathematical constant: Phi `φ = (1+√5)/2`, (`(1 + sqrt(5)) / 2`), the golden ratio
/*!
**	- Math: @f$ {\frac{1}{2}(1 + \sqrt{5})} @f$
**	- Decimal: `1.6180339887498948482045868343656381177203091798057628621354486227...`
*/
#define PHI				(1.6180339887498948482045868343656381177203091798057628621354486227e0L)
//! Alias for #PHI
#define GOLDEN_RATIO	PHI

//! Mathematical constant: Phi `-1/φ = (1-√5)/2`, (`(1 - sqrt(5)) / 2`), the golden ratio conjugate
/*!
**	- Math: @f$ {\frac{1}{2}(1 - \sqrt{5})} @f$
**	- Decimal: `-0.6180339887498948482045868343656381177203091798057628621354486227...`
*/
#define PHI_BAR			(-0.6180339887498948482045868343656381177203091798057628621354486227e0L)
//! Alias for #PHI_BAR
#define GILDED_RATIO	PHI_BAR

//! Mathematical constant: Delta-S `δs = 1+√2`, (`1 + sqrt(2)`), the silver ratio
/*!
**	- Math: @f$ {\frac{1}{2}(1 - \sqrt{5})} @f$
**	- Decimal: `2.414213562373095048801688724209698078569671875376948073176679738...`
*/
#define DELTA_S			(2.414213562373095048801688724209698078569671875376948073176679738e0L)
//! Alias for #DELTA_S
#define SILVER_RATIO	DELTA_S



//! Mathematical constant: Gamma, `γ`, the Euler–Mascheroni constant, the limiting difference between the harmonic series and the natural logarithm
/*!
**	- Math: @f$ {\gamma} = \lim_{n\to\infty} \biggl( -\ln{n} + \sum_{k=1}^n \frac{1}{k} \biggr) @f$
**	- Decimal: `0.5772156649015328606065120900824024310421593359399235988057672348...`
*/
#define EGAMMA			(0.57721566490153286060651209008240243104215933593992e0L)

//! Mathematical constant: G, the Gauss constant, the reciprocal of the arithmetic–geometric mean of 1 and the square root of 2
/*!
**	- Math: @f$ {G = \frac{2}{\pi} \int_{0}^{1} \frac{dx}{\sqrt{1 - x^4}}} @f$
**	- Decimal: `0.8346268416740731862814297327990468089939930134903470024498273701...`
*/
#define GGAUSS			(0.834626841674073194354832594399340450763702392578125e0L)



//! Mathematical constant: The bifurcation velocity, Feigenbaum's first constant, delta
/*!
**	- Math: @f$ {\delta } @f$
**	- Decimal: `4.669201609102990671853203820466...`
*/
#define FEIGENBAUM_DELTA	(4.669201609102990671853203820466e0L)

//! Mathematical constant: The bifurcation ratio, Feigenbaum's second constant, alpha
/*!
**	- Math: @f$ {\alpha } @f$
**	- Decimal: `2.502907875095892822283902873218...`
*/
#define FEIGENBAUM_ALPHA	(4.669201609102990671853203820466e0L)



/*! @endgroup */
HEADER_END
#endif
