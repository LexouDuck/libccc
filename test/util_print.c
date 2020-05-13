
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#include "test.h"



/*
** ************************************************************************** *|
**                          Commandline output utils                          *|
** ************************************************************************** *|
*/



void	print_error(char const * format_error, ...)
{
	va_list		args;

	printf(C_RED"Error"C_RESET": ");
	va_start(args, format_error);
	vprintf(format_error, args);
	va_end(args);
	printf("\n-> in file %s at line %d: in function %s\n", __FILE__, __LINE__, __func__);
}



void	print_usage(char const * program_name)
{
	printf("\nUSAGE");
	printf("\n\t%s [TEST_SUITES] [OPTIONS]", program_name);
	printf("\n");
	printf("\nTEST_SUITES");
	printf("\n    If none of these arguments are provided, all of the test suites will be run.");
	printf("\n    Each of the following arguments runs the corresponding test suite (ie: sequence of unit tests):");
	for (int j = 0; j < TEST_SUITE_AMOUNT; ++j)
	{
		printf("\n\t%s", g_test.suites[j].name);
	}
	printf("\n");
	printf("\nOPTIONS");
	printf("\n    If none of these arguments are provided, this program will only output the total amount of tests passed/failed.");
	printf("\n    Here is the list of accepted options, both in '-c' char format, and '--string' string format:");
	for (int j = 0; j < TEST_ARGS_AMOUNT; ++j)
	{
		printf("\n\t-%c or --%s\t%s", g_test.args[j].arg, g_test.args[j].name, g_test.args[j].description);
	}
	printf("\n\n");
}



void	print_nonstd(void)
{
	if (g_test.flags.verbose)
	{
		printf("\n");
		printf("\n==>\t"C_BLUE"The following tests are for the functions of this category\n"
			"\twhich are not present in the standard C library."C_RESET);
	}
}



void	print_suite_title(char const * suite_name)
{
	if (g_test.flags.verbose)
	{
		printf("\n");
		printf("       .----------------------------------.       \n");
		printf("---==={   LIBFT TEST: libft_%-12s   }===---\n", suite_name);
		printf("       '----------------------------------'       \n");
		printf("\n");
	}
}



void	print_percent(double percent)
{
	printf("%s%g%%"C_RESET"\n", (percent == 100 ? C_GREEN : (percent >= 90 ? C_YELLOW : C_RED)), percent);
}



void	print_totals(s_test_totals totals, char const * category)
{
	double percent = (totals.tests - totals.failed) * 100. / totals.tests;

	printf("\n");
	printf("=============================\n");
	if (category)
		printf("Test suite: libft_%s\n", category);
	else printf("In total:\n");
	printf("=============================\n");
	printf("- Amount of tests: %d\n", totals.tests);
	if (category)
	{
		int passed = totals.tests - totals.failed;
		printf("- Tests: %s%d failed"C_RESET" / %s%d passed"C_RESET"\n",
			(totals.failed == 0 ? C_GREEN : C_RED), totals.failed,
			(passed == totals.tests ? C_GREEN : C_RED), passed);
		printf("- Success rate: ");
		print_percent(percent);
	}
	else
	{
		if (totals.failed)
		{
			printf(C_RED"Failed %d out of %d tests in total."C_RESET"\n", totals.failed, totals.tests);
		}
		else printf(C_GREEN"All tests passed."C_RESET"\n");
	}
	printf("\n");
}
