/*============================================================================*/
/*                                            ______________________________  */
/*  libccc.h                                 |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_H
#define __LIBCCC_H
/*! @file libccc.h
**	This file is simply meant to include all the primitive types together.
**	@addtogroup libccc
**	@{
*/

// define 'extern C' header guards to prevent C++ compilers from doing symbol name mangling
#ifdef __cplusplus
	#ifndef HEADER_CPP
	#define HEADER_CPP	extern "C" {
	#endif
	#ifndef HEADER_END
	#define HEADER_END	}
	#endif
#else
	#ifndef HEADER_CPP
	#define HEADER_CPP	
	#endif
	#ifndef HEADER_END
	#define HEADER_END	
	#endif
#endif

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/pointer.h"
//#include "libccc/memory.h"
//#include "libccc/string.h"

HEADER_CPP

/*! @file libccc.h
**	The naming convention for types is to always use a prefix to show its kind.
**	These prefixes are always one letter followed by an underscore character.
**	There are five such type prefix that libccc uses:
**		- `t_` for a typedef on a primitive type	ex: `typedef t_u32 t_color; t_color a = 0;`
**		- `s_` for a typedef on a struct			ex: `s_point pos = { .x = 0, .y = 0 };`
**		- `e_` for a typedef on an enum				ex: `e_httperror code = ERROR_HTTP_404;`
**		- `u_` for a typedef on a union type		ex: `typedef union color { t_u8 channels[4]; t_u32 argb; } u_color;`
**		- `f_` for a typedef on a function pointer	ex: `typedef char (*f_strmapi)(char c, t_size index);`
**	This also allows most any text editor's syntax coloring to be able to match types with a simple regex rule:
**	\b([tseuf]_\w+)\b
*/

/*! @} */
HEADER_END
#endif
