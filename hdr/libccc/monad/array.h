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
**	This header defines a generic linked list type and utility functions for it.
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

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
#endif

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

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

//! Returns an array which consists of `n` items, initialized with variadic arguments.
/*!
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: there must be `n` arguments, of type `T`
**	@returns
**	An array containing `n` elements (the given `...` varargs)
*/
_GENERIC()
s_array_T			CONCAT(Array,T_NAME)(t_uint n, ...);
#define c_arr		CONCAT(Array,T_NAME)

//! Allocates a new array which consists of `n` items, initialized with variadic arguments.
/*!
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: there must be `n` arguments, of type `T`
**	@returns
**	A newly allocated array containing `n` elements (the given `...` varargs)
*/
_GENERIC()
s_array_T*			CONCAT(Array_New,T_NAME)(t_uint n, ...);
#define c_arrnew	CONCAT(Array_New,T_NAME)



//! Deletes the allocated buffer contained within the given `array` (frees and sets to NULL)
/*!
**	@param	array	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
*/
_GENERIC()
void				CONCAT(Array_Delete,T_NAME)(s_array_T* array);
#define c_arrdel	CONCAT(Array_Delete,T_NAME)

//! Deletes the allocated buffer contained within the given `array` (frees and sets to NULL)
/*!
**	@param	array	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
**	@param	delete	the function which should be executed for each item before deletion.
*/
_GENERIC()
void				CONCAT(Array_Delete_F,T_NAME)(s_array_T* array, void (*delete)(T* item));
#define c_arrfdel	CONCAT(Array_Delete_F,T_NAME)



//! Returns a newly allocated copy of the given `list`
/*!
**	@param	array	The list to duplicate
**	@returns
**	A newly allocated copy of the given linked `list`.
*/
_GENERIC()
s_array_T			CONCAT(Array_Duplicate,T_NAME)(s_array_T const* array);
#define c_arrdup	CONCAT(Array_Duplicate,T_NAME)



//! TODO document this
_GENERIC()
T					CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index);
#define c_arrget	CONCAT(Array_Get,T_NAME)

//! TODO document this
_GENERIC()
void				CONCAT(Array_Set,T_NAME)(s_array_T* array, t_uint index, T item);
#define c_arrset	CONCAT(Array_Set,T_NAME)

//! TODO document this
_GENERIC()
s_array_T*			CONCAT(Array_Copy,T_NAME)(s_array_T* dest, s_array_T const* src, t_uint n);
#define c_arrcpy	CONCAT(Array_Copy,T_NAME)

//! TODO document this
_GENERIC()
s_array_T			CONCAT(Array_Sub,T_NAME)(s_array_T const* array, t_uint index, t_uint n);
#define c_arrsub	CONCAT(Array_Sub,T_NAME)



/*
** ************************************************************************** *|
**                           Array Editing Operations                         *|
** ************************************************************************** *|
*/

//! TODO document this
_GENERIC()
void					CONCAT(Array_Append,T_NAME)(s_array_T* array, T item);
#define c_arrappend		CONCAT(Array_Append,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_Prepend,T_NAME)(s_array_T* array, T item);
#define c_arrprepend	CONCAT(Array_Prepend,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_Insert,T_NAME)(s_array_T* array, T item, t_uint index);
#define c_arrinsert		CONCAT(Array_Insert,T_NAME)



//! TODO document this
_GENERIC()
void					CONCAT(Array_Remove,T_NAME)(s_array_T* array, T item);
#define c_arrdelone		CONCAT(Array_Remove,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_Remove_F,T_NAME)(s_array_T* array, T item, void (*delete)(T));
#define c_arrfdelone	CONCAT(Array_Remove_F,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_RemoveAll,T_NAME)(s_array_T* array, T item);
#define c_arrdelall		CONCAT(Array_RemoveAll,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_RemoveAll_F,T_NAME)(s_array_T* array, T item, void (*delete)(T));
#define c_arrfdelall	CONCAT(Array_RemoveAll_F,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_RemoveAt,T_NAME)(s_array_T* array, t_uint index);
#define c_arrdelat		CONCAT(Array_RemoveAt,T_NAME)

//! TODO document this
_GENERIC()
void					CONCAT(Array_RemoveAt_F,T_NAME)(s_array_T* array, t_uint index, void (*delete)(T));
#define c_arrfdelat		CONCAT(Array_RemoveAt_F,T_NAME)



//! TODO document this
_GENERIC()
s_array_T				CONCAT(Array_Replace,T_NAME)(s_array_T const* array, T old, T new);
#define c_arrrep		CONCAT(Array_Replace,T_NAME)
#define c_arrreplace	CONCAT(Array_Replace,T_NAME)



/*
** ************************************************************************** *|
**                           Array Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO document this
_GENERIC()
T*					CONCAT(Array_Find,T_NAME)(s_array_T const* array, T item);
#define c_arrfind	CONCAT(Array_Find,T_NAME)

//! TODO document this
_GENERIC()
T*					CONCAT(Array_Find_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item));
#define c_arrffind	CONCAT(Array_Find_F,T_NAME)

//! TODO document this
_GENERIC()
t_sint				CONCAT(Array_IndexOf,T_NAME)(s_array_T const* array, T item);
#define c_arrfindi	CONCAT(Array_IndexOf,T_NAME)

//! TODO document this
_GENERIC()
t_sint				CONCAT(Array_IndexOf_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item));
#define c_arrffindi	CONCAT(Array_IndexOf_F,T_NAME)



//! TODO document this
_GENERIC()
t_uint					CONCAT(Array_Count,T_NAME)	(s_array_T const* array, T item);
#define c_arrcount		CONCAT(Array_Count,T_NAME)

//! TODO document this
_GENERIC()
t_bool					CONCAT(Array_Contains,T_NAME)(s_array_T const* array, T item);
#define c_arrcontains	CONCAT(Array_Contains,T_NAME)

//! TODO document this
_GENERIC()
t_bool					CONCAT(Array_Has,T_NAME)	(s_array_T const* array, s_array_T const* target);
#define c_arrhas		CONCAT(Array_Has,T_NAME)

//! TODO document this
_GENERIC()
t_bool					CONCAT(Array_HasOnly,T_NAME)(s_array_T const* array, s_array_T const* target);
#define c_arrhasonly	CONCAT(Array_HasOnly,T_NAME)



//! TODO document this
_GENERIC()
t_bool				CONCAT(Array_Equals,T_NAME)		(s_array_T const* array1, s_array_T const* array2);
#define c_arrequ	CONCAT(Array_Equals,T_NAME)

//! TODO document this
_GENERIC()
t_bool				CONCAT(Array_Equals_N,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_uint n);
#define c_arrnequ	CONCAT(Array_Equals_N,T_NAME)

//! TODO document this
_GENERIC()
t_sint				CONCAT(Array_Compare,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	CONCAT(Array_Compare,T_NAME)

//! TODO document this
_GENERIC()
t_sint				CONCAT(Array_Compare_N,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_arrncmp	CONCAT(Array_Compare_N,T_NAME)



/*
** ************************************************************************** *|
**                          Array Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO document this
_GENERIC()
void				CONCAT(Array_Iterate,T_NAME)	(s_array_T* array, void (*f)(T item));
#define c_arriter	CONCAT(Array_Iterate,T_NAME)

_GENERIC()
void				CONCAT(Array_Iterate_I,T_NAME)	(s_array_T* array, void (*f)(T item, t_uint index));
#define c_arriteri	CONCAT(Array_Iterate_I,T_NAME)



//! TODO document this
_GENERIC()
s_array_T			CONCAT(Array_Map,T_NAME)		(s_array_T const* array, T (*map)(T item));
#define c_arrmap	CONCAT(Array_Map,T_NAME)

_GENERIC()
s_array_T			CONCAT(Array_Map_I,T_NAME)		(s_array_T const* array, T (*map)(T item, t_uint index));
#define c_arrmapi	CONCAT(Array_Map_I,T_NAME)



//! TODO document this
_GENERIC()
s_array_T			CONCAT(Array_Filter,T_NAME)		(s_array_T const* array, t_bool (*filter)(T item));
#define c_arrfilt	CONCAT(Array_Filter,T_NAME)

_GENERIC()
s_array_T			CONCAT(Array_Filter_I,T_NAME)	(s_array_T const* array, t_bool (*filter)(T item, t_uint index));
#define c_arrfilti	CONCAT(Array_Filter_I,T_NAME)



//! TODO Array_Reduce() ?



/*! @} */
HEADER_END
#endif
