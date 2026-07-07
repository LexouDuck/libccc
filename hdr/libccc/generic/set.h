/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/set.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_SET_H
#define __LIBCCC_GENERIC_SET_H
/*!@group{libccc_generic_set,32,libccc/generic/set.h}
**
**	This header defines a generic set type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/generic/set.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A generic set struct, which stores a collection of unique values
/*!
**	A set is an unordered collection which can only hold one occurrence of any
**	given value: adding a value which is already contained does nothing.
**	Value equality is checked using the `T_EQUALS()` macro (which can be
**	user-defined, and defaults to a simple `==` comparison).
**
**	The values are stored contiguously in memory (like an array), but the order
**	of the `.items` is an implementation detail, and should not be relied upon
**	(in particular, removing an item can reorder the remaining items).
*/
struct set(T)
{
	t_uint	length;	//!< The amount of items in this set
	T*		items;	//!< The values contained within this set
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct set(T)	s_set(T);
#endif



#define foreach_s_set_init(		_TYPE_, _VAR_, _SET_)	t_uint _VAR_##_i = 0;
#define foreach_s_set_exit(		_TYPE_, _VAR_, _SET_)	if ((void*)(_SET_) != NULL && (_SET_)->items != NULL)
#define foreach_s_set_loop_init(	_TYPE_, _VAR_, _SET_)	_TYPE_ _VAR_ = (_SET_)->items[_VAR_##_i]
#define foreach_s_set_loop_exit(	_TYPE_, _VAR_, _SET_)	(_VAR_##_i < (_SET_)->length)
#define foreach_s_set_loop_incr(	_TYPE_, _VAR_, _SET_)	++_VAR_##_i
#define foreach_s_set_loop_setv(	_TYPE_, _VAR_, _SET_)	_VAR_ = (_VAR_##_i == (_SET_)->length ? _VAR_ : (_SET_)->items[_VAR_##_i])



/*============================================================================*\
||                        Set: construction/destruction                       ||
\*============================================================================*/

//!@doc Allocates a new empty set
/*!
**	@returns
**	A newly allocated empty set (with a `length` of `0`),
**	or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_New(T)(void);
#define c_setnew(T)		Set_New(T)
//!@}

//!@doc Allocates a new set which contains a single `item`
/*!
**	@param	item	The single value to store in the newly created set
**
**	@returns
**	A newly allocated set which contains only the given `item`,
**	or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Item(T)(T item);
#define c_setitem(T)	Set_Item(T)
//!@}

//!@doc Creates a new set from the given `n` amount of variadic arguments
/*!
**	@param	n		The amount of values given as variadic arguments
**	@param	...		The values to store in the newly created set
**
**	NOTE: any duplicate values among the given arguments are simply ignored
**	(only the first occurrence is stored), since a set holds unique values.
**
**	@returns
**	A newly allocated set which contains the given values,
**	or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Create(T)(t_uint n, ...);
#define c_setcreate(T)	Set_Create(T)
//!@}

//!@doc Creates a new set which is a copy of the given `set`
/*!
**	@param	set		The set to duplicate
**
**	@returns
**	A newly allocated copy of the given `set`,
**	or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Duplicate(T)(s_set(T) const* set);
#define c_setdup(T)		Set_Duplicate(T)
//!@}

//!@doc Deallocates the given `set`, and all its contents
//!@{
_GENERIC()
void					Set_Free(T)(s_set(T)* set);
#define c_setfree(T)	Set_Free(T)
//!@}

//!@doc Like Set_Free(), but you can supply a custom `del` function, called for each item
//!@{
_GENERIC()
void					Set_Free_F(T)(s_set(T)* set, void (*del)(T item));
#define c_setffree(T)	Set_Free_F(T)
//!@}

//!@doc Deallocates the given `set`, and sets the given pointer to `NULL`
//!@{
_GENERIC()
void					Set_Delete(T)(s_set(T)* *a_set);
#define c_setdel(T)		Set_Delete(T)
//!@}

//!@doc Like Set_Delete(), but you can supply a custom `del` function, called for each item
//!@{
_GENERIC()
void					Set_Delete_F(T)(s_set(T)* *a_set, void (*del)(T item));
#define c_setfdel(T)	Set_Delete_F(T)
//!@}



/*============================================================================*\
||                            Set: basic operations                           ||
\*============================================================================*/

//!@doc Returns the amount of items contained in the given `set`
//!@{
_GENERIC()
t_uint					Set_Length(T)(s_set(T) const* set);
#define c_setlen(T)		Set_Length(T)
//!@}

//!@doc Checks whether the given `set` contains the given `item`
/*!
**	@param	set		The set to check
**	@param	item	The value to check for (compared using `T_EQUALS()`)
**
**	@returns
**	`TRUE` if the given `item` is contained in the given `set`,
**	`FALSE` otherwise
*/
//!@{
_GENERIC()
t_bool					Set_Contains(T)(s_set(T) const* set, T item);
#define c_sethas(T)		Set_Contains(T)
//!@}

//!@doc Gets a pointer to the item of the given `set` which is equal to `item`
/*!
**	@param	set		The set to look through
**	@param	item	The value to find (compared using `T_EQUALS()`)
**
**	@returns
**	A pointer to the stored item which is equal to the given `item`,
**	or `NULL` if no such item is contained in the given `set`
**	(no error is set when the item is simply absent)
*/
//!@{
_GENERIC()
T*						Set_Find(T)(s_set(T) const* set, T item);
#define c_setfind(T)	Set_Find(T)
//!@}

//!@doc Gets a pointer to the first item of the given `set` which matches the given `match` function
/*!
**	@param	set		The set to look through
**	@param	match	The predicate function: item(s) for which it returns `TRUE` are matched
**
**	@returns
**	A pointer to a stored item for which the given `match` function returned `TRUE`,
**	or `NULL` if there is no such item in the given `set`
**	(no error is set when no item matches)
*/
//!@{
_GENERIC()
T*						Set_Find_F(T)(s_set(T) const* set, t_bool (*match)(T item));
#define c_setffind(T)	Set_Find_F(T)
//!@}

//!@doc Adds the given `item` to the given `set` (if it is not already contained)
/*!
**	@param	set		The set to add an item to
**	@param	item	The value to add to the set
**
**	NOTE: if the given `item` is already contained in the given `set`,
**	this function does nothing (a set can only hold unique values).
**
**	@returns
**	A pointer to the stored item within the set (whether newly added,
**	or already present beforehand), or `NULL` if an error occurred
*/
//!@{
_GENERIC()
T*						Set_Add(T)(s_set(T)* set, T item);
#define c_setadd(T)		Set_Add(T)
//!@}

//!@doc Removes the given `item` from the given `set` (if it is contained)
/*!
**	@param	set		The set to remove an item from
**	@param	item	The value to remove from the set
**
**	NOTE: if the given `item` is not contained in the given `set`,
**	this function does nothing.
**	NOTE: removing an item can reorder the remaining items of the set
**	(the order of a set's items is an implementation detail).
**
**	@returns
**	The given `set`, or `NULL` if an error occurred
*/
//!@{
_GENERIC()
s_set(T)*				Set_Remove(T)(s_set(T)* set, T item);
#define c_setrem(T)		Set_Remove(T)
//!@}

//!@doc Like Set_Remove(), but you can supply a custom `del` function, called for the removed item
//!@{
_GENERIC()
s_set(T)*				Set_Remove_F(T)(s_set(T)* set, T item, void (*del)(T item));
#define c_setfrem(T)	Set_Remove_F(T)
//!@}



/*============================================================================*\
||                          Set: comparison operations                        ||
\*============================================================================*/

//!@doc Checks whether the two given sets contain the same values
/*!
**	@param	set1	The first set to check
**	@param	set2	The second set to check
**
**	NOTE: this comparison is order-independent: two sets are equal if and only
**	if they contain exactly the same values (in whichever internal order).
**
**	@returns
**	`TRUE` if the two given sets contain the same values,
**	`FALSE` otherwise
*/
//!@{
_GENERIC()
t_bool					Set_Equals(T)(s_set(T) const* set1, s_set(T) const* set2);
#define c_setequ(T)		Set_Equals(T)
//!@}

//!@doc Checks whether the given `sub` set is a subset of the given `super` set
/*!
**	@param	sub		The set whose items should all be contained in `super`
**	@param	super	The set which should contain every item of `sub`
**
**	NOTE: an empty set is a subset of any set (including another empty set),
**	and any set is always a subset of itself.
**
**	@returns
**	`TRUE` if every item of `sub` is contained in `super`,
**	`FALSE` otherwise
*/
//!@{
_GENERIC()
t_bool					Set_IsSubset(T)(s_set(T) const* sub, s_set(T) const* super);
#define c_setsubset(T)	Set_IsSubset(T)
//!@}

//!@doc Checks whether the two given sets have no values in common
/*!
**	@param	set1	The first set to check
**	@param	set2	The second set to check
**
**	NOTE: an empty set is disjoint with any set (including another empty set).
**
**	@returns
**	`TRUE` if the two given sets have no values in common,
**	`FALSE` otherwise
*/
//!@{
_GENERIC()
t_bool						Set_IsDisjoint(T)(s_set(T) const* set1, s_set(T) const* set2);
#define c_setdisjoint(T)	Set_IsDisjoint(T)
//!@}



/*============================================================================*\
||                          Set: set-theory operations                        ||
\*============================================================================*/

//!@doc Creates a new set which is the mathematical union of the two given sets
/*!
**	@param	set1	The first set
**	@param	set2	The second set
**
**	@returns
**	A newly allocated set which contains every value that is present
**	in `set1` or in `set2` (or in both), or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Union(T)(s_set(T) const* set1, s_set(T) const* set2);
#define c_setunion(T)	Set_Union(T)
//!@}

//!@doc Creates a new set which is the mathematical intersection of the two given sets
/*!
**	@param	set1	The first set
**	@param	set2	The second set
**
**	@returns
**	A newly allocated set which contains every value that is present
**	in both `set1` and `set2`, or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Intersect(T)(s_set(T) const* set1, s_set(T) const* set2);
#define c_setinter(T)	Set_Intersect(T)
//!@}

//!@doc Creates a new set which is the mathematical difference of the two given sets
/*!
**	@param	set1	The set whose items to keep
**	@param	set2	The set whose items to subtract from `set1`
**
**	@returns
**	A newly allocated set which contains every value of `set1` which
**	is not present in `set2`, or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Difference(T)(s_set(T) const* set1, s_set(T) const* set2);
#define c_setdiff(T)	Set_Difference(T)
//!@}



/*============================================================================*\
||                          Set: functional operations                        ||
\*============================================================================*/

//!@doc Iterates upon each item of the given `set`, applying the given function `f` to each of its items
//!@{
_GENERIC()
void					Set_Iterate(T)(s_set(T)* set, void (*f)(T item));
#define c_setiter(T)	Set_Iterate(T)
//!@}

//!@doc Like Set_Iterate(), but the user-supplied function receives the current index
/*!
**	NOTE: the index given to `f` reflects the current internal storage order
**	of the set, which is an implementation detail (it is only guaranteed that
**	each item will be given a unique index, in the range `[0, length)`).
*/
//!@{
_GENERIC()
void					Set_Iterate_I(T)(s_set(T)* set, void (*f)(T item, t_uint index));
#define c_setiiter(T)	Set_Iterate_I(T)
//!@}

//!@doc Creates a new set, by applying the given function `map` to each item of the given `set`
/*!
**	NOTE: if the given `map` function maps two distinct items to the same value,
**	that value will only be stored once in the resulting set (which will thus
**	have a smaller `length` than the source set). Beware: in that situation,
**	if the `map` function allocates its result, the duplicate mapped values
**	are simply not stored, and would be leaked (this caveat is inherent to
**	mapping over a unique-value collection).
**
**	@returns
**	A newly allocated set with the mapped values, or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Map(T)(s_set(T) const* set, T (*map)(T item));
#define c_setmap(T)		Set_Map(T)
//!@}

//!@doc Creates a new set, only keeping the items of the given `set` for which the given `filter` function returned `TRUE`
/*!
**	@returns
**	A newly allocated set with the filtered values, or `NULL` if an error occurred
*/
//!@{
_MALLOC()
_GENERIC()
s_set(T)*				Set_Filter(T)(s_set(T) const* set, t_bool (*filter)(T item));
#define c_setfilt(T)	Set_Filter(T)
//!@}

/*! @endgroup */
HEADER_END
#endif
