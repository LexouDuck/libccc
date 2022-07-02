/*============================================================================*\
||                                                                            ||
|| NOTE: This file is a generated source file - do not alter it manually here ||
|| Instead, (see 'make/rules/generic.mk' and 'make/rules/generic.template.c') ||
||                                                                            ||
\*============================================================================*/

//! This file is meant to be imported, instead of its corresponding .h file, to generate code



//! If the generic config macros haven't been defined, set them with `void*` type as default
//!@{
#ifndef T_TYPE
#define T_TYPE	void*
#endif
#ifndef T_NAME
#define T_NAME	any
#endif
#ifndef T_NULL
#define T_NULL	NULL
#endif
#ifndef T_EQUALS
#define T_EQUALS(A, B)	((A) == (B))
#endif
//!@}

//! Get rid of any previously-defined generic macros from user code
//!@{
#undef array
#undef s_array
#undef Array_Item
#undef Array_Get
#undef Array_Set
#undef Array_New
#undef Array_Create
#undef Array_Duplicate
#undef Array_Sub
#undef Array_Copy
#undef Array_Free
#undef Array_Free_F
#undef Array_Delete
#undef Array_Delete_F
#undef Array_FromMemory
#undef Array_ToMemory
#undef Array_FromPointerArray
#undef Array_ToPointerArray
#undef Array_Add
#undef Array_Insert
#undef Array_Wedge
#undef Array_RemoveAt
#undef Array_RemoveAt_F
#undef Array_Remove
#undef Array_Remove_F
#undef Array_RemoveAll
#undef Array_RemoveAll_F
#undef Array_Replace
#undef Array_ReplaceFirst
#undef Array_ReplaceLast
#undef Array_Reverse
#undef Array_Concat
#undef Array_Append
#undef Array_Prepend
#undef Array_Merge
#undef Array_Equals
#undef Array_Equals_N
#undef Array_Compare
#undef Array_Compare_N
#undef Array_Find
#undef Array_Find_F
#undef Array_IndexOf
#undef Array_IndexOf_F
#undef Array_Count
#undef Array_Contains
#undef Array_Has
#undef Array_HasOnly
#undef Array_Iterate
#undef Array_Iterate_I
#undef Array_Map
#undef Array_Map_I
#undef Array_Filter
#undef Array_Filter_I
#undef Array_Reduce
#undef Array_Reduce_I
#undef Array_Fold
#undef Array_Fold_I
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define array(X)	CONCAT(array_,	X##_NAME)
#define s_array(X)	CONCAT(s_array_,	X##_NAME)
#define Array_Item(X)	CONCAT(Array_Item_,	X##_NAME)
#define Array_Get(X)	CONCAT(Array_Get_,	X##_NAME)
#define Array_Set(X)	CONCAT(Array_Set_,	X##_NAME)
#define Array_New(X)	CONCAT(Array_New_,	X##_NAME)
#define Array_Create(X)	CONCAT(Array_Create_,	X##_NAME)
#define Array_Duplicate(X)	CONCAT(Array_Duplicate_,	X##_NAME)
#define Array_Sub(X)	CONCAT(Array_Sub_,	X##_NAME)
#define Array_Copy(X)	CONCAT(Array_Copy_,	X##_NAME)
#define Array_Free(X)	CONCAT(Array_Free_,	X##_NAME)
#define Array_Free_F(X)	CONCAT(Array_Free_F_,	X##_NAME)
#define Array_Delete(X)	CONCAT(Array_Delete_,	X##_NAME)
#define Array_Delete_F(X)	CONCAT(Array_Delete_F_,	X##_NAME)
#define Array_FromMemory(X)	CONCAT(Array_FromMemory_,	X##_NAME)
#define Array_ToMemory(X)	CONCAT(Array_ToMemory_,	X##_NAME)
#define Array_FromPointerArray(X)	CONCAT(Array_FromPointerArray_,	X##_NAME)
#define Array_ToPointerArray(X)	CONCAT(Array_ToPointerArray_,	X##_NAME)
#define Array_Add(X)	CONCAT(Array_Add_,	X##_NAME)
#define Array_Insert(X)	CONCAT(Array_Insert_,	X##_NAME)
#define Array_Wedge(X)	CONCAT(Array_Wedge_,	X##_NAME)
#define Array_RemoveAt(X)	CONCAT(Array_RemoveAt_,	X##_NAME)
#define Array_RemoveAt_F(X)	CONCAT(Array_RemoveAt_F_,	X##_NAME)
#define Array_Remove(X)	CONCAT(Array_Remove_,	X##_NAME)
#define Array_Remove_F(X)	CONCAT(Array_Remove_F_,	X##_NAME)
#define Array_RemoveAll(X)	CONCAT(Array_RemoveAll_,	X##_NAME)
#define Array_RemoveAll_F(X)	CONCAT(Array_RemoveAll_F_,	X##_NAME)
#define Array_Replace(X)	CONCAT(Array_Replace_,	X##_NAME)
#define Array_ReplaceFirst(X)	CONCAT(Array_ReplaceFirst_,	X##_NAME)
#define Array_ReplaceLast(X)	CONCAT(Array_ReplaceLast_,	X##_NAME)
#define Array_Reverse(X)	CONCAT(Array_Reverse_,	X##_NAME)
#define Array_Concat(X)	CONCAT(Array_Concat_,	X##_NAME)
#define Array_Append(X)	CONCAT(Array_Append_,	X##_NAME)
#define Array_Prepend(X)	CONCAT(Array_Prepend_,	X##_NAME)
#define Array_Merge(X)	CONCAT(Array_Merge_,	X##_NAME)
#define Array_Equals(X)	CONCAT(Array_Equals_,	X##_NAME)
#define Array_Equals_N(X)	CONCAT(Array_Equals_N_,	X##_NAME)
#define Array_Compare(X)	CONCAT(Array_Compare_,	X##_NAME)
#define Array_Compare_N(X)	CONCAT(Array_Compare_N_,	X##_NAME)
#define Array_Find(X)	CONCAT(Array_Find_,	X##_NAME)
#define Array_Find_F(X)	CONCAT(Array_Find_F_,	X##_NAME)
#define Array_IndexOf(X)	CONCAT(Array_IndexOf_,	X##_NAME)
#define Array_IndexOf_F(X)	CONCAT(Array_IndexOf_F_,	X##_NAME)
#define Array_Count(X)	CONCAT(Array_Count_,	X##_NAME)
#define Array_Contains(X)	CONCAT(Array_Contains_,	X##_NAME)
#define Array_Has(X)	CONCAT(Array_Has_,	X##_NAME)
#define Array_HasOnly(X)	CONCAT(Array_HasOnly_,	X##_NAME)
#define Array_Iterate(X)	CONCAT(Array_Iterate_,	X##_NAME)
#define Array_Iterate_I(X)	CONCAT(Array_Iterate_I_,	X##_NAME)
#define Array_Map(X)	CONCAT(Array_Map_,	X##_NAME)
#define Array_Map_I(X)	CONCAT(Array_Map_I_,	X##_NAME)
#define Array_Filter(X)	CONCAT(Array_Filter_,	X##_NAME)
#define Array_Filter_I(X)	CONCAT(Array_Filter_I_,	X##_NAME)
#define Array_Reduce(X)	CONCAT(Array_Reduce_,	X##_NAME)
#define Array_Reduce_I(X)	CONCAT(Array_Reduce_I_,	X##_NAME)
#define Array_Fold(X)	CONCAT(Array_Fold_,	X##_NAME)
#define Array_Fold_I(X)	CONCAT(Array_Fold_I_,	X##_NAME)
//!@}



//! NOTE: The next part of the file is not present when included from the .h header file
#ifndef T
#define T	T_TYPE



//! Make all generic functions be defined as `static`, so that dead code elimination can occur on any compiler
//!@{
#undef _GENERIC

#if (defined(__GNUC__) || defined(__llvm__))
#define _GENERIC()	__attribute__((unused)) static

#elif defined(__MSVC__)
#pragma warning(push)
#pragma warning(disable : 4505)
#define _GENERIC()	static

#else
#define _GENERIC()	static

#endif
//!@}

//! Force re-inclusion of header (with the current generic type `T`)
//!@{
#undef __LIBCCC_MONAD_ARRAY_H
#include "libccc/monad/array.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../.././src/monad/array/add.c"
#include "libccc/../.././src/monad/array/compare.c"
#include "libccc/../.././src/monad/array/concat.c"
#include "libccc/../.././src/monad/array/contains.c"
#include "libccc/../.././src/monad/array/copy.c"
#include "libccc/../.././src/monad/array/count.c"
#include "libccc/../.././src/monad/array/create.c"
#include "libccc/../.././src/monad/array/delete.c"
#include "libccc/../.././src/monad/array/duplicate.c"
#include "libccc/../.././src/monad/array/equals.c"
#include "libccc/../.././src/monad/array/filter.c"
#include "libccc/../.././src/monad/array/find.c"
#include "libccc/../.././src/monad/array/get.c"
#include "libccc/../.././src/monad/array/has.c"
#include "libccc/../.././src/monad/array/insert.c"
#include "libccc/../.././src/monad/array/item.c"
#include "libccc/../.././src/monad/array/iterate.c"
#include "libccc/../.././src/monad/array/map.c"
#include "libccc/../.././src/monad/array/new.c"
#include "libccc/../.././src/monad/array/reduce.c"
#include "libccc/../.././src/monad/array/remove.c"
#include "libccc/../.././src/monad/array/removeat.c"
#include "libccc/../.././src/monad/array/replace.c"
#include "libccc/../.././src/monad/array/reverse.c"
#include "libccc/../.././src/monad/array/set.c"
#include "libccc/../.././src/monad/array/sub.c"
#include "libccc/../.././src/monad/array/wedge.c"
//!@}

//! Redefine the `_GENERIC()` macro as empty, so everything works as normal again
//!@{
#undef _GENERIC

#if (defined(__GNUC__) || defined(__llvm__))
#define _GENERIC()	

#elif defined(__MSVC__)
#pragma warning(pop)
#define _GENERIC()	

#else
#define _GENERIC()	

#endif
//!@}

//! Get rid of all generic macros used for declaration
//!@{
#undef array
#undef s_array
#undef Array_Item
#undef Array_Get
#undef Array_Set
#undef Array_New
#undef Array_Create
#undef Array_Duplicate
#undef Array_Sub
#undef Array_Copy
#undef Array_Free
#undef Array_Free_F
#undef Array_Delete
#undef Array_Delete_F
#undef Array_FromMemory
#undef Array_ToMemory
#undef Array_FromPointerArray
#undef Array_ToPointerArray
#undef Array_Add
#undef Array_Insert
#undef Array_Wedge
#undef Array_RemoveAt
#undef Array_RemoveAt_F
#undef Array_Remove
#undef Array_Remove_F
#undef Array_RemoveAll
#undef Array_RemoveAll_F
#undef Array_Replace
#undef Array_ReplaceFirst
#undef Array_ReplaceLast
#undef Array_Reverse
#undef Array_Concat
#undef Array_Append
#undef Array_Prepend
#undef Array_Merge
#undef Array_Equals
#undef Array_Equals_N
#undef Array_Compare
#undef Array_Compare_N
#undef Array_Find
#undef Array_Find_F
#undef Array_IndexOf
#undef Array_IndexOf_F
#undef Array_Count
#undef Array_Contains
#undef Array_Has
#undef Array_HasOnly
#undef Array_Iterate
#undef Array_Iterate_I
#undef Array_Map
#undef Array_Map_I
#undef Array_Filter
#undef Array_Filter_I
#undef Array_Reduce
#undef Array_Reduce_I
#undef Array_Fold
#undef Array_Fold_I
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define array(T)	CONCAT(array_,	T)
#define s_array(T)	CONCAT(s_array_,	T)
#define Array_Item(T)	CONCAT(Array_Item_,	T)
#define Array_Get(T)	CONCAT(Array_Get_,	T)
#define Array_Set(T)	CONCAT(Array_Set_,	T)
#define Array_New(T)	CONCAT(Array_New_,	T)
#define Array_Create(T)	CONCAT(Array_Create_,	T)
#define Array_Duplicate(T)	CONCAT(Array_Duplicate_,	T)
#define Array_Sub(T)	CONCAT(Array_Sub_,	T)
#define Array_Copy(T)	CONCAT(Array_Copy_,	T)
#define Array_Free(T)	CONCAT(Array_Free_,	T)
#define Array_Free_F(T)	CONCAT(Array_Free_F_,	T)
#define Array_Delete(T)	CONCAT(Array_Delete_,	T)
#define Array_Delete_F(T)	CONCAT(Array_Delete_F_,	T)
#define Array_FromMemory(T)	CONCAT(Array_FromMemory_,	T)
#define Array_ToMemory(T)	CONCAT(Array_ToMemory_,	T)
#define Array_FromPointerArray(T)	CONCAT(Array_FromPointerArray_,	T)
#define Array_ToPointerArray(T)	CONCAT(Array_ToPointerArray_,	T)
#define Array_Add(T)	CONCAT(Array_Add_,	T)
#define Array_Insert(T)	CONCAT(Array_Insert_,	T)
#define Array_Wedge(T)	CONCAT(Array_Wedge_,	T)
#define Array_RemoveAt(T)	CONCAT(Array_RemoveAt_,	T)
#define Array_RemoveAt_F(T)	CONCAT(Array_RemoveAt_F_,	T)
#define Array_Remove(T)	CONCAT(Array_Remove_,	T)
#define Array_Remove_F(T)	CONCAT(Array_Remove_F_,	T)
#define Array_RemoveAll(T)	CONCAT(Array_RemoveAll_,	T)
#define Array_RemoveAll_F(T)	CONCAT(Array_RemoveAll_F_,	T)
#define Array_Replace(T)	CONCAT(Array_Replace_,	T)
#define Array_ReplaceFirst(T)	CONCAT(Array_ReplaceFirst_,	T)
#define Array_ReplaceLast(T)	CONCAT(Array_ReplaceLast_,	T)
#define Array_Reverse(T)	CONCAT(Array_Reverse_,	T)
#define Array_Concat(T)	CONCAT(Array_Concat_,	T)
#define Array_Append(T)	CONCAT(Array_Append_,	T)
#define Array_Prepend(T)	CONCAT(Array_Prepend_,	T)
#define Array_Merge(T)	CONCAT(Array_Merge_,	T)
#define Array_Equals(T)	CONCAT(Array_Equals_,	T)
#define Array_Equals_N(T)	CONCAT(Array_Equals_N_,	T)
#define Array_Compare(T)	CONCAT(Array_Compare_,	T)
#define Array_Compare_N(T)	CONCAT(Array_Compare_N_,	T)
#define Array_Find(T)	CONCAT(Array_Find_,	T)
#define Array_Find_F(T)	CONCAT(Array_Find_F_,	T)
#define Array_IndexOf(T)	CONCAT(Array_IndexOf_,	T)
#define Array_IndexOf_F(T)	CONCAT(Array_IndexOf_F_,	T)
#define Array_Count(T)	CONCAT(Array_Count_,	T)
#define Array_Contains(T)	CONCAT(Array_Contains_,	T)
#define Array_Has(T)	CONCAT(Array_Has_,	T)
#define Array_HasOnly(T)	CONCAT(Array_HasOnly_,	T)
#define Array_Iterate(T)	CONCAT(Array_Iterate_,	T)
#define Array_Iterate_I(T)	CONCAT(Array_Iterate_I_,	T)
#define Array_Map(T)	CONCAT(Array_Map_,	T)
#define Array_Map_I(T)	CONCAT(Array_Map_I_,	T)
#define Array_Filter(T)	CONCAT(Array_Filter_,	T)
#define Array_Filter_I(T)	CONCAT(Array_Filter_I_,	T)
#define Array_Reduce(T)	CONCAT(Array_Reduce_,	T)
#define Array_Reduce_I(T)	CONCAT(Array_Reduce_I_,	T)
#define Array_Fold(T)	CONCAT(Array_Fold_,	T)
#define Array_Fold_I(T)	CONCAT(Array_Fold_I_,	T)
//!@}



//! Get rid of all user-specified generic type config macros
//!@{
#undef T
#undef T_TYPE
#undef T_NAME
#undef T_NULL
#undef T_EQUALS
//!@}

#endif
