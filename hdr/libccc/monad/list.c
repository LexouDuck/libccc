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
#undef list
#undef s_list
#undef List_Item
#undef List_Length
#undef List_Get
#undef List_Set
#undef List_New
#undef List_Create
#undef List_Duplicate
#undef List_Sub
#undef List_Copy
#undef List_Free
#undef List_Free_F
#undef List_Delete
#undef List_Delete_F
#undef List_Add
#undef List_Insert
#undef List_Wedge
#undef List_RemoveAt
#undef List_RemoveAt_F
#undef List_Remove
#undef List_Remove_F
#undef List_RemoveAll
#undef List_RemoveAll_F
#undef List_Replace
#undef List_ReplaceFirst
#undef List_ReplaceLast
#undef List_Reverse
#undef List_Concat
#undef List_Append
#undef List_Prepend
#undef List_Merge
#undef List_Equals
#undef List_Equals_N
#undef List_Compare
#undef List_Compare_N
#undef List_Find
#undef List_Find_F
#undef List_IndexOf
#undef List_IndexOf_F
#undef List_Count
#undef List_Contains
#undef List_Has
#undef List_HasOnly
#undef List_Iterate
#undef List_Iterate_I
#undef List_Map
#undef List_Map_I
#undef List_Filter
#undef List_Filter_I
#undef List_Reduce
#undef List_Reduce_I
#undef List_Fold
#undef List_Fold_I
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define list(X)	CONCAT(list_,	X##_NAME)
#define s_list(X)	CONCAT(s_list_,	X##_NAME)
#define List_Item(X)	CONCAT(List_Item_,	X##_NAME)
#define List_Length(X)	CONCAT(List_Length_,	X##_NAME)
#define List_Get(X)	CONCAT(List_Get_,	X##_NAME)
#define List_Set(X)	CONCAT(List_Set_,	X##_NAME)
#define List_New(X)	CONCAT(List_New_,	X##_NAME)
#define List_Create(X)	CONCAT(List_Create_,	X##_NAME)
#define List_Duplicate(X)	CONCAT(List_Duplicate_,	X##_NAME)
#define List_Sub(X)	CONCAT(List_Sub_,	X##_NAME)
#define List_Copy(X)	CONCAT(List_Copy_,	X##_NAME)
#define List_Free(X)	CONCAT(List_Free_,	X##_NAME)
#define List_Free_F(X)	CONCAT(List_Free_F_,	X##_NAME)
#define List_Delete(X)	CONCAT(List_Delete_,	X##_NAME)
#define List_Delete_F(X)	CONCAT(List_Delete_F_,	X##_NAME)
#define List_Add(X)	CONCAT(List_Add_,	X##_NAME)
#define List_Insert(X)	CONCAT(List_Insert_,	X##_NAME)
#define List_Wedge(X)	CONCAT(List_Wedge_,	X##_NAME)
#define List_RemoveAt(X)	CONCAT(List_RemoveAt_,	X##_NAME)
#define List_RemoveAt_F(X)	CONCAT(List_RemoveAt_F_,	X##_NAME)
#define List_Remove(X)	CONCAT(List_Remove_,	X##_NAME)
#define List_Remove_F(X)	CONCAT(List_Remove_F_,	X##_NAME)
#define List_RemoveAll(X)	CONCAT(List_RemoveAll_,	X##_NAME)
#define List_RemoveAll_F(X)	CONCAT(List_RemoveAll_F_,	X##_NAME)
#define List_Replace(X)	CONCAT(List_Replace_,	X##_NAME)
#define List_ReplaceFirst(X)	CONCAT(List_ReplaceFirst_,	X##_NAME)
#define List_ReplaceLast(X)	CONCAT(List_ReplaceLast_,	X##_NAME)
#define List_Reverse(X)	CONCAT(List_Reverse_,	X##_NAME)
#define List_Concat(X)	CONCAT(List_Concat_,	X##_NAME)
#define List_Append(X)	CONCAT(List_Append_,	X##_NAME)
#define List_Prepend(X)	CONCAT(List_Prepend_,	X##_NAME)
#define List_Merge(X)	CONCAT(List_Merge_,	X##_NAME)
#define List_Equals(X)	CONCAT(List_Equals_,	X##_NAME)
#define List_Equals_N(X)	CONCAT(List_Equals_N_,	X##_NAME)
#define List_Compare(X)	CONCAT(List_Compare_,	X##_NAME)
#define List_Compare_N(X)	CONCAT(List_Compare_N_,	X##_NAME)
#define List_Find(X)	CONCAT(List_Find_,	X##_NAME)
#define List_Find_F(X)	CONCAT(List_Find_F_,	X##_NAME)
#define List_IndexOf(X)	CONCAT(List_IndexOf_,	X##_NAME)
#define List_IndexOf_F(X)	CONCAT(List_IndexOf_F_,	X##_NAME)
#define List_Count(X)	CONCAT(List_Count_,	X##_NAME)
#define List_Contains(X)	CONCAT(List_Contains_,	X##_NAME)
#define List_Has(X)	CONCAT(List_Has_,	X##_NAME)
#define List_HasOnly(X)	CONCAT(List_HasOnly_,	X##_NAME)
#define List_Iterate(X)	CONCAT(List_Iterate_,	X##_NAME)
#define List_Iterate_I(X)	CONCAT(List_Iterate_I_,	X##_NAME)
#define List_Map(X)	CONCAT(List_Map_,	X##_NAME)
#define List_Map_I(X)	CONCAT(List_Map_I_,	X##_NAME)
#define List_Filter(X)	CONCAT(List_Filter_,	X##_NAME)
#define List_Filter_I(X)	CONCAT(List_Filter_I_,	X##_NAME)
#define List_Reduce(X)	CONCAT(List_Reduce_,	X##_NAME)
#define List_Reduce_I(X)	CONCAT(List_Reduce_I_,	X##_NAME)
#define List_Fold(X)	CONCAT(List_Fold_,	X##_NAME)
#define List_Fold_I(X)	CONCAT(List_Fold_I_,	X##_NAME)
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
#undef __LIBCCC_MONAD_LIST_H
#include "./hdr/libccc/monad/list.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../../src/monad/list/add.c"
#include "libccc/../../src/monad/list/compare.c"
#include "libccc/../../src/monad/list/concat.c"
#include "libccc/../../src/monad/list/contains.c"
#include "libccc/../../src/monad/list/copy.c"
#include "libccc/../../src/monad/list/count.c"
#include "libccc/../../src/monad/list/create.c"
#include "libccc/../../src/monad/list/delete.c"
#include "libccc/../../src/monad/list/duplicate.c"
#include "libccc/../../src/monad/list/equals.c"
#include "libccc/../../src/monad/list/filter.c"
#include "libccc/../../src/monad/list/find.c"
#include "libccc/../../src/monad/list/free.c"
#include "libccc/../../src/monad/list/get.c"
#include "libccc/../../src/monad/list/has.c"
#include "libccc/../../src/monad/list/insert.c"
#include "libccc/../../src/monad/list/item.c"
#include "libccc/../../src/monad/list/iterate.c"
#include "libccc/../../src/monad/list/length.c"
#include "libccc/../../src/monad/list/map.c"
#include "libccc/../../src/monad/list/new.c"
#include "libccc/../../src/monad/list/reduce.c"
#include "libccc/../../src/monad/list/remove.c"
#include "libccc/../../src/monad/list/removeat.c"
#include "libccc/../../src/monad/list/replace.c"
#include "libccc/../../src/monad/list/reverse.c"
#include "libccc/../../src/monad/list/set.c"
#include "libccc/../../src/monad/list/sub.c"
#include "libccc/../../src/monad/list/wedge.c"
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
#undef list
#undef s_list
#undef List_Item
#undef List_Length
#undef List_Get
#undef List_Set
#undef List_New
#undef List_Create
#undef List_Duplicate
#undef List_Sub
#undef List_Copy
#undef List_Free
#undef List_Free_F
#undef List_Delete
#undef List_Delete_F
#undef List_Add
#undef List_Insert
#undef List_Wedge
#undef List_RemoveAt
#undef List_RemoveAt_F
#undef List_Remove
#undef List_Remove_F
#undef List_RemoveAll
#undef List_RemoveAll_F
#undef List_Replace
#undef List_ReplaceFirst
#undef List_ReplaceLast
#undef List_Reverse
#undef List_Concat
#undef List_Append
#undef List_Prepend
#undef List_Merge
#undef List_Equals
#undef List_Equals_N
#undef List_Compare
#undef List_Compare_N
#undef List_Find
#undef List_Find_F
#undef List_IndexOf
#undef List_IndexOf_F
#undef List_Count
#undef List_Contains
#undef List_Has
#undef List_HasOnly
#undef List_Iterate
#undef List_Iterate_I
#undef List_Map
#undef List_Map_I
#undef List_Filter
#undef List_Filter_I
#undef List_Reduce
#undef List_Reduce_I
#undef List_Fold
#undef List_Fold_I
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define list(T)	CONCAT(list_,	T)
#define s_list(T)	CONCAT(s_list_,	T)
#define List_Item(T)	CONCAT(List_Item_,	T)
#define List_Length(T)	CONCAT(List_Length_,	T)
#define List_Get(T)	CONCAT(List_Get_,	T)
#define List_Set(T)	CONCAT(List_Set_,	T)
#define List_New(T)	CONCAT(List_New_,	T)
#define List_Create(T)	CONCAT(List_Create_,	T)
#define List_Duplicate(T)	CONCAT(List_Duplicate_,	T)
#define List_Sub(T)	CONCAT(List_Sub_,	T)
#define List_Copy(T)	CONCAT(List_Copy_,	T)
#define List_Free(T)	CONCAT(List_Free_,	T)
#define List_Free_F(T)	CONCAT(List_Free_F_,	T)
#define List_Delete(T)	CONCAT(List_Delete_,	T)
#define List_Delete_F(T)	CONCAT(List_Delete_F_,	T)
#define List_Add(T)	CONCAT(List_Add_,	T)
#define List_Insert(T)	CONCAT(List_Insert_,	T)
#define List_Wedge(T)	CONCAT(List_Wedge_,	T)
#define List_RemoveAt(T)	CONCAT(List_RemoveAt_,	T)
#define List_RemoveAt_F(T)	CONCAT(List_RemoveAt_F_,	T)
#define List_Remove(T)	CONCAT(List_Remove_,	T)
#define List_Remove_F(T)	CONCAT(List_Remove_F_,	T)
#define List_RemoveAll(T)	CONCAT(List_RemoveAll_,	T)
#define List_RemoveAll_F(T)	CONCAT(List_RemoveAll_F_,	T)
#define List_Replace(T)	CONCAT(List_Replace_,	T)
#define List_ReplaceFirst(T)	CONCAT(List_ReplaceFirst_,	T)
#define List_ReplaceLast(T)	CONCAT(List_ReplaceLast_,	T)
#define List_Reverse(T)	CONCAT(List_Reverse_,	T)
#define List_Concat(T)	CONCAT(List_Concat_,	T)
#define List_Append(T)	CONCAT(List_Append_,	T)
#define List_Prepend(T)	CONCAT(List_Prepend_,	T)
#define List_Merge(T)	CONCAT(List_Merge_,	T)
#define List_Equals(T)	CONCAT(List_Equals_,	T)
#define List_Equals_N(T)	CONCAT(List_Equals_N_,	T)
#define List_Compare(T)	CONCAT(List_Compare_,	T)
#define List_Compare_N(T)	CONCAT(List_Compare_N_,	T)
#define List_Find(T)	CONCAT(List_Find_,	T)
#define List_Find_F(T)	CONCAT(List_Find_F_,	T)
#define List_IndexOf(T)	CONCAT(List_IndexOf_,	T)
#define List_IndexOf_F(T)	CONCAT(List_IndexOf_F_,	T)
#define List_Count(T)	CONCAT(List_Count_,	T)
#define List_Contains(T)	CONCAT(List_Contains_,	T)
#define List_Has(T)	CONCAT(List_Has_,	T)
#define List_HasOnly(T)	CONCAT(List_HasOnly_,	T)
#define List_Iterate(T)	CONCAT(List_Iterate_,	T)
#define List_Iterate_I(T)	CONCAT(List_Iterate_I_,	T)
#define List_Map(T)	CONCAT(List_Map_,	T)
#define List_Map_I(T)	CONCAT(List_Map_I_,	T)
#define List_Filter(T)	CONCAT(List_Filter_,	T)
#define List_Filter_I(T)	CONCAT(List_Filter_I_,	T)
#define List_Reduce(T)	CONCAT(List_Reduce_,	T)
#define List_Reduce_I(T)	CONCAT(List_Reduce_I_,	T)
#define List_Fold(T)	CONCAT(List_Fold_,	T)
#define List_Fold_I(T)	CONCAT(List_Fold_I_,	T)
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
