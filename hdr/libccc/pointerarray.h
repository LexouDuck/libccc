/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/pointerarray.h              |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_POINTERARRAY_H
#define __LIBCCC_POINTERARRAY_H
/*!@group{libccc_pointerarray}
** @{
**	This header defines the common standard memory manipulation functions.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"
#include "libccc/char.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



/*
** ************************************************************************** *|
**                          Pointer Array Operations                          *|
** ************************************************************************** *|
*/

/*!
**	Returns a newly allocated memory array to serve as a null-terminated
**	pointer array of length 'n'. Returns NULL if memory allocation fails.
*/
_MALLOC()
void**				PointerArray_New(t_size size);
#define c_ptrarrnew	PointerArray_New

/*!
**	Returns the length of a null-terminated pointer array.
*/
t_u32				PointerArray_Length(void const** a_ptrarr);
#define c_ptrarrlen	PointerArray_Length

// TODO ptrarrdup //needs a function pointer to dup internals

// TODO ptrarrsub

// TODO ptrarrmerge
// TODO ptrarrappend
// TODO ptrarrprepend
// TODO ptrarrmap
// TODO ptrarrfilter
// TODO ptrarrfold



/*! @} */
HEADER_END
#endif
