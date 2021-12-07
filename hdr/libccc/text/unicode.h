/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/unicode.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_TEXT_UNICODE_H
#define __LIBCCC_TEXT_UNICODE_H
/*!@group{libccc_text_unicode}
**
**	This header defines all the functions related to Unicode text encodings.
**
**	- https://en.wikipedia.org/wiki/UTF-8
**	- https://en.wikipedia.org/wiki/UTF-16
**	- https://en.wikipedia.org/wiki/UTF-32
**	- https://unicode-table.com/en/#
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_TEXT_UNICODE_T
#define __LIBCCC_TEXT_UNICODE_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Primitive type: Unicode UTF-8 character (variable length: 1 to 4 bytes)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/string/multibyte}
*/
typedef char			t_utf8;
TYPEDEF_ALIAS(			t_utf8, UTF8, PRIMITIVE)



//! Primitive type: Unicode UTF-16 character (variable length: 2 or 4 bytes)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/string/multibyte/char16_t}
**	@isostd{C,https://en.cppreference.com/w/c/string/multibyte}
*/
typedef uint_least16_t	t_utf16; // TODO add option to use C11 `char16_t`
TYPEDEF_ALIAS(			t_utf16, UTF16, PRIMITIVE)



//! Primitive type: Unicode UTF-32 character code point value (fixed length: 4 bytes)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/string/multibyte/char32_t}
**	@isostd{C,https://en.cppreference.com/w/c/string/wide}
*/
typedef uint_least32_t	t_utf32; // TODO add option to use C11 `char32_t`
TYPEDEF_ALIAS(			t_utf32, UTF32, PRIMITIVE)



// TODO add option with wrapper functions for the ones in C11 <uchar.h>



// TODO add useful `CHARSET_*` macros for UTF sets



/*!
**	These macros are used to encode/decode UTF-8 strings.
*/
//!@{
#define UTF8_1BYTE	0x00000080	//!< Beneath this code point, UTF-8 encodes this as a 1-byte character
#define UTF8_2BYTE	0x00000800	//!< Beneath this code point, UTF-8 encodes this as a 2-byte character
#define UTF8_3BYTE	0x00010000	//!< Beneath this code point, UTF-8 encodes this as a 3-byte character
#define UTF8_4BYTE	0x0010FFFF	//!< Beneath this code point, UTF-8 encodes this as a 4-byte character
//!@}



/*!
**	These macros are used to encode/decode UTF-16 strings.
*/
//!@{
#define UTF16_BIAS		0x10000
#define UTF16_SURROGATE_HI	0xD800
#define UTF16_SURROGATE_LO	0xDC00
#define UTF16_SURROGATE_END	0xE000
#define UTF16_SURROGATE_MASK	0x3FF
//!@}



/*!
**	The Unicode byte order mark (https://en.wikipedia.org/wiki/Byte_order_mark) macros.
**	A byte order mark is used at the beginning of a string, to indicate that the string is
**	indeed a Unicode string, the type of Unicode encoding, and the byte endian-ness used.
*/
//!@{
//! The UTF-8 byte order mark: `EF BB BF`
#define UTF8_BOM	"\xEF\xBB\xBF"

//! The UTF-16 byte order mark: `FE FF` (Big-Endian)
#define UTF16_BOM_BE	"\xFE\xFF"
//! The UTF-16 byte order mark: `FF FE` (Little-Endian)
#define UTF16_BOM_LE	"\xFF\xFE"

//! The UTF-16 byte order mark: `00 00 FE FF` (Big-Endian)
#define UTF32_BOM_BE	"\x00\x00\xFE\xFF"
//! The UTF-16 byte order mark: `FF FE 00 00` (Little-Endian)
#define UTF32_BOM_LE	"\xFF\xFE\x00\x00"
//!@}



#endif
#ifndef __LIBCCC_TEXT_UNICODE_F
#define __LIBCCC_TEXT_UNICODE_F

/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//! Check if the given char `c` is a letter character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswalpha}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a letter (lowercase or uppercase),
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsLetter(t_utf32 c);
#define c_wcisalpha		UTF32_IsLetter
#define UTF32_IsAlpha	UTF32_IsLetter

//! Check if the given char `c` is a uppercase letter character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswupper}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a uppercase letter character,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsUppercase(t_utf32 c);
#define c_wcisupper		UTF32_IsUppercase
#define UTF32_IsUpper	UTF32_IsUppercase

//! Check if the given char `c` is an lowercase letter character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswlower}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is an lowercase letter character,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsLowercase(t_utf32 c);
#define c_wcislower		UTF32_IsLowercase
#define UTF32_IsLower	UTF32_IsLowercase

//! Check if the given char `c` is alphanumeric (letter or digit) character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswalnum}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is alphanumeric (letter or digit),
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsAlphaNumeric(t_utf32 c);
#define c_wcisalnum		UTF32_IsAlphaNumeric
#define UTF32_IsAlNum	UTF32_IsAlphaNumeric



//! Check if the given char `c` is a decimal digit character (ie: #CHARSET_DEC: `0123456789`)
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswdigit}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a decimal digit character,
**	otherwise returns `FALSE`.
*/
t_bool						UTF32_IsDigit_Decimal(t_utf32 c);
#define c_wcisdigit			UTF32_IsDigit_Decimal
#define UTF32_IsDigit		UTF32_IsDigit_Decimal
#define UTF32_IsDigit_Dec	ASCII_IsDigit_Decimal

//! Checks if the given char `c` is a hexadecimal digit character (ie: #CHARSET_HEX: `0123456789ABCDEFabcdef`)
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswxdigit}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a hexadecimal digit character,
**	otherwise returns `FALSE`.
*/
t_bool						UTF32_IsDigit_Hexadecimal(t_utf32 c);
#define c_wcisxdigit		UTF32_IsDigit_Hexadecimal
#define UTF32_IsDigit_Hex	UTF32_IsDigit_Hexadecimal

//! Checks if the given char `c` is a octal-base digit character (ie: #CHARSET_OCT: `01234567`)
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is an octal digit character,
**	otherwise returns `FALSE`.
*/
t_bool						UTF32_IsDigit_Octal(t_utf32 c);
#define c_wcisodigit		UTF32_IsDigit_Octal
#define UTF32_IsDigit_Oct	UTF32_IsDigit_Octal

//! Checks if the given char `c` is a binary-base digit character (ie: '0' or '1')
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a binary digit character,
**	otherwise returns `FALSE`.
*/
t_bool						UTF32_IsDigit_Binary(t_utf32 c);
#define c_wcisbdigit		UTF32_IsDigit_Binary
#define UTF32_IsDigit_Bin	UTF32_IsDigit_Binary



//! Check if the given char `c` is whitespace character (prints nothing)
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswspace}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is whitespace character,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsWhiteSpace(t_utf32 c);
#define c_wcisspace		UTF32_IsWhiteSpace
#define UTF32_IsSpace	UTF32_IsWhiteSpace

//! Check if the given char `c` is a punctuation character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswpunct}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a punctuation character,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsPunctuation(t_utf32 c);
#define c_wcispunct		UTF32_IsPunctuation
#define UTF32_IsPunct	UTF32_IsPunctuation

// TODO https://en.cppreference.com/w/c/string/wide/iswcntrl

//! Check if the given char `c` is a printable Unicode character
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/iswprint}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a printable Unicode character,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsPrintable(t_utf32 c);
#define c_wcisprint		UTF32_IsPrintable
#define UTF32_IsPrint	UTF32_IsPrintable

//! Check if the given char `c` is an ASCII-compatible char (non-Unicode)
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` has a value between 0 and 127,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsASCII(t_utf32 c);
#define c_wcisascii		UTF32_IsASCII

//! Check if the given char `c` is a valid Unicode code point
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a valid UTF-32 code point,
**	otherwise returns `FALSE`.
*/
t_bool					UTF32_IsValid(t_utf32 c);
#define c_wcisvalid		UTF32_IsValid



//! Check if the given char `c` is contained in the given 'charset'
/*!
**	Check if the given char `c` is contained in the given 'charset'
**
**	@param	c		The character to check
**	@param	charset	The set of characters to look through
**	@returns
**	`TRUE` if the given char `c` is contained within the given `charset` array,
**	otherwise returns `FALSE`.
*/
t_bool						UTF32_IsInCharset(t_utf32 c, t_utf32 const* charset);
#define c_wcincharset		UTF32_IsInCharset
#define Unicode_IsInCharset	UTF32_IsInCharset



// TODO wctype_t enum, and wctype() function



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//! Get the uppercase version of the given char `c`, if possible
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/towupper}
**
**	@param	c	The character whose uppercase equivalent should be returned
**	@returns
**	The uppercase equivalent of the given character,
**	or returns `c` itself if it is not a letter character.
*/
t_utf32						UTF32_ToUppercase(t_utf32 c);
#define c_wctoupper			UTF32_ToUppercase
#define UTF32_ToUpper		UTF32_ToUppercase

//! Get the lowercase version of the given char `c`, if possible
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/wide/towlower}
**
**	@param	c	The character whose lowercase equivalent should be returned
**	@returns
**	The lowercase equivalent of the given character,
**	or returns `c` itself if it is not a letter character.
*/
t_utf32						UTF32_ToLowercase(t_utf32 c);
#define c_wctolower			UTF32_ToLowercase
#define UTF32_ToLower		UTF32_ToLowercase

// TODO UTF32_ToASCII()



/*
** ************************************************************************** *|
**                             Encoding Conversions                           *|
** ************************************************************************** *|
*/

// TODO UTF8_Length(), to mirror the mblen() function



//! Converts the given Unicode char `c` to its UTF-8 equivalent representation
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/multibyte/wctomb}
**
**	Converts the given char `c` to UTF-8 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-8 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns
**	The size (in bytes) of the character written (can be 0, 1, 2, 3, or 4)
*/
t_size						UTF32_ToUTF8(t_utf8* dest, t_utf32 c);
#define c_wctomb			UTF32_ToUTF8
#define c_wctoutf8			UTF32_ToUTF8

//! Converts the given Unicode char `c` to its UTF-16 equivalent representation
/*!
**	@nonstd
**
**	Converts the given char `c` to UTF-16 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-16 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns
**	The size (in bytes) of the character written (can be 0, 2, or 4)
*/
t_size						UTF32_ToUTF16(t_utf16* dest, t_utf32 c);
#define c_wctomb2			UTF32_ToUTF16
#define c_wctoutf16			UTF32_ToUTF16



//! Returns the Unicode code point value (UTF-32) for the first UTF-8 character in `str`
/*!
**	@isostd{C95,https://en.cppreference.com/w/c/string/multibyte/mbtowc}
**
**	Reads up to 4 bytes in `str`, and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-8 character
**	@returns
**	The Unicode code point value for the character pointed to by `str`
*/
t_utf32						UTF32_FromUTF8(t_utf8 const* str);
#define c_mbtowc			UTF32_FromUTF8
#define c_utf8towc			UTF32_FromUTF8

//! Returns the Unicode code point value (UTF-32) for the first UTF-16 character in `str`
/*!
**	@nonstd
**
**	Reads 2 or 4 bytes in `str`, and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-16 character
**	@returns
**	The Unicode code point value for the character pointed to by `str`
*/
t_utf32						UTF32_FromUTF16(t_utf16 const* str);
#define c_mb2towc			UTF32_FromUTF16
#define c_utf16towc			UTF32_FromUTF16



//! Parses a UTF-8 string escape sequence (`\U????????`, or `\u????`) from the given `str`
/*!
**	@nonstd
**
**	@param	str	The string from which to parse an escape sequence
**	@returns
**	The UTF-32 code point for the parsed unicode character,
**	or `-1`(#ERROR) if there was a parsing error.
*/
t_utf32					UTF32_FromEscape(t_ascii const* str);
#define c_wcparse		UTF32_FromEscape

//! Parses a UTF-8 string escape sequence (`\U????????`, or `\u????`), reading at most `n` chars from `str`
/*!
**	@nonstd
**
**	@param	dest	The pointer to the 32-bit integer in which the result will be written.
**	@param	str		The string from which to parse an escape sequence.
**	@param	n		The maximum amount of characters to read from `str`.
**					NOTE: if `0` is given, then there will be no maximum amount.
**	@returns
**	The total amount of bytes read from the given `str` buffer.
*/
t_size					UTF32_Parse(t_utf32* dest, t_ascii const* str, t_size n);
#define c_wcnparse		UTF32_Parse



/*
** ************************************************************************** *|
**                              Unicode Charsets                              *|
** ************************************************************************** *|
*/

//! Parses a UTF-8 BOM (byte order mark) in `str`
/*!
**	@returns
**	`0` if there is no UTF-8 byte order mark at `str`,
**	or the length of the UTF-8 byte order mark (ie: `3`)
*/
t_sint				UTF8_ByteOrderMark(t_utf8 const* str);
#define c_mbbom		UTF8_ByteOrderMark

//! Parses a UTF-16 BOM (byte order mark) in `str`
/*!
**	@returns
**	`0` if there is no UTF-16 byte order mark at `str`,
**	or the length of the UTF-16 byte order mark (ie: `2`) -
**	also note: the return is negative for a big-endian BOM (ie: `-2`)
*/
t_sint				UTF16_ByteOrderMark(t_utf16 const* str);
#define c_mb2bom	UTF16_ByteOrderMark

//! Parses a UTF-32 BOM (byte order mark) in `str`
/*!
**	@returns
**	`0` if there is no UTF-32 byte order mark at `str`,
**	or the length of the UTF-32 byte order mark (ie: `4`) -
**	also note: the return is negative for a big-endian BOM (ie: `-4`)
*/
t_sint				UTF32_ByteOrderMark(t_utf32 const* str);
#define c_wcbom		UTF32_ByteOrderMark



// TODO UTF32_Charset()

// TODO enum e_unicode
//!< 0x0000 — 0x007F	Basic Latin
//!< 0x0080 — 0x00FF	Latin-1 Supplement
//!< 0x0100 — 0x017F	Latin Extended-A
//!< 0x0180 — 0x024F	Latin Extended-B
//!< 0x0250 — 0x02AF	IPA Extensions
//!< 0x02B0 — 0x02FF	Spacing Modifier Letters
//!< 0x0300 — 0x036F	Combining Diacritical Marks
//!< 0x0370 — 0x03FF	Greek and Coptic
//!< 0x0400 — 0x04FF	Cyrillic
//!< 0x0500 — 0x052F	Cyrillic Supplement
//!< 0x0530 — 0x058F	Armenian
//!< 0x0590 — 0x05FF	Hebrew
//!< 0x0600 — 0x06FF	Arabic
//!< 0x0700 — 0x074F	Syriac
//!< 0x0750 — 0x077F	Arabic Supplement
//!< 0x0780 — 0x07BF	Thaana
//!< 0x07C0 — 0x07FF	NKo
//!< 0x0800 — 0x083F	Samaritan
//!< 0x0840 — 0x085F	Mandaic
//!< 0x0860 — 0x086F	Syriac Supplement
//!< 0x08A0 — 0x08FF	Arabic Extended-A
//!< 0x0900 — 0x097F	Devanagari
//!< 0x0980 — 0x09FF	Bengali
//!< 0x0A00 — 0x0A7F	Gurmukhi
//!< 0x0A80 — 0x0AFF	Gujarati
//!< 0x0B00 — 0x0B7F	Oriya
//!< 0x0B80 — 0x0BFF	Tamil
//!< 0x0C00 — 0x0C7F	Telugu
//!< 0x0C80 — 0x0CFF	Kannada
//!< 0x0D00 — 0x0D7F	Malayalam
//!< 0x0D80 — 0x0DFF	Sinhala
//!< 0x0E00 — 0x0E7F	Thai
//!< 0x0E80 — 0x0EFF	Lao
//!< 0x0F00 — 0x0FFF	Tibetan
//!< 0x1000 — 0x109F	Myanmar
//!< 0x10A0 — 0x10FF	Georgian
//!< 0x1100 — 0x11FF	Hangul Jamo
//!< 0x1200 — 0x137F	Ethiopic
//!< 0x1380 — 0x139F	Ethiopic Supplement
//!< 0x13A0 — 0x13FF	Cherokee
//!< 0x1400 — 0x167F	Unified Canadian Aboriginal Syllabics
//!< 0x1680 — 0x169F	Ogham
//!< 0x16A0 — 0x16FF	Runic
//!< 0x1700 — 0x171F	Tagalog
//!< 0x1720 — 0x173F	Hanunoo
//!< 0x1740 — 0x175F	Buhid
//!< 0x1760 — 0x177F	Tagbanwa
//!< 0x1780 — 0x17FF	Khmer
//!< 0x1800 — 0x18AF	Mongolian
//!< 0x18B0 — 0x18FF	Unified Canadian Aboriginal Syllabics Extended
//!< 0x1900 — 0x194F	Limbu
//!< 0x1950 — 0x197F	Tai Le
//!< 0x1980 — 0x19DF	New Tai Lue
//!< 0x19E0 — 0x19FF	Khmer Symbols
//!< 0x1A00 — 0x1A1F	Buginese
//!< 0x1A20 — 0x1AAF	Tai Tham
//!< 0x1AB0 — 0x1AFF	Combining Diacritical Marks Extended
//!< 0x1B00 — 0x1B7F	Balinese
//!< 0x1B80 — 0x1BBF	Sundanese
//!< 0x1BC0 — 0x1BFF	Batak
//!< 0x1C00 — 0x1C4F	Lepcha
//!< 0x1C50 — 0x1C7F	Ol Chiki
//!< 0x1C80 — 0x1C8F	Cyrillic Extended C
//!< 0x1C90 — 0x1CBF	Georgian Extended
//!< 0x1CC0 — 0x1CCF	Sundanese Supplement
//!< 0x1CD0 — 0x1CFF	Vedic Extensions
//!< 0x1D00 — 0x1D7F	Phonetic Extensions
//!< 0x1D80 — 0x1DBF	Phonetic Extensions Supplement
//!< 0x1DC0 — 0x1DFF	Combining Diacritical Marks Supplement
//!< 0x1E00 — 0x1EFF	Latin Extended Additional
//!< 0x1F00 — 0x1FFF	Greek Extended
//!< 0x2000 — 0x206F	General Punctuation
//!< 0x2070 — 0x209F	Superscripts and Subscripts
//!< 0x20A0 — 0x20CF	Currency Symbols
//!< 0x20D0 — 0x20FF	Combining Diacritical Marks for Symbols
//!< 0x2100 — 0x214F	Letterlike Symbols
//!< 0x2150 — 0x218F	Number Forms
//!< 0x2190 — 0x21FF	Arrows
//!< 0x2200 — 0x22FF	Mathematical Operators
//!< 0x2300 — 0x23FF	Miscellaneous Technical
//!< 0x2400 — 0x243F	Control Pictures
//!< 0x2440 — 0x245F	Optical Character Recognition
//!< 0x2460 — 0x24FF	Enclosed Alphanumerics
//!< 0x2500 — 0x257F	Box Drawing
//!< 0x2580 — 0x259F	Block Elements
//!< 0x25A0 — 0x25FF	Geometric Shapes
//!< 0x2600 — 0x26FF	Miscellaneous Symbols
//!< 0x2700 — 0x27BF	Dingbats
//!< 0x27C0 — 0x27EF	Miscellaneous Mathematical Symbols-A
//!< 0x27F0 — 0x27FF	Supplemental Arrows-A
//!< 0x2800 — 0x28FF	Braille Patterns
//!< 0x2900 — 0x297F	Supplemental Arrows-B
//!< 0x2980 — 0x29FF	Miscellaneous Mathematical Symbols-B
//!< 0x2A00 — 0x2AFF	Supplemental Mathematical Operators
//!< 0x2B00 — 0x2BFF	Miscellaneous Symbols and Arrows
//!< 0x2C00 — 0x2C5F	Glagolitic
//!< 0x2C60 — 0x2C7F	Latin Extended-C
//!< 0x2C80 — 0x2CFF	Coptic
//!< 0x2D00 — 0x2D2F	Georgian Supplement
//!< 0x2D30 — 0x2D7F	Tifinagh
//!< 0x2D80 — 0x2DDF	Ethiopic Extended
//!< 0x2DE0 — 0x2DFF	Cyrillic Extended-A
//!< 0x2E00 — 0x2E7F	Supplemental Punctuation
//!< 0x2E80 — 0x2EFF	CJK Radicals Supplement
//!< 0x2F00 — 0x2FDF	Kangxi Radicals
//!< 0x2FF0 — 0x2FFF	Ideographic Description Characters
//!< 0x3000 — 0x303F	CJK Symbols and Punctuation
//!< 0x3040 — 0x309F	Hiragana
//!< 0x30A0 — 0x30FF	Katakana
//!< 0x3100 — 0x312F	Bopomofo
//!< 0x3130 — 0x318F	Hangul Compatibility Jamo
//!< 0x3190 — 0x319F	Kanbun
//!< 0x31A0 — 0x31BF	Bopomofo Extended
//!< 0x31C0 — 0x31EF	CJK Strokes
//!< 0x31F0 — 0x31FF	Katakana Phonetic Extensions
//!< 0x3200 — 0x32FF	Enclosed CJK Letters and Months
//!< 0x3300 — 0x33FF	CJK Compatibility
//!< 0x3400 — 0x4DBF	CJK Unified Ideographs Extension A
//!< 0x4DC0 — 0x4DFF	Yijing Hexagram Symbols
//!< 0x4E00 — 0x9FFF	CJK Unified Ideographs
//!< 0xA000 — 0xA48F	Yi Syllables
//!< 0xA490 — 0xA4CF	Yi Radicals
//!< 0xA4D0 — 0xA4FF	Lisu
//!< 0xA500 — 0xA63F	Vai
//!< 0xA640 — 0xA69F	Cyrillic Extended-B
//!< 0xA6A0 — 0xA6FF	Bamum
//!< 0xA700 — 0xA71F	Modifier Tone Letters
//!< 0xA720 — 0xA7FF	Latin Extended-D
//!< 0xA800 — 0xA82F	Syloti Nagri
//!< 0xA830 — 0xA83F	Common Indic Number Forms
//!< 0xA840 — 0xA87F	Phags-pa
//!< 0xA880 — 0xA8DF	Saurashtra
//!< 0xA8E0 — 0xA8FF	Devanagari Extended
//!< 0xA900 — 0xA92F	Kayah Li
//!< 0xA930 — 0xA95F	Rejang
//!< 0xA960 — 0xA97F	Hangul Jamo Extended-A
//!< 0xA980 — 0xA9DF	Javanese
//!< 0xA9E0 — 0xA9FF	Myanmar Extended-B
//!< 0xAA00 — 0xAA5F	Cham
//!< 0xAA60 — 0xAA7F	Myanmar Extended-A
//!< 0xAA80 — 0xAADF	Tai Viet
//!< 0xAAE0 — 0xAAFF	Meetei Mayek Extensions
//!< 0xAB00 — 0xAB2F	Ethiopic Extended-A
//!< 0xAB30 — 0xAB6F	Latin Extended-E
//!< 0xAB70 — 0xABBF	Cherokee Supplement
//!< 0xABC0 — 0xABFF	Meetei Mayek
//!< 0xAC00 — 0xD7AF	Hangul Syllables
//!< 0xD7B0 — 0xD7FF	Hangul Jamo Extended-B
//!< 0xD800 — 0xDB7F	High Surrogates
//!< 0xDB80 — 0xDBFF	High Private Use Surrogates
//!< 0xDC00 — 0xDFFF	Low Surrogates
//!< 0xE000 — 0xF8FF	Private Use Area
//!< 0xF900 — 0xFAFF	CJK Compatibility Ideographs
//!< 0xFB00 — 0xFB4F	Alphabetic Presentation Forms
//!< 0xFB50 — 0xFDFF	Arabic Presentation Forms-A
//!< 0xFE00 — 0xFE0F	Variation Selectors
//!< 0xFE10 — 0xFE1F	Vertical Forms
//!< 0xFE20 — 0xFE2F	Combining Half Marks
//!< 0xFE30 — 0xFE4F	CJK Compatibility Forms
//!< 0xFE50 — 0xFE6F	Small Form Variants
//!< 0xFE70 — 0xFEFF	Arabic Presentation Forms-B
//!< 0xFF00 — 0xFFEF	Halfwidth and Fullwidth Forms
//!< 0xFFF0 — 0xFFFF	Specials
//!< 0x10000 — 0x1007F	Linear B Syllabary
//!< 0x10080 — 0x100FF	Linear B Ideograms
//!< 0x10100 — 0x1013F	Aegean Numbers
//!< 0x10140 — 0x1018F	Ancient Greek Numbers
//!< 0x10190 — 0x101CF	Ancient Symbols
//!< 0x101D0 — 0x101FF	Phaistos Disc
//!< 0x10280 — 0x1029F	Lycian
//!< 0x102A0 — 0x102DF	Carian
//!< 0x102E0 — 0x102FF	Coptic Epact Numbers
//!< 0x10300 — 0x1032F	Old Italic
//!< 0x10330 — 0x1034F	Gothic
//!< 0x10350 — 0x1037F	Old Permic
//!< 0x10380 — 0x1039F	Ugaritic
//!< 0x103A0 — 0x103DF	Old Persian
//!< 0x10400 — 0x1044F	Deseret
//!< 0x10450 — 0x1047F	Shavian
//!< 0x10480 — 0x104AF	Osmanya
//!< 0x104B0 — 0x104FF	Osage
//!< 0x10500 — 0x1052F	Elbasan
//!< 0x10530 — 0x1056F	Caucasian Albanian
//!< 0x10600 — 0x1077F	Linear A
//!< 0x10800 — 0x1083F	Cypriot Syllabary
//!< 0x10840 — 0x1085F	Imperial Aramaic
//!< 0x10860 — 0x1087F	Palmyrene
//!< 0x10880 — 0x108AF	Nabataean
//!< 0x108E0 — 0x108FF	Hatran
//!< 0x10900 — 0x1091F	Phoenician
//!< 0x10920 — 0x1093F	Lydian
//!< 0x10980 — 0x1099F	Meroitic Hieroglyphs
//!< 0x109A0 — 0x109FF	Meroitic Cursive
//!< 0x10A00 — 0x10A5F	Kharoshthi
//!< 0x10A60 — 0x10A7F	Old South Arabian
//!< 0x10A80 — 0x10A9F	Old North Arabian
//!< 0x10AC0 — 0x10AFF	Manichaean
//!< 0x10B00 — 0x10B3F	Avestan
//!< 0x10B40 — 0x10B5F	Inscriptional Parthian
//!< 0x10B60 — 0x10B7F	Inscriptional Pahlavi
//!< 0x10B80 — 0x10BAF	Psalter Pahlavi
//!< 0x10C00 — 0x10C4F	Old Turkic
//!< 0x10C80 — 0x10CFF	Old Hungarian
//!< 0x10D00 — 0x10D3F	Hanifi Rohingya
//!< 0x10E60 — 0x10E7F	Rumi Numeral Symbols
//!< 0x10E80 — 0x10EBF	Yezidi
//!< 0x10F00 — 0x10F2F	Old Sogdian
//!< 0x10F30 — 0x10F6F	Sogdian
//!< 0x10FB0 — 0x10FDF	Chorasmian
//!< 0x10FE0 — 0x10FFF	Elymaic
//!< 0x11000 — 0x1107F	Brahmi
//!< 0x11080 — 0x110CF	Kaithi
//!< 0x110D0 — 0x110FF	Sora Sompeng
//!< 0x11100 — 0x1114F	Chakma
//!< 0x11150 — 0x1117F	Mahajani
//!< 0x11180 — 0x111DF	Sharada
//!< 0x111E0 — 0x111FF	Sinhala Archaic Numbers
//!< 0x11200 — 0x1124F	Khojki
//!< 0x11280 — 0x112AF	Multani
//!< 0x112B0 — 0x112FF	Khudawadi
//!< 0x11300 — 0x1137F	Grantha
//!< 0x11400 — 0x1147F	Newa
//!< 0x11480 — 0x114DF	Tirhuta
//!< 0x11580 — 0x115FF	Siddham
//!< 0x11600 — 0x1165F	Modi
//!< 0x11660 — 0x1167F	Mongolian Supplement
//!< 0x11680 — 0x116CF	Takri
//!< 0x11700 — 0x1173F	Ahom
//!< 0x11800 — 0x1184F	Dogra
//!< 0x118A0 — 0x118FF	Warang Citi
//!< 0x11900 — 0x1195F	Dives Akuru
//!< 0x119A0 — 0x119FF	Nandinagari
//!< 0x11A00 — 0x11A4F	Zanabazar Square
//!< 0x11A50 — 0x11AAF	Soyombo
//!< 0x11AC0 — 0x11AFF	Pau Cin Hau
//!< 0x11C00 — 0x11C6F	Bhaiksuki
//!< 0x11C70 — 0x11CBF	Marchen
//!< 0x11D00 — 0x11D5F	Masaram Gondi
//!< 0x11D60 — 0x11DAF	Gunjala Gondi
//!< 0x11EE0 — 0x11EFF	Makasar
//!< 0x11FB0 — 0x11FBF	Lisu Supplement
//!< 0x11FC0 — 0x11FFF	Tamil Supplement
//!< 0x12000 — 0x123FF	Cuneiform
//!< 0x12400 — 0x1247F	Cuneiform Numbers and Punctuation
//!< 0x12480 — 0x1254F	Early Dynastic Cuneiform
//!< 0x13000 — 0x1342F	Egyptian Hieroglyphs
//!< 0x13430 — 0x1343F	Egyptian Hieroglyph Format Controls
//!< 0x14400 — 0x1467F	Anatolian Hieroglyphs
//!< 0x16800 — 0x16A3F	Bamum Supplement
//!< 0x16A40 — 0x16A6F	Mro
//!< 0x16AD0 — 0x16AFF	Bassa Vah
//!< 0x16B00 — 0x16B8F	Pahawh Hmong
//!< 0x16E40 — 0x16E9F	Medefaidrin
//!< 0x16F00 — 0x16F9F	Miao
//!< 0x16FE0 — 0x16FFF	Ideographic Symbols and Punctuation
//!< 0x17000 — 0x187FF	Tangut
//!< 0x18800 — 0x18AFF	Tangut Components
//!< 0x18B00 — 0x18CFF	Khitan Small Script
//!< 0x18D00 — 0x18D8F	Tangut Supplement
//!< 0x1B000 — 0x1B0FF	Kana Supplement
//!< 0x1B100 — 0x1B12F	Kana Extended-A
//!< 0x1B130 — 0x1B16F	Small Kana Extension
//!< 0x1B170 — 0x1B2FF	Nushu
//!< 0x1BC00 — 0x1BC9F	Duployan
//!< 0x1BCA0 — 0x1BCAF	Shorthand Format Controls
//!< 0x1D000 — 0x1D0FF	Byzantine Musical Symbols
//!< 0x1D100 — 0x1D1FF	Musical Symbols
//!< 0x1D200 — 0x1D24F	Ancient Greek Musical Notation
//!< 0x1D2E0 — 0x1D2FF	Mayan Numerals
//!< 0x1D300 — 0x1D35F	Tai Xuan Jing Symbols
//!< 0x1D360 — 0x1D37F	Counting Rod Numerals
//!< 0x1D400 — 0x1D7FF	Mathematical Alphanumeric Symbols
//!< 0x1D800 — 0x1DAAF	Sutton SignWriting
//!< 0x1E000 — 0x1E02F	Glagolitic Supplement
//!< 0x1E100 — 0x1E14F	Nyiakeng Puachue Hmong
//!< 0x1E2C0 — 0x1E2FF	Wancho
//!< 0x1E800 — 0x1E8DF	Mende Kikakui
//!< 0x1E900 — 0x1E95F	Adlam
//!< 0x1EC70 — 0x1ECBF	Indic Siyaq Numbers
//!< 0x1ED00 — 0x1ED4F	Ottoman Siyaq Numbers
//!< 0x1EE00 — 0x1EEFF	Arabic Mathematical Alphabetic Symbols
//!< 0x1F000 — 0x1F02F	Mahjong Tiles
//!< 0x1F030 — 0x1F09F	Domino Tiles
//!< 0x1F0A0 — 0x1F0FF	Playing Cards
//!< 0x1F100 — 0x1F1FF	Enclosed Alphanumeric Supplement
//!< 0x1F200 — 0x1F2FF	Enclosed Ideographic Supplement
//!< 0x1F300 — 0x1F5FF	Miscellaneous Symbols and Pictographs
//!< 0x1F600 — 0x1F64F	Emoticons (Emoji)
//!< 0x1F650 — 0x1F67F	Ornamental Dingbats
//!< 0x1F680 — 0x1F6FF	Transport and Map Symbols
//!< 0x1F700 — 0x1F77F	Alchemical Symbols
//!< 0x1F780 — 0x1F7FF	Geometric Shapes Extended
//!< 0x1F800 — 0x1F8FF	Supplemental Arrows-C
//!< 0x1F900 — 0x1F9FF	Supplemental Symbols and Pictographs
//!< 0x1FA00 — 0x1FA6F	Chess Symbols
//!< 0x1FA70 — 0x1FAFF	Symbols and Pictographs Extended-A
//!< 0x1FB00 — 0x1FBFF	Symbols for Legacy Computing
//!< 0x20000 — 0x2A6DF	CJK Unified Ideographs Extension B
//!< 0x2A700 — 0x2B73F	CJK Unified Ideographs Extension C
//!< 0x2B740 — 0x2B81F	CJK Unified Ideographs Extension D
//!< 0x2B820 — 0x2CEAF	CJK Unified Ideographs Extension E
//!< 0x2CEB0 — 0x2EBEF	CJK Unified Ideographs Extension F
//!< 0x2F800 — 0x2FA1F	CJK Compatibility Ideographs Supplement
//!< 0x30000 — 0x3134F	CJK Unified Ideographs Extension G
//!< 0xE0000 — 0xE007F	Tags
//!< 0xE0100 — 0xE01EF	Variation Selectors Supplement
//!< 0xF0000 — 0xFFFFF	Supplementary Private Use Area-A
//!< 0x100000—0x10FFFF	Supplementary Private Use Area-B



#endif

/*! @endgroup */
HEADER_END
#endif
