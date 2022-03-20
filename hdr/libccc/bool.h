/*============================================================================*\
||                                            ______________________________  ||
||  libccc/bool.h                            |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_BOOL_H
#define __LIBCCC_BOOL_H
/*!@group{libccc_bool,11,libccc/bool.h}
**
**	This header defines the boolean (TRUE/FALSE) primitive type and functions.
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_BOOL_T
#define __LIBCCC_BOOL_T

/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

//!@doc Primitive type: The boolean type (`TRUE` or `FALSE`)
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/types/boolean}
**
**	Here, we use the native (since the C99 standard) `_Bool` boolean type.
**	This type is useful because its value will always be 0 or 1, never more.
**	This means you will not have strange behaviors caused by the use of integer
**	arithmetic operations on booleans - do not assume `t_bool` works like int types.
**	NOTE: Conversion to `_Bool` does not work the same as conversion to integer types:
**	any non-zero value will become `1` once it is casted to the `_Bool` type.
**	So, for example, `(bool)0.5` gives `1`, whereas `(int)0.5` gives `0`.
*/
//!@{
#if (defined(__STDC__) && (__STDC_VERSION__ >= __STDC_VERSION_C99__))
	typedef _Bool	t_bool;

#elif (defined(__NOSTD__))
	typedef _Bool	t_bool;
//	typedef char	t_bool;
//	typedef int		t_bool;

#else
	#include <stdbool.h>
	typedef bool	t_bool;

#endif
TYPEDEF_ALIAS(		t_bool, BOOL, PRIMITIVE)
//!@}



//!@doc Represents a boolean false value (0)
//!@{
#undef	FALSE
#define FALSE	(0)
#ifndef __cplusplus
#undef	false
#define false	FALSE
#endif
//!@}

//!@doc Represents a boolean true value  (1)
//!@{
#undef	TRUE
#define TRUE	(1)
#ifndef __cplusplus
#undef	true
#define true	TRUE
#endif
//!@}



#ifndef __cplusplus

//!@doc Boolean logical operator macros
//!@{
#ifndef and
#define and	&&
#endif
#ifndef or
#define or	||
#endif
#ifndef xor
#define xor	^	//!< TODO create boolean operator `^^` for this operator
#endif
#ifndef not
#define not	!
#endif
//!@}

//!@doc Boolean bitwise operator macros
//!@{
#ifndef bitand
#define bitand	&
#endif
#ifndef bitor
#define bitor	|
#endif
#ifndef bitxor
#define bitxor	^
#endif
#ifndef bitnot
#define bitnot	~
#endif
//!@}

#endif



#endif
#ifndef __LIBCCC_BOOL_F
#define __LIBCCC_BOOL_F

/*
** ************************************************************************** *|
**                             String Conversions                             *|
** ************************************************************************** *|
*/

#define BOOL_TOSTRING \
		BOOL_TOSTRING_UPPER
#define BOOL_TOSTRING_UPPER(VALUE)	((VALUE) ? "TRUE" : "FALSE")
#define BOOL_TOSTRING_LOWER(VALUE)	((VALUE) ? "true" : "false")
#define BOOL_TOSTRING_MIXED(VALUE)	((VALUE) ? "True" : "False")

// TODO split Bool_ToString() into 3 sub-functions with one configurable macro ?



//!@doc Get the string representation of a boolean value ("TRUE" or "FALSE")
//!@{
t_char const*			Bool_String(t_bool value, t_bool uppercase);
#define c_boolstr		Bool_String
//!@}

//!@doc Write the string representation of a boolean value ("TRUE" or "FALSE") into the `dest` buffer
//!@{
t_size					Bool_Print(t_char* dest, t_bool value, t_bool uppercase);
#define c_boolprint		Bool_Print
//!@}

//!@doc Get a newly allocated string representation of a boolean value ("TRUE" or "FALSE")
//!@{
t_char*					Bool_ToString(t_bool value, t_bool uppercase);
#define c_booltostr		Bool_ToString
//!@}



//!@doc Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
//!@{
t_size					Bool_Parse(t_bool *dest, t_char const* str);
#define c_boolparse		Bool_Parse
//!@}

//!@doc Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
//!@{
t_bool					Bool_FromString(t_char const* str);
#define c_strtobool		Bool_FromString
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
