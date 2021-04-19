/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/array.h                     |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_ARRAY_H
#define __LIBCCC_MONAD_ARRAY_H
/*!@group{libccc_monad_array}
** @{
**	This header defines a simple linked list type and utility functions for it.
**
**	@file
*/

#ifndef T
#define T	void*
#endif

#ifndef TYPE
#define TYPE	
#endif

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <stdarg.h>

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#ifdef	Array_T
#undef	Array_T
#endif
#define Array_T		CONCAT(Array, TYPE)

#ifdef	array_T
#undef	array_T
#endif
#define array_T		CONCAT(array, TYPE)

#ifdef	s_array_T
#undef	s_array_T
#endif
#define s_array_T	CONCAT(s_array, TYPE)

//! This struct holds an array of items which can be of any type
/*!
**	The 's_array' struct holds a `void*` pointer to the array of items, the size
**	of a single item in the array, and the total amount of items in this array.
**	As such, a s_array can hold any number of items, but they must all share the same type.
*/
typedef struct array_T
{
	t_size	length;	//!< The amount of elements in the 'items' array
	T*		items;	//!< The pointer to the array (items can be of any one type)
}				s_array_T;
TYPEDEF_ALIAS(	s_array_T, ARRAY, STRUCT)



#define foreach_s_array_init(		_TYPE_, _VAR_, _ARRAY_)	t_size _VAR_##_i = 0;
#define foreach_s_array_exit(		_TYPE_, _VAR_, _ARRAY_)	if (_ARRAY_ && (_ARRAY_)->items)
#define foreach_s_array_loop_init(	_TYPE_, _VAR_, _ARRAY_)	_TYPE_ _VAR_
#define foreach_s_array_loop_exit(	_TYPE_, _VAR_, _ARRAY_)	(_VAR_##_i < (_ARRAY_)->length) && ((_VAR_ = (_TYPE_)((_ARRAY_)->items[_VAR_##_i])) || 1)
#define foreach_s_array_loop_incr(	_TYPE_, _VAR_, _ARRAY_)	++_VAR_##_i



/*
** ************************************************************************** *|
**                            Basic Array Operations                          *|
** ************************************************************************** *|
*/

//! TODO
_MALLOC()
s_array_T*			CONCAT(Array_T,_New)(t_uint n, ...);
#define c_arrnew	CONCAT(Array_T,_New)

//! TODO
void				CONCAT(Array_T,_Delete)(s_array_T* *a_array);
#define c_arrdel	CONCAT(Array_T,_Delete)

//! TODO
_MALLOC()
s_array_T*			CONCAT(Array_T,_Duplicate)(s_array_T const* array);
#define c_arrdup	CONCAT(Array_T,_Duplicate)



//! TODO
T					CONCAT(Array_T,_Get)(s_array_T const* array, t_size index);
#define c_arrget	CONCAT(Array_T,_Get)

//! TODO
void				CONCAT(Array_T,_Set)(s_array_T* array, t_size index, T item);
#define c_arrset	CONCAT(Array_T,_Set)

//! TODO
s_array_T*			CONCAT(Array_T,_Copy)(s_array_T* dest, s_array_T const* src, t_size n);
#define c_arrcpy	CONCAT(Array_T,_Copy)

//! TODO
_MALLOC()
s_array_T*					CONCAT(Array_T,_Sub)(s_array_T const* array, T item);
#define c_arrsub			CONCAT(Array_T,_Sub)



/*
** ************************************************************************** *|
**                           Array Editing Operations                         *|
** ************************************************************************** *|
*/

//! TODO
void					CONCAT(Array_T,_Append)(s_array_T* array, T item);
#define c_arrappend		CONCAT(Array_T,_Append)

//! TODO
void					CONCAT(Array_T,_Prepend)(s_array_T* array, T item);
#define c_arrprepend	CONCAT(Array_T,_Prepend)

//! TODO
void					CONCAT(Array_T,_Insert)(s_array_T* array, T item, t_size index);
#define c_arrinsert		CONCAT(Array_T,_Insert)



//! TODO
void					CONCAT(Array_T,_Remove)(s_array_T* array, t_size index);
#define c_arrremove		CONCAT(Array_T,_Remove)
#define c_arrdelone		CONCAT(Array_T,_Remove)

//! TODO
void					CONCAT(Array_T,_RemoveAll)(s_array_T* array, T target);
#define c_arrremall		CONCAT(Array_T,_RemoveAll)
#define c_arrdelall		CONCAT(Array_T,_RemoveAll)



//! TODO
_MALLOC()
s_array_T*				CONCAT(Array_T,_Replace)(s_array_T const* array, T old, T new);
#define c_arrrep		CONCAT(Array_T,_Replace)
#define c_arrreplace	CONCAT(Array_T,_Replace)



/*
** ************************************************************************** *|
**                           Array Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO
T*					CONCAT(Array_T,_Find)		(s_array_T const* array, T item);
#define c_arrfind	CONCAT(Array_T,_Find)

//! TODO
t_size				CONCAT(Array_T,_IndexOf)	(s_array_T const* array, T item);
#define c_arrfindi	CONCAT(Array_T,_IndexOf)



//! TODO
t_bool				CONCAT(Array_T,_Equals)		(s_array_T const* array1, s_array_T const* array2);
#define c_arrequ	CONCAT(Array_T,_Equals)

//! TODO
t_bool				CONCAT(Array_T,_Equals_N)	(s_array_T const* array1, s_array_T const* array2, t_size n);
#define c_arrnequ	CONCAT(Array_T,_Equals_N)

//! TODO
t_sint				CONCAT(Array_T,_Compare)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	CONCAT(Array_T,_Compare)

//! TODO
t_sint				CONCAT(Array_T,_Compare_N)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_size n);
#define c_arrncmp	CONCAT(Array_T,_Compare_N)



/*
** ************************************************************************** *|
**                          Array Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO
void				CONCAT(Array_T,_Iterate)	(s_array_T* array, void (*f)(T item));
#define c_arriter	CONCAT(Array_T,_Iterate)

void				CONCAT(Array_T,_Iterate_I)	(s_array_T* array, void (*f)(T item, t_size index));
#define c_arriteri	CONCAT(Array_T,_Iterate_I)



//! TODO
_MALLOC()
s_array_T*			CONCAT(Array_T,_Map)		(s_array_T const* array, T (*map)(T item));
#define c_arrmap	CONCAT(Array_T,_Map)

_MALLOC()
s_array_T*			CONCAT(Array_T,_Map_I)		(s_array_T const* array, T (*map)(T item, t_size index));
#define c_arrmapi	CONCAT(Array_T,_Map_I)



//! TODO
_MALLOC()
s_array_T*			CONCAT(Array_T,_Filter)		(s_array_T const* array, t_bool (*filter)(T item));
#define c_arrfilt	CONCAT(Array_T,_Filter)

_MALLOC()
s_array_T*			CONCAT(Array_T,_Filter_I)	(s_array_T const* array, t_bool (*filter)(T item, t_size index));
#define c_arrfilti	CONCAT(Array_T,_Filter_I)


//! TODO CONCAT(Array_T,_Reduce) ?



/*! @} */
HEADER_END
#endif
