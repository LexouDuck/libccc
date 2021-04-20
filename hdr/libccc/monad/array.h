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
#ifndef T_NAME
#define T_NAME	
#endif
#ifndef T_DEFAULT
#define T_DEFAULT	NULL
#endif
#ifndef T_EQUALS
#define T_EQUALS(A, B)	((A) == (B))
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

#define Array_T		CONCAT(Array, T_NAME)
#define array_T		CONCAT(array, T_NAME)
#define s_array_T	CONCAT(s_array, T_NAME)

//! This struct holds an array of items which can be of any type
/*!
**	The 's_array' struct holds a `void*` pointer to the array of items, the size
**	of a single item in the array, and the total amount of items in this array.
**	As such, a s_array can hold any number of items, but they must all share the same type.
*/
typedef struct array_T
{
	t_uint	length;	//!< The amount of elements in the 'items' array
	T*		items;	//!< The pointer to the array (items can be of any one type)
}			s_array_T;



#define foreach_s_array(_TYPE_, _VAR_, _ARRAY_)		foreach (_TYPE_, _VAR_, s_array, _ARRAY_)

#define foreach_s_array_init(		_TYPE_, _VAR_, _ARRAY_)	t_uint _VAR_##_i = 0;
#define foreach_s_array_exit(		_TYPE_, _VAR_, _ARRAY_)	if ((void*)(_ARRAY_) != NULL && (_ARRAY_)->items != NULL)
#define foreach_s_array_loop_init(	_TYPE_, _VAR_, _ARRAY_)	_TYPE_ _VAR_ = (_ARRAY_)->items[_VAR_##_i]
#define foreach_s_array_loop_exit(	_TYPE_, _VAR_, _ARRAY_)	(_VAR_##_i < (_ARRAY_)->length)
#define foreach_s_array_loop_incr(	_TYPE_, _VAR_, _ARRAY_)	++_VAR_##_i
#define foreach_s_array_loop_setv(	_TYPE_, _VAR_, _ARRAY_)	_VAR_ = (_VAR_##_i == (_ARRAY_)->length ? _VAR_ : (_ARRAY_)->items[_VAR_##_i])



/*
** ************************************************************************** *|
**                            Basic Array Operations                          *|
** ************************************************************************** *|
*/

//! Allocates a new array which consists of `n` items.
/*!
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: there must be `n` arguments, of type `T`
**	@returns a newly allocated linked list which consists of `n` structs chained together.
*/
s_array_T			CONCAT(Array_T,_New)(t_uint n, ...);
#define c_arrnew	CONCAT(Array_T,_New)

//! Deletes the allocated buffer contained within the given `array` (frees and sets to NULL)
/*!
**	@param	array	The array whose `items` buffer should be deleted - its `length` will be set to 0
*/
void				CONCAT(Array_T,_Delete)(s_array_T* array);
#define c_arrdel	CONCAT(Array_T,_Delete)

//! Returns a newly allocated copy of the given `list`
/*!
**	@param	array	The list to duplicate
**	@returns a newly allocated copy of the given linked `list`.
*/
s_array_T			CONCAT(Array_T,_Duplicate)(s_array_T const* array);
#define c_arrdup	CONCAT(Array_T,_Duplicate)



//! TODO
T					CONCAT(Array_T,_Get)(s_array_T const* array, t_uint index);
#define c_arrget	CONCAT(Array_T,_Get)

//! TODO
void				CONCAT(Array_T,_Set)(s_array_T* array, t_uint index, T item);
#define c_arrset	CONCAT(Array_T,_Set)

//! TODO
s_array_T*			CONCAT(Array_T,_Copy)(s_array_T* dest, s_array_T const* src, t_uint n);
#define c_arrcpy	CONCAT(Array_T,_Copy)

//! TODO
s_array_T			CONCAT(Array_T,_Sub)(s_array_T const* array, t_uint index, t_uint n);
#define c_arrsub	CONCAT(Array_T,_Sub)



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
void					CONCAT(Array_T,_Insert)(s_array_T* array, T item, t_uint index);
#define c_arrinsert		CONCAT(Array_T,_Insert)



//! TODO
void					CONCAT(Array_T,_Remove)(s_array_T* array, t_uint index);
#define c_arrremove		CONCAT(Array_T,_Remove)
#define c_arrdelone		CONCAT(Array_T,_Remove)

//! TODO
void					CONCAT(Array_T,_RemoveAll)(s_array_T* array, T target);
#define c_arrremall		CONCAT(Array_T,_RemoveAll)
#define c_arrdelall		CONCAT(Array_T,_RemoveAll)



//! TODO
s_array_T				CONCAT(Array_T,_Replace)(s_array_T const* array, T old, T new);
#define c_arrrep		CONCAT(Array_T,_Replace)
#define c_arrreplace	CONCAT(Array_T,_Replace)



/*
** ************************************************************************** *|
**                           Array Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO
T*					CONCAT(Array_T,_Find)(s_array_T const* array, T item);
#define c_arrfind	CONCAT(Array_T,_Find)

//! TODO
t_sint				CONCAT(Array_T,_IndexOf)(s_array_T const* array, T item);
#define c_arrfindi	CONCAT(Array_T,_IndexOf)



// TODO Array_Contains
// TODO Array_Has
// TODO Array_HasOnly



//! TODO
t_bool				CONCAT(Array_T,_Equals)		(s_array_T const* array1, s_array_T const* array2);
#define c_arrequ	CONCAT(Array_T,_Equals)

//! TODO
t_bool				CONCAT(Array_T,_Equals_N)	(s_array_T const* array1, s_array_T const* array2, t_uint n);
#define c_arrnequ	CONCAT(Array_T,_Equals_N)

//! TODO
t_sint				CONCAT(Array_T,_Compare)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	CONCAT(Array_T,_Compare)

//! TODO
t_sint				CONCAT(Array_T,_Compare_N)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_arrncmp	CONCAT(Array_T,_Compare_N)



/*
** ************************************************************************** *|
**                          Array Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO
void				CONCAT(Array_T,_Iterate)	(s_array_T* array, void (*f)(T item));
#define c_arriter	CONCAT(Array_T,_Iterate)

void				CONCAT(Array_T,_Iterate_I)	(s_array_T* array, void (*f)(T item, t_uint index));
#define c_arriteri	CONCAT(Array_T,_Iterate_I)



//! TODO
s_array_T			CONCAT(Array_T,_Map)		(s_array_T const* array, T (*map)(T item));
#define c_arrmap	CONCAT(Array_T,_Map)

s_array_T			CONCAT(Array_T,_Map_I)		(s_array_T const* array, T (*map)(T item, t_uint index));
#define c_arrmapi	CONCAT(Array_T,_Map_I)



//! TODO
s_array_T			CONCAT(Array_T,_Filter)		(s_array_T const* array, t_bool (*filter)(T item));
#define c_arrfilt	CONCAT(Array_T,_Filter)

s_array_T			CONCAT(Array_T,_Filter_I)	(s_array_T const* array, t_bool (*filter)(T item, t_uint index));
#define c_arrfilti	CONCAT(Array_T,_Filter_I)


//! TODO CONCAT(Array_T,_Reduce) ?



/*! @} */
HEADER_END
#endif
