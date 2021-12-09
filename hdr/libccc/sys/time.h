/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/time.h                        |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_TIME_H
#define __LIBCCC_SYS_TIME_H
/*!@group{libccc_sys_time}
**
**	This header defines all the functions for date & time related functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/chrono}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#if (defined(_WIN32) && !defined(__MINGW32__))
		#include <time.h>
	#else
		#include <sys/time.h>
	#endif
#else
	typedef long	time_t;
	struct timespec
	{
		time_t	tv_sec;
		long	tv_nsec;
	};
	struct tm
	{
		int	tm_sec;
		int	tm_min;
		int	tm_hour;
		int	tm_mday;
		int	tm_mon;
		int	tm_year;
		int	tm_wday;
		int	tm_yday;
		int	tm_isdst;
	};
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_TIME_T
#define __LIBCCC_SYS_TIME_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//!@doc The standard type used to represent a date and time, normal precision (seconds)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/chrono/time_t}
**
**	This type stores an integer value representing a standard UNIX epoch time.
**	That means that a `t_time` value holds a the number of seconds since
**	midnight (00:00:00), January 1, 1970, UTC (Coordinated Universal Time)
*/
//!@{
typedef time_t		t_time;
TYPEDEF_ALIAS(		t_time, TIME, PRIMITIVE)
//!@}
//! The default/null/zero value for a #t_time integer
#define TIME_NULL	((t_time)0)



//!@doc This struct is used to store a duration/interval with high precision (nanoseconds)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/chrono/timespec}
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
//!@{
typedef struct nanotime
{
	t_time		sec;		//!< The amount of seconds: only positive values are valid
	t_s64		nanosec;	//!< The amount of nanoseconds: only values in the range [0, 999999999] are valid
}				s_nanotime;
TYPEDEF_ALIAS(	s_nanotime, TIMESPEC, STRUCT)
// typedef struct timespec	s_nanotime;
//!@}
//! The default/null/zero value for a #s_nanotime struct
#define NANOTIME_NULL	((s_nanotime){ .sec=0, .nanosec=0 })



// TODO `t_clock`
/*!
**	@isostd{C,https://en.cppreference.com/w/c/chrono/clock_t}
**
*/



//!@doc This enum lists each day of the week, Sunday counting as zero
//!@{
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
}	e_weekday;
TYPEDEF_ALIAS(e_weekday, WEEKDAY, ENUM)
//!@}
//!@doc Alias macros, for the short 3-letter versions of weekday names
//!@{
#define WEEKDAY_SUN		WEEKDAY_SUNDAY
#define WEEKDAY_MON		WEEKDAY_MONDAY
#define WEEKDAY_TUE		WEEKDAY_TUESDAY
#define WEEKDAY_WED		WEEKDAY_WEDNESDAY
#define WEEKDAY_THU		WEEKDAY_THURSDAY
#define WEEKDAY_FRI		WEEKDAY_FRIDAY
#define WEEKDAY_SAT		WEEKDAY_SATURDAY
//!@}

//! This global constant stores all the string names of the WEEKDAY enum, in lowercase
extern t_char const* const g_weekday[ENUMLENGTH_WEEKDAY];
//! This global constant stores all the string names of the WEEKDAY enum, abbreviated to 3 letters
extern t_char const* const g_weekday_abbreviated[ENUMLENGTH_WEEKDAY];



//!@doc This enum lists each month of the year, January counting as zero
//!@{
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
}	e_month;
TYPEDEF_ALIAS(e_month, MONTH, ENUM)
//!@}
//!@doc Alias macros, for the short 3-letter versions of month names
//!@{
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
//!@}

//! This global constant stores all the string names of the MONTH enum, in lowercase
extern t_char const* const g_month[ENUMLENGTH_MONTH];
//! This global constant stores all the string names of the MONTH enum, abbreviated to 3 letters
extern t_char const* const g_month_abbreviated[ENUMLENGTH_MONTH];



//!@doc This signed int represents a timezone offset (expressed in seconds)
/*!
**	@nonstd
**
**	This signed int is based on the UTC time system - it expresses a time difference, in seconds.
**	The idea is to notate timezones in the commonly accepted UTC format (eg: UTC+01, UTC-06, etc)
**	There are several defines below that are meant to be used within this type:
**	@see
**	- TIMEZONE_UTC()
**	- #TIMEZONE_GMT
**	- #TIMEZONE_NA_EST, #TIMEZONE_NA_EDT
**	- #TIMEZONE_NA_CST, #TIMEZONE_NA_CDT
**	- #TIMEZONE_NA_MST, #TIMEZONE_NA_MDT
**	- #TIMEZONE_NA_PST, #TIMEZONE_NA_PDT
*/
//!@{
typedef t_s32	t_timezone;
TYPEDEF_ALIAS(	t_timezone, TIMEZONE, PRIMITIVE)
//!@}

// Timezones: Commonly used standard timezones
#define TIMEZONE_UTC(X)	(3600 * (X))		//!< Timezone (UTC 00): Universal Coordinated Time (same as GMT)
#define TIMEZONE_GMT	TIMEZONE_UTC(0)		//!< Timezone (UTC 00): Greenwich Mean Time (same as UTC)
#define TIMEZONE_UTCMIN	TIMEZONE_UTC(-12)	//!< Timezone (UTC-12): The minimum UTC timezone (most late)
#define TIMEZONE_UTCMAX	TIMEZONE_UTC(+12)	//!< Timezone (UTC+12): The maximum UTC timezone (most early)
// Timezones: North-American Standard Time (NAST)
#define TIMEZONE_NA_EST	TIMEZONE_UTC(-5)	//!< Timezone (UTC-05): North American Eastern Standard Time
#define TIMEZONE_NA_CST	TIMEZONE_UTC(-6)	//!< Timezone (UTC-06): North American Central Standard Time
#define TIMEZONE_NA_MST	TIMEZONE_UTC(-7)	//!< Timezone (UTC-07): North American Mountain Standard Time
#define TIMEZONE_NA_PST	TIMEZONE_UTC(-8)	//!< Timezone (UTC-08): North American Pacific Standard Time
// Timezones: North-American Daylight-savings Time (NADT)
#define TIMEZONE_NA_EDT	TIMEZONE_UTC(-4)	//!< Timezone (UTC-04): North American Eastern Daylight-savings Time
#define TIMEZONE_NA_CDT	TIMEZONE_UTC(-5)	//!< Timezone (UTC-05): North American Central Daylight-savings Time
#define TIMEZONE_NA_MDT	TIMEZONE_UTC(-6)	//!< Timezone (UTC-06): North American Mountain Daylight-savings Time
#define TIMEZONE_NA_PDT	TIMEZONE_UTC(-7)	//!< Timezone (UTC-07): North American Pacific Daylight-savings Time



//! Has a non-zero value if the current system timezone uses Daylight Savings Time rules
#define TIMEZONE_HAS_DST	(daylight)



//!@doc This struct is used to store all aspects about a certain date/time (equivalent to `struct tm`)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/chrono/tm}
**
**	This struct is equivalent to the ISO C library's `struct tm`,
**	although it's sub-fields have different names:
**		`tm_sec`	->	`sec`
**		`tm_min`	->	`min`
**		`tm_hour`	->	`hour`
**		`tm_mday`	->	`day_month`
**		`tm_mon`	->	`month`
**		`tm_year`	->	`year`
**		`tm_wday`	->	`day_week`
**		`tm_yday`	->	`day_year`
**		`tm_isdst`	->	`is_dst`
**		`tm_gmtoff`	->	`offset` (`tm_gmtoff` is not standard, GNU extension)
*/
//!@{
typedef struct date
{
	t_u8		hour;		//!< [0,23] Amount of hours since midnight
	t_u8		min;		//!< [0,59] Amount of minutes after the hour
	t_u8		sec;		//!< [0,59(60)] Amount of seconds after the minute (usually 0-59 - leap seconds are the exception)
	t_s32		year;		//!< Amount of years since year 0 (https://en.wikipedia.org/wiki/Astronomical_year_numbering)	
	e_month		month;		//!< [0,11] Amount of months since January
	t_u8		day_month;	//!< [1,31] Day of the month
	t_u32		day_year;	//!< [0,364(365)] Amount of days since January 1 (max value is 365 on leap years, otherwise 364)
	e_weekday	day_week;	//!< [0,6] Amount of days since Sunday
	t_bool		is_dst;		//!< If `TRUE`, then Daylight Savings Time is on
	t_timezone	offset;		//!< [UTC-12,UTC+12] The timezone offset of this date (adjusted for DST), expressed in seconds (ie: range is [3600*-12, 3600*+12]
}				s_date;
TYPEDEF_ALIAS(	s_date, TIME_DATE, STRUCT)
// typedef struct tm	s_time
//!@}
//! The default/null value for a #s_date struct (all fields set to zero)
#define DATE_NULL \
	((s_date){			\
		.hour      = 0,	\
		.min       = 0,	\
		.sec       = 0,	\
		.year      = 0,	\
		.month     = 0,	\
		.day_month = 0,	\
		.day_year  = 0,	\
		.day_week  = 0,	\
		.is_dst    = 0,	\
		.offset    = 0,	\
	})



//!@doc The various time range maximum numbers, used in several calculations
/*!
**	These macros are used to indicate a maximum range for a time unit.
**	NOTE: There are some exceptions to these maximums, notably:
**	- Leap years (365->366 days), see #TIME_MAX_SECONDS_LEAP
**	- Lead seconds (60->61 seconds), see #TIME_MAX_DAYS_YEAR_LEAP
*/
//!@{
#define TIME_MAX_SECONDS		(60)	//!< The amount of seconds in a minute
#define TIME_MAX_SECONDS_LEAP	(61)	//!< The amount of seconds in a minute (accounting for leap seconds)

#define TIME_MAX_MINUTES		(60)	//!< The amount of minutes in an hour

#define TIME_MAX_HOURS			(24)	//!< The amount of hours in a day

#define TIME_MAX_DAYS_YEAR		(365)	//!< The amount of days in a year
#define TIME_MAX_DAYS_YEAR_LEAP	(366)	//!< The amount of days in a year (when accounting for leap years)
//!@}



//!@doc Common time string format macro definitions (to be used with Date_Print() and Date_Parse() functions)
/*!
**	These macros are used to indicate a maximum range for a time unit.
**	@see
**	- Date_Parse()
**	- Date_Parse_N()
**	- Date_ParseStrict()
**	- Date_ParseStrict_N()
**	- Date_Print()
**	- Date_Print_N()
*/
//!@{
#define SF_TIME_UNIX		"%H:%M:%S"	//!< date format: `HH:mm:ss`	-> `11:59:59`
#define SF_TIME_DURATION	"%Hh%m'%s\""//!< date format: `HHhmm'ss"`	-> `11h59'59"`

#define SF_DATE_UNIX		"%Y-%m-%d"	//!< date format: `YYYY-MM-DD`	-> `2020-12-31`
#define SF_DATE_YMD			"%Y/%m/%d"	//!< date format: `YYYY/MM/DD`	-> `2020/12/31`
#define SF_DATE_DMY			"%d/%m/%Y"	//!< date format: `DD/MM/YYYY`	-> `31/12/2020`
#define SF_DATE_MDY			"%m/%d/%Y"	//!< date format: `MM/DD/YYYY`	-> `12/31/2020`
//!@}



#endif
#ifndef __LIBCCC_SYS_TIME_F
#define __LIBCCC_SYS_TIME_F

/*
** ************************************************************************** *|
**                           Time integer functions                           *|
** ************************************************************************** *|
*/

//!@doc Returns the current UTC timestamp, according to the system clock
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/chrono/time}
*/
//!@{
t_time					Time_Now(void);
#define c_time			Time_Now
#define c_time_now		Time_Now
//!@}



//!@doc Configurable function (default: "_UTC")
/*!
**	@see
**	- Time_ToDate_UTC()
**	- Time_ToDate_LocalTime()
*/
//!@{
#define 					Time_ToDate			Time_ToDate_UTC
#define c_timetodate		Time_ToDate
//!@}

//!@doc Converts the given `t_time value` to its equivalent `s_date` representation (in UTC)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/chrono/gmtime}
**	@isostd{POSIX,https://linux.die.net/man/3/gmtime}
*/
//!@{
s_date						Time_ToDate_UTC(t_time const value);
#define c_gmtime			Time_ToDate_UTC
#define c_timetodate_utc	Time_ToDate_UTC
//!@}

//!@doc Converts the given `t_time value` to its equivalent `s_date` representation (according to the system timezone)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/chrono/localtime}
**	@isostd{POSIX,https://linux.die.net/man/3/localtime}
*/
//!@{
s_date						Time_ToDate_LocalTime(t_time const value);
#define c_localtime			Time_ToDate_LocalTime
#define c_timetodate_local	Time_ToDate_LocalTime
//!@}



/*
** ************************************************************************** *|
**                s_nanotime: Precise arbitrary time functions                *|
** ************************************************************************** *|
*/

//!@doc Converts the given `s_date` struct to its ISO STD LIBC `struct tm` equivalent
/*!
**	@nonstd
*/
//!@{
struct timespec					NanoTime_ToSTDC(s_nanotime const* value);
#define c_nanotimetostdc		NanoTime_ToSTDC
#define c_nanotimetotimespec	NanoTime_ToSTDC
//!@}

//!@doc Converts the given ISO STD LIBC `struct tm` to its `s_date` struct equivalent
/*!
**	@nonstd
*/
//!@{
s_nanotime						NanoTime_FromSTDC(struct timespec const* value);
#define c_stdctonanotime		NanoTime_FromSTDC
#define c_timespectonanotime	NanoTime_FromSTDC
//!@}



/*
** ************************************************************************** *|
**                          Date structure functions                          *|
** ************************************************************************** *|
*/

//!@doc Returns the current UTC timestamp, according to the system clock
/*!
**	@nonstd
**
**	This equivalent to doing `gmtime(time(NULL))`
**	@see Time_Now() and Time_ToDate()
*/
//!@{
s_date					Date_Now(void);
#define c_date			Date_Now
#define c_datenow		Date_Now
//!@}



//!@doc Configurable function (default: "_UTC")
/*!
**	@nonstd
*/
//!@{
#define 					Date_ToTime			Date_ToTime_UTC
#define c_datetotime		Date_ToTime
//!@}

//!@doc Converts the given 's_date value' to its equivalent 't_time' representation (in UTC)
/*!
**	@isostd{BSD,https://linux.die.net/man/3/timegm}
*/
//!@{
t_time						Date_ToTime_UTC(s_date const* value);
#define c_datetotime_utc	Date_ToTime_UTC
//!@}

//!@doc Converts the given 's_date value' to its equivalent 't_time' representation (according to the system timezone)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/chrono/mktime}
*/
//!@{
t_time						Date_ToTime_LocalTime(s_date const* value);
#define c_mktime			Date_ToTime_LocalTime
#define c_datetotime_local	Date_ToTime_LocalTime
//!@}



//!@doc Converts the given 's_date' struct to its ISO STD LIBC `struct tm` equivalent
/*!
**	@nonstd
*/
//!@{
struct tm					Date_ToSTDC(s_date const* date);
#define c_datetostdc		Date_ToSTDC
//!@}

//!@doc Converts the given ISO STD LIBC `struct tm` to its 's_date' struct equivalent
/*!
**	@nonstd
*/
//!@{
s_date						Date_FromSTDC(struct tm const* value);
#define c_stdctodate		Date_FromSTDC
//!@}



//!@doc Parses the given string representation of a date/time, and returns the resulting 's_date' struct
/*!
**	@isostd{POSIX,https://linux.die.net/man/3/strptime}
**
**	NOTE: The `tm` argument should be cleared (zeroed out) before being passed to this function.
**
**	| Specifier char | Description |
**	|----------------|-------------|
**	| `%%`           | The `'%'` (percent) character. |
**	| `%a`,`%A`      | The name of the day of the week according to the current locale, in abbreviated form or the full name. |
**	| `%b`,`%B`,`%h` | The month name according to the current locale, in abbreviated form or the full name. |
**	| `%c`           | The date and time representation for the current locale. |
**	| `%C`           | [0,99] The century number . |
**	| `%d`,`%e`      | [1,31] The day of month . |
**	| `%D`           | Equivalent to `"%m/%d/%y"`. (This is the American style date, very confusing to non-Americans.. The ISO 8601 standard format is `"%Y-%m-%d"`.) |
**	| `%H`           | [0,23] The hour . |
**	| `%I`           | [1,12] The hour on a 12-hour clock . |
**	| `%j`           | [1,366] The day number in the year . |
**	| `%m`           | [1,12] The month number . |
**	| `%M`           | [0,59] The minute . |
**	| `%n`           | Arbitrary whitespace. |
**	| `%p`           | The locale's equivalent of AM or PM. (NOTE: there may be none.) |
**	| `%r`           | The 12-hour clock time (using the locale's AM or PM). In the POSIX locale equivalent to `"%I:%M:%S %p"` (NOTE: If the locale's `t_fmt_ampm` is empty, then the behavior is undefined). |
**	| `%R`           | Equivalent to `%H:%M`. |
**	| `%S`           | [0,60] The second (60 may occur for leap seconds; earlier also 61 was allowed). |
**	| `%t`           | Arbitrary whitespace. |
**	| `%T`           | Equivalent to `%H:%M:%S`. |
**	| `%U`           | [0,53] The week number with Sunday the first day of the week. The first Sunday of January is the first day of week 1. |
**	| `%W`           | [0,53] The week number with Monday the first day of the week. The first Monday of January is the first day of week 1. |
**	| `%w`           | [0,6] The ordinal number of the day of the week, with Sunday = 0. |
**	| `%X`           | The time, using the locale's time format. |
**	| `%x`           | The date, using the locale's date format. |
**	| `%Y`           | The year, including century (for example, 1991). |
**	| `%y`           | [0,99] The year within century. When a century is not otherwise specified,
**	                    values in the range [69,99] refer to years in the twentieth century: [1969,1999];
**	                    values in the range [00,68] refer to years in the twenty-first century: [2000,2068].
**
**	Some field descriptors can be modified by the E or O modifier characters
**	to indicate that an alternative format or specification should be used.
**	If the alternative format or specification does not exist in the current locale,
**	then the unmodified field descriptor is used.
**
**	The `E` modifier specifies that the input string may contain alternative
**	locale-dependent versions of the date and time representation:
**
**	| Specifier   | Description |
**	|-------------|-------------|
**	| `%Ec`       | The locale's alternative date and time representation. |
**	| `%EC`       | The name of the base year (period) in the locale's alternative representation. |
**	| `%Ex`       | The locale's alternative date representation. |
**	| `%EX`       | The locale's alternative time representation. |
**	| `%Ey`       | The offset from `%EC` (year only) in the locale's alternative representation. |
**	| `%EY`       | The full alternative year representation. |
**
**	The `O` modifier specifies that the numerical input may be in an alternative locale-dependent format:
**
**	| Specifier   | Description |
**	|-------------|-------------|
**	| `%Od`,`%Oe` | The day of the month using the locale's alternative numeric symbols; leading zeros are permitted but not required. |
**	| `%OH`       | The hour (24-hour clock) using the locale's alternative numeric symbols. |
**	| `%OI`       | The hour (12-hour clock) using the locale's alternative numeric symbols. |
**	| `%Om`       | The month using the locale's alternative numeric symbols. |
**	| `%OM`       | The minutes using the locale's alternative numeric symbols. |
**	| `%OS`       | The seconds using the locale's alternative numeric symbols. |
**	| `%OU`       | The week number of the year (Sunday as the first day of the week) using the locale's alternative numeric symbols. |
**	| `%Ow`       | The ordinal number of the day of the week (Sunday=0), using the locale's alternative numeric symbols. |
**	| `%OW`       | The week number of the year (Monday as the first day of the week) using the locale's alternative numeric symbols. |
**	| `%Oy`       | The year (offset from `%C`) using the locale's alternative numeric symbols. |
*/
//!@{
//_FORMAT(strptime, 2, 0) // TODO check if this format() attribute exists even
t_size						Date_Parse(s_date* dest, t_char const* str, t_char const* format);
#define c_strptime			Date_Parse
#define c_dateparse			Date_Parse
//!@}
//!@doc Like Date_Parse(), but directly returns the result
//!@{
s_date						Date_FromString(t_char const* str, t_char const* format);
#define c_strtodate			Date_FromString
//!@}

//!@doc Like Date_Parse(), but will not set every field in the `s_date` struct, only those directly parsed
//!@{
t_size						Date_Parse_Min(s_date* dest, t_char const* str, t_char const* format);
#define c_strmptime			Date_Parse_Min
#define c_dateparsem		Date_Parse_Min
//!@}
//!@doc Like Date_FromString(), but will not set every field in the `s_date` struct, only those directly parsed
//!@{
s_date						Date_FromString_Min(t_char const* str, t_char const* format);
#define c_strmtodate		Date_FromString_Min
//!@}



//!@doc Creates a string representation of the given 'date', according to the given 'format' string
/*!
**	@nonstd, see Date_Print_N() https://www.gnu.org/software/libc/manual/html_node/Formatting-Calendar-Time.html
**
**	This function works similarly to the strftime() function from 'time.h' STDC header
**	It is closer to 'asprintf()' as well, making for a rather easy-to-use equivalent to strftime().
**
**	Here is the list of valid format specifier flags:
**	^	The output uses uppercase characters, but only if this is possible (see Case Conversion).
**	_	The number is padded with spaces.
**	-	The number is not padded at all.
**	0	The number is padded with zeros even if the format specifies padding with spaces.
**		The default action is to pad the number with zeros to keep it a constant width.
**		Numbers that do not have a range indicated below are never padded, since there is no natural width for them.
**
**	Following the flag an optional specification of the width is possible. This is specified in decimal notation.
**	If the natural size of the output of the field has less than the specified number of characters,
**	the result is written right adjusted and space padded to the given size.
**
**	An optional modifier can follow the optional flag and width specification, these are:
**	(ISO C99 and POSIX.2-1992)
**
**	E	Use the locale's alternative representation for date and time. This modifier applies to the `%c`, `%C`, `%x`, `%X`, `%y` and `%Y` format specifiers.
**		In a Japanese locale, for example, `%Ex` might yield a date format based on the Japanese Emperors' reigns (eras).
**	O	With all format specifiers that produce numbers: use the locale's alternative numeric symbols.
**		With `%B`, `%b`, and `%h`: use the grammatical form for month names that is appropriate when the month is named by itself,
**		rather than the form that is appropriate when the month is used as part of a complete date.
**		The `%OB` and `%Ob` formats are a C2X feature, specified in C2X to use the locale's `alternative` month name;
**		the GNU C Library extends this specification to say that the form used in a complete date is the default
**		and the form naming the month by itself is the alternative.
**
**	If the format supports the modifier but no alternative representation is available, it is ignored.
**	The conversion specifier ends with a format specifier taken from the following list.
**	The whole `%` sequence is replaced in the output string as follows:
**
**	%%	A literal '%' character.
**	%a	The abbreviated weekday name according to the current locale.
**	%A	The full weekday name according to the current locale.
**	%b	The abbreviated month name according to the current locale, in the grammatical form used when the month is part of a complete date.
**		As a C2X feature (with a more detailed specification in the GNU C Library), the O modifier can be used (`%Ob`) to get the grammatical form used when the month is named by itself.
**	%B	The full month name according to the current locale, in the grammatical form used when the month is part of a complete date.
**		As a C2X feature (with a more detailed specification in the GNU C Library), the O modifier can be used (`%OB`) to get the grammatical form used when the month is named by itself.
**		Note that not all languages need two different forms of the month names, so the text produced by `%B` and `%OB`, and by `%b` and `%Ob`, may or may not be the same, depending on the locale.
**	%c	The preferred calendar time representation for the current locale.
**	%C	The century of the year. This is equivalent to the greatest integer not greater than the year divided by 100.
**		If the E modifier is specified (`%EC`), instead produces the name of the period for the year (e.g. an era name) in the locale's alternative calendar.
**		(ISO C99 and POSIX.2-1992)
**	%d	The day of the month as a decimal number (range 01 through 31).
**	%D	The date using the format `"%m/%d/%y"`.
**		(ISO C99 and POSIX.2-1992)
**	%e	The day of the month like with `%d`, but padded with spaces (range 1 through 31).
**		(ISO C99 and POSIX.2-1992)
**	%F	The date using the format `"%Y-%m-%d"`. This is the form specified in the ISO 8601 standard and is the preferred form for all uses.
**		(ISO C99 and POSIX.1-2001)
**	%g	The year corresponding to the ISO week number, but without the century (range 00 through 99).
**		This has the same format and value as `%y`, except that if the ISO week number (see `%V`) belongs to the previous or next year, that year is used instead.
**		(ISO C99 and POSIX.1-2001)
**	%G	The year corresponding to the ISO week number
**		This has the same format and value as `%Y`, except that if the ISO week number (see `%V`) belongs to the previous or next year, that year is used instead.
**		(ISO C99 and POSIX.1-2001 but was previously available as a GNU extension)
**	%h	The abbreviated month name according to the current locale. The action is the same as for `%b`.
**		(ISO C99 and POSIX.2-1992)
**	%H	The hour as a decimal number, using a 24-hour clock (range 00 through 23).
**	%I	The hour as a decimal number, using a 12-hour clock (range 01 through 12).
**	%j	The day of the year as a decimal number (range 001 through 366).
**	%k	The hour as a decimal number, using a 24-hour clock like `%H`, but padded with spaces (range 0 through 23).
**		This format is a GNU extension.
**	%l	The hour as a decimal number, using a 12-hour clock like `%I`, but padded with spaces (range 1 through 12).
**		This format is a GNU extension.
**	%m	The month as a decimal number (range 01 through 12).
**	%M	The minute as a decimal number (range 00 through 59).
**	%n	A single `'\n'` (newline) character.
**		(ISO C99 and POSIX.2-1992)
**	%p	Either `AM` or `PM`, according to the given time value; or the corresponding strings for the current locale.
**		Noon is treated as `PM` and midnight as `AM`. In most locales `AM`/`PM` format is not supported, in such cases "%p" yields an empty string.
**	%P	Either `am` or `pm`, according to the given time value; or the corresponding strings for the current locale, printed in lowercase characters.
**		Noon is treated as `pm` and midnight as `am`. In most locales `AM`/`PM` format is not supported, in such cases "%P" yields an empty string.
**		This format is a GNU extension.
**	%r	The complete calendar time using the AM/PM format of the current locale.
**		In the POSIX locale, this format is equivalent to `"%I:%M:%S %p"`.
**		(ISO C99 and POSIX.2-1992)
**	%R	The hour and minute in decimal numbers using the format `"%H:%M"`.
**		(ISO C99 and POSIX.1-2001 but was previously available as a GNU extension)
**	%s	The number of seconds since the epoch, i.e., since 1970-01-01 00:00:00 UTC.
**		Leap seconds are not counted unless leap second support is available.
**		This format is a GNU extension.
**	%S	The seconds as a decimal number (range 00 through 60).
**	%t	A single `'\t'` (tabulator) character.
**		(ISO C99 and POSIX.2-1992)
**	%T	The time of day using decimal numbers using the format `"%H:%M:%S"`.
**		(ISO C99 and POSIX.2-1992)
**	%u	The day of the week as a decimal number (range 1 through 7), Monday being 1.
**		(ISO C99 and POSIX.2-1992)
**	%U	The week number of the current year as a decimal number (range 00 through 53), starting with the first Sunday as the first day of the first week. Days preceding the first Sunday in the year are considered to be in week 00.
**	%V	The ISO 8601:1988 week number as a decimal number (range 01 through 53). ISO weeks start with Monday and end with Sunday.
**		Week 01 of a year is the first week which has the majority of its days in that year;
**		this is equivalent to the week containing the year's first Thursday, and it is also equivalent to the week containing January 4.
**		Week 01 of a year can contain days from the previous year.
**		The week before week 01 of a year is the last week (52 or 53) of the previous year even if it contains days from the new year.
**		(ISO C99 and POSIX.2-1992)
**	%w	The day of the week as a decimal number (range 0 through 6), Sunday being 0.
**	%W	The week number of the current year as a decimal number (range 00 through 53), starting with the first Monday as the first day of the first week.
**		All days preceding the first Monday in the year are considered to be in week 00.
**	%x	The preferred date representation for the current locale.
**	%X	The preferred time of day representation for the current locale.
**	%y	The year without a century as a decimal number (range 00 through 99). This is equivalent to the year modulo 100.
**		If the E modifier is specified (`%Ey`), instead produces the year number according to a locale-specific alternative calendar.
**		Unlike `%y`, the number is not reduced modulo 100. However, by default it is zero-padded to a minimum of two digits
**		(this can be overridden by an explicit field width or by the _ and - flags).
**	%Y	The year as a decimal number, using the Gregorian calendar. Years before the year 1 are numbered 0, -1, and so on.
**		If the E modifier is specified (`%EY`), instead produces a complete representation of the year according to the locale's alternative calendar.
**		Generally this will be some combination of the information produced by `"%EC"` and `"%Ey"`.
**		As a GNU extension, the formatting flags _ or - may be used with this conversion specifier; they affect how the year number is printed.
**	%z	RFC 822/ISO 8601:1988 style numeric time zone (e.g., `"-0600"` or `"+0100"`), or nothing if no time zone is determinable.
**		In the POSIX locale, a full RFC 822 timestamp is generated by the format `"%a, %d %b %Y %H:%M:%S %z"` (or the equivalent `"%a, %d %b %Y %T %z"`).
**		(ISO C99 and POSIX.1-2001 but was previously available as a GNU extension)
**	%Z	The time zone abbreviation (empty if the time zone can't be determined).
*/
//!@{
_FORMAT(strftime, 2, 0)
_MALLOC()
t_char*						Date_ToString(s_date const* date, t_char const* format);
#define c_strftime			Date_ToString
#define c_datetostr			Date_ToString
#define c_datefmt			Date_ToString
#define Date_Format			Date_ToString
#define Date_Print			Date_ToString
//!@}

//!@doc Creates a string representation of the given 'date', according to the given 'format' string
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/chrono/strftime}
**
**	@see Date_ToString
*/
//!@{
_FORMAT(strftime, 4, 0)
t_size						Date_ToString_N(t_char* dest, t_size max, s_date const* date, t_char const* format);
#define c_strnftime			Date_ToString_N
#define c_datetostrn		Date_ToString_N
#define c_datefmtn			Date_ToString_N
#define Date_Format_N		Date_ToString_N
#define Date_Print_N		Date_ToString_N
//!@}

//!@doc Creates a string representation of the given 'date', in standard (sortable) Unix format
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/strftime}
**
**	@see Date_Print
*/
//!@{
t_char*						Date_ToString_Unix(s_date const* date);
#define c_strftime_unix		Date_ToString_Unix
#define c_datetostr_unix	Date_ToString_Unix
#define c_dateunix			Date_ToString_Unix
#define Date_Format_Unix	Date_ToString_Unix
//!@}

//!@doc Creates a string representation of the current time in UTC, in standard (sortable) Unix format
/*!
**	@isostd{https://en.cppreference.com/w/c/chrono/strftime}
**
**	@see Date_Print
*/
//!@{
t_char*						DateNow_ToString_Unix(void);
#define c_datenow_unix		DateNow_ToString_Unix
#define c_utcnow_unix		DateNow_ToString_Unix
#define c_datenowtostr_unix	DateNow_ToString_Unix
#define c_utcnowtostr_unix	DateNow_ToString_Unix
#define DateNow_Format_Unix	DateNow_ToString_Unix
#define UTCNow_Format_Unix	DateNow_ToString_Unix
//!@}


/*
** ************************************************************************** *|
**                       Date-related utility functions                       *|
** ************************************************************************** *|
*/

//!@doc Returns `TRUE` if the given `date` is indeed a valid date according to the Gregorian/Astronomical calendar
/*!
**	@nonstd
*/
//!@{
t_bool					Date_IsValid(s_date const* date);
#define c_dateisvalid	Date_IsValid
//!@}

//!@doc Modifies the given `date`, to force its values to be constrained to their correct ranges
/*!
**	@nonstd
*/
//!@{
void					Date_MakeValid(s_date* date);
#define c_datetovalid	Date_MakeValid
//!@}



//!@doc Returns the amount of days in the given `month`
/*!
**	@nonstd, see https://en.wikipedia.org/wiki/Leap_year
**
**	@param	month	The month to check
**	@param	year	The year to check
**	@returns
**	`30` or `31` for most `month` values, the one exception being february:
**	when `month == MONTH_FEBRUARY`, will return `28`, or `29` if `Date_IsLeapYear(year)`.
*/
//!@{
t_uint					Date_DaysInMonth(e_month month, t_s32 year);
#define c_daysinmonth	Date_DaysInMonth
//!@}

//!@doc Returns the day of the week (according to `date->day_month` or `date->day_year`, as available)
/*!
**	@nonstd
**
**	@returns
**	The day of the week for the given `date` (according to `date->day_month` or `date->day_year`, as available)
*/
//!@{
e_weekday				Date_DayOfTheWeek(s_date* date);
#define c_dayofweek		Date_DayOfTheWeek
//!@}



//!@doc Returns `TRUE` if the given year is a leap year
/*!
**	@nonstd
**
**	@param	year	The year to check
*/
//!@{
t_bool					Date_IsLeapYear(t_s32 year);
#define c_isleapyear	Date_IsLeapYear
//!@}

//!@doc Returns `TRUE` if the given has a leap second on its last day
/*!
**	@nonstd, see https://en.wikipedia.org/wiki/Leap_second
**
**	@param	month	The month to check (typically June 30th, or December 31st)
**	@param	year	The year to check (leap seconds for future dates are not known)
*/
//!@{
t_bool					Date_HasLeapSecond(e_month month, t_s32 year);
#define c_hasleapsec	Date_HasLeapSecond
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
