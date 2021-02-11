
#include "libccc.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Wimplicitly-unsigned-literal"
#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Wconstant-conversion"

/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifdef			c_bool_to_str
void	print_test_bool_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_bool value,
		t_bool uppercase)
{
	TEST_PERFORM_RESULT(bool_to_str, value, uppercase)
	print_test_str(test_name, "_bool_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("value=%d, uppercase=%d", value, uppercase)
}
void	test_bool_to_str(void)
{
//	| TEST FUNCTION       | TEST NAME                   |CAN SEGV|EXPECTING| TEST ARGS
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "false",      0, FALSE);
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "FALSE",      0, TRUE);
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "true",      1, FALSE);
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",      1, TRUE);
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",     42, TRUE);
	print_test_bool_to_str("bool_to_str (n = max)     ",	FALSE,   "true",    255, FALSE);
	print_test_bool_to_str("bool_to_str (n = max)     ",	FALSE,   "TRUE",    255, TRUE);
	if (g_test.flags.test_overflow)
	{
		print_test_bool_to_str("bool_to_str (n < min)     ",	FALSE,  "false",     -1, FALSE);
		print_test_bool_to_str("bool_to_str (n < min)     ",	FALSE,  "FALSE",     -1, TRUE);
		print_test_bool_to_str("bool_to_str (n > max)     ",	FALSE,   "true",    256, FALSE);
		print_test_bool_to_str("bool_to_str (n > max)     ",	FALSE,   "TRUE",    256, TRUE);
		print_test_bool_to_str("bool_to_str (n < maxdigit)",	FALSE,   "true", 999999, FALSE);
		print_test_bool_to_str("bool_to_str (n > maxdigit)",	FALSE,   "TRUE", 999999, TRUE);
		print_test_bool_to_str("bool_to_str (n < maxdigit)",	FALSE,   "true",-999999, FALSE);
		print_test_bool_to_str("bool_to_str (n < maxdigit)",	FALSE,   "TRUE",-999999, TRUE);
	}
}
#else
void	test_bool_to_str(void)	{}
#endif



/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifdef			c_str_to_bool
void	print_test_str_to_bool(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, str_to_bool, str)
	print_test_bool(test_name, "_str_to_bool", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void	test_str_to_bool(void)
{ 
//	| TEST FUNCTION       | TEST NAME                   |CAN SEGV| EXPECTING | TEST ARGS
	print_test_str_to_bool("str_to_bool (F, uppercase)  ",	FALSE,    FALSE,                 "FALSE");
	print_test_str_to_bool("str_to_bool (F, lowercase)  ",	FALSE,    FALSE,                 "False");
	print_test_str_to_bool("str_to_bool (F, mixedcase)  ",	FALSE,    FALSE,                 "false");
	print_test_str_to_bool("str_to_bool (F, invertcase) ",	FALSE,    FALSE,                 "fALSE");
	print_test_str_to_bool("str_to_bool (F, weirdcase)  ",	FALSE,    FALSE,                 "fAlSe");
	print_test_str_to_bool("str_to_bool (T, uppercase)  ",	FALSE,     TRUE,                  "TRUE");
	print_test_str_to_bool("str_to_bool (T, lowercase)  ",	FALSE,     TRUE,                  "true");
	print_test_str_to_bool("str_to_bool (T, mixedcase)  ",	FALSE,     TRUE,                  "True");
	print_test_str_to_bool("str_to_bool (T, invertcase) ",	FALSE,     TRUE,                  "tRUE");
	print_test_str_to_bool("str_to_bool (T, weirdcase)  ",	FALSE,     TRUE,                  "tRuE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                " FALSE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                " False");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                " false");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                " fALSE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                " fAlSe");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 " TRUE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 " true");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 " True");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 " tRUE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 " tRuE");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "FALSE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "False ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "false ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "fALSE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "fAlSe ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "TRUE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "true ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "True ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "tRUE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "tRuE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,               " FALSE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,               " False ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,               " false ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,               " fALSE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,               " fAlSe ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                " TRUE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                " true ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                " True ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                " tRUE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                " tRuE ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                     "0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                     "1");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                    "00");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    "01");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    "10");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                   "000");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "001");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "010");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "100");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                    " 0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    " 1");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                   " 00");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   " 01");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   " 10");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                  " 000");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  " 001");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  " 010");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  " 100");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                    "0 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    "1 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                   "00 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "01 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "10 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                  "000 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "001 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "010 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "100 ");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                     "0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                    "0.");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                   "0.0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                  "0.00");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                     "1");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    "1.");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "1.0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "1.00");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                    "42");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "42.");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "42.0");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "42.00");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                   "0e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                  "0.e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                 "0.0e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,    FALSE,                "0.00e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                   "1e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "1.e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "1.0e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                "1.00e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                  "42e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                 "42.e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,                "42.0e2");
	print_test_str_to_bool("str_to_bool                 ",	FALSE,     TRUE,               "42.00e2");
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                    "-1");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                   "-1.");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                  "-1.0");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                 "-1.00");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                  "-1e2");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                 "-1.e2");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,                "-1.0e2");
		print_test_str_to_bool("str_to_bool (str < 0)       ",	FALSE,     TRUE,               "-1.00e2");
		print_test_str_to_bool("str_to_bool (str > 8max)    ",	FALSE,     TRUE,                   "255");
		print_test_str_to_bool("str_to_bool (str > 8max)    ",	FALSE,     TRUE,                  "+255");
		print_test_str_to_bool("str_to_bool (str > 8max)    ",	FALSE,     TRUE,                   "256");
		print_test_str_to_bool("str_to_bool (str > 8max)    ",	FALSE,     TRUE,                  "+256");
		print_test_str_to_bool("str_to_bool (str > 16max)   ",	FALSE,     TRUE,                 "65535");
		print_test_str_to_bool("str_to_bool (str > 16max)   ",	FALSE,     TRUE,                "+65535");
		print_test_str_to_bool("str_to_bool (str > 16max)   ",	FALSE,     TRUE,                 "65536");
		print_test_str_to_bool("str_to_bool (str > 16max)   ",	FALSE,     TRUE,                "+65536");
		print_test_str_to_bool("str_to_bool (str > 32max)   ",	FALSE,     TRUE,            "4294967295");
		print_test_str_to_bool("str_to_bool (str > 32max)   ",	FALSE,     TRUE,           "+4294967295");
		print_test_str_to_bool("str_to_bool (str > 32max)   ",	FALSE,     TRUE,            "4294967296");
		print_test_str_to_bool("str_to_bool (str > 32max)   ",	FALSE,     TRUE,           "+4294967296");
		print_test_str_to_bool("str_to_bool (str > 64max)   ",	FALSE,     TRUE,  "18446744073709551615");
		print_test_str_to_bool("str_to_bool (str > 64max)   ",	FALSE,     TRUE, "+18446744073709551615");
		print_test_str_to_bool("str_to_bool (str > 64max)   ",	FALSE,     TRUE,  "18446744073709551616");
		print_test_str_to_bool("str_to_bool (str > 64max)   ",	FALSE,     TRUE, "+18446744073709551616");
		print_test_str_to_bool("str_to_bool (str > maxdigit)",	FALSE,     TRUE, "999999999999999999999");
		print_test_str_to_bool("str_to_bool (str >+maxdigit)",	FALSE,     TRUE,"+999999999999999999999");
		print_test_str_to_bool("str_to_bool (str <-maxdigit)",	FALSE,     TRUE,"-999999999999999999999");
	}
	print_test_str_to_bool("str_to_bool (empty str)     ",	FALSE,    FALSE,                      "");
	print_test_str_to_bool("str_to_bool (NULL str)     ",	FALSE,    FALSE,                    NULL);
}
#else
void	test_str_to_bool(void)	{}
#endif




#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



int		testsuite_bool(void)
{
	print_suite_title("bool");

	print_nonstd();

	test_bool_to_str();

	test_str_to_bool();

	return (OK);
}
