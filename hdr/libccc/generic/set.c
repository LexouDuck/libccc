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
#undef set
#undef s_set
#undef Set_New
#undef Set_Item
#undef Set_Create
#undef Set_Duplicate
#undef Set_Free
#undef Set_Free_F
#undef Set_Delete
#undef Set_Delete_F
#undef Set_Length
#undef Set_Contains
#undef Set_Find
#undef Set_Find_F
#undef Set_Add
#undef Set_Remove
#undef Set_Remove_F
#undef Set_Equals
#undef Set_IsSubset
#undef Set_IsDisjoint
#undef Set_Union
#undef Set_Intersect
#undef Set_Difference
#undef Set_Iterate
#undef Set_Iterate_I
#undef Set_Map
#undef Set_Filter
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define set(X)	CONCAT(set_,	X##_NAME)
#define s_set(X)	CONCAT(s_set_,	X##_NAME)
#define Set_New(X)	CONCAT(Set_New_,	X##_NAME)
#define Set_Item(X)	CONCAT(Set_Item_,	X##_NAME)
#define Set_Create(X)	CONCAT(Set_Create_,	X##_NAME)
#define Set_Duplicate(X)	CONCAT(Set_Duplicate_,	X##_NAME)
#define Set_Free(X)	CONCAT(Set_Free_,	X##_NAME)
#define Set_Free_F(X)	CONCAT(Set_Free_F_,	X##_NAME)
#define Set_Delete(X)	CONCAT(Set_Delete_,	X##_NAME)
#define Set_Delete_F(X)	CONCAT(Set_Delete_F_,	X##_NAME)
#define Set_Length(X)	CONCAT(Set_Length_,	X##_NAME)
#define Set_Contains(X)	CONCAT(Set_Contains_,	X##_NAME)
#define Set_Find(X)	CONCAT(Set_Find_,	X##_NAME)
#define Set_Find_F(X)	CONCAT(Set_Find_F_,	X##_NAME)
#define Set_Add(X)	CONCAT(Set_Add_,	X##_NAME)
#define Set_Remove(X)	CONCAT(Set_Remove_,	X##_NAME)
#define Set_Remove_F(X)	CONCAT(Set_Remove_F_,	X##_NAME)
#define Set_Equals(X)	CONCAT(Set_Equals_,	X##_NAME)
#define Set_IsSubset(X)	CONCAT(Set_IsSubset_,	X##_NAME)
#define Set_IsDisjoint(X)	CONCAT(Set_IsDisjoint_,	X##_NAME)
#define Set_Union(X)	CONCAT(Set_Union_,	X##_NAME)
#define Set_Intersect(X)	CONCAT(Set_Intersect_,	X##_NAME)
#define Set_Difference(X)	CONCAT(Set_Difference_,	X##_NAME)
#define Set_Iterate(X)	CONCAT(Set_Iterate_,	X##_NAME)
#define Set_Iterate_I(X)	CONCAT(Set_Iterate_I_,	X##_NAME)
#define Set_Map(X)	CONCAT(Set_Map_,	X##_NAME)
#define Set_Filter(X)	CONCAT(Set_Filter_,	X##_NAME)
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
#undef __LIBCCC_GENERIC_SET_H
#include "libccc/generic/set.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../.././src/generic/set/add.c"
#include "libccc/../.././src/generic/set/count.c"
#include "libccc/../.././src/generic/set/create.c"
#include "libccc/../.././src/generic/set/delete.c"
#include "libccc/../.././src/generic/set/duplicate.c"
#include "libccc/../.././src/generic/set/equals.c"
#include "libccc/../.././src/generic/set/filter.c"
#include "libccc/../.././src/generic/set/find.c"
#include "libccc/../.././src/generic/set/iterate.c"
#include "libccc/../.././src/generic/set/map.c"
#include "libccc/../.././src/generic/set/new.c"
#include "libccc/../.././src/generic/set/remove.c"
#include "libccc/../.././src/generic/set/setops.c"
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
#undef set
#undef s_set
#undef Set_New
#undef Set_Item
#undef Set_Create
#undef Set_Duplicate
#undef Set_Free
#undef Set_Free_F
#undef Set_Delete
#undef Set_Delete_F
#undef Set_Length
#undef Set_Contains
#undef Set_Find
#undef Set_Find_F
#undef Set_Add
#undef Set_Remove
#undef Set_Remove_F
#undef Set_Equals
#undef Set_IsSubset
#undef Set_IsDisjoint
#undef Set_Union
#undef Set_Intersect
#undef Set_Difference
#undef Set_Iterate
#undef Set_Iterate_I
#undef Set_Map
#undef Set_Filter
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define set(T)	CONCAT(set_,	T)
#define s_set(T)	CONCAT(s_set_,	T)
#define Set_New(T)	CONCAT(Set_New_,	T)
#define Set_Item(T)	CONCAT(Set_Item_,	T)
#define Set_Create(T)	CONCAT(Set_Create_,	T)
#define Set_Duplicate(T)	CONCAT(Set_Duplicate_,	T)
#define Set_Free(T)	CONCAT(Set_Free_,	T)
#define Set_Free_F(T)	CONCAT(Set_Free_F_,	T)
#define Set_Delete(T)	CONCAT(Set_Delete_,	T)
#define Set_Delete_F(T)	CONCAT(Set_Delete_F_,	T)
#define Set_Length(T)	CONCAT(Set_Length_,	T)
#define Set_Contains(T)	CONCAT(Set_Contains_,	T)
#define Set_Find(T)	CONCAT(Set_Find_,	T)
#define Set_Find_F(T)	CONCAT(Set_Find_F_,	T)
#define Set_Add(T)	CONCAT(Set_Add_,	T)
#define Set_Remove(T)	CONCAT(Set_Remove_,	T)
#define Set_Remove_F(T)	CONCAT(Set_Remove_F_,	T)
#define Set_Equals(T)	CONCAT(Set_Equals_,	T)
#define Set_IsSubset(T)	CONCAT(Set_IsSubset_,	T)
#define Set_IsDisjoint(T)	CONCAT(Set_IsDisjoint_,	T)
#define Set_Union(T)	CONCAT(Set_Union_,	T)
#define Set_Intersect(T)	CONCAT(Set_Intersect_,	T)
#define Set_Difference(T)	CONCAT(Set_Difference_,	T)
#define Set_Iterate(T)	CONCAT(Set_Iterate_,	T)
#define Set_Iterate_I(T)	CONCAT(Set_Iterate_I_,	T)
#define Set_Map(T)	CONCAT(Set_Map_,	T)
#define Set_Filter(T)	CONCAT(Set_Filter_,	T)
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
