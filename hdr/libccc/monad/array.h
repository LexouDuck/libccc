/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/array.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_ARRAY_H
#define __LIBCCC_MONAD_ARRAY_H
/*!@group{libccc_monad_array}
** @{
**	This header defines a generic array type and utility functions for it.
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

#include "libccc/bool.h"
#include "libccc/int.h"

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
	T*		items;	//!< The pointer to the allocated contiguous array
}			s_array_T;

/* TODO find a way to avoid multiple definitions
extern
s_array_T const CONCAT(NULL_ARRAY,T_NAME);
s_array_T const CONCAT(NULL_ARRAY,T_NAME) = (s_array_T)
{
	.length = 0,
	.items = NULL,
};
*/


#define foreach_s_array(_TYPE_, _VAR_, _ARRAY_)		foreach (_TYPE_, _VAR_, s_array, _ARRAY_)

#define foreach_s_array_init(		_TYPE_, _VAR_, _ARRAY_)	t_uint _VAR_##_i = 0;
#define foreach_s_array_exit(		_TYPE_, _VAR_, _ARRAY_)	if ((void*)(_ARRAY_) != NULL && (_ARRAY_)->items != NULL)
#define foreach_s_array_loop_init(	_TYPE_, _VAR_, _ARRAY_)	_TYPE_ _VAR_ = (_ARRAY_)->items[_VAR_##_i]
#define foreach_s_array_loop_exit(	_TYPE_, _VAR_, _ARRAY_)	(_VAR_##_i < (_ARRAY_)->length)
#define foreach_s_array_loop_incr(	_TYPE_, _VAR_, _ARRAY_)	++_VAR_##_i
#define foreach_s_array_loop_setv(	_TYPE_, _VAR_, _ARRAY_)	_VAR_ = (_VAR_##_i == (_ARRAY_)->length ? _VAR_ : (_ARRAY_)->items[_VAR_##_i])



/*
** ************************************************************************** *|
**                            Array: basic operations                         *|
** ************************************************************************** *|
*/

//! Allocates a single-item array from the given `item` value.
/*!
**	@param	item	The value to store within the array's single item
**	@returns
**	An array of length 1, whose `items` pointer contains the given `item`
*/
_GENERIC()
s_array_T			CONCAT(Array_Item,T_NAME)(T item);
#define c_arritem	CONCAT(Array_Item,T_NAME)



//! Gets the item at position `index` in the array (returns the address of said item)
/*!
**	@param	array	the array to look through
**	@param	index	the index in the array of the item to get
**	@returns
**	The `index`th item in the given `array`,
**	or `NULL`, if the given `index` is beyond the last item.
*/
_GENERIC()
T*					CONCAT(Array_Get,T_NAME)(s_array_T const* array, t_uint index);
#define c_arrget	CONCAT(Array_Get,T_NAME)

//! Sets the value of item at position `index` in the array, and returns the address of said item
/*!
**	@param	array	the array in which an item should be set
**	@param	index	the index in the array of the item to set
**	@param	item	the new value to assign
**	@returns
**	The address of the `index`th item in the given `array`,
**	or `NULL`, if the given `index` is beyond the last item.
*/
_GENERIC()
T*					CONCAT(Array_Set,T_NAME)(s_array_T* array, t_uint index, T item);
#define c_arrset	CONCAT(Array_Set,T_NAME)



/*
** ************************************************************************** *|
**                           Array: creation operations                       *|
** ************************************************************************** *|
*/

//! Allocates a new array which consists of `n` items, each set to the given `value`
/*!
**	@param	n		The amount of items in this array
**	@param	value	The initial value to set for each of the `n` items
**	@returns
**	A newly allocated array containing `n` elements.
*/
_GENERIC()
s_array_T*			CONCAT(Array_New,T_NAME)(t_uint n, T value);
#define c_arrnew	CONCAT(Array_New,T_NAME)

//! Allocates a new array which consists of `n` items, initialized with variadic arguments.
/*!
**	@param	n		The amount of items in this array (amount of variadic args)
**	@param	...		The variadic array of arguments: there must be `n` arguments, of type `T`
**	@returns
**	A newly allocated array containing `n` elements (the given `...` varargs)
*/
_GENERIC()
s_array_T*			CONCAT(Array_Create,T_NAME)(t_uint n, ...);
#define c_arrcreate	CONCAT(Array_Create,T_NAME)



//! Returns a newly allocated copy of the given `array`
/*!
**	@param	array	The array to duplicate
**	@returns
**	A newly allocated copy of the given linked `array`.
*/
_GENERIC()
s_array_T*			CONCAT(Array_Duplicate,T_NAME)(s_array_T const* array);
#define c_arrdup	CONCAT(Array_Duplicate,T_NAME)



//! Creates a new array from a subsection of the given `array`, starting at `index` and taking `n` elements
/*!
**	@param	array	The array to copy a subsection from
**	@param	index	The index in `array` at which to begin copying a subsection of items
**	@param	n		The amount of items to copy - if `0`, then all items until the end are copied
**	@returns
**	A newly allocated subsection of the given `array`, starting at `index`,
**	and copying at most `n` items from the given source `array`.
**	Will return a `NULL` pointer, if `index` is too large or if `(index + n > array->length)`.
**	If `index` is valid but the array is not large enough for `n`,
**	then the resulting array will have fewer than `n` elements.
*/
_GENERIC()
s_array_T*			CONCAT(Array_Sub,T_NAME)(s_array_T const* array, t_uint index, t_uint n);
#define c_arrsub	CONCAT(Array_Sub,T_NAME)



//! Copies over `n` items from the given `src` array into the given `dest` array
/*!
**	@param	dest	The destination array to copy to
**	@param	dest_i	The index in the destination array at which to copy `n` items
**	@param	src		The source array which should be copied
**	@param	src_i	The index in the source array from which to copy `n` items
**	@param	n		The amount of array items to copy from `src` to `dest` - if `0`, all items until the end if `src` are copied
**	@returns
**	The given `dest` pointer, or `NULL` if an error occurred. The `dest` array is modified in-place.
*/
_GENERIC()
s_array_T*			CONCAT(Array_Copy,T_NAME)(s_array_T* dest, t_uint dest_i, s_array_T const* src, t_uint src_i, t_uint n);
#define c_arrcpy	CONCAT(Array_Copy,T_NAME)



/*
** ************************************************************************** *|
**                          Array: deletion operations                        *|
** ************************************************************************** *|
*/

//! Deallocates the given `array`
/*!
**	@param	array	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
*/
_GENERIC()
void				CONCAT(Array_Free,T_NAME)(s_array_T* array);
#define c_arrfree	CONCAT(Array_Free,T_NAME)

//! Deallocates the given `array`, calling the given `delete` function for each item
/*!
**	@param	array	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
**	@param	delete	the function which should be executed for each item before deletion.
*/
_GENERIC()
void				CONCAT(Array_Free_F,T_NAME)(s_array_T* array, void (*delete)(T* item));
#define c_arrffree	CONCAT(Array_Free_F,T_NAME)



//! Deletes the array inside the given address `a_array` (frees and sets to NULL)
/*!
**	@param	a_array	The address of the array whose `items` buffer should be deleted.
*/
_GENERIC()
void				CONCAT(Array_Delete,T_NAME)(s_array_T* *a_array);
#define c_arrdel	CONCAT(Array_Delete,T_NAME)

//! Deletes the array inside the given address `a_array` (frees and sets to NULL), calling the given `delete` function for each item
/*!
**	@param	a_array	The address of the array whose `items` buffer should be deleted.
**	@param	delete	the function which should be executed for each item before deletion.
*/
_GENERIC()
void				CONCAT(Array_Delete_F,T_NAME)(s_array_T* *a_array, void (*delete)(T* item));
#define c_arrfdel	CONCAT(Array_Delete_F,T_NAME)



/*
** ************************************************************************** *|
**                          Array: editing operations                         *|
** ************************************************************************** *|
*/

//! Appends the given item `item` to the end of the given array `dest`.
/*!
**	If `dest` is NULL, it'll append `item` at index 0, creating a 1-item array.
**
**	@param	dest	The destination array to append an item to
**	@param	item	The item to add to the given `dest`
**	@returns
**	The new pointer for the given `array`. The array is modified in-place.
**	This return will be the same as the given `dest` argument, unless `dest == NULL`.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Add,T_NAME)(s_array_T* dest, T item);
#define c_arradd		CONCAT(Array_Add,T_NAME)



//! Inserts the given `item` at the given `index` of the given array `dest`
/*!
**	If `index` is greater than the length of the array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination array in which to insert a new item
**	@param	item	The array item to insert into the given `dest`
**	@param	index	The index at which to insert the new array item
**	@returns
**	The new beginning pointer for the given `dest`. The array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, and the `index` given is zero.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Insert,T_NAME)(s_array_T* dest, T item, t_uint index);
#define c_arrinsert		CONCAT(Array_Insert,T_NAME)



//! Inserts all items from `src` at the given `index` of the given array `dest`
/*!
**	If `index` is greater than the length of the array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination array in which to insert new items
**	@param	src		The source array, whose items will be inserted into `dest`
**	@param	index	The index at which to insert the new array items
**	@returns
**	The new beginning pointer for the given array `dest`. The array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, or the `index` given is zero.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Wedge,T_NAME)(s_array_T* dest, s_array_T const* src, t_uint index);
#define c_arrwedge		CONCAT(Array_Wedge,T_NAME)



//! Removes a single item from the given `array`, at the given `index`
/*!
**	@param	array	The array in which to remove an item
**	@param	index	The index of the item to delete from the array
**	@returns
**	The array given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless the `index` given is zero.
*/
_GENERIC()
void					CONCAT(Array_RemoveAt,T_NAME)(s_array_T* array, t_uint index);
#define c_arrdelat		CONCAT(Array_RemoveAt,T_NAME)

//! Like Array_RemoveAt(), but you can supply a custom `delete` function
_GENERIC()
void					CONCAT(Array_RemoveAt_F,T_NAME)(s_array_T* array, t_uint index, void (*delete)(T));
#define c_arrfdelat		CONCAT(Array_RemoveAt_F,T_NAME)

//! Removes the first item from the given `array` which is equal to the given `item`
/*!
**	@param	array	The array in which to remove an item
**	@param	item	The item value which is to be removed from `array`
**	@returns
**	The `array` given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless the matched item is at position zero.
*/
_GENERIC()
void					CONCAT(Array_Remove,T_NAME)(s_array_T* array, T item);
#define c_arrdelone		CONCAT(Array_Remove,T_NAME)

//! Like Array_Remove(), but you can supply a custom `delete` function
_GENERIC()
void					CONCAT(Array_Remove_F,T_NAME)(s_array_T* array, T item, void (*delete)(T));
#define c_arrfdelone	CONCAT(Array_Remove_F,T_NAME)

//! Removes any items which are equal to the given `item` from the given `array`
/*!
**	@param	array	The array in which to remove items
**	@param	item	The item value for which any occurrences are to be removed from `array`
**	@returns
**	The array given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless a matched item is at position zero.
*/
_GENERIC()
void					CONCAT(Array_RemoveAll,T_NAME)(s_array_T* array, T item);
#define c_arrdelall		CONCAT(Array_RemoveAll,T_NAME)

//! Like Array_RemoveAll(), but you can supply a custom `delete` function
_GENERIC()
void					CONCAT(Array_RemoveAll_F,T_NAME)(s_array_T* array, T item, void (*delete)(T));
#define c_arrfdelall	CONCAT(Array_RemoveAll_F,T_NAME)



//! Creates a new array from the given `array`, where any occurence of `old` is replaced with `new`
/*!
**	@param	array	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@returns
**	A newly created array copied from `array`, in which in any item equal to `old`
**	will instead have a value of `new`, or `NULL` if an error occurred.
*/
_MALLOC()
_GENERIC()
s_array_T*				CONCAT(Array_Replace,T_NAME)(s_array_T const* array, T old, T new);
#define c_arrrep		CONCAT(Array_Replace,T_NAME)

//! Creates a new array from the given `array`, where the first `n` occurences of `old` are replaced with `new`.
/*!
**	@param	array	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created array copied from `strarr`, in which in the first (iterating forwards)
**	`n` encountered items which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
_MALLOC()
_GENERIC()
s_array_T*				CONCAT(Array_ReplaceFirst,T_NAME)(s_array_T const* array, T old, T new, t_uint n);
#define c_arrrepfirst	CONCAT(Array_ReplaceFirst,T_NAME)

//! Creates a new array from the given `array`, where the last `n` occurences of `old` are replaced with `new`.
/*!
**	@param	array	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created array copied from `strarr`, in which in the first (iterating backwards)
**	`n` encountered items which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
_MALLOC()
_GENERIC()
s_array_T*				CONCAT(Array_ReplaceLast,T_NAME)(s_array_T const* array, T old, T new, t_uint n);
#define c_arrreplast	CONCAT(Array_ReplaceLast,T_NAME)



//! Creates a new array from the given `array`, with each item's position being inverted
/*!
**	@param	array	The array to duplicate and invert
**	@returns
**	A newly created array copied from `array`, in which all items' positions have been
**	reversed. This means that the last item will become the first item, and so on.
*/
_MALLOC()
_GENERIC()
s_array_T*				CONCAT(Array_Reverse,T_NAME)(s_array_T const* array);
#define c_arrrev		CONCAT(Array_Reverse,T_NAME)



/*
** ************************************************************************** *|
**                       Array: concatenation operations                      *|
** ************************************************************************** *|
*/

//! Creates a new array which is the concatenation of `array1` and `array2`
/*!
**	@param	array1	The left-hand array to concatenate
**	@param	array2	The right-hand array to concatenate
**	@returns
**	A newly allocated array, created by concatenating `array1` and `array2`.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Concat,T_NAME)(s_array_T const* array1, s_array_T const* array2);
#define c_arrconcat		CONCAT(Array_Concat,T_NAME)

//! Creates a new array which is the concatenation of `array1` and `array2`, and deletes `array1`
/*!
**	@param	array1	The left-hand array to concatenate
**	@param	array2	The right-hand array to concatenate
**	@returns
**	A newly allocated array, created by concatenating `array1` and `array2`.
**	The `array1` argument will be deleted.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Append,T_NAME)(s_array_T* array1, s_array_T const* array2);
#define c_arrappend		CONCAT(Array_Append,T_NAME)

//! Creates a new array which is the concatenation of `array1` and `array2`, and deletes `array2`
/*!
**	@param	array1	The left-hand array to concatenate
**	@param	array2	The right-hand array to concatenate
**	@returns
**	A newly allocated array, created by concatenating `array1` and `array2`.
**	The `array2` argument will be deleted.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Prepend,T_NAME)(s_array_T const* array1, s_array_T* array2);
#define c_arrprepend	CONCAT(Array_Prepend,T_NAME)

//! Creates a new array which is the concatenation of `array1` and `array2`, and deletes both arrays
/*!
**	@param	array1	The left-hand array to concatenate
**	@param	array2	The right-hand array to concatenate
**	@returns
**	A newly allocated array, created by concatenating `array1` and `array2`.
**	Both `array1` and `array2` will be deleted.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Merge,T_NAME)(s_array_T* array1, s_array_T* array2);
#define c_arrmerge		CONCAT(Array_Merge,T_NAME)



/*
** ************************************************************************** *|
**                          Array: comparison operations                      *|
** ************************************************************************** *|
*/

//! Checks if two arrays have the same content
/*!
**	@param	array1	The first array to check for equality
**	@param	array2	The second array to check for equality
**	@returns
**	`TRUE` if each item of both arrays are equal, and the arrays have the same amount of items.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
_GENERIC()
t_bool				CONCAT(Array_Equals,T_NAME)		(s_array_T const* array1, s_array_T const* array2);
#define c_arrequ	CONCAT(Array_Equals,T_NAME)

//! Checks if two arrays have the same content, for the `n` first items
/*!
**	@param	array1	The first array to check for equality
**	@param	array2	The second array to check for equality
**	@param	n		The amount of items to check for equality
**	@returns
**	`TRUE` if the first `n` items of both arrays are equal.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
_GENERIC()
t_bool				CONCAT(Array_Equals_N,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_uint n);
#define c_arrnequ	CONCAT(Array_Equals_N,T_NAME)



//! Compares two arrays using the given `compare` function
/*!
**	@param	array1	The first array to compare
**	@param	array2	The second array to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
_GENERIC()
t_sint				CONCAT(Array_Compare,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2));
#define c_arrcmp	CONCAT(Array_Compare,T_NAME)

//! Compares two arrays using the given `compare` function, for the `n` first items
/*!
**	@param	array1	The first array to compare
**	@param	array2	The second array to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@param	n		The amount of items to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
_GENERIC()
t_sint				CONCAT(Array_Compare_N,T_NAME)	(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_arrncmp	CONCAT(Array_Compare_N,T_NAME)



/*
** ************************************************************************** *|
**                           Array: checking operations                       *|
** ************************************************************************** *|
*/

//! Returns the first encountered item in the given `array` matching the given `item`
/*!
**	@param	array	The linked array to look through
**	@param	item	The `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `NULL` if no such item was found.
*/
_GENERIC()
T*					CONCAT(Array_Find,T_NAME)(s_array_T const* array, T item);
#define c_arrfind	CONCAT(Array_Find,T_NAME)

//! Returns the first encountered item in the given `array` matching the given `item`
/*!
**	@param	array	The linked array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `array` for which the given `match` function
**	returned `TRUE`. Otherwise, returns `NULL` if no such item was found.
*/
_GENERIC()
T*					CONCAT(Array_Find_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item));
#define c_arrffind	CONCAT(Array_Find_F,T_NAME)

//! Returns the index of the first encountered item in the given `array` matching the given `item`
/*!
**	@param	array	the linked array to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `-1` if no such item was found.
*/
_GENERIC()
t_sint				CONCAT(Array_IndexOf,T_NAME)(s_array_T const* array, T item);
#define c_arrfindi	CONCAT(Array_IndexOf,T_NAME)

//! Returns the index of the first encountered item in the given `array` matching the given `item`
/*!
**	@param	array	the linked array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `-1` if no such item was found.
*/
_GENERIC()
t_sint				CONCAT(Array_IndexOf_F,T_NAME)(s_array_T const* array, t_bool (*match)(T item));
#define c_arrffindi	CONCAT(Array_IndexOf_F,T_NAME)



//! Gets the amount of occurences of the given `item` in the given `array`
/*!
**	@param	array	The array in which to check for occurences of `item`
**	@param	item	The item to match with
**	@returns
**	The total amount of items in the given `array` which are equal to `item`
*/
_GENERIC()
t_uint					CONCAT(Array_Count,T_NAME)	(s_array_T const* array, T item);
#define c_arrcount		CONCAT(Array_Count,T_NAME)

//! Checks whether the given `array` contains the given `item`
/*!
**	@param	array	The array in which to check for an occurence of `item`
**	@param	item	The item to check for
**	@returns
**	`TRUE` if the given `array` does contain an item which is equal to the given `item`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(Array_Contains,T_NAME)(s_array_T const* array, T item);
#define c_arrcontains	CONCAT(Array_Contains,T_NAME)

//! Checks whether the given `array` contains any item from the given `targets` array
/*!
**	@param	array	The array in which to check for an occurence of items from `target`
**	@param	targets	The array of items which are to be matched with `array`
**	@returns
**	`TRUE` if the given `array` does contain an item which is equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(Array_Has,T_NAME)	(s_array_T const* array, s_array_T const* target);
#define c_arrhas		CONCAT(Array_Has,T_NAME)

//! Checks whether the given `array` only contains items which are present in the given `targets` array
/*!
**	@param	array	The array which which should only contain items from `target`
**	@param	targets	The array of items which are to be matched with `array`
**	@returns
**	`TRUE` if the given `array` only contains items which are equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(Array_HasOnly,T_NAME)(s_array_T const* array, s_array_T const* target);
#define c_arrhasonly	CONCAT(Array_HasOnly,T_NAME)



/*
** ************************************************************************** *|
**                         Array: functional operations                       *|
** ************************************************************************** *|
*/

//! Iterates upon each item of the given `array`, applying the given function `f` for each of its items.
/*!
**	@param	array	The array whose items should be iterated upon
**	@param	f		The function to call for each item of the given `array`
*/
_GENERIC()
void				CONCAT(Array_Iterate,T_NAME)(s_array_T* array, void (*f)(T item));
#define c_arriter	CONCAT(Array_Iterate,T_NAME)

//! Like Array_Iterate(), but the user-supplied function receives the current index
_GENERIC()
void				CONCAT(Array_Iterate_I,T_NAME)(s_array_T* array, void (*f)(T item, t_uint index));
#define c_arriiter	CONCAT(Array_Iterate_I,T_NAME)



//! Creates a new array which is the result of applying the given `map` function for each item of `array`.
/*!
**	@param	array	The array whose items should be iterated upon
**	@param	map		The function to call for each item of the given `array`
**	@returns
**	A new array, created by storing the return values of each call to the given `map` function.
*/
_GENERIC()
s_array_T*			CONCAT(Array_Map,T_NAME)(s_array_T const* array, T (*map)(T item));
#define c_arrmap	CONCAT(Array_Map,T_NAME)

//! Like Array_Map(), but the user-supplied function receives the current index
_GENERIC()
s_array_T*			CONCAT(Array_Map_I,T_NAME)(s_array_T const* array, T (*map)(T item, t_uint index));
#define c_arrimap	CONCAT(Array_Map_I,T_NAME)



//! Creates a new array which is a subset of `array`, with only the items where the `filter` function returned `TRUE`
/*!
**	@param	array	The array whose items should be iterated upon
**	@param	filter	The function to call to check if an item of `array` should be added to the result
**	@returns
**	A new array, created by only keeping the values of the given `array`
**	for which the corresponding call to the `filter` function returned `TRUE`.
*/
_GENERIC()
s_array_T*				CONCAT(Array_Filter,T_NAME)(s_array_T const* array, t_bool (*filter)(T item));
#define c_arrfilter		CONCAT(Array_Filter,T_NAME)

//! Like Array_Filter(), but the user-supplied function receives the current index
_GENERIC()
s_array_T*				CONCAT(Array_Filter_I,T_NAME)(s_array_T const* array, t_bool (*filter)(T item, t_uint index));
#define c_arrifilter	CONCAT(Array_Filter_I,T_NAME)



//! Creates a single value by executing the given function `f` for each item of the given `array` 
/*!
**	The difference between Array_Reduce() and Array_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	array	The array to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `array`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `array`.
*/
_GENERIC()
void*					CONCAT(Array_Reduce,T_NAME)(s_array_T const* array, void* (*f)(T item, void* acc));
#define c_arrreduce		CONCAT(Array_Reduce,T_NAME)

//! Like Array_Reduce(), but the user-supplied function receives the current index
_GENERIC()
void*					CONCAT(Array_Reduce_I,T_NAME)(s_array_T const* array, void* (*f)(T item, void* acc, t_uint index));
#define c_arrireduce	CONCAT(Array_Reduce_I,T_NAME)

//! Creates a single value by executing the given function `f` for each item of the given `array` 
/*!
**	The difference between Array_Fold() and Array_Reduce() is that with this function,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	array	The array to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `array`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `array`.
*/
_GENERIC()
void*					CONCAT(Array_Fold,T_NAME)(s_array_T const* array, void* (*f)(T item, void* acc), void* initial);
#define c_arrfold		CONCAT(Array_Fold,T_NAME)

//! Like Array_Reduce(), but the user-supplied function receives the current index
_GENERIC()
void*					CONCAT(Array_Fold_I,T_NAME)(s_array_T const* array, void* (*f)(T item, void* acc, t_uint index), void* initial);
#define c_arrifold		CONCAT(Array_Fold_I,T_NAME)



/*! @} */
HEADER_END
#endif
