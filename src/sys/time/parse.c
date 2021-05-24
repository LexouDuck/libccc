
#include "libccc/string.h"
#include "libccc/sys/io.h"
#include "libccc/sys/time.h"

#include LIBCONFIG_HANDLE_INCLUDE



#ifndef strptime
/*
**	Cross-platform implementation of strptime()
**	Courtesy of @Maxxim at https://stackoverflow.com/questions/40159892/using-asprintf-on-windows
*/

/*	$NetBSD: strptime.c,v 1.36 2012/03/13 21:13:48 christos Exp $	*/

/*
**	Copyright (c) 1997, 1998, 2005, 2008 The NetBSD Foundation, Inc.
**	All rights reserved.
**	
**	This code was contributed to The NetBSD Foundation by Klaus Klein.
**	Heavily optimised by David Laight
**	
**	Redistribution and use in source and binary forms, with or without
**	modification, are permitted provided that the following conditions
**	are met:
**	1. Redistributions of source code must retain the above copyright
**	 notice, this list of conditions and the following disclaimer.
**	2. Redistributions in binary form must reproduce the above copyright
**	 notice, this list of conditions and the following disclaimer in the
**	 documentation and/or other materials provided with the distribution.
**	
**	THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
**	``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
**	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
**	PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
**	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
**	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
**	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
**	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
**	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
**	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
**	POSSIBILITY OF SUCH DAMAGE.
*/

/* ************************************************************************** */
/*                                   Includes                                 */
/* ************************************************************************** */

#ifndef __NOSTD__
	#include <ctype.h>
	#include <locale.h>
	#include <string.h>
	#include <time.h>
	#include <stdint.h>
#else
	// TODO
	#define INT64_MAX	-1llu
	extern long	timezone;
	extern char* tzname[2];
	void tzset(void);
	void _tzset(void);
#endif
/*
#ifdef __weak_alias
__weak_alias(strptime,_strptime)
#endif
*/

/* ************************************************************************** */
/*                                 Definitions                                */
/* ************************************************************************** */

#define PARSINGERROR_DATE_MESSAGE	C_RED"DATE PARSE ERROR"C_RESET": "
//! used to handle errors during parsing
#define PARSINGERROR_DATE(MESSAGE, ...) \
	HANDLE_ERROR_MESSAGE(PARSE, (TRUE),	\
		return (0);,					\
		MESSAGE, __VA_ARGS__)			\



#ifndef TIME_MAX
#define TIME_MAX	INT64_MAX
#endif



typedef t_s16	t_bitmask_tm;

#define BITMASK_sec			0
#define BITMASK_min			1
#define BITMASK_hour		2
#define BITMASK_day_week	3
#define BITMASK_day_month	4
#define BITMASK_day_year	5
#define BITMASK_month		6
#define BITMASK_year		7
#define BITMASK_is_dst		8
#define BITMASK_offset		9

#define SET_TM(FIELD, VALUE) \
	date->FIELD = VALUE;	SET_WRITTEN(FIELD)

#ifdef TM_GMTOFF
#define BITMASK_tm_gmtoff	10
#define SET_TM_GMTOFF(X)	/* tm->offset = (X); 	SET_WRITTEN(tm_gmtoff) */
#else
#define SET_TM_GMTOFF(X)	
#endif

#ifdef TM_ZONE
#define BITMASK_tm_zone		11
#define SET_TM_ZONE(X)		/* tm->offset = (X); 	SET_WRITTEN(tm_zone) */
#else
#define SET_TM_ZONE(X)		
#endif

#define SET_WRITTEN(_FIELD_) \
	if (written) (*written) |= (1 << BITMASK_##_FIELD_)

#define HAS_WRITTEN(_FIELD_) \
	(written & (1 << BITMASK_##_FIELD_))

//! We do not implement alternate representations.
//! However, we always check whether a given modifier is allowed for a certain conversion.
#define ALT_E			0x01
#define ALT_O			0x02
#define	LEGAL_ALT(x)	{ if (alt_format & ~(x)) return (0); }

static t_char gmt[] = { "GMT" };
static t_char utc[] = { "UTC" };
/* RFC-822/RFC-2822 */
static t_char const*  const nast[5] =
{
	"EST",
	"CST",
	"MST",
	"PST",
	"\0\0\0"
};
static t_char const*  const nadt[5] =
{
	"EDT",
	"CDT",
	"MDT",
	"PDT",
	"\0\0\0"
};
static t_char const*  const am_pm[2] =
{
	"am",
	"pm",
};



static
t_s64	strptime_parsenumber(t_u8 const* *, t_uint, t_uint);
static
t_s64	strptime_parsestring(t_u8 const* *, t_char const* const*, t_char const* const*, t_sint);


static
t_s64	strptime_parsenumber(t_u8 const* *a_buffer, t_uint min, t_uint max)
{
	t_u8 const*	buffer = *a_buffer;
	t_uint result = 0;
	t_uint limit = max;	/* The limit also determines the number of valid digits. */
	t_u8 c;

	c = *buffer;
	if (!Char_IsDigit(c))
		goto failure;
	do
	{
		result *= 10;
		result += c - '0';
		limit /= 10;
		c = (++buffer)[0];
	}
	while ((result * 10 <= max) && limit && Char_IsDigit(c));

	if (result < min || result > max)
		goto failure;

//success:
	*a_buffer = buffer;
	return (result);

failure:
	*a_buffer = NULL;
	return (0);
}

static
t_s64	strptime_parsestring(t_u8 const* *a_buffer, t_char const* const* n1, t_char const* const* n2, t_sint c)
{
	t_u8 const*	buffer = *a_buffer;
	t_size length;
	t_sint i;

	/* check full name - then abbreviated ones */
	while (n1 != NULL)
	{
		for (i = 0; i < c; ++i, ++n1)
		{
			length = String_Length(*n1);
			if (String_Equals_N_IgnoreCase(*n1, (t_char const*)buffer, length))
			{
				*a_buffer = buffer + length;
				return (i);
			}
		}
		n1 = n2;
		n2 = NULL;
	}
	*a_buffer = NULL;
	return (0); /* Nothing matched */
}



static
t_size	strptime_r(t_char const* str, t_char const* format, s_date* date, t_bitmask_tm* written)
{
	t_u8 c;
	t_u8 const* buffer;
	t_u8 const* ep;
	t_char const* new_fmt;
	t_size length;
	t_sint alt_format;
	t_sint split_year = 0;
	t_sint offset;
	t_sint number = 0;
	t_sint neg = 0;
	t_sint i = 0;

	buffer = (t_u8 const*)str;

	while (buffer != NULL && (c = format[i++]) != '\0')
	{
		/* Clear `alternate' modifier prior to new conversion. */
		alt_format = 0;
		number = 0;
		/* Eat up white-space. */
		if (Char_IsSpace(c))
		{
			while (Char_IsSpace(*buffer))
			{
				buffer++;
			}
			continue;
		}
		if (c != '%')
		{
			if (c != (buffer++)[0])
				PARSINGERROR_DATE("The string to parse (\"%s\") did not match the given format (\"%s\").\n"
					"Expected '%c'/0x%X, instead found '%c'/0x%X", str, format,
					(format[i - 1] ? format[i - 1] : '\a'), format[i - 1],
					(c ? c : '\a'), c);
			LEGAL_ALT(0);
			continue;
		}

again:
		switch (c = format[i++])
		{
			case '%':	/* "%%" is converted to "%". */
			{
				if (c != (buffer++)[0])
					PARSINGERROR_DATE("The string to parse (\"%s\") did not match the given format (\"%s\"): "
						"expected '%c'/0x%X, instead found '%c'/0x%X", str, format,
						(format[i - 1] ? format[i - 1] : '\a'), format[i - 1],
						(c ? c : '\a'), c);
				LEGAL_ALT(0);
				continue;
			}
			/* "Alternative" modifiers. Just set the appropriate flag and start over again. */
			case 'E':	LEGAL_ALT(0);	alt_format |= ALT_E;	goto again;	// "%E?" alternative conversion modifier.
			case 'O':	LEGAL_ALT(0);	alt_format |= ALT_O;	goto again;	// "%O?" alternative conversion modifier.
/*!
** "Complex" conversion rules, implemented through recursion.
*/
/*			case 'c':	new_fmt = _CurrentTimeLocale->d_t_fmt;	goto recurse;	// Date and time, using the locale's format. */
			case 'D':	new_fmt = "%m/%d/%y";	LEGAL_ALT(0);	goto recurse;	// The date as "%m/%d/%y".
			case 'F':	new_fmt = "%Y-%m-%d";	LEGAL_ALT(0);	goto recurse;	// The date as "%Y-%m-%d".
			case 'R':	new_fmt = "%H:%M";		LEGAL_ALT(0);	goto recurse;	// The time as "%H:%M".
			case 'T':	new_fmt = "%H:%M:%S";	LEGAL_ALT(0);	goto recurse;	// The time as "%H:%M:%S".
			case 'r':	new_fmt = "%I:%M:S %p";	LEGAL_ALT(0);	goto recurse;	// The time in 12-hour clock representation. /* _CurrentTimeLocale->t_fmt_ampm */
/*			case 'X':	new_fmt = _CurrentTimeLocale->t_fmt;	goto recurse;	// The time, using the locale's format. */
/*			case 'x':	new_fmt = _CurrentTimeLocale->d_fmt;	goto recurse;	// The date, using the locale's format. */
recurse:
				length = strptime_r((t_char const*)buffer, new_fmt, date, written);
				buffer = (length == 0 ? NULL : buffer + length);
				LEGAL_ALT(ALT_E);
				continue;
/*!
** "Elementary" conversion rules.
*/
			case 'g':	/* The year corresponding to the ISO week number but without the century. */
			{
				number = strptime_parsenumber(&buffer, 0, 99);
				continue;
			}
			case 'G':	/* The year corresponding to the ISO week number with century. */
			{
				do { buffer++; } while (Char_IsDigit(*buffer));
				continue;
			}
			case 'Y':	/* The year. */
			{
				number = strptime_parsenumber(&buffer, 0, 9999);
				SET_TM(year, number);
				LEGAL_ALT(ALT_E);
				continue;
			}
			case 'y':	/* The year within 100 years of the epoch. */
			{
				/* LEGAL_ALT(ALT_E | ALT_O); */
				number = strptime_parsenumber(&buffer, 0, 99);
				if (split_year) /* preserve century */
				{
					number += (date->year / 100) * 100;
				}
				else
				{
					split_year = 1;
					number += ((number <= 68) ? 2000 : 1900);
				}
				SET_TM(year, number);
				continue;
			}

			case 'm':	/* The month. */
			{
				number = 1;
				number = strptime_parsenumber(&buffer, 1, ENUMLENGTH_MONTH);
				SET_TM(month, number - 1);
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'B':	/* The month, using the locale's form. */
			case 'b':
			case 'h':
			{
				SET_TM(month, strptime_parsestring(&buffer, g_month, g_month_abbreviated, ENUMLENGTH_MONTH));
				LEGAL_ALT(0);
				continue;
			}

			case 'd':	/* The day of month. */
			case 'e':
			{
				SET_TM(day_month, strptime_parsenumber(&buffer, 1, 31));
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'j':	/* The day of year. */
			{
				number = 1;
				number = strptime_parsenumber(&buffer, 1, 366);
				SET_TM(day_year, number - 1);
				LEGAL_ALT(0);
				continue;
			}

			case 'V':	/* The ISO 8601:1988 week number as decimal */
				number = strptime_parsenumber(&buffer, 0, 53);
				continue;
			case 'U':	/* The week of year, beginning on sunday. */
			case 'W':	/* The week of year, beginning on monday. */
				/* XXX This is bogus, as we can not assume any valid information present in the date structure */
				/* at this point to calculate a real value, so just check the range for now. */
				number = strptime_parsenumber(&buffer, 0, 53);
				LEGAL_ALT(ALT_O);
				continue;

			case 'w':	/* The day of week, beginning on sunday. */
			{
				SET_TM(day_week, strptime_parsenumber(&buffer, WEEKDAY_SUNDAY, WEEKDAY_SATURDAY));
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'u':	/* The day of week, monday = 1. */
			{
				number = strptime_parsenumber(&buffer, WEEKDAY_MONDAY, ENUMLENGTH_WEEKDAY);
				SET_TM(day_week, number % ENUMLENGTH_WEEKDAY);
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'A':	/* The day of week, using the locale's form. */
			case 'a':
			{
				SET_TM(day_week, strptime_parsestring(&buffer, g_weekday, g_weekday_abbreviated, ENUMLENGTH_WEEKDAY));
				LEGAL_ALT(0);
				continue;
			}



			case 'k':	LEGAL_ALT(0); /* FALLTHROUGH */	/* The hour (24-hour clock representation). */
			case 'H':   
			{
				SET_TM(hour, strptime_parsenumber(&buffer, 0, 23));
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'l':	LEGAL_ALT(0); /* FALLTHROUGH */	/* The hour (12-hour clock representation). */
			case 'I':
			{
				number = strptime_parsenumber(&buffer, 1, 12);
				SET_TM(hour, (number == 12 ? 0 : number));
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'M':	/* The minute. */
			{
				SET_TM(min, strptime_parsenumber(&buffer, 0, 59));
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'S':	/* The seconds. */
			{
				SET_TM(sec, strptime_parsenumber(&buffer, 0, 61));
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 's':	/* The seconds since the epoch */
			{
				time_t sse = 0;
				t_u64 limit = TIME_MAX;

				if (!Char_IsDigit(*buffer))
				{
					buffer = NULL;
					continue;
				}
				do
				{
					sse *= 10;
					sse += (buffer++)[0] - '0';
					limit /= 10;
				}
				while (limit && Char_IsDigit(*buffer)); // (sse * 10 <= TIME_MAX) && (...)

				if (sse < 0 || (t_u64)sse > TIME_MAX)
				{
					buffer = NULL;
					continue;
				}
				if (date == NULL)
					buffer = NULL;
				else
				{
					*date = Time_ToDate_LocalTime(sse);
					SET_WRITTEN(sec);
					SET_WRITTEN(min);
					SET_WRITTEN(hour);
					SET_WRITTEN(day_week);
					SET_WRITTEN(day_month);
					SET_WRITTEN(day_year);
					SET_WRITTEN(month);
					SET_WRITTEN(year);
					SET_WRITTEN(is_dst);
					SET_WRITTEN(offset);
				}
				continue;
			}



			case 'p':	/* The locale's equivalent of AM/PM. */
			{
				number = strptime_parsestring(&buffer, am_pm, NULL, 2);
				if (date->hour > 11)
					PARSINGERROR_DATE("AM/PM specifier cannot be with the given hour number (%i), should be below 12", date->hour)
				SET_TM(hour, date->hour + (number ? 12 : 0));
				LEGAL_ALT(0);
				continue;
			}



			case 'C':	/* The century number. */
			{
				number = 20;
				number = strptime_parsenumber(&buffer, 0, 99);
				number = number * 100;
				if (split_year)
					number += (date->year % 100);
				split_year = 1;
				SET_TM(year, number);
				LEGAL_ALT(ALT_E);
				continue;
			}



			case 'Z':
			{
#ifdef _WIN32
				_tzset();
#else
				tzset();
#endif
				if (String_Equals_N_IgnoreCase((t_char const*)buffer, gmt, 3) ||
					String_Equals_N_IgnoreCase((t_char const*)buffer, utc, 3))
				{
					SET_TM(is_dst, FALSE);
					SET_TM(offset, 0);
					SET_TM_GMTOFF(0);
					SET_TM_ZONE(gmt);
					buffer += 3;
				}
				else
				{
					ep = buffer;
					number = strptime_parsestring(&ep, (t_char const* const*)tzname, NULL, 2);
					if (ep != NULL)
					{
						SET_TM(is_dst, (t_bool)number);
						SET_TM(offset, -(timezone));
						SET_TM_GMTOFF(-(timezone));
						SET_TM_ZONE(tzname[number]);
					}
					buffer = ep;
				}
				continue;
			}

			case 'z':
			{
				/*
				**	We recognize all ISO 8601 formats:
				**		Z	= Zulu time/UTC
				**		[+-]hhmm
				**		[+-]hh:mm
				**		[+-]hh
				**	We recognize all RFC-822/RFC-2822 formats:
				**		UT|GMT
				**	North American : UTC offsets
				**		E[DS]T = Eastern : -4 | -5
				**		C[DS]T = Central : -5 | -6
				**		M[DS]T = Mountain: -6 | -7
				**		P[DS]T = Pacific : -7 | -8
				**	Military
				**		[A-IL-M] = -1 ... -9 (J not used)
				**		[N-Y]  = +1 ... +12
				*/
				while (Char_IsSpace(*buffer))
				{
					buffer++;
				}
				t_char x = '\0';
				switch ((x = (buffer++)[0]))
				{
					case 'G':	x = (buffer++)[0];	if (x != 'M')	PARSINGERROR_DATE("After 'G', expected 'M' char, instead found '%c'", x)	/*FALLTHROUGH*/
					case 'U':	x = (buffer++)[0];	if (x != 'T')	PARSINGERROR_DATE("After 'U', expected 'T' char, instead found '%c'", x)	/*FALLTHROUGH*/
					case 'Z':
						SET_TM(is_dst, FALSE);
						SET_TM(offset, 0);
						SET_TM_GMTOFF(0);
						SET_TM_ZONE(utc);
						continue;

					case '+':	neg = 0;	break;
					case '-':	neg = 1;	break;

					default:
						--buffer;
						ep = buffer;
						number = strptime_parsestring(&ep, nast, NULL, 4);
						if (ep != NULL)
						{
							SET_TM(offset, 0);
							SET_TM_GMTOFF(-5 - number);
							SET_TM_ZONE(__UNCONST(nast[number]));
							buffer = ep;
							continue;
						}
						ep = buffer;
						number = strptime_parsestring(&ep, nadt, NULL, 4);
						if (ep != NULL)
						{
							SET_TM(is_dst, TRUE);
							SET_TM_GMTOFF(-4 - number);
							SET_TM_ZONE(__UNCONST(nadt[number]));
							buffer = ep;
							continue;
						}
						x = *buffer;
						if ((x >= 'A' && x <= 'I') ||
							(x >= 'L' && x <= 'Y'))
						{
							/* Argh! No 'J'! */
							if (x >= 'A' && x <= 'I')		{ SET_TM(offset, ('A' - 1) - (t_sint)x);	SET_TM_GMTOFF(date->offset); }
							else if (x >= 'L' && x <= 'M')	{ SET_TM(offset, ('A' - (t_sint)x));		SET_TM_GMTOFF(date->offset); }
							else if (x >= 'N' && x <= 'Y')	{ SET_TM(offset, ((t_sint)x - 'M'));		SET_TM_GMTOFF(date->offset); }
							SET_TM_ZONE(NULL); /* XXX */
							buffer++;
							x = *buffer;
							continue;
						}
						PARSINGERROR_DATE("Invalid format specifier encountered ('%c'/0x%X) in the given format string (\"%s\")",
							(x ? x : '\a'), x, format)
				}
				offset = 0;
				for (number = 0; number < 4; )
				{
					if (Char_IsDigit(*buffer))
					{
						offset = offset * 10 + ((buffer++)[0] - '0');
						number++;
						continue;
					}
					if (number == 2 && *buffer == ':')
					{
						buffer++;
						continue;
					}
					break;
				}
				switch (number)
				{
					case 2:
					{
						offset *= 100;
						break;
					}
					case 4:
					{
						number = offset % 100;
						if (number >= 60)
							PARSINGERROR_DATE("Invalid timezone offset minutes number encountered (%i), should be 60 or less", number)
						/* Convert minutes into decimal */
						offset = (offset / 100) * 100 + (number * 50) / 30;
						break;
					}
					default:
					{
						PARSINGERROR_DATE("Invalid timezone offset encountered in the given format string (\"%s\")", format)
					}
				}
				if (neg)
				{
					offset = -offset;
				}
				SET_TM(is_dst, FALSE);
				SET_TM(offset, offset);
				SET_TM_GMTOFF(offset);
				SET_TM_ZONE(NULL);	/* XXX */
				continue;
			}
/*
** Miscellaneous conversions.
*/
		case 'n':	/* Any kind of white-space. */
		case 't':
			while (Char_IsSpace(*buffer))
				buffer++;
			LEGAL_ALT(0);
			continue;

		default:
			PARSINGERROR_DATE("Invalid format specifier encountered ('%c'/0x%X) in the given format string (\"%s\")",
				(c ? c : '\a'), c, format)
		}
	}
	return ((t_char*)buffer - str);
}

/*

static
t_char*	strptime(t_char const* str, t_char const* format, s_date* date)
{
	t_bitmask_tm written = 0;
	t_char* parse_end;

	parse_end = (t_char*)(str + strptime_r(str, format, date, &written));
	if (written == 0)
		return (NULL);
	return (parse_end);
}

*/

#endif

#include "libccc/sys/io.h"

static
t_size		Date_Parse_(s_date* dest, t_char const* str, t_char const* format, t_bool onlyknown, t_bool strict)
{
	s_date result = DATE_NULL;
	t_bitmask_tm written = 0;
	t_size	parsed;

	parsed = strptime_r(str, format, &result, &written);
	if (parsed == 0)
		return (0); // TODO handle parsing error here ?
	if (strict)
	{
		if (!Date_IsValid(&result))
			return (0);
	}
	t_uint leapsec = (result.sec >= TIME_MAX_SECONDS) ? (result.sec - (TIME_MAX_SECONDS - 1)) : 0;
	result.sec -= leapsec;
	if (!onlyknown)
	{
		if (HAS_WRITTEN(year) && HAS_WRITTEN(month))
		{
			if (HAS_WRITTEN(day_month) || HAS_WRITTEN(day_year))
			{
				if (HAS_WRITTEN(day_month) && !HAS_WRITTEN(day_year))
				{
					for (e_month i = 0; i < result.month; ++i)
					{
						result.day_year += Date_DaysInMonth(i, result.year);
					}
					result.day_year += result.day_month - 1;
				}
				if (HAS_WRITTEN(day_year) && !HAS_WRITTEN(day_month))
				{
					t_s32 day = result.day_year;
					e_month i = result.month;
					while (i--)
					{
						day -= Date_DaysInMonth(i, result.year);
					}
					result.day_month = day;
				}
				if (!HAS_WRITTEN(day_week))
				{
					result.day_week = Date_DayOfTheWeek(&result);
				}
			}
		}
	}
	result.sec += leapsec;
	*dest = result;
	return (parsed);
}



s_date		Date_Parse(t_char const* str, t_char const* format)
{
	s_date result = DATE_NULL;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (DATE_NULL);)
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (DATE_NULL);)
	Date_Parse_(&result, str, format, FALSE, FALSE);
	return (result);
}



s_date		Date_Parse_Min(t_char const* str, t_char const* format)
{
	s_date result = DATE_NULL;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (DATE_NULL);)
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (DATE_NULL);)
	Date_Parse_(&result, str, format, TRUE, FALSE);
	return (result);
}



t_size		Date_Parse_Strict(s_date* dest, t_char const* str, t_char const* format)
{
	s_date result = DATE_NULL;
	t_size parsed;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (0);)
	parsed = Date_Parse_(&result, str, format, FALSE, TRUE);
	*dest = result;
	return (parsed);
}



t_size		Date_Parse_Strict_Min(s_date* dest, t_char const* str, t_char const* format)
{
	s_date result = DATE_NULL;
	t_size parsed;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (format == NULL), return (0);)
	parsed = Date_Parse_(&result, str, format, TRUE, TRUE);
	*dest = result;
	return (parsed);
}
