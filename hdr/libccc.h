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

//! @defgroup libccc						00) libccc
//! @defgroup libccc_bool					01) libccc/bool
//! @defgroup libccc_int					02) libccc/int
//! @defgroup libccc_fixed					03) libccc/fixed
//! @defgroup libccc_float					04) libccc/float
//! @defgroup libccc_pointer				05) libccc/pointer
//! @defgroup libccc_pointerarray			06) libccc/pointerarray
//! @defgroup libccc_memory					07) libccc/memory
//! @defgroup libccc_char					08) libccc/char
//! @defgroup libccc_string					09) libccc/string
//! @defgroup libccc_stringarray			10) libccc/stringarray
//! @defgroup libccc_format					11) libccc/format
//! @defgroup libccc_color					12) libccc/color
//! @defgroup libccc_sys_io					13) libccc/sys/io
//! @defgroup libccc_sys_time				14) libccc/sys/time
//! @defgroup libccc_sys_logger				15) libccc/sys/logger
//! @defgroup libccc_sys_regex				16) libccc/sys/regex
//! @defgroup libccc_math_constants			27) libccc/math/constants
//! @defgroup libccc_math_float				18) libccc/math/float
//! @defgroup libccc_math_fixed				19) libccc/math/fixed
//! @defgroup libccc_math_vlq				20) libccc/math/vlq
//! @defgroup libccc_math_stat				21) libccc/math/stat
//! @defgroup libccc_math_random			22) libccc/math/random
//! @defgroup libccc_math_complex			23) libccc/math/complex
//! @defgroup libccc_math_algebra			24) libccc/math/algebra
//! @defgroup libccc_math_algebra_vector	25) libccc/math/algebra/vector
//! @defgroup libccc_math_algebra_matrix	26) libccc/math/algebra/matrix
//! @defgroup libccc_math_algebra_interval	27) libccc/math/algebra/interval
//! @defgroup libccc_monad_array			28) libccc/monad/array
//! @defgroup libccc_monad_list				29) libccc/monad/list
//! @defgroup libccc_monad_stack			30) libccc/monad/stack
//! @defgroup libccc_monad_queue			31) libccc/monad/queue
//! @defgroup libccc_monad_tree				32) libccc/monad/tree
//! @defgroup libccc_monad_keyval			33) libccc/monad/keyval
//! @defgroup libccc_monad_dict				34) libccc/monad/dict
//! @defgroup libccc_monad_object			35) libccc/monad/object
//! @defgroup libccc_encode_json			36) libccc/encode/json

#ifndef __LIBCCC_H
#define __LIBCCC_H
/*! @file libccc.h
**	@addtogroup libccc
**	@{
**	This file is simply meant to include all the primitive types together.
*/

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
//#include "libccc/char.h"
//#include "libccc/string.h"
//#include "libccc/memory.h"

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
