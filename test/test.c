
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

#include "test.h"



/*
** ************************************************************************** *|
**                           Global Testing Variables                         *|
** ************************************************************************** *|
*/

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

void segfault_handler(int sig, siginfo_t *info, void *ptr)
{
    if (sig == SIGSEGV)
    {
        longjmp(restore, SIGSEGV);
    }
}



/*
** ************************************************************************** *|
**                           Main Program Definitions                         *|
** ************************************************************************** *|
*/

typedef struct	s_test_suite
{
	char const*	name;
	int		(*test)(void);
}				t_test_suite;

#define TEST_SUITE_AMOUNT	12
t_test_suite	test_suites[TEST_SUITE_AMOUNT] =
{
	(t_test_suite){ "memory",		test_memory },
	(t_test_suite){ "char",			test_char },
	(t_test_suite){ "string",		test_string },
	(t_test_suite){ "stringarray",	test_stringarray },
	(t_test_suite){ "convert",		test_convert },
	(t_test_suite){ "color",		test_color },
	(t_test_suite){ "list",			test_list },
	(t_test_suite){ "math",			test_math },
	(t_test_suite){ "stat",			test_stat },
	(t_test_suite){ "random",		test_random },
	(t_test_suite){ "vlq",			test_vlq },
	(t_test_suite){ "io",			test_io },
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



int		main(int argc, char **argv)
{
	memset(&sig, 0, sizeof(sigaction));
	sigemptyset(&sig.sa_mask);
	sig.sa_flags     = SA_NODEFER;
	sig.sa_sigaction = segfault_handler;
	sigaction(SIGSEGV, &sig, NULL);

	printf("   __   __ ___   _____ ______    ______ _____ ___  ______\n");
	printf("  / /  / // . | / ___//_  __/   /_  __//  __// __|/_  __/\n");
	printf(" / /_ / // , < / __/   / /       / /  /  _/ _\\_ \\  / /   \n");
	printf("/___//_//___-'/_/     /_/       /_/  /____/ \\__-' /_/    \n");
	printf("                                  ==> by duquesne @ 42.fr\n");

	if (argc <= 1)
	{
		int num = 1;
		if (*(char *)&num == 1)
			 printf("\n"C_GREEN"/!\\ Processor is Little-Endian (all tests should work reliably and can be trusted)"C_RESET"\n");
		else printf("\n"C_RED"/!\\ Processor is Big-Endian (errors may arise in certain tests, like 'uint' tests for mem functions)"C_RESET"\n");
		printf("\n"C_YELLOW"All the tests with written in yellow 'can segfault' are NULL pointer tests."C_RESET"\n");

		for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
		{
			test_suites[i].test();
		}
	}
	else
	{
		t_bool match;
		for (t_u32 i = 1; i < argc; ++i)
		{
			match = FALSE;
			if (isalpha(argv[i][0]))
			{
				if (argv[i][1] == '\0') printf("libft_test: expected argument after '-'.\n");
				else for (int j = 0; j < TEST_SUITE_AMOUNT; ++j)
				{
					if (str_equals(argv[i] + 1, test_suites[j].name))
					{
						test_suites[j].test();
						match = TRUE;
						break;
					}
				}
				if (!match)
					printf("libft_test: Argument not recognized: %s.\n", argv[i]);
			}
			else
			{
				printf("libft test: Invalid argument(s), use one of the following:\n");
				for (int j = 0; j < TEST_SUITE_AMOUNT; ++j)
				{
					printf("\t%s\n", test_suites[j].name);
				}
			}
		}
	}
	return (OK);
}
