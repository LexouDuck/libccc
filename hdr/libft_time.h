/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_time.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBFT_TIME_H
#define __LIBFT_TIME_H
/*! @file libft_time.h
**	This header defines all the functions for date & time related functions.
**	@addtogroup libft_time
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

#include <sys/time.h>
#ifndef __APPLE__
	#define _XOPEN_SOURCE 600
	#include <time.h>
#endif

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! The standard type used to represent a date+time (smallest unit is seconds)
/*!
**	This type stores integer standard UNIX epoch time, so that means that a value of zero
**	corresponds to midnight (00:00:00), January 1, 1970, UTC (Coordinated Universal Time)
*/
typedef time_t		t_time;

#define TIME_NULL	((t_time)0)



//! This enum lists each day of the week, Sunday counting as zero
typedef enum	e_weekday_
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

#define WEEKDAY_SUN		WEEKDAY_SUNDAY
#define WEEKDAY_MON		WEEKDAY_MONDAY
#define WEEKDAY_TUE		WEEKDAY_TUESDAY
#define WEEKDAY_WED		WEEKDAY_WEDNESDAY
#define WEEKDAY_THU		WEEKDAY_THURSDAY
#define WEEKDAY_FRI		WEEKDAY_FRIDAY
#define WEEKDAY_SAT		WEEKDAY_SATURDAY

//! This global constant stores all the string names of the WEEKDAY enum, in lowercase
extern char const* const g_time_day[ENUMLENGTH_WEEKDAY];
//! This global constant stores all the string names of the WEEKDAY enum, abbreviated to 3 letters
extern char const* const g_time_day_abbreviated[ENUMLENGTH_WEEKDAY];



//! This enum lists each month of the year, January counting as zero
typedef enum	e_month_
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
extern char const* const g_time_month[ENUMLENGTH_MONTH];
//! This global constant stores all the string names of the MONTH enum, abbreviated to 3 letters
extern char const* const g_time_month_abbreviated[ENUMLENGTH_MONTH];



//! This enum allows one
/*!
**	This enum is based on the UTC time system - as such, it is not so much an enum but a signed integer.
**	The idea is to notate timezones in the commonly accepted UTC format (eg: UTC+01, UTC-06, etc)
**	There are several defines below that are meant to be used within this type:
**	@see TIMEZONE_GMT,
**		 TIMEZONE_EST,
**		 TIMEZONE_CST,
**		 TIMEZONE_MST,
**		 TIMEZONE_PST,
**		 TIMEZONE_EDT,
**		 TIMEZONE_CDT,
**		 TIMEZONE_MDT,
**		 TIMEZONE_PDT,
*/
typedef enum	e_timezone
{
	TIMEZONE_UTC = 0,
}				e_timezone;

// Commonly used timezones
#define TIMEZONE_GMT	(TIMEZONE_UTC)		//!< Timezone (UTC 00): Greenwich Mean Time
#define TIMEZONE_UTCMIN	(TIMEZONE_UTC-12)	//!< Timezone (UTC-12): The minimum UTC timezone (most late)
#define TIMEZONE_UTCMAX	(TIMEZONE_UTC+12)	//!< Timezone (UTC+12): The maximum UTC timezone (most early)
// NAST
#define TIMEZONE_EST	(TIMEZONE_UTC-5)	//!< Timezone (UTC-05): North American Eastern Standard Time
#define TIMEZONE_CST	(TIMEZONE_UTC-6)	//!< Timezone (UTC-06): North American Central Standard Time
#define TIMEZONE_MST	(TIMEZONE_UTC-7)	//!< Timezone (UTC-07): North American Mountain Standard Time
#define TIMEZONE_PST	(TIMEZONE_UTC-8)	//!< Timezone (UTC-08): North American Pacific Standard Time
// NADT
#define TIMEZONE_EDT	(TIMEZONE_UTC-4)	//!< Timezone (UTC-04): North American Eastern Daylight Time
#define TIMEZONE_CDT	(TIMEZONE_UTC-5)	//!< Timezone (UTC-05): North American Central Daylight Time
#define TIMEZONE_MDT	(TIMEZONE_UTC-6)	//!< Timezone (UTC-06): North American Mountain Daylight Time
#define TIMEZONE_PDT	(TIMEZONE_UTC-7)	//!< Timezone (UTC-07): North American Pacific Daylight Time



//! This struct is used to store a "precise time", smallest unit is nanoseconds
/*!
**	This struct is equivalent to the ISO C library's 'struct timespec',
**	although it's sub-fields have different names:
**		tv_sec	->	sec
**		tv_nsec	->	nanosec
*/
typedef struct	s_timespec_
{
	t_time		sec;
	t_s64		nanosec;
}				s_timespec;
// typedef struct timespec	s_timespec;

#define TIMESPEC_NULL	((s_timespec){0})



//! This struct is used to store all aspects about a certain date/time (equivalent to 'struct tm')
/*!
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
typedef struct	s_date_
{
	t_u8		sec;		//!< [0,59(61)] seconds after the minute (usually 0-59 - there is extra range to accommodate for leap seconds)
	t_u8		min;		//!< [0,59] minutes after the hour
	t_u8		hour;		//!< [0,23] hours since midnight
	e_weekday	day_week;	//!< [0,6] days since Sunday
	t_u8		day_month;	//!< [1,31] day of the month
	t_s32		day_year;	//!< [0,365] days since January 1 (max value is 365 every 4 years, otherwise 364)
	e_month		month;		//!< [0,11] months since January
	t_s32		year;		//!< Amount of years since 1900	
	t_bool		is_dst;		//!< if TRUE, then Daylight Savings Time is on
}				s_date;
// typedef struct tm	s_time

#define DATE_NULL	((s_date){0})



#define TIME_MAX_SECONDS	(60)	//!< The amount of seconds in a minute
#define TIME_MAX_MINUTES	(60)	//!< The amount of minutes in an hour
#define TIME_MAX_HOURS		(24)	//!< The amount of hours in a day
#define TIME_MAX_DAYS_MONTH	(31)	//!< The amount of days in a month
#define TIME_MAX_DAYS_YEAR	(365)	//!< The amount of days in a year

#define TIME_MAX_LEAP_SECONDS	(62)	//!< The amount of seconds in a minute (accounting for leap seconds)
#define TIME_MAX_LEAP_DAYS_YEAR	(366)	//!< The amount of days in a year (when accounting for leap 4 years)



/*
** ************************************************************************** *|
**                         Basic Date/Time Operations                         *|
** ************************************************************************** *|
*/

//! Returns the current UTC timestamp, according to the system clock
t_time					Time_Now(void);
#define ft_time			Time_Now
#define ft_time_now		Time_Now

//! Changes the value of the given time 'value', from the 'old' timezone to the 'new' one
t_time					Time_SetTimezone(t_time value, e_timezone old, e_timezone new);
#define ft_tzset		Time_SetTimezone
#define ft_time_set_tz	Time_SetTimezone



//! Converts the given 't_time value' to its equivalent 's_date' representation (in UTC)
s_date						Time_To_Date_UTC(t_time const value);
#define ft_time_to_date_utc	Time_To_Date_UTC
//! Converts the given 't_time value' to its equivalent 's_date' representation (according to the system timezone)
s_date						Time_To_Date_LocalTime(t_time const value);
#define ft_time_to_date		Time_To_Date_LocalTime
//! Converts the given 't_time value' to its equivalent 's_date' representation, according to the given 'timezone'
s_date						Time_To_Date_Timezone(t_time const value, e_timezone timezone);
#define ft_time_to_date_tz	Time_To_Date_Timezone



//! Converts the given 's_date value' to its equivalent 't_time' representation (in UTC)
t_time						Date_To_Time_UTC(s_date const* value);
#define ft_date_to_time_utc	Date_To_Time_UTC
//! Converts the given 's_date value' to its equivalent 't_time' representation (according to the system timezone)
t_time						Date_To_Time_LocalTime(s_date const* value);
#define ft_date_to_time		Date_To_Time_LocalTime
//! Converts the given 's_date value' to its equivalent 't_time' representation, according to the given 'timezone'
t_time						Date_To_Time_Timezone(s_date const* value, e_timezone timezone);
#define ft_date_to_time_tz	Date_To_Time_Timezone



//! Converts the given 's_date' struct to its ISO STD LIBC 'struct tm' equivalent
struct tm					Date_To_STDC(s_date const* date);
#define ft_date_to_stdc		Date_To_STDC
//! Converts the given ISO STD LIBC 'struct tm' to its 's_date' struct equivalent
s_date						STDC_To_Date(struct tm const* value);
#define ft_stdc_to_date		STDC_To_Date



//! Converts the given 's_date' struct to its ISO STD LIBC 'struct tm' equivalent
struct timespec				Timespec_To_STDC(s_timespec const* value);
#define ft_timespec_to_stdc	Timespec_To_STDC
//! Converts the given ISO STD LIBC 'struct tm' to its 's_date' struct equivalent
s_timespec					STDC_To_Timespec(struct timespec const* value);
#define ft_stdc_to_timespec	STDC_To_Timespec



/*! @} */
HEADER_END
#endif
