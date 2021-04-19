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
s_array_T*			Array_New(T* content);
#define c_arrnew	Array_New //!< @alias{Array_New}

//! TODO
void				Array_Delete(s_array_T* *a_array);
#define c_arrdel	Array_Delete //!< @alias{Array_Delete}

//! TODO
_MALLOC()
s_array_T*			Array_Duplicate(s_array_T const* array);
#define c_arrdup	Array_Duplicate //!< @alias{Array_Duplicate}



//! TODO
T					Array_Get(s_array_T const* array, t_size index);
#define c_arrget	Array_Get //!< @alias{Array_Get}

//! TODO
void				Array_Set(s_array_T* array, t_size index, T item);
#define c_arrset	Array_Set //!< @alias{Array_Set}

//! TODO
s_array_T*			Array_Copy(s_array_T* dest, s_array_T const* src, t_size n);
#define c_arrcpy	Array_Copy //!< @alias{Array_Copy}

//! TODO
_MALLOC()
s_array_T*					Array_Sub(s_array_T const* array, T item);
#define c_arrsub			Array_Sub //!< @alias{Array_IndexOf}
#define Array_Subset		Array_Sub //!< @alias{Array_IndexOf}
#define Array_Subsection	Array_Sub //!< @alias{Array_IndexOf}



/*
** ************************************************************************** *|
**                           Array Editing Operations                         *|
** ************************************************************************** *|
*/

//! TODO
void					Array_Append(s_array_T* array, T item);
#define c_arrappend		Array_Append //!< @alias{Array_Append}

//! TODO
void					Array_Prepend(s_array_T* array, T item);
#define c_arrprepend	Array_Prepend //!< @alias{Array_Prepend}

//! TODO
void					Array_Insert(s_array_T* array, T item, t_size index);
#define c_arrinsert		Array_Insert //!< @alias{Array_Insert}



//! TODO
void					Array_Remove(s_array_T* array, t_size index);
#define c_arrremove		Array_Remove //!< @alias{Array_Insert}
#define c_arrdelone		Array_Remove //!< @alias{Array_Insert}

//! TODO
void					Array_RemoveAll(s_array_T* array, T target);
#define c_arrremall		Array_RemoveAll //!< @alias{Array_Insert}
#define c_arrdelall		Array_RemoveAll //!< @alias{Array_Insert}



//! TODO
_MALLOC()
s_array_T*				Array_Replace(s_array_T const* array, T old, T new);
#define c_arrrep		Array_Replace //!< @alias{Array_Replace}
#define c_arrreplace	Array_Replace //!< @alias{Array_Replace}



/*
** ************************************************************************** *|
**                           Array Checking Operations                        *|
** ************************************************************************** *|
*/

//! TODO
T*					Array_Find(s_array_T const* array, T item);
#define c_arrfind	Array_Find //!< @alias{Array_Find}

//! TODO
t_size				Array_IndexOf(s_array_T const* array, T item);
#define c_arrfindi	Array_IndexOf //!< @alias{Array_IndexOf}



//! TODO
t_bool				Array_Equals(s_array_T const* array1, s_array_T const* array2);
#define c_arrequ	Array_Equals //!< @alias{Array_Equals}

//! TODO
t_bool				Array_Equals_N(s_array_T const* array1, s_array_T const* array2, t_size n);
#define c_arrnequ	Array_Equals_N //!< @alias{Array_Equals_N}

//! TODO
t_sint				Array_Compare(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	Array_Compare //!< @alias{Array_Compare}

//! TODO
t_sint				Array_Compare_N(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_size n);
#define c_arrncmp	Array_Compare_N //!< @alias{Array_Compare_N}



/*
** ************************************************************************** *|
**                          Array Functional Operations                       *|
** ************************************************************************** *|
*/

//! TODO
void				Array_Iterate	(s_array_T* array, void (*f)(T* item));
#define c_arriter	Array_Iterate //!< @alias{Array_Iterate}

void				Array_Iterate_I	(s_array_T* array, void (*f)(T* item, t_size index));
#define c_arriteri	Array_Iterate_I //!< @alias{Array_Iterate_I}



//! TODO
_MALLOC()
s_array_T*			Array_Map		(s_array_T const* array, T (*map)(T* item));
#define c_arrmap	Array_Map //!< @alias{Array_Map}

_MALLOC()
s_array_T*			Array_Map_I		(s_array_T const* array, T (*map)(T* item, t_size index));
#define c_arrmapi	Array_Map_I //!< @alias{Array_Map_I}



//! TODO
_MALLOC()
s_array_T*			Array_Filter	(s_array_T const* array, t_bool (*filter)(T* item));
#define c_arrfilt	Array_Filter //!< @alias{Array_Filter}

_MALLOC()
s_array_T*			Array_Filter_I	(s_array_T const* array, t_bool (*filter)(T* item, t_size index));
#define c_arrfilti	Array_Filter_I //!< @alias{Array_Filter_I}


//! TODO Array_Reduce ?



/*! @} */
HEADER_END
#endif
