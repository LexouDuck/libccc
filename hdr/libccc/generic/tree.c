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
#undef tree
#undef s_tree
#undef Tree_Item
#undef Tree_New
#undef Tree_Create
#undef Tree_Duplicate
#undef Tree_Clear
#undef Tree_Clear_F
#undef Tree_Free
#undef Tree_Free_F
#undef Tree_Delete
#undef Tree_Delete_F
#undef Tree_Get
#undef Tree_Set
#undef Tree_Append
#undef Tree_Prepend
#undef Tree_Insert
#undef Tree_RemoveAt
#undef Tree_RemoveAt_F
#undef Tree_Remove
#undef Tree_Remove_F
#undef Tree_RemoveAll
#undef Tree_RemoveAll_F
#undef Tree_Size
#undef Tree_Depth
#undef Tree_Find
#undef Tree_Find_F
#undef Tree_Count
#undef Tree_Contains
#undef Tree_Has
#undef Tree_HasOnly
#undef Tree_Equals
#undef Tree_Equals_N
#undef Tree_Iterate
#undef Tree_Iterate_D
#undef Tree_Map
#undef Tree_Filter
#undef Tree_Reduce
#undef Tree_Fold
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define tree(X)	CONCAT(tree_,	X##_NAME)
#define s_tree(X)	CONCAT(s_tree_,	X##_NAME)
#define Tree_Item(X)	CONCAT(Tree_Item_,	X##_NAME)
#define Tree_New(X)	CONCAT(Tree_New_,	X##_NAME)
#define Tree_Create(X)	CONCAT(Tree_Create_,	X##_NAME)
#define Tree_Duplicate(X)	CONCAT(Tree_Duplicate_,	X##_NAME)
#define Tree_Clear(X)	CONCAT(Tree_Clear_,	X##_NAME)
#define Tree_Clear_F(X)	CONCAT(Tree_Clear_F_,	X##_NAME)
#define Tree_Free(X)	CONCAT(Tree_Free_,	X##_NAME)
#define Tree_Free_F(X)	CONCAT(Tree_Free_F_,	X##_NAME)
#define Tree_Delete(X)	CONCAT(Tree_Delete_,	X##_NAME)
#define Tree_Delete_F(X)	CONCAT(Tree_Delete_F_,	X##_NAME)
#define Tree_Get(X)	CONCAT(Tree_Get_,	X##_NAME)
#define Tree_Set(X)	CONCAT(Tree_Set_,	X##_NAME)
#define Tree_Append(X)	CONCAT(Tree_Append_,	X##_NAME)
#define Tree_Prepend(X)	CONCAT(Tree_Prepend_,	X##_NAME)
#define Tree_Insert(X)	CONCAT(Tree_Insert_,	X##_NAME)
#define Tree_RemoveAt(X)	CONCAT(Tree_RemoveAt_,	X##_NAME)
#define Tree_RemoveAt_F(X)	CONCAT(Tree_RemoveAt_F_,	X##_NAME)
#define Tree_Remove(X)	CONCAT(Tree_Remove_,	X##_NAME)
#define Tree_Remove_F(X)	CONCAT(Tree_Remove_F_,	X##_NAME)
#define Tree_RemoveAll(X)	CONCAT(Tree_RemoveAll_,	X##_NAME)
#define Tree_RemoveAll_F(X)	CONCAT(Tree_RemoveAll_F_,	X##_NAME)
#define Tree_Size(X)	CONCAT(Tree_Size_,	X##_NAME)
#define Tree_Depth(X)	CONCAT(Tree_Depth_,	X##_NAME)
#define Tree_Find(X)	CONCAT(Tree_Find_,	X##_NAME)
#define Tree_Find_F(X)	CONCAT(Tree_Find_F_,	X##_NAME)
#define Tree_Count(X)	CONCAT(Tree_Count_,	X##_NAME)
#define Tree_Contains(X)	CONCAT(Tree_Contains_,	X##_NAME)
#define Tree_Has(X)	CONCAT(Tree_Has_,	X##_NAME)
#define Tree_HasOnly(X)	CONCAT(Tree_HasOnly_,	X##_NAME)
#define Tree_Equals(X)	CONCAT(Tree_Equals_,	X##_NAME)
#define Tree_Equals_N(X)	CONCAT(Tree_Equals_N_,	X##_NAME)
#define Tree_Iterate(X)	CONCAT(Tree_Iterate_,	X##_NAME)
#define Tree_Iterate_D(X)	CONCAT(Tree_Iterate_D_,	X##_NAME)
#define Tree_Map(X)	CONCAT(Tree_Map_,	X##_NAME)
#define Tree_Filter(X)	CONCAT(Tree_Filter_,	X##_NAME)
#define Tree_Reduce(X)	CONCAT(Tree_Reduce_,	X##_NAME)
#define Tree_Fold(X)	CONCAT(Tree_Fold_,	X##_NAME)
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
#undef __LIBCCC_GENERIC_TREE_H
#include "libccc/generic/tree.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../.././src/generic/tree/add.c"
#include "libccc/../.././src/generic/tree/count.c"
#include "libccc/../.././src/generic/tree/create.c"
#include "libccc/../.././src/generic/tree/delete.c"
#include "libccc/../.././src/generic/tree/duplicate.c"
#include "libccc/../.././src/generic/tree/equals.c"
#include "libccc/../.././src/generic/tree/filter.c"
#include "libccc/../.././src/generic/tree/find.c"
#include "libccc/../.././src/generic/tree/get.c"
#include "libccc/../.././src/generic/tree/has.c"
#include "libccc/../.././src/generic/tree/item.c"
#include "libccc/../.././src/generic/tree/iterate.c"
#include "libccc/../.././src/generic/tree/map.c"
#include "libccc/../.././src/generic/tree/new.c"
#include "libccc/../.././src/generic/tree/reduce.c"
#include "libccc/../.././src/generic/tree/remove.c"
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
#undef tree
#undef s_tree
#undef Tree_Item
#undef Tree_New
#undef Tree_Create
#undef Tree_Duplicate
#undef Tree_Clear
#undef Tree_Clear_F
#undef Tree_Free
#undef Tree_Free_F
#undef Tree_Delete
#undef Tree_Delete_F
#undef Tree_Get
#undef Tree_Set
#undef Tree_Append
#undef Tree_Prepend
#undef Tree_Insert
#undef Tree_RemoveAt
#undef Tree_RemoveAt_F
#undef Tree_Remove
#undef Tree_Remove_F
#undef Tree_RemoveAll
#undef Tree_RemoveAll_F
#undef Tree_Size
#undef Tree_Depth
#undef Tree_Find
#undef Tree_Find_F
#undef Tree_Count
#undef Tree_Contains
#undef Tree_Has
#undef Tree_HasOnly
#undef Tree_Equals
#undef Tree_Equals_N
#undef Tree_Iterate
#undef Tree_Iterate_D
#undef Tree_Map
#undef Tree_Filter
#undef Tree_Reduce
#undef Tree_Fold
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define tree(T)	CONCAT(tree_,	T)
#define s_tree(T)	CONCAT(s_tree_,	T)
#define Tree_Item(T)	CONCAT(Tree_Item_,	T)
#define Tree_New(T)	CONCAT(Tree_New_,	T)
#define Tree_Create(T)	CONCAT(Tree_Create_,	T)
#define Tree_Duplicate(T)	CONCAT(Tree_Duplicate_,	T)
#define Tree_Clear(T)	CONCAT(Tree_Clear_,	T)
#define Tree_Clear_F(T)	CONCAT(Tree_Clear_F_,	T)
#define Tree_Free(T)	CONCAT(Tree_Free_,	T)
#define Tree_Free_F(T)	CONCAT(Tree_Free_F_,	T)
#define Tree_Delete(T)	CONCAT(Tree_Delete_,	T)
#define Tree_Delete_F(T)	CONCAT(Tree_Delete_F_,	T)
#define Tree_Get(T)	CONCAT(Tree_Get_,	T)
#define Tree_Set(T)	CONCAT(Tree_Set_,	T)
#define Tree_Append(T)	CONCAT(Tree_Append_,	T)
#define Tree_Prepend(T)	CONCAT(Tree_Prepend_,	T)
#define Tree_Insert(T)	CONCAT(Tree_Insert_,	T)
#define Tree_RemoveAt(T)	CONCAT(Tree_RemoveAt_,	T)
#define Tree_RemoveAt_F(T)	CONCAT(Tree_RemoveAt_F_,	T)
#define Tree_Remove(T)	CONCAT(Tree_Remove_,	T)
#define Tree_Remove_F(T)	CONCAT(Tree_Remove_F_,	T)
#define Tree_RemoveAll(T)	CONCAT(Tree_RemoveAll_,	T)
#define Tree_RemoveAll_F(T)	CONCAT(Tree_RemoveAll_F_,	T)
#define Tree_Size(T)	CONCAT(Tree_Size_,	T)
#define Tree_Depth(T)	CONCAT(Tree_Depth_,	T)
#define Tree_Find(T)	CONCAT(Tree_Find_,	T)
#define Tree_Find_F(T)	CONCAT(Tree_Find_F_,	T)
#define Tree_Count(T)	CONCAT(Tree_Count_,	T)
#define Tree_Contains(T)	CONCAT(Tree_Contains_,	T)
#define Tree_Has(T)	CONCAT(Tree_Has_,	T)
#define Tree_HasOnly(T)	CONCAT(Tree_HasOnly_,	T)
#define Tree_Equals(T)	CONCAT(Tree_Equals_,	T)
#define Tree_Equals_N(T)	CONCAT(Tree_Equals_N_,	T)
#define Tree_Iterate(T)	CONCAT(Tree_Iterate_,	T)
#define Tree_Iterate_D(T)	CONCAT(Tree_Iterate_D_,	T)
#define Tree_Map(T)	CONCAT(Tree_Map_,	T)
#define Tree_Filter(T)	CONCAT(Tree_Filter_,	T)
#define Tree_Reduce(T)	CONCAT(Tree_Reduce_,	T)
#define Tree_Fold(T)	CONCAT(Tree_Fold_,	T)
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
