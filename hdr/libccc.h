/*============================================================================*\
||                                            ______________________________  ||
||  libccc.h                                 |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_H
#define __LIBCCC_H
/*!@group{libccc,1,libccc.h}
**
**	This file is simply meant to include all of the basic primitive types.
**	
**	To be precise, this file exposes the type definitions and macros from:
**	- `libccc/bool.h`
**	- `libccc/int.h`
**	- `libccc/fixed.h`
**	- `libccc/float.h`
**	- `libccc/pointer.h`
**	- `libccc/char.h`
**	- `libccc/text/ascii.h`
**	- `libccc/text/unicode.h`
**	
**	Note that none of the functions from these headers are included/exposed.
**	If you wish to use the utility functions from a header, you must manually include it:
**	for instance, you must `#include <libccc/int.h>` to use, say, `UInt_ToString()`.
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc_define.h"
#include "libccc_errors.h"
#include "libccc_config.h"
#include "libccc_naming.h"

HEADER_CPP

#ifndef __DOXYGEN__

/*!@doc
**	Here we include all the primitive type headers, but we preemptively define some
**	important header macros beforehand, so as to have the header define only the types,
**	and not any of their functions. As such, `libccc.h` only includes important builtins.
*/
//!@{
#define	__LIBCCC_CHAR_F
#define	__LIBCCC_TEXT_ASCII_F
#define	__LIBCCC_TEXT_UNICODE_F
#define	__LIBCCC_BOOL_F
#define	__LIBCCC_INT_F
#define	__LIBCCC_FIXED_F
#define	__LIBCCC_FLOAT_F
#define	__LIBCCC_POINTER_F
//!@}

#ifndef __LIBCCC_BOOL_H
#include "libccc/bool.h"
#endif
#ifndef __LIBCCC_CHAR_H
#include "libccc/char.h"
#endif
#ifndef __LIBCCC_INT_H
#include "libccc/int.h"
#endif
#ifndef __LIBCCC_FIXED_H
#include "libccc/fixed.h"
#endif
#ifndef __LIBCCC_FLOAT_H
#include "libccc/float.h"
#endif
#ifndef __LIBCCC_POINTER_H
#include "libccc/pointer.h"
#endif

#undef	__LIBCCC_CHAR_H
#undef	__LIBCCC_CHAR_F
#undef	__LIBCCC_TEXT_ASCII_H
#undef	__LIBCCC_TEXT_ASCII_F
#undef	__LIBCCC_TEXT_UNICODE_H
#undef	__LIBCCC_TEXT_UNICODE_F
#undef	__LIBCCC_BOOL_H
#undef	__LIBCCC_BOOL_F
#undef	__LIBCCC_INT_H
#undef	__LIBCCC_INT_F
#undef	__LIBCCC_FIXED_H
#undef	__LIBCCC_FIXED_F
#undef	__LIBCCC_FLOAT_H
#undef	__LIBCCC_FLOAT_F
#undef	__LIBCCC_POINTER_H
#undef	__LIBCCC_POINTER_F

//#include "libccc/error.h"
//#include "libccc/memory.h"
//#include "libccc/string.h"

#endif

/*! @endgroup */
HEADER_END
#endif
