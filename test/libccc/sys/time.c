
#if (defined(_WIN32) && !defined(__MINGW32__))
	#include <time.h>
#else
	#include <sys/time.h>
#endif

#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/time.h"

#include "test.h"
#include "test_utils.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

#define SF_UTC	(SF_DATE_UNIX " " SF_TIME_UNIX)

/*
	.year		; Amount of years since 1900	
	.month		; [0,11] months since January
	.day_week	; [0,6] days since Sunday
	.day_month	; [1,31] day of the month
	.day_year	; [0,365] days since January 1 (max value is 365 every 4 years, otherwise 364)
	.hour		; [0,23] hours since midnight
	.min		; [0,59] minutes after the hour
	.sec		; [0,59(61)] seconds after the minute (usually 0-59 - there is extra range to accommodate for leap seconds)
	.is_dst		; If TRUE, then Daylight Savings Time is on
*/

#define DATE_STR_BUFFER		512
#define DATE_STR_FORMAT \
	" .year"      "=%4i," \
	" .month"     "=%2i," \
	" .day_month" "=%2u," \
	" .hour"      "=%2u," \
	" .min"       "=%2u," \
	" .sec"       "=%2u," \
	" .is_dst"    "=%5s," \
	" .offset"    "=%+i " \



char*	y99_str = "1999-01-01 00:00:00";
s_date	y99_date =
{
	.year		= 1999,
	.month		= MONTH_JANUARY,
	.day_week	= WEEKDAY_FRIDAY,
	.day_month	= 1,
	.day_year	= 0,
	.hour		= 0,
	.min		= 0,
	.sec		= 0,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	y2k_str = "2000-01-01 00:00:00";
s_date	y2k_date =
{
	.year		= 2000,
	.month		= MONTH_JANUARY,
	.day_week	= WEEKDAY_SATURDAY,
	.day_month	= 1,
	.day_year	= 0,
	.hour		= 0,
	.min		= 0,
	.sec		= 0,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	xmas_str = "1981-12-25 12:34:56";
s_date	xmas_date =
{
	.year		= 1981,
	.month		= MONTH_DECEMBER,
	.day_week	= WEEKDAY_FRIDAY,
	.day_month	= 25,
	.day_year	= 358,
	.hour		= 12,
	.min		= 34,
	.sec		= 56,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	ween_str = "2007-10-31 01:23:45";
s_date	ween_date =
{
	.year		= 2007,
	.month		= MONTH_OCTOBER,
	.day_week	= WEEKDAY_WEDNESDAY,
	.day_month	= 31,
	.day_year	= 303,
	.hour		= 1,
	.min		= 23,
	.sec		= 45,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	leap_year_str = "2008-02-29 12:30:05";
s_date	leap_year_date =
{
	.year		= 2008,
	.month		= MONTH_FEBRUARY,
	.day_week	= WEEKDAY_FRIDAY,
	.day_month	= 29,
	.day_year	= 59,
	.hour		= 12,
	.min		= 30,
	.sec		= 5,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	leap_second_str  = "2016-12-31 23:59:60";
char*	leap_second_str_ = "2016-12-31 23:59:59";
s_date	leap_second_date =
{
	.year		= 2016,
	.month		= MONTH_DECEMBER,
	.day_week	= WEEKDAY_SATURDAY,
	.day_month	= 31,
	.day_year	= 365,
	.hour		= 23,
	.min		= 59,
	.sec		= 60,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	bad_leap_year_str = "2007-02-29 12:30:05";
s_date	bad_leap_year_date =
{
	.year		= 2007,
	.month		= MONTH_FEBRUARY,
	.day_week	= WEEKDAY_THURSDAY,
	.day_month	= 29,
	.day_year	= 59,
	.hour		= 12,
	.min		= 30,
	.sec		= 5,
	.is_dst		= FALSE,
	.offset		= 0,
};

char*	bad_leap_second_str = "2015-12-31 23:59:60";
s_date	bad_leap_second_date =
{
	.year		= 2015,
	.month		= MONTH_DECEMBER,
	.day_week	= WEEKDAY_THURSDAY,
	.day_month	= 31,
	.day_year	= 364,
	.hour		= 23,
	.min		= 59,
	.sec		= 60,
	.is_dst		= FALSE,
	.offset		= 0,
};



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/



#ifndef c_datetostr
void test_datetostr(void)	{}
#warning "datetostr() test suite function defined, but the function isn't defined."
#else
void	print_test_datetostr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* format,
		s_date const* date)
{
	TEST_INIT(str)
	TEST_PERFORM(	datetostr, date, format)
	TEST_PRINT(str,	datetostr, "format=\"%s\", date = {" DATE_STR_FORMAT "}",
		format,
		date->year,
		date->month,
		date->day_month,
		date->hour,
		date->min,
		date->sec,
		BOOL_TOSTRING(date->is_dst),
		date->offset)
	TEST_FREE()
}
void	test_datetostr(void)
{
	time_t now_time = time(NULL);
	struct tm* now_tm = gmtime(&now_time);
	s_date now_date = Date_FromSTDC(now_tm);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, SF_UTC, now_tm);
/*	| TEST FUNCTION     | TEST NAME                  |TESTFLAG| EXPECTING              | TEST ARGS				*/
	print_test_datetostr("datetostr                  ",	FALSE,                  y99_str, SF_UTC, &y99_date);
	print_test_datetostr("datetostr                  ",	FALSE,                  y2k_str, SF_UTC, &y2k_date);
	print_test_datetostr("datetostr                  ",	FALSE,                  now_str, SF_UTC, &now_date);
	print_test_datetostr("datetostr                  ",	FALSE,                 xmas_str, SF_UTC, &xmas_date);
	print_test_datetostr("datetostr                  ",	FALSE,                 ween_str, SF_UTC, &ween_date);
	print_test_datetostr("datetostr (leap year)      ",	FALSE,            leap_year_str, SF_UTC, &leap_year_date);
	print_test_datetostr("datetostr (leap second)    ",	FALSE,         leap_second_str_, SF_UTC, &leap_second_date);
	print_test_datetostr("datetostr (bad leap year)  ",	FALSE,                     NULL, SF_UTC, &bad_leap_year_date);
	print_test_datetostr("datetostr (bad leap second)",	FALSE,                     NULL, SF_UTC, &bad_leap_second_date);
}
#endif



#ifndef c_strtodate
void test_strtodate(void)	{}
#warning "strtodate() test suite function defined, but the function isn't defined."
#else
void	print_test_strtodate(char const* test_name, t_testflags flags,
		s_date expecting,
		char const* format,
		char const* str)
{
	TEST_INIT(date)
	TEST_PERFORM(	strtodate, str, format)
	TEST_PRINT(date,strtodate, "format=\"%s\", str=\"%s\"", format, str)
}
void	test_strtodate(void)
{
	time_t now_time = time(NULL);
	struct tm* now_tm = gmtime(&now_time);
	s_date now_date = Date_FromSTDC(now_tm);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, SF_UTC, now_tm);
/*	| TEST FUNCTION     | TEST NAME                  |TESTFLAG| EXPECTING              | TEST ARGS				*/
	print_test_strtodate("strtodate                  ",	FALSE,                 y99_date, SF_UTC, y99_str);
	print_test_strtodate("strtodate                  ",	FALSE,                 y2k_date, SF_UTC, y2k_str);
	print_test_strtodate("strtodate                  ",	FALSE,                 now_date, SF_UTC, now_str);
	print_test_strtodate("strtodate                  ",	FALSE,                xmas_date, SF_UTC, xmas_str);
	print_test_strtodate("strtodate                  ",	FALSE,                ween_date, SF_UTC, ween_str);
	print_test_strtodate("strtodate (leap year)      ",	FALSE,           leap_year_date, SF_UTC, leap_year_str);
	print_test_strtodate("strtodate (leap second)    ",	FALSE,         leap_second_date, SF_UTC, leap_second_str);
	print_test_strtodate("strtodate (bad leap year)  ",	FALSE,       bad_leap_year_date, SF_UTC, bad_leap_year_str);
	print_test_strtodate("strtodate (bad leap second)",	FALSE,     bad_leap_second_date, SF_UTC, bad_leap_second_str);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/



int		testsuite_sys_time(void)
{
	print_suite_title("libccc/sys/time");

	test_datetostr();

	test_strtodate();

	// TODO

	return (OK);
}
