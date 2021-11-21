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
**	@addtogroup libccc
**	@{
**	This file is simply meant to include all the primitive types together.
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

/*
**	Here we include all the primitive type headers, but we define some important
**	header macros beforehand, so as to define only the types, not any of the functions
*/

//#define __LIBCCC_NOFUNCTIONS__

#define	__LIBCCC_CHAR_F
#define	__LIBCCC_TEXT_ASCII_F
#define	__LIBCCC_TEXT_UNICODE_F
#define	__LIBCCC_BOOL_F
#define	__LIBCCC_INT_F
#define	__LIBCCC_FIXED_F
#define	__LIBCCC_FLOAT_F
#define	__LIBCCC_POINTER_F

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

HEADER_CPP

/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

//! @defgroup libccc                       01) libccc.h
//! @defgroup libccc_config                02) libccc_config.h
//! @defgroup libccc_naming                03) libccc_naming.h
//! @defgroup libccc_errors                04) libccc_errors.h
//! @defgroup libccc_define                05) libccc_define.h
//! @defgroup libccc_bool                  06) libccc/bool.h
//! @defgroup libccc_int                   07) libccc/int.h
//! @defgroup libccc_fixed                 08) libccc/fixed.h
//! @defgroup libccc_float                 09) libccc/float.h
//! @defgroup libccc_pointer               10) libccc/pointer.h
//! @defgroup libccc_pointerarray          11) libccc/pointerarray.h
//! @defgroup libccc_memory                12) libccc/memory.h
//! @defgroup libccc_char                  13) libccc/char.h
//! @defgroup libccc_string                14) libccc/string.h
//! @defgroup libccc_stringarray           15) libccc/stringarray.h
//! @defgroup libccc_format                16) libccc/format.h
//! @defgroup libccc_color                 17) libccc/color.h
//! @defgroup libccc_error                 18) libccc/error.h
//! @defgroup libccc_sys_io                19) libccc/sys/io.h
//! @defgroup libccc_sys_ansi              20) libccc/sys/ansi.h
//! @defgroup libccc_sys_ascii             21) libccc/sys/ascii.h
//! @defgroup libccc_sys_unicode           22) libccc/sys/unicode.h
//! @defgroup libccc_sys_logger            23) libccc/sys/logger.h
//! @defgroup libccc_sys_regex             24) libccc/sys/regex.h
//! @defgroup libccc_sys_time              25) libccc/sys/time.h
//! @defgroup libccc_math_constants        26) libccc/math/constants.h
//! @defgroup libccc_math_math             27) libccc/math/math.h
//! @defgroup libccc_math_float            28) libccc/math/float.h
//! @defgroup libccc_math_fixed            29) libccc/math/fixed.h
//! @defgroup libccc_math_vlq              30) libccc/math/vlq.h
//! @defgroup libccc_math_sort             31) libccc/math/sort.h
//! @defgroup libccc_math_stat             32) libccc/math/stat.h
//! @defgroup libccc_math_complex          33) libccc/math/complex.h
//! @defgroup libccc_math_algebra          34) libccc/math/algebra.h
//! @defgroup libccc_math_algebra_vector   35) libccc/math/algebra/vector.h
//! @defgroup libccc_math_algebra_matrix   36) libccc/math/algebra/matrix.h
//! @defgroup libccc_math_algebra_interval 37) libccc/math/algebra/interval.h
//! @defgroup libccc_random_random         38) libccc/random/random.h
//! @defgroup libccc_random_prng           39) libccc/random/prng.h
//! @defgroup libccc_random_csprng         40) libccc/random/csprng.h
//! @defgroup libccc_monad_convert         41) libccc/monad/convert.h
//! @defgroup libccc_monad_stack           42) libccc/monad/stack.h
//! @defgroup libccc_monad_queue           43) libccc/monad/queue.h
//! @defgroup libccc_monad_array           44) libccc/monad/array.h
//! @defgroup libccc_monad_list            45) libccc/monad/list.h
//! @defgroup libccc_monad_hash            46) libccc/monad/hash.h
//! @defgroup libccc_monad_keyval          47) libccc/monad/keyval.h
//! @defgroup libccc_monad_dict            48) libccc/monad/dict.h
//! @defgroup libccc_monad_tree            49) libccc/monad/tree.h
//! @defgroup libccc_monad_object          50) libccc/monad/object.h
//! @defgroup libccc_encode_common         51) libccc/encode/common.h
//! @defgroup libccc_encode_json           52) libccc/encode/json.h
//! @defgroup libccc_encode_toml           53) libccc/encode/toml.h



/*! @} */
HEADER_END
#endif
