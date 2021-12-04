/*============================================================================*\
||                                            ______________________________  ||
||  libccc/pointerarray.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

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

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Type definition for an array of pointers
/*!
**	This typedef is only provided for certain niche purposes, since it is typically
**	not very good practice in C to hide pointers within `typedef` types.
*/
typedef t_char**	p_ptrarray;



/*
** ************************************************************************** *|
**                       PointerArray: basic operations                       *|
** ************************************************************************** *|
*/

//! Gets the amount of strings contained in the given pointer array `ptrarr`
/*!
**	@param	ptrarr	The pointer array whose length shall be counted
**	@returns
**	The amount of strings in the given pointer array `ptrarr` (before the first `NULL` pointer).
*/
t_uint					PointerArray_Length(void* const* ptrarr);
#define c_ptrarrlen		PointerArray_Length



/*
** ************************************************************************** *|
**                     Pointer Array: creation operations                     *|
** ************************************************************************** *|
*/

//! Allocates a new array which consists of `n` items, each set to the given `value`
/*!
**	@param	n		The amount of items in this array
**	@param	value	The initial value to set for each of the `n` items
**	@returns
**	A newly allocated array containing `n` elements.
*/
void**					PointerArray_New(t_uint n, void const* value);
#define c_ptrarrnew		PointerArray_New

//! Allocates a new array which consists of `n` items, initialized with variadic arguments.
/*!
**	@param	n		The amount of items in this array (amount of variadic args)
**	@param	...		The variadic array of arguments: there must be `n` arguments, of any type
**	@returns
**	A newly allocated array containing `n` elements (the given `...` varargs)
*/
void**					PointerArray_Create(t_uint n, ...);
#define c_ptrarrcreate	PointerArray_Create



//! Returns a newly allocated copy of the given `array`
/*!
**	@param	ptrarr	The array to duplicate
**	@returns
**	A newly allocated copy of the given linked `array`.
*/
void**					PointerArray_Duplicate(void* const* ptrarr);
#define c_ptrarrdup		PointerArray_Duplicate



//! Creates a new array from a subsection of the given `array`, starting at `index` and taking `n` elements
/*!
**	@param	ptrarr	The array to copy a subsection from
**	@param	index	The index in `array` at which to begin copying a subsection of items
**	@param	n		The amount of items to copy - if `0`, then all items until the end are copied
**	@returns
**	A newly allocated subsection of the given `array`, starting at `index`,
**	and copying at most `n` items from the given source `array`.
**	Will return a `NULL` pointer, if `index` is too large or if `(index + n > array->length)`.
**	If `index` is valid but the array is not large enough for `n`,
**	then the resulting array will have fewer than `n` elements.
*/
void**					PointerArray_Sub(void* const* ptrarr, t_uint index, t_uint n);
#define c_ptrarrsub		PointerArray_Sub



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
void**					PointerArray_Copy(void** dest, t_uint dest_i, void* const* src, t_uint src_i, t_uint n);
#define c_ptrarrcpy		PointerArray_Copy



/*
** ************************************************************************** *|
**                     PointerArray: deletion operations                      *|
** ************************************************************************** *|
*/

//! Deallocates the given `array`
/*!
**	@param	ptrarr	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
*/
void					PointerArray_Free(void** ptrarr);
#define c_ptrarrfree	PointerArray_Free

//! Deallocates the given `array`, calling the given `delete` function for each item
/*!
**	@param	ptrarr	The array whose `items` buffer should be deleted - its `length` will be set to `0`.
**	@param	delete	the function which should be executed for each item before deletion.
*/
void					PointerArray_Free_F(void** ptrarr, void (*delete)(void* ptr));
#define c_ptrarrffree	PointerArray_Free_F



//! Deletes the array inside the given address `ptrarr` (frees and sets to NULL)
/*!
**	@param	ptrarr	The address of the array whose `items` buffer should be deleted.
*/
void					PointerArray_Delete(void** *ptrarr);
#define c_ptrarrdel		PointerArray_Delete

//! Deletes the array inside the given address `ptrarr` (frees and sets to NULL), calling the given `delete` function for each item
/*!
**	@param	ptrarr	The address of the array whose `items` buffer should be deleted.
**	@param	delete	the function which should be executed for each item before deletion.
*/
void					PointerArray_Delete_F(void** *ptrarr, void (*delete)(void* ptr));
#define c_ptrarrfdel	PointerArray_Delete_F



/*
** ************************************************************************** *|
**                  Pointer Array: editing operations                         *|
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
void**					PointerArray_Add(void** dest, void const* ptr);
#define c_ptrarradd		PointerArray_Add



//! Inserts the given `item` at the given `index` of the given array `dest`
/*!
**	If `index` is greater than the length of the ptrarr, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination array in which to insert a new item
**	@param	item	The array item to insert into the given `dest`
**	@param	index	The index at which to insert the new array item
**	@returns
**	The new beginning pointer for the given `dest`. The array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, and the `index` given is zero.
*/
void**					PointerArray_Insert(void** dest, void const* ptr, t_uint index);
#define c_ptrarrinsert	PointerArray_Insert



//! Inserts all items from `src` at the given `index` of the given array `dest`
/*!
**	If `index` is greater than the length of the ptrarr, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination array in which to insert new items
**	@param	src		The source ptrarr, whose items will be inserted into `dest`
**	@param	index	The index at which to insert the new array items
**	@returns
**	The new beginning pointer for the given array `dest`. The array is modified in-place.
**	The return value will be the same as the given `dest` argument,
**	unless `dest == NULL`, or the `index` given is zero.
*/
void**					PointerArray_Wedge(void** dest, void* const* src, t_uint index);
#define c_ptrarrwedge	PointerArray_Wedge



//! Removes a single item from the given `array`, at the given `index`
/*!
**	@param	ptrarr	The array in which to remove an item
**	@param	index	The index of the item to delete from the array
**	@returns
**	The array given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless the `index` given is zero.
*/
void					PointerArray_RemoveAt(void** ptrarr, t_uint index);
#define c_ptrarrdelat	PointerArray_RemoveAt

//! Like Array_RemoveAt(), but you can supply a custom `delete` function
void					PointerArray_RemoveAt_F(void** ptrarr, t_uint index, void (*delete)(void*));
#define c_ptrarrfdelat	PointerArray_RemoveAt_F

//! Removes the first item from the given `array` which is equal to the given `item`
/*!
**	@param	ptrarr	The array in which to remove an item
**	@param	item	The item value which is to be removed from `array`
**	@returns
**	The `array` given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless the matched item is at position zero.
*/
void					PointerArray_Remove(void** ptrarr, void const* ptr);
#define c_ptrarrdelone	PointerArray_Remove

//! Like Array_Remove(), but you can supply a custom `delete` function
void					PointerArray_Remove_F(void** ptrarr, void const* ptr, void (*delete)(void*));
#define c_ptrarrfdelone	PointerArray_Remove_F

//! Removes any items which are equal to the given `item` from the given `array`
/*!
**	@param	ptrarr	The array in which to remove items
**	@param	item	The item value for which any occurrences are to be removed from `array`
**	@returns
**	The array given as argument. The array is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `array`, unless a matched item is at position zero.
*/
void					PointerArray_RemoveAll(void** ptrarr, void const* ptr);
#define c_ptrarrdelall	PointerArray_RemoveAll

//! Like Array_RemoveAll(), but you can supply a custom `delete` function
void					PointerArray_RemoveAll_F(void** ptrarr, void const* ptr, void (*delete)(void*));
#define c_ptrarrfdelall	PointerArray_RemoveAll_F



//! Creates a new array from the given `array`, where any occurence of `old` is replaced with `new`
/*!
**	@param	ptrarr	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@returns
**	A newly created array copied from `array`, in which in any item equal to `old`
**	will instead have a value of `new`, or `NULL` if an error occurred.
*/
_MALLOC()
void**						PointerArray_Replace(void* const* ptrarr, void const* old, void const* new);
#define c_ptrarrrep			PointerArray_Replace

//! Creates a new array from the given `array`, where the first `n` occurences of `old` are replaced with `new`.
/*!
**	@param	ptrarr	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created array copied from `strarr`, in which in the first (iterating forwards)
**	`n` encountered items which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
_MALLOC()
void**						PointerArray_ReplaceFirst(void* const* ptrarr, void const* old, void const* new, t_uint n);
#define c_ptrarrrepfirst	PointerArray_ReplaceFirst

//! Creates a new array from the given `array`, where the last `n` occurences of `old` are replaced with `new`.
/*!
**	@param	ptrarr	The array to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting array
**	@param	n		The amount of occurences of `old` to replace
**	@returns
**	A newly created array copied from `strarr`, in which in the first (iterating backwards)
**	`n` encountered items which are equal to `old` will instead have a value of `new`,
**	or `NULL` if an error occurred.
*/
_MALLOC()
void**						PointerArray_ReplaceLast(void* const* ptrarr, void const* old, void const* new, t_uint n);
#define c_ptrarrreplast		PointerArray_ReplaceLast



//! Creates a new array from the given `array`, with each item's position being inverted
/*!
**	@param	ptrarr	The array to duplicate and invert
**	@returns
**	A newly created array copied from `array`, in which all items' positions have been
**	reversed. This means that the last item will become the first ptr, and so on.
*/
_MALLOC()
void**					PointerArray_Reverse(void* const* ptrarr);
#define c_ptrarrrev		PointerArray_Reverse



/*
** ************************************************************************** *|
**               Pointer Array: concatenation operations                      *|
** ************************************************************************** *|
*/

//! Creates a new array which is the concatenation of `ptrarr1` and `ptrarr2`
/*!
**	@param	ptrarr1	The left-hand array to concatenate
**	@param	ptrarr2	The right-hand array to concatenate
**	@returns
**	A newly allocated ptrarr, created by concatenating `ptrarr1` and `ptrarr2`.
*/
_MALLOC()
void**					PointerArray_Concat(void* const* ptrarr1, void* const* ptrarr2);
#define c_ptrarrconcat	PointerArray_Concat

//! Creates a new array which is the concatenation of `ptrarr1` and `ptrarr2`, and deletes `ptrarr1`
/*!
**	@param	ptrarr1	The left-hand array to concatenate
**	@param	ptrarr2	The right-hand array to concatenate
**	@returns
**	A newly allocated ptrarr, created by concatenating `ptrarr1` and `ptrarr2`.
**	The `ptrarr1` argument will be deleted.
*/
_MALLOC()
void**					PointerArray_Append(void** *a_ptrarr1, void* const* ptrarr2);
#define c_ptrarrappend	PointerArray_Append

//! Creates a new array which is the concatenation of `ptrarr1` and `ptrarr2`, and deletes `ptrarr2`
/*!
**	@param	ptrarr1	The left-hand array to concatenate
**	@param	ptrarr2	The right-hand array to concatenate
**	@returns
**	A newly allocated ptrarr, created by concatenating `ptrarr1` and `ptrarr2`.
**	The `ptrarr2` argument will be deleted.
*/
_MALLOC()
void**					PointerArray_Prepend(void* const* ptrarr1, void** *a_ptrarr2);
#define c_ptrarrprepend	PointerArray_Prepend

//! Creates a new array which is the concatenation of `ptrarr1` and `ptrarr2`, and deletes both arrays
/*!
**	@param	ptrarr1	The left-hand array to concatenate
**	@param	ptrarr2	The right-hand array to concatenate
**	@returns
**	A newly allocated ptrarr, created by concatenating `ptrarr1` and `ptrarr2`.
**	Both `ptrarr1` and `ptrarr2` will be deleted.
*/
_MALLOC()
void**					PointerArray_Merge(void** *a_ptrarr1, void** *a_ptrarr2);
#define c_ptrarrmerge	PointerArray_Merge



//! Concatenates a set of arrays together, adding the given set of items `sep` between each
/*!
**	@param	ptrarrs	The set of arrays which should be joined together
**	@param	sep		The separator array, to be added in between each array of `ptrarrs`
**	@returns
**	A newly allocated array, which is the concatenation of all arrays in `ptrarrs`,
**	with the items of `sep` added between each array.
*/
_MALLOC()
void**					PointerArray_Join(void* const** ptrarrs, void* const* sep);
#define c_ptrarrjoin	PointerArray_Join



/*
** ************************************************************************** *|
**                  Pointer Array: comparison operations                      *|
** ************************************************************************** *|
*/

//! Checks if two arrays have the same content
/*!
**	@param	ptrarr1	The first array to check for equality
**	@param	ptrarr2	The second array to check for equality
**	@returns
**	`TRUE` if each item of both arrays are equal, and the arrays have the same amount of items.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
t_bool					PointerArray_Equals(void* const* ptrarr1, void* const* ptrarr2);
#define c_ptrarrequ		PointerArray_Equals

//! Checks if two arrays have the same content, for the `n` first items
/*!
**	@param	ptrarr1	The first array to check for equality
**	@param	ptrarr2	The second array to check for equality
**	@param	n		The amount of items to check for equality
**	@returns
**	`TRUE` if the first `n` items of both arrays are equal.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
t_bool					PointerArray_Equals_N(void* const* ptrarr1, void* const* ptrarr2, t_uint n);
#define c_ptrarrnequ	PointerArray_Equals_N



//! Compares two arrays using the given `compare` function
/*!
**	@param	ptrarr1	The first array to compare
**	@param	ptrarr2	The second array to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					PointerArray_Compare(void* const* ptrarr1, void* const* ptrarr2, t_sint (*compare)(void const* ptr1, void const* ptr2));
#define c_ptrarrcmp		PointerArray_Compare

//! Compares two arrays using the given `compare` function, for the `n` first items
/*!
**	@param	ptrarr1	The first array to compare
**	@param	ptrarr2	The second array to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@param	n		The amount of items to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
t_sint					PointerArray_Compare_N(void* const* ptrarr1, void* const* ptrarr2, t_sint (*compare)(void const* ptr1, void const* ptr2), t_uint n);
#define c_ptrarrncmp	PointerArray_Compare_N



/*
** ************************************************************************** *|
**                   Pointer Array: checking operations                       *|
** ************************************************************************** *|
*/

//! Returns the first encountered item in the given `array` matching the given `item`
/*!
**	@param	ptrarr	The linked array to look through
**	@param	item	The `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `NULL` if no such item was found.
*/
void* const*			PointerArray_Find(void* const* ptrarr, void const* ptr);
#define c_ptrarrfind	PointerArray_Find

//! Returns the first encountered item in the given `array` matching the given `item`
/*!
**	@param	ptrarr	The linked array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `array` for which the given `match` function
**	returned `TRUE`. Otherwise, returns `NULL` if no such item was found.
*/
void* const*			PointerArray_Find_F(void* const* ptrarr, t_bool (*match)(void const* ptr));
#define c_ptrarrffind	PointerArray_Find_F

//! Returns the index of the first encountered item in the given `array` matching the given `item`
/*!
**	@param	ptrarr	the linked array to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `-1` if no such item was found.
*/
t_sint					PointerArray_IndexOf(void* const* ptrarr, void const* ptr);
#define c_ptrarrfindi	PointerArray_IndexOf

//! Returns the index of the first encountered item in the given `array` matching the given `item`
/*!
**	@param	ptrarr	the linked array to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `array` which is equal to `item`,
**	or `-1` if no such item was found.
*/
t_sint					PointerArray_IndexOf_F(void* const* ptrarr, t_bool (*match)(void const* ptr));
#define c_ptrarrffindi	PointerArray_IndexOf_F



//! Gets the amount of occurences of the given `item` in the given `array`
/*!
**	@param	ptrarr	The array in which to check for occurences of `item`
**	@param	item	The item to match with
**	@returns
**	The total amount of items in the given `array` which are equal to `item`
*/
t_uint					PointerArray_Count	(void* const* ptrarr, void const* ptr);
#define c_ptrarrcount	PointerArray_Count

//! Checks whether the given `array` contains the given `item`
/*!
**	@param	ptrarr	The array in which to check for an occurence of `item`
**	@param	item	The item to check for
**	@returns
**	`TRUE` if the given `array` does contain an item which is equal to the given `item`,
**	otherwise returns `FALSE`.
*/
t_bool						PointerArray_Contains(void* const* ptrarr, void const* ptr);
#define c_ptrarrcontains	PointerArray_Contains

//! Checks whether the given `array` contains any item from the given `targets` array
/*!
**	@param	ptrarr	The array in which to check for an occurence of items from `target`
**	@param	targets	The array of items which are to be matched with `array`
**	@returns
**	`TRUE` if the given `array` does contain an item which is equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
t_bool					PointerArray_Has	(void* const* ptrarr, void* const* target);
#define c_ptrarrhas		PointerArray_Has

//! Checks whether the given `array` only contains items which are present in the given `targets` array
/*!
**	@param	ptrarr	The array which which should only contain items from `target`
**	@param	targets	The array of items which are to be matched with `array`
**	@returns
**	`TRUE` if the given `array` only contains items which are equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
t_bool					PointerArray_HasOnly(void* const* ptrarr, void* const* target);
#define c_ptrarrhasonly	PointerArray_HasOnly



/*
** ************************************************************************** *|
**                 Pointer Array: functional operations                       *|
** ************************************************************************** *|
*/

//! Iterates upon each item of the given `array`, applying the given function `f` for each of its items.
/*!
**	@param	ptrarr	The array whose items should be iterated upon
**	@param	f		The function to call for each item of the given `array`
*/
void					PointerArray_Iterate(void** ptrarr, void* (*f)(void* ptr));
#define c_ptrarriter	PointerArray_Iterate

//! Like Array_Iterate(), but the user-supplied function receives the current index
void					PointerArray_Iterate_I(void** ptrarr, void* (*f)(void* ptr, t_uint index));
#define c_ptrarriiter	PointerArray_Iterate_I



//! Creates a new array which is the result of applying the given `map` function for each item of `array`.
/*!
**	@param	ptrarr	The array whose items should be iterated upon
**	@param	map		The function to call for each item of the given `array`
**	@returns
**	A new ptrarr, created by storing the return values of each call to the given `map` function.
*/
_MALLOC()
void**					PointerArray_Map(void* const* ptrarr, void* (*map)(void const* ptr));
#define c_ptrarrmap		PointerArray_Map

//! Like Array_Map(), but the user-supplied function receives the current index
_MALLOC()
void**					PointerArray_Map_I(void* const* ptrarr, void* (*map)(void const* ptr, t_uint index));
#define c_ptrarrimap	PointerArray_Map_I



//! Creates a new array which is a subset of `array`, with only the items where the `filter` function returned `TRUE`
/*!
**	@param	ptrarr	The array whose items should be iterated upon
**	@param	filter	The function to call to check if an item of `array` should be added to the result
**	@returns
**	A new ptrarr, created by only keeping the values of the given `array`
**	for which the corresponding call to the `filter` function returned `TRUE`.
*/
_MALLOC()
void**					PointerArray_Filter(void* const* ptrarr, t_bool (*filter)(void const* ptr));
#define c_ptrarrfilter	PointerArray_Filter

//! Like Array_Filter(), but the user-supplied function receives the current index
_MALLOC()
void**					PointerArray_Filter_I(void* const* ptrarr, t_bool (*filter)(void const* ptr, t_uint index));
#define c_ptrarrifilter	PointerArray_Filter_I



//! Creates a single value by executing the given function `f` for each item of the given `array` 
/*!
**	The difference between Array_Reduce() and Array_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	ptrarr	The array to iterate upon
**	@param	f		The user-specified function to execute for each item of `array`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `array`.
*/
void*					PointerArray_Reduce(void* const* ptrarr, void* (*f)(void const* ptr, void* acc));
#define c_ptrarrreduce	PointerArray_Reduce

//! Like Array_Reduce(), but the user-supplied function receives the current index
void*					PointerArray_Reduce_I(void* const* ptrarr, void* (*f)(void const* ptr, void* acc, t_uint index));
#define c_ptrarrireduce	PointerArray_Reduce_I

//! Creates a single value by executing the given function `f` for each item of the given `array` 
/*!
**	The difference between Array_Fold() and Array_Reduce() is that with this function,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	ptrarr	The array to iterate upon
**	@param	f		The user-specified function to execute for each item of `array`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `array`.
*/
void*					PointerArray_Fold(void* const* ptrarr, void* (*f)(void const* ptr, void* acc), void* initial);
#define c_ptrarrfold	PointerArray_Fold

//! Like Array_Reduce(), but the user-supplied function receives the current index
void*					PointerArray_Fold_I(void* const* ptrarr, void* (*f)(void const* ptr, void* acc, t_uint index), void* initial);
#define c_ptrarrifold	PointerArray_Fold_I



/*! @} */
HEADER_END
#endif
