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

//! @defgroup libccc						01) libccc
//! @defgroup libccc_bool					02) libccc/bool
//! @defgroup libccc_int					03) libccc/int
//! @defgroup libccc_fixed					04) libccc/fixed
//! @defgroup libccc_float					05) libccc/float
//! @defgroup libccc_pointer				06) libccc/pointer
//! @defgroup libccc_pointerarray			07) libccc/pointerarray
//! @defgroup libccc_memory					08) libccc/memory
//! @defgroup libccc_char					09) libccc/char
//! @defgroup libccc_string					10) libccc/string
//! @defgroup libccc_stringarray			11) libccc/stringarray
//! @defgroup libccc_format					12) libccc/format
//! @defgroup libccc_color					13) libccc/color
//! @defgroup libccc_sys_io					14) libccc/sys/io
//! @defgroup libccc_sys_ansi				15) libccc/sys/ansi
//! @defgroup libccc_sys_ascii				16) libccc/sys/ascii
//! @defgroup libccc_sys_unicode			17) libccc/sys/unicode
//! @defgroup libccc_sys_logger				18) libccc/sys/logger
//! @defgroup libccc_sys_regex				19) libccc/sys/regex
//! @defgroup libccc_sys_time				20) libccc/sys/time
//! @defgroup libccc_math_constants			21) libccc/math/constants
//! @defgroup libccc_math_float				22) libccc/math/float
//! @defgroup libccc_math_fixed				23) libccc/math/fixed
//! @defgroup libccc_math_vlq				24) libccc/math/vlq
//! @defgroup libccc_math_stat				25) libccc/math/stat
//! @defgroup libccc_math_random			26) libccc/math/random
//! @defgroup libccc_math_complex			27) libccc/math/complex
//! @defgroup libccc_math_algebra			28) libccc/math/algebra
//! @defgroup libccc_math_algebra_vector	29) libccc/math/algebra/vector
//! @defgroup libccc_math_algebra_matrix	30) libccc/math/algebra/matrix
//! @defgroup libccc_math_algebra_interval	31) libccc/math/algebra/interval
//! @defgroup libccc_monad_array			32) libccc/monad/array
//! @defgroup libccc_monad_list				33) libccc/monad/list
//! @defgroup libccc_monad_stack			34) libccc/monad/stack
//! @defgroup libccc_monad_queue			35) libccc/monad/queue
//! @defgroup libccc_monad_tree				36) libccc/monad/tree
//! @defgroup libccc_monad_keyval			37) libccc/monad/keyval
//! @defgroup libccc_monad_dict				38) libccc/monad/dict
//! @defgroup libccc_monad_object			39) libccc/monad/object
//! @defgroup libccc_encode_json			40) libccc/encode/json
//! @defgroup libccc_encode_toml			41) libccc/encode/toml

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

#include "libccc/char.h"
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/pointer.h"
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
