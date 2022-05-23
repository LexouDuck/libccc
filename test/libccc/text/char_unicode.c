
#include <wctype.h>

#include "libccc.h"
#include "libccc/text/char_unicode.h"

#include "test.h"



#define SF_TEXTCHAR	"'%lc'/0x%8.8X"

#define TEST_PERFORM_CHAR_is(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s("SF_TEXTCHAR")" \
		"\t""returned 0x%X," \
		"\t""but libc %s() returned 0x%X\n", \
		#FUNCTION, \
		(wint_t)c, c, \
		(wint_t)result, \
		#FUNCTION, \
		(wint_t)expect);

#define TEST_PERFORM_CHAR_to(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s("SF_TEXTCHAR")" \
		"\t""returned "SF_TEXTCHAR"," \
		"\t""but libc %s() returned "SF_TEXTCHAR"\n", \
		#FUNCTION, \
		(wint_t)c, c, \
		(wint_t)result, result, \
		#FUNCTION, \
		(wint_t)expect, expect); \

#define TEST_PERFORM_CHAR(KIND, FUNCTION, STRICT) \
	c = 0;												\
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

int		testsuite_text_char_unicode(void)
{
	print_suite_title("libccc/text/char_unicode");

	int warnings = 0;
	int errors = 0;
	t_utf32 max = 0x20000;
	t_utf32 c = 0;
	t_sint result;
	t_sint expect;

	TEST_PERFORM_CHAR(is, iswalpha, TRUE)
	TEST_PERFORM_CHAR(is, iswupper, TRUE)
	TEST_PERFORM_CHAR(is, iswlower, TRUE)
	TEST_PERFORM_CHAR(is, iswalnum, TRUE)
	TEST_PERFORM_CHAR(is, iswdigit, TRUE)
	TEST_PERFORM_CHAR(is, iswspace, TRUE)
//	TEST_PERFORM_CHAR(is, iswpunct, TRUE)
//	TEST_PERFORM_CHAR(is, iswprint, TRUE)
//	TEST_PERFORM_CHAR(is, iswascii, TRUE)

	TEST_PERFORM_CHAR(to, towupper, TRUE)
	TEST_PERFORM_CHAR(to, towlower, TRUE)

	if (g_test.config.verbose)
	{
		if (errors || warnings)
		{
			printf("\nWhile testing every ascii up to %d, got in total:", max);
			printf("\n- %s%d"C_RESET" errors",	 (errors	== 0 ? C_GREEN : C_RED),	errors);
			printf("\n- %s%d"C_RESET" warnings", (warnings	== 0 ? C_GREEN : C_YELLOW),	warnings);
		}
	}
	return (OK);
}
