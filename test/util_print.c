
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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
//	printf("-> in file %s at line %d (in function '%s()')\n", __FILE__, __LINE__, __func__);
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
		printf("Test suite: libccc_%s\n", category);
	else printf("In total:\n");
	printf("=============================\n");
	printf("- Amount of tests: %d\n", totals.tests);

	int passed = totals.tests - totals.failed;
	printf("- Tests: %s%d failed"C_RESET" / %s%d passed"C_RESET"\n",
		(totals.failed == 0 ? C_GREEN : C_RED), totals.failed,
		(totals.tests ? (passed == totals.tests ? C_GREEN : C_YELLOW) : C_RED), passed);
	printf("- Success rate: ");
	if (totals.tests == 0)
		print_percent(0);
	else print_percent(percent);
	if (category == NULL)
	{
		if (totals.failed)
		{
			printf("\n"C_RED"FAIL: Failed %d out of %d tests in total."C_RESET"\n", totals.failed, totals.tests);
		}
		else printf("\n"C_GREEN"SUCCESS: All tests passed."C_RESET"\n");
	}
	printf("\n");
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



void	print_suite_title(char const * suite_name)
{
	if (g_test.flags.verbose)
	{
		printf("\n");
		printf("       .----------------------------------.       \n");
		printf("---==={   LIBCCC TEST: libccc_%-12s   }===---\n", suite_name);
		printf("       '----------------------------------'       \n");
	}
}



void	print_title(void)
{
	printf("   __   __ ___   ____     ______ _____ ___  ______\n");
	printf("  / /  / // . | / ___|   /_  __//  __// __|/_  __/\n");
	printf(" / /_ / // , < / /___     / /  /  _/ _\\_ \\  / /   \n");
	printf("/___//_//___-' \\____/    /_/  /____/ \\__-' /_/    \n");
	printf("                           ==> by duquesne @ 42.fr\n");
	printf("==================================================\n");
	printf("\n");
	printf(C_YELLOW"NB: All the tests with written in yellow 'can segfault' are NULL pointer tests of some kind."C_RESET"\n\n");
	fflush(stdout);
}



void	print_endian_warning(void)
{
	if (g_test.flags.verbose)
	{
		int n = 1;
		if (*(char *)&n == 1)
			printf(C_GREEN"/!\\ Your machine is little-endian (all tests should work reliably and can be trusted)"C_RESET"\n\n");
		else printf(C_RED"/!\\ Your machine is not little-endian (errors may arise in certain tests which handle memory directly)"C_RESET"\n\n");
	}
	fflush(stdout);
}



void	print_nonstd(void)
{
	if (g_test.flags.verbose)
	{
		printf("\n\n");
		printf(C_BLUE"================ NON-STD FUNCTIONS ================"C_RESET
			"\nThe following tests are for the functions of this category"
			"\nwhich are not present in the ISO standard C library.\n");
	}
}
