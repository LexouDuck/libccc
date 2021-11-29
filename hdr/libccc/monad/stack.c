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
#undef stack
#undef s_stack
//!@}

//! Set the generic macros to allow for declarations, written as `mygeneric(T)`
//!@{
#define stack(X)	CONCAT(stack_,	X##_NAME)
#define s_stack(X)	CONCAT(s_stack_,	X##_NAME)
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
#undef __LIBCCC_MONAD_STACK_H
#include "./hdr/libccc/monad/stack.h"
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
#undef stack
#undef s_stack
//!@}

//! Finally, redefine all generic macros, for user code
//!@{
#define stack(T)	CONCAT(stack_,	T)
#define s_stack(T)	CONCAT(s_stack_,	T)
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
