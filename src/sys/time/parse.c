
#include "libccc/string.h"
#include "libccc/sys/time.h"



#ifndef strptime
/*
**	Cross-platform implementation of strptime()
**	Courtesy of @Maxxim at https://stackoverflow.com/questions/40159892/using-asprintf-on-windows
**
**	To be included BEFORE <time.h>
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
**	   notice, this list of conditions and the following disclaimer.
**	2. Redistributions in binary form must reproduce the above copyright
**	   notice, this list of conditions and the following disclaimer in the
**	   documentation and/or other materials provided with the distribution.
**	
**	THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
**	``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
**	TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
**	PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
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

/*
#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: strptime.c,v 1.36 2012/03/13 21:13:48 christos Exp $");
#endif

#include "namespace.h"
#include <sys/localedef.h>
*/
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
/*
#include <tzfile.h>
#include "private.h"

#ifdef __weak_alias
__weak_alias(strptime,_strptime)
#endif
*/

#include <inttypes.h>

/* ************************************************************************** */
/*                                 Definitions                                */
/* ************************************************************************** */

typedef unsigned int	uint;
typedef unsigned char	uchar;
//typedef unsigned __int64 uint64_t;

typedef t_s16	t_bitmask_tm;

#define BITMASK_tm_sec		tm_sec
#define BITMASK_tm_min		tm_min
#define BITMASK_tm_hour		tm_hour
#define BITMASK_tm_wday		tm_wday
#define BITMASK_tm_mday		tm_mday
#define BITMASK_tm_yday		tm_yday
#define BITMASK_tm_mon		tm_mon
#define BITMASK_tm_year		tm_year
#define BITMASK_tm_isdst	tm_isdst
#ifdef TM_GMTOFF
#define BITMASK_tm_gmtoff	tm_gmtoff
#define SET_TM_GMTOFF(X)	tm->tm_gmtoff = (X);
#else
#define SET_TM_GMTOFF(X)	
#endif
#ifdef TM_ZONE
#define BITMASK_tm_zone		tm_zone
#define SET_TM_ZONE(X)		tm->tm_zone = (X);
#else
#define SET_TM_ZONE(X)	
#endif

#define HAS_WRITTEN(FIELD) \
	((*written) & (1 << TM_BITMASK_##FIELD))



#ifndef TIME_MAX
#define TIME_MAX	INT64_MAX
#endif



//! We do not implement alternate representations.
//! However, we always check whether a given modifier is allowed for a certain conversion.
#define ALT_E			0x01
#define ALT_O			0x02
#define	LEGAL_ALT(x)	{ if (alt_format & ~(x)) return (NULL); }



static int TM_YEAR_BASE = 1900;
static char gmt[] = { "GMT" };
static char utc[] = { "UTC" };
/* RFC-822/RFC-2822 */
static char const*  const nast[5] =
{
	"EST",
	"CST",
	"MST",
	"PST",
	"\0\0\0"
};
static char const*  const nadt[5] =
{
	"EDT",
	"CDT",
	"MDT",
	"PDT",
	"\0\0\0"
};
static char const*  const am_pm[2] =
{
	"am",
	"pm"
};



static
uchar const* strptime_convert_number(uchar const* , int*, uint, uint);
static
uchar const* strptime_find_string(uchar const*, int*, char const* const*, char const* const*, int);


static
uchar const* strptime_convert_number(uchar const* buffer, int *dest, uint llim, uint ulim)
{
	uint result = 0;
	uchar ch;

	/* The limit also determines the number of valid digits. */
	uint rulim = ulim;

	ch = *buffer;
	if (ch < '0' || ch > '9')
		return (NULL);

	do
	{
		result *= 10;
		result += ch - '0';
		rulim /= 10;
		ch = *++buffer;
	}
	while ((result * 10 <= ulim) && rulim && ch >= '0' && ch <= '9');

	if (result < llim || result > ulim)
		return (NULL);

	*dest = result;
	return (buffer);
}

static
uchar const* strptime_find_string(uchar const* bp, int *tgt, char const* const* n1, char const* const* n2, int c)
{
	int i;
	size_t len;

	/* check full name - then abbreviated ones */
	for (; n1 != NULL; n1 = n2, n2 = NULL)
	{
		for (i = 0; i < c; i++, n1++)
		{
			len = c_strlen(*n1);
			if (c_strnicmp(*n1, (char const*)bp, len) == 0)
			{
				*tgt = i;
				return (bp + len);
			}
		}
	}

	/* Nothing matched */
	return (NULL);
}

/*
** NB: Reminder that tm must be set to 0 before being passed here.
*/
char* 	strptime(char const* buffer, char const* format, struct tm *tm, t_bitmask_tm* written)
{
	uchar c;
	uchar const* bp;
	uchar const* ep;
	char const* new_fmt;
	int alt_format;
	int offset;
	int split_year = 0;
	int neg = 0;
	int i;

	bp = (uchar const*)buffer;

	while (bp != NULL && (c = *format++) != '\0')
	{
		/* Clear `alternate' modifier prior to new conversion. */
		alt_format = 0;
		i = 0;
		/* Eat up white-space. */
		if (isspace(c))
		{
			while (isspace(*bp))
				bp++;
			continue;
		}
		if (c != '%')
		{
			if (c != *bp++)
				return (NULL);
			LEGAL_ALT(0);
			continue;
		}

again:
		switch (c = *format++)
		{
			case '%':	/* "%%" is converted to "%". */
			{
				if (c != *bp++)
					return (NULL);
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
				bp = (uchar const*)strptime((char const*)bp, new_fmt, tm, written);
				LEGAL_ALT(ALT_E);
				continue;
/*!
** "Elementary" conversion rules.
*/
			case 'g':	/* The year corresponding to the ISO week number but without the century. */
			{
				bp = strptime_convert_number(bp, &i, 0, 99);
				continue;
			}
			case 'G':	/* The year corresponding to the ISO week number with century. */
			{
				do { bp++; } while (isdigit(*bp));
				continue;
			}
			case 'Y':	/* The year. */
			{
				i = TM_YEAR_BASE;	/* just for data sanity... */
				bp = strptime_convert_number(bp, &i, 0, 9999);
				tm->tm_year = i - TM_YEAR_BASE;
				LEGAL_ALT(ALT_E);
				continue;
			}
			case 'y':	/* The year within 100 years of the epoch. */
			{
				/* LEGAL_ALT(ALT_E | ALT_O); */
				bp = strptime_convert_number(bp, &i, 0, 99);

				if (split_year) /* preserve century */
					i += (tm->tm_year / 100) * 100;
				else
				{
					split_year = 1;
					i += ((i <= 68) ? 2000 : 1900) - TM_YEAR_BASE;
				}
				tm->tm_year = i;
				continue;
			}

			case 'm':	/* The month. */
			{
				i = 1;
				bp = strptime_convert_number(bp, &i, 1, 12);
				tm->tm_mon = i - 1;
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'B':	/* The month, using the locale's form. */
			case 'b':
			case 'h':
			{
				bp = strptime_find_string(bp, &tm->tm_mon, g_month, g_month_abbreviated, 12);
				LEGAL_ALT(0);
				continue;
			}

			case 'd':	/* The day of month. */
			case 'e':
			{
				bp = strptime_convert_number(bp, &tm->tm_mday, 1, 31);
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'j':	/* The day of year. */
			{
				i = 1;
				bp = strptime_convert_number(bp, &i, 1, 366);
				tm->tm_yday = i - 1;
				LEGAL_ALT(0);
				continue;
			}

			case 'V':	/* The ISO 8601:1988 week number as decimal */
				bp = strptime_convert_number(bp, &i, 0, 53);
				continue;
			case 'U':	/* The week of year, beginning on sunday. */
			case 'W':	/* The week of year, beginning on monday. */
				/* XXX This is bogus, as we can not assume any valid information present in the tm structure */
				/* at this point to calculate a real value, so just check the range for now. */
				bp = strptime_convert_number(bp, &i, 0, 53);
				LEGAL_ALT(ALT_O);
				continue;

			case 'w':	/* The day of week, beginning on sunday. */
			{
				bp = strptime_convert_number(bp, &tm->tm_wday, 0, 6);
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'u':	/* The day of week, monday = 1. */
			{
				bp = strptime_convert_number(bp, &i, 1, 7);
				tm->tm_wday = i % 7;
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'A':	/* The day of week, using the locale's form. */
			case 'a':
			{
				bp = strptime_find_string(bp, &tm->tm_wday, g_weekday, g_weekday_abbreviated, 7);
				LEGAL_ALT(0);
				continue;
			}



			case 'k':	LEGAL_ALT(0); /* FALLTHROUGH */	/* The hour (24-hour clock representation). */
			case 'H':
			{
				bp = strptime_convert_number(bp, &tm->tm_hour, 0, 23);
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 'l':	LEGAL_ALT(0); /* FALLTHROUGH */	/* The hour (12-hour clock representation). */
			case 'I':
			{
				bp = strptime_convert_number(bp, &tm->tm_hour, 1, 12);
				if (tm->tm_hour == 12)
					tm->tm_hour = 0;
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'M':	/* The minute. */
			{
				bp = strptime_convert_number(bp, &tm->tm_min, 0, 59);
				LEGAL_ALT(ALT_O);
				continue;
			}

			case 'S':	/* The seconds. */
			{
				bp = strptime_convert_number(bp, &tm->tm_sec, 0, 61);
				LEGAL_ALT(ALT_O);
				continue;
			}
			case 's':	/* The seconds since the epoch */
			{
				time_t sse = 0;
				uint64_t rulim = TIME_MAX;

				if (*bp < '0' || *bp > '9')
				{
					bp = NULL;
					continue;
				}

				do
				{
					sse *= 10;
					sse += *bp++ - '0';
					rulim /= 10;
				}
				while (rulim && *bp >= '0' && *bp <= '9'); // (sse * 10 <= TIME_MAX) && (...)

				if (sse < 0 || (uint64_t)sse > TIME_MAX)
				{
					bp = NULL;
					continue;
				}
				tm = localtime(&sse);
				if (tm == NULL)
					bp = NULL;
				continue;
			}



			case 'p':	/* The locale's equivalent of AM/PM. */
			{
				bp = strptime_find_string(bp, &i, am_pm, NULL, 2);
				if (tm->tm_hour > 11)
					return (NULL);
				tm->tm_hour += i * 12;
				LEGAL_ALT(0);
				continue;
			}



			case 'C':	/* The century number. */
			{
				i = 20;
				bp = strptime_convert_number(bp, &i, 0, 99);

				i = i * 100 - TM_YEAR_BASE;
				if (split_year)
					i += tm->tm_year % 100;
				split_year = 1;
				tm->tm_year = i;
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
				if (c_strnicmp((char const*)bp, gmt, 3) == 0 ||
					c_strnicmp((char const*)bp, utc, 3) == 0)
				{
					tm->tm_isdst = 0;
					SET_TM_GMTOFF(0)
					SET_TM_ZONE(gmt)
					bp += 3;
				}
				else
				{
					ep = strptime_find_string(bp, &i, (char const* const*)tzname, NULL, 2);
					if (ep != NULL)
					{
						tm->tm_isdst = i;
						SET_TM_GMTOFF(-(timezone))
						SET_TM_ZONE(tzname[i])
					}
					bp = ep;
				}
				continue;
			}

			case 'z':
			{
				/*
				**	We recognize all ISO 8601 formats:
				**	Z	= Zulu time/UTC
				**	[+-]hhmm
				**	[+-]hh:mm
				**	[+-]hh
				**	We recognize all RFC-822/RFC-2822 formats:
				**	UT|GMT
				**	         North American : UTC offsets
				**	E[DS]T = Eastern : -4 | -5
				**	C[DS]T = Central : -5 | -6
				**	M[DS]T = Mountain: -6 | -7
				**	P[DS]T = Pacific : -7 | -8
				**	         Military
				**	[A-IL-M] = -1 ... -9 (J not used)
				**	[N-Y]  = +1 ... +12
				*/
				while (isspace(*bp))
				{
					bp++;
				}
				switch (*bp++)
				{
					case 'G':	if (*bp++ != 'M')	return (NULL);	/*FALLTHROUGH*/
					case 'U':	if (*bp++ != 'T')	return (NULL);	/*FALLTHROUGH*/
					case 'Z':
						tm->tm_isdst = 0;
						SET_TM_GMTOFF(0)
						SET_TM_ZONE(utc)
						continue;

					case '+':	neg = 0;	break;
					case '-':	neg = 1;	break;

					default:
						--bp;
						ep = strptime_find_string(bp, &i, nast, NULL, 4);
						if (ep != NULL)
						{
							SET_TM_GMTOFF(-5 - i)
							SET_TM_ZONE(__UNCONST(nast[i]))
							bp = ep;
							continue;
						}
						ep = strptime_find_string(bp, &i, nadt, NULL, 4);
						if (ep != NULL)
						{
							tm->tm_isdst = 1;
							SET_TM_GMTOFF(-4 - i)
							SET_TM_ZONE(__UNCONST(nadt[i]))
							bp = ep;
							continue;
						}

						if ((*bp >= 'A' && *bp <= 'I') ||
							(*bp >= 'L' && *bp <= 'Y'))
						{
#ifdef TM_GMTOFF
							/* Argh! No 'J'! */
							if (*bp >= 'A' && *bp <= 'I')		SET_TM_GMTOFF(('A' - 1) - (int)*bp)
							else if (*bp >= 'L' && *bp <= 'M')	SET_TM_GMTOFF('A' - (int)*bp)
							else if (*bp >= 'N' && *bp <= 'Y')	SET_TM_GMTOFF((int)*bp - 'M')
#endif
							SET_TM_ZONE(NULL) /* XXX */
							bp++;
							continue;
						}
						return (NULL);
				}
				offset = 0;
				for (i = 0; i < 4; )
				{
					if (isdigit(*bp))
					{
						offset = offset * 10 + (*bp++ - '0');
						i++;
						continue;
					}
					if (i == 2 && *bp == ':')
					{
						bp++;
						continue;
					}
					break;
				}
				switch (i)
				{
					case 2:
					{
						offset *= 100;
						break;
					}
					case 4:
					{
						i = offset % 100;
						if (i >= 60)
							return (NULL);
						/* Convert minutes into decimal */
						offset = (offset / 100) * 100 + (i * 50) / 30;
						break;
					}
					default:
					{
						return (NULL);
					}
				}
				if (neg)
					offset = -offset;
				tm->tm_isdst = 0;	/* XXX */
				SET_TM_GMTOFF(offset)
				SET_TM_ZONE(NULL)	/* XXX */
				continue;
			}
/*
** Miscellaneous conversions.
*/
		case 'n':	/* Any kind of white-space. */
		case 't':
			while (c_isspace(*bp))
				bp++;
			LEGAL_ALT(0);
			continue;

		default:	/* Unknown/unsupported conversion. */
			return (NULL);
		}
	}
	return ((char*)bp);
}

#endif



s_date		Date_FromString(char const* str, char const* format)
{
	struct tm t = { 0 };
	t_bitmask_tm written;
	s_date result;

	LIBCONFIG_HANDLE_NULLPOINTER(DATE_NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(DATE_NULL, format)
	if (strptime(str, format, &t) == NULL)
		return (DATE_NULL); // TODO handle error here ?
	result = Date_FromSTDC(&t);
	if (result.day_year == 0 && result.month > 0 && result.day_month > 0)
	{
		for (e_month i = 0; i < result.month; ++i)
		{
			result.day_year += Date_DaysInMonth(i, result.year);
		}
		result.day_year += result.day_month;
	}
	if (result.day_week == 0)
	{
		result.day_week = Date_DayOfTheWeek(&result);
	}
	return (result);
}
