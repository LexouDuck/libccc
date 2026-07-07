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
#undef keyval
#undef s_keyval
#undef dict
#undef s_dict
#undef Dict_HashKey
#undef KeyVal
#undef KeyVal_Free
#undef Dict_New
#undef Dict_Create
#undef Dict_Duplicate
#undef Dict_Free
#undef Dict_Free_F
#undef Dict_Delete
#undef Dict_Delete_F
#undef Dict_Get
#undef Dict_Set
#undef Dict_Add
#undef Dict_Remove
#undef Dict_Remove_F
#undef Dict_RemoveMatch
#undef Dict_RemoveMatch_F
#undef Dict_RemoveMatches
#undef Dict_RemoveMatches_F
#undef Dict_Sub
#undef Dict_Find
#undef Dict_Find_F
#undef Dict_HasKey
#undef Dict_KeyOf
#undef Dict_Count
#undef Dict_Contains
#undef Dict_Has
#undef Dict_HasOnly
#undef Dict_Equals
#undef Dict_Iterate
#undef Dict_Iterate_I
#undef Dict_Map
#undef Dict_Filter
#undef Dict_Reduce
#undef Dict_Fold
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define keyval(X)	CONCAT(keyval_,	X##_NAME)
#define s_keyval(X)	CONCAT(s_keyval_,	X##_NAME)
#define dict(X)	CONCAT(dict_,	X##_NAME)
#define s_dict(X)	CONCAT(s_dict_,	X##_NAME)
#define Dict_HashKey(X)	CONCAT(Dict_HashKey_,	X##_NAME)
#define KeyVal(X)	CONCAT(KeyVal_,	X##_NAME)
#define KeyVal_Free(X)	CONCAT(KeyVal_Free_,	X##_NAME)
#define Dict_New(X)	CONCAT(Dict_New_,	X##_NAME)
#define Dict_Create(X)	CONCAT(Dict_Create_,	X##_NAME)
#define Dict_Duplicate(X)	CONCAT(Dict_Duplicate_,	X##_NAME)
#define Dict_Free(X)	CONCAT(Dict_Free_,	X##_NAME)
#define Dict_Free_F(X)	CONCAT(Dict_Free_F_,	X##_NAME)
#define Dict_Delete(X)	CONCAT(Dict_Delete_,	X##_NAME)
#define Dict_Delete_F(X)	CONCAT(Dict_Delete_F_,	X##_NAME)
#define Dict_Get(X)	CONCAT(Dict_Get_,	X##_NAME)
#define Dict_Set(X)	CONCAT(Dict_Set_,	X##_NAME)
#define Dict_Add(X)	CONCAT(Dict_Add_,	X##_NAME)
#define Dict_Remove(X)	CONCAT(Dict_Remove_,	X##_NAME)
#define Dict_Remove_F(X)	CONCAT(Dict_Remove_F_,	X##_NAME)
#define Dict_RemoveMatch(X)	CONCAT(Dict_RemoveMatch_,	X##_NAME)
#define Dict_RemoveMatch_F(X)	CONCAT(Dict_RemoveMatch_F_,	X##_NAME)
#define Dict_RemoveMatches(X)	CONCAT(Dict_RemoveMatches_,	X##_NAME)
#define Dict_RemoveMatches_F(X)	CONCAT(Dict_RemoveMatches_F_,	X##_NAME)
#define Dict_Sub(X)	CONCAT(Dict_Sub_,	X##_NAME)
#define Dict_Find(X)	CONCAT(Dict_Find_,	X##_NAME)
#define Dict_Find_F(X)	CONCAT(Dict_Find_F_,	X##_NAME)
#define Dict_HasKey(X)	CONCAT(Dict_HasKey_,	X##_NAME)
#define Dict_KeyOf(X)	CONCAT(Dict_KeyOf_,	X##_NAME)
#define Dict_Count(X)	CONCAT(Dict_Count_,	X##_NAME)
#define Dict_Contains(X)	CONCAT(Dict_Contains_,	X##_NAME)
#define Dict_Has(X)	CONCAT(Dict_Has_,	X##_NAME)
#define Dict_HasOnly(X)	CONCAT(Dict_HasOnly_,	X##_NAME)
#define Dict_Equals(X)	CONCAT(Dict_Equals_,	X##_NAME)
#define Dict_Iterate(X)	CONCAT(Dict_Iterate_,	X##_NAME)
#define Dict_Iterate_I(X)	CONCAT(Dict_Iterate_I_,	X##_NAME)
#define Dict_Map(X)	CONCAT(Dict_Map_,	X##_NAME)
#define Dict_Filter(X)	CONCAT(Dict_Filter_,	X##_NAME)
#define Dict_Reduce(X)	CONCAT(Dict_Reduce_,	X##_NAME)
#define Dict_Fold(X)	CONCAT(Dict_Fold_,	X##_NAME)
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
#undef __LIBCCC_GENERIC_DICT_H
#include "libccc/generic/dict.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../.././src/generic/dict/add.c"
#include "libccc/../.././src/generic/dict/count.c"
#include "libccc/../.././src/generic/dict/create.c"
#include "libccc/../.././src/generic/dict/delete.c"
#include "libccc/../.././src/generic/dict/duplicate.c"
#include "libccc/../.././src/generic/dict/equals.c"
#include "libccc/../.././src/generic/dict/filter.c"
#include "libccc/../.././src/generic/dict/find.c"
#include "libccc/../.././src/generic/dict/get.c"
#include "libccc/../.././src/generic/dict/has.c"
#include "libccc/../.././src/generic/dict/hash.c"
#include "libccc/../.././src/generic/dict/iterate.c"
#include "libccc/../.././src/generic/dict/keyval.c"
#include "libccc/../.././src/generic/dict/map.c"
#include "libccc/../.././src/generic/dict/new.c"
#include "libccc/../.././src/generic/dict/reduce.c"
#include "libccc/../.././src/generic/dict/remove.c"
#include "libccc/../.././src/generic/dict/set.c"
#include "libccc/../.././src/generic/dict/sub.c"
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
#undef keyval
#undef s_keyval
#undef dict
#undef s_dict
#undef Dict_HashKey
#undef KeyVal
#undef KeyVal_Free
#undef Dict_New
#undef Dict_Create
#undef Dict_Duplicate
#undef Dict_Free
#undef Dict_Free_F
#undef Dict_Delete
#undef Dict_Delete_F
#undef Dict_Get
#undef Dict_Set
#undef Dict_Add
#undef Dict_Remove
#undef Dict_Remove_F
#undef Dict_RemoveMatch
#undef Dict_RemoveMatch_F
#undef Dict_RemoveMatches
#undef Dict_RemoveMatches_F
#undef Dict_Sub
#undef Dict_Find
#undef Dict_Find_F
#undef Dict_HasKey
#undef Dict_KeyOf
#undef Dict_Count
#undef Dict_Contains
#undef Dict_Has
#undef Dict_HasOnly
#undef Dict_Equals
#undef Dict_Iterate
#undef Dict_Iterate_I
#undef Dict_Map
#undef Dict_Filter
#undef Dict_Reduce
#undef Dict_Fold
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define keyval(T)	CONCAT(keyval_,	T)
#define s_keyval(T)	CONCAT(s_keyval_,	T)
#define dict(T)	CONCAT(dict_,	T)
#define s_dict(T)	CONCAT(s_dict_,	T)
#define Dict_HashKey(T)	CONCAT(Dict_HashKey_,	T)
#define KeyVal(T)	CONCAT(KeyVal_,	T)
#define KeyVal_Free(T)	CONCAT(KeyVal_Free_,	T)
#define Dict_New(T)	CONCAT(Dict_New_,	T)
#define Dict_Create(T)	CONCAT(Dict_Create_,	T)
#define Dict_Duplicate(T)	CONCAT(Dict_Duplicate_,	T)
#define Dict_Free(T)	CONCAT(Dict_Free_,	T)
#define Dict_Free_F(T)	CONCAT(Dict_Free_F_,	T)
#define Dict_Delete(T)	CONCAT(Dict_Delete_,	T)
#define Dict_Delete_F(T)	CONCAT(Dict_Delete_F_,	T)
#define Dict_Get(T)	CONCAT(Dict_Get_,	T)
#define Dict_Set(T)	CONCAT(Dict_Set_,	T)
#define Dict_Add(T)	CONCAT(Dict_Add_,	T)
#define Dict_Remove(T)	CONCAT(Dict_Remove_,	T)
#define Dict_Remove_F(T)	CONCAT(Dict_Remove_F_,	T)
#define Dict_RemoveMatch(T)	CONCAT(Dict_RemoveMatch_,	T)
#define Dict_RemoveMatch_F(T)	CONCAT(Dict_RemoveMatch_F_,	T)
#define Dict_RemoveMatches(T)	CONCAT(Dict_RemoveMatches_,	T)
#define Dict_RemoveMatches_F(T)	CONCAT(Dict_RemoveMatches_F_,	T)
#define Dict_Sub(T)	CONCAT(Dict_Sub_,	T)
#define Dict_Find(T)	CONCAT(Dict_Find_,	T)
#define Dict_Find_F(T)	CONCAT(Dict_Find_F_,	T)
#define Dict_HasKey(T)	CONCAT(Dict_HasKey_,	T)
#define Dict_KeyOf(T)	CONCAT(Dict_KeyOf_,	T)
#define Dict_Count(T)	CONCAT(Dict_Count_,	T)
#define Dict_Contains(T)	CONCAT(Dict_Contains_,	T)
#define Dict_Has(T)	CONCAT(Dict_Has_,	T)
#define Dict_HasOnly(T)	CONCAT(Dict_HasOnly_,	T)
#define Dict_Equals(T)	CONCAT(Dict_Equals_,	T)
#define Dict_Iterate(T)	CONCAT(Dict_Iterate_,	T)
#define Dict_Iterate_I(T)	CONCAT(Dict_Iterate_I_,	T)
#define Dict_Map(T)	CONCAT(Dict_Map_,	T)
#define Dict_Filter(T)	CONCAT(Dict_Filter_,	T)
#define Dict_Reduce(T)	CONCAT(Dict_Reduce_,	T)
#define Dict_Fold(T)	CONCAT(Dict_Fold_,	T)
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
