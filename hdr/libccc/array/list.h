/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/list.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ARRAY_LIST_H
#define __LIBCCC_ARRAY_LIST_H
/*! @file libccc/array/list.h
**	This header defines a simple linked list type and utility functions for it.
**	@defgroup libccc_array_list
**	@grouporder{31}
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

typedef struct s_array_	s_array;

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This is a simple linked list struct, with dynamic content type
/*!
**	The `s_list` struct represents one chainlink in the linked-list, so a
**	linked-list with 3 elements would consist of 3 different `s_list` structs,
**	all chained together with their `next` pointer, and the last element would
**	have this `next` pointer set to NULL(0)
*/
typedef struct		s_list_
{
//	struct s_list_*	prev;		//!< The pointer to the previous item in the list (or NULL if this is the first item)
	struct s_list_*	next;		//!< The pointer to the next item in the list (or NULL if this is the last item)
	t_size			item_size;	//!< The size of the data contained within `item`
	void*			item;		//!< The contents of this linked-list element
}					s_list;
TYPEDEF_ALIAS(		s_list, LIST, STRUCT)



//! A literal of an `s_list` struct which has all fields set to zero
#define LIST_NULL	(s_list){ .next = NULL, .item_size = 0, .item = NULL }



#define foreach_s_list_init(		TYPE, VAR, LIST)	foreach_s_list_init_1(TYPE, VAR, LIST); foreach_s_list_init_2(TYPE, VAR, LIST);
#define foreach_s_list_init_1(		TYPE, VAR, LIST)	t_size VAR##_i = 0
#define foreach_s_list_init_2(		TYPE, VAR, LIST)	s_list* VAR##_lst = (LIST)
#define foreach_s_list_exit(		TYPE, VAR, LIST)	if (LIST)
#define foreach_s_list_loop_init(	TYPE, VAR, LIST)	TYPE VAR = (TYPE)((LIST)->item)
#define foreach_s_list_loop_exit(	TYPE, VAR, LIST)	VAR##_lst != NULL
#define foreach_s_list_loop_incr(	TYPE, VAR, LIST)	++VAR##_i, foreach_s_list_loop_incr_1(TYPE, VAR, LIST), foreach_s_list_loop_incr_2(TYPE, VAR, LIST)
#define foreach_s_list_loop_incr_1(	TYPE, VAR, LIST)	VAR##_lst = VAR##_lst->next
#define foreach_s_list_loop_incr_2(	TYPE, VAR, LIST)	VAR = (VAR##_lst ? (TYPE)(VAR##_lst->item) : NULL)



/* TODO function pointer types
**	typedef void	(*f_list_delete)	(void*, t_size)
**	typedef void	(*f_list_iterate)	(s_list *)
**	typedef s_list*	(*f_list_map)		(s_list *)
*/



/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

//! Allocates and returns a list element from the given `item` pointer and `item_size`
/*!
**	Allocates a new linked list element, and feeds it the given `item` pointer
**	and the given `item_size` (if `item` is NULL, item_size is set to 0).
**	The `prev` and `next` pointers are both set to NULL.
**
**	@param	item		A pointer to the data/value to store in this list
**	@param	item_size	The size (in bytes) of the data in question
**	@returns the linked-list element containing the given data
*/
_MALLOC()
s_list*					List_New(void* item, t_size item_size);
#define c_lstnew		List_New

//! Inserts the given element `elem` to the beginning of the list starting at `a_lst`
/*!
**	Inserts a new element `elem` into the list at the address `a_lst`,
**	chaining this new element with the next element of this list
**	(ie: this function will set the `next` pointer to `*a_lst`,
**	and '(*a_lst)->prev' will be set to `elem`).
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to prepend to `alst` - if NULL, this function does nothing
*/
void					List_Prepend(s_list* *a_lst, s_list* elem);
#define c_lstprepend	List_Prepend
#define c_lstadd		List_Prepend

//! Appends the given element `elem` to the end of the list starting at `a_lst`
/*!
**	Appends the given element `elem` to the end of the list starting at `*a_lst`.
**	If `*a_lst` is NULL, it'll append `elem` at index 0, creating a 1-elem list.
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to prepend to `alst` - if NULL, this function does nothing
*/
void					List_Append(s_list* *a_lst, s_list* elem);
#define c_lstappend		List_Append

//! Inserts the given element `elem` at the given `index` of the list starting at `a_lst`
/*!
**	Inserts the given element `elem` at the given `index` of the list `*a_lst`.
**	If `index` is too large, the `elem` is appended to the end of the list.
**	If `elem` is NULL, then nothing is done by this function.
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	elem	The list element to insert in `alst` - if NULL, this function does nothing
**	@param	index	
*/
void					List_Insert(s_list* *a_lst, s_list* elem, t_u32 index);
#define c_lstinsert		List_Insert

//! Returns a "shallow copy" of the given list `lst` (copies only pointers, not the underlying data)
/*!
**	@param	lst		The list to copy
**	@returns a newly allocated copy of the given linked list `lst`.
**	The underlying data is not copied, only the s_list* structs are malloc'ed.
*/
_MALLOC()
s_list*					List_Copy(s_list const* lst);
#define c_lstcpy		List_Copy

//! Returns a "deep copy" of the given list `lst` (copies s_list structs, and the data in `item`)
/*!
**	@param	lst		The list to duplicate
**	@returns a newly allocated copy of the given linked list `lst`.
**	The underlying data `item` for each element will be allocated and copied, according to `item_size`
*/
_MALLOC()
s_list*					List_Duplicate(s_list const* lst);
#define c_lstdup		List_Duplicate



/*
** ************************************************************************** *|
**                             Deletion Operations                            *|
** ************************************************************************** *|
*/

//! Deletes the given element pointed to by `a_lst` using the given `del()` function.
/*!
**	Deletes the given element pointed to by `a_lst` with the given `del()` function,
**	and then frees memory and sets `*a_lst` to the old value of '*a_lst->next'.
**	So, the linked list remains "chained together" after removing an element in the middle.
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	del		The function used to delete one list item
*/
void					List_Remove(s_list* *a_lst, void (*del)(void*, t_size));
#define c_lstdelone		List_Remove

//! Deletes all the elements in the list starting at `a_lst`, using the given `del()` function.
/*!
**	Deletes all the elements in the list starting at `*a_lst`,
**	calls `del` and frees memory for each, and lastly sets `*a_lst` as NULL.
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	del		The function used to delete one list item
*/
void					List_Delete(s_list* *a_lst, void (*del)(void*, t_size));
#define c_lstdel		List_Delete

//! Deletes the given element pointed to by `a_lst` using the given `del()` function.
/*!
**	Deletes the last element in the list starting at `*a_lst`, calling `del()`
**	and freeing that element, and setting the preceding `lst.next` as NULL.
**
**	@param	a_lst	The address ('&') of the beginning of the list (the address of the first item)
**	@param	del		The function used to delete one list item
*/
void					List_Pop(s_list* *a_lst, void (*del)(void*, t_size));
#define c_lstpop		List_Pop



/*
** ************************************************************************** *|
**                                 List Checks                                *|
** ************************************************************************** *|
*/

//! Returns the amount of elements in the given list `lst`
/*!
**	@param	lst		the list to look through
**	@returns the amount of elements in the given list `lst`,
**	by traversing it, looping through every `next` pointer.
*/
t_u32					List_Size(s_list const* lst);
#define c_lstsize		List_Size

//! Gets the element at position `index` in the list, and returns it
/*!
**	@param	lst		the list to look through
**	@param	index	the index in the list of the element to get
**	@returns the `index`th element in the given list `lst`.
**	Will return NULL if `index` is beyond the last element.
*/
s_list*					List_Get(s_list const* lst, t_u32 index);
#define c_lstget		List_Get

//! Returns the first encountered item in the given list `lst` matching the given `query`
/*!
**	@param	lst		the list to look through
**	@param	query	the `item` pointer to match against
**	@returns the first encountered element of the given linked list `lst`
**	for which (lst.item == query), matching only the pointers, not the data.
*/
s_list*					List_Find(s_list const* lst, void const* query);
#define c_lstfind		List_Find



/*
** ************************************************************************** *|
**                             Other List Operations                          *|
** ************************************************************************** *|
*/

//! Returns a "shallow copy" of a subsection of the given list `lst`, starting at `index` and taking `n` elements
/*!
**	Returns a newly allocated subsection of the given list `lst`,
**	starting at `index`, and copying `n` list elements (not their `item` data).
**	Will return NULL if `index` is too large or if `n` is 0.
**	If `index` is valid but the list is not large enough for `n`,
**	then the resulting list will have fewer than `n` elements.
*/
_MALLOC()
s_list*					List_Sub(s_list* lst, t_u32 index, t_u32 n);
#define c_lstsub		List_Sub

//! Iterates upon each element of the given list `lst`, applying the given function `f` to each of its elements.
/*!
**	Iterates upon each element of the given list `lst`,
**	applying the given function `f` to each of its elements.
*/
void					List_Iterate(s_list* lst, void (*f)(s_list* elem));
#define c_lstiter		List_Iterate
void					List_Iterate_I(s_list* lst, void (*f)(s_list* elem, t_u32 index));
#define c_lstiteri		List_Iterate_I

//! Creates a new list which is the result of applying the given function `f` to each element of `lst`.
/*!
**	Creates a new list which is the result of applying
**	the given function `f` to each element of `lst`.
*/
_MALLOC()
s_list*					List_Map(s_list* lst, s_list *(*f)(s_list* elem));
#define c_lstmap		List_Map

_MALLOC()
s_list*					List_Map_I(s_list* lst, s_list *(*f)(s_list* elem, t_u32 index));
#define c_lstmapi		List_Map_I

//! Converts the given list at address `a_lst` to a NULL-terminated pointer array
/*!
**	Creates a new jagged array (2D pointer array) from the given list `*a_lst`.
**	The top-level pointer array is terminated by a NULL pointer.
**	The underlying `lst.item` data is not copied, only the pointers are.
*/
_MALLOC()
void**					List_To_PointerArray(s_list const** a_lst);
#define c_lst_to_ptrarr	List_To_PointerArray

//! Converts the given list at address `a_lst` to a array
/*!
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the `items` pointer of the given `array`.
**	It also sets the `item_size` and `length` fields of this `array`.
**
**	@returns the resulting `s_array` struct from the given list, or NULL
**		if any elements of `*a_lst` are of unequal `lst.item_size`.
*/
s_array					List_To_Array(s_list const** a_lst);
#define c_lst_to_array	List_To_Array



/*! @} */
HEADER_END
#endif
