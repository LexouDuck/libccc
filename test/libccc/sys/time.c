
#include <time.h>
#include <sys/time.h>

#include "libccc/sys/time.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

#define FORMAT_UTC	(FORMAT_DATE_UNIX" "FORMAT_TIME_UNIX)

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
#define DATE_STR_FORMAT	\
	" .year"      "=%i," \
	" .month"     "=%i," \
	" .day_month" "=%u," \
	" .hour"      "=%u," \
	" .min"       "=%u," \
	" .sec"       "=%u," \
	" .is_dst"    "=%s " \



char*	y99_str = "1999-01-01 00:00:00";
s_date	y99_date = (s_date)
{
	.year		= 99,
	.month		= MONTH_JANUARY,
	.day_week	= WEEKDAY_FRIDAY,
	.day_month	= 1,
	.day_year	= 0,
	.hour		= 0,
	.min		= 0,
	.sec		= 0,
	.is_dst		= FALSE,
};
char*	y2k_str = "2000-01-01 00:00:00";
s_date	y2k_date = (s_date)
{
	.year		= 100,
	.month		= MONTH_JANUARY,
	.day_week	= WEEKDAY_SATURDAY,
	.day_month	= 1,
	.day_year	= 0,
	.hour		= 0,
	.min		= 0,
	.sec		= 0,
	.is_dst		= FALSE,
};



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/



#ifndef c_datetostr
void test_datetostr(void)	{}
#else
void	print_test_datetostr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* format,
		s_date const* date)
{
	TEST_PERFORM_RESULT(datetostr, date, format)
	print_test_str(test_name, "_datetostr", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("date = {"DATE_STR_FORMAT"}",
		date->year + 1900,
		date->month,
		date->day_month,
		date->hour,
		date->min,
		date->sec,
		BOOL_TOSTRING(date->is_dst))
}
void	test_datetostr(void)
{
	time_t now_time = time(NULL);
	struct tm* now_tm = gmtime(&now_time);
	s_date now_date = Date_FromSTDC(now_tm);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, FORMAT_UTC, now_tm);
/*	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING              | TEST ARGS				*/
	print_test_datetostr("datetostr                 ",	FALSE,                  y99_str, FORMAT_UTC, &y99_date);
	print_test_datetostr("datetostr                 ",	FALSE,                  y2k_str, FORMAT_UTC, &y2k_date);
	print_test_datetostr("datetostr                 ",	FALSE,                  now_str, FORMAT_UTC, &now_date);
}
#endif



#ifndef c_strtodate
void test_strtodate(void)	{}
#else
void	print_test_strtodate(char const* test_name, int can_segfault,
		s_date const* expecting,
		char const* format,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(s_date, strtodate, str, format)
	print_test_date(test_name, "_strtodate", &result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("format=\"%s\", str=\"%s\"", format, str)
}
void	test_strtodate(void)
{
	time_t now_time = time(NULL);
	struct tm* now_tm = gmtime(&now_time);
	s_date now_date = Date_FromSTDC(now_tm);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, FORMAT_UTC, now_tm);
/*	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING              | TEST ARGS				*/
	print_test_strtodate("strtodate                 ",	FALSE,                &y99_date, FORMAT_UTC, y99_str);
	print_test_strtodate("strtodate                 ",	FALSE,                &y2k_date, FORMAT_UTC, y2k_str);
	print_test_strtodate("strtodate                 ",	FALSE,                &now_date, FORMAT_UTC, now_str);
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
