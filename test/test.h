
#ifndef LIBCCC_TEST_H
#define LIBCCC_TEST_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
	void	(*handle_arg)();	//!< The function to execute for this program argument
	char		arg;			//!< The "character version" of this argument (ie: `-a`)
	char const*	name;			//!< The "string version" of this argument (ie: `--arg`)
	char const* description;	//!< The description for this argument (displayed when doing `--help`)
}				s_test_arg;
//! The amount of different arguments accepted by the test suite
#define TEST_ARGS_AMOUNT	10

//! This struct stores the program argument boolean flags
typedef struct test_flags
{
	bool	verbose;		//!< if `TRUE`, display all logger output for each test
	bool	show_args;		//!< if `TRUE`, display arguments given to each test
	bool	show_speed;		//!< if `TRUE`, display performance (execution speed) for each test
	bool	show_result;	//!< if `TRUE`, display result, even when test passed
	bool	show_errors;	//!< if `TRUE`, display any errors output by libccc during function execution
	bool	show_escaped;	//!< if `TRUE`, display strings with non-printable characters as escape sequences
	bool	test_nullptrs;	//!< if `TRUE`, perform all NULL pointer tests
	bool	test_overflow;	//!< if `TRUE`, perform all the libccc_convert overflowing number tests
}				s_test_flags;



//! This struct stores one test suite (typically, one header file)
typedef struct test_suite
{
	bool		run;		//!< If 0, does not run
	char const*	name;		//!< Name for test suite to identify
	int		(*test)(void);	//!< Test suite launcher
}				s_test_suite;
#define TEST_SUITE_AMOUNT	30

//! This struct stores the total amount of tests failed/passed
typedef struct test_totals
{
	int		tests;	//!< The total amount of tests ran.
	int		failed; //!< The amount of tests which had an ERROR result.
}				s_test_totals;



//! This struct holds all program state data
typedef struct program
{
	bool			last_test_failed;			//!< is `TRUE` if the latest test performed had an error.
	char*			last_test_error;			//!< contains any error output by libccc during the latest test
	s_test_totals	totals;						//!< Stores the total amounts of tests ran/failed
	s_test_flags	flags;						//!< Stores the main program argument options (as boolean flags)
	s_test_arg		args[TEST_ARGS_AMOUNT];		//!< Stores the chars/names and descriptions for each valid program argument
	s_test_suite	suites[TEST_SUITE_AMOUNT];	//!< Stores info of which test suites should be run or not
}				s_program;

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
int		testsuite_bool(void);
int		testsuite_char(void);
int		testsuite_int(void);
int		testsuite_fixed(void);
int		testsuite_float(void);
int		testsuite_memory(void);
int		testsuite_pointer(void);
int		testsuite_pointerarray(void);
int		testsuite_string(void);
int		testsuite_stringarray(void);
int		testsuite_color(void);
int		testsuite_sys_io(void);
int		testsuite_sys_time(void);
int		testsuite_sys_regex(void);
int		testsuite_math(void);
int		testsuite_math_int(void);
int		testsuite_math_fixed(void);
int		testsuite_math_float(void);
int		testsuite_math_stat(void);
int		testsuite_math_algebra(void);
int		testsuite_math_complex(void);
int		testsuite_math_random(void);
int		testsuite_math_vlq(void);
int		testsuite_monad_array(void);
int		testsuite_monad_list(void);
//int	testsuite_monad_stack(void);
//int	testsuite_monad_queue(void);
int		testsuite_monad_dict(void);
int		testsuite_monad_tree(void);
int		testsuite_monad_object(void);
int		testsuite_encode_json(void);
int		testsuite_encode_toml(void);
//int	testsuite_encode_yaml(void);
//int	testsuite_encode_xml(void);

/*
**	Global variables used in tests
*/
extern char const* test1; extern t_size const test1_len;
extern char const* test2; extern t_size const test2_len;
extern char const* test3; extern t_size const test3_len;



#endif
