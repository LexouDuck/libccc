/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memory.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEMORY_H
#define LIBFT_MEMORY_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Memory_Alloc		ft_memalloc
#define Memory_New			ft_memnew

#define Memory_Free			ft_memfree
#define Memory_Delete		ft_memdel

#define Memory_Set			ft_memset
#define Memory_Clear		ft_memclr
#define Memory_Copy			ft_memcpy
#define Memory_Copy_C		ft_memccpy
#define Memory_Move			ft_memmove

#define Memory_Duplicate	ft_memdup

#define Memory_Find			ft_memchr
#define Memory_Compare		ft_memcmp
#define Memory_Swap			ft_memswap

#define Memory_GetBits		ft_getbits

#define PointerArray_New	ft_ptrarrnew
#define PointerArray_Length	ft_ptrarrlen



/*
** ************************************************************************** *|
**                          Basic Memory Operations                           *|
** ************************************************************************** *|
*/

/*
**	Allocates 'size' bytes in memory, returning the pointer at which
**	said bytes were allocated, or NULL if the memory could not be allocated.
*/
void	*ft_memalloc(t_size size);

/*
**	Allocates 'size' bytes in memory, setting each byte of this newly allocated
**	memory space to '0'. Returns the pointer at which said bytes were allocated,
**	or NULL if the memory could not be allocated.
*/
void	*ft_memnew(t_size size);



/*
**	Frees the allocated memory at '*ptr'.
*/
void	ft_memfree(void *ptr);

/*
**	Frees the allocated memory at '**ptr', and sets '*ptr' to NULL.
*/
void	ft_memdel(void **ptr);



/*
**	Sets 'n' bytes of memory with the given 8-bit value 'byte' (taking only the
**	first 8 bits of this value and writing it byte-per-byte), starting at 'ptr'.
*/
void	ft_memset(void *ptr, t_u8 byte, t_size n);

/*
**	Sets 'n' bytes of memory to 0, starting at 'ptr'. (same as bzero)
*/
void	ft_memclr(void *ptr, t_size n);

/*
**	Copies 'n' bytes of memory from 'src' to 'dest', and returns 'dest'.
*/
void	*ft_memcpy(void *dest, void const *src, t_size n);

/*
**	Copies at most 'n' bytes of memory from 'src' to 'dest',
**	stopping after the first occurence of a byte equal to 'byte',
**	and returns a pointer to ('byte' + 1) in 'dest', or NULL.
*/
void	*ft_memccpy(void *dest, void const *src, t_u8 byte, t_size n);

/*
**	Reads 'n' bytes of memory from 'src', and then writes
**	all of those bytes to 'dest' after having read everything.
**	This function is useful if the 'src' and 'dest' buffers overlap.
*/
void	*ft_memmove(void *dest, void const *src, t_size n);



/*
**	Returns a newly allocated memory area which is a copy of
**	the given memory area 'ptr' (or NULL if the required memory
**	could not be allocated, or if 'ptr' is NULL or 'n' == 0).
*/
void	*ft_memdup(void const *ptr, t_size n);



/*
** ************************************************************************** *|
**                          Other Memory Operations                           *|
** ************************************************************************** *|
*/

/*
**	Returns a pointer to the first occurrence of a byte equal to 'byte'
**	(or NULL if no byte was a match), starting the search at 'ptr'
**	and searching 'n' bytes of memory.
*/
void	*ft_memchr(void const *ptr, t_u8 byte, t_size n);

/*
**	Iterates through 'n' bytes of memory starting at 'ptr', replacing every
**	byte equal to 'old' with the value 'new' instead.
*/
void	ft_memrep(void *ptr, t_u8 old, t_u8 new, t_size n);

/*
**	Compares 'n' bytes of memory at 'ptr1' and 'ptr2',
**	returning (byte1 - byte2) at the first difference encountered.
**	As such, will return 0 if the contents of 'ptr1' and 'ptr2' match.
*/
int		ft_memcmp(void const *ptr1, void const *ptr2, t_size n);

/*
**	Swaps the memory content pointed to by 'ptr1' and 'ptr2',
**	copying exactly 'size' bytes of data between the two. (XOR swap method)
**	Returns 0 if the swap was successful, and 1 otherwise.
*/
int		ft_memswap(void *ptr1, void *ptr2, t_size size);

/*
**	Returns a subsection of the 'value' argument, taking 'length' bits
**	from 'value' at the given bit index 'bit', and bitshifting the resulting
**	bits to the right by 'bit' bits (so as to center the value back to 0).
*/
t_u64	ft_getbits(t_u64 value, t_u8 bit, t_u8 length);



/*
** ************************************************************************** *|
**                          Pointer Array Operations                          *|
** ************************************************************************** *|
*/

/*
** Returns a newly allocated memory array to serve as a length n,
** null-terminated, pointer array. Returns NULL if malloc fails.
*/
void	*ft_ptrarrnew(t_size size);

/*
** Returns the length of a null-terminated pointer array.
*/
t_u32	ft_ptrarrlen(const void **a_ptrarr);

#endif
