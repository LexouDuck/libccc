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
//! @defgroup libccc_config					02) libccc_config
//! @defgroup libccc_naming					03) libccc_naming
//! @defgroup libccc_errors					04) libccc_errors
//! @defgroup libccc_define					05) libccc_define
//! @defgroup libccc_bool					06) libccc/bool
//! @defgroup libccc_int					07) libccc/int
//! @defgroup libccc_fixed					08) libccc/fixed
//! @defgroup libccc_float					09) libccc/float
//! @defgroup libccc_pointer				10) libccc/pointer
//! @defgroup libccc_pointerarray			11) libccc/pointerarray
//! @defgroup libccc_memory					12) libccc/memory
//! @defgroup libccc_char					13) libccc/char
//! @defgroup libccc_string					14) libccc/string
//! @defgroup libccc_stringarray			15) libccc/stringarray
//! @defgroup libccc_format					16) libccc/format
//! @defgroup libccc_color					17) libccc/color
//! @defgroup libccc_sys_io					18) libccc/sys/io
//! @defgroup libccc_sys_ansi				19) libccc/sys/ansi
//! @defgroup libccc_sys_ascii				20) libccc/sys/ascii
//! @defgroup libccc_sys_unicode			21) libccc/sys/unicode
//! @defgroup libccc_sys_logger				22) libccc/sys/logger
//! @defgroup libccc_sys_regex				23) libccc/sys/regex
//! @defgroup libccc_sys_time				24) libccc/sys/time
//! @defgroup libccc_math_constants			25) libccc/math/constants
//! @defgroup libccc_math_float				26) libccc/math/float
//! @defgroup libccc_math_fixed				27) libccc/math/fixed
//! @defgroup libccc_math_vlq				28) libccc/math/vlq
//! @defgroup libccc_math_sort				29) libccc/math/sort
//! @defgroup libccc_math_stat				30) libccc/math/stat
//! @defgroup libccc_math_random			31) libccc/math/random
//! @defgroup libccc_math_complex			32) libccc/math/complex
//! @defgroup libccc_math_algebra			33) libccc/math/algebra
//! @defgroup libccc_math_algebra_vector	34) libccc/math/algebra/vector
//! @defgroup libccc_math_algebra_matrix	35) libccc/math/algebra/matrix
//! @defgroup libccc_math_algebra_interval	36) libccc/math/algebra/interval
//! @defgroup libccc_monad_convert			37) libccc/monad/convert
//! @defgroup libccc_monad_array			38) libccc/monad/array
//! @defgroup libccc_monad_list				39) libccc/monad/list
//! @defgroup libccc_monad_stack			40) libccc/monad/stack
//! @defgroup libccc_monad_queue			41) libccc/monad/queue
//! @defgroup libccc_monad_tree				42) libccc/monad/tree
//! @defgroup libccc_monad_keyval			43) libccc/monad/keyval
//! @defgroup libccc_monad_dict				44) libccc/monad/dict
//! @defgroup libccc_monad_object			45) libccc/monad/object
//! @defgroup libccc_encode_json			46) libccc/encode/json
//! @defgroup libccc_encode_toml			47) libccc/encode/toml

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

/*! @} */
HEADER_END
#endif
