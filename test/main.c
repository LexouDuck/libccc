
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>

#include "test.h"



static char const* program_name = NULL;

/*
** ************************************************************************** *|
**                           Global Testing Variables                         *|
** ************************************************************************** *|
*/

char const* test1 = "Omae wa mou shindeiru.\0";		t_size const test1_len = 23;
char const* test2 = "Nani???\0";					t_size const test2_len = 8;
char const* test3 = "Un ange mange de la fange.\0";	t_size const test3_len = 27;



s_program	g_test;



/*
** ************************************************************************** *|
**                           Main Program Definitions                         *|
** ************************************************************************** *|
*/

static void	handle_arg_verbose()		{ g_test.flags.verbose		 = TRUE; }
static void	handle_arg_show_args()		{ g_test.flags.show_args	 = TRUE; }
static void	handle_arg_show_errors()	{ g_test.flags.show_errors	 = TRUE; }
static void	handle_arg_show_result()	{ g_test.flags.show_result	 = TRUE; }
static void	handle_arg_show_escaped()	{ g_test.flags.show_escaped	 = TRUE; }
static void handle_arg_show_speed()		{ g_test.flags.show_speed	 = TRUE; }
static void	handle_arg_test_nullptrs()	{ g_test.flags.test_nullptrs = TRUE; }
static void	handle_arg_test_overflow()	{ g_test.flags.test_overflow = TRUE; }
static void	handle_arg_test_all()
{
	g_test.flags.test_nullptrs = TRUE;
	g_test.flags.test_overflow = TRUE;
}

/*
**	This function initializes the global variable 'g_test', which is used everywhere.
*/
static void	init(void)
{
	// default every option to FALSE
	memset(&g_test.flags, 0, sizeof(s_test_flags));

	static const s_test_suite suites[TEST_SUITE_AMOUNT] =
	{
		(s_test_suite){ FALSE, "bool",				testsuite_bool },
		(s_test_suite){ FALSE, "char",				testsuite_char },
		(s_test_suite){ FALSE, "int",				testsuite_int },
		(s_test_suite){ FALSE, "fixed",				testsuite_fixed },
		(s_test_suite){ FALSE, "float",				testsuite_float },
		(s_test_suite){ FALSE, "memory",			testsuite_memory },
		(s_test_suite){ FALSE, "pointer",			testsuite_pointer },
		(s_test_suite){ FALSE, "pointerarray",		testsuite_pointerarray },
		(s_test_suite){ FALSE, "string",			testsuite_string },
		(s_test_suite){ FALSE, "stringarray",		testsuite_stringarray },
		(s_test_suite){ FALSE, "color",				testsuite_color },
//		(s_test_suite){ FALSE, "text/ascii",		testsuite_text_ascii },
//		(s_test_suite){ FALSE, "text/unicode",		testsuite_text_unicode },
		(s_test_suite){ FALSE, "text/regex",		testsuite_text_regex },
		(s_test_suite){ FALSE, "sys/io",			testsuite_sys_io },
		(s_test_suite){ FALSE, "sys/time",			testsuite_sys_time },
		(s_test_suite){ FALSE, "math/math",			testsuite_math },
		(s_test_suite){ FALSE, "math/int",			testsuite_math_int },
		(s_test_suite){ FALSE, "math/fixed",		testsuite_math_fixed },
		(s_test_suite){ FALSE, "math/float",		testsuite_math_float },
		(s_test_suite){ FALSE, "math/stat",			testsuite_math_stat },
		(s_test_suite){ FALSE, "math/algebra",		testsuite_math_algebra },
		(s_test_suite){ FALSE, "math/complex",		testsuite_math_complex },
		(s_test_suite){ FALSE, "math/random",		testsuite_math_random },
		(s_test_suite){ FALSE, "math/vlq",			testsuite_math_vlq },
		(s_test_suite){ FALSE, "monad/array",		testsuite_monad_array },
		(s_test_suite){ FALSE, "monad/list",		testsuite_monad_list },
//		(s_test_suite){ FALSE, "monad/stack",		testsuite_monad_stack },
//		(s_test_suite){ FALSE, "monad/queue",		testsuite_monad_queue },
		(s_test_suite){ FALSE, "monad/dict",		testsuite_monad_dict },
		(s_test_suite){ FALSE, "monad/tree",		testsuite_monad_tree },
		(s_test_suite){ FALSE, "monad/object",		testsuite_monad_object },
		(s_test_suite){ FALSE, "encode/kvt",		testsuite_encode_kvt },
		(s_test_suite){ FALSE, "encode/json",		testsuite_encode_json },
		(s_test_suite){ FALSE, "encode/toml",		testsuite_encode_toml },
//		(s_test_suite){ FALSE, "encode/yaml",		testsuite_encode_yaml },
//		(s_test_suite){ FALSE, "encode/xml",		testsuite_encode_xml },
	};
	memcpy(g_test.suites, suites, sizeof(s_test_suite) * TEST_SUITE_AMOUNT);

	static const s_test_arg args[TEST_ARGS_AMOUNT] =
	{
		(s_test_arg){ NULL,						'h', "help",			"If provided, output only the program usage help and exit." },
		(s_test_arg){ handle_arg_verbose,		'v', "verbose",			"If provided, output each test result (as either 'OK!' or 'ERROR: return was _')." },
		(s_test_arg){ handle_arg_show_args,		'a', "show-args",		"If provided, output the arguments used for each test performed." },
		(s_test_arg){ handle_arg_show_errors,	'e', "show-errors",		"If provided, output any errors that occurred during function execution, with the default libccc error handler." },
		(s_test_arg){ handle_arg_show_result,	'r', "show-result",		"If provided, output the result for each test performed, even when passed." },
		(s_test_arg){ handle_arg_show_escaped,	's', "show-escaped",	"If provided, output any non-printable characters as a backslash C escape sequence." },
		(s_test_arg){ handle_arg_show_speed,	'p', "show-performance","If provided, output the execution speed for each test performed." },
		(s_test_arg){ handle_arg_test_all,		't', "test-all",		"Sets all the 'test-something' arguments below (is equivalent to doing '-no')" },
		(s_test_arg){ handle_arg_test_nullptrs,	'n', "test-nullptrs",	"If provided, perform the NULL pointer tests for all functions." },
		(s_test_arg){ handle_arg_test_overflow,	'o', "test-overflow",	"If provided, perform the overflowing number tests for 'libccc_convert' functions." },
	};
	memcpy(g_test.args, args, sizeof(s_test_arg) * TEST_ARGS_AMOUNT);
}



/*
** ************************************************************************** *|
**                             Main Program Logic                             *|
** ************************************************************************** *|
*/

// A special return value to signal when a help argument has been provided by the user
#define MATCHED_HELP	((int)-1)



static int	handle_args_test_suites(char const* arg)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.suites[i].name))
		{
			g_test.suites[i].run = TRUE;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	handle_args_option_char(char arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (arg == g_test.args[i].arg)
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	handle_args_option_string(char const* arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (str_equals(arg, g_test.args[i].name))
		{
			if (g_test.args[i].handle_arg)
				g_test.args[i].handle_arg();
			else return (MATCHED_HELP);
			return (TRUE);
		}
	}
	return (FALSE);
}



int	main(int argc, char** argv)
{
	if (argc < 1 || argv == NULL || argv[0] == NULL)
	{
		print_error("Invalid platform, no 'argv' program argument list received.");
		return (ERROR);
	}
	program_name = argv[0];

	init();
	init_segfault_handler();

	// Handle main program arguments
	int	match;
	int tmp;
	for (int i = 1; i < argc; ++i)
	{
		match = FALSE;
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '\0')
			{
				print_error("Unexpected end of argument after '-'.");
				continue;
			}
			else if (argv[i][1] == '-')
			{
				match = handle_args_option_string(argv[i] + 2);
			}
			else for (size_t j = 1; j < strlen(argv[i]); ++j)
			{
				tmp = handle_args_option_char(argv[i][j]);
				if (match)
					match = (tmp == MATCHED_HELP ? tmp : match);
				else match = tmp;
			}
		}
		else if (isalpha(argv[i][0]))
		{
			match = handle_args_test_suites(argv[i]);
		}

		if (match == FALSE)
		{
			print_error("Argument not recognized (%s)\n", argv[i]);
			print_usage(program_name);
			return (ERROR);
		}
		else if (match == MATCHED_HELP)
		{
			print_usage(program_name);
			return (OK);
		}
	}

	// Run the appropriate test suites
	print_title();
	print_endian_warning();
	test_init();
	s_test_totals suite;
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (g_test.suites[i].run)
		{
			suite = g_test.totals;
			g_test.suites[i].test();
			suite.tests = g_test.totals.tests - suite.tests;
			suite.failed = g_test.totals.failed - suite.failed;
			if (suite.tests)
				print_totals(suite.tests, suite.failed, g_test.suites[i].name);
		}
	}
	print_totals(g_test.totals.tests, g_test.totals.failed, NULL);
	return (g_test.totals.failed);
}
