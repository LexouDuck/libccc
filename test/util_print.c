
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "test.h"



/*
** ************************************************************************** *|
**                          Commandline output utils                          *|
** ************************************************************************** *|
*/

void	print_error(char const* format_error, ...)
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
	char const* color;
	if (percent >= 100)		color = C_GREEN;
	else if (percent >= 90)	color = C_YELLOW;
	else if (percent >= 0)	color = C_RED;
	else					color = C_RESET;
	printf("%s%g%%"C_RESET"\n", color, percent);
}



void	print_totals(int amount, int failed, char const* category)
{
	double percent = (amount == 0 ? 100. : ((amount - failed) * 100. / amount));

	printf("\n\n");
	printf("|========================================\n");
	if (category)
		printf("|  Test suite: libccc/%s\n", category);
	else printf("|  In total:\n");
	printf("|========================================\n");
	printf("- Amount of tests: %d\n", amount);

	int passed = amount - failed;
	printf("- Tests: %s%d failed"C_RESET" / %s%d passed"C_RESET"\n",
		(failed == 0 ? C_GREEN : C_RED), failed,
		(amount ? (passed == amount ? C_GREEN : C_YELLOW) : C_RED), passed);
	printf("- Success rate: ");
	if (amount == 0)
		print_percent(0);
	else print_percent(percent);
	if (category == NULL)
	{
		if (failed)
		{
			printf("\n"C_RED"FAIL: Failed %d out of %d tests in total."C_RESET"\n", failed, amount);
		}
		else printf("\n"C_GREEN"SUCCESS: All tests passed."C_RESET"\n");
	}
	printf("\n");
}



void	print_usage(char const* program_name)
{
	printf("\n""USAGE");
	printf("\n""\t%s [TEST_SUITES] [OPTIONS]", program_name);
	printf("\n""");
	printf("\n""TEST_SUITES");
	printf("\n""    If none of these arguments are provided, all of the test suites will be run.");
	printf("\n""    Each of the following arguments runs the corresponding test suite (ie: sequence of unit tests):");
	for (int j = 0; j < TEST_SUITE_AMOUNT; ++j)
	{
		printf("\n\t%s", g_test.suites[j].name);
	}
	printf("\n");
	printf("\n""OPTIONS");
	printf("\n""    If none of these arguments are provided, this program will only output the total amount of tests passed/failed.");
	printf("\n""    Here is the list of accepted options, both in '-c' char format, and '--string' string format:");
	for (int j = 0; j < TEST_ARGS_AMOUNT; ++j)
	{
		printf("\n\t-%c or --%s\t%s", g_test.args[j].arg, g_test.args[j].name, g_test.args[j].description);
	}
	printf("\n\n");
}



void	print_suite_title(char const* suite_name)
{
	if (g_test.flags.verbose)
	{
		printf("\n");
		printf("       .-------------------------------------.       \n");
		printf("---==={   LIBCCC TEST: %20.20s   }===---\n", suite_name);
		printf("       '-------------------------------------'       \n");
	}
}



void	print_title(void)
{
	printf("   __   __ ___   ____     ______ _____ ___  ______\n");
	printf("  / /  / // . | / ___|   /_  __//  __// __|/_  __/\n");
	printf(" / /_ / // , < / /___     / /  /  _/ _\\_ \\  / /   \n");
	printf("/___//_//___-' \\____/    /_/  /____/ \\__-' /_/    \n");
	printf(" ==> from https://github.com/lexouduck/libccc.git \n");
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
			"\n""The following tests are for the functions of this category"
			"\n""which are not present in the ISO standard C library.\n");
	}
}
