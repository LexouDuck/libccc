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

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

#define FT_ListNew(item, size)				ft_lstnew(item, size)
#define FT_ListAdd(alst, elem)				ft_lstadd(alst, elem)
#define FT_ListAppend(alst, elem)			ft_lstappend(alst, elem)
#define FT_ListInsert(alst, elem, index)	ft_lstinsert(alst, elem, index)
#define FT_ListCopy(lst)					ft_lstcpy(lst)
#define FT_ListRemove(alst, del)			ft_lstdelone(alst, del)
#define FT_ListDelete(alst, del)			ft_lstdel(alst, del)
#define FT_ListPop(alst, del)				ft_lstpop(alst, del)

#define FT_ListSize(lst)					ft_lstsize(lst)
#define FT_ListGet(alst, index)				ft_lstget(alst, index)
#define FT_ListFind(lst, query)				ft_lstfind(lst, query)

#define FT_ListSub(alst, index, n)			ft_lstsub(alst, index, n)
#define FT_ListIterate(lst, f)				ft_lstiter(lst, f)
#define FT_ListIterate_I(lst, f)			ft_lstiteri(lst, f)
#define FT_ListMap(lst, f)					ft_lstmap(lst, f)
#define FT_ListMap_I(lst, f)				ft_lstmapi(lst, f)
#define FT_ListToArray(alst)				ft_lst_to_array(alst)
#define FT_ListToTuple(alst, tuple)			ft_lst_to_tuple(alst, tuple)

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef struct		s_tuple
{
	void			*items;
	size_t			item_size;
	size_t			length;
}					t_tuple;

typedef struct		s_list
{
	void			*item;
	size_t			item_size;
	struct s_list	*next;
}					t_list;

/*
**	typedef void	(*f_list_delete)(void *, size_t);
**	typedef void	(*f_list_iterate)(t_list *);
**	typedef t_list*	(*f_list_map)(t_list *);
*/

/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

/*
**	Allocates a new linked list element, and feeds it the given 'item' pointer
**	and the given 'item_size' (if 'item' is NULL, item_size is set to 0).
*/
t_list				*ft_lstnew(void *item, size_t item_size);

/*
**	Inserts a new element of a list 'elem' at the pointer '*alst',
**	chaining this new element with the next element of this list.
*/
void				ft_lstadd(t_list **alst, t_list *elem);

/*
**	Appends the element 'elem' to the end of the list starting at '*alst'.
**	If '*alst' is NULL, it'll append 'elem' at index 0, creating a 1-elem list.
*/
void				ft_lstappend(t_list **alst, t_list *elem);

/*
**	Inserts the given element 'elem' at the given 'index' of the list '*alst'.
**	If 'index' is too large, the 'elem' is appended to the end of the list.
**	If 'elem' is NULL, then nothing is done by this function.
*/
void				ft_lstinsert(t_list **alst, t_list *elem, t_u32 index);

/*
**	Returns a newly allocated copy of the given linked list 'lst'.
**	The underlying data is not copied, only the t_list* structs are malloc'ed.
*/
t_list				*ft_lstcpy(t_list *lst);

/*
**	Deletes the given element pointed to by 'alst' with the function 'del',
**	and then frees memory and sets '*alst' as a NULL pointer.
*/
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

/*
**	Deletes all the elements in the list starting at '*alst',
**	calls 'del' and frees memory for each, and lastly sets '*alst' as NULL.
*/
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
**	Deletes the last element in the list starting at '*alst', calling 'del'
**	and freeing that element, and setting the preceding 'lst->next' as NULL.
*/
void				ft_lstpop(t_list **alst, void (*del)(void *, size_t));

/*
** ************************************************************************** *|
**                                 List Checks                                *|
** ************************************************************************** *|
*/

/*
**	Returns the amount of elements in the given list 'lst'.
*/
t_u32				ft_lstsize(t_list *lst);

/*
**	Returns the 'index'th element in the given list 'lst'.
**	Will return NULL if 'index' is beyond the last element.
*/
t_list				*ft_lstget(t_list *lst, t_u32 index);

/*
**	Returns the first encountered element of the given linked list 'lst'
**	for which (lst.item == query), matching only the pointers, not the data.
*/
t_list				*ft_lstfind(t_list *lst, void const *query);

/*
** ************************************************************************** *|
**                             Other List Operations                          *|
** ************************************************************************** *|
*/

/*
**	Returns a newly allocated subsection of the given list 'lst',
**	starting at 'index', and copying 'n' list elements (not their 'item' data).
**	Will return NULL if 'index' is too large or if 'n' is 0.
**	If 'index' is valid but the list is not large enough for 'n',
**	then the resulting list will have fewer than 'n' elements.
*/
t_list				*ft_lstsub(t_list *lst, t_u32 index, t_u32 n);

/*
**	Iterates upon each element of the given list 'lst',
**	applying the given function 'f' to each of its elements.
*/
void				ft_lstiter(t_list *lst,
					void (*f)(t_list *elem));
void				ft_lstiteri(t_list *lst,
					void (*f)(t_list *elem, t_u32 index));

/*
**	Creates a new list which is the result of applying
**	the given function 'f' to each element of 'lst'.
*/
t_list				*ft_lstmap(t_list *lst,
					t_list *(*f)(t_list *elem));
t_list				*ft_lstmapi(t_list *lst,
					t_list *(*f)(t_list *elem, t_u32 index));

/*
**	Creates a new jagged array (2D pointer array) from the given list '*alst'.
**	The top-level pointer array is terminated by a NULL pointer.
**	The underlying 'lst->item' data is not copied, only the pointers are.
*/
void				**ft_lst_to_array(t_list **alst);

/*
**	Creates a new contiguous memory array from the given linked list.
**	It sets this array pointer to the 'items' pointer of the given 'tuple'.
**	It also sets the 'item_size' and 'length' fields of this 'tuple'.
**	Returns NULL if any elements of '*alst' are of unequal 'lst->item_size'.
*/
t_tuple				*ft_lst_to_tuple(t_list **alst, t_tuple *tuple);

#endif
