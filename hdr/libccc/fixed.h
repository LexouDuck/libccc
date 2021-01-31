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

#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#if LIBCONFIG_BITS_FIXED != 8 && \
	LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64
	#error "LIBCONFIG_BITS_FIXED must be equal to one of: 8, 16, 32, 64"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGERPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_INTEGERPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_DECIMALPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_DECIMALPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGERPART + LIBCONFIG_BITS_FIXED_DECIMALPART > LIBCONFIG_BITS_FIXED
	#error "The sum of both _INTEGERPART and _DECIMALPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif



typedef t_s8	t_q8;	//!< The type for 8-bit signed fixed-point rational numbers
typedef t_s16	t_q16;	//!< The type for 16-bit signed fixed-point rational numbers
typedef t_s32	t_q32;	//!< The type for 32-bit signed fixed-point rational numbers
typedef	t_s64	t_q64;	//!< The type for 64-bit signed fixed-point rational numbers

typedef	LIBCONFIG_TYPE_FIXED	t_fixed;



/*
** ************************************************************************** *|
**                         Basic fixed-point operations                       *|
** ************************************************************************** *|
*/

// TODO add
// TODO sub
// TODO div
// TODO mul



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
