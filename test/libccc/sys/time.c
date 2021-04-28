
#include "libccc/sys/time.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

#define FORMAT_UTC	(FORMAT_DATE_UNIX" "FORMAT_TIME_UNIX)



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
	.sec = 0,		//!< [0,59(61)] seconds after the minute (usually 0-59 - there is extra range to accommodate for leap seconds)
	.min = 0,		//!< [0,59] minutes after the hour
	.hour = 0,		//!< [0,23] hours since midnight
	.day_week = 0,	//!< [0,6] days since Sunday
	.day_month = 1,	//!< [1,31] day of the month
	.day_year = 0,	//!< [0,365] days since January 1 (max value is 365 every 4 years, otherwise 364)
	.month = 0,		//!< [0,11] months since January
	.year = 99,		//!< Amount of years since 1900	
	.is_dst = FALSE,//!< If TRUE, then Daylight Savings Time is on
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
	/*
	s_date now = c_date();
	struct tm now_tm = Date_ToSTDC(&now);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, FORMAT_UTC, &now_tm);
	*/
/*	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING              | TEST ARGS				*/
//	print_test_datetostr("datetostr                 ",	FALSE,                  now_str, FORMAT_UTC, &now);
	print_test_datetostr("datetostr                 ",	FALSE,                  y99_str, FORMAT_UTC, &y99_date);
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
	/*
	s_date now = c_date();
	struct tm now_tm = Date_ToSTDC(&now);
	char now_str[DATE_STR_BUFFER];
	strftime(now_str, DATE_STR_BUFFER, FORMAT_UTC, &now_tm);
	*/
/*	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING              | TEST ARGS				*/
//	print_test_strtodate("strtodate                 ",	FALSE,                     &now, FORMAT_UTC, now_str);
	print_test_strtodate("strtodate                 ",	FALSE,                &y99_date, FORMAT_UTC, y99_str);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/



int		testsuite_sys_time(void)
{
	print_suite_title("sys/time");

	test_datetostr();

	test_strtodate();

	// TODO

	return (OK);
}
