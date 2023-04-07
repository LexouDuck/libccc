/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/hashmap.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_HASHMAP_H
#define __LIBCCC_MONAD_HASHMAP_H
/*!@group{libccc_monad_hashmap,32,libccc/monad/hashmap.h}
**
**	This header defines a generic hashmap type and utility functions for it.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/hashmap.c"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! The integer type used to store a hash key
typedef t_u32	t_hash;

//! A dynamic hashmap item struct, stores a single hash-value pair
/*
**	TODO document this
*/
struct hashitem(T)
{
	t_hash	hash;	//!< hash code used to index/identify this item
	T		value;	//!< value stored for this item
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct hashitem(T)	s_hashitem(T);
#endif

//! A dynamic hashmap struct, stores several hash-value pairs
/*
**	TODO document this
*/
struct hashmap(T)
{
	t_uint			length;	//!< The pointer to the next item in the hashmap (or NULL if this is the last item)
	s_hashitem(T)*	items;	//!< The fields (key-value pairs) contained within this hashmap
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct hashmap(T)	s_hashmap(T);
#endif



#define foreach_s_hashmap_init(     _TYPE_, _VAR_, _HASHMAP_)	
#define foreach_s_hashmap_exit(     _TYPE_, _VAR_, _HASHMAP_)	
#define foreach_s_hashmap_loop_init(_TYPE_, _VAR_, _HASHMAP_)	
#define foreach_s_hashmap_loop_exit(_TYPE_, _VAR_, _HASHMAP_)	
#define foreach_s_hashmap_loop_incr(_TYPE_, _VAR_, _HASHMAP_)	



/*
** ************************************************************************** *|
**                          HashMap: basic operations                         *|
** ************************************************************************** *|
*/

//s_hashmap(T)*       HashMap_Item(T)          (T item);
//t_uint              HashMap_Length(T)        (s_hashmap(T) const* hashmap);
//T*                  HashMap_Get(T)           (s_hashmap(T) const* hashmap, t_uint index);
//T*                  HashMap_Set(T)           (s_hashmap(T)* hashmap, t_uint index, T item);

//s_hashmap(T)*       HashMap_New(T)           (t_uint n, T value);
//s_hashmap(T)*       HashMap_Create(T)        (t_uint n, ...);
//s_hashmap(T)*       HashMap_Duplicate(T)     (s_hashmap(T) const* hashmap);
//s_hashmap(T)*       HashMap_Sub(T)           (s_hashmap(T) const* hashmap, t_uint index, t_uint n);
//s_hashmap(T)*       HashMap_Copy(T)          (s_hashmap(T)* dest, t_uint dest_i, s_hashmap(T) const* src, t_uint src_i, t_uint n);

//void                HashMap_Free(T)          (s_hashmap(T)* hashmap);
//void                HashMap_Free_F(T)        (s_hashmap(T)* hashmap, void (*delete)(T* item));
//void                HashMap_Delete(T)        (s_hashmap(T)* *a_hashmap);
//void                HashMap_Delete_F(T)      (s_hashmap(T)* *a_hashmap, void (*delete)(T* item));

//s_hashmap(T)*       HashMap_Add(T)           (s_hashmap(T)* dest, T item);
//s_hashmap(T)*       HashMap_Insert(T)        (s_hashmap(T)* dest, T item, t_uint index);
//s_hashmap(T)*       HashMap_Wedge(T)         (s_hashmap(T)* hashmap, s_hashmap(T) const* src, t_uint index);
//s_hashmap(T)*       HashMap_RemoveAt(T)      (s_hashmap(T)* hashmap, t_uint index);
//s_hashmap(T)*       HashMap_RemoveAt_F(T)    (s_hashmap(T)* hashmap, t_uint index, void (*delete)(T));
//s_hashmap(T)*       HashMap_Remove(T)        (s_hashmap(T)* hashmap, T item);
//s_hashmap(T)*       HashMap_Remove_F(T)      (s_hashmap(T)* hashmap, T item, void (*delete)(T));
//s_hashmap(T)*       HashMap_RemoveAll(T)     (s_hashmap(T)* hashmap, T item);
//s_hashmap(T)*       HashMap_RemoveAll_F(T)   (s_hashmap(T)* hashmap, T item, void (*delete)(T));
//s_hashmap(T)*       HashMap_Replace(T)       (s_hashmap(T) const* hashmap, T old, T new);
//s_hashmap(T)*       HashMap_ReplaceFirst(T)  (s_hashmap(T) const* hashmap, T old, T new, t_uint n);
//s_hashmap(T)*       HashMap_ReplaceLast(T)   (s_hashmap(T) const* hashmap, T old, T new, t_uint n);
//s_hashmap(T)*       HashMap_Reverse(T)       (s_hashmap(T) const* hashmap);

//s_hashmap(T)*       HashMap_Concat(T)        (s_hashmap(T) const* hashmap1, s_hashmap(T) const* hashmap2);
//s_hashmap(T)*       HashMap_Append(T)        (s_hashmap(T)* hashmap1, s_hashmap(T) const* hashmap2);
//s_hashmap(T)*       HashMap_Prepend(T)       (s_hashmap(T) const* hashmap1, s_hashmap(T)* hashmap2);
//s_hashmap(T)*       HashMap_Merge(T)         (s_hashmap(T)* hashmap1, s_hashmap(T)* hashmap2);

//t_bool              HashMap_Equals(T)        (s_hashmap(T) const* hashmap1, s_hashmap(T) const* hashmap2);
//t_bool              HashMap_Equals_N(T)      (s_hashmap(T) const* hashmap1, s_hashmap(T) const* hashmap2, t_uint n);
//t_sint              HashMap_Compare(T)       (s_hashmap(T) const* hashmap1, s_hashmap(T) const* hashmap2, t_sint (*compare)(T item1, T item2));
//t_sint              HashMap_Compare_N(T)     (s_hashmap(T) const* hashmap1, s_hashmap(T) const* hashmap2, t_sint (*compare)(T item1, T item2), t_uint n);

//s_hashmap(T) const* HashMap_Find(T)          (s_hashmap(T) const* hashmap, T item);
//s_hashmap(T) const* HashMap_Find_F(T)        (s_hashmap(T) const* hashmap, t_bool (*match)(T item));
//t_sint              HashMap_IndexOf(T)       (s_hashmap(T) const* hashmap, T item);
//t_sint              HashMap_IndexOf_F(T)     (s_hashmap(T) const* hashmap, t_bool (*match)(T item));
//t_uint              HashMap_Count(T)         (s_hashmap(T) const* hashmap, T item);
//t_bool              HashMap_Contains(T)      (s_hashmap(T) const* hashmap, T item);
//t_bool              HashMap_Has(T)           (s_hashmap(T) const* hashmap, s_hashmap(T) const* targets);
//t_bool              HashMap_HasOnly(T)       (s_hashmap(T) const* hashmap, s_hashmap(T) const* targets);

//void                HashMap_Iterate(T)       (s_hashmap(T)* hashmap, void (*f)(T item));
//void                HashMap_Iterate_I(T)     (s_hashmap(T)* hashmap, void (*f)(T item, t_uint index));
//s_hashmap(T)*       HashMap_Map(T)           (s_hashmap(T) const* hashmap, T (*map)(T item));
//s_hashmap(T)*       HashMap_Map_I(T)         (s_hashmap(T) const* hashmap, T (*map)(T item, t_uint index));
//s_hashmap(T)*       HashMap_Filter(T)        (s_hashmap(T) const* hashmap, t_bool (*filter)(T item));
//s_hashmap(T)*       HashMap_Filter_I(T)      (s_hashmap(T) const* hashmap, t_bool (*filter)(T item, t_uint index));
//void*               HashMap_Reduce(T)        (s_hashmap(T) const* hashmap, void* (*f)(T item, void* acc));
//void*               HashMap_Reduce_I(T)      (s_hashmap(T) const* hashmap, void* (*f)(T item, void* acc, t_uint index));
//void*               HashMap_Fold(T)          (s_hashmap(T) const* hashmap, void* (*f)(T item, void* acc), void* initial);
//void*               HashMap_Fold_I(T)        (s_hashmap(T) const* hashmap, void* (*f)(T item, void* acc, t_uint index), void* initial);



/*! @endgroup */
HEADER_END
#endif
