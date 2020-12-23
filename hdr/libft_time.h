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

//! The standard type used to represent a date+time stamp (smallest unit is seconds)
/*!
**	This type stores integer standard UNIX epoch time, so that means that a value of zero
**	corresponds to midnight (00:00:00), January 1, 1970, UTC (Coordinated Universal Time)
*/
typedef time_t		t_time;

#define TIME_NULL	((t_time)0)



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



//! This struct is used to store all aspects about a certain date/time (equivalent to 'struct tm')
/*!
**	This struct is equivalent to the ISO C library's 'struct timespec',
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



#define TIME_MAX_SECONDS	60
#define TIME_MAX_MINUTES	60
#define TIME_MAX_HOURS		24
#define TIME_MAX_DAYS_MONTH	31
#define TIME_MAX_DAYS_YEAR	365

#define TIME_MAX_LEAP_SECONDS	62
#define TIME_MAX_LEAP_YEARS		366



/*
** ************************************************************************** *|
**                         Basic Date/Time Operations                         *|
** ************************************************************************** *|
*/

//! Returns the current UTC timestamp, according to the system clock
t_time					Time_Now(void);
#define ft_time			Time_Now
#define ft_time_now		Time_Now



//! Converts the given 't_time value' to its equivalent 's_date' representation (in UTC)
s_date						Time_To_Date_UTC(t_time const value);
#define ft_time_to_date_utc	Time_To_Date_UTC

//! Converts the given 't_time value' to its equivalent 's_date' representation (according to the system timezone)
s_date						Time_To_Date_LocalTime(t_time const value);
#define ft_time_to_date		Time_To_Date_LocalTime



//! Converts the given 's_date value' to its equivalent 't_time' representation (in UTC)
t_time						Date_To_Time_UTC(s_date const* value);
#define ft_date_to_time_utc	Date_To_Time_UTC

//! Converts the given 's_date value' to its equivalent 't_time' representation (according to the system timezone)
t_time						Date_To_Time_LocalTime(s_date const* value);
#define ft_date_to_time		Date_To_Time_LocalTime



//! Converts the given 's_date' struct to its ISO STD LIBC 'struct tm' equivalent
struct tm					Date_To_STDC(s_date const* date);
#define ft_date_to_stdc		Date_To_STDC

//! Converts the given ISO STD LIBC 'struct tm' to its 's_date' struct equivalent
s_date						STDC_To_Date(struct tm const* value);
#define ft_stdc_to_date		STDC_To_Date



/*! @} */
HEADER_END
#endif
