/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/format.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_FORMAT_H
#define __LIBCCC_FORMAT_H
/*!@group{libccc_format}
** @{
**	This header defines printf-style functions, and their format specifiers
**
**	@isostd{C,https://en.cppreference.com/w/c/variadic}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
#endif

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*!
**	Cross-platform '%' format specifiers for `printf()`-like function calls:
**	@see
**	- String_Format()
**	- IO_Write_Format()
**	- IO_Output_Format()
**
**	NOTE: the "SF_" stands for "String Format"
**
**	@file
*/

#define SF_ENUM	"%d"

//! @see libccc/bool.h
//!@{
#define SF_BOOL	"%d"
//!@}

//! @see libccc/char.h
//!@{
#define SF_CHAR	"%c"
#define SF_UTF8	"%c"
//!@}

//! @see libccc/int.h
//!@{
#define SF_S8		"%i"
#define SF_S16		"%i"
#define SF_S32		"%i"
#define SF_U8		"%u"
#define SF_U16		"%u"
#define SF_U32		"%u"
#define SF_HEX_U8	"%#X"
#define SF_HEX_U16	"%#X"
#define SF_HEX_U32	"%#X"
#if (defined(__APPLE__) || defined(_WIN32))
	#define SF_S64		"%lli"
	#define SF_U64		"%llu"
	#define SF_HEX_U64	"%#llX"
#else
	#define SF_S64		"%li"
	#define SF_U64		"%lu"
	#define SF_HEX_U64	"%#lX"
#endif
#define SF_S128		"[128-bit signed int]"		// TODO find a way to make this work
#define SF_U128		"[128-bit unsigned int]"	// TODO find a way to make this work
#define SF_HEX_U128	"[128-bit unsigned int]"	// TODO find a way to make this work

#define SF_SINT		CONCAT(SF_S,	 LIBCONFIG_SINT_BITS)
#define SF_UINT		CONCAT(SF_U,	 LIBCONFIG_UINT_BITS)
#define SF_HEX_UINT	CONCAT(SF_HEX_U, LIBCONFIG_UINT_BITS)
//!@}

//! @see libccc/fixed.h
//!@{
#define SF_Q16		"%0.8i"
#define SF_Q32		"%0.8i"
#define SF_Q64		"%0.8li"
#define SF_Q128		"%0.8lli"
#define SF_HEX_Q16	"%#0.8X"
#define SF_HEX_Q32	"%#0.8X"
#define SF_HEX_Q64	"%#0.8lX"
#define SF_HEX_Q128	"%#0.8llX"

#define SF_FIXED		CONCAT(SF_Q,	 LIBCONFIG_FIXED_BITS)
#define SF_HEX_FIXED	CONCAT(SF_HEX_Q, LIBCONFIG_FIXED_BITS)
//!@}

//! @see libccc/float.h
//!@{
#define SF_F32		"%#g"
#define SF_F64		"%#g"
#define SF_F80		"%#Lg"
#define SF_F128		"%#Lg"
#define SF_HEX_F32	"%#a"
#define SF_HEX_F64	"%#a"
#define SF_HEX_F80	"%#La"
#define SF_HEX_F128	"%#La"

#define SF_FLOAT		CONCAT(SF_F,	 LIBCONFIG_FLOAT_BITS)
#define SF_HEX_FLOAT	CONCAT(SF_HEX_F, LIBCONFIG_FLOAT_BITS)
//!@}

//! @see libccc/pointer.h
//!@{
#define SF_PTR			SF_POINTER
#define SF_POINTER		"%#p"
#define SF_SIZE			"%zu"
#define SF_HEX_SIZE		"%#zx"
#define SF_PTRDIFF		"%ti"
#define SF_HEX_PTRDIFF	"%#tx"
#define SF_SINTPTR		"%zi"
#define SF_UINTPTR		"%zu"
#define SF_SINTMAX		"%ji"
#define SF_UINTMAX		"%ju"
//!@}

//! @see libccc/memory.h
//!@{
#define SF_MEM(N)		SF_MEMORY(N)
#define SF_MEMORY(N)	"%."#N"s"
//!@}

//! @see libccc/string.h
//!@{
#define SF_STR			SF_STRING
#define SF_STRING		"%s"
//!@}

//! @see libccc/color.h
//!@{
#define SF_COLOR_ARGB16	"#%X"
#define SF_COLOR_ARGB32	"#%X"
#define SF_COLOR_ARGB	"(A:%g, R:%g, G:%g, B:%g)"
#define SF_COLOR_AHSL	"(A:%g, H:%g, S:%g, L:%g)"
//!@}

//! @see libccc/math/complex.h
//!@{
#define SF_COMPLEX	"(%g + %g*i)"
//!@}

//! @see libccc/math/algebra.h
//!@{
#define SF_VECTOR	"(%g)"
#define SF_VECTOR2D	"(%g, %g)"
#define SF_VECTOR3D	"(%g, %g, %g)"
#define SF_VECTOR4D	"(%g, %g, %g, %g)"
#define SF_MATRIX	SF_VECTOR
#define SF_MATRIX2D	SF_VECTOR2D"\n"SF_VECTOR2D"\n"
#define SF_MATRIX3D	SF_VECTOR3D"\n"SF_VECTOR3D"\n"SF_VECTOR3D"\n"
#define SF_MATRIX4D	SF_VECTOR4D"\n"SF_VECTOR4D"\n"SF_VECTOR4D"\n"SF_VECTOR4D"\n"
//!@}



/*
** ************************************************************************** *|
**                           String Format Functions                          *|
** ************************************************************************** *|
*/

//! Constructs a string from the given `format` string and multiple args (equivalent to `asprintf()`)
/*!
**	@isostd{BSD,https://linux.die.net/man/3/asprintf}
**
**	Constructs a new null-terminated string, which is generated from the given `format` string,
**	as well as any relevant variadic arguments - it is equivalent to the `asprintf()` function.
**
**	The `format` string may contain format specifiers (ie: a '%%' followed by
**	certain specific text characters, documented below).
**	A format specifier has the following syntax (items between brackets are optional):
**
**	```c
**	%[flags][minsize][.precision][bitsize]char
**	```
**
**	Here is a description of the valid possible choices for each of these 5 fields: (flags,minsize,precision,bitsize,char)
**	```c
**	.________________________________________________________________________
**	| char	| Output										| Output Example |
**	|_______|_______________________________________________|________________|
**	|'d','i'| Signed decimal integer						| "392"
**	| 'u'	| Unsigned decimal integer						| "7235"
**	| 'o'	| Unsigned octal								| "610"
**	| 'x'	| Unsigned hexadecimal integer, lowercase		| "7fa"
**	| 'X'	| Unsigned hexadecimal integer, uppercase		| "7FA"
**	| 'f'	| Decimal notation floating-point, lowercase	| "392.65"
**	| 'F'	| Decimal notation floating-point, uppercase	| "392.65"
**	| 'e'	| Scientific notation floating-point, lowercase	| "3.9265e+2"
**	| 'E'	| Scientific notation floating-point, uppercase	| "3.9265E+2"
**	| 'g'	| Use the shortest representation: "%e" or "%f"	| "392.65"
**	| 'G'	| Use the shortest representation: "%E" or "%F"	| "392.65"
**	| 'a'	| Hexadecimal floating point, lowercase			| "-0xc.90fep-2"
**	| 'A'	| Hexadecimal floating point, uppercase			| "-0XC.90FEP-2"
**	| 'c'	| Character										| "a"
**	| 's'	| String of characters							| "example"
**	| 'p'	| Pointer address								| "b8000000"
**	| '%'	| A "%%" specifier will write a single '%' char	| "%"
**	| 'n'	| Nothing printed: the corresponding argument must be a pointer to a signed int.
**	|_______|	The number of characters written so far is stored in the pointed location.	
**	.___________________________________________________________________________________________________________________
**	| flags	| Description																								|
**	|_______|___________________________________________________________________________________________________________|
**	| '+'	| Precede the result with a plus '+' or minus '-' sign, even for positive/unsigned numbers.					|
**	|_______|_By default, only negative numbers are preceded with a minus '-' sign._____________________________________|
**	| '#'	| With 'o','x','X': the value is preceeded with 0, 0x or 0X respectively, for values different than zero.	|
**	|_______|_With 'a','A','e','E','f','F','g','G': forces the written output number to contain a decimal point.________|
**	|(space)| If no sign is going to be written, a blank space is inserted before the value.							|
**	|_______|___________________________________________________________________________________________________________|
**	.___________________________________________________________________________________________
**	| minsize	|	is a number (so, decimal numerical digit chars).							|
**	|___________|_______________________________________________________________________________|
**	| The minimum amount of characters to be printed for this specifier.
**	| The value is not truncated, even if the result is larger.
**	| If the value is shorter than this number, the result is padded with blank spaces.
**	.___________________________________________________________________________________________
**	| precision	|	is a number (so, decimal numerical digit chars), preceded by a '.' period.	|
**	|___________|_______________________________________________________________________________|
**	| With 'a','A','e','E','f','F': the number of digits to be printed after the decimal point (by default, this is 6).
**	| With 'g','G': the maximum number of significant digits to be printed for the mantissa.
**	| With 's': this is the maximum number of characters to be printed (by default, all chars are printed until the '\0').
**	| If the period is specified without an explicit value for precision, 0 is assumed.
**	.___________________________________________________________________________________________________________
**	|bitsize| 'd', 'i'		| 'u', 'o', 'x', 'X'	|'f','e','g','a'| 'c'	| 's'		| 'p'	| 'n'			|
**	|_______|_______________|_______________________|'F'_'E'_'G'_'A'|_______|___________|_______|_______________|
**	|(none)	| int			| unsigned int			| double		| int	| char*		| void*	| int*			|
**	| "hh"	| signed char	| unsigned char			|				|		|			|		| signed char*	|
**	|  "h"	| short int		| unsigned short int	|				|		|			|		| short int*	|
**	|  "l"	| long int		| unsigned long int		|				| wint_t| wchar_t*	|		| long int*		|
**	| "ll"	| long long int	| unsigned long long int|				|		|			|		| long long int*|
**	|  "j"	| intmax_t		| uintmax_t				|				|		|			|		| intmax_t*		|
**	|  "z"	| size_t		| size_t				|				|		|			|		| size_t*		|
**	|  "t"	| ptrdiff_t		| ptrdiff_t				|				|		|			|		| ptrdiff_t*	|
**	|  "L"	|				|						| long double	|		|			|		|				|
**	|_______|_______________|_______________________|_______________|_______|___________|_______|_______________|
**	```
**
**	@returns
**	A newly allocated string, constructed from the given `format` string and arguments
*/
_FORMAT(printf, 1, 2)
_MALLOC()
t_char*					String_Format(t_char const* format, ...);
#define c_asprintf		String_Format //!< @alias{String_Format}
#define c_strfmt		String_Format //!< @alias{String_Format}
#define c_strformat		String_Format //!< @alias{String_Format}
#define String_Build	String_Format //!< @alias{String_Format}

//! @see				String_Format
_MALLOC()
t_char*					String_Format_VA(t_char const* format, va_list args);
#define c_vasprintf		String_Format_VA //!< @alias{String_Format_VA}
#define c_strfmt_va		String_Format_VA //!< @alias{String_Format_VA}
#define c_strformat_va	String_Format_VA //!< @alias{String_Format_VA}
#define String_Build_VA	String_Format_VA //!< @alias{String_Format_VA}



//! Constructs a string from the given `format` string and multiple args, writing at most `max` chars into `dest` (equivalent to `snprintf()`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/io/snprintf}
**
**	@param	dest	The destination buffer, in which to write the resulting string
**					NOTE: if `NULL`, does not write anything and simply returns the length
**	@param	max		The maximum amount of characters to write to `dest`,
**					including the `'\0'` null terminator
**	@param	format	The format string used to construct the resulting date string.
**					You can learn more here: https://www.cplusplus.com/reference/cstdio/printf/
**	@returns
**	The amount of characters in the constructed format string, regardless of `max` size
*/
_FORMAT(printf, 3, 4)
t_size						String_Format_N(t_char* dest, t_size max, t_char const* format, ...);
#define c_snprintf			String_Format_N //!< @alias{String_Format_N}
#define c_strnfmt			String_Format_N //!< @alias{String_Format_N}
#define c_strnformat		String_Format_N //!< @alias{String_Format_N}
#define String_Build_N		String_Format_N //!< @alias{String_Format_N}

//! @see					String_Format_N
t_size						String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args);
#define c_vsnprintf			String_Format_N_VA //!< @alias{String_Format_N_VA}
#define c_strnfmt_va		String_Format_N_VA //!< @alias{String_Format_N_VA}
#define c_strnformat_va		String_Format_N_VA //!< @alias{String_Format_N_VA}
#define String_Build_N_VA	String_Format_N_VA //!< @alias{String_Format_N_VA}



/* NB: SEE ALSO (in libccc/sys/io.h)

//! Writes the given formatted string to the standard output - equivalent to `fprintf()`, or rather `dprintf()`
_FORMAT(printf, 2, 3)
int						IO_Write_Format(t_fd fd, t_char const* format, ...);
#define c_write_format	IO_Write_Format
#define c_dprintf		IO_Write_Format

//! Writes the given formatted string to the standard output - equivalent to `printf()`
_FORMAT(printf, 1, 2)
int						IO_Output_Format(t_char const* format, ...);
#define c_output_format	IO_Output_Format
#define c_printf		IO_Output_Format
*/



/*! @} */
HEADER_END
#endif
