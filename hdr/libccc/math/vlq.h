/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/vlq.h                        |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_VLQ_H
#define __LIBCCC_MATH_VLQ_H
/*!@group{libccc_math_vlq}
** @{
**	This header defines variable-length numeric types, and utility functions for them.
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
#include "libccc/fixed.h"
#include "libccc/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



/*
** ************************************************************************** *|
**                       Variable-size primitive types                        *|
** ************************************************************************** *|
*/

//! A union storing an integer (signed or unsigned) of any common storage size
/*!
**	These unions are used for certain difficult casting conditions.
**	They are used in particular when casting an <stdarg.h> va_arg to the right type.
*/
//!@{
typedef union varuint // TODO refactor this and add similar types for fixed and float
{
	t_u8	uc;	//!< unsigned integer: 8-bit (char)
	t_u16	us;	//!< unsigned integer: 16-bit (short)
	t_u32	ui;	//!< unsigned integer: 32-bit (int)
	t_u64	ul;	//!< unsigned integer: 64-bit (long)
#if LIBCONFIG_USE_128BIT
	t_q128	uh;	//!< unsigned integer: 128-bit (huge) 
#endif
}		u_varuint;

typedef union varsint // TODO refactor this and add similar types for fixed and float
{
	t_s8	sc;	//!< signed integer: 8-bit (char)
	t_s16	ss;	//!< signed integer: 16-bit (short)
	t_s32	si;	//!< signed integer: 32-bit (int)
	t_s64	sl;	//!< signed integer: 64-bit (long)
#if LIBCONFIG_USE_128BIT
	t_q128	sh;	//!< signed integer: 128-bit (huge) 
#endif
}		u_varsint;
//!@}



//! A union storing a fixed-point number of any common size/precision
/*!
**	These unions are used for certain difficult casting conditions.
**	They are used in particular when casting an <stdarg.h> va_arg to the right type.
*/
typedef union varfixed
{
	t_q16	qs;	//!< fixed-point: 16-bit (short)
	t_q32	qi;	//!< fixed-point: 32-bit (int)
	t_q64	ql;	//!< fixed-point: 64-bit (long)
#if LIBCONFIG_USE_128BIT
	t_q128	qh;	//!< fixed-point: 128-bit (huge) 
#endif
}		u_varfixed;



//! A union storing a floating-point number of any common size/precision
/*!
**	These unions are used for certain difficult casting conditions.
**	They are used in particular when casting an <stdarg.h> va_arg to the right type.
*/
typedef union varfloat
{
	t_f32	fs;	//!< floating-point: single precision
	t_f64	fd;	//!< floating-point: double precision
#ifdef	__float80
	t_f80	fe;	//!< floating-point: extended precision
#endif
#ifdef	__float128
	t_f128	fq;	//!< floating-point: quadruple precision
#endif
}		u_varfloat;



/*! @} */
HEADER_END
#endif
