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

extern
s_list_T const CONCAT(NULL_LIST,T_NAME);



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
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

//! Allocates and returns a single list element from the given `item`.
/*!
**	@param	item	The value to store within the linked list element
**	@returns
**	A newly allocated linked list element containing `item`
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Item,T_NAME)(T item);
#define c_lstitem	CONCAT(List_Item,T_NAME)

//! Returns the amount of elements in the given `list`
/*!
**	@param	list		the list to look through
**	@returns
**	The amount of elements in the given `list`,
**	by traversing it, looping through every `next` pointer.
*/
_GENERIC()
t_uint				CONCAT(List_Length,T_NAME)(s_list_T const* list);
#define c_lstlen	CONCAT(List_Length,T_NAME)



//! Allocates and returns a linked list with `n` elements.
/*!
**	Allocates a new linked list, consisting of several `s_list` structs chained
**	together via their `next` pointer, with each struct storing an `item`.
**
**	@param	n		The amount of items in this list (amount of variadic args)
**	@returns
**	A newly allocated linked list which consists of `n` structs chained together.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_New,T_NAME)(t_uint n);
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



//! Deletes all the elements in the list starting at `*a_list`
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
*/
_GENERIC()
void				CONCAT(List_Delete,T_NAME)(s_list_T* list);
#define c_lstdel	CONCAT(List_Delete,T_NAME)

//! Deletes all the elements in the list starting at `*a_list`, calling `delete()` for each item
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
**	@param	delete	the function which should be executed for each item before deletion.
*/
_GENERIC()
void				CONCAT(List_Delete_F,T_NAME)(s_list_T* list, void (*delete)(T* item));
#define c_lstfdel	CONCAT(List_Delete_F,T_NAME)



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



//! Gets the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the element to get
**	@returns
**	The `index`th element in the given `list`,
**	or `NULL`, if `index` is beyond the last element.
*/
_GENERIC()
T*					CONCAT(List_Get,T_NAME)(s_list_T const* list, t_uint index);
#define c_lstget	CONCAT(List_Get,T_NAME)

//! Sets the item at position `index` in the list, and returns that link chain TODO
/*!
**	@param	list	the list in which an item should be set
**	@param	index	the index in the list of the element to get
**	@returns
**	The `index`th element in the given `list`,
**	or `NULL`, if `index` is beyond the last element.
*/
_GENERIC()
T*					CONCAT(List_Set,T_NAME)(s_list_T* list, t_uint index, T item);
#define c_lstset	CONCAT(List_Set,T_NAME)

//! Copies over `n` items from the given `src` list into the given `dest` list
/*!
**	@param	dest	The destination list to copy to
**	@param	src		The source list which should be copied
**	@param	n		The amount of list items to copy from `src` to `dest`
**	@returns
**	The given `dest` pointer.
*/
_GENERIC()
s_list_T*			CONCAT(List_Copy,T_NAME)(s_list_T* dest, s_list_T const* src, t_uint n);
#define c_lstcpy	CONCAT(List_Copy,T_NAME)

//! Returns a copy of a subsection of the given `list`, starting at `index` and taking `n` elements
/*!
**	@returns
**	A newly allocated subsection of the given `list`, starting at `index`,
**	and copying at most `n` items from the given source `list`.
**	Will return `NULL` if `index` is too large or if `(n == 0)`.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` elements.
*/
_MALLOC()
_GENERIC()
s_list_T*			CONCAT(List_Sub,T_NAME)(s_list_T const* list, t_uint index, t_uint n);
#define c_lstsub	CONCAT(List_Sub,T_NAME)



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
**	@returns
**	The new beginning pointer for the given `list`.
**	This return will always be the same as the given `list` argument.
**	The return value only exists to imitate `List_Prepend<T>()` and `List_Insert<T>()`.
*/
_GENERIC()
s_list_T*				CONCAT(List_Append,T_NAME)(s_list_T* list, s_list_T* elem);
#define c_lstappend		CONCAT(List_Append,T_NAME)

//! Inserts the given element `elem` to the beginning of the given `list`.
/*!
**	Inserts a new element `elem` into the list at the address `list`,
**	chaining this new element with the next element of this list
**	(ie: this function will set the `next` pointer to `list`).
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to prepend to `alst` - if NULL, this function does nothing
**	@returns
**	The new beginning pointer for the given `list`.
*/
_GENERIC()
s_list_T*				CONCAT(List_Prepend,T_NAME)(s_list_T* list, s_list_T* elem);
#define c_lstprepend	CONCAT(List_Prepend,T_NAME)

//! Inserts the given `item` at the given `index` of the given `list`
/*!
**	Inserts the given element `elem` at the given `index` of the list `list`.
**	If `index` is too large, then nothing is done by this function.
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to insert in `alst` - if NULL, this function does nothing
**	@param	index	The index at which to insert the new list item
**	@returns
**	The new beginning pointer for the given `list`. This pointer will only
**	be different from the given `list` pointer if `index` given is zero.
*/
_GENERIC()
s_list_T*				CONCAT(List_Insert,T_NAME)(s_list_T* list, T item, t_uint index);
#define c_lstinsert		CONCAT(List_Insert,T_NAME)



//! TODO
_GENERIC()
s_list_T*				CONCAT(List_Remove,T_NAME)(s_list_T* list, T item);
#define c_lstdelone		CONCAT(List_Remove,T_NAME)

//! TODO
_GENERIC()
s_list_T*				CONCAT(List_Remove_F,T_NAME)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelone	CONCAT(List_Remove_F,T_NAME)

//! TODO
_GENERIC()
s_list_T*				CONCAT(List_RemoveAll,T_NAME)(s_list_T* list, T item);
#define c_lstdelall		CONCAT(List_RemoveAll,T_NAME)

//! TODO
_GENERIC()
s_list_T*				CONCAT(List_RemoveAll_F,T_NAME)(s_list_T* list, T item, void (*delete)(T));
#define c_lstfdelall	CONCAT(List_RemoveAll_F,T_NAME)

//! TODO
_GENERIC()
s_list_T*				CONCAT(List_RemoveAt,T_NAME)(s_list_T* list, t_uint index);
#define c_lstdelat		CONCAT(List_RemoveAt,T_NAME)

//! TODO
_GENERIC()
s_list_T*				CONCAT(List_RemoveAt_F,T_NAME)(s_list_T* list, t_uint index, void (*delete)(T));
#define c_lstfdelat		CONCAT(List_RemoveAt_F,T_NAME)



//! TODO
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Replace,T_NAME)(s_list_T const* list, T old, T new);
#define c_lstrep		CONCAT(List_Replace,T_NAME)
#define c_lstreplace	CONCAT(List_Replace,T_NAME)



/*
** ************************************************************************** *|
**                            List Checking Operations                        *|
** ************************************************************************** *|
*/

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered element of the given linked `list`,
**	for which `(list->item == item)`, or `NULL` otherwise
*/
_GENERIC()
s_list_T const*			CONCAT(List_Find,T_NAME)(s_list_T const* list, T item);
#define c_lstfind		CONCAT(List_Find,T_NAME)

//! Returns the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The first encountered element of the given linked `list`,
**	for which `(list->item == item)`, or `NULL` otherwise
*/
_GENERIC()
s_list_T const*			CONCAT(List_Find_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffind		CONCAT(List_Find_F,T_NAME)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The index of the first encountered element of the given `list`,
**	for which `(list->item == item)`, or `-1` otherwise.
*/
_GENERIC()
t_sint					CONCAT(List_IndexOf,T_NAME)(s_list_T const* list, T item);
#define c_lstfindi		CONCAT(List_IndexOf,T_NAME)

//! Returns the index of the first encountered item in the given `list` matching the given `item`
/*!
**	@param	list	the linked list to look through
**	@param	item	the `item` pointer to match against
**	@returns
**	The index of the first encountered element of the given `list`,
**	for which `(list->item == item)`, or `-1` otherwise.
*/
_GENERIC()
t_sint					CONCAT(List_IndexOf_F,T_NAME)(s_list_T const* list, t_bool (*match)(T item));
#define c_lstffindi		CONCAT(List_IndexOf_F,T_NAME)



//! TODO
_GENERIC()
t_uint					CONCAT(List_Count,T_NAME)	(s_list_T const* list, T item);
#define c_lstcount		CONCAT(List_Count,T_NAME)

//! TODO
_GENERIC()
t_bool					CONCAT(List_Contains,T_NAME)(s_list_T const* list, T item);
#define c_lstcontains	CONCAT(List_Contains,T_NAME)

//! TODO
_GENERIC()
t_bool					CONCAT(List_Has,T_NAME)		(s_list_T const* list, s_list_T const* target);
#define c_lsthas		CONCAT(List_Has,T_NAME)

//! TODO
_GENERIC()
t_bool					CONCAT(List_HasOnly,T_NAME)	(s_list_T const* list, s_list_T const* target);
#define c_lsthasonly	CONCAT(List_HasOnly,T_NAME)



//! TODO
_GENERIC()
t_bool					CONCAT(List_Equals,T_NAME)(s_list_T const* list1, s_list_T const* list2);
#define c_lstequ		CONCAT(List_Equals,T_NAME)

//! TODO
_GENERIC()
t_bool					CONCAT(List_Equals_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_uint n);
#define c_lstnequ		CONCAT(List_Equals_N,T_NAME)

//! TODO
_GENERIC()
t_sint					CONCAT(List_Compare,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2));
#define c_lstcmp		CONCAT(List_Compare,T_NAME)

//! TODO
_GENERIC()
t_sint					CONCAT(List_Compare_N,T_NAME)(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_uint n);
#define c_lstncmp		CONCAT(List_Compare_N,T_NAME)



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
_GENERIC()
void					CONCAT(List_Iterate,T_NAME)(s_list_T* list, void (*f)(T item));
#define c_lstiter		CONCAT(List_Iterate,T_NAME)

_GENERIC()
void					CONCAT(List_Iterate_I,T_NAME)(s_list_T* list, void (*f)(T item, t_uint index));
#define c_lstiteri		CONCAT(List_Iterate_I,T_NAME)



//! Creates a new list which is the result of applying the given function `f` to each element of `list`.
/*!
**	Creates a new list which is the result of applying
**	the given function `f` to each element of `list`.
*/
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Map,T_NAME)(s_list_T const* list, T (*map)(T item));
#define c_lstmap		CONCAT(List_Map,T_NAME)

_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Map_I,T_NAME)(s_list_T const* list, T (*map)(T item, t_uint index));
#define c_lstmapi		CONCAT(List_Map_I,T_NAME)



//! TODO
_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Filter,T_NAME)(s_list_T const* list, t_bool (*filter)(T item));
#define c_lstfilt		CONCAT(List_Filter,T_NAME)

_MALLOC()
_GENERIC()
s_list_T*				CONCAT(List_Filter_I,T_NAME)(s_list_T const* list, t_bool (*filter)(T item, t_uint index));
#define c_lstfilti		CONCAT(List_Filter_I,T_NAME)



//! TODO List_Reduce() ?



/*! @} */
HEADER_END
#endif
