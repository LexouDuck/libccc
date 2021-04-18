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

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#ifdef	array_T
#undef	array_T
#define array_T		CONCAT(array, TYPE)
#endif

#ifdef	s_array_T
#undef	s_array_T
#define s_array_T	CONCAT(s_array, TYPE)
#endif

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

//! A literal of an 's_array' struct which has all fields set to zero
#define ARRAY_NULL	(s_array_T){ .length = 0, .items = NULL }



#define foreach_s_array_init(		_TYPE_, _VAR_, _ARRAY_)	t_size _VAR_##_i = 0;
#define foreach_s_array_exit(		_TYPE_, _VAR_, _ARRAY_)	if (_ARRAY_ && (_ARRAY_)->items)
#define foreach_s_array_loop_init(	_TYPE_, _VAR_, _ARRAY_)	_TYPE_ _VAR_ = (_TYPE_)((_ARRAY_)->items[0])
#define foreach_s_array_loop_exit(	_TYPE_, _VAR_, _ARRAY_)	_VAR_##_i < (_ARRAY_)->length
#define foreach_s_array_loop_incr(	_TYPE_, _VAR_, _ARRAY_)	++_VAR_##_i, _VAR_ = (_TYPE_)((_ARRAY_)->items[_VAR_##_i])



/*
** ************************************************************************** *|
**                            Basic Array Operations                          *|
** ************************************************************************** *|
*/

//! TODO
s_array_T*			Array_New(T* content);
#define c_arrnew	Array_New

//! TODO
void				Array_Delete(s_array_T* *array);
#define c_arrdel	Array_Delete

//! TODO
s_array_T*			Array_Duplicate(s_array_T* array);
#define c_arrdup	Array_Duplicate




//! TODO
T					Array_Get(s_array_T* array, t_size index);
#define c_arrget	Array_Get

//! TODO
void				Array_Set(s_array_T* array, t_size index, T item);
#define c_arrset	Array_Set

//! TODO
void				Array_Copy(s_array_T* dest, s_array_T* src, t_size n);
#define c_arrcpy	Array_Copy



//! TODO
void					Array_Append(s_array_T* array, T item);
#define c_arrappend		Array_Append

//! TODO
void					Array_Prepend(s_array_T* array, T item);
#define c_arrprepend	Array_Prepend

//! TODO
void					Array_Insert(s_array_T* array, T item, t_size index);
#define c_arrinsert		Array_Insert



//! TODO
t_bool				Array_Equals(s_array_T* array1, s_array_T* array2);
#define c_arrequ	Array_Equals

//! TODO
t_bool				Array_Equals_N(s_array_T* array1, s_array_T* array2, t_size n);
#define c_arrnequ	Array_Equals_N

//! TODO
t_sint				Array_Compare(s_array_T* array1, s_array_T* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	Array_Compare

//! TODO
t_sint				Array_Compare_N(s_array_T* array1, s_array_T* array2, t_sint (*compare)(T item1, T item2), t_size n);
#define c_arrncmp	Array_Compare_N



//! TODO
s_array_T*			Array_Replace(s_array_T* array, T old, T new);
#define c_arrrep	Array_Replace

//! TODO
T*					Array_Find(s_array_T* array, T item);
#define c_arrfind	Array_Find

//! TODO
t_size				Array_IndexOf(s_array_T* array, T item);
#define c_arrfindi	Array_IndexOf



//! TODO
void				Array_Iterate	(s_array_T* array, T (*iterate)(T item));
#define c_arriter	Array_Iterate
void				Array_Iterate_I	(s_array_T* array, T (*iterate)(T item, t_size index));
#define c_arriteri	Array_Iterate_I

//! TODO
s_array_T*			Array_Map		(s_array_T* array, T (*map)(T item));
#define c_arrmap	Array_Map
s_array_T*			Array_Map_I		(s_array_T* array, T (*map)(T item, t_size index));
#define c_arrmapi	Array_Map_I

//! TODO
s_array_T*			Array_Filter	(s_array_T* array, t_bool (*filter)(T item));
#define c_arrfold	Array_Filter
s_array_T*			Array_Filter_I	(s_array_T* array, t_bool (*filter)(T item, t_size index));
#define c_arrfoldi	Array_Filter_I



/*! @} */
HEADER_END
#endif
