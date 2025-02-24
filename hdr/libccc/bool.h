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

/*============================================================================*\
||                                 Includes                                   ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_BOOL_T
#define __LIBCCC_BOOL_T

/*============================================================================*\
||                             Common Definitions                             ||
\*============================================================================*/

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

/*============================================================================*\
||                             String Conversions                             ||
\*============================================================================*/

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
t_size					Bool_Parse(t_bool *dest, t_size n, t_char const* str);
#define c_boolparse		Bool_Parse
//!@}

//!@doc Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
//!@{
t_bool					Bool_FromString(t_char const* str);
#define c_strtobool		Bool_FromString
//!@}



// Boolean operators



//!@doc Boolean operator: ⊤	(always true)
//!@{
t_bool				Bool_True(t_bool a, t_bool b);
#define c_true		Bool_True
#define Bool_T		Bool_True
//!@}

//!@doc Boolean operator: ⊥	(always false)
//!@{
t_bool				Bool_False(t_bool a, t_bool b);
#define c_false		Bool_False
#define Bool_F		Bool_False
//!@}

//!@doc Boolean operator: ⊣	(left operand value)
//!@{
t_bool				Bool_Left(t_bool a, t_bool b);
#define c_left		Bool_Left
#define Bool_L		Bool_Left
//!@}

//!@doc Boolean operator: ⫣	(not left operand value)
//!@{
t_bool				Bool_NotLeft(t_bool a, t_bool b);
#define c_nleft		Bool_NotLeft
#define Bool_NL		Bool_NotLeft
//!@}

//!@doc Boolean operator: ⊢	(right operand value)
//!@{
t_bool				Bool_Right(t_bool a, t_bool b);
#define c_right		Bool_Right
#define Bool_R		Bool_Right
//!@}

//!@doc Boolean operator: ⊬	(not right operand value)
//!@{
t_bool				Bool_NotRight(t_bool a, t_bool b);
#define c_nright	Bool_NotRight
#define Bool_NR		Bool_NotRight
//!@}

//!@doc Boolean operator: ⋀	(and)
//!@{
t_bool				Bool_And(t_bool a, t_bool b);
#define c_and		Bool_And
//!@}

//!@doc Boolean operator: ⊼	(not and)
//!@{
t_bool				Bool_NotAnd(t_bool a, t_bool b);
#define c_nand		Bool_NotAnd
#define Bool_NAnd	Bool_NotAnd
//!@}

//!@doc Boolean operator: ⋁	(or)
//!@{
t_bool				Bool_Or(t_bool a, t_bool b);
#define c_or		Bool_Or
//!@}

//!@doc Boolean operator: ⊽	(not or)
//!@{
t_bool				Bool_NotOr(t_bool a, t_bool b);
#define c_nor		Bool_NotOr
#define Bool_NOr	Bool_NotOr
//!@}

//!@doc Boolean operator: ⊻	(exclusive or)
//!@{
t_bool				Bool_ExOr(t_bool a, t_bool b);
#define c_xor		Bool_ExOr
#define Bool_XOr	Bool_ExOr
#define Bool_NEq	Bool_ExOr
//!@}

//!@doc Boolean operator: ⇔	(equivalence)
//!@{
t_bool				Bool_Equiv(t_bool a, t_bool b);
#define c_eq		Bool_Equiv
#define Bool_Eq		Bool_Equiv
//!@}

//!@doc Boolean operator: ⇒	(implication)
//!@{
t_bool					Bool_Imply(t_bool a, t_bool b);
#define c_imply			Bool_Imply
#define Bool_RArrow		Bool_Imply
//!@}

//!@doc Boolean operator: ⇏	(not implication)
//!@{
t_bool					Bool_NotImply(t_bool a, t_bool b);
#define c_nimply		Bool_NotImply
#define Bool_NRArrow	Bool_NotImply
#define Bool_NotRArrow	Bool_NotImply
//!@}

//!@doc Boolean operator: ⇐	(necessity)
//!@{
t_bool					Bool_Needs(t_bool a, t_bool b);
#define c_needs			Bool_Needs
#define Bool_LArrow		Bool_Needs
//!@}

//!@doc Boolean operator: ⇍	(not necessity)
//!@{
t_bool					Bool_NotNeeds(t_bool a, t_bool b);
#define c_nneeds		Bool_NotNeeds
#define Bool_NLArrow	Bool_NotNeeds
#define Bool_NotLArrow	Bool_NotNeeds
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
