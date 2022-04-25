
#include <ctype.h>

#include "libccc.h"
#include "libccc/text/ascii.h"

#include "test.h"



#define TEST_PERFORM_CHAR_(FUNCTION, ERRORPREFIX) \
	printf( ERRORPREFIX "c_%s(c = '%c'/0x%4.4X)\treturned 0x%.4X,\tbut the C stdlib equivalent returned 0x%.4X\n", #FUNCTION, c, c, result, expect);

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

int		testsuite_text_ascii(void)
{
	print_suite_title("libccc/text/ascii");

//	int		c_isalpha(int c);
//	int		c_isdigit(int c);
//	int		c_isalnum(int c);
//	int		c_isascii(int c);
//	int		c_isprint(int c);
//	int		c_toupper(int c);
//	int		c_tolower(int c);

	int warnings = 0;
	int errors = 0;
	t_utf32 ascii_max = 0x7F;
	t_utf32 c = 0;
	t_sint result;
	t_sint expect;
	while (c++ < ascii_max)
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
	ascii_max = 128;
	while (c++ < ascii_max)
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

	if (g_test.flags.verbose)
	{
		if (errors || warnings)
		{
			printf("\nWhile testing every ascii up to %d, found:", ascii_max);
			printf("\n- %s%d"C_RESET" errors",	 (errors	== 0 ? C_GREEN : C_RED),	errors);
			printf("\n- %s%d"C_RESET" warnings", (warnings	== 0 ? C_GREEN : C_YELLOW),	warnings);
		}
	}
	return (OK);
}
