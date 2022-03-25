/*============================================================================*\
||                                            ______________________________  ||
||  libccc/enum.h                            |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_ENUM_H
#define __LIBCCC_ENUM_H
/*!@group{libccc_enum,11,libccc/enum.h}
**
**	This header defines several utility functions and macros for enumerations.
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_ENUM_T
#define __LIBCCC_ENUM_T

/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

//!@doc This type is used to represent any enum as a generic integer
typedef int	t_enum;

//!@doc This struct holds relevant information for a single enum item
/*!
**	This struct can be useful to store info for a single enum item
*/
//!@{
typedef struct enum_item
{
	t_enum			value;	//!< The enum item's integer value
	t_char const*	name;	//!< The enum item's string name
	t_char const*	description;
}	s_enum_item;
//!@}

//!@doc This struct holds relevant information for an enum type
/*!
**	This struct can be useful to store info for an enum type
*/
//!@{
typedef struct enum_type
{
	t_char const*		name;	//!< The enum type name
	s_enum_item const*	items;	//!< The array of enum items
	t_uint				length;	//!< The amount of enum items in `.items`
}	s_enum_type;
//!@}



#endif
#ifndef __LIBCCC_ENUM_F
#define __LIBCCC_ENUM_F

/*
** ************************************************************************** *|
**                              Utility Functions                             *|
** ************************************************************************** *|
*/

//!@doc Get the string representation of an enum value
//!@{
t_char const*			Enum_String(t_enum value, s_enum_type const* enum_type);
#define c_enumstr		Enum_String
//!@}

//!@doc Write the string representation of an enum value to the `dest` buffer
//!@{
t_size					Enum_Print(t_char* dest, t_enum value, s_enum_type const* enum_type);
#define c_enumprint		Enum_Print
//!@}

//!@doc Get a newly allocated string representation of an enum value
//!@{
_MALLOC()
t_char*					Enum_ToString(t_enum value, s_enum_type const* enum_type);
#define c_enumtostr		Enum_ToString
//!@}



//!@doc Parse an enum value from the given string
//!@{
t_size					Enum_Parse(t_enum *dest, t_size n, t_char const* str, s_enum_type const* enum_type);
#define c_enumparse		Enum_Parse
//!@}

//!@doc Parse an enum value from the given string
//!@{
t_enum					Enum_FromString(t_char const* str, s_enum_type const* enum_type);
#define c_strtoenum		Enum_FromString
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
