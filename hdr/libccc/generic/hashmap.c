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
#undef hashitem
#undef s_hashitem
#undef hashmap
#undef s_hashmap
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define hashitem(X)	CONCAT(hashitem_,	X##_NAME)
#define s_hashitem(X)	CONCAT(s_hashitem_,	X##_NAME)
#define hashmap(X)	CONCAT(hashmap_,	X##_NAME)
#define s_hashmap(X)	CONCAT(s_hashmap_,	X##_NAME)
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
#undef __LIBCCC_GENERIC_HASHMAP_H
#include "libccc/generic/hashmap.h"
//!@}

//! Include all source files, to generate code for all generic functions
//!@{
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
#undef hashitem
#undef s_hashitem
#undef hashmap
#undef s_hashmap
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define hashitem(T)	CONCAT(hashitem_,	T)
#define s_hashitem(T)	CONCAT(s_hashitem_,	T)
#define hashmap(T)	CONCAT(hashmap_,	T)
#define s_hashmap(T)	CONCAT(s_hashmap_,	T)
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
