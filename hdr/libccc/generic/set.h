/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/set.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_SET_H
#define __LIBCCC_GENERIC_SET_H
/*!@group{libccc_generic_set,32,libccc/generic/set.h}
**
**	This header defines a generic set type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/generic/set.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A dynamic set struct, stores several hash-value pairs
/*
**	TODO document this
*/
struct set(T)
{
	t_uint	length;	//!< The amount of items in this set
	T*		items;	//!< The values contained within this set
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct set(T)	s_set(T);
#endif



#define foreach_s_set_init(     _TYPE_, _VAR_, _SET_)	
#define foreach_s_set_exit(     _TYPE_, _VAR_, _SET_)	
#define foreach_s_set_loop_init(_TYPE_, _VAR_, _SET_)	
#define foreach_s_set_loop_exit(_TYPE_, _VAR_, _SET_)	
#define foreach_s_set_loop_incr(_TYPE_, _VAR_, _SET_)	



/*============================================================================*\
||                            Set: basic operations                           ||
\*============================================================================*/

//s_set(T)*       Set_Item(T)          (T item);
//t_uint          Set_Length(T)        (s_set(T) const* set);
//T*              Set_Get(T)           (s_set(T) const* set, t_uint index);
//T*              Set_Set(T)           (s_set(T)* set, t_uint index, T item);

//s_set(T)*       Set_New(T)           (t_uint n, T value);
//s_set(T)*       Set_Create(T)        (t_uint n, ...);
//s_set(T)*       Set_Duplicate(T)     (s_set(T) const* set);
//s_set(T)*       Set_Sub(T)           (s_set(T) const* set, t_uint index, t_uint n);
//s_set(T)*       Set_Copy(T)          (s_set(T)* dest, t_uint dest_i, s_set(T) const* src, t_uint src_i, t_uint n);

//void            Set_Free(T)          (s_set(T)* set);
//void            Set_Free_F(T)        (s_set(T)* set, void (*delete)(T* item));
//void            Set_Delete(T)        (s_set(T)* *a_set);
//void            Set_Delete_F(T)      (s_set(T)* *a_set, void (*delete)(T* item));

//s_set(T)*       Set_Add(T)           (s_set(T)* dest, T item);
//s_set(T)*       Set_Insert(T)        (s_set(T)* dest, T item, t_uint index);
//s_set(T)*       Set_Wedge(T)         (s_set(T)* set, s_set(T) const* src, t_uint index);
//s_set(T)*       Set_RemoveAt(T)      (s_set(T)* set, t_uint index);
//s_set(T)*       Set_RemoveAt_F(T)    (s_set(T)* set, t_uint index, void (*delete)(T));
//s_set(T)*       Set_Remove(T)        (s_set(T)* set, T item);
//s_set(T)*       Set_Remove_F(T)      (s_set(T)* set, T item, void (*delete)(T));
//s_set(T)*       Set_RemoveAll(T)     (s_set(T)* set, T item);
//s_set(T)*       Set_RemoveAll_F(T)   (s_set(T)* set, T item, void (*delete)(T));
//s_set(T)*       Set_Replace(T)       (s_set(T) const* set, T old, T new);
//s_set(T)*       Set_ReplaceFirst(T)  (s_set(T) const* set, T old, T new, t_uint n);
//s_set(T)*       Set_ReplaceLast(T)   (s_set(T) const* set, T old, T new, t_uint n);
//s_set(T)*       Set_Reverse(T)       (s_set(T) const* set);

//s_set(T)*       Set_Concat(T)        (s_set(T) const* set1, s_set(T) const* set2);
//s_set(T)*       Set_Append(T)        (s_set(T)* set1, s_set(T) const* set2);
//s_set(T)*       Set_Prepend(T)       (s_set(T) const* set1, s_set(T)* set2);
//s_set(T)*       Set_Merge(T)         (s_set(T)* set1, s_set(T)* set2);

//t_bool          Set_Equals(T)        (s_set(T) const* set1, s_set(T) const* set2);
//t_bool          Set_Equals_N(T)      (s_set(T) const* set1, s_set(T) const* set2, t_uint n);
//t_sint          Set_Compare(T)       (s_set(T) const* set1, s_set(T) const* set2, t_sint (*compare)(T item1, T item2));
//t_sint          Set_Compare_N(T)     (s_set(T) const* set1, s_set(T) const* set2, t_sint (*compare)(T item1, T item2), t_uint n);

//s_set(T) const* Set_Find(T)          (s_set(T) const* set, T item);
//s_set(T) const* Set_Find_F(T)        (s_set(T) const* set, t_bool (*match)(T item));
//t_sint          Set_IndexOf(T)       (s_set(T) const* set, T item);
//t_sint          Set_IndexOf_F(T)     (s_set(T) const* set, t_bool (*match)(T item));
//t_uint          Set_Count(T)         (s_set(T) const* set, T item);
//t_bool          Set_Contains(T)      (s_set(T) const* set, T item);
//t_bool          Set_Has(T)           (s_set(T) const* set, s_set(T) const* targets);
//t_bool          Set_HasOnly(T)       (s_set(T) const* set, s_set(T) const* targets);

//void            Set_Iterate(T)       (s_set(T)* set, void (*f)(T item));
//void            Set_Iterate_I(T)     (s_set(T)* set, void (*f)(T item, t_uint index));
//s_set(T)*       Set_Map(T)           (s_set(T) const* set, T (*map)(T item));
//s_set(T)*       Set_Map_I(T)         (s_set(T) const* set, T (*map)(T item, t_uint index));
//s_set(T)*       Set_Filter(T)        (s_set(T) const* set, t_bool (*filter)(T item));
//s_set(T)*       Set_Filter_I(T)      (s_set(T) const* set, t_bool (*filter)(T item, t_uint index));
//void*           Set_Reduce(T)        (s_set(T) const* set, void* (*f)(T item, void* acc));
//void*           Set_Reduce_I(T)      (s_set(T) const* set, void* (*f)(T item, void* acc, t_uint index));
//void*           Set_Fold(T)          (s_set(T) const* set, void* (*f)(T item, void* acc), void* initial);
//void*           Set_Fold_I(T)        (s_set(T) const* set, void* (*f)(T item, void* acc, t_uint index), void* initial);



/*! @endgroup */
HEADER_END
#endif
