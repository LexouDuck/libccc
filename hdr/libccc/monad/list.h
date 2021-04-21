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

#define List_T		CONCAT(List, T_NAME)
#define list_T		CONCAT(list, T_NAME)
#define s_list_T	CONCAT(s_list, T_NAME)

//! This is a simple linked list struct, with dynamic content type
/*!
**	The list struct represents one chainlink in the linked-list. So, a linked-list
**	which contains 3 elements would consist of 3 different list structs,
**	all chained together via their `next` pointer, and the last element would
**	have this `next` pointer set to `NULL`.
*/
typedef struct list_T
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	struct list_T*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
#endif
	struct list_T*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	T				item;	//!< The content of this linked-list element
}				s_list_T;



#define foreach_s_list(_TYPE_, _VAR_, _LIST_)		foreach (_TYPE_, _VAR_, s_list, _LIST_)

#define foreach_s_list_init(		_TYPE_, _VAR_, _LIST_)	struct _##_VAR_{ struct _##_VAR_*next; _TYPE_ item; }* _VAR_##_i = (struct _##_VAR_*)(_LIST_);
#define foreach_s_list_exit(		_TYPE_, _VAR_, _LIST_)	if ((void*)(_LIST_) != NULL)
#define foreach_s_list_loop_init(	_TYPE_, _VAR_, _LIST_)	_TYPE_ _VAR_ = (_TYPE_)(_VAR_##_i->item)
#define foreach_s_list_loop_exit(	_TYPE_, _VAR_, _LIST_)	(_VAR_##_i != NULL)
#define foreach_s_list_loop_incr(	_TYPE_, _VAR_, _LIST_)	_VAR_##_i = _VAR_##_i->next
#define foreach_s_list_loop_setv(	_TYPE_, _VAR_, _LIST_)	_VAR_ = (_VAR_##_i == NULL ? _VAR_ : (_TYPE_)(_VAR_##_i->item))



/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

//! Allocates and returns a single list element from the given `item`.
/*!
**	@param	item	The value to store within the linked list element
**	@returns a newly allocated linked list element containing `item`
*/
_MALLOC()
s_list_T*			CONCAT(List_T,_Item)(T item);
#define c_lstitem	CONCAT(List_T,_Item)

//! Returns the amount of elements in the given `list`
/*!
**	@param	list		the list to look through
**	@returns the amount of elements in the given `list`,
**	by traversing it, looping through every `next` pointer.
*/
t_uint				CONCAT(List_T,_Length)(s_list_T const* list);
#define c_lstlen	CONCAT(List_T,_Length)



//! Allocates and returns a list element from the given list of arguments.
/*!
**	Allocates a new linked list, consisting of several `s_list` structs chained
**	together via their `next` pointer, with each struct storing an `item`.
**	This function accepts a variadic list of arguments to initialize the list.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@param	...		The variadic list of arguments: they must all be of type `T`
**	@returns a newly allocated linked list which consists of `n` structs chained together.
*/
_MALLOC()
s_list_T*			CONCAT(List_T,_New)(t_uint n, ...);
#define c_lstnew	CONCAT(List_T,_New)

//! Deletes all the elements in the list starting at `*a_list`
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
*/
void				CONCAT(List_T,_Delete)(s_list_T* *a_list);
#define c_lstdel	CONCAT(List_T,_Delete)

//! Returns a newly allocated copy of the given `list`
/*!
**	@param	list	The list to duplicate
**	@returns a newly allocated copy of the given linked `list`.
*/
_MALLOC()
s_list_T*			CONCAT(List_T,_Duplicate)(s_list_T const* list);
#define c_lstdup	CONCAT(List_T,_Duplicate)



//! Gets the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the element to get
**	@returns the `index`th element in the given `list`.
**		Will return NULL if `index` is beyond the last element.
*/
s_list_T*			CONCAT(List_T,_Get)(s_list_T const* list, t_uint index);
#define c_lstget	CONCAT(List_T,_Get)

//! Sets the item at position `index` in the list, and returns that link chain TODO
/*!
**	@param	list	the list in which an item should be set
**	@param	index	the index in the list of the element to get
**	@returns the `index`th element in the given `list`.
**		Will return NULL if `index` is beyond the last element.
*/
s_list_T*			CONCAT(List_T,_Set)(s_list_T* list, t_uint index, T item);
#define c_lstset	CONCAT(List_T,_Set)

//! Copies over `n` items from the given `src` list into the given `dest` list
/*!
**	@param	dest	The destination list to copy to
**	@param	src		The source list which should be copied
**	@param	n		The amount of list items to copy from `src` to `dest`
**	@returns the given `dest` pointer.
*/
s_list_T*			CONCAT(List_T,_Copy)(s_list_T* dest, s_list_T const* src, t_uint n);
#define c_lstcpy	CONCAT(List_T,_Copy)

//! Returns a copy of a subsection of the given `list`, starting at `index` and taking `n` elements
/*!
**	Returns a newly allocated subsection of the given `list`, starting at `index`,
**	and copying at most `n` items from the given source `list`.
**	Will return NULL if `index` is too large or if `n` is 0.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` elements.
*/
_MALLOC()
s_list_T*			CONCAT(List_T,_Sub)(s_list_T const* list, t_uint index, t_uint n);
#define c_lstsub	CONCAT(List_T,_Sub)



/*
** ************************************************************************** *|
**                            List Editing Operations                         *|
** ************************************************************************** *|
*/

//! Appends the given element `elem` to the end of the given `list`.
/*!
**	Appends the given element `elem` to the end of the list starting at `list`.
**	If `list` is NULL, it'll append `elem` at index 0, creating a 1-elem list.
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to prepend to `alst` - if NULL, this function does nothing
**	@returns the new beginning pointer for the given `list`.
**		This return will always be the same as the given `list` argument.
**		The return value only exists to imitate CONCAT(List_T,_Prepend)() and CONCAT(List_T,_Insert)().
*/
s_list_T*				CONCAT(List_T,_Append)(s_list_T* list, s_list_T* elem);
#define c_lstappend		CONCAT(List_T,_Append)

//! Inserts the given element `elem` to the beginning of the given `list`.
/*!
**	Inserts a new element `elem` into the list at the address `list`,
**	chaining this new element with the next element of this list
**	(ie: this function will set the `next` pointer to `list`).
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to prepend to `alst` - if NULL, this function does nothing
**	@returns the new beginning pointer for the given `list`.
*/
s_list_T*				CONCAT(List_T,_Prepend)(s_list_T* list, s_list_T* elem);
#define c_lstprepend	CONCAT(List_T,_Prepend)

//! Inserts the given `item` at the given `index` of the given `list`
/*!
**	Inserts the given element `elem` at the given `index` of the list `list`.
**	If `index` is too large, then nothing is done by this function.
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to insert in `alst` - if NULL, this function does nothing
**	@param	index	The index at which to insert the new list item
**	@returns the new beginning pointer for the given `list`. This pointer will only
**		be different from the given `list` pointer if `index` given is zero.
*/
s_list_T*				CONCAT(List_T,_Insert)(s_list_T* list, T item, t_uint index);
#define c_lstinsert		CONCAT(List_T,_Insert)



//! TODO
s_list_T*				CONCAT(List_T,_Remove)(s_list_T* list, T item);
#define c_lstdelone		CONCAT(List_T,_Remove)

//! TODO
s_list_T*				CONCAT(List_T,_Remove_F)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelone	CONCAT(List_T,_Remove_F)

//! TODO
s_list_T*				CONCAT(List_T,_RemoveAll)(s_list_T* list, T item);
#define c_lstdelall		CONCAT(List_T,_RemoveAll)

//! TODO
s_list_T*				CONCAT(List_T,_RemoveAll_F)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelall	CONCAT(List_T,_RemoveAll_F)

//! TODO
s_list_T*				CONCAT(List_T,_RemoveAt)(s_list_T* list, t_uint index);
#define c_lstdelat		CONCAT(List_T,_RemoveAt)

//! TODO
s_list_T*				CONCAT(List_T,_RemoveAt_F)(s_list_T* list, t_uint index, void (*delete)(T));
#define c_lstfdelat		CONCAT(List_T,_RemoveAt_F)



//! TODO
_MALLOC()
s_list_T*				CONCAT(List_T,_Replace)(s_list_T const* list, T old, T new);
#define c_lstrep		CONCAT(List_T,_Replace)
#define c_lstreplace	CONCAT(List_T,_Replace)



/*
** ************************************************************************** *|
**                            List Checking Operations                        *|
** ************************************************************************** *|
*/

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns the first encountered element of the given linked `list`,
**		for which `(list->item == item)`, or `NULL` otherwise
*/
s_list_T const*			CONCAT(List_T,_Find)(s_list_T const* list, T item);
#define c_lstfind		CONCAT(List_T,_Find)

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns the first encountered element of the given linked `list`,
**		for which `(list->item == item)`, or `NULL` otherwise
*/
s_list_T const*			CONCAT(List_T,_Find_F)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffind		CONCAT(List_T,_Find_F)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns the index of the first encountered element of the given `list`,
**		for which `(list->item == item)`, or `-1` otherwise.
*/
t_sint					CONCAT(List_T,_IndexOf)(s_list_T const* list, T item);
#define c_lstfindi		CONCAT(List_T,_IndexOf)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns the index of the first encountered element of the given `list`,
**		for which `(list->item == item)`, or `-1` otherwise.
*/
t_sint					CONCAT(List_T,_IndexOf_F)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffindi		CONCAT(List_T,_IndexOf_F)



//! TODO
t_uint					CONCAT(List_T,_Count)	(s_list_T const* list, T item);
#define c_lstcount		CONCAT(List_T,_Count)

//! TODO
t_bool					CONCAT(List_T,_Contains)(s_list_T const* list, T item);
#define c_lstcontains	CONCAT(List_T,_Contains)

//! TODO
t_bool					CONCAT(List_T,_Has)		(s_list_T const* list, s_list_T const* target);
#define c_lsthas		CONCAT(List_T,_Has)

//! TODO
t_bool					CONCAT(List_T,_HasOnly)	(s_list_T const* list, s_list_T const* target);
#define c_lsthasonly	CONCAT(List_T,_HasOnly)



//! TODO
t_bool					CONCAT(List_T,_Equals)(s_list_T const* list1, s_list_T const* list2);
#define c_lstequ		CONCAT(List_T,_Equals)

//! TODO
t_bool					CONCAT(List_T,_Equals_N)(s_list_T const* list1, s_list_T const* list2, t_uint n);
#define c_lstnequ		CONCAT(List_T,_Equals_N)

//! TODO
t_sint					CONCAT(List_T,_Compare)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2));
#define c_lstcmp		CONCAT(List_T,_Compare)

//! TODO
t_sint					CONCAT(List_T,_Compare_N)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_lstncmp		CONCAT(List_T,_Compare_N)



/*
** ************************************************************************** *|
**                           List Functional Operations                       *|
** ************************************************************************** *|
*/

//! Iterates upon each element of the given `list`, applying the given function `f` to each of its elements.
/*!
**	Iterates upon each element of the given `list`,
**	applying the given function `f` to each of its elements.
*/
void					CONCAT(List_T,_Iterate)(s_list_T* list, void (*f)(T item));
#define c_lstiter		CONCAT(List_T,_Iterate)

void					CONCAT(List_T,_Iterate_I)(s_list_T* list, void (*f)(T item, t_uint index));
#define c_lstiteri		CONCAT(List_T,_Iterate_I)



//! Creates a new list which is the result of applying the given function `f` to each element of `list`.
/*!
**	Creates a new list which is the result of applying
**	the given function `f` to each element of `list`.
*/
_MALLOC()
s_list_T*				CONCAT(List_T,_Map)(s_list_T const* list, T (*map)(T item));
#define c_lstmap		CONCAT(List_T,_Map)

_MALLOC()
s_list_T*				CONCAT(List_T,_Map_I)(s_list_T const* list, T (*map)(T item, t_uint index));
#define c_lstmapi		CONCAT(List_T,_Map_I)



//! TODO
_MALLOC()
s_list_T*				CONCAT(List_T,_Filter)(s_list_T const* list, t_bool (*filter)(T item));
#define c_lstfilt		CONCAT(List_T,_Filter)

_MALLOC()
s_list_T*				CONCAT(List_T,_Filter_I)(s_list_T const* list, t_bool (*filter)(T item, t_uint index));
#define c_lstfilti		CONCAT(List_T,_Filter_I)



//! TODO List_Reduce() ?



/*! @} */
HEADER_END
#endif
