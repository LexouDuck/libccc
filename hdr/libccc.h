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
**	- `libccc/text/char_ascii.h`
**	- `libccc/text/char_unicode.h`
**	
**	Note that none of the functions from these headers are included/exposed.
**	If you wish to use the utility functions from a header, you must manually include it:
**	for instance, you must `#include <libccc/int.h>` to use, say, `UInt_ToString()`.
*/

/*============================================================================*\
||                                 Includes                                   ||
\*============================================================================*/

#include "libccc_define.h"
#include "libccc_errors.h"
#include "libccc_config.h"
#include "libccc_naming.h"

HEADER_CPP

// This include fixes a problem where <math.h> ends up being included after <libccc/float.h>
#ifndef __MSVC__
#ifndef __NOSTD__
#ifndef __EMSCRIPTEN__
#if LIBCONFIG_USE_STD_MATH
#include <math.h>
#endif
#endif
#endif
#endif

#ifndef __DOXYGEN__

/*!@doc
**	Here we include all the primitive type headers, but we preemptively define some
**	important header macros beforehand, so as to have the header define only the types,
**	and not any of their functions. As such, `libccc.h` only includes important builtins.
*/
//!@{
#define	__LIBCCC_BOOL_F
#define	__LIBCCC_CHAR_F
#define	__LIBCCC_CHAR_ASCII_F
#define	__LIBCCC_CHAR_UNICODE_F
#define	__LIBCCC_INT_F
#define	__LIBCCC_FIXED_F
#define	__LIBCCC_FLOAT_F
#define	__LIBCCC_POINTER_F
//!@}

#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/pointer.h"

#undef	__LIBCCC_BOOL_H
#undef	__LIBCCC_BOOL_F
#undef	__LIBCCC_CHAR_H
#undef	__LIBCCC_CHAR_F
#undef	__LIBCCC_CHAR_ASCII_H
#undef	__LIBCCC_CHAR_ASCII_F
#undef	__LIBCCC_CHAR_UNICODE_H
#undef	__LIBCCC_CHAR_UNICODE_F
#undef	__LIBCCC_INT_H
#undef	__LIBCCC_INT_F
#undef	__LIBCCC_FIXED_H
#undef	__LIBCCC_FIXED_F
#undef	__LIBCCC_FLOAT_H
#undef	__LIBCCC_FLOAT_F
#undef	__LIBCCC_POINTER_H
#undef	__LIBCCC_POINTER_F

//#include "libccc/sys/error.h"
//#include "libccc/memory.h"
//#include "libccc/string.h"

#endif

/*! @endgroup */
HEADER_END
#endif
