
#include <wctype.h>

#include "libccc.h"
#include "libccc/text/char_unicode.h"

#include "test.h"
#include "test_utils.h"



#define SF_TEXTCHAR	"'%lc'/0x%8.8X"

#define TEST_PERFORM_CHAR_is(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s(" SF_TEXTCHAR ")" \
		"\t""returned 0x%X," \
		"\t""but libc %s() returned 0x%X\n", \
		#FUNCTION, \
		(wint_t)c, c, \
		(wint_t)result, \
		#FUNCTION, \
		(wint_t)expect);

#define TEST_PERFORM_CHAR_to(FUNCTION, ERRORPREFIX) \
	printf(ERRORPREFIX \
		"c_%s(" SF_TEXTCHAR ")" \
		"\t""returned " SF_TEXTCHAR "," \
		"\t""but libc %s() returned " SF_TEXTCHAR "\n", \
		#FUNCTION, \
		(wint_t)c, c, \
		(wint_t)result, result, \
		#FUNCTION, \
		(wint_t)expect, expect); \

#define TEST_PERFORM_CHAR(KIND, FUNCTION, STRICT) \
	warnings = 0; \
	errors   = 0; \
	c = min; \
	while (c++ < max) \
	{ \
		result = c_##FUNCTION(c); \
		expect =     FUNCTION(c); \
		if (result != expect) \
		{ \
			if (STRICT && !bool_equals(result, expect)) \
			{ \
				errors++; \
				TEST_PERFORM_CHAR_##KIND(FUNCTION, \
					ANSI_COLOR_FG_RED "Error" ANSI_RESET ": ") \
				g_test.suites[TESTSUITE_TEXT_CHAR_UNICODE].totals.failed += 1;\
			} \
			else \
			{ \
				warnings++; \
				if (g_test.config.verbose) \
					TEST_PERFORM_CHAR_##KIND(FUNCTION, \
						ANSI_COLOR_FG_YELLOW "Warning" ANSI_RESET ": ") \
				g_test.suites[TESTSUITE_TEXT_CHAR_UNICODE].totals.warnings += 1;\
			} \
		} \
		g_test.suites[TESTSUITE_TEXT_CHAR_UNICODE].totals.tests += 1;\
	} \
	if (errors || warnings) \
	{ \
		printf(#FUNCTION"(): tested every character from %u to %u, got in total:\n", min, max); \
		printf("- %s%d" ANSI_RESET " errors""\n", (errors   == 0 ? ANSI_COLOR_FG_GREEN : ANSI_COLOR_FG_RED),    errors  ); \
		printf("- %s%d" ANSI_RESET " warnings\n", (warnings == 0 ? ANSI_COLOR_FG_GREEN : ANSI_COLOR_FG_YELLOW), warnings); \
	}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_char_unicode(void)
{
	print_suite_title("libccc/text/char_unicode");

	int warnings = 0;
	int errors = 0;
	t_sint result;
	t_sint expect;
	t_utf32 c = 0;
	t_utf32 min = 0x0;
	t_utf32 max = 0x80;

	bool strict = TRUE;
#ifdef _WIN32
	strict = FALSE;
#endif
	TEST_PERFORM_CHAR(is, iswlower, TRUE)
	TEST_PERFORM_CHAR(is, iswupper, TRUE)
	TEST_PERFORM_CHAR(is, iswalpha, TRUE)
	TEST_PERFORM_CHAR(is, iswalnum, TRUE)
	TEST_PERFORM_CHAR(is, iswdigit, TRUE)
	TEST_PERFORM_CHAR(is, iswspace, TRUE)
	TEST_PERFORM_CHAR(is, iswpunct, TRUE)
	TEST_PERFORM_CHAR(is, iswprint, strict)
//	TEST_PERFORM_CHAR(is, iswvalid, TRUE)

	TEST_PERFORM_CHAR(to, towlower, TRUE)
	TEST_PERFORM_CHAR(to, towupper, TRUE)

	printf("\n""NOTE: The following tests go beyond the ASCII plane (128 and above)."
		"\n\t""As such, libc implmentations vary, so it is quite normal to have many warnings.\n\n");

	min = 0x80;
	max = 0x20000;

	TEST_PERFORM_CHAR(is, iswlower, FALSE)
	TEST_PERFORM_CHAR(is, iswupper, FALSE)
	TEST_PERFORM_CHAR(is, iswalpha, FALSE)
	TEST_PERFORM_CHAR(is, iswalnum, FALSE)
	TEST_PERFORM_CHAR(is, iswdigit, FALSE)
	TEST_PERFORM_CHAR(is, iswspace, FALSE)
	TEST_PERFORM_CHAR(is, iswpunct, FALSE)
//	TEST_PERFORM_CHAR(is, iswprint, FALSE)
//	TEST_PERFORM_CHAR(is, iswvalid, FALSE)

	TEST_PERFORM_CHAR(to, towlower, FALSE)
	TEST_PERFORM_CHAR(to, towupper, FALSE)

	return (OK);
}
