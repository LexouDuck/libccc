
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

	printf(ANSI_COLOR_FG_RED "Error" ANSI_RESET ": ");
	va_start(args, format_error);
	vprintf(format_error, args);
	va_end(args);
//	printf("-> in file %s at line %d (in function '%s()')\n", __FILE__, __LINE__, __func__);
}



void	print_percent(double percent)
{
	char const* color;
	if (percent >= 100)		color = ANSI_COLOR_FG_GREEN;
	else if (percent >= 90)	color = ANSI_COLOR_FG_YELLOW;
	else if (percent >= 0)	color = ANSI_COLOR_FG_RED;
	else					color = ANSI_RESET;
	printf("%s%g%%"ANSI_RESET"\n", color, percent);
}



void	print_totals(int amount, int failed, int warnings, char const* suite_name)
{
	double percent = (amount == 0 ? 100. : ((amount - failed) * 100. / amount));

	printf("\n\n");
	printf("|========================================\n");
	if (suite_name == NULL)
		 printf("|  In total:\n");
	else printf("|  Test suite: libccc/%s\n", suite_name);
	printf("|========================================\n");
	printf("- Amount of tests: %d\n", amount);

	int passed = amount - failed;
	printf("- Tests: %s%d failed" ANSI_RESET " / %s%d passed" ANSI_RESET "\n",
		(failed == 0 ? ANSI_COLOR_FG_GREEN : ANSI_COLOR_FG_RED), failed,
		(amount ? (passed == amount ? ANSI_COLOR_FG_GREEN : ANSI_COLOR_FG_YELLOW) : ANSI_COLOR_FG_RED), passed);
	if (warnings)
		printf("- Warnings: " ANSI_COLOR_FG_YELLOW "%d warnings issued" ANSI_RESET "\n", warnings);
	printf("- Success rate: ");
	if (amount == 0)
		print_percent(0);
	else print_percent(percent);
	if (suite_name == NULL)
	{
		if (failed)
		{
			printf("\n" ANSI_COLOR_FG_RED "FAIL: Failed %d out of %d tests in total." ANSI_RESET "\n", failed, amount);
		}
		else printf("\n" ANSI_COLOR_FG_GREEN "SUCCESS: All tests passed." ANSI_RESET "\n");
	}
	printf("\n");
}



int	print_results(s_test_suite const* suites)
{
	int total_tests = 0;
	int total_failed = 0;
	int total_warnings = 0;
	double percent = 0;

	printf("\n\n");
	printf("|========================================\n");
	printf("| Final results:\n");
	printf("|========================================\n");
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		percent = (suites[i].totals.tests == 0 ? 100. : ((suites[i].totals.tests - suites[i].totals.failed) * 100. / suites[i].totals.tests));
		printf(" - %-20s: (%s%8d" ANSI_RESET " tests, %s%8d" ANSI_RESET " failed, %s%8d" ANSI_RESET " warnings)\t-> ",
			suites[i].name,
			(suites[i].totals.tests    == 0 ? ANSI_COLOR_FG_YELLOW : ""),       suites[i].totals.tests,
			(suites[i].totals.failed   == 0 ? ANSI_COLOR_FG_GREEN  : ANSI_COLOR_FG_RED),    suites[i].totals.failed,
			(suites[i].totals.warnings == 0 ? ANSI_COLOR_FG_GREEN  : ANSI_COLOR_FG_YELLOW), suites[i].totals.warnings);
		print_percent(percent);
		total_tests    += suites[i].totals.tests;
		total_failed   += suites[i].totals.failed;
		total_warnings += suites[i].totals.warnings;
	}
	print_totals(
		total_tests,
		total_failed,
		total_warnings,
		NULL);
	return (total_failed > 0);
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
	if (g_test.config.verbose)
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
	printf(ANSI_COLOR_FG_YELLOW "NB: All the tests with written in yellow 'can segfault' are NULL pointer tests of some kind." ANSI_RESET "\n\n");
	fflush(stdout);
}



void	print_endian_warning(void)
{
	if (g_test.config.verbose)
	{
		int n = 1;
		if (*(char *)&n == 1)
			printf(ANSI_COLOR_FG_GREEN "/!\\ Your machine is little-endian (all tests should work reliably and can be trusted)" ANSI_RESET "\n\n");
		else printf(ANSI_COLOR_FG_RED "/!\\ Your machine is not little-endian (errors may arise in certain tests which handle memory directly)" ANSI_RESET "\n\n");
	}
	fflush(stdout);
}



void	print_nonstd(void)
{
	if (g_test.config.verbose)
	{
		printf("\n\n");
		printf(ANSI_COLOR_FG_BLUE "================ NON-STD FUNCTIONS ================" ANSI_RESET
			"\n""The following tests are for the functions of this category"
			"\n""which are not present in the ISO standard C library.\n");
	}
}
