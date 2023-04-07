/*============================================================================*\
||                                            ______________________________  ||
||  libccc/text/char_ascii.h                 |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_CHAR_ASCII_H
#define __LIBCCC_CHAR_ASCII_H
/*!@group{libccc_char_ascii,6,libccc/text/char_ascii.h}
**
**	This header defines all the functions related to ASCII text (7-bit chars).
**
**	@isostd{C,https://en.cppreference.com/w/c/language/ascii}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_CHAR_ASCII_T
#define __LIBCCC_CHAR_ASCII_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//!@doc Primitive type: `char`, ie: a text character (1 byte: ANSI/ASCII)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/string/byte}
*/
//!@{
typedef char	t_ascii;
TYPEDEF_ALIAS(	t_ascii, ASCII, PRIMITIVE)
//!@}



// TODO add option with wrapper functions for the ones in C11 <uchar.h>

 

//!@doc ASCII/Unicode C0 control code characters (from 0x00 to 0x1F)
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

//!@doc ASCII/Unicode C1 control code characters (from 0x80 to 0x9F)
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



#endif
#ifndef __LIBCCC_CHAR_ASCII_F
#define __LIBCCC_CHAR_ASCII_F

/*
** ************************************************************************** *|
**                              Character Checks                              *|
** ************************************************************************** *|
*/

//!@doc Check if the given char `c` is a letter (lowercase or uppercase)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isalpha}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a letter (lowercase or uppercase),
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsLetter(t_ascii c);
#define c_iscalpha			CharASCII_IsLetter
#define c_cisalpha			CharASCII_IsLetter
#define CharASCII_IsAlpha	CharASCII_IsLetter
//!@}

//!@doc Check if the given char `c` is a uppercase letter character
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isupper}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a uppercase letter character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsUppercase(t_ascii c);
#define c_iscupper			CharASCII_IsUppercase
#define c_cisupper			CharASCII_IsUppercase
#define CharASCII_IsUpper	CharASCII_IsUppercase
//!@}

//!@doc Check if the given char `c` is an lowercase letter character
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/islower}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is an lowercase letter character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsLowercase(t_ascii c);
#define c_isclower			CharASCII_IsLowercase
#define c_cislower			CharASCII_IsLowercase
#define CharASCII_IsLower	CharASCII_IsLowercase
//!@}

//!@doc Check if the given char `c` is alphanumeric (letter or digit) character
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isalnum}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is alphanumeric (letter or digit),
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsAlphaNumeric(t_ascii c);
#define c_iscalnum			CharASCII_IsAlphaNumeric
#define c_cisalnum			CharASCII_IsAlphaNumeric
#define CharASCII_IsAlNum	CharASCII_IsAlphaNumeric
//!@}



//!@doc Check if the given char `c` is a decimal digit character (ie: #CHARSET_DEC: `0123456789`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isdigit}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a decimal digit character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool							CharASCII_IsDigit_Decimal(t_ascii c);
#define c_iscdigit				CharASCII_IsDigit_Decimal
#define c_cisdigit				CharASCII_IsDigit_Decimal
#define CharASCII_IsDigit		CharASCII_IsDigit_Decimal
#define CharASCII_IsDigit_Dec	CharASCII_IsDigit_Decimal
//!@}

//!@doc Checks if the given char `c` is a hexadecimal digit character (ie: #CHARSET_HEX: `0123456789abcdefABCDEF`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isxdigit}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a hexadecimal digit character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool							CharASCII_IsDigit_Hexadecimal(t_ascii c);
#define c_iscxdigit				CharASCII_IsDigit_Hexadecimal
#define c_cisxdigit				CharASCII_IsDigit_Hexadecimal
#define CharASCII_IsDigit_Hex	CharASCII_IsDigit_Hexadecimal
//!@}

//!@doc Checks if the given char `c` is a octal-base digit character (ie: #CHARSET_OCT: `01234567`)
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is an octal digit character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool							CharASCII_IsDigit_Octal(t_ascii c);
#define c_iscodigit				CharASCII_IsDigit_Octal
#define c_cisodigit				CharASCII_IsDigit_Octal
#define CharASCII_IsDigit_Oct	CharASCII_IsDigit_Octal
//!@}

//!@doc Checks if the given char `c` is a binary-base digit character (ie: '0' or '1')
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a binary digit character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool							CharASCII_IsDigit_Binary(t_ascii c);
#define c_iscbdigit				CharASCII_IsDigit_Binary
#define c_cisbdigit				CharASCII_IsDigit_Binary
#define CharASCII_IsDigit_Bin	CharASCII_IsDigit_Binary
//!@}



//!@doc Check if the given char `c` is whitespace character (`' '`,`'\t'`,`'\r'`,`'\n'`,`'\f'`,`'\v'`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isspace}
**
**	Whitespace characters are:
**	- `' '`	space
**	- `'\t'`	TAB- horiztonal tab
**	- `'\r'`	CR - carriage return
**	- `'\n'`	LF - line feed (newline)
**	- `'\f'`	FF - form feed (next page)
**	- `'\v'`	VT - vertical tab
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is whitespace character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsWhiteSpace(t_ascii c);
#define c_iscspace			CharASCII_IsWhiteSpace
#define c_cisspace			CharASCII_IsWhiteSpace
#define CharASCII_IsSpace	CharASCII_IsWhiteSpace
//!@}

//!@doc Check if the given char `c` is a punctuation character
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/ispunct}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a punctuation character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsPunctuation(t_ascii c);
#define c_iscpunct			CharASCII_IsPunctuation
#define c_cispunct			CharASCII_IsPunctuation
#define CharASCII_IsPunct	CharASCII_IsPunctuation
//!@}

// TODO https://en.cppreference.com/w/c/string/byte/iscntrl

//!@doc Check if the given char `c` is a printable ASCII character
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/isprint}
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` is a printable ASCII character,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool						CharASCII_IsPrintable(t_ascii c);
#define c_iscprint			CharASCII_IsPrintable
#define c_cisprint			CharASCII_IsPrintable
#define CharASCII_IsPrint	CharASCII_IsPrintable
//!@}

//!@doc Check if the given char `c` is an ASCII-compatible char (non-Unicode)
/*!
**	@nonstd
**
**	@param	c	The character to check
**	@returns
**	`TRUE` if the given char `c` has a value between `0x00` and `0x7F`,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool					CharASCII_IsValid(t_ascii c);
#define c_iscascii		CharASCII_IsASCII
#define c_cisascii		CharASCII_IsASCII
#define c_isccvalid		CharASCII_IsValid
//!@}



//!@doc Check if the given char `c` is contained in the given 'charset'
/*!
**	Check if the given char `c` is contained in the given 'charset'
**
**	@param	c		The character to check
**	@param	charset	The set of characters to look through
**	@returns
**	`TRUE` if the given char `c` is contained within the given `charset` array,
**	otherwise returns `FALSE`.
*/
//!@{
t_bool					CharASCII_IsInCharset(t_ascii c, t_ascii const* charset);
#define c_isccincharset	CharASCII_IsInCharset
//!@}



/*
** ************************************************************************** *|
**                           Character Substitutions                          *|
** ************************************************************************** *|
*/

//!@doc Get the uppercase version of the given char `c`, if possible
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/toupper}
**
**	@param	c	The character whose uppercase equivalent should be returned
**	@returns
**	The uppercase equivalent of the given character `c`,
**	or returns `c` itself if it is not a letter character.
*/
//!@{
t_ascii						CharASCII_ToUppercase(t_ascii c);
#define c_tocupper			CharASCII_ToUppercase
#define c_ctoupper			CharASCII_ToUppercase
#define CharASCII_ToUpper	CharASCII_ToUppercase
//!@}

//!@doc Get the lowercase version of the given char `c`, if possible
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/tolower}
**
**	@param	c	The character whose lowercase equivalent should be returned
**	@returns
**	The lowercase equivalent of the given character `c`,
**	or returns `c` itself if it is not a letter character.
*/
//!@{
t_ascii						CharASCII_ToLowercase(t_ascii c);
#define c_toclower			CharASCII_ToLowercase
#define c_ctolower			CharASCII_ToLowercase
#define CharASCII_ToLower	CharASCII_ToLowercase
//!@}


//! Converts `c` to \xFF
/*! 
**	@nonstd
**
**	Converts `c` to \xFF format where each 'F' is an hexadecimal number represented with ASCII char 0-9 and A-F
**	If `c` is too big to be encoded with this format (if c > 0xFF), then `ERROR` is returned and nothing is written
**	If `dest` is not NULL, writes 4 ASCII char to dest to represent the character in the format \xFF
**	This function's behavior is kept consisten with `CharUTF8_ToEscaped_xFF`
**
**	@param	dest	The buffer in which the output will be written, if non NULL
**	@param	c		the unicode character to encode
**	@returns
**	4: The number of byte written on `dest`, or that would have been written to `dest` if `dest` wasn't NULL
*/
//!@{
t_size					CharASCII_ToEscaped_xFF(t_ascii *dest, t_ascii c);
#define c_ctoesc_xFF	CharASCII_ToEscaped_xFF
//!@}

#endif

/*! @endgroup */
HEADER_END
#endif
