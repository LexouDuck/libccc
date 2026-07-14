
/*
**	libccc/text/format.c
**
**	This file implements the `String_Format` family of functions (ie: printf-like
**	string formatting), from scratch, without relying on the platform's `stdio`.
**
**	It implements all of the ISO C standard format specifiers, and also several
**	custom, libccc-specific format specifiers:
**	- `%b`/`%B`: unsigned binary integer / boolean ("TRUE" or "FALSE")
**	- `%C`: char, with non-printable characters shown as escape-sequences
**	- `%S`: string, with non-printable characters shown as escape-sequences
**	- `%q`: fixed-point number (`t_fixed`), decimal notation
**	- `%k`/`%K`: fixed-point number (`t_fixed`), hexadecimal notation
**	- `%m`: raw memory/data bytes, shown as hexadecimal (precision = amount of bytes)
**
**	NOTE: floating-point number output is computed using `long double` arithmetic,
**	which yields (at least) 18 correct significant decimal digits: any digits
**	beyond that amount of significant digits will be output as '0' - unlike certain
**	libc implementations (like glibc), which use arbitrary-precision arithmetic to
**	output several hundred exact significant digits. Similarly, decimal rounding
**	is performed in "round-half-away-from-zero" fashion upon the 18-digit estimate,
**	rather than "round-half-to-even" upon the exact value.
*/

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/memory.h"
#include "libccc/pointer.h"
#include "libccc/string.h"
#include "libccc/text/format.h"
#include "libccc/text/escape.h"
#include "libccc/text/string/ascii.h"

#ifndef __NOSTD__
	#include <stdarg.h>
#else
	typedef __builtin_va_list va_list;
	#define va_start(v,l) __builtin_va_start(v,l)
	#define va_end(v)     __builtin_va_end(v)
	#define va_arg(v,l)   __builtin_va_arg(v,l)
	#define va_copy(d,s)  __builtin_va_copy(d,s)
#endif

#include LIBCONFIG_ERROR_INCLUDE



/*============================================================================*\
||                              Output accumulator                            ||
\*============================================================================*/

//! The state for the format-string output writer (handles both "counting" and "writing" modes)
typedef struct format_output
{
	t_char*	dest;	//!< the destination buffer to write to (if `NULL`, only counts the amount of chars)
	t_size	max;	//!< the maximum amount of chars writable to `dest`, including the final `'\0'`
	t_size	total;	//!< the total amount of chars generated so far (regardless of any truncation)
}	s_format_output;

static
void	Format_WriteChar(s_format_output* out, t_char c)
{
	if (out->dest != NULL && out->max > 0 && out->total < out->max - 1)
		out->dest[out->total] = c;
	out->total += 1;
}

static
void	Format_Write(s_format_output* out, t_char const* str, t_size length)
{
	t_size	i;

	for (i = 0; i < length; ++i)
		Format_WriteChar(out, str[i]);
}

static
void	Format_WriteRepeat(s_format_output* out, t_char c, t_size amount)
{
	while (amount--)
		Format_WriteChar(out, c);
}



/*============================================================================*\
||                            Format specifier parsing                        ||
\*============================================================================*/

//! The possible values for a parsed format specifier's `bitsize` field
typedef enum format_sizespec
{
	FORMATSIZE_DEFAULT = 0,	//!< (none)
	FORMATSIZE_HH,	//!< `hh`	char
	FORMATSIZE_H,	//!< `h`	short
	FORMATSIZE_L,	//!< `l`	long
	FORMATSIZE_LL,	//!< `ll`	long long
	FORMATSIZE_J,	//!< `j`	intmax_t
	FORMATSIZE_Z,	//!< `z`	size_t
	FORMATSIZE_T,	//!< `t`	ptrdiff_t
	FORMATSIZE_CAPL,//!< `L`	long double
}	e_format_sizespec;

//! The state for a single parsed format specifier: `%[flags][min_size][.precision][bitsize]char`
typedef struct format_spec
{
	t_bool	flag_minus;	//!< `-` flag: left-justify within the field
	t_bool	flag_plus;	//!< `+` flag: always show number sign
	t_bool	flag_space;	//!< ` ` flag: leave a blank space in front of positive numbers
	t_bool	flag_hash;	//!< `#` flag: "alternative form" (number base prefix, forced decimal point)
	t_bool	flag_zero;	//!< `0` flag: pad numbers with leading zeros
	t_bool	has_width;	//!< whether a `min_size` field was given
	t_size	width;		//!< the parsed `min_size` field value
	t_bool	has_precision;	//!< whether a `.precision` field was given
	t_size	precision;	//!< the parsed `.precision` field value
	e_format_sizespec	size;	//!< the parsed `bitsize` field value
}	s_format_spec;

//! Parses everything in a format specifier after the initial `'%'` char, except the final conversion char
/*!
**	@param	spec	The struct in which to store the parsed format specifier state
**	@param	format	The format string, positioned right after a `'%'` character
**	@param	args	The variadic arguments list (only used for `*` width/precision fields)
**	@returns
**	The amount of chars read from `format`
**	(such that `format[result]` is the conversion char).
*/
static
t_size	Format_ParseSpec(s_format_spec* spec, t_char const* format, va_list* args)
{
	t_size	i = 0;
	int	value;

	*spec = (s_format_spec){0};
	// flags
	while (TRUE)
	{
		switch (format[i])
		{
			case '-':	spec->flag_minus = TRUE;	break;
			case '+':	spec->flag_plus  = TRUE;	break;
			case ' ':	spec->flag_space = TRUE;	break;
			case '#':	spec->flag_hash  = TRUE;	break;
			case '0':	spec->flag_zero  = TRUE;	break;
			default:	goto parse_width;
		}
		i += 1;
	}
parse_width:
	if (format[i] == '*')
	{
		i += 1;
		value = va_arg(*args, int);
		spec->has_width = TRUE;
		if (value < 0)
		{	// a negative `*` width argument is taken as a `-` flag with a positive width
			spec->flag_minus = TRUE;
			spec->width = (t_size)-value;
		}
		else spec->width = (t_size)value;
	}
	else while (format[i] >= '0' && format[i] <= '9')
	{
		spec->has_width = TRUE;
		spec->width = spec->width * 10 + (t_size)(format[i] - '0');
		i += 1;
	}
	// precision
	if (format[i] == '.')
	{
		i += 1;
		spec->has_precision = TRUE;
		spec->precision = 0;
		if (format[i] == '*')
		{
			i += 1;
			value = va_arg(*args, int);
			if (value < 0)	// a negative `*` precision argument is taken as if no precision was given
				spec->has_precision = FALSE;
			else spec->precision = (t_size)value;
		}
		else while (format[i] >= '0' && format[i] <= '9')
		{
			spec->precision = spec->precision * 10 + (t_size)(format[i] - '0');
			i += 1;
		}
	}
	// bitsize
	switch (format[i])
	{
		case 'h':
			i += 1;
			if (format[i] == 'h')	{	i += 1;	spec->size = FORMATSIZE_HH;	}
			else spec->size = FORMATSIZE_H;
			break;
		case 'l':
			i += 1;
			if (format[i] == 'l')	{	i += 1;	spec->size = FORMATSIZE_LL;	}
			else spec->size = FORMATSIZE_L;
			break;
		case 'j':	i += 1;	spec->size = FORMATSIZE_J;	break;
		case 'z':	i += 1;	spec->size = FORMATSIZE_Z;	break;
		case 't':	i += 1;	spec->size = FORMATSIZE_T;	break;
		case 'L':	i += 1;	spec->size = FORMATSIZE_CAPL;	break;
		default:	break;
	}
	return (i);
}



/*============================================================================*\
||                              Integer conversions                           ||
\*============================================================================*/

#define FORMAT_MAXDIGITS_UINT	64	//!< the largest amount of digits a `t_u64` can have (binary)

//! Converts the given `value` to its string representation in the given number `base` (reversed digit order)
/*!
**	@param	digits		The buffer in which to write the digits (in reverse order, no '\0')
**	@param	value		The unsigned integer value to convert
**	@param	base		The number base to use: `2`, `8`, `10`, or `16`
**	@param	uppercase	If `TRUE`, use uppercase letters for base-16 digits
**	@returns
**	The amount of digit chars written to `digits` (always at least `1`)
*/
static
t_size	Format_ConvertUInt(t_char* digits, t_u64 value, t_u8 base, t_bool uppercase)
{
	static t_char const	digits_lowercase[16+1] = "0123456789abcdef";
	static t_char const	digits_uppercase[16+1] = "0123456789ABCDEF";
	t_char const*	charset = (uppercase ? digits_uppercase : digits_lowercase);
	t_size	i = 0;

	do
	{
		digits[i++] = charset[value % base];
		value /= base;
	}
	while (value > 0);
	return (i);
}

//! Outputs a formatted integer number, with the appropriate flags/width/precision handling
/*!
**	@param	out			The output writer state
**	@param	spec		The parsed format specifier
**	@param	is_signed	Whether this is a signed conversion (ie: whether `+`/` ` flags apply)
**	@param	negative	Whether the number is negative (ie: whether to show a '-' sign)
**	@param	value		The absolute value of the number to write
**	@param	base		The number base to use: `2`, `8`, `10`, or `16`
**	@param	uppercase	If `TRUE`, use uppercase letters (for base-16 digits, and base prefixes)
*/
static
void	Format_WriteInteger(s_format_output* out, s_format_spec const* spec,
	t_bool is_signed, t_bool negative, t_u64 value, t_u8 base, t_bool uppercase)
{
	t_char	digits[FORMAT_MAXDIGITS_UINT];
	t_char	prefix[2] = {0};
	t_size	prefix_len = 0;
	t_size	ndigits = 0;
	t_size	zeros = 0;
	t_size	length;
	t_size	padding;
	t_char	sign = '\0';
	t_size	i;

	if (!(value == 0 && spec->has_precision && spec->precision == 0))
		ndigits = Format_ConvertUInt(digits, value, base, uppercase);
	if (spec->has_precision && spec->precision > ndigits)
		zeros = spec->precision - ndigits;
	if (spec->flag_hash)
	{	// "alternative form": `0` prefix for octal, `0x`/`0b` prefix for hex/binary
		if (base == 8 && zeros == 0 && (ndigits == 0 || digits[ndigits - 1] != '0'))
			zeros = 1;
		else if ((base == 16 || base == 2) && value != 0)
		{
			prefix[0] = '0';
			prefix[1] = (base == 16 ?
				(uppercase ? 'X' : 'x') :
				(uppercase ? 'B' : 'b'));
			prefix_len = 2;
		}
	}
	if (negative)	sign = '-';
	else if (is_signed && spec->flag_plus)	sign = '+';
	else if (is_signed && spec->flag_space)	sign = ' ';
	length = (sign ? 1 : 0) + prefix_len + zeros + ndigits;
	padding = (spec->has_width && spec->width > length ? spec->width - length : 0);
	if (spec->flag_zero && !spec->flag_minus && !spec->has_precision)
	{	// the '0' flag pads with leading zeros (after any sign/prefix), and is ignored if a precision is given
		zeros += padding;
		padding = 0;
	}
	if (!spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
	if (sign)
		Format_WriteChar(out, sign);
	Format_Write(out, prefix, prefix_len);
	Format_WriteRepeat(out, '0', zeros);
	for (i = ndigits; i--; )
		Format_WriteChar(out, digits[i]);
	if (spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
}



/*============================================================================*\
||                               String conversions                           ||
\*============================================================================*/

//! Returns the length of the given string, reading at most `max` chars (like `strnlen()`)
static
t_size	Format_StringLength(t_char const* str, t_bool has_max, t_size max)
{
	t_size	i = 0;

	while (str[i] != '\0' && !(has_max && i >= max))
		i += 1;
	return (i);
}

//! Outputs a formatted string of `length` chars, with the appropriate width/justification handling
static
void	Format_WriteString(s_format_output* out, s_format_spec const* spec,
	t_char const* str, t_size length)
{
	t_size	padding;

	padding = (spec->has_width && spec->width > length ? spec->width - length : 0);
	if (!spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
	Format_Write(out, str, length);
	if (spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
}



/*============================================================================*\
||                          Floating-point conversions                        ||
\*============================================================================*/

#define FORMAT_MAXDIGITS_FLOAT	18	//!< the amount of significant decimal digits computed for floats

//! The decimal decomposition of a floating-point number: `0.[digits] * 10^(exp + 1)`
typedef struct format_float
{
	t_s64	exp;	//!< the decimal exponent of the first digit (ie: its power-of-ten "position")
	t_s64	count;	//!< the amount of significant digits stored in `digits`
	t_char	digits[FORMAT_MAXDIGITS_FLOAT];	//!< the significant decimal digits (most-significant first)
}	s_format_float;

//! Returns the decimal digit of `fd` which is at the given power-of-ten `position` (or `'0'`)
static
t_char	Format_Float_GetDigit(s_format_float const* fd, t_s64 position)
{
	t_s64	index = fd->exp - position;

	return ((index >= 0 && index < fd->count) ? fd->digits[index] : '0');
}

//! Decomposes the given positive, finite, floating-point number into its decimal digits
static
void	Format_Float_Decompose(s_format_float* fd, long double value)
{
	t_u64	mantissa;
	t_u64	divisor;
	t_s64	i;

	fd->exp = 0;
	fd->count = FORMAT_MAXDIGITS_FLOAT;
	if (value == 0)
	{
		fd->count = 1;
		fd->digits[0] = '0';
		return;
	}
	// normalize `value` into the interval [1, 10) - keeping track of the decimal exponent
	while (value >= 1e32L)	{	value /= 1e32L;	fd->exp += 32;	}
	while (value >= 10)	{	value /= 10;	fd->exp += 1;	}
	while (value < 1e-32L)	{	value *= 1e32L;	fd->exp -= 32;	}
	while (value < 1)	{	value *= 10;	fd->exp -= 1;	}
	// extract the 18 most significant decimal digits into a `t_u64` (rounding the last digit)
	mantissa = (t_u64)(value * 1e17L + 0.5L);
	if (mantissa >= (t_u64)1000000000000000000llu)
	{	// the rounding of the last digit carried over: `value` was ~9.9999999...
		mantissa /= 10;
		fd->exp += 1;
	}
	divisor = (t_u64)100000000000000000llu;
	for (i = 0; i < FORMAT_MAXDIGITS_FLOAT; ++i)
	{
		fd->digits[i] = (t_char)('0' + (mantissa / divisor) % 10);
		divisor /= 10;
	}
}

//! Rounds the given float decimal decomposition to only keep `n` significant digits
/*!
**	Performs "round-half-away-from-zero" rounding upon the digits of `fd`,
**	such that only `n` significant digits remain (`fd->count` is updated).
**	NOTE: if the rounding carries beyond the first digit (eg: `9.97 -> 10.0`),
**	then `fd->exp` will be incremented accordingly.
*/
static
void	Format_Float_Round(s_format_float* fd, t_s64 n)
{
	t_bool	round_up;
	t_s64	i;

	if (n >= fd->count)
		return;
	if (n < 0)
	{	// the requested precision is such that no digit of `fd` can appear in the output
		fd->count = 0;
		return;
	}
	round_up = (fd->digits[n] >= '5');
	fd->count = n;
	if (!round_up)
		return;
	i = n - 1;
	while (i >= 0 && fd->digits[i] == '9')
	{
		fd->digits[i] = '0';
		i -= 1;
	}
	if (i >= 0)
		fd->digits[i] += 1;
	else
	{	// the round-up carried over beyond the first digit: (eg: 9.99 -> 10.0)
		if (fd->count == 0)
			fd->count = 1;
		fd->digits[0] = '1';
		for (i = 1; i < fd->count; ++i)
			fd->digits[i] = '0';
		fd->exp += 1;
	}
}

//! Outputs the common "padded number" scaffolding around a float body of `length` chars
/*!
**	Handles the sign char, width, and padding flags, which are common logic
**	for every float notation. Returns the amount of leading zeros to write
**	(the caller is expected to write the body of the number right after this call).
*/
static
t_size	Format_Float_WritePadding(s_format_output* out, s_format_spec const* spec,
	t_char sign, t_size length)
{
	t_size	padding;
	t_size	zeros = 0;

	length += (sign ? 1 : 0);
	padding = (spec->has_width && spec->width > length ? spec->width - length : 0);
	if (spec->flag_zero && !spec->flag_minus)
	{
		zeros = padding;
		padding = 0;
	}
	if (!spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
	if (sign)
		Format_WriteChar(out, sign);
	return (zeros);
}

//! Outputs a formatted floating-point number, in fixed-point decimal notation (ie: `%f`)
static
void	Format_WriteFloat_Dec(s_format_output* out, s_format_spec const* spec,
	t_char sign, s_format_float* fd, t_size precision)
{
	t_bool	point = (precision > 0 || spec->flag_hash);
	t_size	length;
	t_size	zeros;
	t_s64	position;
	t_s64	int_max;

	Format_Float_Round(fd, fd->exp + 1 + (t_s64)precision);
	int_max = (fd->exp > 0 ? fd->exp : 0);
	length = (t_size)(int_max + 1) + (point ? 1 : 0) + precision;
	zeros = Format_Float_WritePadding(out, spec, sign, length);
	Format_WriteRepeat(out, '0', zeros);
	for (position = int_max; position >= 0; --position)
		Format_WriteChar(out, Format_Float_GetDigit(fd, position));
	if (point)
		Format_WriteChar(out, '.');
	for (position = -1; position >= -(t_s64)precision; --position)
		Format_WriteChar(out, Format_Float_GetDigit(fd, position));
	if (spec->flag_minus && spec->has_width)
	{
		length += (sign ? 1 : 0);
		if (spec->width > length)
			Format_WriteRepeat(out, ' ', spec->width - length);
	}
}

//! Outputs a formatted floating-point number, in scientific/exponent notation (ie: `%e`)
static
void	Format_WriteFloat_Exp(s_format_output* out, s_format_spec const* spec,
	t_char sign, s_format_float* fd, t_size precision, t_bool uppercase)
{
	t_char	expdigits[FORMAT_MAXDIGITS_UINT];
	t_size	expcount;
	t_bool	point = (precision > 0 || spec->flag_hash);
	t_size	length;
	t_size	zeros;
	t_s64	exponent;
	t_size	i;

	Format_Float_Round(fd, (t_s64)precision + 1);
	exponent = (fd->count == 0 ? 0 : fd->exp);
	expcount = Format_ConvertUInt(expdigits,
		(t_u64)(exponent < 0 ? -exponent : exponent), 10, FALSE);
	if (expcount < 2)
		expdigits[expcount++] = '0';	// the exponent always has at least 2 digits
	length = 1 + (point ? 1 : 0) + precision + 2 + expcount;
	zeros = Format_Float_WritePadding(out, spec, sign, length);
	Format_WriteRepeat(out, '0', zeros);
	Format_WriteChar(out, Format_Float_GetDigit(fd, fd->exp));
	if (point)
		Format_WriteChar(out, '.');
	for (i = 1; i <= precision; ++i)
		Format_WriteChar(out, Format_Float_GetDigit(fd, fd->exp - (t_s64)i));
	Format_WriteChar(out, uppercase ? 'E' : 'e');
	Format_WriteChar(out, exponent < 0 ? '-' : '+');
	for (i = expcount; i--; )
		Format_WriteChar(out, expdigits[i]);
	if (spec->flag_minus && spec->has_width)
	{
		length += (sign ? 1 : 0);
		if (spec->width > length)
			Format_WriteRepeat(out, ' ', spec->width - length);
	}
}

//! Outputs a formatted floating-point number, in "shortest representation" notation (ie: `%g`)
static
void	Format_WriteFloat_Any(s_format_output* out, s_format_spec const* spec,
	t_char sign, s_format_float* fd, t_size precision, t_bool uppercase)
{
	t_s64	sigdigits = (t_s64)(precision == 0 ? 1 : precision);
	t_s64	exponent;

	Format_Float_Round(fd, sigdigits);
	if (!spec->flag_hash)
	{	// strip any trailing zero decimal digits
		while (fd->count > 1 && fd->digits[fd->count - 1] == '0')
			fd->count -= 1;
	}
	exponent = (fd->count == 0 ? 0 : fd->exp);
	if (exponent < -4 || exponent >= sigdigits)
	{
		precision = (t_size)(spec->flag_hash ?
			sigdigits - 1 :
			(fd->count > 1 ? fd->count - 1 : 0));
		Format_WriteFloat_Exp(out, spec, sign, fd, precision, uppercase);
	}
	else
	{
		if (spec->flag_hash)
			precision = (t_size)(sigdigits - 1 - exponent);
		else
		{
			precision = (t_size)(fd->count - 1 - exponent > 0 ?
				fd->count - 1 - exponent : 0);
		}
		Format_WriteFloat_Dec(out, spec, sign, fd, precision);
	}
}

#define FORMAT_MAXDIGITS_FLOATHEX	32	//!< enough hex digits for a 128-bit float mantissa

//! Outputs a formatted floating-point number, in hexadecimal notation (ie: `%a`)
/*!
**	NOTE: unlike the decimal notations, this conversion is exact: scaling a binary
**	floating-point number by powers of two, and subtracting its integer part,
**	are both lossless operations, so the hexadecimal mantissa digits are exact.
*/
static
void	Format_WriteFloat_Hex(s_format_output* out, s_format_spec const* spec,
	t_char sign, long double value, t_bool has_precision, t_size precision, t_bool uppercase)
{
	static t_char const	digits_lowercase[16+1] = "0123456789abcdef";
	static t_char const	digits_uppercase[16+1] = "0123456789ABCDEF";
	t_char const*	charset = (uppercase ? digits_uppercase : digits_lowercase);
	t_char	mantissa[FORMAT_MAXDIGITS_FLOATHEX];
	t_char	expdigits[FORMAT_MAXDIGITS_UINT];
	t_size	expcount;
	t_size	count = 0;
	t_s64	exponent = 0;
	t_char	leading;
	t_bool	point;
	t_size	length;
	t_size	zeros;
	t_size	i;
	t_u8	digit;

	if (value != 0)
	{	// normalize `value` into the interval [1, 2) - keeping track of the binary exponent
		while (value >= 0x1p+32L)	{	value /= 0x1p+32L;	exponent += 32;	}
		while (value >= 2)	{	value /= 2;	exponent += 1;	}
		while (value < 0x1p-32L)	{	value *= 0x1p+32L;	exponent -= 32;	}
		while (value < 1)	{	value *= 2;	exponent -= 1;	}
	}
	leading = (t_char)('0' + (t_s64)value);
	value -= (t_s64)value;
	while (count < FORMAT_MAXDIGITS_FLOATHEX && value != 0 &&
		!(has_precision && count >= precision + 1))
	{	// extract the hexadecimal digits of the mantissa, one by one (this is exact)
		value *= 16;
		digit = (t_u8)value;
		value -= digit;
		mantissa[count++] = charset[digit];
	}
	if (has_precision)
	{
		if (count > precision)
		{	// round the digit string to `precision` hexadecimal digits
			t_bool	round_up = (mantissa[precision] >= '8');
			count = precision;
			if (round_up)
			{
				i = count;
				while (i-- > 0)
				{
					if (mantissa[i] == 'f' || mantissa[i] == 'F')
						mantissa[i] = '0';
					else
					{
						mantissa[i] = (mantissa[i] == '9' ? charset[10] : mantissa[i] + 1);
						break;
					}
				}
				if (i >= count)	// unsigned wrap: the carry went beyond the first mantissa digit
					leading += 1;
			}
		}
		while (count < precision)
			mantissa[count++] = '0';
	}
	point = (count > 0 || spec->flag_hash);
	expcount = Format_ConvertUInt(expdigits,
		(t_u64)(exponent < 0 ? -exponent : exponent), 10, FALSE);
	length = 2 + 1 + (point ? 1 : 0) + count + 2 + expcount;
	zeros = Format_Float_WritePadding(out, spec, sign, length);
	Format_WriteChar(out, '0');
	Format_WriteChar(out, uppercase ? 'X' : 'x');
	Format_WriteRepeat(out, '0', zeros);
	Format_WriteChar(out, leading);
	if (point)
		Format_WriteChar(out, '.');
	Format_Write(out, mantissa, count);
	Format_WriteChar(out, uppercase ? 'P' : 'p');
	Format_WriteChar(out, exponent < 0 ? '-' : '+');
	for (i = expcount; i--; )
		Format_WriteChar(out, expdigits[i]);
	if (spec->flag_minus && spec->has_width)
	{
		length += (sign ? 1 : 0);
		if (spec->width > length)
			Format_WriteRepeat(out, ' ', spec->width - length);
	}
}

//! Outputs a formatted floating-point number, dispatching to the appropriate notation
static
void	Format_WriteFloat(s_format_output* out, s_format_spec const* spec,
	t_char conversion, long double value)
{
	s_format_float	fd;
	t_bool	uppercase = (conversion >= 'A' && conversion <= 'Z');
	t_char	sign = '\0';
	t_size	precision;

	if (value != value)	// NAN
	{
		t_char const*	str = (uppercase ? "NAN" : "nan");
		t_char	buffer[4];
		t_size	length = 3;
		if (__builtin_signbitl(value))	sign = '-';
		else if (spec->flag_plus)	sign = '+';
		else if (spec->flag_space)	sign = ' ';
		if (sign)
		{
			buffer[0] = sign;
			buffer[1] = str[0];	buffer[2] = str[1];	buffer[3] = str[2];
			str = buffer;
			length = 4;
		}
		Format_WriteString(out, spec, str, length);
		return;
	}
	if (__builtin_signbitl(value))	// NOTE: handles negative zero, unlike `(value < 0)`
	{
		sign = '-';
		value = -value;
	}
	else if (spec->flag_plus)	sign = '+';
	else if (spec->flag_space)	sign = ' ';
	if (value != 0 && value / 2 == value)	// INFINITY
	{
		t_char const*	str = (uppercase ? "INF" : "inf");
		t_char	buffer[4];
		t_size	length = 3;
		if (sign)
		{
			buffer[0] = sign;
			buffer[1] = str[0];	buffer[2] = str[1];	buffer[3] = str[2];
			str = buffer;
			length = 4;
		}
		Format_WriteString(out, spec, str, length);
		return;
	}
	precision = (spec->has_precision ? spec->precision : 6);
	switch (conversion)
	{
		case 'f': case 'F':
			Format_Float_Decompose(&fd, value);
			Format_WriteFloat_Dec(out, spec, sign, &fd, precision);
			break;
		case 'e': case 'E':
			Format_Float_Decompose(&fd, value);
			Format_WriteFloat_Exp(out, spec, sign, &fd, precision, uppercase);
			break;
		case 'g': case 'G':
			Format_Float_Decompose(&fd, value);
			Format_WriteFloat_Any(out, spec, sign, &fd, precision, uppercase);
			break;
		case 'a': case 'A':
			Format_WriteFloat_Hex(out, spec, sign, value,
				spec->has_precision, spec->precision, uppercase);
			break;
		default: break;
	}
}



/*============================================================================*\
||                           Fixed-point conversions                          ||
\*============================================================================*/

#define FORMAT_FIXED_MAXDIGITS_FRACTION	16	//!< the maximum amount of hex digits output for a fixed-point fraction part

//! Outputs a formatted fixed-point number, in hexadecimal notation (ie: `%k`/`%K`)
/*!
**	The output notation is `[-]0x[integerpart].[fractionpart]`, where both the
**	integer part and fraction part digits are written in hexadecimal.
**	The precision field sets the amount of fraction digits to output (with rounding);
**	if no precision is given, digits are output until the fraction is expressed
**	exactly (with a maximum of #FORMAT_FIXED_MAXDIGITS_FRACTION digits).
*/
static
void	Format_WriteFixed_Hex(s_format_output* out, s_format_spec const* spec,
	t_fixed value, t_bool uppercase)
{
	static t_char const	digits_lowercase[16+1] = "0123456789abcdef";
	static t_char const	digits_uppercase[16+1] = "0123456789ABCDEF";
	t_char const*	charset = (uppercase ? digits_uppercase : digits_lowercase);
	t_char	digits[FORMAT_MAXDIGITS_UINT];
	t_char	fraction[FORMAT_FIXED_MAXDIGITS_FRACTION];
	t_size	ndigits;
	t_size	count = 0;
	t_size	amount;
	t_bool	negative;
	t_bool	point;
	t_u64	denom = (t_u64)CONCAT(FIXED_TYPE,_DENOM);
	t_u64	part_i;
	t_u64	part_f;
	t_size	length;
	t_size	zeros;
	t_size	i;
	t_s64	raw;

#if LIBCONFIG_USE_STD_FIXEDPOINT
	raw = (t_s64)((long double)value * (long double)denom);
#else
	raw = (t_s64)value._;
#endif
	negative = (raw < 0);
	part_i = (t_u64)(negative ? -raw : raw);
	part_f = part_i % denom;
	part_i = part_i / denom;
	amount = (spec->has_precision ?
		(spec->precision < FORMAT_FIXED_MAXDIGITS_FRACTION ?
			spec->precision : FORMAT_FIXED_MAXDIGITS_FRACTION) :
		FORMAT_FIXED_MAXDIGITS_FRACTION);
	while (count < amount && !(count > 0 && part_f == 0 && !spec->has_precision))
	{	// extract the hexadecimal digits of the fraction part, one by one
		part_f *= 16;
		fraction[count++] = charset[part_f / denom];
		part_f %= denom;
	}
	if (part_f * 2 >= denom)
	{	// round the last fraction digit (carry can propagate into the integer part)
		i = count;
		while (i-- > 0)
		{
			if (fraction[i] == 'f' || fraction[i] == 'F')
				fraction[i] = '0';
			else
			{
				fraction[i] = (fraction[i] == '9' ? charset[10] : fraction[i] + 1);
				break;
			}
		}
		if (i >= count)	// unsigned wrap: the carry went beyond the first fraction digit
			part_i += 1;
	}
	if (!spec->has_precision)
	{	// strip any trailing zero fraction digits
		while (count > 1 && fraction[count - 1] == '0')
			count -= 1;
		if (count == 1 && fraction[0] == '0')
			count = 0;
	}
	ndigits = Format_ConvertUInt(digits, part_i, 16, uppercase);
	point = (count > 0 || spec->flag_hash);
	length = 2 + ndigits + (point ? 1 : 0) + count;
	zeros = Format_Float_WritePadding(out, spec,
		(negative ? '-' : (spec->flag_plus ? '+' : (spec->flag_space ? ' ' : '\0'))), length);
	Format_WriteChar(out, '0');
	Format_WriteChar(out, uppercase ? 'X' : 'x');
	Format_WriteRepeat(out, '0', zeros);
	for (i = ndigits; i--; )
		Format_WriteChar(out, digits[i]);
	if (point)
		Format_WriteChar(out, '.');
	Format_Write(out, fraction, count);
	if (spec->flag_minus && spec->has_width)
	{
		length += (negative || spec->flag_plus || spec->flag_space ? 1 : 0);
		if (spec->width > length)
			Format_WriteRepeat(out, ' ', spec->width - length);
	}
}



/*============================================================================*\
||                          Custom-specifier conversions                      ||
\*============================================================================*/

#define FORMAT_MAXLENGTH_ESCAPECHAR	16	//!< enough space to escape any single char (at most `\UFFFFFFFF` + `'\0'`)

//! Outputs a single char, with non-printable characters shown as escape-sequences (ie: `%C`)
//! Manually escapes a single byte, writing at most 4 chars to `dest` - returns the amount written
/*!
**	This fallback is used for bytes which the libccc escape API cannot process
**	(ie: bytes which do not form a valid text encoding sequence): any such byte
**	is displayed in `\xFF`-style hexadecimal notation, rather than being dropped.
*/
static
t_size	Format_EscapeByte(t_char* dest, t_u8 c)
{
	static t_char const	charset[16+1] = "0123456789ABCDEF";

	dest[0] = '\\';
	dest[1] = 'x';
	dest[2] = charset[c >> 4];
	dest[3] = charset[c & 0xF];
	return (4);
}

static
void	Format_WriteEscapedChar(s_format_output* out, s_format_spec const* spec, t_char c)
{
	t_char	escaped[FORMAT_MAXLENGTH_ESCAPECHAR] = {0};
	t_char	str[2] = {0};
	t_size	length;

	if (c == '\0')
	{	// special case: a string cannot hold a '\0' char, so it is escaped manually here
		escaped[0] = '\\';
		escaped[1] = '0';
		length = 2;
	}
	else if ((t_u8)c >= 0x80)
	{	// a single byte >= 0x80 can never be a valid UTF-8 sequence: escape it manually
		length = Format_EscapeByte(escaped, (t_u8)c);
	}
	else
	{
		str[0] = c;
		length = StringASCII_ToASCIIEscapedBuf(escaped, sizeof(escaped), str);
		if (length == SIZE_ERROR || length >= sizeof(escaped))
		{	// the escape API cannot process this byte: escape it manually
			length = Format_EscapeByte(escaped, (t_u8)c);
		}
	}
	if (spec->has_precision && length > spec->precision)
		length = spec->precision;
	Format_WriteString(out, spec, escaped, length);
}

//! Manual fallback for Format_WriteEscapedString(), used when the escape API fails
/*!
**	Escapes the given string byte-by-byte: printable ASCII chars are output as-is,
**	standard C escape sequences are used where applicable, and any other byte
**	(including invalid text encoding sequences) is shown as `\xFF`-style hexadecimal.
*/
static
void	Format_WriteEscapedString_Fallback(s_format_output* out, s_format_spec const* spec, t_char const* str)
{
	t_char*	escaped;
	t_size	length = 0;
	t_size	i;

	for (i = 0; str[i] != '\0'; ++i)
		;
	escaped = (t_char*)Memory_Allocate((i * 4 + 1) * sizeof(t_char)); // worst case: 4 chars per byte
	if CCCERROR((escaped == NULL), ERROR_ALLOCFAILURE, NULL)
		return;
	for (i = 0; str[i] != '\0'; ++i)
	{
		t_u8	c = (t_u8)str[i];
		switch (c)
		{
			case '\\':	escaped[length++] = '\\';	escaped[length++] = '\\';	break;
			case '\a':	escaped[length++] = '\\';	escaped[length++] = 'a';	break;
			case '\b':	escaped[length++] = '\\';	escaped[length++] = 'b';	break;
			case '\t':	escaped[length++] = '\\';	escaped[length++] = 't';	break;
			case '\n':	escaped[length++] = '\\';	escaped[length++] = 'n';	break;
			case '\v':	escaped[length++] = '\\';	escaped[length++] = 'v';	break;
			case '\f':	escaped[length++] = '\\';	escaped[length++] = 'f';	break;
			case '\r':	escaped[length++] = '\\';	escaped[length++] = 'r';	break;
			case 0x1B:	escaped[length++] = '\\';	escaped[length++] = 'e';	break;
			default:
			{
				if (c >= 0x20 && c < 0x7F)
					escaped[length++] = (t_char)c;
				else length += Format_EscapeByte(escaped + length, c);
				break;
			}
		}
	}
	escaped[length] = '\0';
	if (spec->has_precision && length > spec->precision)
		length = spec->precision;
	Format_WriteString(out, spec, escaped, length);
	Memory_Free(escaped);
}

//! Outputs a string, with non-printable characters shown as escape-sequences (ie: `%S`)
static
void	Format_WriteEscapedString(s_format_output* out, s_format_spec const* spec, t_char const* str)
{
	t_char*	escaped;
	t_size	max_writelen;
	t_size	length;

	if (str == NULL)
	{
		Format_WriteString(out, spec, "(null)", 6);
		return;
	}
	if (str[0] == '\0' || (spec->has_precision && spec->precision == 0))
	{	// empty string, or zero-length truncation: still apply any `min_size` width padding
		Format_WriteString(out, spec, "", 0);
		return;
	}
	// NOTE: the `+ 1` is because the "escaped buf" length limit includes the final '\0'
	max_writelen = (spec->has_precision ? spec->precision + 1 : SIZE_ERROR);
	length = StringASCII_ToASCIIEscapedBuf(NULL, max_writelen, str);
	if (length == SIZE_ERROR)
	{	// the escape API cannot process this string: escape it manually, byte-by-byte
		Format_WriteEscapedString_Fallback(out, spec, str);
		return;
	}
	escaped = (t_char*)Memory_Allocate((length + 1) * sizeof(t_char));
	if CCCERROR((escaped == NULL), ERROR_ALLOCFAILURE, NULL)
		return;
	length = StringASCII_ToASCIIEscapedBuf(escaped, length + 1, str);
	if (length != SIZE_ERROR)
		Format_WriteString(out, spec, escaped, length);
	Memory_Free(escaped);
}

//! Outputs a region of memory, as hexadecimal byte values (ie: `%m`)
/*!
**	The precision field gives the amount of bytes of memory to display
**	(when no precision field is given, no bytes are shown).
**	The `#` flag adds a "0x" prefix in front of the byte values.
*/
static
void	Format_WriteMemory(s_format_output* out, s_format_spec const* spec, t_u8 const* ptr)
{
	static t_char const	charset[16+1] = "0123456789ABCDEF";
	t_size	amount = (spec->has_precision ? spec->precision : 0);
	t_size	length;
	t_size	padding;
	t_size	i;

	if (ptr == NULL)
		amount = 0;
	length = (spec->flag_hash ? 2 : 0) + (amount * 2);
	padding = (spec->has_width && spec->width > length ? spec->width - length : 0);
	if (!spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
	if (spec->flag_hash)
	{
		Format_WriteChar(out, '0');
		Format_WriteChar(out, 'x');
	}
	for (i = 0; i < amount; ++i)
	{
		Format_WriteChar(out, charset[(ptr[i] >> 4) & 0xF]);
		Format_WriteChar(out, charset[(ptr[i] >> 0) & 0xF]);
	}
	if (spec->flag_minus)
		Format_WriteRepeat(out, ' ', padding);
}



/*============================================================================*\
||                              Core format engine                            ||
\*============================================================================*/

//! Fetches a signed integer variadic argument, according to the given `bitsize` field value
static
t_s64	Format_ArgSInt(va_list* args, e_format_sizespec size)
{
	switch (size)
	{
		case FORMATSIZE_HH:	return ((t_s64)(t_s8)va_arg(*args, int));
		case FORMATSIZE_H:	return ((t_s64)(t_s16)va_arg(*args, int));
		case FORMATSIZE_L:	return ((t_s64)va_arg(*args, long));
		case FORMATSIZE_LL:	return ((t_s64)va_arg(*args, long long));
		case FORMATSIZE_J:	return ((t_s64)va_arg(*args, t_s64));
		case FORMATSIZE_Z:	return ((t_s64)va_arg(*args, t_size));
		case FORMATSIZE_T:	return ((t_s64)va_arg(*args, t_ptrdiff));
		default:	return ((t_s64)va_arg(*args, int));
	}
}

//! Fetches an unsigned integer variadic argument, according to the given `bitsize` field value
static
t_u64	Format_ArgUInt(va_list* args, e_format_sizespec size)
{
	switch (size)
	{
		case FORMATSIZE_HH:	return ((t_u64)(t_u8)va_arg(*args, unsigned int));
		case FORMATSIZE_H:	return ((t_u64)(t_u16)va_arg(*args, unsigned int));
		case FORMATSIZE_L:	return ((t_u64)va_arg(*args, unsigned long));
		case FORMATSIZE_LL:	return ((t_u64)va_arg(*args, unsigned long long));
		case FORMATSIZE_J:	return ((t_u64)va_arg(*args, t_u64));
		case FORMATSIZE_Z:	return ((t_u64)va_arg(*args, t_size));
		case FORMATSIZE_T:	return ((t_u64)va_arg(*args, t_ptrdiff));
		default:	return ((t_u64)va_arg(*args, unsigned int));
	}
}

//! The core format-string engine: parses `format`, writing the output to `out`
static
void	Format_Engine(s_format_output* out, t_char const* format, va_list* args)
{
	s_format_spec	spec;
	t_char	conversion;
	t_size	speclen;
	t_size	length;
	t_size	i = 0;
	t_s64	svalue;
	t_u64	uvalue;

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			Format_WriteChar(out, format[i++]);
			continue;
		}
		i += 1;	// skip the '%' char
		speclen = Format_ParseSpec(&spec, format + i, args);
		conversion = format[i + speclen];
		switch (conversion)
		{
			case '%':
			{
				Format_WriteChar(out, '%');
				break;
			}
			case 'd': case 'i':
			{
				svalue = Format_ArgSInt(args, spec.size);
				Format_WriteInteger(out, &spec, TRUE, (svalue < 0),
					(svalue < 0 ? -(t_u64)svalue : (t_u64)svalue), 10, FALSE);
				break;
			}
			case 'u':
			{
				uvalue = Format_ArgUInt(args, spec.size);
				Format_WriteInteger(out, &spec, FALSE, FALSE, uvalue, 10, FALSE);
				break;
			}
			case 'o':
			{
				uvalue = Format_ArgUInt(args, spec.size);
				Format_WriteInteger(out, &spec, FALSE, FALSE, uvalue, 8, FALSE);
				break;
			}
			case 'x': case 'X':
			{
				uvalue = Format_ArgUInt(args, spec.size);
				Format_WriteInteger(out, &spec, FALSE, FALSE, uvalue, 16, (conversion == 'X'));
				break;
			}
			case 'b':	// libccc extension: unsigned binary integer
			{
				uvalue = Format_ArgUInt(args, spec.size);
				Format_WriteInteger(out, &spec, FALSE, FALSE, uvalue, 2, FALSE);
				break;
			}
			case 'B':	// libccc extension: boolean ("TRUE" or "FALSE")
			{
				t_char const*	str = Bool_String((t_bool)(va_arg(*args, int) != 0), TRUE);
				length = Format_StringLength(str, spec.has_precision, spec.precision);
				Format_WriteString(out, &spec, str, length);
				break;
			}
			case 'f': case 'F':
			case 'e': case 'E':
			case 'g': case 'G':
			case 'a': case 'A':
			{
				long double	fvalue = (spec.size == FORMATSIZE_CAPL ?
					va_arg(*args, long double) :
					(long double)va_arg(*args, double));
				Format_WriteFloat(out, &spec, conversion, fvalue);
				break;
			}
			case 'c':
			{
				t_char	c = (t_char)va_arg(*args, int);
				Format_WriteString(out, &spec, &c, 1);
				break;
			}
			case 'C':	// libccc extension: char, escaping any non-printable characters
			{
				Format_WriteEscapedChar(out, &spec, (t_char)va_arg(*args, int));
				break;
			}
			case 's':
			{
				t_char const*	str = va_arg(*args, t_char const*);
				if (str == NULL)
					str = "(null)";
				length = Format_StringLength(str, spec.has_precision, spec.precision);
				Format_WriteString(out, &spec, str, length);
				break;
			}
			case 'S':	// libccc extension: string, escaping any non-printable characters
			{
				Format_WriteEscapedString(out, &spec, va_arg(*args, t_char const*));
				break;
			}
			case 'p':
			{
				uvalue = (t_u64)(t_uintptr)va_arg(*args, void const*);
				spec.flag_hash = TRUE;	// the "0x" prefix is always shown for pointers
				if (uvalue == 0)
					Format_WriteString(out, &spec, "0x0", 3);
				else Format_WriteInteger(out, &spec, FALSE, FALSE, uvalue, 16, FALSE);
				break;
			}
			case 'q':	// libccc extension: fixed-point number, decimal notation
			{
				t_fixed	fixed = va_arg(*args, t_fixed);
				t_char*	str = Fixed_ToString(fixed);
				if CCCERROR((str == NULL), ERROR_ALLOCFAILURE, NULL)
					break;
				length = Format_StringLength(str, spec.has_precision, spec.precision);
				Format_WriteString(out, &spec, str, length);
				Memory_Free(str);
				break;
			}
			case 'k': case 'K':	// libccc extension: fixed-point number, hexadecimal notation
			{
				t_fixed	fixed = va_arg(*args, t_fixed);
				Format_WriteFixed_Hex(out, &spec, fixed, (conversion == 'K'));
				break;
			}
			case 'm':	// libccc extension: raw memory/data bytes, shown as hexadecimal
			{
				Format_WriteMemory(out, &spec, va_arg(*args, t_u8 const*));
				break;
			}
			case 'n':
			{
				switch (spec.size)
				{
					case FORMATSIZE_HH:	*va_arg(*args, t_s8*) = (t_s8)out->total;	break;
					case FORMATSIZE_H:	*va_arg(*args, t_s16*) = (t_s16)out->total;	break;
					case FORMATSIZE_L:	*va_arg(*args, long*) = (long)out->total;	break;
					case FORMATSIZE_LL:	*va_arg(*args, long long*) = (long long)out->total;	break;
					case FORMATSIZE_J:	*va_arg(*args, t_s64*) = (t_s64)out->total;	break;
					case FORMATSIZE_Z:	*va_arg(*args, t_size*) = out->total;	break;
					case FORMATSIZE_T:	*va_arg(*args, t_ptrdiff*) = (t_ptrdiff)out->total;	break;
					default:	*va_arg(*args, int*) = (int)out->total;	break;
				}
				break;
			}
			case '\0':	// a stray '%' at the very end of the format string: output it as-is
			{
				Format_Write(out, format + i - 1, speclen + 1);
				i += speclen;
				continue;
			}
			default:	// unknown conversion char: output the whole specifier text as-is
			{
				Format_Write(out, format + i - 1, speclen + 2);
				break;
			}
		}
		i += speclen + 1;	// skip the parsed specifier and conversion char
	}
	if (out->dest != NULL && out->max > 0)
		out->dest[out->total < out->max - 1 ? out->total : out->max - 1] = '\0';
}



/*============================================================================*\
||                           String Format Functions                          ||
\*============================================================================*/



t_char*	String_Format_VA(t_char const* format, va_list args)
{
	s_format_output	out = {0};
	va_list	args_copy;
	t_char*	result;

	if CCCERROR((format == NULL), ERROR_NULLPOINTER, "format string given is NULL")
		return (NULL);
	va_copy(args_copy, args);
	Format_Engine(&out, format, &args_copy);	// first pass: get the total output length
	va_end(args_copy);
	result = (t_char*)Memory_Allocate((out.total + 1) * sizeof(t_char));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	out.dest = result;
	out.max = out.total + 1;
	out.total = 0;
	va_copy(args_copy, args);
	Format_Engine(&out, format, &args_copy);	// second pass: write the output string
	va_end(args_copy);
	return (result);
}

t_char*	String_Format(t_char const* format, ...)
{
	t_char*	result;
	va_list	args;

	va_start(args, format);
	result = String_Format_VA(format, args);
	va_end(args);
	return (result);
}



t_size	String_Format_N_VA(t_char* dest, t_size max, t_char const* format, va_list args)
{
	s_format_output	out = {0};
	va_list	args_copy;

	if CCCERROR((format == NULL), ERROR_NULLPOINTER, "format string given is NULL")
		return (0);
	out.dest = dest;
	out.max = (dest == NULL ? 0 : max);
	va_copy(args_copy, args);
	Format_Engine(&out, format, &args_copy);
	va_end(args_copy);
	if (dest == NULL)
		return (out.total);	// `NULL` dest: simply return the total length
	if (max == 0)
		return (0);
	return (out.total < max - 1 ? out.total : max - 1);
}

t_size	String_Format_N(t_char* dest, t_size max, t_char const* format, ...)
{
	t_size	result;
	va_list	args;

	va_start(args, format);
	result = String_Format_N_VA(dest, max, format, args);
	va_end(args);
	return (result);
}
