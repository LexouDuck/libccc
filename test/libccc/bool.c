
#include "libccc.h"
#include "libccc/bool.h"
#include "libccc/sys/io.h"

#include "test.h"
#include "test_utils.h"



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



/*============================================================================*\
||                          Other Convert to Strings                          ||
\*============================================================================*/

#ifndef c_booltostr
void test_booltostr(void)	{}
#warning "booltostr() test suite function defined, but the function isn't defined."
#else
void	print_test_booltostr(char const* test_name, t_testflags flags,
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
//	| TEST FUNCTION       | TEST NAME                   |TESTFLAG|EXPECTING| TEST ARGS
	print_test_booltostr("booltostr (n = min)     ",	FALSE,  "false",      0, FALSE);
	print_test_booltostr("booltostr (n = min)     ",	FALSE,  "FALSE",      0, TRUE);
	print_test_booltostr("booltostr               ",	FALSE,   "true",      1, FALSE);
	print_test_booltostr("booltostr               ",	FALSE,   "TRUE",      1, TRUE);
	print_test_booltostr("booltostr               ",	FALSE,   "TRUE",     42, TRUE);
	print_test_booltostr("booltostr (n = max)     ",	FALSE,   "true",    255, FALSE);
	print_test_booltostr("booltostr (n = max)     ",	FALSE,   "TRUE",    255, TRUE);
	if (g_test.config.test_overflow)
	{
		print_test_booltostr("booltostr (n < min)     ",	FALSE,   "true",     -1, FALSE);
		print_test_booltostr("booltostr (n < min)     ",	FALSE,   "TRUE",     -1, TRUE);
		print_test_booltostr("booltostr (n > max)     ",	FALSE,   "true",    256, FALSE);
		print_test_booltostr("booltostr (n > max)     ",	FALSE,   "TRUE",    256, TRUE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "true", 999999, FALSE);
		print_test_booltostr("booltostr (n > maxdigit)",	FALSE,   "TRUE", 999999, TRUE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "true",-999999, FALSE);
		print_test_booltostr("booltostr (n < maxdigit)",	FALSE,   "TRUE",-999999, TRUE);
	}
}
#endif



/*============================================================================*\
||                          Other Convert to Strings                          ||
\*============================================================================*/

#ifndef c_strtobool
void test_strtobool(void)	{}
#warning "strtobool() test suite function defined, but the function isn't defined."
#else
void	print_test_strtobool(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* str)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strtobool, str)
	TEST_PRINT(bool,strtobool, "str=\"%s\"", str)
}
void	test_strtobool(void)
{ 
//	| TEST FUNCTION       | TEST NAME                   |TESTFLAG| EXPECTING | TEST ARGS
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
	if (g_test.config.test_overflow)
	{
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                    "-1");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                   "-1.");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                  "-1.0");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                 "-1.00");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                  "-1e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                 "-1.e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,                "-1.0e2");
		print_test_strtobool("strtobool (str < 0)       ",	FALSE,     TRUE,               "-1.00e2");
		print_test_strtobool("strtobool (str = s8max)   ",	FALSE,     TRUE,                   "127");
		print_test_strtobool("strtobool (str = s8max)   ",	FALSE,     TRUE,                  "+127");
		print_test_strtobool("strtobool (str > s8max)   ",	FALSE,     TRUE,                   "128");
		print_test_strtobool("strtobool (str > s8max)   ",	FALSE,     TRUE,                  "+128");
		print_test_strtobool("strtobool (str = s8min)   ",	FALSE,     TRUE,                  "-128");
		print_test_strtobool("strtobool (str < s8min)   ",	FALSE,     TRUE,                  "-129");
		print_test_strtobool("strtobool (str = u8max)   ",	FALSE,     TRUE,                   "255");
		print_test_strtobool("strtobool (str = u8max)   ",	FALSE,     TRUE,                  "+255");
		print_test_strtobool("strtobool (str > u8max)   ",	FALSE,     TRUE,                   "256");
		print_test_strtobool("strtobool (str > u8max)   ",	FALSE,     TRUE,                  "+256");
		print_test_strtobool("strtobool (str = s16max)  ",	FALSE,     TRUE,                 "32767");
		print_test_strtobool("strtobool (str = s16max)  ",	FALSE,     TRUE,                "+32767");
		print_test_strtobool("strtobool (str > s16max)  ",	FALSE,     TRUE,                 "32768");
		print_test_strtobool("strtobool (str > s16max)  ",	FALSE,     TRUE,                "+32768");
		print_test_strtobool("strtobool (str = s16min)  ",	FALSE,     TRUE,                "-32768");
		print_test_strtobool("strtobool (str < s16min)  ",	FALSE,     TRUE,                "-32769");
		print_test_strtobool("strtobool (str = u16max)  ",	FALSE,     TRUE,                 "65535");
		print_test_strtobool("strtobool (str = u16max)  ",	FALSE,     TRUE,                "+65535");
		print_test_strtobool("strtobool (str > u16max)  ",	FALSE,     TRUE,                 "65536");
		print_test_strtobool("strtobool (str > u16max)  ",	FALSE,     TRUE,                "+65536");
		print_test_strtobool("strtobool (str = s32min)  ",	FALSE,     TRUE,            "2147483647");
		print_test_strtobool("strtobool (str = s32min)  ",	FALSE,     TRUE,           "+2147483647");
		print_test_strtobool("strtobool (str > s32min)  ",	FALSE,     TRUE,            "2147483648");
		print_test_strtobool("strtobool (str > s32min)  ",	FALSE,     TRUE,           "+2147483648");
		print_test_strtobool("strtobool (str = s32min)  ",	FALSE,     TRUE,           "-2147483648");
		print_test_strtobool("strtobool (str < s32min)  ",	FALSE,     TRUE,           "-2147483649");
		print_test_strtobool("strtobool (str = u32max)  ",	FALSE,     TRUE,            "4294967295");
		print_test_strtobool("strtobool (str = u32max)  ",	FALSE,     TRUE,           "+4294967295");
		print_test_strtobool("strtobool (str > u32max)  ",	FALSE,     TRUE,            "4294967296");
		print_test_strtobool("strtobool (str > u32max)  ",	FALSE,     TRUE,           "+4294967296");
		print_test_strtobool("strtobool (str = s64max)  ",	FALSE,     TRUE,   "9223372036854775808");
		print_test_strtobool("strtobool (str = s64max)  ",	FALSE,     TRUE,  "+9223372036854775808");
		print_test_strtobool("strtobool (str > s64max)  ",	FALSE,     TRUE,   "9223372036854775808");
		print_test_strtobool("strtobool (str > s64max)  ",	FALSE,     TRUE,  "+9223372036854775808");
		print_test_strtobool("strtobool (str = s64min)  ",	FALSE,     TRUE,  "-9223372036854775808");
		print_test_strtobool("strtobool (str < s64min)  ",	FALSE,     TRUE,  "-9223372036854775809");
		print_test_strtobool("strtobool (str = u64max)  ",	FALSE,     TRUE,  "18446744073709551615");
		print_test_strtobool("strtobool (str = u64max)  ",	FALSE,     TRUE, "+18446744073709551615");
		print_test_strtobool("strtobool (str > u64max)  ",	FALSE,     TRUE,  "18446744073709551616");
		print_test_strtobool("strtobool (str > u64max)  ",	FALSE,     TRUE, "+18446744073709551616");
		print_test_strtobool("strtobool (str > maxdigit)",	FALSE,     TRUE,  "999999999999999999999");
		print_test_strtobool("strtobool (str >+maxdigit)",	FALSE,     TRUE, "+999999999999999999999");
		print_test_strtobool("strtobool (str <-maxdigit)",	FALSE,     TRUE, "-999999999999999999999");
		print_test_strtobool("strtobool (str = s128max) ",	FALSE,     TRUE,  "170141183460469231731687303715884105727");
		print_test_strtobool("strtobool (str = s128max) ",	FALSE,     TRUE, "+170141183460469231731687303715884105727");
		print_test_strtobool("strtobool (str > s128max) ",	FALSE,     TRUE,  "170141183460469231731687303715884105728");
		print_test_strtobool("strtobool (str > s128max) ",	FALSE,     TRUE, "+170141183460469231731687303715884105728");
		print_test_strtobool("strtobool (str = s128min) ",	FALSE,     TRUE, "-170141183460469231731687303715884105728");
		print_test_strtobool("strtobool (str < s128min) ",	FALSE,     TRUE, "-170141183460469231731687303715884105729");
		print_test_strtobool("strtobool (str = u128max) ",	FALSE,     TRUE,  "340282366920938463463374607431768211453");
		print_test_strtobool("strtobool (str = u128max) ",	FALSE,     TRUE, "+340282366920938463463374607431768211453");
		print_test_strtobool("strtobool (str > u128max) ",	FALSE,     TRUE,  "340282366920938463463374607431768211454");
		print_test_strtobool("strtobool (str > u128max) ",	FALSE,     TRUE, "+340282366920938463463374607431768211454");
	}
	print_test_strtobool("strtobool (empty str)     ",	FALSE,    FALSE,                      "");
	print_test_strtobool("strtobool (NULL str)     ",	FALSE,    FALSE,                    NULL);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

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
