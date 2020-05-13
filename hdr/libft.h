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
**	TODO	libft_math			+ tests
**	TODO	libft_stat			+ tests
**	TODO	libft_random		+ tests
**	TODO	libft_stringarray	+ tests
**	TODO	libft_vlq			+ tests
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

/*
**	Functions used:
**	-	void*	malloc(size_t n);
**	-	void	free(void* ptr);
*/
#include <stdlib.h>

/*
**	Included for the standard defined stable primitive int & uint types
*/
#include <inttypes.h>

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

/*
**	This macro determines how NULL pointers are to be handled
**	If 1, then all NULL pointer dereferences in libft functions will be avoided.
**	Otherwise if 0, then libft functions will always segfault when given NULLs.
*/
#define HANDLE_NULLPOINTERS		0



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
**	Define some useful string literals for some of the common number bases
**	and other useful charsets.
*/
#ifndef __CHARSETS_BASES__
#define __CHARSETS_BASES__
#define CHARSET_BINARY		"01"
#define CHARSET_OCTAL		"01234567"
#define CHARSET_DECIMAL		"0123456789"
#define CHARSET_HEX_LOWER	"0123456789abcdef"
#define CHARSET_HEX_UPPER	"0123456789ABCDEF"
#endif

#define CHARSET_WHITESPACE	"\t\f\v\n "


/*
**	The following macro sets what the 't_float' type should be.
**	_FLOAT_32_ means a 32-bit IEEE 754 standard precision float
**	_FLOAT_64_ means a 64-bit "double" precision float
*/
#define _FLOAT_32_
/*
**	This macro sets the default 't_uint' unsigned integer type to use:
**	_UINT_8_	for 8-bit uint	[0, 255]
**	_UINT_16_	for 16-bit uint	[0, 65535]
**	_UINT_32_	for 32-bit uint	[0, 2147483647]
**	_UINT_64_	for 64-bit uint	[0, 18446744073709551615]
*/
#define _UINT_32_
/*
**	This macro sets the default 't_int' signed integer type to use:
**	_INT_8_		for 8-bit int	[-128, 127]
**	_INT_16_	for 16-bit int	[-32648, 32647]
**	_INT_32_	for 32-bit int	[-2147483648, 2147483647]
**	_INT_64_	for 64-bit int	[-9223372036854775808, +9223372036854775807]
*/
#define _INT_32_

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



/*
** More care should be used with the default int/uint types: know your
** compiler
*/
#ifdef _UINT_8_
typedef t_u8			t_uint;
#endif
#ifdef _UINT_16_
typedef t_u16			t_uint;
#endif
#ifdef _UINT_32_
typedef t_u32			t_uint;
#endif
#ifdef _UINT_64_
typedef t_u64			t_uint;
#endif

#ifdef _INT_8_
typedef t_s8			t_int;
#endif
#ifdef _INT_16_
typedef t_s16			t_int;
#endif
#ifdef _INT_32_
typedef t_s32			t_int;
#endif
#ifdef _INT_64_
typedef t_s64			t_int;
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
** ************************************************************************** *|
**                       Floating-point primitive types                       *|
** ************************************************************************** *|
*/

/*
**	This very small value is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable operation.
*/
#define FLOAT_BIAS		(1.0e-10)

/*
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
#define F32_SIGNED			0x80000000
#define F32_EXPONENT_BIAS	127
#define F32_EXPONENT		0x7F800000
#define F32_EXPONENT_ZERO	0x3F800000
#define F32_EXPONENT_BITS	8
#define F32_MANTISSA		0x007FFFFF
#define F32_MANTISSA_SIGNED	0x807FFFFF
#define F32_MANTISSA_BITS	23
#define F32_INIT_VALUE		0x1.p-23

/*
**	IEEE 754 64-bit floating point "double" precision bitwise macros
*/
#define F64_SIGNED			0x8000000000000000
#define F64_EXPONENT_BIAS	1023
#define F64_EXPONENT		0x7FF0000000000000
#define F64_EXPONENT_ZERO	0x3FF0000000000000
#define F64_EXPONENT_BITS	11
#define F64_MANTISSA		0x000FFFFFFFFFFFFF
#define F64_MANTISSA_SIGNED	0x800FFFFFFFFFFFFF
#define F64_MANTISSA_BITS	52
#define F64_INIT_VALUE		0x1.p-52



/*
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/

#ifdef _FLOAT_32_
typedef t_f32	t_float;
#define FLOAT_SIGNED			F32_SIGNED
#define FLOAT_EXPONENT_BIAS		F32_EXPONENT_BIAS
#define FLOAT_EXPONENT			F32_EXPONENT
#define FLOAT_EXPONENT_ZERO		F32_EXPONENT_ZERO
#define FLOAT_EXPONENT_BITS		F32_EXPONENT_BITS
#define FLOAT_MANTISSA			F32_MANTISSA
#define FLOAT_MANTISSA_SIGNED	F32_MANTISSA_SIGNED
#define FLOAT_MANTISSA_BITS		F32_MANTISSA_BITS
#define FLOAT_INIT_VALUE		F32_INIT_VALUE
#endif

#ifdef _FLOAT_64_
typedef t_f64	t_float;
#define FLOAT_SIGNED			F64_SIGNED
#define FLOAT_EXPONENT_BIAS		F64_EXPONENT_BIAS
#define FLOAT_EXPONENT			F64_EXPONENT
#define FLOAT_EXPONENT_ZERO		F64_EXPONENT_ZERO
#define FLOAT_EXPONENT_BITS		F64_EXPONENT_BITS
#define FLOAT_MANTISSA			F64_MANTISSA
#define FLOAT_MANTISSA_SIGNED	F64_MANTISSA_SIGNED
#define FLOAT_MANTISSA_BITS		F64_MANTISSA_BITS
#define FLOAT_INIT_VALUE		F64_INIT_VALUE
#endif



#ifndef INFINITY
#define INFINITY		(1. / 0.)
#endif
#define IS_INFINITY(x)	((x) == INFINITY || (x) == -INFINITY)

#ifndef NAN
#define NAN				(0. / 0.)
#endif
#define IS_NAN(x)		((x) != (x))



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
typedef union		u_varint
{
	t_s8			sc;
	t_s16			ss;
	t_s32			si;
	t_s64			sl;
	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
}					t_varint;

typedef union		u_varfloat
{
	t_f32			f;
	t_f64			lf;
}					t_varfloat;

#endif
