/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/format.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_TEXT_FORMAT_H
#define __LIBCCC_TEXT_FORMAT_H
/*!@group{libccc_text_format,10,libccc/text/format.h}
**
**	This header defines printf-style functions, and their format specifiers.
**
**	The cross-platform `"%"` format specifier macros in this header can either
**	be used individually, or you can use the SF() macro function if you wish to
**	have further customization potential for the exact format of the output string.
**
**	NOTE: the "SF" abbreviation used here stands for "String Format".
**
**	@see
**	- String_Format()
**	- String_Format_N()
**	- IO_Write_Format()
**	- IO_Output_Format()
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

//!@doc @isostd{C,https://en.cppreference.com/w/c/variadic}
//!@{
#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
#endif
//!@}

//!@doc @isostd{C99,https://en.cppreference.com/w/c/types/integer}
//!@{
#ifndef __NOSTD__
	#include <inttypes.h>

	#if (defined(__WINDOWS__) && __USE_MINGW_ANSI_STDIO)
		#ifdef __clang__
			#undef	PRIu64
			#define	PRIu64	"lu"
			#undef	PRIi64
			#define	PRIi64	"li"
			#undef	PRIX64
			#define	PRIX64	"lX"
			#undef	PRIo64
			#define	PRIo64	"lo"
		#else
			#undef	PRIu64
			#define	PRIu64	"llu"
			#undef	PRIi64
			#define	PRIi64	"lli"
			#undef	PRIX64
			#define	PRIX64	"llX"
			#undef	PRIo64
			#define	PRIo64	"llo"
		#endif
	#endif

#else
// TODO: better logic than just using 'long' here, with the __DATAMODEL__ macro ?
	#define PRIu8	"hhu"
	#define PRIi8	"hhi"
	#define PRIX8	"hhX"
	#define PRIo8	"hho"
	#define PRIu16	"hu"
	#define PRIi16	"hi"
	#define PRIX16	"hX"
	#define PRIo16	"ho"
	#define PRIu32	"lu"
	#define PRIi32	"li"
	#define PRIX32	"lX"
	#define PRIo32	"lo"
	#define PRIu64	"llu"
	#define PRIi64	"lli"
	#define PRIX64	"llX"
	#define PRIo64	"llo"
#endif
//!@}

#include "libccc.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! This macro is used to make custom "SF_" string format macros
/*!
**	@param TYPE    The type of the string format argument specifier (UPPERCASE)
**	@param PREFIX  The custom configuration prefix (typically, precision/padding specifiers)
**	@returns
**	A concatenated custom format specifier, like so: `"%[PREFIX]"SF_[TYPE]_`
*/
#define SF(TYPE, PREFIX)	"%" PREFIX SF_##TYPE##_



//!@doc String format specifier macros for libccc/bool.h
//!@{
#define SF_t_bool_   SF_BOOL_
#define SF_BOOL  "%" SF_BOOL_
#define SF_BOOL_ "d" // TODO `%B` boolean format specifier
//!@}

//!@doc String format specifier macros for libccc/enum.h
//!@{
#define SF_t_enum_   SF_ENUM_
#define SF_ENUM  "%" SF_ENUM_
#define SF_ENUM_ "d" // TODO fancy type reflection (++C) ?
//!@}

//!@doc String format specifier macros for libccc/char.h
//!@{
#define SF_t_char_      SF_CHAR_
#define SF_CHAR     "%" SF_CHAR_
#define SF_CHAR_    CONCAT(SF_,CONCAT(LIBCONFIG_CHAR_NAME,_))

#define SF_t_ascii_     SF_ASCII_
#define SF_ASCII    "%" SF_ASCII_
#define SF_ASCII_   "c"

#define SF_t_utf8_      SF_UTF8_
#define SF_UTF8     "%" SF_UTF8_
#define SF_UTF8_    "c"

#define SF_t_utf16_     SF_UTF16_
#define SF_UTF16    "%" SF_UTF16_
#define SF_UTF16_   "lc"
#define SF_UTF16_CODE   "\\u%" SF_UTF16_CODE_
#define SF_UTF16_CODE_  "4.4X"

#define SF_t_utf32_     SF_UTF32_
#define SF_UTF32    "%" SF_UTF32_
#define SF_UTF32_   "lc"
#define SF_UTF32_CODE   "\\U%" SF_UTF32_CODE_
#define SF_UTF32_CODE_  "8.8X"
//!@}

//!@doc String format specifier macros for libccc/string.h
//!@{
#define SF_p_string_    SF_STRING_
#define SF_STRING   "%" SF_STRING_
#define SF_STRING_  "s"

#define SF_p_string_ascii_   SF_STRING_ASCII_
#define SF_STRING_ASCII  "%" SF_STRING_ASCII_
#define SF_STRING_ASCII_ "s"

#define SF_p_string_utf8_    SF_STRING_UTF8_
#define SF_STRING_UTF8   "%" SF_STRING_UTF8_
#define SF_STRING_UTF8_  "s"

#define SF_p_string_utf16_   SF_STRING_UTF16_
#define SF_STRING_UTF16  "%" SF_STRING_UTF16_
#define SF_STRING_UTF16_ "ls"

#define SF_p_string_utf32_   SF_STRING_UTF32_
#define SF_STRING_UTF32  "%" SF_STRING_UTF32_
#define SF_STRING_UTF32_ "ls"
//!@}

//!@doc String format specifier macros for libccc/int.h
//!@{
#define SF_UINT      "%" SF_UINT_
#define SF_UINT_     CONCAT(SF_U,CONCAT(LIBCONFIG_UINT_BITS,_))
#define SF_UINT_HEX  "%" SF_UINT_HEX_
#define SF_UINT_HEX_ CONCAT(SF_U,CONCAT(LIBCONFIG_UINT_BITS,_HEX_))
#define SF_UINT_OCT  "%" SF_UINT_OCT_
#define SF_UINT_OCT_ CONCAT(SF_U,CONCAT(LIBCONFIG_UINT_BITS,_OCT_))
#define SF_SINT      "%" SF_SINT_
#define SF_SINT_     CONCAT(SF_S,CONCAT(LIBCONFIG_SINT_BITS,_))
#define SF_SINT_HEX  "%" SF_SINT_HEX_
#define SF_SINT_HEX_ CONCAT(SF_S,CONCAT(LIBCONFIG_SINT_BITS,_HEX_))
#define SF_SINT_OCT  "%" SF_SINT_OCT_
#define SF_SINT_OCT_ CONCAT(SF_S,CONCAT(LIBCONFIG_SINT_BITS,_OCT_))

#define SF_t_u8_        SF_U8_
#define SF_U8       "%" SF_U8_
#define SF_U8_      PRIu8
#define SF_U8_HEX   "0x%" SF_U8_HEX_
#define SF_U8_HEX_  PRIX8
#define SF_U8_OCT   "0o%" SF_U8_OCT_
#define SF_U8_OCT_  PRIo8
#define SF_t_s8_        SF_S8_
#define SF_S8       "%" SF_S8_
#define SF_S8_      PRIi8
#define SF_S8_HEX   "0x%" SF_S8_HEX_
#define SF_S8_HEX_  PRIX8
#define SF_S8_OCT   "0o%" SF_S8_OCT_
#define SF_S8_OCT_  PRIo8

#define SF_t_u16_       SF_U16_
#define SF_U16      "%" SF_U16_
#define SF_U16_     PRIu16
#define SF_U16_HEX  "0x%" SF_U16_HEX_
#define SF_U16_HEX_ PRIX16
#define SF_U16_OCT  "0o%" SF_U16_OCT_
#define SF_U16_OCT_ PRIo16
#define SF_t_s16_       SF_S16_
#define SF_S16      "%" SF_S16_
#define SF_S16_     PRIi16
#define SF_S16_HEX  "0x%" SF_S16_HEX_
#define SF_S16_HEX_ PRIX16
#define SF_S16_OCT  "0o%" SF_S16_OCT_
#define SF_S16_OCT_ PRIo16

#define SF_t_u32_       SF_U32_
#define SF_U32      "%" SF_U32_
#define SF_U32_     PRIu32
#define SF_U32_HEX  "0x%" SF_U32_HEX_
#define SF_U32_HEX_ PRIX32
#define SF_U32_OCT  "0o%" SF_U32_OCT_
#define SF_U32_OCT_ PRIo32
#define SF_t_s32_       SF_S32_
#define SF_S32      "%" SF_S32_
#define SF_S32_     PRIi32
#define SF_S32_HEX  "0x%" SF_S32_HEX_
#define SF_S32_HEX_ PRIX32
#define SF_S32_OCT  "0o%" SF_S32_OCT_
#define SF_S32_OCT_ PRIo32

#define SF_t_u64_        SF_U64_
#define SF_U64       "%" SF_U64_
#define SF_U64_      PRIu64
#define SF_U64_HEX   "0x%" SF_U64_HEX_
#define SF_U64_HEX_  PRIX64
#define SF_U64_OCT   "0o%" SF_U64_OCT_
#define SF_U64_OCT_  PRIo64
#define SF_t_s64_        SF_S64_
#define SF_S64       "%" SF_S64_
#define SF_S64_      PRIi64
#define SF_S64_HEX   "0x%" SF_S64_HEX_
#define SF_S64_HEX_  PRIX64
#define SF_S64_OCT   "0o%" SF_S64_OCT_
#define SF_S64_OCT_  PRIo64

#define SF_t_u128_       SF_U128_
#define SF_U128      "%" SF_U128_
#define SF_U128_     PRIu128 //TODO
#define SF_U128_HEX  "0x%" SF_U128_HEX_
#define SF_U128_HEX_ PRIX128 //TODO
#define SF_U128_OCT  "0o%" SF_U128_OCT_
#define SF_U128_OCT_ PRIo128 //TODO
#define SF_t_s128_       SF_S128_
#define SF_S128      "%" SF_S128_
#define SF_S128_     PRIi128 //TODO
#define SF_S128_HEX  "0x%" SF_S128_HEX_
#define SF_S128_HEX_ PRIX128 //TODO
#define SF_S128_OCT  "0o%" SF_S128_OCT_
#define SF_S128_OCT_ PRIo128 //TODO

#ifndef PRIu128
#define PRIu128	"LLu"
#endif
#ifndef PRIX128
#define PRIX128	"LLX"
#endif
#ifndef PRIo128
#define PRIo128	"LLo"
#endif
#ifndef PRIi128
#define PRIi128	"LLi"
#endif
#ifndef PRIX128
#define PRIX128	"LLX"
#endif
#ifndef PRIo128
#define PRIo128	"LLo"
#endif
//!@}

//!@doc String format specifier macros for libccc/fixed.h
//!@{
#define SF_t_fixed_       SF_FIXED_
#define SF_FIXED      "%" SF_FIXED_
#define SF_FIXED_     CONCAT(SF_Q,CONCAT(LIBCONFIG_FIXED_BITS,_))
#define SF_FIXED_HEX  "%" SF_FIXED_HEX_
#define SF_FIXED_HEX_ CONCAT(SF_Q,CONCAT(LIBCONFIG_FIXED_BITS,_HEX_))

#define SF_t_q8_          SF_Q8_
#define SF_Q8         "%" SF_Q8_ "/" STRING(Q8_DENOM)
#define SF_Q8_        SF_S8_ // TODO "q"
#define SF_Q8_HEX     "0x%" SF_Q8_HEX_ "/" STRING(Q8_DENOM)
#define SF_Q8_HEX_    SF_S8_HEX_ // TODO "K"

#define SF_t_q16_         SF_Q16_
#define SF_Q16        "%" SF_Q16_ "/" STRING(Q16_DENOM)
#define SF_Q16_       SF_S16_ // TODO "q"
#define SF_Q16_HEX    "0x%" SF_Q16_HEX_ "/" STRING(Q16_DENOM)
#define SF_Q16_HEX_   SF_S16_HEX_ // TODO "K"

#define SF_t_q32_         SF_Q32_
#define SF_Q32        "%" SF_Q32_ "/" STRING(Q32_DENOM)
#define SF_Q32_       SF_S32_ // TODO "q"
#define SF_Q32_HEX    "0x%" SF_Q32_HEX_ "/" STRING(Q32_DENOM)
#define SF_Q32_HEX_   SF_S32_HEX_ // TODO "K"

#define SF_t_q64_         SF_Q64_
#define SF_Q64        "%" SF_Q64_ "/" STRING(Q64_DENOM)
#define SF_Q64_       SF_S64_ // TODO "lq"
#define SF_Q64_HEX    "0x%" SF_Q64_HEX_ "/" STRING(Q64_DENOM)
#define SF_Q64_HEX_   SF_S64_HEX_ // TODO "lK"

#define SF_t_q128_        SF_Q128_
#define SF_Q128       "%" SF_Q128_ "/" STRING(Q128_DENOM)
#define SF_Q128_      SF_S128_ // TODO "Lq"
#define SF_Q128_HEX   "0x%" SF_Q128_HEX_ "/" STRING(Q128_DENOM)
#define SF_Q128_HEX_  SF_S128_HEX_ // TODO "LK"
//!@}

//!@doc String format specifier macros for libccc/float.h
//!@{
#define SF_t_float_        SF_FLOAT_
#define SF_FLOAT       "%" SF_FLOAT_
#define SF_FLOAT_      CONCAT(SF_F,CONCAT(LIBCONFIG_FLOAT_BITS,_))
#define SF_FLOAT_HEX   "%" SF_FLOAT_HEX_
#define SF_FLOAT_HEX_  CONCAT(SF_F,CONCAT(LIBCONFIG_FLOAT_BITS,_HEX_))

#define SF_t_f16_          SF_F16_
#define SF_F16        "%#" SF_F16_
#define SF_F16_       "g"
#define SF_F16_HEX    "%#" SF_F16_HEX_
#define SF_F16_HEX_   "a"
#define SF_F16_FULL   "%.9E"

#define SF_t_f32_          SF_F32_
#define SF_F32        "%#" SF_F32_
#define SF_F32_       "g"
#define SF_F32_HEX    "%#" SF_F32_HEX_
#define SF_F32_HEX_   "a"
#define SF_F32_FULL   "%.9E"

#define SF_t_f64_          SF_F64_
#define SF_F64        "%#" SF_F64_
#define SF_F64_       "g"
#define SF_F64_HEX    "%#" SF_F64_HEX_
#define SF_F64_HEX_   "a"
#define SF_F64_FULL   "%.17E"

#define SF_t_f80_          SF_F80_
#define SF_F80        "%#" SF_F80_
#define SF_F80_       "Lg"
#define SF_F80_HEX    "%#" SF_F80_HEX_
#define SF_F80_HEX_   "La"
#define SF_F80_FULL   "%.21LE"

#define SF_t_f128_         SF_F128_
#define SF_F128       "%#" SF_F128_
#define SF_F128_      "Lg"
#define SF_F128_HEX   "%#" SF_F128_HEX_
#define SF_F128_HEX_  "La"
#define SF_F128_FULL  "%.36LE"
//!@}

//!@doc String format specifier macros for libccc/pointer.h
//!@{
#define SF_t_pointer_          SF_POINTER_
#define SF_POINTER      "$0x%" SF_POINTER_
#define SF_POINTER_     "p"

#define SF_t_size_          SF_SIZE_
#define SF_SIZE         "%" SF_SIZE_
#define SF_SIZE_        "zu"
#define SF_SIZE_HEX     "0x%" SF_SIZE_HEX_
#define SF_SIZE_HEX_    "zx"

#ifdef _IS_64BIT
#define SF_t_ptrdiff_       SF_PTRDIFF_
#define SF_PTRDIFF      "%" SF_PTRDIFF_
#define SF_PTRDIFF_     "ti"
#define SF_PTRDIFF_HEX  "0x%" SF_PTRDIFF_HEX_
#define SF_PTRDIFF_HEX_ "tx"

#define SF_t_sintptr_       SF_SINTPTR_
#define SF_SINTPTR      "%" SF_SINTPTR_
#define SF_SINTPTR_     "zi"
#define SF_t_uintptr_       SF_UINTPTR_
#define SF_UINTPTR      "%" SF_UINTPTR_
#define SF_UINTPTR_     "zu"
#define SF_SINTPTR_HEX  "0x%" SF_SINTPTR_HEX_
#define SF_SINTPTR_HEX_ "zX"
#define SF_UINTPTR_HEX  "0x%" SF_UINTPTR_HEX_
#define SF_UINTPTR_HEX_ "zX"
#else
#define SF_t_ptrdiff_       SF_PTRDIFF_
#define SF_PTRDIFF      "%" SF_PTRDIFF_
#define SF_PTRDIFF_     "i"
#define SF_PTRDIFF_HEX  "0x%" SF_PTRDIFF_HEX_
#define SF_PTRDIFF_HEX_ "x"

#define SF_t_sintptr_       SF_SINTPTR_
#define SF_SINTPTR      "%" SF_SINTPTR_
#define SF_SINTPTR_     "i"
#define SF_t_uintptr_       SF_UINTPTR_
#define SF_UINTPTR      "%" SF_UINTPTR_
#define SF_UINTPTR_     "u"
#define SF_SINTPTR_HEX  "0x%" SF_SINTPTR_HEX_
#define SF_SINTPTR_HEX_ "X"
#define SF_UINTPTR_HEX  "0x%" SF_UINTPTR_HEX_
#define SF_UINTPTR_HEX_ "X"
#endif

#define SF_t_sintmax_       SF_SINTMAX_
#define SF_SINTMAX      "%" SF_SINTMAX_
#define SF_SINTMAX_     "ji"
#define SF_t_uintmax_       SF_UINTMAX_
#define SF_UINTMAX      "%" SF_UINTMAX_
#define SF_UINTMAX_     "ju"
#define SF_SINTMAX_HEX  "0x%" SF_SINTMAX_HEX_
#define SF_SINTMAX_HEX_ "jX"
#define SF_UINTMAX_HEX  "0x%" SF_UINTMAX_HEX_
#define SF_UINTMAX_HEX_ "jX"
//!@}



//!@doc String format specifier macros for libccc/memory.h
//!@{
#define SF_MEMORY     "%" SF_MEMORY_
#define SF_MEMORY_    "m" //
//!@}



//!@doc String format specifier macros for libccc/math/complex.h
//!@{
#define SF_COMPLEX          SF_COMPLEX_()
#define SF_COMPLEX_(PREFIX) "(" SF(COMPLEX_RE_,PREFIX) " + " SF(COMPLEX_IM_,PREFIX) "*i)"

#define SF_COMPLEX_RE  "%" SF_COMPLEX_RE_
#define SF_COMPLEX_RE_ "g"

#define SF_COMPLEX_IM  "%" SF_COMPLEX_IM_
#define SF_COMPLEX_IM_ "g"
//!@}



//!@doc String format specifier macros for libccc/math/algebra/vector.h
//!@{
#define SF_VECTOR_AXIS  "%" SF_VECTOR_AXIS_
#define SF_VECTOR_AXIS_ "g"

#define SF_VECTOR1D \
		SF_VECTOR1D_()
#define SF_VECTOR1D_(PREFIX) \
		"(" SF(VECTOR_AXIS_,PREFIX) ")"

#define SF_VECTOR2D \
		SF_VECTOR2D_()
#define SF_VECTOR2D_(PREFIX) \
		"(" SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ")"

#define SF_VECTOR3D \
		SF_VECTOR3D_()
#define SF_VECTOR3D_(PREFIX) \
		"(" SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ")"

#define SF_VECTOR4D \
		SF_VECTOR4D_()
#define SF_VECTOR4D_(PREFIX) \
		"(" SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ", " SF(VECTOR_AXIS_,PREFIX) ")"
//!@}

//!@doc String format specifier macros for libccc/math/algebra/matrix.h
//!@{
#define SF_MATRIX1D \
		SF_MATRIX1D_()
#define SF_MATRIX1D_(PREFIX) \
		SF_VECTOR1D_(PREFIX) "\n"

#define SF_MATRIX2D \
		SF_MATRIX2D_()
#define SF_MATRIX2D_(PREFIX) \
		SF_VECTOR2D_(PREFIX) "\n" SF_VECTOR2D_(PREFIX) "\n"

#define SF_MATRIX3D \
		SF_MATRIX3D_()
#define SF_MATRIX3D_(PREFIX) \
		SF_VECTOR3D_(PREFIX) "\n" SF_VECTOR3D_(PREFIX) "\n" SF_VECTOR3D_(PREFIX) "\n"

#define SF_MATRIX4D \
		SF_MATRIX4D_()
#define SF_MATRIX4D_(PREFIX) \
		SF_VECTOR4D_(PREFIX) "\n" SF_VECTOR4D_(PREFIX) "\n" SF_VECTOR4D_(PREFIX) "\n" SF_VECTOR4D_(PREFIX) "\n"
//!@}



//!@doc String format specifier macros for libccc/image/color.h
//!@{
#define SF_COLOR_ARGB16  "#%" SF_COLOR_ARGB16_
#define SF_COLOR_ARGB16_ "X"

#define SF_COLOR_ARGB32  "#%" SF_COLOR_ARGB32_
#define SF_COLOR_ARGB32_ "X"

#define SF_COLOR_ARGB_CHANNEL  "%" SF_COLOR_ARGB_CHANNEL_
#define SF_COLOR_ARGB_CHANNEL_ "g"
#define SF_COLOR_ARGB \
		SF_COLOR_ARGB_()
#define SF_COLOR_ARGB_(PREFIX) "(" \
	"A:" SF(COLOR_ARGB_CHANNEL,PREFIX) ", " \
	"R:" SF(COLOR_ARGB_CHANNEL,PREFIX) ", " \
	"G:" SF(COLOR_ARGB_CHANNEL,PREFIX) ", " \
	"B:" SF(COLOR_ARGB_CHANNEL,PREFIX) ")"

#define SF_COLOR_AHSL_CHANNEL  "%" SF_COLOR_AHSL_CHANNEL_
#define SF_COLOR_AHSL_CHANNEL_ "g"
#define SF_COLOR_AHSL \
		SF_COLOR_AHSL_()
#define SF_COLOR_AHSL_(PREFIX) "(" \
	"A:" SF(COLOR_AHSL_CHANNEL,PREFIX) ", " \
	"H:" SF(COLOR_AHSL_CHANNEL,PREFIX) ", " \
	"S:" SF(COLOR_AHSL_CHANNEL,PREFIX) ", " \
	"L:" SF(COLOR_AHSL_CHANNEL,PREFIX) ")"
//!@}



/*============================================================================*\
||                           String Format Functions                          ||
\*============================================================================*/

//!@doc Constructs a string from the given `format` string and multiple args (equivalent to `asprintf()`)
/*!
**	Constructs a new null-terminated string, which is generated from the given `format` string,
**	as well as any relevant variadic arguments - it is equivalent to the `asprintf()` function.
**
**	The `format` string may contain format specifiers (ie: a '%%' followed by
**	certain specific text characters, documented below).
**	A format specifier has the following syntax (items between brackets are optional):
**
**	`%[flags][min_size][.precision][bitsize]char`
**
**	Here is a description of the valid possible choices for each of these 5 fields:
**
**	`char`:
**	
**	| char  | Output                                        | Output Example |
**	|:-----:|-----------------------------------------------|----------------|
**	|`d`,`i`| Signed decimal integer                        |`"392"`         |
**	| `u`   | Unsigned decimal integer                      |`"7235"`        |
**	| `o`   | Unsigned octal                                |`"610"`         |
**	| `x`   | Unsigned hexadecimal integer, lowercase       |`"7fa"`         |
**	| `X`   | Unsigned hexadecimal integer, uppercase       |`"7FA"`         |
**	| `f`   | Decimal notation floating-point, lowercase    |`"392.65"`      |
**	| `F`   | Decimal notation floating-point, uppercase    |`"392.65"`      |
**	| `e`   | Scientific notation floating-point, lowercase |`"3.9265e+2"`   |
**	| `E`   | Scientific notation floating-point, uppercase |`"3.9265E+2"`   |
**	| `g`   | Use the shortest representation: `%e` or `%f` |`"392.65"`      |
**	| `G`   | Use the shortest representation: `%E` or `%F` |`"392.65"`      |
**	| `a`   | Hexadecimal floating point, lowercase         |`"-0xc.90fep-2"`|
**	| `A`   | Hexadecimal floating point, uppercase         |`"-0XC.90FEP-2"`|
**	| `c`   | Character                                     |`"a"`           |
**	| `s`   | String of characters                          |`"example"`     |
**	| `p`   | Pointer address                               |`"b8000000"`    |
**	| `%`   | A `%%` specifier will write a single '%' char |`"%"`           |
**	| `n`   | Nothing printed: the corresponding argument must be a pointer to a signed int.<br/> The number of characters written so far is stored in the pointed location.	| `""` |
**
**	`flags`: (optional)
**	
**	- `-`: The output is left-justified within the field (by default, it is right-justified)
**	- `+`: Precede the result with a plus '+' or minus '-' sign, even for positive/unsigned numbers.
**	       By default, only negative numbers are preceded with a minus '-' sign.
**	- `#`: With `o`,`x`,`X`: the value is preceded with `0`, `0x` or `0X` respectively, for values other than zero.
**	       With `a`,`A`,`e`,`E`,`f`,`F`,`g`,`G`: forces the written output number to contain a decimal point.
**	- `0`: For number-type format specifiers, leading zeros will be used to pad the field instead of space characters.
**	       Is ignored if `-` flag is present. Undefined behavior will occur for any non-number format specifiers.
**	- (space): If no sign is going to be written, a blank space is inserted before the value.
**
**	`min_size`: (optional)
**	
**	- Is a number (so, decimal numerical digit chars) or `*`).
**	- The minimum amount of characters to be printed for this specifier.
**	- NOTE: The value is not truncated, even if the result is larger.
**	- NOTE: If the value is shorter than this number, the result is padded with blank spaces.
**
**	`precision`: (optional)
**	
**	- Is a number (so, decimal numerical digit chars) or `*`, preceded by a '.' period.
**	- If the period is specified without an explicit value for precision, 0 is assumed.
**	- With `a`,`A`,`e`,`E`,`f`,`F`: the amount of digits to be printed after the decimal point (by default, this is 6).
**	- With `g`,`G`: the maximum number of significant digits to be printed for the mantissa.
**	- With `s`: this is the maximum number of characters to be printed (by default, all chars are printed until the `'\0'` terminator).
**
**	`bitsize`: (optional)
**	
**	| size | `d`/`i`       | `u`, `o`, `x`/`X`      |`f`,`e`,`g`,`a`| `c`  | `s`    | `p` | `n`			   |
**	|:----:|---------------|------------------------|---------------|------|--------|-----|----------------|
**	|(none)| int           | unsigned int           | double        | int  | char*  |void*| int*           |
**	| `hh` | signed char   | unsigned char          |               |      |        |     | signed char*   |
**	| `h`  | short int     | unsigned short int     |               |      |        |     | short int*     |
**	| `l`  | long int      | unsigned long int      |               |wint_t|wchar_t*|     | long int*      |
**	| `ll` | long long int | unsigned long long int |               |      |        |     | long long int* |
**	| `j`  | intmax_t      | uintmax_t              |               |      |        |     | intmax_t*      |
**	| `z`  | size_t        | size_t                 |               |      |        |     | size_t*        |
**	| `t`  | ptrdiff_t     | ptrdiff_t              |               |      |        |     | ptrdiff_t*     |
**	| `L`  |               |                        | long double   |      |        |     |                |
**
**	@param	format	The format string: may contain `%` argument specifiers, as described above.
**	@param	...		The list of variadic arguments, corresponding to the `%` specifiers in the `format` string.
**	@returns
**	A newly allocated string, constructed from the given `format` string and arguments
*/
//!@{
//! @isostd{BSD,https://linux.die.net/man/3/asprintf}
_FORMAT(printf, 1, 2)
_MALLOC()
t_char*					String_Format(t_char const* format, ...);
#define c_asprintf		String_Format
#define c_strfmt		String_Format
#define c_strformat		String_Format
#define String_Build	String_Format
//! @isostd{BSD,https://linux.die.net/man/3/vasprintf}
_MALLOC()
t_char*					String_Format_VA(t_char const* format, va_list args);
#define c_vasprintf		String_Format_VA
#define c_strfmt_va		String_Format_VA
#define c_strformat_va	String_Format_VA
#define String_Build_VA	String_Format_VA
//!@}



//!@doc Constructs a string from the given `format` string and multiple args, writing at most `max` chars into `dest` (equivalent to `snprintf()`)
/*!
**	@param	dest	The destination buffer, in which to write the resulting string
**					NOTE: if `NULL`, does not write anything and simply returns the length
**	@param	max		The maximum amount of characters to write to `dest`,
**					including the `'\0'` null terminator
**	@param	format	The format string used to construct the resulting output string.
**					You can learn more about how this works in the doc for String_Format()
**	@param	...		The list of variadic arguments, corresponding to the `%` specifiers in the `format` string.
**	@returns
**	The amount of characters written to `dest`, or `0` if there was an error.
**	You may assume that the returned size will always be less than or equal to `max`.
*/
//!@{
//!	@isostd{C89,https://en.cppreference.com/w/c/io/snprintf}
_FORMAT(printf, 3, 4)
t_size						String_Format_N(t_char* dest, t_size max, t_char const* format, ...);
#define c_snprintf			String_Format_N
#define c_strnfmt			String_Format_N
#define c_strnformat		String_Format_N
#define String_Build_N		String_Format_N
//!	@isostd{C89,https://en.cppreference.com/w/c/io/vsnprintf}
t_size						String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args);
#define c_vsnprintf			String_Format_N_VA
#define c_strnfmt_va		String_Format_N_VA
#define c_strnformat_va		String_Format_N_VA
#define String_Build_N_VA	String_Format_N_VA
//!@}



/*! @endgroup */
HEADER_END
#endif
