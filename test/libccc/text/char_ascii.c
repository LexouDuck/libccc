
#include <ctype.h>

#include "libccc.h"
#include "libccc/text/char_ascii.h"

#include "test.h"



#define SF_TEXTCHAR	"'%c'/0x%2.2X"

#define TEST_PERFORM_CHAR_is(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s("SF_TEXTCHAR")" \
		"\t""returned 0x%X," \
		"\t""but libc %s() returned 0x%X\n", \
		#FUNCTION, \
		c, c, \
		result, \
		#FUNCTION, \
		expect);

#define TEST_PERFORM_CHAR_to(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s("SF_TEXTCHAR")" \
		"\t""returned "SF_TEXTCHAR"," \
		"\t""but libc %s() returned "SF_TEXTCHAR"\n", \
		#FUNCTION, \
		c, c, \
		result, result, \
		#FUNCTION, \
		expect, expect); \

#define TEST_PERFORM_CHAR(KIND, FUNCTION, STRICT) \
	c = min;											\
	while (c++ < max)									\
	{													\
		g_test.totals.tests += 1;						\
		result = c_##FUNCTION(c);						\
		expect =     FUNCTION(c);						\
		if (result != expect)							\
		{												\
			if (STRICT && !bool_equals(result, expect))	\
			{											\
				errors++;								\
				TEST_PERFORM_CHAR_##KIND(FUNCTION,		\
					C_RED"Error"C_RESET": ")			\
				g_test.totals.failed += 1;				\
			}											\
			else										\
			{											\
				warnings++;								\
				TEST_PERFORM_CHAR_##KIND(FUNCTION,		\
					C_YELLOW"Warning"C_RESET": ")		\
				g_test.totals.warnings += 1;			\
			}											\
		}												\
	}



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_text_char_ascii(void)
{
	print_suite_title("libccc/text/char_ascii");

	int warnings = 0;
	int errors = 0;
	t_utf32 c = 0;
	t_utf32 min = 0x0;
	t_utf32 max = 0x7F;
	t_sint result;
	t_sint expect;

	TEST_PERFORM_CHAR(is, islower, TRUE)
	TEST_PERFORM_CHAR(is, isupper, TRUE)
	TEST_PERFORM_CHAR(is, isalpha, TRUE)
	TEST_PERFORM_CHAR(is, isalnum, TRUE)
	TEST_PERFORM_CHAR(is, isdigit, TRUE)
	TEST_PERFORM_CHAR(is, isspace, TRUE)
	TEST_PERFORM_CHAR(is, ispunct, TRUE)
	TEST_PERFORM_CHAR(is, isprint, TRUE)
	TEST_PERFORM_CHAR(is, isascii, TRUE)

	TEST_PERFORM_CHAR(to, tolower, TRUE)
	TEST_PERFORM_CHAR(to, toupper, TRUE)

	if (g_test.config.verbose)
	{
		if (errors || warnings)
		{
			printf("\nWhile testing every ASCII char up to %u, got in total:", max);
			printf("\n- %s%d"C_RESET" errors",	 (errors	== 0 ? C_GREEN : C_RED),	errors);
			printf("\n- %s%d"C_RESET" warnings", (warnings	== 0 ? C_GREEN : C_YELLOW),	warnings);
		}
	}
	return (OK);
}
