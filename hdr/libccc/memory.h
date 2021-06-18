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
/*!@group{libccc_memory}
** @{
**	This header defines the common standard memory manipulation functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/memory}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! macros for byte sizes
#define KB(X)	((X) * 1024)	//!< converts a value expressed in kilobytes to its equivalent in bytes
#define MB(X)	(KB(X) * 1024)	//!< converts a value expressed in megabytes to its equivalent in bytes
#define GB(X)	(MB(X) * 1024)	//!< converts a value expressed in gigabytes to its equivalent in bytes
#define TB(X)	(GB(X) * 1024)	//!< converts a value expressed in terabytes to its equivalent in bytes



//! Macros to convert values' endianness (invert byte-per-byte)
//!@{
#define ENDIAN_INVERT_16(X) \
	( (((X)&0XFF)<<8) \
	| (((X)>>8)&0XFF) )
#define ENDIAN_INVERT_32(X) \
	( (((X)&0XFF)<<24) | (((X)&0XFF00)<<8) \
	| (((X)>>24)&0XFF) | (((X)>>8)&0XFF00) )
#define ENDIAN_INVERT_64(X) \
	( (((X)&0XFF)<<56) | (((X)&0XFF00)<<40) | (((X)&0XFF0000)<<24) | (((X)&0XFF000000)<<8) \
	| (((X)>>56)&0XFF) | (((X)>>40)&0XFF00) | (((X)>>24)&0XFF0000) | (((X)>>8)&0XFF000000) )
//!@}



/*
** ************************************************************************** *|
**                          Basic Memory Operations                           *|
** ************************************************************************** *|
*/

//! Returns a newly allocated memory area which is `size` bytes long, with every byte set to `0`.
/*!
**	@nonstd
**	This function is similar to:
**	@isostd{C89,https://en.cppreference.com/w/c/memory/calloc}
**
**	Allocates `size` bytes in memory, returning the pointer to allocated region.
**	Sets each byte of this newly allocated memory space to `0`.
**
**	@returns
**	The pointer to newly allocated region, or `NULL` if an error occurred
**	(ie: the memory could not be allocated for whatever reason).
*/
_MALLOC()
void*				Memory_New(t_size size);
#define c_memnew	Memory_New //!< @alias{Memory_New}

//! Returns a newly allocated memory area which is `size` bytes long, with every byte set to `c`.
/*!
**	@nonstd
**
**	Allocates `size` bytes in memory, setting each byte of this newly allocated
**	memory space to `c`. Returns the pointer at which said bytes were allocated,
**	or `NULL` if the memory could not be allocated.
**
**	@returns
**	The pointer to newly allocated region, or `NULL` if an error occurred
**	(ie: the memory could not be allocated for whatever reason).
*/
_MALLOC()
void*				Memory_New_C(t_size size, char c);
#define c_memcnew	Memory_New_C //!< @alias{Memory_New_C}

//! Returns a pointer to a newly allocated memory area which is `size` bytes long, uninitialized.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/memory/malloc}
**
**	Allocates `size` bytes in memory, returning the pointer to allocated region.
**	NB: This function only allocates a new memory region and does nothign more:
**		This means that there may be garbage leftover values in the newly allocated region.
**		It generally recommended to use Memory_New() instead, to avoid garbage memory issues.
**
**	@returns
**	The pointer to newly allocated region, or `NULL` if an error occurred
**	(ie: the memory could not be allocated for whatever reason).
*/
_MALLOC()
void*					Memory_Allocate(t_size size);
#define c_malloc		Memory_Allocate //!< @alias{Memory_Allocate}
#define c_memalloc		Memory_Allocate //!< @alias{Memory_Allocate}
#define Memory_Alloc	Memory_Allocate //!< @alias{Memory_Allocate}

//! Reallocates the given area of memory `ptr` to be `size` bytes long, returning the new (or same) pointer.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/memory/realloc}
**
**	This function will either reallocate in-place (ie: not changing the pointer),
**	or, if that is not possible, it will allocate the needed `size` to a new region.
**
**	@returns
**	The pointer to newly allocated region, or `NULL` if an error occurred
**	(ie: the memory could not be allocated for whatever reason).
**	NOTE: If the requested region is not too different in size, then
**	the return value may be the exact same pointer as the given `ptr` argument.
*/
_MALLOC()
void*					Memory_Reallocate(void* ptr, t_size size);
#define c_realloc		Memory_Reallocate //!< @alias{Memory_Reallocate}
#define c_memrealloc	Memory_Reallocate //!< @alias{Memory_Reallocate}
#define Memory_Realloc	Memory_Reallocate //!< @alias{Memory_Reallocate}



//! Frees the previously allocated memory area at `*ptr`.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/memory/free}
**
**	Deallocates the area of memory pointed to by `ptr`, assuming it was
**	previously allocated by a call to Memory_Alloc() or Memory_New()
*/
void					Memory_Deallocate(void* ptr);
#define c_dealloc		Memory_Deallocate //!< @alias{Memory_Deallocate}
#define c_memdealloc	Memory_Deallocate //!< @alias{Memory_Deallocate}
#define Memory_Dealloc	Memory_Deallocate //!< @alias{Memory_Deallocate}
#define c_free			Memory_Deallocate //!< @alias{Memory_Deallocate}
#define c_memfree		Memory_Deallocate //!< @alias{Memory_Deallocate}
#define Memory_Free		Memory_Deallocate //!< @alias{Memory_Deallocate}

//! Frees the allocated memory at `**a_ptr`, and sets `*a_ptr` to `NULL`.
/*!
**	@nonstd
**
**	Frees the allocated memory at `**a_ptr`, and sets `*a_ptr` to `NULL`.
**
**	@param	a_ptr	The address of the pointer to free and `NULL`ify
*/
void				Memory_Delete(void* *a_ptr);
#define c_memdel	Memory_Delete //!< @alias{Memory_Delete}



//! Sets `n` bytes of memory, starting at `ptr`, to the given value `byte`.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/memset}
**
**	Sets `n` bytes of memory with the given 8-bit value `byte` (taking only the
**	first 8 bits of this value and writing it byte-per-byte), starting at `ptr`.
*/
void				Memory_Set(void* ptr, t_u8 byte, t_size n);
#define c_memset	Memory_Set //!< @alias{Memory_Set}

//! Sets `n` bytes of memory to 0, starting at `ptr`.
/*!
**	@isostd{BSD,https://linux.die.net/man/3/bzero}
**
**	Sets `n` bytes of memory to 0, starting at `ptr`. (equivalent to bzero)
*/
void				Memory_Clear(void* ptr, t_size n);
#define c_bzero		Memory_Clear //!< @alias{Memory_Clear}
#define c_memclr	Memory_Clear //!< @alias{Memory_Clear}



//! Copies `n` bytes of data from `src` into `dest`, and returns `dest`.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/memcpy}
**
**	Copies `n` bytes of memory from `src` to `dest`, and returns `dest`.
*/
void*				Memory_Copy(void* dest, void const* src, t_size n);
#define c_memcpy	Memory_Copy //!< @alias{Memory_Copy}

//! Copies `n` bytes of data from `src` into `dest`, and returns `dest` (stops upon encountering `byte`).
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/string/byte/memccpy}
**
**	Copies at most `n` bytes of memory from `src` to `dest`,
**	stopping after the first occurence of a byte equal to `byte`,
**	and returns a pointer to (`byte` + 1) in `dest`, or `NULL`.
*/
void*				Memory_Copy_C(void* dest, void const* src, t_u8 byte, t_size n);
#define c_memccpy	Memory_Copy_C //!< @alias{Memory_Copy_C}

//! Moves `n` bytes of data from `src` into `dest`, and returns `dest`.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/memmove}
**
**	Reads `n` bytes of memory from `src`, and then writes
**	all of those bytes to `dest` after having read everything.
**	This function is useful if the `src` and `dest` buffers overlap.
*/
void*				Memory_Move(void* dest, void const* src, t_size n);
#define c_memmove	Memory_Move //!< @alias{Memory_Move}



//! Allocates a memory region which is `n` bytes long and has the same content as `ptr`.
/*!
**	@nonstd
**
**	Returns a newly allocated memory area which is a copy of
**	the given memory area `ptr` (or `NULL` if the required memory
**	could not be allocated, or if `ptr == `NULL`` or `n == 0`).
*/
_MALLOC()
void*				Memory_Duplicate(void const* ptr, t_size n);
#define c_memdup	Memory_Duplicate //!< @alias{Memory_Duplicate}



/*
** ************************************************************************** *|
**                       Memory Concatenation Operations                      *|
** ************************************************************************** *|
*/

//! Return a newly allocated memory region, by concatenating `ptr1` and `ptr2`
/*!
**	@nonstd
*/
void*					Memory_Join(void const* ptr1, t_size length1, void const* ptr2, t_size length2);
#define c_memjoin		Memory_Join //!< @alias{Memory_Join}

//! Return a newly allocated memory region, by concatenating `*a_dest` (deletes old) and `src`
/*!
**	@nonstd
*/
void*					Memory_Append(void* *a_dest, t_size dest_length, void const* src, t_size src_length);
#define c_memappend		Memory_Append //!< @alias{Memory_Append}

//! Return a newly allocated memory region, by concatenating `src` and `*a_dest` (deletes old)
/*!
**	@nonstd
*/
void*					Memory_Prepend(void const* src, t_size src_length, void* *a_dest, t_size dest_length);
#define c_memprepend	Memory_Prepend //!< @alias{Memory_Prepend}

//! Return a newly allocated memory region, by concatenating `*a_ptr1` (deletes old) and `*a_ptr2` (deletes old)
/*!
**	@nonstd
*/
void*					Memory_Merge(void* *a_ptr1, t_size length1, void* *a_ptr2, t_size length2);
#define c_memmerge		Memory_Merge //!< @alias{Memory_Merge}



/*
** ************************************************************************** *|
**                          Other Memory Operations                           *|
** ************************************************************************** *|
*/

//! Finds the first occurence of the given `byte` value in the first `n` bytes at `ptr`.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/memchr}
**
**	Returns a pointer to the first occurrence of a byte which is equal to
**	the given `byte` value, or `NULL` if no matching byte was encountered.
**	Begins the search at `ptr`, and reads through `n` bytes of memory.
*/
void*				Memory_Find(void const* ptr, t_u8 byte, t_size n);
#define c_memchr	Memory_Find //!< @alias{Memory_Find}
#define c_memfind	Memory_Find //!< @alias{Memory_Find}



//! Replaces every `old` byte with `new`, in the `n` byte long memory region starting at `ptr`.
/*!
**	@nonstd
**
**	Iterates through `n` bytes of memory starting at `ptr`, replacing every
**	byte equal to `old` with the value `new` instead.
*/
void				Memory_Replace(void* ptr, t_u8 old, t_u8 new, t_size n);
#define c_memrep	Memory_Replace //!< @alias{Memory_Replace}



//! Compares `n` bytes of memory in `ptr1` and `ptr2`: returns the first difference of chars encountered, or zero, if the bytes all match.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/memcmp}
**
**	Compares `n` bytes of memory between `ptr1` and `ptr2`.
**
**	@returns
**	The first difference between bytes encountered: `(ptr1[i] - ptr2[i])`,
**	or `0` if the contents of `ptr1` and `ptr2` match.
*/
t_sint				Memory_Compare(void const* ptr1, void const* ptr2, t_size n);
#define c_memcmp	Memory_Compare //!< @alias{Memory_Compare}



//! Swaps `size` bytes of memory between `ptr1` and `ptr2`
/*!
**	@nonstd
**
**	Swaps the memory content pointed to by `ptr1` and `ptr2`,
**	copying exactly `size` bytes of data between the two. (XOR swap method)
**
**	@returns
**	`FALSE` if the swap was successful,
**	or `TRUE` otherwise.
*/
t_bool				Memory_Swap(void* ptr1, void* ptr2, t_size size); // TODO change retrun type to t_error
#define c_memswap	Memory_Swap //!< @alias{Memory_Swap}



/*
** ************************************************************************** *|
**                          Bitwise Memory Operations                         *|
** ************************************************************************** *|
*/

//! Get a subsection of `n` bits from the data in `ptr`, starting at bit index `bit`.
/*!
**	@nonstd
**
**	@param	ptr		The point which stores the data
**	@param	bit		The offset at which to get (in bits)
**	@param	n		The amount of bits to copy into the return value (max: 128)
**	@returns
**	A subsection of the data in `ptr` argument which is `n` bits long,
**	starting at the given bit index `bit`, and bit-shifting the resulting
**	bits to the right by `bit` bits (so as to center the value back to zero).
**	TODO document how this function handles endian-ness ?
*/
t_uintmax			Memory_GetBits(void* ptr, t_size bit, t_u8 n);
#define c_getbits	Memory_GetBits //!< @alias{Memory_GetBits}

//! Set a subsection of `n` bits from the data in `ptr`, starting at bit index `bit`.
/*!
**	@nonstd
**
**	@param	ptr		The point which stores the data
**	@param	bit		The offset at which to get (in bits)
**	@param	n		The amount of bits to copy into the return value (max: 128)
**	@param	value	The bits to write to `ptr + bit`
**	@returns
**	A subsection of the data in `ptr` argument which is `n` bits long,
**	starting at the given bit index `bit`, and bit-shifting the resulting
**	bits to the right by `bit` bits (so as to center the value back to zero).
**	TODO document how this function handles endian-ness ?
*/
void				Memory_SetBits(void* ptr, t_size bit, t_u8 n, t_uintmax value);
#define c_setbits	Memory_SetBits //!< @alias{Memory_SetBits}



//! Get a subsection of `n` bits from `value`, starting at bit index `bit`.
/*!
**	@nonstd
**
**	@returns
**	A subsection of the `value` argument which is `n` bits long,
**	starting at the given bit index `bit`, and bit-shifting the resulting
**	bits to the right by `bit` bits (so as to center the value back to zero).
*/
t_uintmax			Memory_BitRegion(t_uintmax value, t_u8 bit, t_u8 n);
#define c_bitregion	Memory_BitRegion //!< @alias{Memory_BitRegion}



//! Get the total amount of bits set to `1` in the given `value`.
/*!
**	@nonstd
**
**	@returns
**	The total amount of bits set to `1` in the given `value`.
*/
t_u8				Memory_CountBits(t_uintmax value);
#define c_countbits	Memory_CountBits //!< @alias{Memory_CountBits}



//! Get the bit index of the most signficant `1`-bit of the given `value`
/*!
**	@nonstd, similar to the builtin `clz()` function
**
**	@returns
**	The bit index of the highest bit which is set to 1 in the given `value`.
**	If `value == 0` (all bits set to zero), returns `-1`
*/
t_s8					Memory_GetMostSignificantBit(t_uintmax value);
#define c_getmsb		Memory_GetMostSignificantBit //!< @alias{Memory_GetMostSignificantBit}
#define Memory_GetMSB	Memory_GetMostSignificantBit //!< @alias{Memory_GetMostSignificantBit}

//! Get the bit index of the least signficant `1`-bit of the given `value`
/*!
**	@nonstd, similar to the builtin `clz()` function
**
**	@returns
**	The bit index of the lowest bit which is set to 1 in the given `value`.
**	If `value == 0` (all bits set to zero), returns `-1`
*/
t_s8					Memory_GetLeastSignificantBit(t_uintmax value);
#define c_getlsb		Memory_GetLeastSignificantBit //!< @alias{Memory_GetLeastSignificantBit}
#define Memory_GetLSB	Memory_GetLeastSignificantBit //!< @alias{Memory_GetLeastSignificantBit}



/*
** ************************************************************************** *|
**                    Essential builtins (for compatibility)                  *|
** ************************************************************************** *|
*/

#ifdef __IOS__ // TODO smarter check here

inline
void*	memset(void* ptr, int c, size_t n)
{ Memory_Set(ptr, c, n); return (ptr); }

inline
int		memcmp(void const* ptr1, void const* ptr2, size_t n)
{ return (Memory_Compare(ptr1, ptr2, n)); }

inline
void*	memchr(void const* ptr, int c, size_t n)
{ return (Memory_Find(ptr, c, n)); }

inline
void*	memcpy(void* dest, void const* src, size_t n)
{ return (Memory_Copy(dest, src, n)); }

inline
void*	memccpy(void* dest, void const* src, int c, size_t n)
{ return (Memory_Copy_C(dest, src, c, n)); }

inline
void*	memmove(void* dest, void const* src, t_size n)
{ return (Memory_Move(dest, src, n)); }

#endif



/*! @} */
HEADER_END
#endif
