
/*!@file test.h
**
**	How to create a testing function for a libccc function:
**	```c
**	void    print_test_<func>(char const* test_name, t_testflags flags,
**	        <args>)
**	{
**	    TEST_INIT(<test_type>)
**	    TEST_PERFORM_<test_kind>(<func>, <args>)
**	    TEST_PRINT(<test_type>, <func>, <printf_format_for_args>, <args>)
**	    TEST_FREE()
**	}
**	```
**	- `<func>`: name of the function (in C-like lowercase namingstyle, so that the preprocessor can check if the function is `#define`d or not, and run the test accordingly)
**	- `<args>`: the arguments that the function takes
**	- `<test_type>`: the suffix part of the testing result-check function to use (for the list of available testing functions, see `libccc/test/test-utils.h`, lines ~100 to ~200)
**	- `<test_kind>`: this suffix part of the `TEST_PERFORM_*()` macro function indicates if there exists an approriate counterpart function in the stdlibc, or if the expected test result is manually written for each test
**
**	How to create a test suite function for a libccc function:	
**	```c
**	void    test_<func>(void)
**	{
**	//  | TEST FUNCTION  | TEST NAME             | CAN SEGFAULT     | TEST ARGS
**	    print_test_<func>("<func> (<argdetails>)",<expects_segfault>, <test_args>)
**	}
**	```
**	- `<argdetails>`: short string which tells how this test in particular is special
**	- `<expects_segfault>`: whether or not this test passes or fails if the function segfaults
**	- `<printf_format_for_args>`: format string to show arguments given for this test, for the `libccc-test -a` flag
**	- `<test_args>`: the actual hardcoded literal values to give as arguments for this test
*/

#ifndef LIBCCC_TEST_H
#define LIBCCC_TEST_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/
#if (!defined(_WIN32) || defined(__MINGW32__))
#include <strings.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "libccc.h"

#include "test_catch.h"
#include "test_timer.h"
#include "test_utils.h"



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

//! This type stores info about a program argument (ie: `argc`/`argv`)
typedef struct test_arg
{
	void	(*handle_arg)();  //!< The function to execute for this program argument
	char		arg;          //!< The "character version" of this argument (ie: `-a`)
	char const*	name;         //!< The "string version" of this argument (ie: `--arg`)
	char const* description;  //!< The description for this argument (displayed when doing `--help`)
}	s_test_arg;
//! The amount of different arguments accepted by the test suite
#define TEST_ARGS_AMOUNT	10

//! This struct stores the program argument boolean flags
typedef struct test_flags
{
	bool	verbose;        //!< if `TRUE`, display all logger output for each test
	bool	show_args;      //!< if `TRUE`, display arguments given to each test
	bool	show_speed;     //!< if `TRUE`, display performance (execution speed) for each test
	bool	show_result;    //!< if `TRUE`, display result, even when test passed
	bool	show_errors;    //!< if `TRUE`, display any errors output by libccc during function execution
	bool	show_escaped;   //!< if `TRUE`, display strings with non-printable characters as escape sequences
	bool	test_nullptrs;  //!< if `TRUE`, perform all NULL pointer tests
	bool	test_overflow;  //!< if `TRUE`, perform all the libccc_convert overflowing number tests
}	s_test_config;



//! This struct stores the total amount of tests failed/passed
typedef struct test_totals
{
	int	tests;     //!< The total amount of tests ran.
	int	failed;    //!< The total amount of tests which had an ERROR result.
	int	warnings;  //!< The total amount of warnings issued by the test suite.
}	s_test_totals;

//! This struct stores one test suite (typically, one header file)
typedef struct test_suite
{
	bool		run;		//!< If 0, does not run
	char const*	name;		//!< Name for test suite to identify
	int		(*test)(void);	//!< Test suite launcher
	s_test_totals	totals;	//!< Stores the total amounts of tests ran/failed
}	s_test_suite;



typedef enum test_suite_libccc
{
#undef ENUM
#define ENUM(_name_, _func_, _enum_, ...) \
	_enum_,
#include "test_suites.enum"
#undef ENUM
}	e_test_suite_libccc;
//! The total amount of test suites for libccc
#define TEST_SUITE_AMOUNT	34



//! This struct holds all program state data
typedef struct program
{
	e_test_suite_libccc current_suite;			//!< Index of the currently running test suite
	bool			last_test_failed;			//!< Is `TRUE` if the latest test performed had an error.
	bool			last_test_warned;			//!< Is `TRUE` if the latest test performed issued a warning.
	char*			last_test_error;			//!< Contains any error output by libccc during the latest test
	s_test_config	config;						//!< Stores the main program argument options (as boolean flags)
	s_test_arg		args[TEST_ARGS_AMOUNT];		//!< Stores the chars/names and descriptions for each valid program argument
	s_test_suite	suites[TEST_SUITE_AMOUNT];	//!< Stores info of which test suites should be run or not
}	s_program;

//! Global variable to access the program state data from anywhere
extern s_program	g_test;



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

//! Initializes variables to prepare to run test suites
void	test_init(void);

/*
**	Test suite functions
*/
#undef ENUM
#define ENUM(_name_, _func_, _enum_, ...) \
int	_func_(void);
#include "test_suites.enum"
#undef ENUM

/*
**	Global variables used in tests
*/
extern char const* test1; extern t_size const test1_len;
extern char const* test2; extern t_size const test2_len;
extern char const* test3; extern t_size const test3_len;

extern char const* teststr_cc_c0;
extern char const* teststr_cc_c1;
extern char const* teststr_utf8_fr;
extern char const* teststr_utf8_ru;
extern char const* teststr_utf8_jp;
extern char const* teststr_utf8_ho;
extern char const* teststr_utf8_one_symbol_two_seq ;
extern char const* teststr_utf8_one_symbol_three_seq ;
extern char const* teststr_utf8_hardcore; extern t_size const teststr_utf8_hardcore_len; extern t_size const teststr_utf8_hardcore_bytelen;



int	print_results(s_test_suite const* suites);



#endif
