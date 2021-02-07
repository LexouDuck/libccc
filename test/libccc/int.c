
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
**                        Convert Integers to Strings                         *|
** ************************************************************************** *|
*/

#ifdef			c_s8_to_str
void	print_test_s8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s8 number)
{
	TEST_PERFORM_RESULT(s8_to_str, number)
/*
	s_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = c_s8_to_str(number); timer_clock(&t.end1); } else result = segstr;
*/
	print_test_str(test_name, "_s8_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_s8_to_str(void)
{
//	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "1", 1    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,     "42", 42   );
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "0", 0    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,    "111", 111  );
	print_test_s8_to_str("s8_to_str               ",	FALSE,   "-111",-111  );
	print_test_s8_to_str("s8_to_str (n = min)     ",	FALSE,   "-128",-128  );
	print_test_s8_to_str("s8_to_str (n = max)     ",	FALSE,    "127", 127  );
	if (g_test.flags.test_overflow)
	{
		print_test_s8_to_str("s8_to_str (n < min)     ",	FALSE,   "-129",-129  );
		print_test_s8_to_str("s8_to_str (n > max)     ",	FALSE,    "128", 128  );
		print_test_s8_to_str("s8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
		print_test_s8_to_str("s8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
	}
}
#endif



#ifdef			c_s16_to_str
void	print_test_s16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s16 number)
{
	TEST_PERFORM_RESULT(s16_to_str, number)
	print_test_str(test_name, "_s16_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_s16_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "1", 1      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,       "42", 42     );
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "0", 0      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,      "777", 777    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,     "-666",-666    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_s16_to_str("s16_to_str               ",	FALSE,   "-10000",-10000  );
	print_test_s16_to_str("s16_to_str (n = min)     ",	FALSE,   "-32768",-32768  );
	print_test_s16_to_str("s16_to_str (n = max)     ",	FALSE,    "32767", 32767  );
	if (g_test.flags.test_overflow)
	{
		print_test_s16_to_str("s16_to_str (n < min)     ",	FALSE,   "-32769",-32769  );
		print_test_s16_to_str("s16_to_str (n > max)     ",	FALSE,    "32768", 32768  );
		print_test_s16_to_str("s16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
		print_test_s16_to_str("s16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
	}
}
#endif



#ifdef			c_s32_to_str
void	print_test_s32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	TEST_PERFORM_RESULT(s32_to_str, number)
	print_test_str(test_name, "_s32_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_s32_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "1", 1           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,            "42", 42          );
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "0", 0           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,           "777", 777         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,          "-666",-666         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,        "-10000",-10000       );
	print_test_s32_to_str("s32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_s32_to_str("s32_to_str (n = min)     ",	FALSE,   "-2147483648",-2147483648  );
	print_test_s32_to_str("s32_to_str (n = max)     ",	FALSE,    "2147483647", 2147483647  );
	if (g_test.flags.test_overflow)
	{
		print_test_s32_to_str("s32_to_str (n < min)     ",	FALSE,   "-2147483649",-2147483649  );
		print_test_s32_to_str("s32_to_str (n > max)     ",	FALSE,    "2147483648", 2147483648  );
		print_test_s32_to_str("s32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
		print_test_s32_to_str("s32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
	}
}
#endif



#ifdef			c_s64_to_str
void	print_test_s64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s64 number)
{
	TEST_PERFORM_RESULT(s64_to_str, number)
	print_test_str(test_name, "_s64_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS(FORMAT_S64, number)
}
void	test_s64_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_s64_to_str("s64_to_str               ",	FALSE,                      "1", 1                     );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                     "42", 42                    );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                      "0", 0                     );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                    "777", 777                   );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                   "-666",-666                   );
	print_test_s64_to_str("s64_to_str               ",	FALSE,                 "-10000",-10000                 );
	print_test_s64_to_str("s64_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_s64_to_str("s64_to_str               ",	FALSE,             "2147483648", 2147483648            );
	print_test_s64_to_str("s64_to_str               ",	FALSE,            "-2147483649",-2147483649            );
	print_test_s64_to_str("s64_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_s64_to_str("s64_to_str               ",	FALSE,          "-999999999999",-999999999999          );
	print_test_s64_to_str("s64_to_str (n = min)     ",	FALSE,   "-9223372036854775807",-9223372036854775807LL );
	print_test_s64_to_str("s64_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807LL );
	if (g_test.flags.test_overflow)
	{
		print_test_s64_to_str("s64_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809LL  );
		print_test_s64_to_str("s64_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808LL  );
#ifndef __clang__
		print_test_s64_to_str("s64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999LL);
		print_test_s64_to_str("s64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999LL);
#endif	
	}
}
#endif



#ifdef			c_u8_to_str
void	print_test_u8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u8 number)
{
	TEST_PERFORM_RESULT(u8_to_str, number)
	print_test_str(test_name, "_u8_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u8_to_str(void)
{
//	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS
	print_test_u8_to_str("u8_to_str               ",	FALSE,      "1", 1    );
	print_test_u8_to_str("u8_to_str               ",	FALSE,     "42", 42   );
	print_test_u8_to_str("u8_to_str               ",	FALSE,    "111", 111  );
	print_test_u8_to_str("u8_to_str (n = min)     ",	FALSE,      "0", 0    );
	print_test_u8_to_str("u8_to_str (n = max)     ",	FALSE,    "255", 255  );
	if (g_test.flags.test_overflow)
	{
		print_test_u8_to_str("u8_to_str (n < min)     ",	FALSE,     "-1", -1   );
		print_test_u8_to_str("u8_to_str (n > max)     ",	FALSE,    "256", 256  );
		print_test_u8_to_str("u8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
		print_test_u8_to_str("u8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
	}
}
#endif



#ifdef			c_u16_to_str
void	print_test_u16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u16 number)
{
	TEST_PERFORM_RESULT(u16_to_str, number)
	print_test_str(test_name, "_u16_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u16_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS
	print_test_u16_to_str("u16_to_str               ",	FALSE,        "1", 1      );
	print_test_u16_to_str("u16_to_str               ",	FALSE,       "42", 42     );
	print_test_u16_to_str("u16_to_str               ",	FALSE,      "777", 777    );
	print_test_u16_to_str("u16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_u16_to_str("u16_to_str (n = min)     ",	FALSE,        "0", 0      );
	print_test_u16_to_str("u16_to_str (n = max)     ",	FALSE,    "65535", 65535  );
	if (g_test.flags.test_overflow)
	{
		print_test_u16_to_str("u16_to_str (n < min)     ",	FALSE,       "-1", -1     );
		print_test_u16_to_str("u16_to_str (n > max)     ",	FALSE,    "65536", 65536  );
		print_test_u16_to_str("u16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
		print_test_u16_to_str("u16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
	}
}
#endif



#ifdef			c_u32_to_str
void	print_test_u32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u32 number)
{
	TEST_PERFORM_RESULT(u32_to_str, number)
	print_test_str(test_name, "_u32_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u32_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "1", 1           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,            "42", 42          );
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "0", 0           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,           "777", 777         );
	print_test_u32_to_str("u32_to_str               ",	FALSE,         "10000", 10000       );
	print_test_u32_to_str("u32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_u32_to_str("u32_to_str (n = max)     ",	FALSE,    "4294967295", 4294967295  );
	print_test_u32_to_str("u32_to_str (n = min)     ",	FALSE,             "0", 0           );
	if (g_test.flags.test_overflow)
	{
		print_test_u32_to_str("u32_to_str (n < min)     ",	FALSE,            "-1", -1          );
		print_test_u32_to_str("u32_to_str (n > max)     ",	FALSE,    "4294967296", 4294967296  );
		print_test_u32_to_str("u32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
		print_test_u32_to_str("u32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
	}
}
#endif



#ifdef			c_u64_to_str
void	print_test_u64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u64 number)
{
	TEST_PERFORM_RESULT(u64_to_str, number)
	print_test_str(test_name, "_u64_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS(FORMAT_U64, number)
}
void	test_u64_to_str(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_u64_to_str("u64_to_str               ",	FALSE,                      "1", 1                     );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                     "42", 42                    );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                    "777", 777                   );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                  "10000", 10000                 );
	print_test_u64_to_str("u64_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_u64_to_str("u64_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_u64_to_str("u64_to_str (n = max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL);
	print_test_u64_to_str("u64_to_str (n = min)     ",	FALSE,                      "0", 0                     );
	if (g_test.flags.test_overflow)
	{
		print_test_u64_to_str("u64_to_str (n < min)     ",	FALSE,                     "-1", -1                    );
#ifndef __clang__
		print_test_u64_to_str("u64_to_str (n > max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL);
		print_test_u64_to_str("u64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);
		print_test_u64_to_str("u64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);
#endif
	}
}
#endif



/*
** ************************************************************************** *|
**                        Convert to Number Operations                        *|
** ************************************************************************** *|
*/

#ifdef			c_str_to_s8
void	print_test_str_to_s8(char const* test_name, int can_segfault,
		t_s8 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_s8, str_to_s8, str)
	print_test_s8(test_name, "_str_to_s8", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_s8(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "0"                          );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           1, "1"                          );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          42, "42"                         );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         -42, "-42"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          85, "   85"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          35, "\f35"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          56, "\n56"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          39, "\r39+"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         138, "\t138"                      );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "swag123"                    );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                          45, "45_"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                         111, "111"                        );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                        -111, "-111"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "  + 56"                     );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, "++43"                       );
	print_test_str_to_s8("str_to_s8               ",	FALSE,                           0, " + 41dsf-+"                 );
	print_test_str_to_s8("str_to_s8 (n = max)     ",	FALSE,                         127, "127"                        );
	print_test_str_to_s8("str_to_s8 (n = min)     ",	FALSE,                        -128, "-128"                       );
	print_test_str_to_s8("str_to_s8 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s8("str_to_s8 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_s8("str_to_s8 (n < min)     ",	FALSE,                        -129, "-129"                       );
		print_test_str_to_s8("str_to_s8 (n > max)     ",	FALSE,                         128, " 128"                       );
		print_test_str_to_s8("str_to_s8 (n > maxdigit)",	FALSE,                       99999, " 99999"                     );
		print_test_str_to_s8("str_to_s8 (n < maxdigit)",	FALSE,                      -99999, "-99999"                     );
	}
}
#endif



#ifdef			c_str_to_s16
void	print_test_str_to_s16(char const* test_name, int can_segfault,
		t_s16 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_s16, str_to_s16, str)
	print_test_s16(test_name, "_str_to_s16", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_s16(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           1, "1"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          42, "42"                         );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         397, "\r397"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                       32000, "\v32000"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "- 45678978748"              );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s16("str_to_s16 (n = max)     ",	FALSE,                       32767, " 32767"                     );
	print_test_str_to_s16("str_to_s16 (n = min)     ",	FALSE,                      -32768, "-32768"                     );
	print_test_str_to_s16("str_to_s16 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s16("str_to_s16 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_s16("str_to_s16 (n < min)     ",	FALSE,                      -32769, "-32769"                     );
		print_test_str_to_s16("str_to_s16 (n > max)     ",	FALSE,                       32768,  "32768"                     );
		print_test_str_to_s16("str_to_s16 (n > maxdigit)",	FALSE,                     9999999,  "9999999"                   );
		print_test_str_to_s16("str_to_s16 (n < maxdigit)",	FALSE,                    -9999999, "-9999999"                   );
	}
}
#endif



#ifdef			c_str_to_s32
void	print_test_str_to_s32(char const* test_name, int can_segfault,
		t_s32 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_s32, str_to_s32, str)
	print_test_s32(test_name, "_str_to_s32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_s32(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0"                          );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           1, "1"                          );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          42, "42"                         );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s32("str_to_s32",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "_456"                       );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_s32("str_to_s32",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_s32("str_to_s32 (n = max)     ",	FALSE,                  2147483647,  "2147483647"                );
	print_test_str_to_s32("str_to_s32 (n = min)     ",	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s32("str_to_s32 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s32("str_to_s32 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_s32("str_to_s32 (n < min)     ",	FALSE,                 -2147483649, "-2147483649"                );
		print_test_str_to_s32("str_to_s32 (n > max)     ",	FALSE,                  2147483648,  "2147483648"                );
		print_test_str_to_s32("str_to_s32 (n > maxdigit)",	FALSE,                999999999999,  "999999999999"              );
		print_test_str_to_s32("str_to_s32 (n < maxdigit)",	FALSE,               -999999999999, "-999999999999"              );
	}
}
#endif



#ifdef			c_str_to_s64
void	print_test_str_to_s64(char const* test_name, int can_segfault,
		t_s64 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_s64, str_to_s64, str)
	print_test_s64(test_name, "_str_to_s64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_s64(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0"                          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           1, "1"                          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          42, "42"                         );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          45, "45_"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           2, "  2"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "!789"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "#45"                        );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "$786"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "&789"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ",7"                         );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, ".456"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "_456"                       );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_s64("str_to_s64",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\\25627165465413"           );
	print_test_str_to_s64("str_to_s64",               	FALSE,                           0, "\2568"                      );
	print_test_str_to_s64("str_to_s64",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_s64("str_to_s64",               	FALSE,               -500000000000, "-500000000000"              );
	print_test_str_to_s64("str_to_s64",               	FALSE,           -6513212312310531, "-6513212312310531"          );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_s64("str_to_s64",               	FALSE,                 -3000000000, "-3000000000"                );
	print_test_str_to_s64("str_to_s64 (n = max)     ",	FALSE,       9223372036854775807LL,  "9223372036854775807"       );
	print_test_str_to_s64("str_to_s64 (n = min)     ",	FALSE,      -9223372036854775807LL, "-9223372036854775807"       );
	print_test_str_to_s64("str_to_s64 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_s64("str_to_s64 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_s64("str_to_s64 (n < min)     ",	FALSE,      -9223372036854775809LL, "-9223372036854775809"       );
		print_test_str_to_s64("str_to_s64 (n > max)     ",	FALSE,       9223372036854775808LL,  "9223372036854775808"       );
#ifndef __clang__
		print_test_str_to_s64("str_to_s64 (n > maxdigit)",	FALSE,     999999999999999999999LL,  "999999999999999999999"     );
		print_test_str_to_s64("str_to_s64 (n < maxdigit)",	FALSE,    -999999999999999999999LL, "-999999999999999999999"     );
#endif
	}
}
#endif



#ifdef			c_str_to_u8
void	print_test_str_to_u8(char const* test_name, int can_segfault,
		t_u8 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u8, str_to_u8, str)
	print_test_u8(test_name, "_str_to_u8", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_u8(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           1, "1"                          );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          42, "42"                         );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "-42"                        );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          85, "   85"                      );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          35, "\f35"                       );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          56, "\n56"                       );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          39, "\r39+"                      );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                         138, "\t138"                      );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "swag123"                    );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "(-(123"                     );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "[12]123"                    );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                          45, "45_"                        );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                         111, "111"                        );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "-111"                       );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "  + 56"                     );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, "++43"                       );
	print_test_str_to_u8("str_to_u8               ",	FALSE,                           0, " + 41dsf-+"                 );
	print_test_str_to_u8("str_to_u8 (n = max)     ",	FALSE,                         255, "255"                        );
	print_test_str_to_u8("str_to_u8 (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_u8("str_to_u8 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_u8("str_to_u8 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_u8("str_to_u8 (n < min)     ",	FALSE,                           0, "-1"                         );
		print_test_str_to_u8("str_to_u8 (n > max)     ",	FALSE,                         256,  "256"                       );
		print_test_str_to_u8("str_to_u8 (n > maxdigit)",	FALSE,                       99999,  "99999"                     );
		print_test_str_to_u8("str_to_u8 (n < maxdigit)",	FALSE,                           0, "-99999"                     );
	}
}
#endif



#ifdef			c_str_to_u16
void	print_test_str_to_u16(char const* test_name, int can_segfault,
		t_u16 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u16, str_to_u16, str)
	print_test_u16(test_name, "_str_to_u16", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_u16(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_u16("str_to_u16",               	FALSE,                           1, "1"                          );
	print_test_str_to_u16("str_to_u16",               	FALSE,                          42, "42"                         );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "-42"                        );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "-5435"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_u16("str_to_u16",               	FALSE,                          45, "45_"                        );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "  -2"                       );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           2, "  2"                        );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "!789"                       );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "#45"                        );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "$786"                       );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "&789"                       );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, ",7"                         );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, ".456"                       );
	print_test_str_to_u16("str_to_u16",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_u16("str_to_u16",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_u16("str_to_u16 (n = max)     ",	FALSE,                       65535, "65535"                      );
	print_test_str_to_u16("str_to_u16 (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_u16("str_to_u16 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_u16("str_to_u16 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_u16("str_to_u16 (n < min)     ",	FALSE,                           0, "-32769"                     );
		print_test_str_to_u16("str_to_u16 (n > max)     ",	FALSE,                       65536, "65536"                      );
		print_test_str_to_u16("str_to_u16 (n > maxdigit)",	FALSE,                     9999999, "9999999"                    );
		print_test_str_to_u16("str_to_u16 (n < maxdigit)",	FALSE,                           0, "-9999999"                   );
	}
}
#endif



#ifdef			c_str_to_u32
void	print_test_str_to_u32(char const* test_name, int can_segfault,
		t_u32 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u32, str_to_u32, str)
	print_test_u32(test_name, "_str_to_u32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_u32(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_u32("str_to_u32",               	FALSE,                           1, "1"                          );
	print_test_str_to_u32("str_to_u32",               	FALSE,                          42, "42"                         );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "-42"                        );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "-5435"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "-2147483648"                );
	print_test_str_to_u32("str_to_u32",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                          45, "45_"                        );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\f-3541"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\n-5643"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "  -2"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           2, "  2"                        );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "!789"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "#45"                        );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "$786"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "&789"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, ",7"                         );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, ".456"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "_456"                       );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_u32("str_to_u32",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_u32("str_to_u32 (n = max)     ",	FALSE,                  4294967295, "4294967295"                 );
	print_test_str_to_u32("str_to_u32 (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_u32("str_to_u32 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_u32("str_to_u32 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_u32("str_to_u32 (n < min)     ",	FALSE,                           0, "-1"                         );
		print_test_str_to_u32("str_to_u32 (n > max)     ",	FALSE,                  4294967296, "4294967296"                 );
		print_test_str_to_u32("str_to_u32 (n > maxdigit)",	FALSE,                999999999999, "999999999999"               );
		print_test_str_to_u32("str_to_u32 (n < maxdigit)",	FALSE,                           0, "-999999999999"              );
	}
}
#endif



#ifdef			c_str_to_u64
void	print_test_str_to_u64(char const* test_name, int can_segfault,
		t_u64 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u64, str_to_u64, str)
	print_test_u64(test_name, "_str_to_u64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_u64(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "0"                          );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           1, "1"                          );
	print_test_str_to_u64("str_to_u64",               	FALSE,                          42, "42"                         );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-42"                        );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-5435"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-2147483648"                );
	print_test_str_to_u64("str_to_u64",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                          45, "45_"                        );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\f-3541"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\n-5643"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "  -2"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           2, "  2"                        );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "!789"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "#45"                        );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "$786"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "&789"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, ",7"                         );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, ".456"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "_456"                       );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_u64("str_to_u64",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\\25627165465413"           );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "\2568"                      );
	print_test_str_to_u64("str_to_u64",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_u64("str_to_u64",               	FALSE,                         000, "-500000000000"              );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-6513212312310531"          );
	print_test_str_to_u64("str_to_u64",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-2147483649"                );
	print_test_str_to_u64("str_to_u64",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_u64("str_to_u64",               	FALSE,                           0, "-3000000000"                );
	print_test_str_to_u64("str_to_u64 (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_u64("str_to_u64 (n = max)     ",	FALSE,      18446744073709551615UL, "18446744073709551615"       );
	print_test_str_to_u64("str_to_u64 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_u64("str_to_u64 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
		print_test_str_to_u64("str_to_u64 (n < min)     ",	FALSE,                           0, "-1"                         );
#ifndef __clang__
		print_test_str_to_u64("str_to_u64 (n > max)     ",	FALSE,      18446744073709551616UL, "18446744073709551616"       );
		print_test_str_to_u64("str_to_u64 (n > maxdigit)",	FALSE,     999999999999999999999LL, "999999999999999999999"      );
#endif
		print_test_str_to_u64("str_to_u64 (n < maxdigit)",	FALSE,                           0, "-999999999999999999999"     );
	}
}
#endif



/*
** ************************************************************************** *|
**                       Convert to Hexadecimal String                        *|
** ************************************************************************** *|
*/

#ifdef			c_u8_to_strhex
void	print_test_u8_to_strhex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	TEST_PERFORM_RESULT(u8_to_strhex, number)
	print_test_str(test_name, "_u8_to_strhex", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u8_to_strhex(void)
{
//	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS
	print_test_u8_to_strhex("u8_to_strhex               ",	FALSE,      "1", 1    );
	print_test_u8_to_strhex("u8_to_strhex               ",	FALSE,     "2A", 42   );
	print_test_u8_to_strhex("u8_to_strhex               ",	FALSE,     "6F", 111  );
	print_test_u8_to_strhex("u8_to_strhex (n = max)     ",	FALSE,     "FF", 255  );
	print_test_u8_to_strhex("u8_to_strhex (n = min)     ",	FALSE,      "0", 0    );
	if (g_test.flags.test_overflow)
	{
		print_test_u8_to_strhex("u8_to_strhex (n < min)     ",	FALSE,     "-1", -1   );
		print_test_u8_to_strhex("u8_to_strhex (n > max)     ",	FALSE,    "100", 256  );
		print_test_u8_to_strhex("u8_to_strhex (n > maxdigit)",	FALSE,  "1869F", 99999);
		print_test_u8_to_strhex("u8_to_strhex (n < maxdigit)",	FALSE, "-1869F",-99999);
	}
}
#endif



#ifdef			c_u16_to_strhex
void	print_test_u16_to_strhex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	TEST_PERFORM_RESULT(u16_to_strhex, number)
	print_test_str(test_name, "_u16_to_strhex", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u16_to_strhex(void)
{
//	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS
	print_test_u16_to_strhex("u16_to_strhex               ",	FALSE,        "1", 1      );
	print_test_u16_to_strhex("u16_to_strhex               ",	FALSE,       "2A", 42     );
	print_test_u16_to_strhex("u16_to_strhex               ",	FALSE,      "309", 777    );
	print_test_u16_to_strhex("u16_to_strhex               ",	FALSE,     "2710", 10000  );
	print_test_u16_to_strhex("u16_to_strhex (n = max)     ",	FALSE,     "FFFF", 65535  );
	print_test_u16_to_strhex("u16_to_strhex (n = min)     ",	FALSE,        "0", 0      );
	if (g_test.flags.test_overflow)
	{
		print_test_u16_to_strhex("u16_to_strhex (n < min)     ",	FALSE,       "-1", -1     );
		print_test_u16_to_strhex("u16_to_strhex (n > max)     ",	FALSE,    "10000", 65536  );
		print_test_u16_to_strhex("u16_to_strhex (n > maxdigit)",	FALSE,   "98967F", 9999999);
		print_test_u16_to_strhex("u16_to_strhex (n < maxdigit)",	FALSE,  "-98967F",-9999999);
	}
}
#endif



#ifdef			c_u32_to_strhex
void	print_test_u32_to_strhex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	TEST_PERFORM_RESULT(u32_to_strhex, number)
	print_test_str(test_name, "_u32_to_strhex", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%d", number)
}
void	test_u32_to_strhex(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,             "1", 1           );
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,            "2A", 42          );
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,             "0", 0           );
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,           "30A", 778         );
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,          "2710", 10000       );
	print_test_u32_to_strhex("u32_to_strhex               ",	FALSE,       "75BCD15", 123456789   );
	print_test_u32_to_strhex("u32_to_strhex (n = max)     ",	FALSE,      "FFFFFFFF", 4294967295  );
	print_test_u32_to_strhex("u32_to_strhex (n = min)     ",	FALSE,             "0", 0           );
	if (g_test.flags.test_overflow)
	{
		print_test_u32_to_strhex("u32_to_strhex (n < min)     ",	FALSE,            "-1", -1          );
		print_test_u32_to_strhex("u32_to_strhex (n > max)     ",	FALSE,     "100000000", 4294967296  );
		print_test_u32_to_strhex("u32_to_strhex (n > maxdigit)",	FALSE,    "E8D4A50FFF", 999999999999);
		print_test_u32_to_strhex("u32_to_strhex (n < maxdigit)",	FALSE,   "-E8D4A50FFF",-999999999999);
	}
}
#endif



#ifdef			c_u64_to_strhex
void	print_test_u64_to_strhex(char const* test_name, int can_segfault,
		char const* expecting,
		t_u64 number)
{
	TEST_PERFORM_RESULT(u64_to_strhex, number)
	print_test_str(test_name, "_u64_to_strhex", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS(FORMAT_U64, number)
}
void	test_u64_to_strhex(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,                      "1", 1                     );
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,                     "2A", 42                    );
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,                    "30A", 778                   );
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,                   "2710", 10000                 );
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,                "75BCD15", 123456789             );
	print_test_u64_to_strhex("u64_to_strhex               ",	FALSE,             "E8D4A50FFF", 999999999999L         );
	print_test_u64_to_strhex("u64_to_strhex (n = max)     ",	FALSE,       "FFFFFFFFFFFFFFFF", 18446744073709551615UL);
	print_test_u64_to_strhex("u64_to_strhex (n = min)     ",	FALSE,                      "0", 0                     );
	if (g_test.flags.test_overflow)
	{
		print_test_u64_to_strhex("u64_to_strhex (n < min)     ",	FALSE,                     "-1", -1                    );
#ifndef __clang__
		print_test_u64_to_strhex("u64_to_strhex (n > max)     ",	FALSE,      "10000000000000000", 18446744073709551616UL);
		print_test_u64_to_strhex("u64_to_strhex (n > maxdigit)",	FALSE,                      "0", 999999999999999999999UL);
		print_test_u64_to_strhex("u64_to_strhex (n < maxdigit)",	FALSE,                      "0",-999999999999999999999UL);
#endif
	}
}
#endif



#ifdef			c_strhex_to_u8
void	print_test_strhex_to_u8(char const* test_name, int can_segfault,
		t_u8 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u8, strhex_to_u8, str)
	print_test_u8(test_name, "_strhex_to_u8", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhex_to_u8(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			c_strhex_to_u16
void	print_test_strhex_to_u16(char const* test_name, int can_segfault,
		t_u16 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u16, strhex_to_u16, str)
	print_test_u16(test_name, "_strhex_to_u16", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhex_to_u16(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			c_strhex_to_u32
void	print_test_strhex_to_u32(char const* test_name, int can_segfault,
		t_u32 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u32, strhex_to_u32, str)
	print_test_u32(test_name, "_strhex_to_u32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhex_to_u32(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			c_strhex_to_u64
void	print_test_strhex_to_u64(char const* test_name, int can_segfault,
		t_u64 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_u64, strhex_to_u64, str)
	print_test_u64(test_name, "_strhex_to_u64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhex_to_u64(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



/*
** ************************************************************************** *|
**                       Convert Integer to Base String                       *|
** ************************************************************************** *|
*/

#ifdef			c_s8_to_strbase
void	print_test_s8_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s8 number,
		char const* base)
{
	TEST_PERFORM_RESULT(s8_to_strbase, number, base)
	print_test_str(test_name, "_s8_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_s8_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,           "1",           1,               "01");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,           1,               "+1");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,           0,                "m");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,           1,                "m");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,      "101010",          42,               "01");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,           0,              "mom");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,           "0",           0,              "0az");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,         "aaa",         111,       "_abcdefghi");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,        "-aaa",        -111,       "_abcdefghi");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          "-F",         -15, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,        "rdmm",          63,              "mdr");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,       "|*_*|",         100,              "*|_");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,        ".._.",          13,               "_.");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          "2A",          42, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          "42",          42,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,          42,       "012345678-");
	print_test_s8_to_strbase("s8_to_strbase               ",	FALSE,          NULL,          42,       "012345678+");
	print_test_s8_to_strbase("s8_to_strbase (n = min, dec)",	FALSE,        "-128",        -128,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n = max, dec)",	FALSE,         "127",         127,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n = min, hex)",	FALSE,         "-80",        -128, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase (n = max, hex)",	FALSE,          "7F",         127, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase (n = min, bin)",	FALSE,   "-10000000",        -128,               "01");
	print_test_s8_to_strbase("s8_to_strbase (n = max, bin)",	FALSE,     "1111111",         127,               "01");
	print_test_s8_to_strbase("s8_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_s8_to_strbase("s8_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_s8_to_strbase("s8_to_strbase (n < min)     ",	FALSE,        "-129",        -129,       "0123456789");
		print_test_s8_to_strbase("s8_to_strbase (n > max)     ",	FALSE,         "128",         128,       "0123456789");
		print_test_s8_to_strbase("s8_to_strbase (n > maxdigit)",	FALSE,          NULL,       99999,               "01");
		print_test_s8_to_strbase("s8_to_strbase (n < maxdigit)",	FALSE,          NULL,      -99999,               "01");
	}
}
#endif



#ifdef			c_s16_to_strbase
void	print_test_s16_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s16 number,
		char const* base)
{
	TEST_PERFORM_RESULT(s16_to_strbase, number, base)
	print_test_str(test_name, "_s16_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_s16_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,           "1",           1,               "01");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,           1,               "+1");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,           0,                "m");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,           1,                "m");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,      "101010",          42,               "01");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,           0,              "mom");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,           "0",           0,              "0az");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,         "aaa",         111,       "_abcdefghi");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,        "-aaa",        -111,       "_abcdefghi");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          "-F",         -15, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,        "rdmm",          63,              "mdr");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,       "|*_*|",         100,              "*|_");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,        ".._.",          13,               "_.");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,       "12345",       12345,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,       12345,       "012345678-");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,       12345,       "012345678+");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          NULL,         999,       "01+3456789");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,       "c===3",       10007,       "=cbadef389");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,        "swag",        1234,       "0swag56789");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,        "-3e8",       -1000, "0123456789abcdef");
	print_test_s16_to_strbase("s16_to_strbase               ",	FALSE,          "2A",          42, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase (n = min, dec)",	FALSE,      "-32768",      -32768,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n = max, dec)",	FALSE,       "32767",       32767,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n = min, hex)",	FALSE,       "-8000",      -32768, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase (n = max, hex)",	FALSE,        "7FFF",       32767, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase (n = min, bin)",	FALSE,"-1000000000000000", -32768,               "01");
	print_test_s16_to_strbase("s16_to_strbase (n = max, bin)",	FALSE,  "111111111111111",  32767,               "01");
	print_test_s16_to_strbase("s16_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_s16_to_strbase("s16_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_s16_to_strbase("s16_to_strbase (n < min)     ",	FALSE,      "-32769",      -32769,       "0123456789");
		print_test_s16_to_strbase("s16_to_strbase (n > max)     ",	FALSE,       "32768",       32768,       "0123456789");
		print_test_s16_to_strbase("s16_to_strbase (n > maxdigit)",	FALSE,          NULL,     9999999,               "01");
		print_test_s16_to_strbase("s16_to_strbase (n < maxdigit)",	FALSE,          NULL,    -9999999,               "01");
	}
}
#endif



#ifdef			c_s32_to_strbase
void	print_test_s32_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number,
		char const* base)
{
	TEST_PERFORM_RESULT(s32_to_strbase, number, base)
	print_test_str(test_name, "_s32_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_s32_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING                   | TEST ARGS
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                       "1",                   1,               "01");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,                   1,               "+1");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,                   0,                "m");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,                   1,                "m");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                  "101010",                  42,               "01");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,                   0,              "mom");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      "-F",                 -15, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                    "rdmm",                  63,              "mdr");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                   "|*_*|",                 100,              "*|_");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                    ".._.",                  13,               "_.");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                       "0",                   0,              "0az");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                     "aaa",                 111,       "_abcdefghi");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                    "-aaa",                -111,       "_abcdefghi");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                   "12345",               12345,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,               12345,       "012345678-");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,               12345,       "012345678+");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                      NULL,                 999,       "01+3456789");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                   "c===3",               10007,       "=cbadef389");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                    "swag",                1234,       "0swag56789");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                    "-3e8",               -1000, "0123456789abcdef");
	print_test_s32_to_strbase("s32_to_strbase               ",	FALSE,                  "*xurin",             +987123,       "grincheux*");
	print_test_s32_to_strbase("s32_to_strbase (n = min, dec)",	FALSE,             "-2147483648",         -2147483648,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n = max, dec)",	FALSE,              "2147483647",          2147483647,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n = min, hex)",	FALSE,               "-80000000",         -2147483648, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase (n = max, hex)",	FALSE,                "7FFFFFFF",          2147483647, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase (n = min, bin)",	FALSE,"-10000000000000000000000000000000",-2147483648,               "01");
	print_test_s32_to_strbase("s32_to_strbase (n = max, bin)",	FALSE,  "1111111111111111111111111111111", 2147483647,               "01");
	print_test_s32_to_strbase("s32_to_strbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");
	print_test_s32_to_strbase("s32_to_strbase (null base)   ",	TRUE,                     segstr,                  42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_s32_to_strbase("s32_to_strbase (n < min)     ",	FALSE,             "-2147483649",         -2147483649,       "0123456789");
		print_test_s32_to_strbase("s32_to_strbase (n > max)     ",	FALSE,              "2147483648",          2147483648,       "0123456789");
		print_test_s32_to_strbase("s32_to_strbase (n > maxdigit)",	FALSE,                      NULL,        999999999999,               "01");
		print_test_s32_to_strbase("s32_to_strbase (n < maxdigit)",	FALSE,                      NULL,       -999999999999,               "01");
	}
}
#endif



#ifdef			c_s64_to_strbase
void	print_test_s64_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s64 number,
		char const* base)
{
	TEST_PERFORM_RESULT(s64_to_strbase, number, base)
	print_test_str(test_name, "_s64_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n="FORMAT_S64, base, number);
}
void	test_s64_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                     "1",                    1,               "01");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                    1,               "+1");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                    0,                "m");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                    1,                "m");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                "101010",                   42,               "01");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                    0,              "mom");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    "2A",                   42, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                     "0",                    0,              "0az");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                   "aaa",                  111,       "_abcdefghi");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                  "-aaa",                 -111,       "_abcdefghi");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    "-F",                  -15, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                  "rdmm",                   63,              "mdr");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                 "|*_*|",                  100,              "*|_");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                  ".._.",                   13,               "_.");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                 "12345",                12345,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                12345,       "012345678-");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                12345,       "012345678+");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                    NULL,                  999,       "01+3456789");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                 "c===3",                10007,       "=cbadef389");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                  "swag",                 1234,       "0swag56789");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                  "-3e8",                -1000, "0123456789abcdef");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,                "*xurin",              +987123,       "grincheux*");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,              "7FFFFFFF",           2147483647, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase               ",	FALSE,           "-2147483648",          -2147483648,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n = min, dec)",	FALSE,  "-9223372036854775807", -9223372036854775807,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n = max, dec)",	FALSE,   "9223372036854775807",  9223372036854775807,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n = min, hex)",	FALSE,     "-7FFFFFFFFFFFFFFF", -9223372036854775807, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase (n = max, hex)",	FALSE,      "7FFFFFFFFFFFFFFF",  9223372036854775807, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase (n = min, bin)",	FALSE,"-111111111111111111111111111111111111111111111111111111111111111",-9223372036854775807,"01");
	print_test_s64_to_strbase("s64_to_strbase (n = max, bin)",	FALSE, "111111111111111111111111111111111111111111111111111111111111111", 9223372036854775807,"01");
	print_test_s64_to_strbase("s64_to_strbase (empty base)  ",	FALSE,                    NULL,                   42,                 "");
	print_test_s64_to_strbase("s64_to_strbase (null base)   ",	TRUE,                   segstr,                   42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_s64_to_strbase("s64_to_strbase (n < min)     ",	FALSE,"-9223372036854775808",   -9223372036854775808,       "0123456789");
		print_test_s64_to_strbase("s64_to_strbase (n > max)     ",	FALSE, "9223372036854775808",    9223372036854775808,       "0123456789");
#ifndef __clang__
		print_test_s64_to_strbase("s64_to_strbase (n > maxdigit)",	FALSE,                  NULL,  999999999999999999999,               "01");
		print_test_s64_to_strbase("s64_to_strbase (n < maxdigit)",	FALSE,                  NULL, -999999999999999999999,               "01");
#endif
	}
}
#endif



#ifdef			c_u8_to_strbase
void	print_test_u8_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u8 number,
		char const* base)
{
	TEST_PERFORM_RESULT(u8_to_strbase, number, base)
	print_test_str(test_name, "_u8_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_u8_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,           "1",           1,               "01");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,           "1",           1,               "+1");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          NULL,           0,                "m");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          NULL,           1,                "m");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,      "101010",          42,               "01");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          NULL,           0,              "mom");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,           "0",           0,              "0az");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,         "aaa",         111,       "_abcdefghi");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,           "F",          15, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,        "rdmm",          63,              "mdr");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,       "|*_*|",         100,              "*|_");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,        ".._.",          13,               "_.");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          "2A",          42, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          "42",          42,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          "42",          42,       "012345678-");
	print_test_u8_to_strbase("u8_to_strbase               ",	FALSE,          "42",          42,       "012345678+");
	print_test_u8_to_strbase("u8_to_strbase (n = min, dec)",	FALSE,           "0",           0,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n = max, dec)",	FALSE,         "255",         255,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n = min, hex)",	FALSE,           "0",           0, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase (n = max, hex)",	FALSE,          "FF",         255, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase (n = min, bin)",	FALSE,           "0",           0,               "01");
	print_test_u8_to_strbase("u8_to_strbase (n = max, bin)",	FALSE,    "11111111",         255,               "01");
	print_test_u8_to_strbase("u8_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_u8_to_strbase("u8_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_u8_to_strbase("u8_to_strbase (n < min)     ",	FALSE,          "-1",          -1,       "0123456789");
		print_test_u8_to_strbase("u8_to_strbase (n > max)     ",	FALSE,         "256",         256,       "0123456789");
		print_test_u8_to_strbase("u8_to_strbase (n > maxdigit)",	FALSE,          NULL,       99999,               "01");
		print_test_u8_to_strbase("u8_to_strbase (n < maxdigit)",	FALSE,          NULL,      -99999,               "01");
	}
}
#endif



#ifdef			c_u16_to_strbase
void	print_test_u16_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u16 number,
		char const* base)
{
	TEST_PERFORM_RESULT(u16_to_strbase, number, base)
	print_test_str(test_name, "_u16_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_u16_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,           "1",           1,               "01");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,           "1",           1,               "+1");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,          NULL,           0,                "m");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,          NULL,           1,                "m");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,      "101010",          42,               "01");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,          NULL,           0,              "mom");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,           "0",           0,              "0az");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,         "aaa",         111,       "_abcdefghi");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,           "F",          15, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,        "rdmm",          63,              "mdr");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,       "|*_*|",         100,              "*|_");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,        ".._.",          13,               "_.");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,       "12345",       12345,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,       "12345",       12345,       "012345678-");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,       "12345",       12345,       "012345678+");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,          NULL,         999,       "0123456739");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,       "c===3",       10007,       "=cbadef389");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,        "swag",        1234,       "0swag56789");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,         "3e8",        1000, "0123456789abcdef");
	print_test_u16_to_strbase("u16_to_strbase               ",	FALSE,          "2A",          42, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase (n = min, dec)",	FALSE,           "0",           0,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n = max, dec)",	FALSE,       "65535",       65535,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n = min, hex)",	FALSE,           "0",           0, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase (n = max, hex)",	FALSE,        "FFFF",       65535, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase (n = min, bin)",	FALSE,           "0",           0,               "01");
	print_test_u16_to_strbase("u16_to_strbase (n = max, bin)",	FALSE, "1111111111111111",  65535,               "01");
	print_test_u16_to_strbase("u16_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_u16_to_strbase("u16_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_u16_to_strbase("u16_to_strbase (n < min)     ",	FALSE,          "-1",          -1,       "0123456789");
		print_test_u16_to_strbase("u16_to_strbase (n > max)     ",	FALSE,       "65536",       65536,       "0123456789");
		print_test_u16_to_strbase("u16_to_strbase (n > maxdigit)",	FALSE,          NULL,     9999999,               "01");
		print_test_u16_to_strbase("u16_to_strbase (n < maxdigit)",	FALSE,          NULL,    -9999999,               "01");
	}
}
#endif



#ifdef			c_u32_to_strbase
void	print_test_u32_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u32 number,
		char const* base)
{
	TEST_PERFORM_RESULT(u32_to_strbase, number, base)
	print_test_str(test_name, "_u32_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);
}
void	test_u32_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING                   | TEST ARGS
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                       "1",                   1,               "01");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                       "1",                   1,               "+1");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                      NULL,                   0,                "m");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                      NULL,                   1,                "m");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                  "101010",                  42,               "01");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                      NULL,                   0,              "mom");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                       "F",                  15, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                    "rdmm",                  63,              "mdr");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                   "|*_*|",                 100,              "*|_");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                    ".._.",                  13,               "_.");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                       "0",                   0,              "0az");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                     "aaa",                 111,       "_abcdefghi");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                   "12345",               12345,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                   "12345",               12345,       "012345678-");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                   "12345",               12345,       "012345678+");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                      NULL,                 999,       "0123456739");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                   "c===3",               10007,       "=cbadef389");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                    "swag",                1234,       "0swag56789");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                     "3e8",                1000, "0123456789abcdef");
	print_test_u32_to_strbase("u32_to_strbase               ",	FALSE,                  "*xurin",             +987123,       "grincheux*");
	print_test_u32_to_strbase("u32_to_strbase (n = min, dec)",	FALSE,                       "0",                   0,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n = max, dec)",	FALSE,              "4294967295",          4294967295,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n = min, hex)",	FALSE,                       "0",                   0, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase (n = max, hex)",	FALSE,                "FFFFFFFF",          4294967295, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase (n = min, bin)",	FALSE,                       "0",                   0,               "01");
	print_test_u32_to_strbase("u32_to_strbase (n = max, bin)",	FALSE, "11111111111111111111111111111111", 4294967295,               "01");
	print_test_u32_to_strbase("u32_to_strbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");
	print_test_u32_to_strbase("u32_to_strbase (null base)   ",	TRUE,                     segstr,                  42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_u32_to_strbase("u32_to_strbase (n < min)     ",	FALSE,                      "-1",                  -1,       "0123456789");
		print_test_u32_to_strbase("u32_to_strbase (n > max)     ",	FALSE,              "4294967296",          4294967296,       "0123456789");
		print_test_u32_to_strbase("u32_to_strbase (n > maxdigit)",	FALSE,                      NULL,        999999999999,               "01");
		print_test_u32_to_strbase("u32_to_strbase (n < maxdigit)",	FALSE,                      NULL,       -999999999999,               "01");
	}
}
#endif



#ifdef			c_u64_to_strbase
void	print_test_u64_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u64 number,
		char const* base)
{
	TEST_PERFORM_RESULT(u64_to_strbase, number, base)
	print_test_str(test_name, "_u64_to_strbase", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n="FORMAT_U64, base, number);
}
void	test_u64_to_strbase(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                    "1",                      1,               "01");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                    "1",                      1,               "+1");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                   NULL,                      0,                "m");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                   NULL,                      1,                "m");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,               "101010",                     42,               "01");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                   NULL,                      0,              "mom");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                   "2A",                     42, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                    "0",                      0,              "0az");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                  "aaa",                    111,       "_abcdefghi");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                    "F",                     15, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                 "rdmm",                     63,              "mdr");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                "|*_*|",                    100,              "*|_");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                 ".._.",                     13,               "_.");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                "12345",                  12345,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                "12345",                  12345,       "012345678-");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                "12345",                  12345,       "012345678+");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                   NULL,                    999,       "0123456389");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                "c===3",                  10007,       "=cbadef389");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                 "swag",                   1234,       "0swag56789");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,                  "3e8",                   1000, "0123456789abcdef");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,               "*xurin",                +987123,       "grincheux*");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,             "7FFFFFFF",             2147483647, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase               ",	FALSE,           "2147483648",             2147483648,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n = min, dec)",	FALSE,                    "0",                      0,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n = max, dec)",	FALSE, "18446744073709551615", 18446744073709551615UL,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n = min, hex)",	FALSE,                    "0",                      0, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase (n = max, hex)",	FALSE,     "FFFFFFFFFFFFFFFF", 18446744073709551615UL, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase (n = min, bin)",	FALSE,                     "0",                     0,               "01");
	print_test_u64_to_strbase("u64_to_strbase (n = max, bin)",	FALSE, "1111111111111111111111111111111111111111111111111111111111111111", 18446744073709551615UL,"01");
	print_test_u64_to_strbase("u64_to_strbase (empty base)  ",	FALSE,                    NULL,                    42,                 "");
	print_test_u64_to_strbase("u64_to_strbase (null base)   ",	TRUE,                   segstr,                    42,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_u64_to_strbase("u64_to_strbase (n < min)     ",	FALSE,                   "-1",                       -1,     "0123456789");
#ifndef __clang__
		print_test_u64_to_strbase("u64_to_strbase (n > max)     ",	FALSE, "18446744073709551616",   18446744073709551616UL,     "0123456789");
		print_test_u64_to_strbase("u64_to_strbase (n > maxdigit)",	FALSE,                   NULL,  999999999999999999999LL,             "01");
		print_test_u64_to_strbase("u64_to_strbase (n < maxdigit)",	FALSE,                   NULL, -999999999999999999999LL,             "01");
#endif
	}
}
#endif











/*
** ************************************************************************** *|
**                       Convert Base String to Integer                       *|
** ************************************************************************** *|
*/

#ifdef			c_strbase_to_s8
void	print_test_strbase_to_s8(char const* test_name, int can_segfault,
		t_s8 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_s8, strbase_to_s8, number, base)
	print_test_s8(test_name, "_strbase_to_s8", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_s8(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           1,           "1",               "01");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "1",               "+1");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "m",                "m");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,          "mm",                "m");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,         "mmm",                "m");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,          42,      "101010",               "01");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,      "101012",               "01");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "m",              "mom");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "o",              "mom");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "0",              "0az");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,         111,         "aaa",       "_abcdefghi");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,        -111,        "-aaa",       "_abcdefghi");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,         -15,          "-F", "0123456789ABCDEF");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,          63,        "rdmm",              "mdr");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,         100,       "|*_*|",              "*|_");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,          13,        ".._.",               "_.");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,          42,          "2A", "0123456789ABCDEF");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,          42,          "42",       "0123456789");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "2",       "012345678-");
	print_test_strbase_to_s8("strbase_to_s8               ",	FALSE,           0,           "2",       "012345678+");
	print_test_strbase_to_s8("strbase_to_s8 (n = min, dec)",	FALSE,        -128,        "-128",       "0123456789");
	print_test_strbase_to_s8("strbase_to_s8 (n = max, dec)",	FALSE,         127,         "127",       "0123456789");
	print_test_strbase_to_s8("strbase_to_s8 (n = min, hex)",	FALSE,        -128,         "-80", "0123456789ABCDEF");
	print_test_strbase_to_s8("strbase_to_s8 (n = max, hex)",	FALSE,         127,          "7F", "0123456789ABCDEF");
	print_test_strbase_to_s8("strbase_to_s8 (n = min, bin)",	FALSE,        -128,   "-10000000",               "01");
	print_test_strbase_to_s8("strbase_to_s8 (n = max, bin)",	FALSE,         127,     "1111111",               "01");
	print_test_strbase_to_s8("strbase_to_s8 (empty base)  ",	FALSE,           0,          "01",                 "");
	print_test_strbase_to_s8("strbase_to_s8 (empty number)",	FALSE,           0,            "",               "01");
	print_test_strbase_to_s8("strbase_to_s8 (both empty)  ",	FALSE,           0,            "",                 "");
	print_test_strbase_to_s8("strbase_to_s8 (null base)   ",	SEGV,            0,          "01",               NULL);
	print_test_strbase_to_s8("strbase_to_s8 (null number) ",	SEGV,            0,          NULL,               "01");
	print_test_strbase_to_s8("strbase_to_s8 (both null)   ",	SEGV,            0,          NULL,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_s8("strbase_to_s8 (n < min)     ",	FALSE,       -129,     "-129",       "0123456789");
		print_test_strbase_to_s8("strbase_to_s8 (n > max)     ",	FALSE,        128,      "128",       "0123456789");
		print_test_strbase_to_s8("strbase_to_s8 (n < maxdigit)",	FALSE,     -99999,   "-99999",       "0123456789");
		print_test_strbase_to_s8("strbase_to_s8 (n > maxdigit)",	FALSE,      99999,    "99999",       "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_s16
void	print_test_strbase_to_s16(char const* test_name, int can_segfault,
		t_s16 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_s16, strbase_to_s16, number, base)
	print_test_s16(test_name, "_strbase_to_s16", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_s16(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          1,            "1",                   "01");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,            "1",                   "+1");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,            "m",                    "m");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,           "mm",                    "m");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,          "mmm",                    "m");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,         42,       "101010",                   "01");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,       "101012",                   "01");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,            "m",                  "mom");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,            "o",                  "mom");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,            "0",                  "0az");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,        111,          "aaa",           "_abcdefghi");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,       -111,         "-aaa",           "_abcdefghi");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,        -15,           "-F",     "0123456789ABCDEF");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,         63,         "rdmm",                  "mdr");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,        100,        "|*_*|",                  "*|_");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,         13,         ".._.",                   "_.");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,      12345,        "12345",           "0123456789");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,        "12345",           "012345678-");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,        "12345",           "012345678+");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,          0,          "999",           "01+3456789");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,      10007,        "c===3",           "=cbadef389");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,       1234,         "swag",           "0swag56789");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,      -1000,         "-3e8",     "0123456789abcdef");
	print_test_strbase_to_s16("strbase_to_s16               ",	FALSE,         42,           "2A",     "0123456789ABCDEF");
	print_test_strbase_to_s16("strbase_to_s16 (n = min, dec)",	FALSE,     -32768,       "-32768",           "0123456789");
	print_test_strbase_to_s16("strbase_to_s16 (n = max, dec)",	FALSE,      32767,        "32767",           "0123456789");
	print_test_strbase_to_s16("strbase_to_s16 (n = min, hex)",	FALSE,     -32768,        "-8000",     "0123456789ABCDEF");
	print_test_strbase_to_s16("strbase_to_s16 (n = max, hex)",	FALSE,      32767,         "7FFF",     "0123456789ABCDEF");
	print_test_strbase_to_s16("strbase_to_s16 (n = min, bin)",	FALSE,     -32768,     "-1000000000000000",          "01");
	print_test_strbase_to_s16("strbase_to_s16 (n = max, bin)",	FALSE,      32767,       "111111111111111",          "01");
	print_test_strbase_to_s16("strbase_to_s16 (empty base)  ",	FALSE,          0,          "01",                      "");
	print_test_strbase_to_s16("strbase_to_s16 (empty number)",	FALSE,          0,            "",                    "01");
	print_test_strbase_to_s16("strbase_to_s16 (both empty)  ",	FALSE,          0,            "",                      "");
	print_test_strbase_to_s16("strbase_to_s16 (null base)   ",	SEGV,           0,          "01",                    NULL);
	print_test_strbase_to_s16("strbase_to_s16 (null number) ",	SEGV,           0,          NULL,                    "01");
	print_test_strbase_to_s16("strbase_to_s16 (both null)   ",	SEGV,           0,          NULL,                    NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_s16("strbase_to_s16 (n < min)     ",	FALSE,     -32769,    "-32769",          "0123456789");
		print_test_strbase_to_s16("strbase_to_s16 (n > max)     ",	FALSE,      32768,     "32768",          "0123456789");
		print_test_strbase_to_s16("strbase_to_s16 (n < maxdigit)",	FALSE,   -9999999,  "-9999999",          "0123456789");
		print_test_strbase_to_s16("strbase_to_s16 (n > maxdigit)",	FALSE,    9999999,   "9999999",          "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_s32
void	print_test_strbase_to_s32(char const* test_name, int can_segfault,
		t_s32 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_s32, strbase_to_s32, number, base)
	print_test_s32(test_name, "_strbase_to_s32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_s32(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV| EXPECTING  | TEST ARGS
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           1,                       "1",                        "01");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                       "1",                        "+1");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                       "m",                         "m");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                      "mm",                         "m");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                     "mmm",                         "m");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,          42,                  "101010",                        "01");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                  "101012",                        "01");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                       "m",                       "mom");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                       "o",                       "mom");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,         -15,                      "-F",          "0123456789ABCDEF");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,          63,                    "rdmm",                       "mdr");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,         100,                   "|*_*|",                       "*|_");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,          13,                    ".._.",                        "_.");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,          42,                      "2A",          "0123456789ABCDEF");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                       "0",                       "0az");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,         111,                     "aaa",                "_abcdefghi");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,        -111,                    "-aaa",                "_abcdefghi");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,       12345,                   "12345",                "0123456789");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                   "12345",                "012345678-");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                   "12345",                "012345678+");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,           0,                     "999",                "01+3456789");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,       10007,                   "c===3",                "=cbadef389");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,        1234,                    "swag",                "0swag56789");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,       -1000,                    "-3e8",          "0123456789abcdef");
	print_test_strbase_to_s32("strbase_to_s32               ",	FALSE,     +987123,                  "*xurin",                "grincheux*");
	print_test_strbase_to_s32("strbase_to_s32 (n = min, dec)",	FALSE, -2147483648,             "-2147483648",                "0123456789");
	print_test_strbase_to_s32("strbase_to_s32 (n = max, dec)",	FALSE,  2147483647,              "2147483647",                "0123456789");
	print_test_strbase_to_s32("strbase_to_s32 (n = min, hex)",	FALSE, -2147483648,               "-80000000",          "0123456789ABCDEF");
	print_test_strbase_to_s32("strbase_to_s32 (n = max, hex)",	FALSE,  2147483647,                "7FFFFFFF",          "0123456789ABCDEF");
	print_test_strbase_to_s32("strbase_to_s32 (n = min, bin)",	FALSE, -2147483648,    "-10000000000000000000000000000000",           "01");
	print_test_strbase_to_s32("strbase_to_s32 (n = max, bin)",	FALSE,  2147483647,      "1111111111111111111111111111111",           "01");
	print_test_strbase_to_s32("strbase_to_s32 (empty base)  ",	FALSE,           0,                      "01",                          "");
	print_test_strbase_to_s32("strbase_to_s32 (empty number)",	FALSE,           0,                        "",                        "01");
	print_test_strbase_to_s32("strbase_to_s32 (both empty)  ",	FALSE,           0,                        "",                          "");
	print_test_strbase_to_s32("strbase_to_s32 (null base)   ",	SEGV,            0,                      "01",                        NULL);
	print_test_strbase_to_s32("strbase_to_s32 (null number) ",	SEGV,            0,                      NULL,                        "01");
	print_test_strbase_to_s32("strbase_to_s32 (both null)   ",	SEGV,            0,                      NULL,                        NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_s32("strbase_to_s32 (n < min)     ",	FALSE,    -2147483649,      "-2147483649",                "0123456789");
		print_test_strbase_to_s32("strbase_to_s32 (n > max)     ",	FALSE,     2147483648,       "2147483648",                "0123456789");
		print_test_strbase_to_s32("strbase_to_s32 (n < maxdigit)",	FALSE,  -999999999999,    "-999999999999",                "0123456789");
		print_test_strbase_to_s32("strbase_to_s32 (n > maxdigit)",	FALSE,   999999999999,     "999999999999",                "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_s64
void	print_test_strbase_to_s64(char const* test_name, int can_segfault,
		t_s64 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_s64, strbase_to_s64, number, base)
	print_test_s64(test_name, "_strbase_to_s64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_s64(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING         | TEST ARGS
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    1,                    "1",               "01");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                    "1",               "+1");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                    "m",                "m");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                   "mm",                "m");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                  "mmm",                "m");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                   42,               "101010",               "01");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,               "101012",               "01");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                    "m",              "mom");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                    "o",              "mom");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                   42,                   "2A", "0123456789ABCDEF");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                    "0",              "0az");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                  111,                  "aaa",       "_abcdefghi");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                 -111,                 "-aaa",       "_abcdefghi");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                  -15,                   "-F", "0123456789ABCDEF");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                   63,                 "rdmm",              "mdr");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                  100,                "|*_*|",              "*|_");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                   13,                 ".._.",               "_.");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                12345,                "12345",       "0123456789");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                "12345",       "012345678-");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                "12345",       "012345678+");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                    0,                  "999",       "01+3456789");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                10007,                "c===3",       "=cbadef389");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                 1234,                 "swag",       "0swag56789");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,                -1000,                 "-3e8", "0123456789abcdef");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,              +987123,               "*xurin",       "grincheux*");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,           2147483647,             "7FFFFFFF", "0123456789ABCDEF");
	print_test_strbase_to_s64("strbase_to_s64               ",	FALSE,          -2147483648,          "-2147483648",       "0123456789");
	print_test_strbase_to_s64("strbase_to_s64 (n = min, dec)",	FALSE, -9223372036854775807, "-9223372036854775807",       "0123456789");
	print_test_strbase_to_s64("strbase_to_s64 (n = max, dec)",	FALSE,  9223372036854775807,  "9223372036854775807",       "0123456789");
	print_test_strbase_to_s64("strbase_to_s64 (n = min, hex)",	FALSE, -9223372036854775807,    "-7FFFFFFFFFFFFFFF", "0123456789ABCDEF");
	print_test_strbase_to_s64("strbase_to_s64 (n = max, hex)",	FALSE,  9223372036854775807,     "7FFFFFFFFFFFFFFF", "0123456789ABCDEF");
	print_test_strbase_to_s64("strbase_to_s64 (n = min, bin)",	FALSE, -9223372036854775807,"-111111111111111111111111111111111111111111111111111111111111111","01");
	print_test_strbase_to_s64("strbase_to_s64 (n = max, bin)",	FALSE,  9223372036854775807, "111111111111111111111111111111111111111111111111111111111111111","01");
	print_test_strbase_to_s64("strbase_to_s64 (empty base)  ",	FALSE,                    0,                   "01",                 "");
	print_test_strbase_to_s64("strbase_to_s64 (empty number)",	FALSE,                    0,                     "",               "01");
	print_test_strbase_to_s64("strbase_to_s64 (both empty)  ",	FALSE,                    0,                     "",                 "");
	print_test_strbase_to_s64("strbase_to_s64 (null base)   ",	SEGV,                     0,                   "01",               NULL);
	print_test_strbase_to_s64("strbase_to_s64 (null number) ",	SEGV,                     0,                   NULL,               "01");
	print_test_strbase_to_s64("strbase_to_s64 (both null)   ",	SEGV,                     0,                   NULL,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_s64("strbase_to_s64 (n < min)     ",	FALSE,   -9223372036854775808,  "-9223372036854775808",    "0123456789");
		print_test_strbase_to_s64("strbase_to_s64 (n > max)     ",	FALSE,    9223372036854775808,   "9223372036854775808",    "0123456789");
#ifndef __clang__
		print_test_strbase_to_s64("strbase_to_s64 (n < maxdigit)",	FALSE, -999999999999999999999, "999999999999999999999",    "0123456789");
		print_test_strbase_to_s64("strbase_to_s64 (n > maxdigit)",	FALSE,  999999999999999999999,"-999999999999999999999",    "0123456789");
#endif
	}
}
#endif



#ifdef			c_strbase_to_u8
void	print_test_strbase_to_u8(char const* test_name, int can_segfault,
		t_u8 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_u8, strbase_to_u8, number, base)
	print_test_u8(test_name, "_strbase_to_u8", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_u8(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            1,          "1",               "01");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,          "1",               "+1");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,          "m",                "m");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,         "mm",                "m");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,        "mmm",                "m");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           42,     "101010",               "01");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,     "101012",               "01");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,          "m",              "mom");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,          "o",              "mom");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,          "0",              "0az");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,          111,        "aaa",       "_abcdefghi");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           15,          "F", "0123456789ABCDEF");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           63,       "rdmm",              "mdr");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,          100,      "|*_*|",              "*|_");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           13,       ".._.",               "_.");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           42,         "2A", "0123456789ABCDEF");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,           42,         "42",       "0123456789");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,         "42",       "012345678-");
	print_test_strbase_to_u8("strbase_to_u8               ",	FALSE,            0,         "42",       "012345678+");
	print_test_strbase_to_u8("strbase_to_u8 (n = min, dec)",	FALSE,            0,          "0",       "0123456789");
	print_test_strbase_to_u8("strbase_to_u8 (n = max, dec)",	FALSE,          255,        "255",       "0123456789");
	print_test_strbase_to_u8("strbase_to_u8 (n = min, hex)",	FALSE,            0,          "0", "0123456789ABCDEF");
	print_test_strbase_to_u8("strbase_to_u8 (n = max, hex)",	FALSE,          255,         "FF", "0123456789ABCDEF");
	print_test_strbase_to_u8("strbase_to_u8 (n = min, bin)",	FALSE,            0,          "0",               "01");
	print_test_strbase_to_u8("strbase_to_u8 (n = max, bin)",	FALSE,          255,   "11111111",               "01");
	print_test_strbase_to_u8("strbase_to_u8 (empty base)  ",	FALSE,            0,         "01",                 "");
	print_test_strbase_to_u8("strbase_to_u8 (empty number)",	FALSE,            0,           "",               "01");
	print_test_strbase_to_u8("strbase_to_u8 (both empty)  ",	FALSE,            0,           "",                 "");
	print_test_strbase_to_u8("strbase_to_u8 (null base)   ",	SEGV,             0,         "01",               NULL);
	print_test_strbase_to_u8("strbase_to_u8 (null number) ",	SEGV,             0,         NULL,               "01");
	print_test_strbase_to_u8("strbase_to_u8 (both null)   ",	SEGV,             0,         NULL,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_u8("strbase_to_u8 (n < min)     ",	FALSE,       -1,         "-1",       "0123456789");
		print_test_strbase_to_u8("strbase_to_u8 (n > max)     ",	FALSE,      256,        "256",       "0123456789");
		print_test_strbase_to_u8("strbase_to_u8 (n < maxdigit)",	FALSE,   -99999,     "-99999",       "0123456789");
		print_test_strbase_to_u8("strbase_to_u8 (n > maxdigit)",	FALSE,    99999,      "99999",       "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_u16
void	print_test_strbase_to_u16(char const* test_name, int can_segfault,
		t_u16 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_u16, strbase_to_u16, number, base)
	print_test_u16(test_name, "_strbase_to_u16", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_u16(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV| EXPECTING | TEST ARGS
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         1,          "1",                "01");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,          "1",                "+1");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,          "m",                 "m");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,         "mm",                 "m");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,        "mmm",                 "m");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,        42,     "101010",                "01");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,     "101012",                "01");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,          "m",               "mom");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,          "o",               "mom");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,          "0",               "0az");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,       111,        "aaa",        "_abcdefghi");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,        15,          "F",  "0123456789ABCDEF");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,        63,       "rdmm",               "mdr");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,       100,      "|*_*|",               "*|_");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,        13,       ".._.",                "_.");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,     12345,      "12345",        "0123456789");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,      "12345",        "012345678-");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,      "12345",        "012345678+");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,         0,        "999",        "0123456709");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,       999,        "999",        "0123456789");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,     10007,      "c===3",        "=cbadef389");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,      1234,       "swag",        "0swag56789");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,      1000,        "3e8",  "0123456789abcdef");
	print_test_strbase_to_u16("strbase_to_u16               ",	FALSE,        42,         "2A",  "0123456789ABCDEF");
	print_test_strbase_to_u16("strbase_to_u16 (n = min, dec)",	FALSE,         0,          "0",        "0123456789");
	print_test_strbase_to_u16("strbase_to_u16 (n = max, dec)",	FALSE,     65535,      "65535",        "0123456789");
	print_test_strbase_to_u16("strbase_to_u16 (n = min, hex)",	FALSE,         0,          "0",  "0123456789ABCDEF");
	print_test_strbase_to_u16("strbase_to_u16 (n = max, hex)",	FALSE,     65535,       "FFFF",  "0123456789ABCDEF");
	print_test_strbase_to_u16("strbase_to_u16 (n = min, bin)",	FALSE,         0,          "0",                "01");
	print_test_strbase_to_u16("strbase_to_u16 (n = max, bin)",	FALSE,     65535,     "1111111111111111",      "01");
	print_test_strbase_to_u16("strbase_to_u16 (empty base)  ",	FALSE,         0,         "01",                  "");
	print_test_strbase_to_u16("strbase_to_u16 (empty number)",	FALSE,         0,           "",                "01");
	print_test_strbase_to_u16("strbase_to_u16 (both empty)  ",	FALSE,         0,           "",                  "");
	print_test_strbase_to_u16("strbase_to_u16 (null base)   ",	SEGV,          0,         "01",                NULL);
	print_test_strbase_to_u16("strbase_to_u16 (null number) ",	SEGV,          0,         NULL,                "01");
	print_test_strbase_to_u16("strbase_to_u16 (both null)   ",	SEGV,          0,         NULL,                NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_u16("strbase_to_u16 (n < min)     ",	FALSE,         -1,         "-1",   "0123456789");
		print_test_strbase_to_u16("strbase_to_u16 (n > max)     ",	FALSE,      65536,      "65536",   "0123456789");
		print_test_strbase_to_u16("strbase_to_u16 (n < maxdigit)",	FALSE,   -9999999,   "-9999999",   "0123456789");
		print_test_strbase_to_u16("strbase_to_u16 (n > maxdigit)",	FALSE,    9999999,    "9999999",   "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_u32
void	print_test_strbase_to_u32(char const* test_name, int can_segfault,
		t_u32 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_u32, strbase_to_u32, number, base)
	print_test_u32(test_name, "_strbase_to_u32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_u32(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING    | TEST ARGS
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              1,                      "1",               "01");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                      "1",               "+1");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                      "m",                "m");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                     "mm",                "m");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                    "mmm",                "m");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,             42,                 "101010",               "01");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                 "101012",               "01");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                      "m",              "mom");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                      "o",              "mom");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,             15,                      "F", "0123456789ABCDEF");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,             63,                   "rdmm",              "mdr");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,            100,                  "|*_*|",              "*|_");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,             13,                   ".._.",               "_.");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,             42,                     "2A", "0123456789ABCDEF");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                      "0",              "0az");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,            111,                    "aaa",       "_abcdefghi");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,          12345,                  "12345",       "0123456789");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                  "12345",       "012345678-");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                  "12345",       "012345678+");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,              0,                    "999",       "0123456739");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,            999,                    "999",       "0123456789");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,          10007,                  "c===3",       "=cbadef389");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,           1234,                   "swag",       "0swag56789");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,           1000,                    "3e8", "0123456789abcdef");
	print_test_strbase_to_u32("strbase_to_u32               ",	FALSE,        +987123,                 "*xurin",       "grincheux*");
	print_test_strbase_to_u32("strbase_to_u32 (n = min, dec)",	FALSE,              0,                      "0",       "0123456789");
	print_test_strbase_to_u32("strbase_to_u32 (n = max, dec)",	FALSE,     4294967295,             "4294967295",       "0123456789");
	print_test_strbase_to_u32("strbase_to_u32 (n = min, hex)",	FALSE,              0,                      "0", "0123456789ABCDEF");
	print_test_strbase_to_u32("strbase_to_u32 (n = max, hex)",	FALSE,     4294967295,               "FFFFFFFF", "0123456789ABCDEF");
	print_test_strbase_to_u32("strbase_to_u32 (n = min, bin)",	FALSE,              0,                      "0",               "01");
	print_test_strbase_to_u32("strbase_to_u32 (n = max, bin)",	FALSE,     4294967295,      "11111111111111111111111111111111","01");
	print_test_strbase_to_u32("strbase_to_u32 (empty base)  ",	FALSE,              0,                     "01",                 "");
	print_test_strbase_to_u32("strbase_to_u32 (empty number)",	FALSE,              0,                       "",               "01");
	print_test_strbase_to_u32("strbase_to_u32 (both empty)  ",	FALSE,              0,                       "",                 "");
	print_test_strbase_to_u32("strbase_to_u32 (null base)   ",	SEGV,               0,                     "01",               NULL);
	print_test_strbase_to_u32("strbase_to_u32 (null number) ",	SEGV,               0,                     NULL,               "01");
	print_test_strbase_to_u32("strbase_to_u32 (both null)   ",	SEGV,               0,                     NULL,               NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_u32("strbase_to_u32 (n < min)     ",	FALSE,                -1,              "-1",       "0123456789");
		print_test_strbase_to_u32("strbase_to_u32 (n > max)     ",	FALSE,        4294967296,      "4294967296",       "0123456789");
		print_test_strbase_to_u32("strbase_to_u32 (n < maxdigit)",	FALSE,     -999999999999,   "-999999999999",       "0123456789");
		print_test_strbase_to_u32("strbase_to_u32 (n > maxdigit)",	FALSE,      999999999999,    "999999999999",       "0123456789");
	}
}
#endif



#ifdef			c_strbase_to_u64
void	print_test_strbase_to_u64(char const* test_name, int can_segfault,
		t_u64 expecting,
		char const* number,
		char const* base)
{
	TEST_PERFORM_RESULT_TYPE(t_u64, strbase_to_u64, number, base)
	print_test_u64(test_name, "_strbase_to_u64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);
}
void	test_strbase_to_u64(void)
{
//	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|      EXPECTING       | TEST ARGS
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      1,                   "1",                "01");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "1",                "+1");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "m",                 "m");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "m",                 "m");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                  "mm",                 "m");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                 "mmm",                 "m");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                     42,              "101010",                "01");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,              "101012",                "01");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "m",               "mom");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "o",               "mom");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                     42,                  "2A",  "0123456789ABCDEF");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                   "0",               "0az");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                    111,                 "aaa",        "_abcdefghi");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                     15,                   "F",  "0123456789ABCDEF");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                     63,                "rdmm",               "mdr");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                    100,               "|*_*|",               "*|_");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                     13,                ".._.",                "_.");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                  12345,               "12345",        "0123456789");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,               "12345",        "012345678-");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,               "12345",        "012345678+");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                      0,                 "999",        "0123456389");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                    999,                 "999",        "0123456789");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                  10007,               "c===3",        "=cbadef389");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                   1234,                "swag",        "0swag56789");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                   1000,                 "3e8",  "0123456789abcdef");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,                +987123,              "*xurin",        "grincheux*");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,             2147483647,            "7FFFFFFF",  "0123456789ABCDEF");
	print_test_strbase_to_u64("strbase_to_u64               ",	FALSE,             2147483648,          "2147483648",        "0123456789");
	print_test_strbase_to_u64("strbase_to_u64 (n = min, dec)",	FALSE,                      0,                   "0",        "0123456789");
	print_test_strbase_to_u64("strbase_to_u64 (n = max, dec)",	FALSE, 18446744073709551615UL,"18446744073709551615",        "0123456789");
	print_test_strbase_to_u64("strbase_to_u64 (n = min, hex)",	FALSE,                      0,                   "0",  "0123456789ABCDEF");
	print_test_strbase_to_u64("strbase_to_u64 (n = max, hex)",	FALSE, 18446744073709551615UL,    "FFFFFFFFFFFFFFFF",  "0123456789ABCDEF");
	print_test_strbase_to_u64("strbase_to_u64 (n = min, bin)",	FALSE,                      0,                   "0",                "01");
	print_test_strbase_to_u64("strbase_to_u64 (n = max, bin)",	FALSE, 18446744073709551615UL, "1111111111111111111111111111111111111111111111111111111111111111","01");
	print_test_strbase_to_u64("strbase_to_u64 (empty base)  ",	FALSE,                      0,                  "01",                  "");
	print_test_strbase_to_u64("strbase_to_u64 (empty number)",	FALSE,                      0,                    "",                "01");
	print_test_strbase_to_u64("strbase_to_u64 (both empty)  ",	FALSE,                      0,                    "",                  "");
	print_test_strbase_to_u64("strbase_to_u64 (null base)   ",	SEGV,                       0,                  "01",                NULL);
	print_test_strbase_to_u64("strbase_to_u64 (null number) ",	SEGV,                       0,                  NULL,                "01");
	print_test_strbase_to_u64("strbase_to_u64 (both null)   ",	SEGV,                       0,                  NULL,                NULL);
	if (g_test.flags.test_overflow)
	{
		print_test_strbase_to_u64("strbase_to_u64 (n < min)     ",	FALSE,                       -1,                     "-1",  "0123456789");
#ifndef __clang__
		print_test_strbase_to_u64("strbase_to_u64 (n > max)     ",	FALSE,   18446744073709551616UL,   "18446744073709551616",  "0123456789");
		print_test_strbase_to_u64("strbase_to_u64 (n < maxdigit)",	FALSE, -999999999999999999999LL, "-999999999999999999999",  "0123456789");
		print_test_strbase_to_u64("strbase_to_u64 (n > maxdigit)",	FALSE,  999999999999999999999LL,  "999999999999999999999",  "0123456789");
#endif
	}
}
#endif





#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



int		testsuite_int(void)
{
	print_suite_title("int");

	print_nonstd();

#ifdef c_s8_to_str
	test_s8_to_str();
#endif
#ifdef c_s16_to_str
	test_s16_to_str();
#endif
#ifdef c_s32_to_str
	test_s32_to_str();
#endif
#ifdef c_s64_to_str
	test_s64_to_str();
#endif

#ifdef c_u8_to_str
	test_u8_to_str();
#endif
#ifdef c_u16_to_str
	test_u16_to_str();
#endif
#ifdef c_u32_to_str
	test_u32_to_str();
#endif
#ifdef c_u64_to_str
	test_u64_to_str();
#endif


#ifdef c_u8_to_strhex
	test_u8_to_strhex();
#endif
#ifdef c_u16_to_strhex
	test_u16_to_strhex();
#endif
#ifdef c_u32_to_strhex
	test_u32_to_strhex();
#endif
#ifdef c_u64_to_strhex
	test_u64_to_strhex();
#endif


#ifdef c_s8_to_strbase
	test_s8_to_strbase();
#endif
#ifdef c_s16_to_strbase
	test_s16_to_strbase();
#endif
#ifdef c_s32_to_strbase
	test_s32_to_strbase();
#endif
#ifdef c_s64_to_strbase
	test_s64_to_strbase();
#endif

#ifdef c_u8_to_strbase
	test_u8_to_strbase();
#endif
#ifdef c_u16_to_strbase
	test_u16_to_strbase();
#endif
#ifdef c_u32_to_strbase
	test_u32_to_strbase();
#endif
#ifdef c_u64_to_strbase
	test_u64_to_strbase();
#endif



#ifdef c_str_to_s8
	test_str_to_s8();
#endif
#ifdef c_str_to_s16
	test_str_to_s16();
#endif
#ifdef c_str_to_s32
	test_str_to_s32();
#endif
#ifdef c_str_to_s64
	test_str_to_s64();
#endif

#ifdef c_str_to_u8
	test_str_to_u8();
#endif
#ifdef c_str_to_u16
	test_str_to_u16();
#endif
#ifdef c_str_to_u32
	test_str_to_u32();
#endif
#ifdef c_str_to_u64
	test_str_to_u64();
#endif


#ifdef c_strhex_to_u8
//	test_strhex_to_u8();
#endif
#ifdef c_strhex_to_u16
//	test_strhex_to_u16();
#endif
#ifdef c_strhex_to_u32
//	test_strhex_to_u32();
#endif
#ifdef c_strhex_to_u64
//	test_strhex_to_u64();
#endif


#ifdef c_strbase_to_s8
	test_strbase_to_s8();
#endif
#ifdef c_strbase_to_s16
	test_strbase_to_s16();
#endif
#ifdef c_strbase_to_s32
	test_strbase_to_s32();
#endif
#ifdef c_strbase_to_s64
	test_strbase_to_s64();
#endif

#ifdef c_strbase_to_u8
	test_strbase_to_u8();
#endif
#ifdef c_strbase_to_u16
	test_strbase_to_u16();
#endif
#ifdef c_strbase_to_u32
	test_strbase_to_u32();
#endif
#ifdef c_strbase_to_u64
	test_strbase_to_u64();
#endif

	return (OK);
}
