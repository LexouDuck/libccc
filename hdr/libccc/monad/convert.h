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
/*!@group{libccc_monad_convert,39,libccc/monad/convert.h}
**
**	This header defines conversions functions between the generic monad types.
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

//!@doc Creates a new linked list, converted from the given `array`
/*!
**	Creates a new linked list chain, by copying each item of the given `array`.
**
**	@returns
**	The pointer to the first `s_list` struct in the chain which constitutes the
**	resulting linked list, converted from the given array,
**	or `NULL` if an error occurred.
*/
//!@{
s_list(T)*					Array_ToList(T)(s_array(T) const* array);
#define c_arrtolst(T)		Array_ToList(T)



/*
** ************************************************************************** *|
**                               List Conversions                             *|
** ************************************************************************** *|
*/

//!@doc Creates a new generic array, converted from the given `list`
/*!
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the `items` pointer of the given `array`.
**	It also sets the `item_size` and `length` fields of this `array`.
**
**	@returns
**	The resulting `s_array` struct converted from the given list,
**	or `NULL` if an error occurred.
*/
//!@{
s_array(T)*					List_ToArray(T)(s_list(T) const* list);
#define c_lsttoarr(T)		List_ToArray(T)
//!@}



/*! @endgroup */
HEADER_END
#endif
