/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

/*
**	TODO	libft_color			+ tests
**	TODO	libft_random		+ tests
**	TODO	libft_stringarray	+ tests
**	TODO	libft_io			+ tests
**
**	TODO	libft_time			+ tests
**	TODO	libft_algebra		+ tests
**	TODO	libft_complex		+ tests
**	TODO	libft_fixedpoint	+ tests
**	TODO	libft_compress		+ tests
**	TODO	libft_socket		+ tests
**	TODO	libft_vlq			+ tests
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

/*
**	Included for the standard defined stable primitive int & uint types
*/
#include <inttypes.h>



/*
** ************************************************************************** *|
**                            Library Configuration                           *|
** ************************************************************************** *|
*/

/*
**	This macro determines how NULL pointer arguments are to be handled
**	If 0, then libft functions will always segfault when given NULL pointers.
**	If 1, then all NULL pointer dereferences in libft functions will be avoided.
*/
#define HANDLE_NULLPOINTERS		0

/*
**	This macro determines which math function implementations should be used.
**	If 1, the libft fast approximate functions will be used (precision error margin: 0.0001)
**	If 0, the builtin libc functions will be used
*/
#define LIBFTCONFIG_FAST_APPROX_MATH	0



/*
**	This macro sets the default 't_uint' default unsigned integer type to use:
**	_UINT_8_	for 8-bit uint	[0, 255]
**	_UINT_16_	for 16-bit uint	[0, 65535]
**	_UINT_32_	for 32-bit uint	[0, 2147483647]
**	_UINT_64_	for 64-bit uint	[0, 18446744073709551615]
*/
#define _UINT_64_
/*
**	This macro sets the default 't_int' default signed integer type to use:
**	_INT_8_		for 8-bit int	[-128, 127]
**	_INT_16_	for 16-bit int	[-32648, 32647]
**	_INT_32_	for 32-bit int	[-2147483648, 2147483647]
**	_INT_64_	for 64-bit int	[-9223372036854775808, +9223372036854775807]
*/
#define _INT_64_
/*
**	The following macro sets what the 't_float' default floating-point type should be.
**	_FLOAT_32_	for 32-bit IEEE 754 standard precision floating-point number
**	_FLOAT_64_	for 64-bit IEEE 754 double-precision floating-point number
**	_FLOAT_80_	for 80-bit x86 extended-precision floating-point number
**	_FLOAT_128_	for 128-bit IEEE 754 quadruple-precision floating-point number (GNU GCC 4.3 and up)
*/
#define _FLOAT_64_



/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

/*
**	Define the common useful macros for writing some pseudo-boolean syntax.
*/
#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	0

#ifdef	TRUE
#undef	TRUE
#endif
#define TRUE	1

/*
**	Define the common macros for return values used by several C functions.
*/
#ifdef	OK
#undef	OK
#endif
#define OK		0

#ifdef	ERROR
#undef	ERROR
#endif
#define ERROR	1

/*
**	NB: The following macros listed in this comment exist on any platform
**	Here is the list of all the predefined ANSI C macros
**	__cplusplus	Defined only when a C++ compiler is being used.
**	__OBJC__	Defined as 1 when the compiler is Objective-C.
**	__STDC__	Defined as 1 when the compiler complies with the ANSI standard.
**	__DATE__	String literal: The current date, in "MMM DD YYYY" format.
**	__TIME__	String literal: The current time, in "HH:MM:SS" format.
**	__FILE__	String literal: This contains the current source code filename.
**	__LINE__	Integer constant: the current source code line number.
**
**	There's also this very useful (non-macro) identifier, only defined in C99/C++:
**	__func__	String constant: The current function name.
**
**	Here are some of the many common GNU C macros:
**	__GNUC__			Integer constant (with value = GCC version), if the compiler is GNU-compliant.
**	__BASE_FILE__		String literal: the source entry point filename (the file which holds the 'int main()')
**	__INCLUDE_LEVEL__	Integer constant: The current depth of nesting within '#include' directives.
*/



/*
** ************************************************************************** *|
**                      Shorthands for primitive types                        *|
** ************************************************************************** *|
*/

/*
**	Define pseudo-types for all the primitive number types in a clear naming
**	convention, to better reflect the amount of bits used by each type.
**	(and also to avoid having to type 'unsigned' all the time)
*/
typedef uint8_t			t_u8;
typedef uint16_t		t_u16;
typedef uint32_t		t_u32;
typedef	uint64_t		t_u64;

typedef int8_t			t_s8;
typedef int16_t			t_s16;
typedef int32_t			t_s32;
typedef	int64_t			t_s64;

typedef float			t_f32;
typedef double			t_f64;
typedef long double		t_f80;
typedef __float128		t_f128;



/*
**	Much care should be used with the default int/uint types:
**	This obviously depends on you knowing your compiler
*/
#ifdef _UINT_8_
typedef t_u8		t_uint;
#endif
#ifdef _UINT_16_
typedef t_u16		t_uint;
#endif
#ifdef _UINT_32_
typedef t_u32		t_uint;
#endif
#ifdef _UINT_64_
typedef t_u64		t_uint;
#endif

#ifdef _INT_8_
typedef t_s8		t_int;
#endif
#ifdef _INT_16_
typedef t_s16		t_int;
#endif
#ifdef _INT_32_
typedef t_s32		t_int;
#endif
#ifdef _INT_64_
typedef t_s64		t_int;
#endif

#ifdef _FLOAT_32_
typedef t_f32		t_float;
#endif
#ifdef _FLOAT_64_
typedef t_f64		t_float;
#endif
#ifdef _FLOAT_80_
typedef t_f80		t_float;
#endif
#ifdef _FLOAT_128_
typedef t_f128		t_float;
#endif

/*
**	Define a boolean pseudo-type that is potentially faster than just 'int'.
**	The uint_fast8_t type is the fastest primitive type on the current machine
**	which contains at least 8 usable bits (ie: at least a range of 0-255).
**	On ARM processors this type might be 'int', otherwise it might be 'char'.
**	On embedded systems, this type could have all sorts of unusual bitsizes,
**	so no program should rely on any kind of overflow behavior from this type.
*/
typedef uint_fast8_t	t_bool;

/*
**	This typedef is here purely for nomenclature consistency
*/
typedef size_t			t_size;



/*
** ************************************************************************** *|
**                       Variable-size primitive types                        *|
** ************************************************************************** *|
*/

/*
** These unions are used for certain difficult casting conditions.
** They are used in particular when casting an <stdarg.h> var_arg to the
** appropriate type in ft_printf.
*/
typedef union		u_varint_
{
	t_s8			sc;
	t_s16			ss;
	t_s32			si;
	t_s64			sl;
	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
}					u_varint;

typedef union		u_varfloat_
{
	t_f32			f;
	t_f64			lf;
}					u_varfloat;

#endif
