/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/list.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_LIST_H
#define __LIBCCC_MONAD_LIST_H
/*!@group{libccc_monad_list,31,libccc/monad/list.h}
**
**	This header defines a generic linked list type and utility functions for it.
*/

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

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/list.c"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This is a basic linked list struct, with dynamic content type
/*!
**	The list struct represents one chainlink in the linked-list. So, a linked-list
**	which contains 3 items would consist of 3 different list structs,
**	all chained together via their `next` pointer, and the last item would
**	have this `next` pointer set to `NULL`.
*/
typedef struct list(T)
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	struct list(T)*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
#endif
	struct list(T)*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	T				item;	//!< The content of this linked-list item
}	s_list(T);

/* TODO find a way to avoid multiple definitions
extern
s_list(T) const		NULL_L_##S
s_list(T) const		NULL_LIST,T_NAME) = (s_l_##s
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	.prev = NULL,
#endif
	.next = NULL,
	.item = T_NULL,
};
*/



//!@doc Implementation of the #foreach keyword macro, for the #s_list type
//!@{
#define foreach_s_list(_TYPE_, _VAR_, _LIST_)		foreach (_TYPE_, _VAR_, s_list, _LIST_)

#define foreach_s_list_init(		_TYPE_, _VAR_, _LIST_)	foreach_s_list_T(_TYPE_, _VAR_, _LIST_) _VAR_##_i = (_LIST_);
#define foreach_s_list_exit(		_TYPE_, _VAR_, _LIST_)	if ((void*)(_LIST_) != NULL)
#define foreach_s_list_loop_init(	_TYPE_, _VAR_, _LIST_)	_TYPE_ _VAR_ = (_VAR_##_i->item)
#define foreach_s_list_loop_exit(	_TYPE_, _VAR_, _LIST_)	(_VAR_##_i != NULL)
#define foreach_s_list_loop_incr(	_TYPE_, _VAR_, _LIST_)	_VAR_##_i = _VAR_##_i->next
#define foreach_s_list_loop_setv(	_TYPE_, _VAR_, _LIST_)	_VAR_ = (_VAR_##_i == NULL ? _VAR_ : (_VAR_##_i->item))

#if 1
	#define foreach_s_list_T(_TYPE_, _VAR_, _LIST_) \
		__typeof__(_LIST_)
#else
	//! if the `typeof()` operator doesn't exist, an inline anonymous struct is used (very unsafe !)
	#if LIBCONFIG_LIST_DOUBLYLINKED
	#define foreach_s_list_T(_TYPE_, _VAR_, _LIST_) \
		struct _##_VAR_				\
		{							\
			struct _##_VAR_*prev;	\
			struct _##_VAR_*next;	\
			_TYPE_			item;	\
		}
	#else
	#define foreach_s_list_T(_TYPE_, _VAR_, _LIST_) \
		struct _##_VAR_				\
		{							\
			struct _##_VAR_*next;	\
			_TYPE_			item;	\
		}
	#endif
#endif
//!@}



/*
** ************************************************************************** *|
**                            List: basic operations                          *|
** ************************************************************************** *|
*/

//!@doc Allocates and returns a single list item from the given `item`.
/*!
**	@param	item	The value to store within the linked list item
**	@returns
**	A newly allocated linked list item containing `item`
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Item(T)(T item);
#define c_lstitem(T)	List_Item(T)
//!@}

//!@doc Returns the amount of items in the given `list`
/*!
**	@param	list		the list to look through
**	@returns
**	The amount of items in the given `list`,
**	by traversing it, looping through every `next` pointer.
*/
//!@{
_GENERIC()
t_uint				List_Length(T)(s_list(T) const* list);
#define c_lstlen(T)	List_Length(T)
//!@}



//!@doc Gets the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the item to get
**	@returns
**	The `index`th item in the given `list`,
**	or `NULL`, if `index` is beyond the last item.
*/
//!@{
_GENERIC()
T*					List_Get(T)(s_list(T) const* list, t_uint index);
#define c_lstget(T)	List_Get(T)
//!@}

//!@doc Sets the value of the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list in which an item should be set
**	@param	index	the index in the list of the item to set
**	@param	item	the new value to assign
**	@returns
**	The `index`th item in the given `list`,
**	or `NULL`, if `index` is beyond the last item.
*/
//!@{
_GENERIC()
T*					List_Set(T)(s_list(T)* list, t_uint index, T item);
#define c_lstset(T)	List_Set(T)
//!@}



/*
** ************************************************************************** *|
**                          List: creation operations                         *|
** ************************************************************************** *|
*/

//!@doc Allocates a new linked list containing `n` items, each set to the given `value`
/*!
**	Allocates a new linked list, consisting of several `s_list` structs chained
**	together via their `next` pointer, with each struct storing an `item`.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	value	The initial value to set for each of the `n` items
**	@returns
**	A newly allocated linked list which consists of `n` list structs chained together.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_New(T)(t_uint n, T value);
#define c_lstnew(T)		List_New(T)
//!@}



//!@doc Allocates and returns a linked list, created from the given variadic arguments.
/*!
**	This function accepts a variadic list of arguments to initialize the list.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: they must all be of type `T`
**	@returns
**	A newly allocated linked list which consists of `n` structs chained together.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Create(T)(t_uint n, ...);
#define c_lstcreate(T)	List_Create(T)
//!@}



//!@doc Returns a newly allocated copy of the given `list`
/*!
**	@param	list	The list to duplicate
**	@returns
**	A newly allocated copy of the given linked `list`.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Duplicate(T)(s_list(T) const* list);
#define c_lstdup(T)		List_Duplicate(T)
//!@}



//!@doc Creates a new list from a subsection of the given `list`, starting at `index` and taking `n` items
/*!
**	@param	list	The list to copy a subsection from
**	@param	index	The index in `array` at which to begin copying a subsection of items
**	@param	n		The amount of items to copy - if `0`, then all items until the end are copied
**	@returns
**	A newly allocated subsection of the given `list`, starting at `index`,
**	and copying at most `n` items from the given source `list`.
**	Will return `NULL` if `index` is too large or if `(index + n > List_Length(list))`.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` items.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Sub(T)(s_list(T) const* list, t_uint index, t_uint n);
#define c_lstsub(T)		List_Sub(T)
//!@}



//!@doc Copies over `n` items from the given `src` list into the given `dest` list
/*!
**	@param	dest	The destination list to copy to
**	@param	dest_i	The index in the destination array at which to copy `n` items
**	@param	src		The source list which should be copied
**	@param	src_i	The index in the source array from which to copy `n` items
**	@param	n		The amount of list items to copy from `src` to `dest`
**	@returns
**	The given `dest` pointer, or `NULL` if an error occurred. The `dest` list is modified in-place.
*/
//!@{
_GENERIC()
s_list(T)*				List_Copy(T)(s_list(T)* dest, t_uint dest_i, s_list(T) const* src, t_uint src_i, t_uint n);
#define c_lstcpy(T)		List_Copy(T)
//!@}



/*
** ************************************************************************** *|
**                          List: deletion operations                         *|
** ************************************************************************** *|
*/

//!@doc Deallocates all the items in the given `list`
/*!
**	@param	list	The first element of the list to remove.
*/
//!@{
_GENERIC()
void					List_Free(T)(s_list(T)* list);
#define c_lstfree(T)	List_Free(T)
//!@}

//!@doc Deallocates all the items in the given `list`, calling `del()` for each item.
/*!
**	@param	list	The first element of the list to remove.
**	@param	del		The function which should be executed for each item before deletion.
*/
//!@{
_GENERIC()
void					List_Free_F(T)(s_list(T)* list, void (*del)(T* item));
#define c_lstffree(T)	List_Free_F(T)
//!@}



//!@doc Deletes all the items in the list starting at `*a_list`.
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
*/
//!@{
_GENERIC()
void					List_Delete(T)(s_list(T)* *a_list);
#define c_lstdel(T)		List_Delete(T)
//!@}

//!@doc Deletes all the items in the list starting at `*a_list`, calling `del()` for each item.
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
**	@param	del		The function which should be executed for each item before deletion.
*/
//!@{
_GENERIC()
void					List_Delete_F(T)(s_list(T)* *a_list, void (*del)(T* item));
#define c_lstfdel(T)	List_Delete_F(T)
//!@}



/*
** ************************************************************************** *|
**                           List: editing operations                         *|
** ************************************************************************** *|
*/

//!@doc Appends the given item `item` to the end of the given list `dest`.
/*!
**	If `dest` is NULL, it'll append `item` at index 0, creating a 1-item list.
**
**	@param	dest	list destination array to append an item to
**	@param	item	The list item to append to the given list `dest`
**	@returns
**	The new beginning pointer for the given list `dest`. The list is modified in-place.
**	This return will be the same as the given list `dest` argument, unless `dest == NULL`.
*/
//!@{
_GENERIC()
s_list(T)*				List_Add(T)(s_list(T)* dest, T item);
#define c_lstadd(T)		List_Add(T)
//!@}



//!@doc Inserts the given `item` at the given `index` of the given list `dest`
/*!
**	If `index` is greater than the length of the array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination list in which to insert a new item
**	@param	item	The item to insert into the given list `dest`
**	@param	index	The index at which to insert the new list item
**	@returns
**	The new beginning pointer for the given list `dest`. The list is modified in-place.
**	The return value will be the same as the given list `dest` argument,
**	unless `dest == NULL`, and the `index` given is zero.
*/
//!@{
_GENERIC()
s_list(T)*				List_Insert(T)(s_list(T)* dest, T item, t_uint index);
#define c_lstinsert(T)	List_Insert(T)
//!@}



//!@doc Inserts all items from `src` at the given `index` of the given list `dest`
/*!
**	If `index` is greater than the length of the array, then nothing is done and `NULL` is returned.
**
**	@param	dest	The destination list in which to insert new items
**	@param	src		The source list, whose items will be inserted into `dest`
**	@param	index	The index at which to insert the new list item
**	@returns
**	The new beginning pointer for the given list `dest`. The list is modified in-place.
**	The return value will be the same as the given list `dest` argument,
**	unless `dest == NULL`, or the `index` given is zero.
*/
//!@{
_GENERIC()
s_list(T)*				List_Wedge(T)(s_list(T)* list, s_list(T) const* src, t_uint index);
#define c_lstwedge(T)	List_Wedge(T)
//!@}



//!@doc Removes a single item from the given `list`, at the given `index`
/*!
**	@param	list	The list in which to remove an item
**	@param	index	The index of the item to remove from the list
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless the `index` given is zero.
*/
//!@{
_GENERIC()
s_list(T)*				List_RemoveAt(T)(s_list(T)* list, t_uint index);
#define c_lstdelat(T)	List_RemoveAt(T)
//!@}

//!@doc Like List_RemoveAt(), but you can supply a custom `del` function
//!@{
_GENERIC()
s_list(T)*				List_RemoveAt_F(T)(s_list(T)* list, t_uint index, void (*del)(T));
#define c_lstfdelat(T)	List_RemoveAt_F(T)
//!@}

//!@doc Removes the first item from the given `list` which is equal to the given `item`
/*!
**	@param	list	The list in which to remove an item
**	@param	item	The item value which is to be removed from `list`
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless the matched item is at position zero.
*/
//!@{
_GENERIC()
s_list(T)*				List_Remove(T)(s_list(T)* list, T item);
#define c_lstdelone(T)	List_Remove(T)
//!@}

//!@doc Like List_Remove(), but you can supply a custom `del` function
//!@{
_GENERIC()
s_list(T)*				List_Remove_F(T)(s_list(T)* list, T item, void (*del)(T));
#define c_lstfdelone(T)	List_Remove_F(T)
//!@}

//!@doc Removes any items which are equal to the given `item` from the given `list`
/*!
**	@param	list	The list in which to remove items
**	@param	item	The item value for which any occurrences are to be removed from `list`
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless a matched item is at position zero.
*/
//!@{
_GENERIC()
s_list(T)*				List_RemoveAll(T)(s_list(T)* list, T item);
#define c_lstdelall(T)	List_RemoveAll(T)
//!@}

//!@doc Like List_RemoveAll(), but you can supply a custom `del` function
//!@{
_GENERIC()
s_list(T)*				List_RemoveAll_F(T)(s_list(T)* list, T item, void (*del)(T));
#define c_lstfdelall(T)	List_RemoveAll_F(T)
//!@}



//!@doc Creates a new list from the given `list`, where any occurence of `item_old` is replaced with `item_new`.
/*!
**	@param	list		The list to use as a basis for copy and item replacement
**	@param	item_old	The item to be replaced
**	@param	item_new	The replacement for the resulting list
**	@returns
**	A newly created list copied from `list`, in which in any item equal to `item_old`
**	will instead have a value of `item_new`, or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*					List_Replace(T)(s_list(T) const* list, T item_old, T item_new);
#define c_lstrep(T)			List_Replace(T)
//!@}

//!@doc Creates a new list from the given `list`, where the `n` first occurences of `item_old` are replaced with `item_new`.
/*!
**	@param	list		The list to use as a basis for copy and item replacement
**	@param	item_old	The item to be replaced
**	@param	item_new	The replacement for the resulting list
**	@param	n			The amount of occurences of `item_old` to replace
**	@returns
**	A newly created list copied from `strarr`, in which in the first (iterating forwards)
**	`n` encountered items which are equal to `item_old` will instead have a value of `item_new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*					List_ReplaceFirst(T)(s_list(T) const* list, T item_old, T item_new, t_uint n);
#define c_lstrepfirst(T)	List_ReplaceFirst(T)
//!@}

//!@doc Creates a new list from the given `list`, where the `n` last occurences of `item_old` are replaced with `item_new`.
/*!
**	@param	list		The list to use as a basis for copy and item replacement
**	@param	item_old	The item to be replaced
**	@param	item_new	The replacement for the resulting list
**	@param	n			The amount of occurences of `item_old` to replace
**	@returns
**	A newly created list copied from `strarr`, in which in the first (iterating backwards)
**	`n` encountered items which are equal to `item_old` will instead have a value of `item_new`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*					List_ReplaceLast(T)(s_list(T) const* list, T item_old, T item_new, t_uint n);
#define c_lstreplast(T)		List_ReplaceLast(T)
//!@}



//!@doc Creates a new list from the given `list`, with each item's position being inverted
/*!
**	@param	list	The list to duplicate and invert
**	@returns
**	A newly created list copied from `list`, in which all items' positions have been
**	reversed. This means that the last item will become the first item, and so on.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Reverse(T)(s_list(T) const* list);
#define c_lstrev(T)		List_Reverse(T)
//!@}



/*
** ************************************************************************** *|
**                         List concatenation operations                      *|
** ************************************************************************** *|
*/

//!@doc Creates a new list which is the concatenation of `list1` and `list2`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
*/
//!@{
_GENERIC()
s_list(T)*				List_Concat(T)(s_list(T) const* list1, s_list(T) const* list2);
#define c_lstconcat(T)	List_Concat(T)
//!@}

//!@doc Creates a new list which is the concatenation of `list1` and `list2`, and deletes `list1`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	The `list1` argument will be deleted.
*/
//!@{
_GENERIC()
s_list(T)*				List_Append(T)(s_list(T)* list1, s_list(T) const* list2);
#define c_lstappend(T)	List_Append(T)
//!@}

//!@doc Creates a new list which is the concatenation of `list1` and `list2`, and deletes `list2`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	The `list2` argument will be deleted.
*/
//!@{
_GENERIC()
s_list(T)*				List_Prepend(T)(s_list(T) const* list1, s_list(T)* list2);
#define c_lstprepend(T)	List_Prepend(T)
//!@}

//!@doc Creates a new list which is the concatenation of `list1` and `list2`, and deletes both lists
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	Both `list1` and `list2` will be deleted.
*/
//!@{
_GENERIC()
s_list(T)*				List_Merge(T)(s_list(T)* list1, s_list(T)* list2);
#define c_lstmerge(T)	List_Merge(T)
//!@}



/*
** ************************************************************************** *|
**                          List: comparison operations                       *|
** ************************************************************************** *|
*/

//!@doc Checks if two lists have the same content
/*!
**	@param	list1	The first list to check for equality
**	@param	list2	The second list to check for equality
**	@returns
**	`TRUE` if each item of both lists are equal, and the lists have the same amount of items.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
//!@{
_GENERIC()
t_bool					List_Equals(T)(s_list(T) const* list1, s_list(T) const* list2);
#define c_lstequ(T)		List_Equals(T)
//!@}

//!@doc Checks if two lists have the same content, for the `n` first items
/*!
**	@param	list1	The first list to check for equality
**	@param	list2	The second list to check for equality
**	@param	n		The amount of items to check for equality
**	@returns
**	`TRUE` if the first `n` items of both lists are equal.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
//!@{
_GENERIC()
t_bool					List_Equals_N(T)(s_list(T) const* list1, s_list(T) const* list2, t_uint n);
#define c_lstnequ(T)	List_Equals_N(T)
//!@}



//!@doc Compares two lists using the given `compare` function
/*!
**	@param	list1	The first list to compare
**	@param	list2	The second list to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
//!@{
_GENERIC()
t_sint					List_Compare(T)(s_list(T) const* list1, s_list(T) const* list2, t_sint (*compare)(T item1, T item2));
#define c_lstcmp(T)		List_Compare(T)
//!@}

//!@doc Compares two lists using the given `compare` function, for the `n` first items
/*!
**	@param	list1	The first list to compare
**	@param	list2	The second list to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@param	n		The amount of items to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
//!@{
_GENERIC()
t_sint					List_Compare_N(T)(s_list(T) const* list1, s_list(T) const* list2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_lstncmp(T)	List_Compare_N(T)
//!@}



/*
** ************************************************************************** *|
**                           List: checking operations                        *|
** ************************************************************************** *|
*/

//!@doc Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	The linked list to look through
**	@param	item	The `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `NULL` if no such item was found.
*/
//!@{
_GENERIC()
s_list(T) const*		List_Find(T)(s_list(T) const* list, T item);
#define c_lstfind(T)	List_Find(T)
//!@}

//!@doc Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	The linked list to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `list` for which the given `match` function
**	returned `TRUE`. Otherwise, returns `NULL` if no such item was found.
*/
//!@{
_GENERIC()
s_list(T) const*		List_Find_F(T)(s_list(T) const* list, t_bool (*match)(T item));
#define c_lstffind(T)	List_Find_F(T)
//!@}

//!@doc Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `-1` if no such item was found.
*/
//!@{
_GENERIC()
t_sint					List_IndexOf(T)(s_list(T) const* list, T item);
#define c_lstfindi(T)	List_IndexOf(T)
//!@}

//!@doc Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `-1` if no such item was found.
*/
//!@{
_GENERIC()
t_sint					List_IndexOf_F(T)(s_list(T) const* list, t_bool (*match)(T item));
#define c_lstffindi(T)	List_IndexOf_F(T)
//!@}



//!@doc Gets the amount of occurences of the given `item` in the given `list`
/*!
**	@param	list	The list in which to check for occurences of `item`
**	@param	item	The item to match with
**	@returns
**	The total amount of items in the given `list` which are equal to `item`
*/
//!@{
_GENERIC()
t_uint					List_Count(T)(s_list(T) const* list, T item);
#define c_lstcount(T)	List_Count(T)
//!@}

//!@doc Checks whether the given `list` contains the given `item`
/*!
**	@param	list	The list in which to check for an occurence of `item`
**	@param	item	The item to check for
**	@returns
**	`TRUE` if the given `list` does contain an item which is equal to the given `item`,
**	otherwise returns `FALSE`.
*/
//!@{
_GENERIC()
t_bool						List_Contains(T)(s_list(T) const* list, T item);
#define c_lstcontains(T)	List_Contains(T)
//!@}

//!@doc Checks whether the given `list` contains any item from the given `targets` list
/*!
**	@param	list	The list in which to check for an occurence of items from `target`
**	@param	targets	The list of items which are to be matched with `list`
**	@returns
**	`TRUE` if the given `list` does contain an item which is equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
//!@{
_GENERIC()
t_bool					List_Has(T)(s_list(T) const* list, s_list(T) const* targets);
#define c_lsthas(T)		List_Has(T)
//!@}

//!@doc Checks whether the given `list` only contains items which are present in the given `targets` list
/*!
**	@param	list	The list which which should only contain items from `target`
**	@param	targets	The list of items which are to be matched with `list`
**	@returns
**	`TRUE` if the given `list` only contains items which are equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
//!@{
_GENERIC()
t_bool					List_HasOnly(T)(s_list(T) const* list, s_list(T) const* targets);
#define c_lsthasonly(T)	List_HasOnly(T)
//!@}



/*
** ************************************************************************** *|
**                          List: functional operations                       *|
** ************************************************************************** *|
*/

//!@doc Iterates upon each item of the given `list`, applying the given function `f` for each of its items.
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	f		The function to call for each item of the given `list`
*/
//!@{
_GENERIC()
void					List_Iterate(T)(s_list(T)* list, void (*f)(T item));
#define c_lstiter(T)	List_Iterate(T)
//!@}

//!@doc Like List_Iterate(), but the user-supplied function receives the current index
//!@{
_GENERIC()
void					List_Iterate_I(T)(s_list(T)* list, void (*f)(T item, t_uint index));
#define c_lstiiter(T)	List_Iterate_I(T)
//!@}



//!@doc Creates a new list which is the result of applying the given `map` function for each item of `list`.
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	map		The function to call for each item of the given `list`
**	@returns
**	A new list, created by storing the return values of each call to the given `map` function.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Map(T)(s_list(T) const* list, T (*map)(T item));
#define c_lstmap(T)		List_Map(T)
//!@}

//!@doc Like List_Map(), but the user-supplied function receives the current index
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Map_I(T)(s_list(T) const* list, T (*map)(T item, t_uint index));
#define c_lstimap(T)	List_Map_I(T)
//!@}



//!@doc Creates a new list which is a subset of `list`, with only the items where the `filter` function returned `TRUE`
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	filter	The function to call to check if an item of `list` should be added to the result
**	@returns
**	A new list, created by only keeping the values of the given `list`
**	for which the corresponding call to the `filter` function returned `TRUE`.
*/
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Filter(T)(s_list(T) const* list, t_bool (*filter)(T item));
#define c_lstfilter(T)	List_Filter(T)
//!@}

//!@doc Like List_Filter(), but the user-supplied function receives the current index
//!@{
_MALLOC()
_GENERIC()
s_list(T)*				List_Filter_I(T)(s_list(T) const* list, t_bool (*filter)(T item, t_uint index));
#define c_lstifilter(T)	List_Filter_I(T)
//!@}



//!@doc Creates a single value by executing the given function `f` for each item of the given `list` 
/*!
**	The difference between List_Reduce() and List_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	list	The list to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `list`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `list`.
*/
//!@{
_GENERIC()
void*					List_Reduce(T)(s_list(T) const* list, void* (*f)(T item, void* acc));
#define c_lstreduce(T)	List_Reduce(T)
//!@}

//!@doc Like List_Reduce(), but the user-supplied function receives the current index
//!@{
_GENERIC()
void*					List_Reduce_I(T)(s_list(T) const* list, void* (*f)(T item, void* acc, t_uint index));
#define c_lstireduce(T)	List_Reduce_I(T)
//!@}

//!@doc Creates a single value by executing the given function `f` for each item of the given `list` 
/*!
**	The difference between List_Fold() and List_Reduce() is that with this function,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	list	The list to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `list`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `list`.
*/
//!@{
_GENERIC()
void*					List_Fold(T)(s_list(T) const* list, void* (*f)(T item, void* acc), void* initial);
#define c_lstfold(T)	List_Fold(T)
//!@}

//!@doc Like List_Reduce(), but the user-supplied function receives the current index
//!@{
_GENERIC()
void*					List_Fold_I(T)(s_list(T) const* list, void* (*f)(T item, void* acc, t_uint index), void* initial);
#define c_lstifold(T)	List_Fold_I(T)
//!@}



/*! @endgroup */
HEADER_END
#endif
