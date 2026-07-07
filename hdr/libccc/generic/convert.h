/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/convert.h                 |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_CONVERT_H
#define __LIBCCC_GENERIC_CONVERT_H
/*!@group{libccc_generic_convert,39,libccc/generic/convert.h}
**
**	This header defines conversions functions between the generic generic types.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/generic/convert.c"

#include "libccc/generic/array.h"
#include "libccc/generic/list.h"

//! NOTE: this header declares cross-type generic functions, which requires the
//! foreign type macros (`s_array`, `s_list`) to be in "declaration" form (ie:
//! `X##_NAME` suffixing), regardless of which form they are currently in (they
//! will be in their user-facing form if the array/list generic import files
//! were already fully included beforehand, within this translation unit).
//!@{
#undef	s_array
#undef	s_list
#define	s_array(X)	CONCAT(s_array_,	X##_NAME)
#define	s_list(X)	CONCAT(s_list_,	X##_NAME)
//!@}

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

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



/*============================================================================*\
||                              Array Conversions                             ||
\*============================================================================*/

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
_MALLOC()
_GENERIC()
s_list(T)*					Array_ToList(T)(s_array(T) const* array);
#define c_arrtolst(T)		Array_ToList(T)
//!@}



/*============================================================================*\
||                               List Conversions                             ||
\*============================================================================*/

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
_MALLOC()
_GENERIC()
s_array(T)*					List_ToArray(T)(s_list(T) const* list);
#define c_lsttoarr(T)		List_ToArray(T)
//!@}



//! NOTE: restore the foreign type macros to their normal user-facing form
//!@{
#undef	s_array
#undef	s_list
#define	s_array(T)	CONCAT(s_array_,	T)
#define	s_list(T)	CONCAT(s_list_,	T)
//!@}

/*! @endgroup */
HEADER_END
#endif
