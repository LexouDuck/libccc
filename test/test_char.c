
#include <ctype.h>

#include "libccc_char.h"

#include "test.h"



static void	print_char_foreword(void)
{
	if (g_test.flags.verbose)
	{
		printf("\n==> "C_BLUE"The following tests are done by comparing your 'c_' functions to the ctype.h standard functions."C_RESET);
		printf("\n==> "C_BLUE"Ideally, all of these char function tests should succeed, and no output will be shown."C_RESET);
		printf("\n==> "C_BLUE"(You may see warnings for characters beyond 255, those chars are undefined behavior)."C_RESET);
		printf("\n==> "C_BLUE"In any case, errors/warnings will be displayed if there are any, important or not."C_RESET"\n");
		printf("\n");
	}
}



#define TEST_PERFORM_CHAR(FUNCTION) \
	g_test.totals.tests += 1; \
	if (!bool_equals(c_##FUNCTION(i), FUNCTION(i))) \
	{ \
		g_test.totals.failed += 1; \
		++errors; \
		printf(C_RED">Error"C_RESET": c_%s(%d) returned %d\n", #FUNCTION, i, c_##FUNCTION(i)); \
	} \

#define TEST_PERFORM_CHAR_WARNING(FUNCTION) \
	g_test.totals.tests += 1; \
	if (!bool_equals(c_##FUNCTION(i), FUNCTION(i))) \
	{ \
		++warnings; \
		printf(C_YELLOW">Warning"C_RESET": c_%s(%d) returned %d\n", #FUNCTION, i, c_##FUNCTION(i)); \
	} \



int		testsuite_char(void)
{
	print_suite_title("char");

	print_char_foreword();

//	int		c_isalpha(int c);
//	int		c_isdigit(int c);
//	int		c_isalnum(int c);
//	int		c_isascii(int c);
//	int		c_isprint(int c);
//	int		c_toupper(int c);
//	int		c_tolower(int c);

	int char_max = 256;
	int warnings = 0;
	int errors = 0;
	int i = -1;
	while (++i < char_max)
	{
		TEST_PERFORM_CHAR(isalpha)
		TEST_PERFORM_CHAR(isupper)
		TEST_PERFORM_CHAR(islower)
		TEST_PERFORM_CHAR(isalnum)
		TEST_PERFORM_CHAR(isdigit)
		TEST_PERFORM_CHAR(isspace)
		TEST_PERFORM_CHAR(ispunct)
		TEST_PERFORM_CHAR(isprint)
		TEST_PERFORM_CHAR(isascii)

		TEST_PERFORM_CHAR(toupper)
		TEST_PERFORM_CHAR(tolower)
	}
	char_max = 260;
	while (++i < char_max)
	{
		TEST_PERFORM_CHAR_WARNING(isalpha)
		TEST_PERFORM_CHAR_WARNING(isupper)
		TEST_PERFORM_CHAR_WARNING(islower)
		TEST_PERFORM_CHAR_WARNING(isalnum)
		TEST_PERFORM_CHAR_WARNING(isdigit)
		TEST_PERFORM_CHAR_WARNING(isspace)
		TEST_PERFORM_CHAR_WARNING(ispunct)
		TEST_PERFORM_CHAR_WARNING(isprint)
		TEST_PERFORM_CHAR_WARNING(isascii)

		TEST_PERFORM_CHAR_WARNING(toupper)
		TEST_PERFORM_CHAR_WARNING(tolower)
	}

	if (g_test.flags.verbose)
	{
		if (errors || warnings)
		{
			printf("\nWhile testing every char up to %d, found:", char_max);
			printf("\n- %s%d"C_RESET" errors",	 (errors	== 0 ? C_GREEN : C_RED),	errors);
			printf("\n- %s%d"C_RESET" warnings", (warnings	== 0 ? C_GREEN : C_YELLOW),	warnings);
		}
	}
	return (OK);
}
