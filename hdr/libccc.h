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

//! @defgroup libccc					00) libccc
//! @defgroup libccc_bool				01) libccc/bool
//! @defgroup libccc_int				02) libccc/int
//! @defgroup libccc_fixed				03) libccc/fixed
//! @defgroup libccc_float				04) libccc/float
//! @defgroup libccc_pointer			05) libccc/pointer
//! @defgroup libccc_memory				06) libccc/memory
//! @defgroup libccc_char				07) libccc/char
//! @defgroup libccc_string				08) libccc/string
//! @defgroup libccc_format				09) libccc/format
//! @defgroup libccc_regex				10) libccc/regex
//! @defgroup libccc_color				11) libccc/color
//! @defgroup libccc_sys_io				12) libccc/sys/io
//! @defgroup libccc_sys_time			13) libccc/sys/time
//! @defgroup libccc_sys_logger			14) libccc/sys/logger
//! @defgroup libccc_math_math			15) libccc/math/math
//! @defgroup libccc_math_vlq			16) libccc/math/vlq
//! @defgroup libccc_math_stat			17) libccc/math/stat
//! @defgroup libccc_math_random		18) libccc/math/random
//! @defgroup libccc_math_algebra		19) libccc/math/algebra
//! @defgroup libccc_math_complex		20) libccc/math/complex
//! @defgroup libccc_array_array		21) libccc/array/array
//! @defgroup libccc_array_list			22) libccc/array/list
//! @defgroup libccc_array_dict			23) libccc/array/dict
//! @defgroup libccc_array_tree			24) libccc/array/tree
//! @defgroup libccc_array_pointerarray	25) libccc/array/pointerarray
//! @defgroup libccc_array_stringarray	26) libccc/array/stringarray

#ifndef __LIBCCC_H
#define __LIBCCC_H
/*! @file libccc.h
**	@addtogroup libccc
**	@{
**	This file is simply meant to include all the primitive types together.
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

/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

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
**		`\b([tseuf]_\w+)\b`
*/



/*! @} */
HEADER_END
#endif
