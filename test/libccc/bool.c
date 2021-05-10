
#include "libccc.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



// Disable certain GCC warnings temporarily
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-overflow"
// Disable certain clang warnings temporarily
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicitly-unsigned-literal"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconstant-conversion"



/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifndef c_booltostr
void test_booltostr(void)	{}
#else
void	print_test_booltostr(char const* test_name, int can_segfault,
		char const* expecting,
		t_bool value,
		t_bool uppercase)
{
	TEST_INIT(str)
	TEST_PERFORM(	booltostr, value, uppercase)
	TEST_PRINT(str,	booltostr, "value=%d, uppercase=%d", value, uppercase)
	TEST_FREE()
}
void	test_booltostr(void)
{
//	| TEST FUNCTION       | TEST NAME                   |CAN SEGV|EXPECTING| TEST ARGS
	print_test_booltostr("booltostr (n = min)     ",	FALSE,  "false",      0, FALSE);
	print_test_booltostr("booltostr (n = min)     ",	FALSE,  "FALSE",      0, TRUE);
	print_test_booltostr("booltostr               ",	FALSE,   "true",      1, FALSE);
	print_test_booltostr("booltostr               ",	FALSE,   "TRUE",      1, TRUE);
	print_test_booltostr("booltostr               ",	FALSE,   "TRUE",     42, TRUE);
	print_test_booltostr("booltostr (n = max)     ",	FALSE,   "true",    255, FALSE);
	print_test_booltostr("booltostr (n = max)     ",	FALSE,   "TRUE",    255, TRUE);
	if (g_test.flags.test_overflow)
	{
		print_test_booltostr("booltostr (n < min)     ",	FALSE,  "false",     -1, FALSE);
		print_test_booltostr("booltostr (n < min)     ",	FALSE,  "FALSE",     -1, TRUE);
		print_test_booltostr("booltostr (n > max)     ",	FALSE,   "true",    256, FALSE);
		print_test_booltostr("booltostr (n > max)     ",	FALSE,   "TRUE",    256, TRUE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "true", 999999, FALSE);
		print_test_booltostr("booltostr (n > maxdigit)",	FALSE,   "TRUE", 999999, TRUE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "true",-999999, FALSE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "TRUE",-999999, TRUE);
	}
}
#endif



/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifndef c_strtobool
void test_strtobool(void)	{}
#else
void	print_test_strtobool(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strtobool, str)
	TEST_PRINT(bool,strtobool, "str=\"%s\"", str)
}
void	test_strtobool(void)
{ 
//	| TEST FUNCTION       | TEST NAME                   |CAN SEGV| EXPECTING | TEST ARGS
	print_test_strtobool("strtobool (F, uppercase)  ",	FALSE,    FALSE,                 "FALSE");
	print_test_strtobool("strtobool (F, lowercase)  ",	FALSE,    FALSE,                 "False");
	print_test_strtobool("strtobool (F, mixedcase)  ",	FALSE,    FALSE,                 "false");
	print_test_strtobool("strtobool (F, invertcase) ",	FALSE,    FALSE,                 "fALSE");
	print_test_strtobool("strtobool (F, weirdcase)  ",	FALSE,    FALSE,                 "fAlSe");
	print_test_strtobool("strtobool (T, uppercase)  ",	FALSE,     TRUE,                  "TRUE");
	print_test_strtobool("strtobool (T, lowercase)  ",	FALSE,     TRUE,                  "true");
	print_test_strtobool("strtobool (T, mixedcase)  ",	FALSE,     TRUE,                  "True");
	print_test_strtobool("strtobool (T, invertcase) ",	FALSE,     TRUE,                  "tRUE");
	print_test_strtobool("strtobool (T, weirdcase)  ",	FALSE,     TRUE,                  "tRuE");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                " FALSE");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                " False");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                " false");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                " fALSE");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                " fAlSe");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 " TRUE");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 " true");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 " True");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 " tRUE");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 " tRuE");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "FALSE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "False ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "false ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "fALSE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "fAlSe ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "TRUE ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "true ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "True ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "tRUE ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "tRuE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,               " FALSE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,               " False ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,               " false ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,               " fALSE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,               " fAlSe ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                " TRUE ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                " true ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                " True ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                " tRUE ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                " tRuE ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                     "0");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                     "1");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                    "00");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    "01");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    "10");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                   "000");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "001");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "010");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "100");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                    " 0");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    " 1");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                   " 00");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   " 01");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   " 10");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                  " 000");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  " 001");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  " 010");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  " 100");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                    "0 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    "1 ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                   "00 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "01 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "10 ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                  "000 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "001 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "010 ");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "100 ");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                     "0");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                    "0.");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                   "0.0");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                  "0.00");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                     "1");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    "1.");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "1.0");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "1.00");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                    "42");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "42.");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "42.0");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "42.00");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                   "0e2");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                  "0.e2");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                 "0.0e2");
	print_test_strtobool("strtobool                 ",	FALSE,    FALSE,                "0.00e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                   "1e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "1.e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "1.0e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                "1.00e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                  "42e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                 "42.e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,                "42.0e2");
	print_test_strtobool("strtobool                 ",	FALSE,     TRUE,               "42.00e2");
	if (g_test.flags.test_overflow)
	{
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                    "-1");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                   "-1.");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                  "-1.0");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                 "-1.00");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                  "-1e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                 "-1.e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                "-1.0e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,               "-1.00e2");
		print_test_strtobool("strtobool (str > 8max)    ",	FALSE,     TRUE,                   "255");
		print_test_strtobool("strtobool (str > 8max)    ",	FALSE,     TRUE,                  "+255");
		print_test_strtobool("strtobool (str > 8max)    ",	FALSE,     TRUE,                   "256");
		print_test_strtobool("strtobool (str > 8max)    ",	FALSE,     TRUE,                  "+256");
		print_test_strtobool("strtobool (str > 16max)   ",	FALSE,     TRUE,                 "65535");
		print_test_strtobool("strtobool (str > 16max)   ",	FALSE,     TRUE,                "+65535");
		print_test_strtobool("strtobool (str > 16max)   ",	FALSE,     TRUE,                 "65536");
		print_test_strtobool("strtobool (str > 16max)   ",	FALSE,     TRUE,                "+65536");
		print_test_strtobool("strtobool (str > 32max)   ",	FALSE,     TRUE,            "4294967295");
		print_test_strtobool("strtobool (str > 32max)   ",	FALSE,     TRUE,           "+4294967295");
		print_test_strtobool("strtobool (str > 32max)   ",	FALSE,     TRUE,            "4294967296");
		print_test_strtobool("strtobool (str > 32max)   ",	FALSE,     TRUE,           "+4294967296");
		print_test_strtobool("strtobool (str > 64max)   ",	FALSE,     TRUE,  "18446744073709551615");
		print_test_strtobool("strtobool (str > 64max)   ",	FALSE,     TRUE, "+18446744073709551615");
		print_test_strtobool("strtobool (str > 64max)   ",	FALSE,     TRUE,  "18446744073709551616");
		print_test_strtobool("strtobool (str > 64max)   ",	FALSE,     TRUE, "+18446744073709551616");
		print_test_strtobool("strtobool (str > maxdigit)",	FALSE,     TRUE, "999999999999999999999");
		print_test_strtobool("strtobool (str >+maxdigit)",	FALSE,     TRUE,"+999999999999999999999");
		print_test_strtobool("strtobool (str <-maxdigit)",	FALSE,     TRUE,"-999999999999999999999");
	}
	print_test_strtobool("strtobool (empty str)     ",	FALSE,    FALSE,                      "");
	print_test_strtobool("strtobool (NULL str)     ",	FALSE,    FALSE,                    NULL);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
// Resets the clang warning settings back to normal
#pragma clang diagnostic pop
#pragma clang diagnostic pop



int		testsuite_bool(void)
{
	print_suite_title("libccc/bool");

	print_nonstd();

	test_booltostr();

	test_strtobool();

	return (OK);
}
