/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/convert.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_CONVERT_H
#define __LIBCCC_MONAD_CONVERT_H
/*!@group{libccc_monad_convert}
**
**	This header defines conversions functions between the generic monad types.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/convert.c"

#include "libccc/monad/array.h"
#include "libccc/monad/list.h"
#include "libccc/monad/dict.h"
#include "libccc/monad/tree.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*!
**	Monadic compound storage types:
**	`Array`  indexed contiguous storage (fast access, slow for size-changes)
**	`List`   indexed fragmented storage (slow access, fast for size-changes)
**	`Hash`   unordered bucket-like storage (fast, slightly more memory-hungry) TODO
**	`KeyVal` key+value pair (simple struct with a string and value)
**	`Dict`   named storage (configurable) TODO
**	`Dict<Array>`	?
**	`Dict<List>`	?
**	`Dict<Hash>`	?
**	`Tree`   nested storage (configurable) TODO
**	`Tree<Array>`	?
**	`Tree<List>`	?
**	`Tree<Hash>`	?
*/



/*
** ************************************************************************** *|
**                              Array Conversions                             *|
** ************************************************************************** *|
*/

// TODO: s_list(T)*	Array_ToList(s_array(T) const* array);
// TODO: void**		Array_ToPointerArray(s_array(T) const* array);



/*
** ************************************************************************** *|
**                               List Conversions                             *|
** ************************************************************************** *|
*/

//! Converts the given `list` to an array
/*!
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the `items` pointer of the given `array`.
**	It also sets the `item_size` and `length` fields of this `array`.
**
**	@returns
**	The resulting `s_array` struct converted from the given list,
**	or `NULL` if an error occurred.
*/
s_array(T)*				List_ToArray(s_list(T) const* list);
#define c_lst_to_array	List_ToArray

//! Converts the given `list` to a NULL-terminated pointer array
/*!
**	Creates a new jagged array (2D pointer array) from the given list `*a_lst`.
**	The top-level pointer array is terminated by a NULL pointer.
**	The underlying `lst.item` data is not copied, only the pointers are.
**
**	@returns
**	The resulting pointer array converted from the given list,
**	or `NULL` if an error occurred.
*/
_MALLOC()
void**					List_ToPointerArray(s_list(T) const* list);
#define c_lst_to_ptrarr	List_ToPointerArray



/*! @endgroup */
HEADER_END
#endif
