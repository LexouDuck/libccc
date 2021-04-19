/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/convert.h                   |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_CONVERT_H
#define __LIBCCC_MONAD_CONVERT_H
/*!@group{libccc_monad_convert}
** @{
**	This header defines a simple tree/node/leaf type and utility functions for it.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"
#include "libccc/monad/array.h"
#include "libccc/monad/list.h"
#include "libccc/monad/dict.h"
#include "libccc/monad/tree.h"
#include "libccc/monad/object.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



/*
** ************************************************************************** *|
**                              Array Conversions                             *|
** ************************************************************************** *|
*/

// TODO Array_ToList
// TODO Array_ToPointerArray



/*
** ************************************************************************** *|
**                              List Conversions                              *|
** ************************************************************************** *|
*/

//! Converts the given list at address `a_lst` to a array
/*!
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the `items` pointer of the given `array`.
**	It also sets the `item_size` and `length` fields of this `array`.
**
**	@returns the resulting `s_array` struct from the given list, or NULL
**		if any elements of `*a_lst` are of unequal `lst.item_size`.
*/
s_array					List_To_Array(s_list const** a_lst);
#define c_lst_to_array	List_To_Array

//! Converts the given list at address `a_lst` to a NULL-terminated pointer array
/*!
**	Creates a new jagged array (2D pointer array) from the given list `*a_lst`.
**	The top-level pointer array is terminated by a NULL pointer.
**	The underlying `lst.item` data is not copied, only the pointers are.
*/
_MALLOC()
void**					List_To_PointerArray(s_list const** a_lst);
#define c_lst_to_ptrarr	List_To_PointerArray



/*! @} */
HEADER_END
#endif
