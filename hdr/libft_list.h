/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_LIST_H
#define __LIBFT_LIST_H
/*! @file libft_list.h
**	This header defines a simple linked list type and utility functions for it.
**	@addtogroup libft_list
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This struct holds an array of items which can be of any type
/*!
**	The 's_tuple' struct holds a `void*` pointer to the array of items, the size
**	of a single item in the array, and the total amount of items in this array.
*/
typedef struct		s_tuple_
{
	void*			items;		//!< The pointer to the any-type array
	t_size			item_size;	//!< The size (in bytes) of one object in this array
	t_size			length;		//!< The amount of elements in the 'items' array
}					s_tuple;

//! This is a very simple linked-list struct, storing only the 'next' pointer
/*!
**	The 's_list' struct represents one chainlink in the linked-list, so a
**	linked-list with 3 elements would consist of 3 different 's_list' structs,
**	all chained together with their 'next' pointer, and the last element would
**	have this 'next' pointer set to NULL(0)
*/
typedef struct		s_list_
{
	void*			item;		//!< The contents of this linked-list element
	t_size			item_size;	//!< The size of the data contained within 'item'
	struct s_list_*	next;		//!< The pointer to the next item in the list (or NULL if this is the last item)
}					s_list;

/* TODO function pointers
**	typedef void	(*f_list_delete)	(void *, t_size)
**	typedef void	(*f_list_iterate)	(s_list *)
**	typedef s_list*	(*f_list_map)		(s_list *)
*/



/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

/*!
**	Allocates a new linked list element, and feeds it the given 'item' pointer
**	and the given 'item_size' (if 'item' is NULL, item_size is set to 0).
**
**	@param	item		A pointer to the data/value to store in this list
**	@param	item_size	The size (in bytes) of the data in question
**	@return the linked-list element containing the given data
*/
s_list*					List_New(void *item, t_size item_size);
#define ft_lstnew		List_New

/*!
**	Inserts a new element of a list 'elem' at the pointer '*alst',
**	chaining this new element with the next element of this list.
*/
void					List_Add(s_list **alst, s_list *elem);
#define ft_lstadd		List_Add

/*!
**	Appends the element 'elem' to the end of the list starting at '*alst'.
**	If '*alst' is NULL, it'll append 'elem' at index 0, creating a 1-elem list.
*/
void					List_Append(s_list **alst, s_list *elem);
#define ft_lstappend	List_Append

/*!
**	Inserts the given element 'elem' at the given 'index' of the list '*alst'.
**	If 'index' is too large, the 'elem' is appended to the end of the list.
**	If 'elem' is NULL, then nothing is done by this function.
*/
void					List_Insert(s_list **alst, s_list *elem, t_u32 index);
#define ft_lstinsert	List_Insert

/*!
**	Returns a newly allocated copy of the given linked list 'lst'.
**	The underlying data is not copied, only the s_list* structs are malloc'ed.
*/
s_list*					List_Copy(s_list *lst);
#define ft_lstcpy		List_Copy

/*!
**	Deletes the given element pointed to by 'alst' with the function 'del',
**	and then frees memory and sets '*alst' as a NULL pointer.
*/
void					List_Remove(s_list **alst, void (*del)(void *, t_size));
#define ft_lstdelone	List_Remove

/*!
**	Deletes all the elements in the list starting at '*alst',
**	calls 'del' and frees memory for each, and lastly sets '*alst' as NULL.
*/
void					List_Delete(s_list **alst, void (*del)(void *, t_size));
#define ft_lstdel		List_Delete

/*!
**	Deletes the last element in the list starting at '*alst', calling 'del'
**	and freeing that element, and setting the preceding 'lst->next' as NULL.
*/
void					List_Pop(s_list **alst, void (*del)(void *, t_size));
#define ft_lstpop		List_Pop



/*
** ************************************************************************** *|
**                                 List Checks                                *|
** ************************************************************************** *|
*/

/*!
**	Returns the amount of elements in the given list 'lst'.
*/
t_u32					List_Size(s_list *lst);
#define ft_lstsize		List_Size

/*!
**	Returns the 'index'th element in the given list 'lst'.
**	Will return NULL if 'index' is beyond the last element.
*/
s_list*					List_Get(s_list *lst, t_u32 index);
#define ft_lstget		List_Get

/*!
**	Returns the first encountered element of the given linked list 'lst'
**	for which (lst.item == query), matching only the pointers, not the data.
*/
s_list*					List_Find(s_list *lst, void const *query);
#define ft_lstfind		List_Find



/*
** ************************************************************************** *|
**                             Other List Operations                          *|
** ************************************************************************** *|
*/

/*!
**	Returns a newly allocated subsection of the given list 'lst',
**	starting at 'index', and copying 'n' list elements (not their 'item' data).
**	Will return NULL if 'index' is too large or if 'n' is 0.
**	If 'index' is valid but the list is not large enough for 'n',
**	then the resulting list will have fewer than 'n' elements.
*/
s_list*					List_Sub(s_list *lst, t_u32 index, t_u32 n);
#define ft_lstsub		List_Sub

/*!
**	Iterates upon each element of the given list 'lst',
**	applying the given function 'f' to each of its elements.
*/
void					List_Iterate(s_list *lst, void (*f)(s_list *elem));
#define ft_lstiter		List_Iterate
void					List_Iterate_I(s_list *lst, void (*f)(s_list *elem, t_u32 index));
#define ft_lstiteri		List_Iterate_I

/*!
**	Creates a new list which is the result of applying
**	the given function 'f' to each element of 'lst'.
*/
s_list*					List_Map(s_list *lst, s_list *(*f)(s_list *elem));
#define ft_lstmap		List_Map
s_list*					List_Map_I(s_list *lst, s_list *(*f)(s_list *elem, t_u32 index));
#define ft_lstmapi		List_Map_I

/*!
**	Creates a new jagged array (2D pointer array) from the given list '*alst'.
**	The top-level pointer array is terminated by a NULL pointer.
**	The underlying 'lst->item' data is not copied, only the pointers are.
*/
void**						List_ToArray(s_list **alst);
#define ft_lst_to_array		List_ToArray

/*!
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the 'items' pointer of the given 'tuple'.
**	It also sets the 'item_size' and 'length' fields of this 'tuple'.
**	Returns NULL if any elements of '*alst' are of unequal 'lst->item_size'.
*/
s_tuple*					List_ToTuple(s_list **alst, s_tuple *tuple);
#define ft_lst_to_tuple		List_ToTuple



/*! @} */
HEADER_END
#endif
