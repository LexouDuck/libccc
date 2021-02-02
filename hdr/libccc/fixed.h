/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/fixed.h                           |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_FIXED_H
#define __LIBCCC_FIXED_H
/*! @file libccc/fixed.h
**	This header defines the fixed-point number primitive types and functions.
**	@addtogroup libccc/fixed
**	@{
*/

/*
** ************************************************************************** *|
**                                  Includes                                  *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#if LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64 && \
	LIBCONFIG_BITS_FIXED != 128
	#error "LIBCONFIG_BITS_FIXED must be equal to one of: 16, 32, 64, 128"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGRALPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_INTEGRALPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_FRACTIONPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_FRACTIONPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGRALPART + LIBCONFIG_BITS_FIXED_FRACTIONPART > LIBCONFIG_BITS_FIXED
	#error "The sum of both _INTEGERPART and _DECIMALPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif



#if LIBCONFIG_USE_STD_FIXEDPOINT

#include <stdfix.h>

typedef _Sat short _Accum		t_g16;	//!< The type for 16-bit signed fixed-point rational numbers
typedef _Sat _Accum				t_g32;	//!< The type for 32-bit signed fixed-point rational numbers
typedef	_Sat long _Accum		t_g64;	//!< The type for 64-bit signed fixed-point rational numbers
#ifdef	__int128
typedef _Sat long long _Accum	t_g128;	//!< The type for 128-bit fixed-point numbers (only certain platforms)
#endif

#else

typedef t_s16		t_g16;	//!< The type for 16-bit signed fixed-point rational numbers
typedef t_s32		t_g32;	//!< The type for 32-bit signed fixed-point rational numbers
typedef	t_s64		t_g64;	//!< The type for 64-bit signed fixed-point rational numbers
#ifdef	__int128
typedef __int128	t_g128;	//!< The type for 128-bit fixed-point numbers (only certain platforms)
#endif

#endif



#if LIBCONFIG_BITS_FIXED == 128 && !defined(__int128)
	#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
#endif
//! The configurable-size fixed-point number primitive type.
typedef	LIBCONFIG_TYPE_FIXED	t_fixed;



/*
** ************************************************************************** *|
**                         Basic fixed-point operations                       *|
** ************************************************************************** *|
*/

#define Fixed_Rounded(R)	((t_fixed)((R) * (((t_fixed)1 << LIBCONFIG_BITS_FIXED_FRACTIONPART) + ((R) >= 0 ? 0.5 : -0.5))))
#define Fixed_FromInt(I)	((t_fixed)(I) << LIBCONFIG_BITS_FIXED_FRACTIONPART)
#define Fixed_ToInt(F)		((F) >> LIBCONFIG_BITS_FIXED_FRACTIONPART)
#define Fixed_FractionPart(A)	((t_fixed)(A) & FIXEDPT_FMASK)

#define Fixed_Add(A, B)	((A) + (B))
#define Fixed_Sub(A, B)	((A) - (B))
#define Fixed_Mul(A, B)	((t_fixed)(((t_fixed)(A) * (t_fixed)(B)) >> LIBCONFIG_BITS_FIXED_FRACTIONPART))
#define Fixed_Div(A, B)	((t_fixed)(((t_fixed)(A) << LIBCONFIG_BITS_FIXED_FRACTIONPART) / (t_fixed)(B)))



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

// TODO fixed_to_str
// TODO str_to_fixed



/*! @} */
HEADER_END
#endif
