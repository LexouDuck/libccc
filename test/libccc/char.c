
#include <ctype.h>

#include "libccc/char.h"

#include "test.h"



static
void	print_char_foreword(void)
{
	if (g_test.config.verbose)
	{
		printf("\n==> "C_BLUE"The following tests are done by comparing your 'c_' functions to the ctype.h standard functions."C_RESET);
		printf("\n==> "C_BLUE"Ideally, all of these char function tests should succeed, and no output will be shown."C_RESET);
		printf("\n==> "C_BLUE"(You may see warnings for characters beyond 255, those chars are undefined behavior)."C_RESET);
		printf("\n==> "C_BLUE"In any case, errors/warnings will be displayed if there are any, important or not."C_RESET"\n");
		printf("\n");
	}
}



#define TEST_PERFORM_CHAR_(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX"c_%s(c = '%c'/0x%4.4X)\treturned 0x%.4X,\tbut the C stdlib equivalent returned 0x%.4X\n",\
		#FUNCTION, c, c, result, expect);\
	g_test.totals.warnings += 1;\

#define TEST_PERFORM_CHAR(FUNCTION, STRICT) \
	g_test.totals.tests += 1;						\
	result = c_##FUNCTION(c);						\
	expect =     FUNCTION(c);						\
	if (result != expect)							\
	{												\
		if (STRICT && !bool_equals(result, expect))	\
		{											\
			errors++;								\
			TEST_PERFORM_CHAR_(FUNCTION,			\
				C_RED"Error"C_RESET": ")			\
			g_test.totals.failed += 1;				\
		}											\
		else										\
		{											\
			warnings++;								\
			TEST_PERFORM_CHAR_(FUNCTION,			\
				C_YELLOW"Warning"C_RESET": ")		\
		}											\
	}												\



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int	testsuite_char(void)
{
	print_suite_title("libccc/char");

	print_char_foreword();

//	int		c_isalpha(int c);
//	int		c_isdigit(int c);
//	int		c_isalnum(int c);
//	int		c_isascii(int c);
//	int		c_isprint(int c);
//	int		c_toupper(int c);
//	int		c_tolower(int c);

	int warnings = 0;
	int errors = 0;
	t_utf32 char_max = 0x7F;
	t_utf32 c = 0;
	t_sint result;
	t_sint expect;
	while (c++ < char_max)
	{
		TEST_PERFORM_CHAR(isalpha, TRUE)
		TEST_PERFORM_CHAR(isupper, TRUE)
		TEST_PERFORM_CHAR(islower, TRUE)
		TEST_PERFORM_CHAR(isalnum, TRUE)
		TEST_PERFORM_CHAR(isdigit, TRUE)
		TEST_PERFORM_CHAR(isspace, TRUE)
		TEST_PERFORM_CHAR(ispunct, TRUE)
		TEST_PERFORM_CHAR(isprint, TRUE)
		TEST_PERFORM_CHAR(isascii, TRUE)

		TEST_PERFORM_CHAR(toupper, TRUE)
		TEST_PERFORM_CHAR(tolower, TRUE)
	}
	char_max = 300;
	while (c++ < char_max)
	{
		TEST_PERFORM_CHAR(isalpha, FALSE)
		TEST_PERFORM_CHAR(isupper, FALSE)
		TEST_PERFORM_CHAR(islower, FALSE)
		TEST_PERFORM_CHAR(isalnum, FALSE)
		TEST_PERFORM_CHAR(isdigit, FALSE)
		TEST_PERFORM_CHAR(isspace, FALSE)
		TEST_PERFORM_CHAR(ispunct, FALSE)
		TEST_PERFORM_CHAR(isprint, FALSE)
		TEST_PERFORM_CHAR(isascii, FALSE)

		TEST_PERFORM_CHAR(toupper, FALSE)
		TEST_PERFORM_CHAR(tolower, FALSE)
	}

	if (g_test.config.verbose)
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
