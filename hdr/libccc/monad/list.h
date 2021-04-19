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

#ifndef TYPE
#define TYPE	
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

#ifdef	list_T
#undef	list_T
#endif
#define list_T		CONCAT(list, TYPE)

#ifdef	s_list_T
#undef	s_list_T
#endif
#define s_list_T	CONCAT(s_list, TYPE)

//! This is a simple linked list struct, with dynamic content type
/*!
**	The list struct represents one chainlink in the linked-list. So, a linked-list
**	which contains 3 elements would consist of 3 different list structs,
**	all chained together via their `next` pointer, and the last element would
**	have this `next` pointer set to `NULL`.
*/
typedef struct list_T
{
//	struct list_T*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
	struct list_T*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	T				item;	//!< The content of this linked-list element
}				s_list_T;
TYPEDEF_ALIAS(	s_list_T, LIST, STRUCT)



#define foreach_s_list_init(		_TYPE_, _VAR_, _LIST_)	s_list_T* _VAR_##_i = (_LIST_);
#define foreach_s_list_exit(		_TYPE_, _VAR_, _LIST_)	if (_LIST_)
#define foreach_s_list_loop_init(	_TYPE_, _VAR_, _LIST_)	_TYPE_ _VAR_
#define foreach_s_list_loop_exit(	_TYPE_, _VAR_, _LIST_)	(_VAR_##_i != NULL) && ((_VAR_ = (_TYPE_)(_VAR_##_i->item)) || 1)
#define foreach_s_list_loop_incr(	_TYPE_, _VAR_, _LIST_)	_VAR_##_i = _VAR_##_i->next



/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

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
s_list_T*			List_New(t_uint n, ...);
#define c_lstnew	List_New //!< @alias{List_New}

//! Deletes all the elements in the list starting at `*a_list`
/*!
**	@param	a_list	The address ('&') of the beginning of the list - will be set to NULL.
*/
void				List_Delete(s_list_T* *a_list);
#define c_lstdel	List_Delete //!< @alias{List_Delete}

//! Returns a newly allocated copy of the given `list`
/*!
**	@param	list	The list to duplicate
**	@returns a newly allocated copy of the given linked `list`.
*/
_MALLOC()
s_list_T*			List_Duplicate(s_list_T const* list);
#define c_lstdup	List_Duplicate //!< @alias{List_Duplicate}



//! Gets the item at position `index` in the list, and returns that link chain
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the element to get
**	@returns the `index`th element in the given `list`.
**		Will return NULL if `index` is beyond the last element.
*/
s_list_T*			List_Get(s_list_T const* list, t_uint index);
#define c_lstget	List_Get //!< @alias{List_Get}

//! Sets the item at position `index` in the list, and returns that link chain TODO
/*!
**	@param	list	the list to look through
**	@param	index	the index in the list of the element to get
**	@returns the `index`th element in the given `list`.
**		Will return NULL if `index` is beyond the last element.
*/
s_list_T*			List_Set(s_list_T* list, t_uint index, T item);
#define c_lstset	List_Set //!< @alias{List_Set}

//! Returns a "shallow copy" of the given `list` (copies only pointers, not the underlying data)
/*!
**	@param	dest	The destination list to copy to
**	@param	src		The source list which should be copied
**	@returns a newly allocated copy of the given linked `list`.
**	The underlying data is not copied, only the s_list_T* structs are malloc'ed.
*/
s_list_T*			List_Copy(s_list_T* dest, s_list_T const* src, t_uint n);
#define c_lstcpy	List_Copy //!< @alias{List_Copy}

//! Returns a copy of a subsection of the given `list`, starting at `index` and taking `n` elements
/*!
**	Returns a newly allocated subsection of the given `list`, starting at `index`,
**	and copying at most `n` items from the given source `list`.
**	Will return NULL if `index` is too large or if `n` is 0.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` elements.
*/
_MALLOC()
s_list_T*				List_Sub(s_list_T const* list, t_uint index, t_uint n);
#define c_lstsub		List_Sub //!< @alias{List_Sub}
#define List_Subset		List_Sub
#define List_Subsection	List_Sub



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
**		The return value only exists to imitate List_Prepend() and List_Insert().
*/
s_list_T*				List_Append(s_list_T* list, s_list_T* elem);
#define c_lstappend		List_Append //!< @alias{List_Append}

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
s_list_T*				List_Prepend(s_list_T* list, s_list_T* elem);
#define c_lstprepend	List_Prepend //!< @alias{List_Prepend}

//! Inserts the given `item` at the given `index` of the given `list`
/*!
**	Inserts the given element `elem` at the given `index` of the list `list`.
**	If `index` is too large, the `elem` is appended to the end of the list.
**	If `elem` is NULL, then nothing is done by this function.
**
**	@param	list	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to insert in `alst` - if NULL, this function does nothing
**	@param	index	The index at which to insert the new list item
**	@returns the new beginning pointer for the given `list`. This pointer will only
**		be different from the given `list` pointer if `index` given is zero.
*/
s_list_T*				List_Insert(s_list_T* list, T item, t_uint index);
#define c_lstinsert		List_Insert //!< @alias{List_Insert}



//! TODO
s_list_T*				List_Remove(s_list_T* list, t_uint index);
#define c_lstremove		List_Remove //!< @alias{List_Remove}
#define c_lstdelone		List_Remove //!< @alias{List_Remove}

//! TODO
s_list_T*				List_RemoveAll(s_list_T* list, T target);
#define c_lstremall		List_RemoveAll //!< @alias{List_Remove}
#define c_lstdelall		List_RemoveAll //!< @alias{List_Remove}



//! TODO
_MALLOC()
s_list_T*				List_Replace(s_list_T const* array, T old, T new);
#define c_lstrep		List_Replace //!< @alias{Array_Replace}
#define c_lstreplace	List_Replace //!< @alias{Array_Replace}



/*
** ************************************************************************** *|
**                            List Checking Operations                        *|
** ************************************************************************** *|
*/

//! Returns the amount of elements in the given `list`
/*!
**	@param	list		the list to look through
**	@returns the amount of elements in the given `list`,
**	by traversing it, looping through every `next` pointer.
*/
t_uint					List_Size(s_list_T const* list);
#define c_lstsize		List_Size //!< @alias{List_Size}
#define List_Count		List_Size
#define List_Length		List_Size

//! Returns the first encountered item in the given `list` matching the given `target`
/*!
**	@param	list	the linked list to look through
**	@param	target	the `item` pointer to match against
**	@returns the first encountered element of the given linked `list`,
**		for which `(list->item == target)`, or `NULL` otherwise
*/
s_list_T*				List_Find(s_list_T const* list, T target);
#define c_lstfind		List_Find //!< @alias{List_Find}

//! Returns the index of the first encountered item in the given `list` matching the given `target`
/*!
**	@param	list	the linked list to look through
**	@param	target	the `item` pointer to match against
**	@returns the index of the first encountered element of the given `list`,
**		for which `(list->item == target)`, or `-1` otherwise.
*/
t_sint					List_IndexOf(s_list_T const* list, T target);
#define c_lstfindi		List_IndexOf //!< @alias{List_IndexOf}



//! TODO
t_bool					List_Equals(s_list_T const* list1, s_list_T const* list2);
#define c_lstequ		List_Equals //!< @alias{List_Equals}

//! TODO
t_bool					List_Equals_N(s_list_T const* list1, s_list_T const* list2, t_size n);
#define c_lstnequ		List_Equals_N //!< @alias{List_Equals_N}

//! TODO
t_sint					List_Compare(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2));
#define c_lstcmp		List_Compare //!< @alias{List_Compare}

//! TODO
t_sint					List_Compare_N(s_list_T const* list1, s_list_T const* list2, t_sint (*compare)(T item1, T item2), t_size n);
#define c_lstncmp		List_Compare_N //!< @alias{List_Compare_N}



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
void					List_Iterate(s_list_T* list, void (*f)(s_list_T* elem));
#define c_lstiter		List_Iterate //!< @alias{List_Iterate}

void					List_Iterate_I(s_list_T* list, void (*f)(s_list_T* elem, t_uint index));
#define c_lstiteri		List_Iterate_I //!< @alias{List_Iterate_I}



//! Creates a new list which is the result of applying the given function `f` to each element of `list`.
/*!
**	Creates a new list which is the result of applying
**	the given function `f` to each element of `list`.
*/
_MALLOC()
s_list_T*				List_Map(s_list_T const* list, T (*map)(s_list_T* elem));
#define c_lstmap		List_Map //!< @alias{List_Map}

_MALLOC()
s_list_T*				List_Map_I(s_list_T const* list, T (*map)(s_list_T* elem, t_uint index));
#define c_lstmapi		List_Map_I //!< @alias{List_Map_I}



//! TODO
_MALLOC()
s_list_T*				List_Filter(s_list_T const* list, t_bool (*filter)(s_list_T* elem));
#define c_lstfilt		List_Filter //!< @alias{List_Filter}

_MALLOC()
s_list_T*				List_Filter_I(s_list_T const* list, t_bool (*filter)(s_list_T* elem, t_uint index));
#define c_lstfilti		List_Filter_I //!< @alias{List_Filter_I}



/*! @} */
HEADER_END
#endif
