/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/char.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_CHAR_H
#define __LIBCCC_CHAR_H
/*!@group{libccc_char}
** @{
**	This header defines all the functions/sets related to single ASCII chars.
**
**	@isostd{https://en.cppreference.com/w/c/language/ascii}
**	- https://en.wikipedia.org/wiki/UTF-8
**	- https://en.wikipedia.org/wiki/UTF-16
**	- https://en.wikipedia.org/wiki/UTF-32
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_naming.h"
#include "libccc_define.h"

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Primitive type: `char`, ie: a text character (1 byte: ANSI/ASCII)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte}
*/
typedef char	t_char;
TYPEDEF_ALIAS(	t_char, CHAR, PRIMITIVE)

//! Primitive type: Unicode UTF-8 character (variable length: 1 to 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte}
*/
typedef char		t_utf8;
TYPEDEF_ALIAS(		t_utf8, UTF8, PRIMITIVE)

//! Primitive type: Unicode UTF-16 character (variable length: 2 or 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/char16_t}
**	@isostd{https://en.cppreference.com/w/c/string/multibyte}
*/
typedef uint_least16_t	t_utf16; // TODO add option to use C11 `char16_t`
TYPEDEF_ALIAS(			t_utf16, UTF16, PRIMITIVE)

//! Primitive type: Unicode UTF-32 character code point value (fixed length: 4 bytes)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/char32_t}
**	@isostd{https://en.cppreference.com/w/c/string/wide}
*/
typedef uint_least32_t	t_utf32; // TODO add option to use C11 `char32_t`
TYPEDEF_ALIAS(			t_utf32, UTF32, PRIMITIVE)

// TODO add option with wrapper functions for the ones in C11 <uchar.h>


/*
**	Define string literals for alphabet characters
*/
//! Set of characters for the lowercase latin alphabet
#define CHARSET_LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
//! Set of characters for the uppercase latin alphabet
#define CHARSET_UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//! Set of characters for the latin alphabet (both lowercase and uppercase)
#define CHARSET_ALPHABET	"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"

/*
**	Define string literals for some of the commonly used number bases.
*/
#define CHARSET_BINARY		"01"
#define CHARSET_OCTAL		"01234567"
#define CHARSET_DECIMAL		"0123456789"
#define CHARSET_HEX_LOWER	"0123456789abcdef"
#define CHARSET_HEX_UPPER	"0123456789ABCDEF"
#define CHARSET_HEX			CHARSET_HEXADECIMAL
#define CHARSET_HEXADECIMAL	"0123456789aAbBcCdDeEfF"

//! A charset containing all of the different whitespace characters
#define CHARSET_WHITESPACE	" \t\n\r\v\f"

//! A charset containing all of the ASCII punctuation characters
#define CHARSET_PUNCTUATION	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

 

//! ASCII/Unicode C0 control code characters (from 0x00 to 0x1F)
/*!
**	@see https://en.wikipedia.org/wiki/C0_and_C1_control_codes#C0_controls
*/
//!@{
#define C0_NUL	0x00	//!< ^@	`␀`	NUL	`\0`	Null
#define C0_SOH	0x01	//!< ^A	`␁`	SOH			Start of Heading
#define C0_STX	0x02	//!< ^B	`␂`	STX			Start of Text
#define C0_ETX	0x03	//!< ^C	`␃`	ETX			End of Text
#define C0_EOT	0x04	//!< ^D	`␄`	EOT			End of Transmission
#define C0_ENQ	0x05	//!< ^E	`␅`	ENQ			Enquiry
#define C0_ACK	0x06	//!< ^F	`␆`	ACK			Acknowledge
#define C0_BEL	0x07	//!< ^G	`␇`	BEL	`\a`	Bell, Alert
#define C0_BS	0x08	//!< ^H	`␈`	BS	`\b`	Backspace
#define C0_HT	0x09	//!< ^I	`␉`	HT	`\t`	Char/Horizontal Tab
#define C0_LF	0x0A	//!< ^J	`␊`	LF	`\n`	Line Feed
#define C0_VT	0x0B	//!< ^K	`␋`	VT	`\v`	Line/Vertical Tab
#define C0_FF	0x0C	//!< ^L	`␌`	FF	`\f`	Form Feed
#define C0_CR	0x0D	//!< ^M	`␍`	CR	`\r`	Carriage Return
#define C0_SO	0x0E	//!< ^N	`␎`	SO			Shift Out
#define C0_SI	0x0F	//!< ^O	`␏`	SI			Shift In
#define C0_DLE	0x10	//!< ^P	`␐`	DLE			Data Link Escape
#define C0_DC1	0x11	//!< ^Q	`␑`	DC1			Device Control One (XON)
#define C0_DC2	0x12	//!< ^R	`␒`	DC2			Device Control Two
#define C0_DC3	0x13	//!< ^S	`␓`	DC3			Device Control Three (XOFF)
#define C0_DC4	0x14	//!< ^T	`␔`	DC4			Device Control Four
#define C0_NAK	0x15	//!< ^U	`␕`	NAK			Negative Acknowledge
#define C0_SYN	0x16	//!< ^V	`␖`	SYN			Synchronous Idle
#define C0_ETB	0x17	//!< ^W	`␗`	ETB			End of Transmission Block
#define C0_CAN	0x18	//!< ^X	`␘`	CAN			Cancel
#define C0_EM	0x19	//!< ^Y	`␙`	EM			End of medium
#define C0_SUB	0x1A	//!< ^Z	`␚`	SUB			Substitute
#define C0_ESC	0x1B	//!< ^[	`␛`	ESC	`\e`	Escape
#define C0_FS	0x1C	//!< ^\	`␜`	FS			File Separator
#define C0_GS	0x1D	//!< ^]	`␝`	GS			Group Separator
#define C0_RS	0x1E	//!< ^^	`␞`	RS			Record Separator
#define C0_US	0x1F	//!< ^_	`␟`	US			Unit Separator

#define C0_DEL	0x7F	//!< ^?	`␡`	DEL			Delete	(Not technically part of the C0 control character range)
//!@}

//! ASCII/Unicode C1 control code characters (from 0x80 to 0x9F)
/*!
**	@see https://en.wikipedia.org/wiki/C0_and_C1_control_codes#C1_controls
*/
//!@{
#define C1_PAD	0x80	//!< ^ 	``	PAD		Padding Character
#define C1_HOP	0x81	//!< ^ 	``	HOP		High Octet Preset
#define C1_BPH	0x82	//!< ^ 	``	BPH		Break Permitted Here
#define C1_NBH	0x83	//!< ^ 	``	NBH		No Break Here
#define C1_IND	0x84	//!< ^ 	``	IND		Index
#define C1_NEL	0x85	//!< ^ 	``	NEL		Next Line
#define C1_SSA	0x86	//!< ^ 	``	SSA		Start of Selected Area
#define C1_ESA	0x87	//!< ^ 	``	ESA		End of Selected Area
#define C1_HTS	0x88	//!< ^ 	``	HTS		Char/Horizontal Tabulation Set
#define C1_HTJ	0x89	//!< ^ 	``	HTJ		Char/Horizontal Tabulation With Justification
#define C1_VTS	0x8A	//!< ^ 	``	VTS		Line/Vertical Tabulation Set
#define C1_PLD	0x8B	//!< ^ 	``	PLD		Partial Line Forward / Partial Line Down
#define C1_PLU	0x8C	//!< ^ 	``	PLU		Partial Line Backward / Partial Line Up
#define C1_RI	0x8D	//!< ^ 	``	RI		Reverse Line Feed / Reverse Index
#define C1_SS2	0x8E	//!< ^ 	``	SS2		Single-Shift 2
#define C1_SS3	0x8F	//!< ^ 	``	SS3		Single-Shift 3
#define C1_DCS	0x90	//!< ^ 	``	DCS		Device Control String
#define C1_PU1	0x91	//!< ^ 	``	PU1		Private Use 1
#define C1_PU2	0x92	//!< ^ 	``	PU2		Private Use 2
#define C1_STS	0x93	//!< ^ 	``	STS		Set Transmit State
#define C1_CCH	0x94	//!< ^ 	``	CCH		Cancel character
#define C1_MW	0x95	//!< ^ 	``	MW		Message Waiting
#define C1_SPA	0x96	//!< ^ 	``	SPA		Start of Protected Area
#define C1_EPA	0x97	//!< ^ 	``	EPA		End of Protected Area
#define C1_SOS	0x98	//!< ^ 	``	SOS		Start of String
#define C1_SGC	0x99	//!< ^ 	``	SGC		Single Graphic Character Introducer
#define C1_SCI	0x9A	//!< ^ 	``	SCI		Single Character Introducer
#define C1_CSI	0x9B	//!< ^ 	``	CSI		Control Sequence Introducer
#define C1_ST	0x9C	//!< ^ 	``	ST		String Terminator
#define C1_OSC	0x9D	//!< ^ 	``	OSC		Operating System Command
#define C1_PM	0x9E	//!< ^ 	``	PM		Privacy Message
#define C1_APC	0x9F	//!< ^ 	``	APC		Application Program Command
//!@}



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



/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//! Check if the given char `c` is a letter (lowercase or uppercase)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isalpha}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a letter (lowercase or uppercase), otherwise #FALSE.
*/
t_bool					Char_IsLetter(t_utf32 c);
#define c_isalpha		Char_IsLetter
#define Char_IsAlpha	Char_IsLetter

//! Check if the given char `c` is a uppercase letter character
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isupper}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a uppercase letter character, otherwise #FALSE.
*/
t_bool					Char_IsUppercase(t_utf32 c);
#define c_isupper		Char_IsUppercase
#define Char_IsUpper	Char_IsUppercase

//! Check if the given char `c` is an lowercase letter character
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/islower}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is an lowercase letter character, otherwise #FALSE.
*/
t_bool					Char_IsLowercase(t_utf32 c);
#define c_islower		Char_IsLowercase
#define Char_IsLower	Char_IsLowercase

//! Check if the given char `c` is alphanumeric (letter or digit) character
/*!
**	Check if the given char `c` is alphanumeric (letter or digit) character
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is alphanumeric (letter or digit), otherwise #FALSE.
**	@isostd{https://en.cppreference.com/w/c/string/byte/isalnum}
*/
t_bool					Char_IsAlphaNumeric(t_utf32 c);
#define c_isalnum		Char_IsAlphaNumeric
#define Char_IsAlNum	Char_IsAlphaNumeric

//! Check if the given char `c` is a decimal digit character (ie: #CHARSET_DEC: `0123456789`)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isdigit}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a decimal digit character, otherwise #FALSE.
*/
t_bool							Char_IsDigit(t_utf32 c);
#define c_isdigit				Char_IsDigit
#define Char_IsDigit			Char_IsDigit
#define Char_IsDigit_Dec		Char_IsDigit
#define Char_IsDigit_Decimal	Char_IsDigit

//! Checks if the given char `c` is a hexadecimal digit character (ie: #CHARSET_HEX: `0123456789abcdefABCDEF`)
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isxdigit}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a hexadecimal digit character, otherwise #FALSE.
*/
t_bool								Char_IsDigit_Hex(t_utf32 c);
#define c_isdigit_hex				Char_IsDigit_Hex
#define Char_IsDigit_Hexadecimal	Char_IsDigit_Hex

//! Checks if the given char `c` is a octal-base digit character (ie: #CHARSET_OCT: `01234567`)
/*!
**	@nonstd
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is an octal digit character, otherwise #FALSE.
*/
t_bool								Char_IsDigit_Oct(t_utf32 c);
#define c_isdigit_oct				Char_IsDigit_Oct
#define Char_IsDigit_Octal			Char_IsDigit_Oct

//! Checks if the given char `c` is a binary-base digit character (ie: '0' or '1')
/*!
**	@nonstd
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a binary digit character, otherwise #FALSE.
*/
t_bool								Char_IsDigit_Bin(t_utf32 c);
#define c_isdigit_bin				Char_IsDigit_Bin
#define Char_IsDigit_Binary			Char_IsDigit_Bin

//! Check if the given char `c` is whitespace character (' ','\\t','\\r','\\n','\\f','\\v')
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isspace}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is whitespace character: ' ','\\t','\\r','\\n','\\f','\\v'
**			(carriage return, newline, form feed, vertical tab, tab, or space), and returns #FALSE otherwise.
*/
t_bool						Char_IsSpace(t_utf32 c);
#define c_isspace			Char_IsSpace
#define Char_IsWhiteSpace	Char_IsSpace

//! Check if the given char `c` is a punctuation character
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/ispunct}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a punctuation character,
**			and returns #FALSE otherwise.
*/
t_bool					Char_IsPunctuation(t_utf32 c);
#define c_ispunct		Char_IsPunctuation
#define Char_IsPunct	Char_IsPunctuation

// TODO https://en.cppreference.com/w/c/string/byte/iscntrl

//! Check if the given char `c` is a printable ASCII character
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/isprint}
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a printable ASCII character,
**			(0x20 <= c && c <= 0x7E) and returns #FALSE otherwise.
*/
t_bool					Char_IsPrintable(t_utf32 c);
#define c_isprint		Char_IsPrintable
#define Char_IsPrint	Char_IsPrintable

//! Check if the given char `c` is an ASCII-compatible char (non-Unicode)
/*!
**	@nonstd
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` has a value between 0 and 127,
**			(0x00 <= c && c <= 0x7F) and returns #FALSE otherwise.
*/
t_bool				Char_IsASCII(t_utf32 c);
#define c_isascii	Char_IsASCII

//! Check if the given char `c` is a valid Unicode code point
/*!
**	@nonstd
**
**	@param	c	The character to check (ASCII or Unicode)
**	@returns #TRUE if the given char `c` is a valid UTF-32 code point
*/
t_bool				Char_IsValid(t_utf32 c);
#define c_isvalid	Char_IsValid



//! Check if the given char `c` is contained in the given 'charset'
/*!
**	Check if the given char `c` is contained in the given 'charset'
**
**	@param	c		The character to check (ASCII or Unicode)
**	@param	charset	String, the set of characters to look through (the '\0' terminator ends the charset)
**	@returns #TRUE if the given char `c` is contained within the given `charset` array
*/
//!@{
t_bool					Char_IsInCharset(t_utf32 c, t_char const* charset);
#define c_isincharset	Char_IsInCharset
/* TODO
t_bool						Char_IsInCharset_UTF8(t_utf32 c, t_utf8 const* charset);
#define c_isinutf8charset	Char_IsInCharset_UTF8
*/
/* TODO
t_bool						Char_IsInCharset_UTF16(t_utf32 c, t_utf16 const* charset);
#define c_isinutf16charset	Char_IsInCharset_UTF16
*/
//!@}



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//! Get the uppercase version of the given char `c`, if possible
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/toupper}
**
**	@param	c	The character to uppercase-ify (only ASCII characters will be affected)
**	@returns the uppercase equivalent of the given character, or returns `c` itself if it is not a letter character.
*/
//!@{
t_char					Char_ToUppercase(t_char c);
#define c_ctoupper		Char_ToUppercase
#define Char_ToUpper	Char_ToUppercase

t_utf32					Unicode_ToUppercase(t_utf32 c);
#define c_toupper		Unicode_ToUppercase
#define c_wctoupper		Unicode_ToUppercase
#define Unicode_ToUpper	Unicode_ToUppercase
//!@}

//! Get the lowercase version of the given char `c`, if possible
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/tolower}
**
**	@param	c	The character to lowercase-ify (only ASCII characters will be affected)
**	@returns the lowercase equivalent of the given character, or returns `c` itself if it is not a letter character.
*/
//!@{
t_char					Char_ToLowercase(t_char c); // TODO refactor `t_char` here to `t_utf32` (breaking change)
#define c_ctolower		Char_ToLowercase
#define Char_ToLower	Char_ToLowercase

t_utf32					Unicode_ToLowercase(t_utf32 c);
#define c_tolower		Unicode_ToLowercase
#define c_wctolower		Unicode_ToLowercase
#define Unicode_ToLower	Unicode_ToLowercase
//!@}

// TODO Char_ToASCII()



/*
** ************************************************************************** *|
**                             Encoding Conversions                           *|
** ************************************************************************** *|
*/

// TODO UTF8_Length(), to mirror the mblen() function



//! Converts the given Unicode code point value `c` to its UTF-8 equivalent representation
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/wctomb}
**
**	Converts the given char `c` to UTF-8 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-8 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns The size (in bytes) of the character written (can be 0, 1, 2, 3, or 4)
*/
t_size					Char_ToUTF8(t_utf8* dest, t_utf32 c);
#define c_wctomb		Char_ToUTF8
#define c_ctoutf8		Char_ToUTF8

//! Converts the given Unicode code point value `c` to its UTF-16 equivalent representation
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/wctomb}
**
**	Converts the given char `c` to UTF-16 representation, and writes it to 'dest'
**	@param	c		The character to convert (UTF-32 Unicode code point value)
**	@param	dest	The pointer at which to write the resulting UTF-16 char
**					(you must ensure that at least 4 bytes are writable to 'dest')
**	@returns The size (in bytes) of the character written (can be 0, 2, or 4)
*/
t_size					Char_ToUTF16(t_utf16* dest, t_utf32 c);
#define c_wctomb2		Char_ToUTF16
#define c_ctoutf16		Char_ToUTF16



//! Returns the Unicode code point value (UTF-32) for the UTF-8 character pointed to by 'str'
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/mbtowc}
**
**	Reads up to 4 bytes in 'str', and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-8 character
**	@returns The Unicode code point value for the character pointed to by 'str'
*/
t_utf32					Char_FromUTF8(t_utf8 const* str);
#define c_mbtowc		Char_FromUTF8
#define c_utf8toc		Char_FromUTF8
#define UTF8_Get		Char_FromUTF8

//! Returns the Unicode code point value (UTF-32) for the UTF-16 character pointed to by 'str'
/*!
**	@isostd{https://en.cppreference.com/w/c/string/multibyte/mbtowc}
**
**	Reads 2 or 4 bytes in 'str', and converts these bytes to a Unicode code point value
**	@param	str		The string from which to read a UTF-16 character
**	@returns The Unicode code point value for the character pointed to by 'str'
*/
t_utf32					Char_FromUTF16(t_utf16 const* str);
#define c_mb2towc		Char_FromUTF16
#define c_utf16toc		Char_FromUTF16
#define UTF16_Get		Char_FromUTF16



//! Parses a `\U????????`, or `\u????` or `\u????\u????` UTF-8 string escape sequence
/*!
**	@param	str	The string from which to parse an escape sequence
**	@returns the UTF-32 code point for the parsed unicode character,
**		or #ERROR (`-1`) if there was a parsing error.
*/
t_utf32		Char_Parse_Unicode(t_char const* str);

//! Parses a `\U????????`, or `\u????` or `\u????\u????` UTF-8 string escape sequence, reading at most `n` chars from `str`
/*!
**	@param	dest	The pointer to the 32-bit integer in which the result will be written.
**	@param	str		The string from which to parse an escape sequence.
**	@param	n		The maximum amount of characters to read from `str`.
**		NOTE: if `0` is given, then there will be no maximum amount.
**	@returns the total amount of bytes read from the given `str` buffer.
*/
t_size		Char_Parse_Unicode_N(t_utf32* dest, t_char const* str, t_size n);



/*! @} */
HEADER_END
#endif
