/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/memory.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MEMORY_H
#define __LIBCCC_MEMORY_H
/*! @file libccc/memory.h
**	This header defines the common standard memory manipulation functions.
**	@addtogroup libccc/memory
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                          Basic Memory Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Allocates 'size' bytes in memory, returning the pointer at which
**	said bytes were allocated, or NULL if the memory could not be allocated.
*/
_MALLOC()
void*				Memory_Alloc(t_size size);
#define c_memalloc	Memory_Alloc

/*!
**	Allocates 'size' bytes in memory, setting each byte of this newly allocated
**	memory space to '0'. Returns the pointer at which said bytes were allocated,
**	or NULL if the memory could not be allocated.
*/
_MALLOC()
void*				Memory_New(t_size size);
#define c_memnew	Memory_New

/*!
**	Allocates 'size' bytes in memory, setting each byte of this newly allocated
**	memory space to 'c'. Returns the pointer at which said bytes were allocated,
**	or NULL if the memory could not be allocated.
*/
_MALLOC()
void*				Memory_New_C(t_size size, char c);
#define c_memcnew	Memory_New_C

/*!
**	Frees the allocated memory at '*ptr'.
*/
void				Memory_Free(void* ptr);
#define c_memfree	Memory_Free

/*!
**	Frees the allocated memory at '**a_ptr', and sets '*a_ptr' to NULL.
*/
void				Memory_Delete(void* *a_ptr);
#define c_memdel	Memory_Delete



/*!
**	Sets 'n' bytes of memory with the given 8-bit value 'byte' (taking only the
**	first 8 bits of this value and writing it byte-per-byte), starting at 'ptr'.
*/
void				Memory_Set(void* ptr, t_u8 byte, t_size n);
#define c_memset	Memory_Set

/*!
**	Sets 'n' bytes of memory to 0, starting at 'ptr'. (same as bzero)
*/
void				Memory_Clear(void* ptr, t_size n);
#define c_memclr	Memory_Clear

/*!
**	Copies 'n' bytes of memory from 'src' to 'dest', and returns 'dest'.
*/
void*				Memory_Copy(void* dest, void const* src, t_size n);
#define c_memcpy	Memory_Copy

/*!
**	Copies at most 'n' bytes of memory from 'src' to 'dest',
**	stopping after the first occurence of a byte equal to 'byte',
**	and returns a pointer to ('byte' + 1) in 'dest', or NULL.
*/
void*				Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n);
#define c_memccpy	Memory_Copy_C

/*!
**	Reads 'n' bytes of memory from 'src', and then writes
**	all of those bytes to 'dest' after having read everything.
**	This function is useful if the 'src' and 'dest' buffers overlap.
*/
void*				Memory_Move(void* dest, void const* src, t_size n);
#define c_memmove	Memory_Move



/*!
**	Returns a newly allocated memory area which is a copy of
**	the given memory area 'ptr' (or NULL if the required memory
**	could not be allocated, or if 'ptr' is NULL or 'n' == 0).
*/
_MALLOC()
void*				Memory_Duplicate(void const* ptr, t_size n);
#define c_memdup	Memory_Duplicate



/*
** ************************************************************************** *|
**                          Other Memory Operations                           *|
** ************************************************************************** *|
*/

/*!
**	Returns a pointer to the first occurrence of a byte equal to 'byte'
**	(or NULL if no byte was a match), starting the search at 'ptr'
**	and searching 'n' bytes of memory.
*/
void*				Memory_Find(void const* ptr, t_u8 byte, t_size n);
#define c_memchr	Memory_Find

/*!
**	Iterates through 'n' bytes of memory starting at 'ptr', replacing every
**	byte equal to 'old' with the value 'new' instead.
*/
void				Memory_Replace(void* ptr, t_u8 old, t_u8 new, t_size n);
#define c_memrep	Memory_Replace

/*!
**	Compares 'n' bytes of memory at 'ptr1' and 'ptr2',
**	returning (byte1 - byte2) at the first difference encountered.
**	As such, will return 0 if the contents of 'ptr1' and 'ptr2' match.
*/
int					Memory_Compare(void const* ptr1, void const* ptr2, t_size n);
#define c_memcmp	Memory_Compare

/*!
**	Swaps the memory content pointed to by 'ptr1' and 'ptr2',
**	copying exactly 'size' bytes of data between the two. (XOR swap method)
**	Returns 0 if the swap was successful, and 1 otherwise.
*/
int					Memory_Swap(void* ptr1, void* ptr2, t_size size);
#define c_memswap	Memory_Swap

/*!
**	Returns a subsection of the 'value' argument, taking 'length' bits
**	from 'value' at the given bit index 'bit', and bitshifting the resulting
**	bits to the right by 'bit' bits (so as to center the value back to 0).
*/
t_u64				Memory_GetBits(t_u64 value, t_u8 bit, t_u8 length);
#define c_getbits	Memory_GetBits



/*! @} */
HEADER_END
#endif