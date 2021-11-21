/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/list.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_LIST_H
#define __LIBCCC_MONAD_LIST_H
/*!@group{libccc_monad_list}
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

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define list_T		CONCAT(list, T_NAME)
#define s_list_T	CONCAT(s_list, T_NAME)

//! This is a simple linked list struct, with dynamic content type
/*!
**	The list struct represents one chainlink in the linked-list. So, a linked-list
**	which contains 3 items would consist of 3 different list structs,
**	all chained together via their `next` pointer, and the last item would
**	have this `next` pointer set to `NULL`.
*/
typedef struct list_T
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	struct list_T*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
#endif
	struct list_T*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	T				item;	//!< The content of this linked-list item
}				s_list_T;

/* TODO find a way to avoid multiple definitions
extern
s_list_T const CONCAT(NULL_LIST,T_NAME);
s_list_T const CONCAT(NULL_LIST,T_NAME) = (s_list_T)
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	.prev = NULL,
#endif
	.next = NULL,
	.item = T_DEFAULT,
};
*/



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



/*
** ************************************************************************** *|
**                            List: basic operations                          *|
** ************************************************************************** *|
*/

//! Allocates and returns a single list item from the given `item`.
/*!
**	@param	item	The value to store within the linked list item
**	@returns
**	A newly allocated linked list item containing `item`
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Item,T_NAME)(T item);
#define c_lstitem	CONCAT(List_Item,T_NAME)

//! Returns the amount of items in the given `list`
/*!
**	@param	list		the list to look through
**	@returns
**	The amount of items in the given `list`,
**	by traversing it, looping through every `next` pointer.
*/
_GENERIC()
t_uint				CONCAT(List_Length,T_NAME)(s_list_T const* list);
#define c_lstlen	CONCAT(List_Length,T_NAME)



//! Gets the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the item to get
**	@returns
**	The `index`th item in the given `list`,
**	or `NULL`, if `index` is beyond the last item.
*/
_GENERIC()
T*					CONCAT(List_Get,T_NAME)(s_list_T const* list, t_uint index);
#define c_lstget	CONCAT(List_Get,T_NAME)

//! Sets the value of the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list in which an item should be set
**	@param	index	the index in the list of the item to set
**	@param	item	the new value to assign
**	@returns
**	The `index`th item in the given `list`,
**	or `NULL`, if `index` is beyond the last item.
*/
_GENERIC()
T*					CONCAT(List_Set,T_NAME)(s_list_T* list, t_uint index, T item);
#define c_lstset	CONCAT(List_Set,T_NAME)



/*
** ************************************************************************** *|
**                          List: creation operations                         *|
** ************************************************************************** *|
*/

//! Allocates a new linked list containing `n` items, each set to the given `value`
/*!
**	Allocates a new linked list, consisting of several `s_list` structs chained
**	together via their `next` pointer, with each struct storing an `item`.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	value	The initial value to set for each of the `n` items
**	@returns
**	A newly allocated linked list which consists of `n` list structs chained together.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_New,T_NAME)(t_uint n, T value);
#define c_lstnew	CONCAT(List_New,T_NAME)



//! Allocates and returns a linked list, created from the given variadic arguments.
/*!
**	This function accepts a variadic list of arguments to initialize the list.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: they must all be of type `T`
**	@returns
**	A newly allocated linked list which consists of `n` structs chained together.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Create,T_NAME)(t_uint n, ...);
#define c_lstcreate	CONCAT(List_Create,T_NAME)



//! Returns a newly allocated copy of the given `list`
/*!
**	@param	list	The list to duplicate
**	@returns
**	A newly allocated copy of the given linked `list`.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Duplicate,T_NAME)(s_list_T const* list);
#define c_lstdup	CONCAT(List_Duplicate,T_NAME)



//! Copies over `n` items from the given `src` list into the given `dest` list
/*!
**	@param	dest	The destination list to copy to
**	@param	src		The source list which should be copied
**	@param	n		The amount of list items to copy from `src` to `dest`
**	@returns
**	The given `dest` pointer. The list is modified in-place.
*/
_GENERIC()
s_list_T*			CONCAT(List_Copy,T_NAME)(s_list_T* dest, s_list_T const* src, t_uint n);
#define c_lstcpy	CONCAT(List_Copy,T_NAME)



//! Creates a new list from a subsection of the given `list`, starting at `index` and taking `n` items
/*!
**	@returns
**	A newly allocated subsection of the given `list`, starting at `index`,
**	and copying at most `n` items from the given source `list`.
**	Will return `NULL` if `index` is too large or if `(n == 0)`.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` items.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Sub,T_NAME)(s_list_T const* list, t_uint index, t_uint n);
#define c_lstsub	CONCAT(List_Sub,T_NAME)



/*
** ************************************************************************** *|
**                          List: deletion operations                         *|
** ************************************************************************** *|
*/

//! Deletes all the items in the list starting at `*a_list`
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
*/
_GENERIC()
void				CONCAT(List_Delete,T_NAME)(s_list_T* list);
#define c_lstdel	CONCAT(List_Delete,T_NAME)

//! Deletes all the items in the list starting at `*a_list`, calling `delete()` for each item
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
**	@param	delete	the function which should be executed for each item before deletion.
*/
_GENERIC()
void				CONCAT(List_Delete_F,T_NAME)(s_list_T* list, void (*delete)(T* item));
#define c_lstfdel	CONCAT(List_Delete_F,T_NAME)



/*
** ************************************************************************** *|
**                           List: editing operations                         *|
** ************************************************************************** *|
*/

//! Appends the given item `item` to the end of the given `list`.
/*!
**	Appends the given item `item` to the end of the list starting at `list`.
**	If `list` is NULL, it'll append `item` at index 0, creating a 1-item list.
**
**	@param	list	The pointer to the beginning of the list (the address of the first item)
**	@param	item	The list item to append to the given `list`
**	@returns
**	The new beginning pointer for the given `list`. The list is modified in-place.
**	This return will be the same as the given `list` argument, unless `list == NULL`.
*/
_GENERIC()
s_list_T*				CONCAT(List_Add,T_NAME)(s_list_T* list, T item);
#define c_lstadd		CONCAT(List_Add,T_NAME)



//! Inserts the given `item` at the given `index` of the given `list`
/*!
**	Inserts the given `item` at the given `index` of the given `list`.
**	If `index` is greater than the length of the list, then nothing is done.
**
**	@param	list	The pointer to the beginning of the list (the address of the first item)
**	@param	item	The item to insert into the given `list`
**	@param	index	The index at which to insert the new list item
**	@returns
**	The new beginning pointer for the given `list`. The list is modified in-place.
**	The return value will be the same as the given `list` argument,
**	unless `list == NULL`, and the `index` given is zero.
*/
_GENERIC()
s_list_T*				CONCAT(List_Insert,T_NAME)(s_list_T* list, T item, t_uint index);
#define c_lstinsert		CONCAT(List_Insert,T_NAME)



//! Creates a new list from the given `list`, where any occurence of `old` is replaced with `new`
/*!
**	@param	list	The list to use as a basis for copy and item replacement
**	@param	old		The item to be replaced
**	@param	new		The replacement for the resulting list
**	@returns
**	A newly created list copied from `list`, in which in any item equal to `old`
**	will instead have a value of `new`, or `NULL` if an error occurred.
*/
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Replace,T_NAME)(s_list_T const* list, T old, T new);
#define c_lstrep		CONCAT(List_Replace,T_NAME)
#define c_lstreplace	CONCAT(List_Replace,T_NAME)



// TODO List_Reverse()



//! Removes a single item from the given `list`, at the given `index`
/*!
**	@param	list	The list in which to remove an item
**	@param	index	The index of the item to delete from the list
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless the `index` given is zero.
*/
_GENERIC()
s_list_T*				CONCAT(List_RemoveAt,T_NAME)(s_list_T* list, t_uint index);
#define c_lstdelat		CONCAT(List_RemoveAt,T_NAME)

//! Like List_RemoveAt(), but you can supply a custom `delete` function
_GENERIC()
s_list_T*				CONCAT(List_RemoveAt_F,T_NAME)(s_list_T* list, t_uint index, void (*delete)(T));
#define c_lstfdelat		CONCAT(List_RemoveAt_F,T_NAME)

//! Removes the first item from the given `list` which is equal to the given `item`
/*!
**	@param	list	The list in which to remove an item
**	@param	item	The item value which is to be removed from `list`
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless the matched item is at position zero.
*/
_GENERIC()
s_list_T*				CONCAT(List_Remove,T_NAME)(s_list_T* list, T item);
#define c_lstdelone		CONCAT(List_Remove,T_NAME)

//! Like List_Remove(), but you can supply a custom `delete` function
_GENERIC()
s_list_T*				CONCAT(List_Remove_F,T_NAME)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelone	CONCAT(List_Remove_F,T_NAME)

//! Removes any items which are equal to the given `item` from the given `list`
/*!
**	@param	list	The list in which to remove items
**	@param	item	The item value for which any occurrences are to be removed from `list`
**	@returns
**	The list given as argument. The list is edited in-place, no allocation is performed.
**	This pointer will typically be equal to `list`, unless a matched item is at position zero.
*/
_GENERIC()
s_list_T*				CONCAT(List_RemoveAll,T_NAME)(s_list_T* list, T item);
#define c_lstdelall		CONCAT(List_RemoveAll,T_NAME)

//! Like List_RemoveAll(), but you can supply a custom `delete` function
_GENERIC()
s_list_T*				CONCAT(List_RemoveAll_F,T_NAME)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelall	CONCAT(List_RemoveAll_F,T_NAME)



/*
** ************************************************************************** *|
**                         List concatenation operations                      *|
** ************************************************************************** *|
*/

//! Creates a new list which is the concatenation of `list1` and `list2`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
*/
_GENERIC()
s_list_T*				CONCAT(List_Concat,T_NAME)(s_list_T const* list1, s_list_T const* list2);
#define c_lstcat		CONCAT(List_Concat,T_NAME)
#define c_lstconcat		CONCAT(List_Concat,T_NAME)

//! Creates a new list which is the concatenation of `list1` and `list2`, and deletes `list1`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	The `list1` argument will be deleted.
*/
_GENERIC()
s_list_T*				CONCAT(List_Append,T_NAME)(s_list_T* list1, s_list_T const* list2);
#define c_lstappend		CONCAT(List_Append,T_NAME)

//! Creates a new list which is the concatenation of `list1` and `list2`, and deletes `list2`
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	The `list2` argument will be deleted.
*/
_GENERIC()
s_list_T*				CONCAT(List_Prepend,T_NAME)(s_list_T const* list1, s_list_T* list2);
#define c_lstprepend	CONCAT(List_Prepend,T_NAME)

//! Creates a new list which is the concatenation of `list1` and `list2`, and deletes both lists
/*!
**	@param	list1	The left-hand list to concatenate
**	@param	list2	The right-hand list to concatenate
**	@returns
**	A newly allocated list, created by concatenating `list1` and `list2`.
**	Both `list1` and `list2` will be deleted.
*/
_GENERIC()
s_list_T*				CONCAT(List_Merge,T_NAME)(s_list_T* list1, s_list_T* list2);
#define c_lstmerge		CONCAT(List_Merge,T_NAME)



/*
** ************************************************************************** *|
**                          List: comparison operations                       *|
** ************************************************************************** *|
*/

//! Checks if two lists have the same content
/*!
**	@param	list1	The first list to check for equality
**	@param	list2	The second list to check for equality
**	@returns
**	`TRUE` if each item of both lists are equal, and the lists have the same amount of items.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
_GENERIC()
t_bool					CONCAT(List_Equals,T_NAME)(s_list_T const* list1, s_list_T const* list2);
#define c_lstequ		CONCAT(List_Equals,T_NAME)

//! Checks if two lists have the same content, for the `n` first items
/*!
**	@param	list1	The first list to check for equality
**	@param	list2	The second list to check for equality
**	@param	n		The amount of items to check for equality
**	@returns
**	`TRUE` if the first `n` items of both lists are equal.
**	If both pointers given are identical, it simply returns `TRUE` without even checking.
**	Otherwise, `FALSE` is returned.
*/
_GENERIC()
t_bool					CONCAT(List_Equals_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_uint n);
#define c_lstnequ		CONCAT(List_Equals_N,T_NAME)



//! Compares two lists using the given `compare` function
/*!
**	@param	list1	The first list to compare
**	@param	list2	The second list to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
_GENERIC()
t_sint					CONCAT(List_Compare,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2));
#define c_lstcmp		CONCAT(List_Compare,T_NAME)

//! Compares two lists using the given `compare` function, for the `n` first items
/*!
**	@param	list1	The first list to compare
**	@param	list2	The second list to compare
**	@param	compare	The function used to determine whether items are considered "equal" or not
**	@param	n		The amount of items to check for equality
**	@returns
**	The first non-zero value returned by the `compare` function given.
*/
_GENERIC()
t_sint					CONCAT(List_Compare_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_lstncmp		CONCAT(List_Compare_N,T_NAME)



/*
** ************************************************************************** *|
**                           List: checking operations                        *|
** ************************************************************************** *|
*/

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	The linked list to look through
**	@param	item	The `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `NULL` if no such item was found.
*/
_GENERIC()
s_list_T const*			CONCAT(List_Find,T_NAME)(s_list_T const* list, T item);
#define c_lstfind		CONCAT(List_Find,T_NAME)

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	The linked list to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `list` for which the given `match` function
**	returned `TRUE`. Otherwise, returns `NULL` if no such item was found.
*/
_GENERIC()
s_list_T const*			CONCAT(List_Find_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffind		CONCAT(List_Find_F,T_NAME)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `-1` if no such item was found.
*/
_GENERIC()
t_sint					CONCAT(List_IndexOf,T_NAME)(s_list_T const* list, T item);
#define c_lstfindi		CONCAT(List_IndexOf,T_NAME)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	match	The function used to compare items to the target value
**	@returns
**	The first encountered item of the given linked `list` which is equal to `item`,
**	or `-1` if no such item was found.
*/
_GENERIC()
t_sint					CONCAT(List_IndexOf_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffindi		CONCAT(List_IndexOf_F,T_NAME)



//! Gets the amount of occurences of the given `item` in the given `list`
/*!
**	@param	list	The list in which to check for occurences of `item`
**	@param	item	The item to match with
**	@returns
**	The total amount of items in the given `list` which are equal to `item`
*/
_GENERIC()
t_uint					CONCAT(List_Count,T_NAME)	(s_list_T const* list, T item);
#define c_lstcount		CONCAT(List_Count,T_NAME)

//! Checks whether the given `list` contains the given `item`
/*!
**	@param	list	The list in which to check for an occurence of `item`
**	@param	item	The item to check for
**	@returns
**	`TRUE` if the given `list` does contain an item which is equal to the given `item`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(List_Contains,T_NAME)(s_list_T const* list, T item);
#define c_lstcontains	CONCAT(List_Contains,T_NAME)

//! Checks whether the given `list` contains any item from the given `targets` list
/*!
**	@param	list	The list in which to check for an occurence of items from `target`
**	@param	targets	The list of items which are to be matched with `list`
**	@returns
**	`TRUE` if the given `list` does contain an item which is equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(List_Has,T_NAME)		(s_list_T const* list, s_list_T const* targets);
#define c_lsthas		CONCAT(List_Has,T_NAME)

//! Checks whether the given `list` only contains items which are present in the given `targets` list
/*!
**	@param	list	The list which which should only contain items from `target`
**	@param	targets	The list of items which are to be matched with `list`
**	@returns
**	`TRUE` if the given `list` only contains items which are equal to any item in `targets`,
**	otherwise returns `FALSE`.
*/
_GENERIC()
t_bool					CONCAT(List_HasOnly,T_NAME)	(s_list_T const* list, s_list_T const* targets);
#define c_lsthasonly	CONCAT(List_HasOnly,T_NAME)



/*
** ************************************************************************** *|
**                          List: functional operations                       *|
** ************************************************************************** *|
*/

//! Iterates upon each item of the given `list`, applying the given function `f` for each of its items.
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	f		The function to call for each item of the given `list`
*/
_GENERIC()
void					CONCAT(List_Iterate,T_NAME)(s_list_T* list, void (*f)(T item));
#define c_lstiter		CONCAT(List_Iterate,T_NAME)

//! Like List_Iterate(), but the user-supplied function receives the current index
_GENERIC()
void					CONCAT(List_Iterate_I,T_NAME)(s_list_T* list, void (*f)(T item, t_uint index));
#define c_lstiiter		CONCAT(List_Iterate_I,T_NAME)



//! Creates a new list which is the result of applying the given `map` function for each item of `list`.
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	map		The function to call for each item of the given `list`
**	@returns
**	A new list, created by storing the return values of each call to the given `map` function.
*/
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Map,T_NAME)(s_list_T const* list, T (*map)(T item));
#define c_lstmap		CONCAT(List_Map,T_NAME)

//! Like List_Map(), but the user-supplied function receives the current index
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Map_I,T_NAME)(s_list_T const* list, T (*map)(T item, t_uint index));
#define c_lstimap		CONCAT(List_Map_I,T_NAME)



//! Creates a new list which is a subset of `list`, with only the items where the `filter` function returned `TRUE`
/*!
**	@param	list	The list whose items should be iterated upon
**	@param	filter	The function to call to check if an item of `list` should be added to the result
**	@returns
**	A new list, created by storing the return values of each call to the given `map` function.
*/
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Filter,T_NAME)(s_list_T const* list, t_bool (*filter)(T item));
#define c_lstfilter		CONCAT(List_Filter,T_NAME)

//! Like List_Filter(), but the user-supplied function receives the current index
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Filter_I,T_NAME)(s_list_T const* list, t_bool (*filter)(T item, t_uint index));
#define c_lstifilter	CONCAT(List_Filter_I,T_NAME)



//! Creates a single value by executing the given function `f` for each item of the given `list` 
/*!
**	The difference between this List_Reduce() and List_Fold() is that with this function,
**	the initial value which will be passed as the `acc` parameter is a `NULL` pointer.
**
**	@param	list	The list to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `list`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `list`.
*/
_GENERIC()
void*					CONCAT(List_Reduce,T_NAME)(s_list_T const* list, void* (*f)(T item, void* acc));
#define c_lstreduce		CONCAT(List_Reduce,T_NAME)

//! Like List_Reduce(), but the user-supplied function receives the current index
_GENERIC()
void*					CONCAT(List_Reduce_I,T_NAME)(s_list_T const* list, void* (*f)(T item, void* acc, t_uint index));
#define c_lstireduce	CONCAT(List_Reduce_I,T_NAME)

//! Creates a single value by executing the given function `f` for each item of the given `list` 
/*!
**	The difference between this List_Fold() and List_Reduce() is that with ,
**	you can supply an initial value for the `acc` parameter, which will be passed to the first call of `f`.
**
**	@param	list	The list to iterate upon
**	@param	reduce	The user-specified function to execute for each item of `list`.
**					It takes the previous return value `acc` as argument, and its return value may be of any type
**	@returns
**	A single value, of any type, which is created by calling `f()` for each item of the given `list`.
*/
_GENERIC()
void*					CONCAT(List_Fold,T_NAME)(s_list_T const* list, void* (*f)(T item, void* acc), void* initial);
#define c_lstfold		CONCAT(List_Fold,T_NAME)

//! Like List_Reduce(), but the user-supplied function receives the current index
_GENERIC()
void*					CONCAT(List_Fold_I,T_NAME)(s_list_T const* list, void* (*f)(T item, void* acc, t_uint index), void* initial);
#define c_lstifold		CONCAT(List_Fold_I,T_NAME)



/*! @} */
HEADER_END
#endif
