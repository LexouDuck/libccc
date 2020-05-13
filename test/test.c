
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include <signal.h>

#include "test.h"



/*
** ************************************************************************** *|
**                           Global Testing Variables                         *|
** ************************************************************************** *|
*/

// default every option to FALSE
s_test_flags	g_flags = (s_test_flags){ FALSE, FALSE, FALSE };

char const* test1 = "Omae wa mou shindeiru.\0";		size_t const test1_len = 23;
char const* test2 = "Nani???\0";					size_t const test2_len = 8;
char const* test3 = "Un ange mange de la fange.\0";	size_t const test3_len = 27;



/*
** ************************************************************************** *|
**                              Segfault Handling                             *|
** ************************************************************************** *|
*/

char*	nullstr	= "(NULL)";
char*	segstr	= "(segfault)";

void	segfault_handler(int sig, siginfo_t *info, void *ptr)
{
    if (sig == SIGSEGV)
    {
        longjmp(restore, SIGSEGV);
    }
}

void	init_segfault_handler()
{
	memset(&sig, 0, sizeof(sigaction));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags     = SA_NODEFER;
	sig.sa_sigaction = segfault_handler;
	sigaction(SIGSEGV, &sig, NULL);
}



/*
** ************************************************************************** *|
**                           Main Program Definitions                         *|
** ************************************************************************** *|
*/

typedef struct	s_test_suite_
{
	bool		run;
	char const*	name;
	int		(*test)(void);
}				s_test_suite;

#define TEST_SUITE_AMOUNT	12
s_test_suite	test_suites[TEST_SUITE_AMOUNT] =
{
	(s_test_suite){ FALSE, "memory",		test_memory },
	(s_test_suite){ FALSE, "char",			test_char },
	(s_test_suite){ FALSE, "string",		test_string },
	(s_test_suite){ FALSE, "stringarray",	test_stringarray },
	(s_test_suite){ FALSE, "convert",		test_convert },
	(s_test_suite){ FALSE, "color",			test_color },
	(s_test_suite){ FALSE, "list",			test_list },
	(s_test_suite){ FALSE, "math",			test_math },
	(s_test_suite){ FALSE, "stat",			test_stat },
	(s_test_suite){ FALSE, "random",		test_random },
	(s_test_suite){ FALSE, "vlq",			test_vlq },
	(s_test_suite){ FALSE, "io",			test_io },
};



static void	handle_arg_verbose()	{ g_flags.verbose = TRUE; }
static void	handle_arg_arguments()	{ g_flags.show_args = TRUE; }
static void	handle_arg_overflow()	{ g_flags.test_overflow = TRUE; }

typedef struct	s_test_arg_
{
	void	(*handle_arg)();
	char		arg;
	char const*	name;
	char const* description;
}				s_test_arg;

#define TEST_ARGS_AMOUNT	3
s_test_arg	test_args[TEST_ARGS_AMOUNT] =
{
	(s_test_arg){ handle_arg_verbose,	'v', "verbose",		"If provided, output each test result (as either 'OK!' or 'ERROR: return was _')." },
	(s_test_arg){ handle_arg_arguments,	'a', "arguments",	"If provided, output the arguments used for each test performed." },
	(s_test_arg){ handle_arg_overflow,	'o', "overflow",	"If provided, perform the overflowing number tests for 'libft_convert' functions." },
};



/*
** ************************************************************************** *|
**                             Main Program Logic                             *|
** ************************************************************************** *|
*/



void	print_nonstd(void)
{
printf("\n");
	printf("\n==>\t"C_BLUE"The following tests are for the functions of this category\n"
		"\twhich are not present in the standard C library."C_RESET);
}

void	print_usage(void)
{
	printf("\nUSAGE");
	printf("\n\t./%s [TEST_SUITES] [OPTIONS]", __FILE__);
	printf("\n");
	printf("\nTEST_SUITES");
	printf("\n    If none of these arguments are provided, all of the test suites will be run.");
	printf("\n    Each of the following arguments runs the corresponding test suite (ie: sequence of unit tests):");
	for (int j = 0; j < TEST_SUITE_AMOUNT; ++j)
	{
		printf("\n\t%s", test_suites[j].name);
	}
	printf("\n");
	printf("\nOPTIONS");
	printf("\n    If none of these arguments are provided, this program will only output the total amount of tests passed/failed.");
	printf("\n    Here is the list of accepted options, both in '-c' char format, and '--string' string format:");
	for (int j = 0; j < TEST_ARGS_AMOUNT; ++j)
	{
		printf("\n\t-%c or --%s\t%s", test_args[j].arg, test_args[j].name, test_args[j].description);
	}
	printf("\n\n");
}

void	print_error_argument(char const * arg)
{
	printf(C_RED"Error: "C_RESET"Argument not recognized (%s)\n", arg);
}



static bool	handle_args_test_suites(char const * arg)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (str_equals(arg, test_suites[i].name))
		{
			test_suites[i].run = TRUE;
			return (TRUE);
		}
	}
	return (FALSE);
}

static bool	handle_args_option_char(char arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (arg == test_args[i].arg)
		{
			test_args[i].handle_arg();
			return (TRUE);
		}
	}
	return (FALSE);
}

static bool	handle_args_option_string(char const * arg)
{
	for (int i = 0; i < TEST_ARGS_AMOUNT; ++i)
	{
		if (str_equals(arg, test_args[i].name))
		{
			test_args[i].handle_arg();
			return (TRUE);
		}
	}
	return (FALSE);
}



static bool	check_no_test_suites(void)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (test_suites[i].run)
			return (FALSE);
	}
	return (TRUE);
}



int		main(int argc, char **argv)
{
	init_segfault_handler();

	printf("   __   __ ___   _____ ______    ______ _____ ___  ______\n");
	printf("  / /  / // . | / ___//_  __/   /_  __//  __// __|/_  __/\n");
	printf(" / /_ / // , < / __/   / /       / /  /  _/ _\\_ \\  / /   \n");
	printf("/___//_//___-'/_/     /_/       /_/  /____/ \\__-' /_/    \n");
	printf("                                  ==> by duquesne @ 42.fr\n");
	int n = 1;
	if (*(char *)&n == 1)
		 printf("\n\n"C_GREEN"/!\\ Processor is Little-Endian (all tests should work reliably and can be trusted)"C_RESET);
	else printf("\n\n"C_RED"/!\\ Processor is Big-Endian (errors may arise in certain tests, like 'uint' tests for mem functions)"C_RESET);

	printf("\n\n"C_YELLOW"NB: All the tests with written in yellow 'can segfault' are NULL pointer tests of some kind."C_RESET);

	// Handle main program arguments
	bool	match;
	for (int i = 1; i < argc; ++i)
	{
		match = FALSE;
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '\0')
			{
				printf("libft_test: Unexpected end of argument after '-'.\n");
				continue;
			}
			else if (argv[i][1] == '-')
			{
				match = handle_args_option_string(argv[i] + 2);
			}
			else for (int j = 0; j < strlen(argv[i]); ++j)
			{
				match = handle_args_option_char(argv[i][j]);
			}
		}
		else if (isalpha(argv[i][0]))
		{
			match = handle_args_test_suites(argv[i]);
		}

		if (!match)
		{
			print_error_argument(argv[i]);
			print_usage();
		}
	}
	// Run the appropriate test suites
	if (check_no_test_suites())
	{
		for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
		{
			test_suites[i].run = TRUE;
		}
	}
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (test_suites[i].run)
			test_suites[i].test();
	}
	return (OK);
}
