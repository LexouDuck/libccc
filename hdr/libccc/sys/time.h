/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/sys/time.h                        |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_SYS_TIME_H
#define __LIBCCC_SYS_TIME_H
/*!@group{libccc_sys_time}
** @{
**	This header defines all the functions for date & time related functions.
**
**	@isostd{https://en.cppreference.com/w/c/chrono}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

/*
#ifndef __APPLE__
	#define _XOPEN_SOURCE 600
#endif
*/
#include <sys/time.h>

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! The standard type used to represent a date and time, normal precision (seconds)
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/time_t}
**
**	This type stores an integer value representing a standard UNIX epoch time.
**	That means that a `t_time` value holds a the number of seconds since
**	midnight (00:00:00), January 1, 1970, UTC (Coordinated Universal Time)
*/
typedef time_t		t_time;
TYPEDEF_ALIAS(		t_time, TIME, PRIMITIVE)

#define TIME_NULL	((t_time)0)



//! This struct is used to store a duration/interval with high precision (nanoseconds)
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/timespec}
**
**	This 'nanotime' has an arbitrary begin point (typically the start of program
**	execution, but it can be the last machine boot, among many other possibilities).
**	It is meant to be used measure intervals of time during program execution,
**	by calling the 'clock()' function several times and comparing their outputs.
**	
**	This struct is equivalent to the ISO C library's 'struct timespec',
**	although the struct member fields have different names:
**		tv_sec	->	sec
**		tv_nsec	->	nanosec
*/
typedef struct nanotime
{
	t_time		sec;		//!< The amount of seconds: only positive values are valid
	t_s64		nanosec;	//!< The amount of nanoseconds: only values in the range [0, 999999999] are valid
}				s_nanotime;
TYPEDEF_ALIAS(	s_nanotime, TIMESPEC, STRUCT)
// typedef struct timespec	s_nanotime;

#define NANOTIME_NULL	((s_nanotime){0})



// TODO `t_clock`
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/clock_t}
**
*/



//! This enum lists each day of the week, Sunday counting as zero
typedef enum weekday
{
	WEEKDAY_SUNDAY,
	WEEKDAY_MONDAY,
	WEEKDAY_TUESDAY,
	WEEKDAY_WEDNESDAY,
	WEEKDAY_THURSDAY,
	WEEKDAY_FRIDAY,
	WEEKDAY_SATURDAY,
	ENUMLENGTH_WEEKDAY
}				e_weekday;
TYPEDEF_ALIAS(	e_weekday, WEEKDAY, ENUM)

#define WEEKDAY_SUN		WEEKDAY_SUNDAY
#define WEEKDAY_MON		WEEKDAY_MONDAY
#define WEEKDAY_TUE		WEEKDAY_TUESDAY
#define WEEKDAY_WED		WEEKDAY_WEDNESDAY
#define WEEKDAY_THU		WEEKDAY_THURSDAY
#define WEEKDAY_FRI		WEEKDAY_FRIDAY
#define WEEKDAY_SAT		WEEKDAY_SATURDAY

//! This global constant stores all the string names of the WEEKDAY enum, in lowercase
extern char const* const g_weekday[ENUMLENGTH_WEEKDAY];
//! This global constant stores all the string names of the WEEKDAY enum, abbreviated to 3 letters
extern char const* const g_weekday_abbreviated[ENUMLENGTH_WEEKDAY];



//! This enum lists each month of the year, January counting as zero
typedef enum month
{
	MONTH_JANUARY,
	MONTH_FEBRUARY,
	MONTH_MARCH,
	MONTH_APRIL,
	MONTH_MAY,
	MONTH_JUNE,
	MONTH_JULY,
	MONTH_AUGUST,
	MONTH_SEPTEMBER,
	MONTH_OCTOBER,
	MONTH_NOVEMBER,
	MONTH_DECEMBER,
	ENUMLENGTH_MONTH
}				e_month;
TYPEDEF_ALIAS(	e_month, MONTH, ENUM)

#define MONTH_JAN	MONTH_JANUARY
#define MONTH_FEB	MONTH_FEBRUARY
#define MONTH_MAR	MONTH_MARCH
#define MONTH_APR	MONTH_APRIL
#define MONTH_MAY	MONTH_MAY
#define MONTH_JUN	MONTH_JUNE
#define MONTH_JUL	MONTH_JULY
#define MONTH_AUG	MONTH_AUGUST
#define MONTH_SEP	MONTH_SEPTEMBER
#define MONTH_OCT	MONTH_OCTOBER
#define MONTH_NOV	MONTH_NOVEMBER
#define MONTH_DEC	MONTH_DECEMBER

//! This global constant stores all the string names of the MONTH enum, in lowercase
extern char const* const g_month[ENUMLENGTH_MONTH];
//! This global constant stores all the string names of the MONTH enum, abbreviated to 3 letters
extern char const* const g_month_abbreviated[ENUMLENGTH_MONTH];



//! This signed int represents a timezone offset (expressed in seconds)
/*!
**	This signed int is based on the UTC time system - it expresses a time difference, in seconds.
**	The idea is to notate timezones in the commonly accepted UTC format (eg: UTC+01, UTC-06, etc)
**	There are several defines below that are meant to be used within this type:
**	@see
**	- TIMEZONE_UTC()
**	- TIMEZONE_GMT
**	- #TIMEZONE_US_EST, #TIMEZONE_US_EDT
**	- #TIMEZONE_US_CST, #TIMEZONE_US_CDT
**	- #TIMEZONE_US_MST, #TIMEZONE_US_MDT
**	- #TIMEZONE_US_PST, #TIMEZONE_US_PDT
*/
typedef t_sint	t_timezone;
TYPEDEF_ALIAS(	t_timezone, TIMEZONE, PRIMITIVE)

// Commonly used timezones
#define TIMEZONE_UTC(X)	(3600 * (X))		//!< Timezone (UTC 00): Universal Coordinated Time (same as GMT)
#define TIMEZONE_GMT	TIMEZONE_UTC(0)		//!< Timezone (UTC 00): Greenwich Mean Time (same as UTC)
#define TIMEZONE_UTCMIN	TIMEZONE_UTC(-12)	//!< Timezone (UTC-12): The minimum UTC timezone (most late)
#define TIMEZONE_UTCMAX	TIMEZONE_UTC(+12)	//!< Timezone (UTC+12): The maximum UTC timezone (most early)
// NAST
#define TIMEZONE_US_EST	TIMEZONE_UTC(-5)	//!< Timezone (UTC-05): North American Eastern Standard Time
#define TIMEZONE_US_CST	TIMEZONE_UTC(-6)	//!< Timezone (UTC-06): North American Central Standard Time
#define TIMEZONE_US_MST	TIMEZONE_UTC(-7)	//!< Timezone (UTC-07): North American Mountain Standard Time
#define TIMEZONE_US_PST	TIMEZONE_UTC(-8)	//!< Timezone (UTC-08): North American Pacific Standard Time
// NADT
#define TIMEZONE_US_EDT	TIMEZONE_UTC(-4)	//!< Timezone (UTC-04): North American Eastern Daylight Time
#define TIMEZONE_US_CDT	TIMEZONE_UTC(-5)	//!< Timezone (UTC-05): North American Central Daylight Time
#define TIMEZONE_US_MDT	TIMEZONE_UTC(-6)	//!< Timezone (UTC-06): North American Mountain Daylight Time
#define TIMEZONE_US_PDT	TIMEZONE_UTC(-7)	//!< Timezone (UTC-07): North American Pacific Daylight Time



//! This struct is used to store all aspects about a certain date/time (equivalent to 'struct tm')
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/tm}
**
**	This struct is equivalent to the ISO C library's 'struct tm',
**	although it's sub-fields have different names:
**		tm_sec	 ->	sec
**		tm_min	 ->	min
**		tm_hour	 ->	hour
**		tm_mday	 ->	day_month
**		tm_mon	 ->	month
**		tm_year	 ->	year
**		tm_wday	 ->	day_week
**		tm_yday	 ->	day_year
**		tm_isdst ->	is_dst
**	NB: This struct does not store timezone information, there are conversion functions for that:
**	@see	Time_To_Date_Timezone, Date_To_Time_Timezone
*/
typedef struct date
{
	t_u8		sec;		//!< [0,59(61)] seconds after the minute (usually 0-59 - there is extra range to accommodate for leap seconds)
	t_u8		min;		//!< [0,59] minutes after the hour
	t_u8		hour;		//!< [0,23] hours since midnight
	e_weekday	day_week;	//!< [0,6] days since Sunday
	t_u8		day_month;	//!< [1,31] day of the month
	t_s32		day_year;	//!< [0,364(365)] days since January 1 (max value is 365 every 4 years, otherwise 364)
	e_month		month;		//!< [0,11] months since January
	t_s32		year;		//!< Amount of years since 1900	
	t_bool		is_dst;		//!< If TRUE, then Daylight Savings Time is on
	t_timezone	offset;		//!< [UTC-12,UTC+12] The timezone offset of this date, expressed in seconds (ie: range is [3600*-12, 3600*+12]
}				s_date;
TYPEDEF_ALIAS(	s_date, TIME_DATE, STRUCT)
// typedef struct tm	s_time

#define DATE_NULL	((s_date){0})



#define DATE_YEAR_BASE		1900
#define DATE_YEAR(X)		((X) - DATE_YEAR_BASE)
#define YEAR(X)				DATE_YEAR(X)



#define FORMAT_TIME_UNIX	"%H:%M:%S"	//!< @ref Date_ToString() date format: hh:mm:ss	 -> 11:59:59
#define FORMAT_TIME_PRIME	"%Hh%m'%s\""//!< @ref Date_ToString() date format: hhhmm'ss" -> 11h59'59"

#define FORMAT_DATE_UNIX	"%Y-%m-%d"	//!< @ref Date_ToString() date format: YYYY-MM-DD -> 2020-12-31
#define FORMAT_DATE_YMD		"%Y/%m/%d"	//!< @ref Date_ToString() date format: YYYY/MM/DD -> 2020/12/31
#define FORMAT_DATE_DMY		"%d/%m/%Y"	//!< @ref Date_ToString() date format: DD/MM/YYYY -> 31/12/2020
#define FORMAT_DATE_MDY		"%m/%d/%Y"	//!< @ref Date_ToString() date format: MM/DD/YYYY -> 12/31/2020



#define TIME_MAX_SECONDS	(60)	//!< The amount of seconds in a minute
#define TIME_MAX_MINUTES	(60)	//!< The amount of minutes in an hour
#define TIME_MAX_HOURS		(24)	//!< The amount of hours in a day
#define TIME_MAX_DAYS_MONTH	(31)	//!< The amount of days in a month
#define TIME_MAX_DAYS_YEAR	(365)	//!< The amount of days in a year

#define TIME_MAX_LEAP_SECONDS	(62)	//!< The amount of seconds in a minute (accounting for leap seconds)
#define TIME_MAX_LEAP_DAYS_YEAR	(366)	//!< The amount of days in a year (when accounting for leap 4 years)



/*
** ************************************************************************** *|
**                           Time integer functions                           *|
** ************************************************************************** *|
*/

//! Returns the current UTC timestamp, according to the system clock
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/time}
*/
t_time					Time_Now(void);
#define c_time			Time_Now
#define c_time_now		Time_Now



//! Configurable function (default: "_UTC")
/*!
**	@see
**	- Time_ToDate_UTC()
**	- Time_ToDate_LocalTime()
*/
#define 					Time_ToDate			Time_ToDate_UTC
#define c_timetodate		Time_ToDate

//! Converts the given 't_time value' to its equivalent 's_date' representation (in UTC)
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/gmtime}
*/
s_date						Time_ToDate_UTC(t_time const value);
#define c_gmtime			Time_ToDate_UTC
#define c_timetodate_utc	Time_ToDate_UTC

//! Converts the given 't_time value' to its equivalent 's_date' representation (according to the system timezone)
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/localtime}
*/
s_date						Time_ToDate_LocalTime(t_time const value);
#define c_localtime			Time_ToDate_LocalTime
#define c_timetodate_local	Time_ToDate_LocalTime



/*
** ************************************************************************** *|
**                s_nanotime: Precise arbitrary time functions                *|
** ************************************************************************** *|
*/

//! Converts the given `s_date` struct to its ISO STD LIBC `struct tm` equivalent
/*!
**	@nonstd
*/
struct timespec					NanoTime_ToSTDC(s_nanotime const* value);
#define c_nanotimetostdc		NanoTime_ToSTDC
#define c_nanotimetotimespec	NanoTime_ToSTDC

//! Converts the given ISO STD LIBC `struct tm` to its `s_date` struct equivalent
/*!
**	@nonstd
*/
s_nanotime						NanoTime_FromSTDC(struct timespec const* value);
#define c_stdctonanotime		NanoTime_FromSTDC
#define c_timespectonanotime	NanoTime_FromSTDC



/*
** ************************************************************************** *|
**                       t_timezone: Timezone functions                       *|
** ************************************************************************** *|
*/

//! Returns the value of the given 't_time value', updating the timezone offset from 'old' to 'new'
/*
**	NOTE: this function does not behave like the POSIX tzset() function.
**	Assuming the given 'value' has a timezone offset of 'old', then the
**	returned value will have a timezone offset of 'new'.
*/
t_time					Time_SetTimezone(t_time value, t_timezone old, t_timezone new);
#define c_timetz		Time_SetTimezone

//! Returns the value of the given 't_time value', updating the timezone offset from 'old' to 'new'
/*
**	NOTE: this function does not behave like the POSIX tzset() function.
**	Assuming the given 'value' has a timezone offset of 'old', then the
**	returned value will have a timezone offset of 'new'.
*/
s_date					Date_SetTimezone(s_date const* value, t_timezone old, t_timezone new);
#define c_datetz		Date_SetTimezone



/*
** ************************************************************************** *|
**                          Date structure functions                          *|
** ************************************************************************** *|
*/

//! Returns the current UTC timestamp, according to the system clock
/*!
**	@nonstd
**
**	This equivalent to doing `gmtime(time(NULL))`
**	@see Time_Now() and Time_ToDate()
*/
s_date					Date_Now(void);
#define c_date			Date_Now
#define c_datenow		Date_Now



//! Configurable function (default: "_UTC")
/*!
**	@nonstd
*/
#define 					Date_ToTime			Date_ToTime_UTC
#define c_datetotime		Date_ToTime

//! Converts the given 's_date value' to its equivalent 't_time' representation (in UTC)
/*!
**	@nonstd
*/
t_time						Date_ToTime_UTC(s_date const* value);
#define c_datetotime_utc	Date_ToTime_UTC

//! Converts the given 's_date value' to its equivalent 't_time' representation (according to the system timezone)
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/mktime}
*/
t_time						Date_ToTime_LocalTime(s_date const* value);
#define c_mktime			Date_ToTime_LocalTime
#define c_datetotime_local	Date_ToTime_LocalTime



//! Converts the given 's_date' struct to its ISO STD LIBC 'struct tm' equivalent
/*!
**	@nonstd
*/
struct tm					Date_ToSTDC(s_date const* date);
#define c_datetostdc		Date_ToSTDC

//! Converts the given ISO STD LIBC 'struct tm' to its 's_date' struct equivalent
/*!
**	@nonstd
*/
s_date						Date_FromSTDC(struct tm const* value);
#define c_stdctodate		Date_FromSTDC



//! Parses the given string representation of a date/time, and returns the resulting 's_date' struct
/*!
**	@nonstd
**
**	NOTE: The `tm` argument must be set to 0 before being passed here.
**
**	%%			The '%' character.
**	%a, %A		The name of the day of the week according to the current locale, in abbreviated form or the full name.
**	%b, %B, %h	The month name according to the current locale, in abbreviated form or the full name.
**	%c			The date and time representation for the current locale.
**	%C			The century number (0–99).
**	%d, %e		The day of month (1–31).
**	%D			Equivalent to `%m/%d/%y`. (This is the American style date, very confusing to non-Americans.. The ISO 8601 standard format is `%Y-%m-%d`.)
**	%H			The hour (0–23).
**	%I			The hour on a 12-hour clock (1–12).
**	%j			The day number in the year (1–366).
**	%m			The month number (1–12).
**	%M			The minute (0–59).
**	%n			Arbitrary whitespace.
**	%p			The locale's equivalent of AM or PM. (NOTE: there may be none.)
**	%r			The 12-hour clock time (using the locale's AM or PM). In the POSIX locale equivalent to `%I:%M:%S %p` (NOTE: If the locale's `t_fmt_ampm` is empty, then the behavior is undefined).
**	%R			Equivalent to `%H:%M`.
**	%S			The second (0–60; 60 may occur for leap seconds; earlier also 61 was allowed).
**	%t			Arbitrary whitespace.
**	%T			Equivalent to `%H:%M:%S`.
**	%U			The week number with Sunday the first day of the week (0–53). The first Sunday of January is the first day of week 1.
**	%W			The week number with Monday the first day of the week (0–53). The first Monday of January is the first day of week 1.
**	%w			The ordinal number of the day of the week (0–6), with Sunday = 0.
**	%X			The time, using the locale's time format.
**	%x			The date, using the locale's date format.
**	%Y			The year, including century (for example, 1991).
**	%y			The year within century (0–99). When a century is not otherwise specified,
**				values in the range 69–99 refer to years in the twentieth century (1969–1999);
**				values in the range 00–68 refer to years in the twenty-first century (2000–2068).
**
**	Some field descriptors can be modified by the E or O modifier characters
**	to indicate that an alternative format or specification should be used.
**	If the alternative format or specification does not exist in the current locale,
**	then the unmodified field descriptor is used.
**
**	The `E` modifier specifies that the input string may contain alternative
**	locale-dependent versions of the date and time representation:
**
**	%Ec			The locale's alternative date and time representation.
**	%EC			The name of the base year (period) in the locale's alternative representation.
**	%Ex			The locale's alternative date representation.
**	%EX			The locale's alternative time representation.
**	%Ey			The offset from %EC (year only) in the locale's alternative representation.
**	%EY			The full alternative year representation.
**
**	The `O` modifier specifies that the numerical input may be in an alternative locale-dependent format:
**
**	%Od, %Oe	The day of the month using the locale's alternative numeric symbols; leading zeros are permitted but not required.
**	%OH			The hour (24-hour clock) using the locale's alternative numeric symbols.
**	%OI			The hour (12-hour clock) using the locale's alternative numeric symbols.
**	%Om			The month using the locale's alternative numeric symbols.
**	%OM			The minutes using the locale's alternative numeric symbols.
**	%OS			The seconds using the locale's alternative numeric symbols.
**	%OU			The week number of the year (Sunday as the first day of the week) using the locale's alternative numeric symbols.
**	%Ow			The ordinal number of the day of the week (Sunday=0), using the locale's alternative numeric symbols.
**	%OW			The week number of the year (Monday as the first day of the week) using the locale's alternative numeric symbols.
**	%Oy			The year (offset from %C) using the locale's alternative numeric symbols.
*/
//_FORMAT(strptime, 2, 0) // TODO check if this format() attribute exists even
s_date						Date_Parse(char const* str, char const* format);
#define c_strptime			Date_Parse
#define c_strtodate			Date_Parse
#define c_dateparse			Date_Parse
#define Date_FromString		Date_Parse

s_date						Date_Parse_N(char const* str, char const* format, t_size n);
#define c_strnptime			Date_Parse_N
#define c_strntodate		Date_Parse_N
#define c_dateparsen		Date_Parse_N
#define Date_FromString_N	Date_Parse_N

t_size							Date_ParseStrict(s_date* dest, char const* str, char const* format);
#define c_strsptime				Date_ParseStrict
#define c_strstodate			Date_ParseStrict
#define c_dateparses			Date_ParseStrict
#define Date_FromStringStrict	Date_ParseStrict

t_size							Date_ParseStrict_N(s_date* dest, char const* str, char const* format, t_size n);
#define c_strnsptime			Date_ParseStrict_N
#define c_strnstodate			Date_ParseStrict_N
#define c_dateparsesn			Date_ParseStrict_N
#define Date_FromStringStrict_N	Date_ParseStrict_N



//! Creates a string representation of the given 'date', according to the given 'format' string
/*!
**	@nonstd
**
**	This function works similarly to the strftime() function from 'time.h' STDC header
**	It is closer to 'asprintf()' as well, making for a rather easy-to-use equivalent to strftime().
**	That being said, it is probably better to use Date_String_Format_N for machines with little RAM.
*/
_FORMAT(strftime, 2, 0)
_MALLOC()
char*						Date_Print(s_date const* date, char const* format);
#define c_strftime			Date_Print
#define c_datetostr			Date_Print
#define c_datefmt			Date_Print
#define Date_Format			Date_Print
#define Date_ToString		Date_Print

//! Creates a string representation of the given 'date', according to the given 'format' string
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/strftime}
**
**	@see Date_ToString
*/
_FORMAT(strftime, 4, 0)
t_size						Date_Print_N(char* dest, t_size max, s_date const* date, char const* format);
#define c_strnftime			Date_Print_N
#define c_datetostrn		Date_Print_N
#define c_datefmtn			Date_Print_N
#define Date_Format_N		Date_Print_N
#define Date_ToString_N		Date_Print_N



/*
** ************************************************************************** *|
**                       Date-related utility functions                       *|
** ************************************************************************** *|
*/

//! returns TRUE if the given year is a leap year
t_bool	Date_IsLeapYear(t_s32 year);

//! returns the amount of days in the given `month`
t_uint	Date_DaysInMonth(e_month month, t_s32 year);

//! returns the day of the week
t_uint	Date_DayOfTheWeek(s_date* date);



/*! @} */
HEADER_END
#endif
