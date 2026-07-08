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
#undef Array_ToList
#undef Array_ToSet
#undef List_ToArray
#undef List_ToSet
#undef Set_ToArray
#undef Set_ToList
#undef Dict_ToArray
#undef Dict_ToArray_Keys
#undef Dict_ToArray_Values
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define Array_ToList(X)	CONCAT(Array_ToList_,	X##_NAME)
#define Array_ToSet(X)	CONCAT(Array_ToSet_,	X##_NAME)
#define List_ToArray(X)	CONCAT(List_ToArray_,	X##_NAME)
#define List_ToSet(X)	CONCAT(List_ToSet_,	X##_NAME)
#define Set_ToArray(X)	CONCAT(Set_ToArray_,	X##_NAME)
#define Set_ToList(X)	CONCAT(Set_ToList_,	X##_NAME)
#define Dict_ToArray(X)	CONCAT(Dict_ToArray_,	X##_NAME)
#define Dict_ToArray_Keys(X)	CONCAT(Dict_ToArray_Keys_,	X##_NAME)
#define Dict_ToArray_Values(X)	CONCAT(Dict_ToArray_Values_,	X##_NAME)
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
#undef __LIBCCC_GENERIC_CONVERT_H
#include "libccc/generic/convert.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
#include "libccc/../.././src/generic/convert/array.c"
#include "libccc/../.././src/generic/convert/dict.c"
#include "libccc/../.././src/generic/convert/list.c"
#include "libccc/../.././src/generic/convert/set.c"
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
#undef Array_ToList
#undef Array_ToSet
#undef List_ToArray
#undef List_ToSet
#undef Set_ToArray
#undef Set_ToList
#undef Dict_ToArray
#undef Dict_ToArray_Keys
#undef Dict_ToArray_Values
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define Array_ToList(T)	CONCAT(Array_ToList_,	T)
#define Array_ToSet(T)	CONCAT(Array_ToSet_,	T)
#define List_ToArray(T)	CONCAT(List_ToArray_,	T)
#define List_ToSet(T)	CONCAT(List_ToSet_,	T)
#define Set_ToArray(T)	CONCAT(Set_ToArray_,	T)
#define Set_ToList(T)	CONCAT(Set_ToList_,	T)
#define Dict_ToArray(T)	CONCAT(Dict_ToArray_,	T)
#define Dict_ToArray_Keys(T)	CONCAT(Dict_ToArray_Keys_,	T)
#define Dict_ToArray_Values(T)	CONCAT(Dict_ToArray_Values_,	T)
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
