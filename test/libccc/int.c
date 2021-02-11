
#include "libccc.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Woverflow"
// "-Wimplicitly-unsigned-literal"
// "-Wconstant-conversion"

/*
** ************************************************************************** *|
**                        Convert Integers to Strings                         *|
** ************************************************************************** *|
*/

#define DEFINETEST_UINT_TO_STR(TYPE) \
void	print_test_##TYPE##_to_str(char const* test_name, int can_segfault,					\
		char const* expecting,																\
		t_u64 number)																		\
{																							\
	TEST_PERFORM_RESULT(TYPE##_to_str, number)												\
	print_test_str(test_name, "_"#TYPE"_to_str", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);															\
	TEST_PRINT_ARGS(FORMAT_UINT, number)													\
}																							\
void	test_##TYPE##_to_str(void)																							\
{																															\
/*	| TEST FUNCTION            | TEST NAME                       |CAN SEGV| EXPECTING              | TEST ARGS			*/	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = min)       ",	FALSE,                      "0", 0                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "1", 1                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "9", 9                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "10", 10                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "11", 11                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "42", 42                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "99", 99                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "100", 100                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "111", 111                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "123", 123                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "127", 127                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "128", 128                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "129", 129                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8max)      ",	FALSE,                    "255", 255                   );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8min)      ",	FALSE,                     "-1", -1                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8max)      ",	FALSE,                    "256", 256                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8maxdigit) ",	FALSE,                  "99999", 99999                 );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8maxdigit) ",	FALSE,                 "-99999",-99999                 );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 16)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "777", 777                   );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "7777", 7777                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                  "10000", 10000                 );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16max)     ",	FALSE,                  "65535", 65535                 );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16min)     ",	FALSE,                     "-1", -1                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16max)     ",	FALSE,                  "65536", 65536                 );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16maxdigit)",	FALSE,                "9999999", 9999999               );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16maxdigit)",	FALSE,               "-9999999",-9999999               );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 32)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,              "123456789", 123456789             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,              "555555555", 555555555             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,              "987654321", 987654321             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32max)     ",	FALSE,             "4294967295", 4294967295            );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32min)     ",	FALSE,                     "-1", -1                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32max)     ",	FALSE,             "4294967296", 4294967296            );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32maxdigit)",	FALSE,           "999999999999", 999999999999          );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32maxdigit)",	FALSE,          "-999999999999",-999999999999          );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 64)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,           "999999999999", 999999999999          );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,        "999999999999000", 999999999999000       );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,     "999999999999000999", 999999999999000999    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL);	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64min)     ",	FALSE,                     "-1", -1                    );	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL); */\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);*/\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);*/\
	}																														\
	}}}																														\
}

#ifndef _u8_to_str
void test_u8_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(u8)
#endif

#ifndef _u16_to_str
void test_u16_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(u16)
#endif

#ifndef _u32_to_str
void test_u32_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(u32)
#endif

#ifndef _u64_to_str
void test_u64_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(u64)
#endif

#ifdef __int128
#ifndef _u128_to_str
void test_u128_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(u128)
#endif
#endif

#ifndef _uint_to_str
void test_uint_to_str(void)	{}
#else
DEFINETEST_UINT_TO_STR(uint)
#endif



#define DEFINETEST_SINT_TO_STR(TYPE) \
void	print_test_##TYPE##_to_str(char const* test_name, int can_segfault,					\
		char const* expecting,																\
		t_##TYPE number)																	\
{																							\
	TEST_PERFORM_RESULT(TYPE##_to_str, number)											\
	print_test_str(test_name, "_s"#TYPE"_to_str", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);															\
	TEST_PRINT_ARGS(FORMAT_SINT, number)													\
}																							\
void	test_##TYPE##_to_str(void)																							\
{																															\
/*	| TEST FUNCTION      | TEST NAME                         |CAN SEGV| EXPECTING              | TEST ARGS				*/	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "1", 1                      );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "-1",-1                      );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "10", 10                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "-10",-10                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                      "0", 0                      );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                     "42", 42                     );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "111", 111                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-111",-111                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8min)      ",	FALSE,                   "-128",-128                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 8max)      ",	FALSE,                    "127", 127                    );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8min)      ",	FALSE,                   "-129",-129                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8max)      ",	FALSE,                    "128", 128                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 8maxdigit) ",	FALSE,                  "99999", 99999                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 8maxdigit) ",	FALSE,                 "-99999",-99999                  );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 16)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                    "777", 777                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                   "-666",-666                    );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                 "-10000",-10000                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,                  "10000",+10000                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16min)     ",	FALSE,                 "-32768",-32768                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 16max)     ",	FALSE,                  "32767", 32767                  );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16min)     ",	FALSE,                 "-32769",-32769                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16max)     ",	FALSE,                  "32768", 32768                  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 16maxdigit)",	FALSE,                "9999999", 9999999                );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 16maxdigit)",	FALSE,               "-9999999",-9999999                );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 32)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-123456789",-123456789              );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,              "123456789", 123456789              );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "-987654321",-987654321              );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,              "987654321", 987654321              );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32min)     ",	FALSE,            "-2147483648",-2147483648             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 32max)     ",	FALSE,             "2147483647", 2147483647             );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32min)     ",	FALSE,            "-2147483649",-2147483649             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32max)     ",	FALSE,             "2147483648", 2147483648             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 32maxdigit)",	FALSE,           "999999999999", 999999999999           );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 32maxdigit)",	FALSE,          "-999999999999",-999999999999           );	\
	}																														\
	if (sizeof(t_##TYPE) * 8 >= 64)																							\
	{																														\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,             "2147483648", 2147483648             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,            "-2147483649",-2147483649             );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,           "999999999999", 999999999999           );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str                 ",	FALSE,          "-999999999999",-999999999999           );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808LL  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n = 64max)     ",	FALSE,    "9223372036854775807", 9223372036854775807LL  );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809LL  );	\
	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64max)     ",	FALSE,    "9223372036854775808", 9223372036854775808LL  );	\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n > 64maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999LL);*/\
/*	print_test_##TYPE##_to_str(#TYPE"_to_str (n < 64maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999LL);*/\
	}																														\
	}}}																														\
}

#ifndef _s8_to_str
void test_s8_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(s8)
#endif

#ifndef _s16_to_str
void test_s16_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(s16)
#endif

#ifndef _s32_to_str
void test_s32_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(s32)
#endif

#ifndef _s64_to_str
void test_s64_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(s64)
#endif

#ifdef __int128
#ifndef _s128_to_str
void test_s128_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(s128)
#endif
#endif

#ifndef _sint_to_str
void test_sint_to_str(void)	{}
#else
DEFINETEST_SINT_TO_STR(sint)
#endif



/*
** ************************************************************************** *|
**                       Convert to Hexadecimal String                        *|
** ************************************************************************** *|
*/

#define DEFINETEST_UINT_TO_STRHEX(TYPE) \
void	print_test_##TYPE##_to_strhex(char const* test_name, int can_segfault,					\
		char const* expecting,																	\
		t_u64 number)																			\
{																								\
	TEST_PERFORM_RESULT(TYPE##_to_strhex, number)												\
	print_test_str(test_name, "_"#TYPE"_to_strhex", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS(FORMAT_UINT, number)														\
}																								\
void	test_##TYPE##_to_strhex(void)																								\
{																																	\
/*	| TEST FUNCTION              | TEST NAME                         |CAN SEGV| EXPECTING              | TEST ARGS				*/	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n = min)       ",	FALSE,                      "0", 0                     );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                      "1", 1                     );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                      "2", 2                     );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                      "3", 3                     );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                      "F", 15                    );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                     "10", 16                    );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                     "2A", 42                    );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                     "6F", 111                   );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n = 8max)      ",	FALSE,                     "FF", 255                   );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 8min)      ",	FALSE,                 "-1", -1                    );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 8max)      ",	FALSE,                "100", 256                   );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 8maxdigit) ",	FALSE,              "1869F", 99999                 );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 8maxdigit) ",	FALSE,             "-1869F",-99999                 );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 16)																									\
	{																																\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                    "30A", 778                   );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                   "2710", 10000                 );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n = 16max)     ",	FALSE,                   "FFFF", 65535                 );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 16min)     ",	FALSE,                 "-1", -1                    );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 16max)     ",	FALSE,              "10000", 65536                 );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 16maxdigit)",	FALSE,             "98967F", 9999999               );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 16maxdigit)",	FALSE,            "-98967F",-9999999               );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 32)																									\
	{																																\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,                "75BCD15", 123456789             );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,               "3ADE68B1", 987654321             );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n = 32max)     ",	FALSE,               "FFFFFFFF", 4294967295            );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 32min)     ",	FALSE,                 "-1", -1                    );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 32max)     ",	FALSE,          "100000000", 4294967296            );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 32maxdigit)",	FALSE,         "E8D4A50FFF", 999999999999          );	\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 32maxdigit)",	FALSE,         "E8D4A51000", 1000000000000         );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 64)																									\
	{																																\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,             "E8D4A50FFF", 999999999999L         );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex                 ",	FALSE,             "E8D4A51000", 1000000000000         );	\
	print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n = 64max)     ",	FALSE,       "FFFFFFFFFFFFFFFF", 18446744073709551615UL);	\
	if (g_test.flags.test_overflow) {																								\
		print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 64min)     ",	FALSE,                 "-1", -1                    );	\
		/*print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 64max)     ",	FALSE,  "10000000000000000", 18446744073709551616UL);*/	\
		/*print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n > 64maxdigit)",	FALSE,                  "0", 999999999999999999999UL);*/\
		/*print_test_##TYPE##_to_strhex(#TYPE"_to_strhex (n < 64maxdigit)",	FALSE,                  "0",-999999999999999999999UL);*/\
	}																																\
	}}}																																\
}

#ifndef c_u8_to_strhex
void test_u8_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(u8)
#endif

#ifndef c_u16_to_strhex
void test_u16_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(u16)
#endif

#ifndef c_u32_to_strhex
void test_u32_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(u32)
#endif

#ifndef c_u64_to_strhex
void test_u64_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(u64)
#endif

#ifdef __int128
#ifndef c_u128_to_strhex
void test_u128_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(u128)
#endif
#endif

#ifndef c_uint_to_strhex
void test_uint_to_strhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(uint)
#endif



/*
** ************************************************************************** *|
**                       Convert Integer to Base String                       *|
** ************************************************************************** *|
*/

#define DEFINETEST_SINT_TO_STRBASE(TYPE) \
void	print_test_##TYPE##_to_strbase(char const* test_name, int can_segfault,					\
		char const* expecting,																	\
		t_##TYPE number,																		\
		char const* base)																		\
{																								\
	TEST_PERFORM_RESULT(TYPE##_to_strbase, number, base)										\
	print_test_str(test_name, "_s"#TYPE"_to_strbase", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS("base='%s', n="FORMAT_SINT, base, number);									\
}																								\
void	test_##TYPE##_to_strbase(void)																													\
{																																						\
/*	| TEST FUNCTION                | TEST NAME                       |CAN SEGV| EXPECTING                | TEST ARGS								*/	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                         "1",                   1,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,                   1,               "+1");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,                   0,                "m");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,                   1,                "m");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                    "101010",                  42,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,                   0,              "mom");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                         "0",                   0,              "0az");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "aaa",                 111,       "_abcdefghi");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "-aaa",                -111,       "_abcdefghi");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        "-F",                 -15, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "rdmm",                  63,              "mdr");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "|*_*|",                 100,              "*|_");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      ".._.",                  13,               "_.");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        "42",                  42,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,               12345,       "012345678-");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,               12345,       "012345678+");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        NULL,                 999,       "01+3456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8min, dec) ",	FALSE,                      "-128",                -128,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, dec) ",	FALSE,                       "127",                 127,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8min, hex) ",	FALSE,                       "-80",                -128, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, hex) ",	FALSE,                        "7F",                 127, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8min, oct) ",	FALSE,                      "-200",                -128,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, oct) ",	FALSE,                       "177",                 127,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8min, bin) ",	FALSE,                 "-10000000",                -128,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, bin) ",	FALSE,                   "1111111",                 127,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 8min)      ",	FALSE,                  "-129",                -129,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 8max)      ",	FALSE,                   "128",                 128,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 8maxdigit) ",	FALSE,                    NULL,               99999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 8maxdigit) ",	FALSE,                    NULL,              -99999,               "01");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 16)																														\
	{																																					\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "12345",               12345,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "12345",               12345,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "c===3",               10007,       "=cbadef389");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "swag",                1234,       "0swag56789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "-3e8",               -1000, "0123456789abcdef");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16min, dec)",	FALSE,                    "-32768",              -32768,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, dec)",	FALSE,                     "32767",               32767,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16min, hex)",	FALSE,                     "-8000",              -32768, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, hex)",	FALSE,                      "7FFF",               32767, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16min, oct)",	FALSE,                   "-100000",              -32768,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, oct)",	FALSE,                     "77777",               32767,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16min, bin)",	FALSE,         "-1000000000000000",              -32768,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, bin)",	FALSE,           "111111111111111",               32767,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 16min)     ",	FALSE,                "-32769",              -32769,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 16max)     ",	FALSE,                 "32768",               32768,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 16maxdigit)",	FALSE,                    NULL,             9999999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 16maxdigit)",	FALSE,                    NULL,            -9999999,               "01");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 32)																														\
	{																																					\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                    "*xurin",             +987123,       "grincheux*");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                 "abcdefghi",           123456789,       " abcdefghi");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32min, dec)",	FALSE,               "-2147483648",         -2147483648,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, dec)",	FALSE,                "2147483647",          2147483647,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32min, hex)",	FALSE,                 "-80000000",         -2147483648, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, hex)",	FALSE,                  "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32min, oct)",	FALSE,              "-20000000000",         -2147483648,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, oct)",	FALSE,               "17777777777",          2147483647,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32min, bin)",	FALSE,"-10000000000000000000000000000000",  -2147483648,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, bin)",	FALSE,  "1111111111111111111111111111111",   2147483647,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 32min)     ",	FALSE,           "-2147483649",         -2147483649,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 32max)     ",	FALSE,            "2147483648",          2147483648,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 32maxdigit)",	FALSE,                    NULL,        999999999999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 32maxdigit)",	FALSE,                    NULL,       -999999999999,               "01");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 64)																														\
	{																																					\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                  "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,               "-2147483648",         -2147483648,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64min, dec)",	FALSE,      "-9223372036854775808",-9223372036854775808,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, dec)",	FALSE,       "9223372036854775807", 9223372036854775807,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64min, hex)",	FALSE,         "-8000000000000000",-9223372036854775808, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, hex)",	FALSE,          "7FFFFFFFFFFFFFFF", 9223372036854775807, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64min, oct)",	FALSE,   "-1000000000000000000000",-9223372036854775808,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, oct)",	FALSE,     "777777777777777777777", 9223372036854775807,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64min, bin)",	FALSE,"-1000000000000000000000000000000000000000000000000000000000000000",-9223372036854775808,"01");\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, bin)",	FALSE,  "111111111111111111111111111111111111111111111111111111111111111", 9223372036854775807,"01");\
	if (g_test.flags.test_overflow) {																													\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 64min)     ",	FALSE,  "-9223372036854775808",-9223372036854775808,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 64max)     ",	FALSE,   "9223372036854775808", 9223372036854775808,       "0123456789");	\
	/*	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 64maxdigit)",	FALSE,                  NULL, 999999999999999999999,               "01");*/	\
	/*	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 64maxdigit)",	FALSE,                  NULL,-999999999999999999999,               "01");*/	\
	}																																					\
	}}}																																					\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (empty base)    ",	FALSE,                        NULL,                  42,                 "");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (null base)     ",	TRUE,                       segstr,                  42,               NULL);	\
}

#ifndef c_s8_to_strbase
void test_s8_to_strbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(s8)
#endif

#ifndef c_s16_to_strbase
void test_s16_to_strbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(s16)
#endif

#ifndef c_s32_to_strbase
void test_s32_to_strbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(s32)
#endif

#ifndef c_s64_to_strbase
void test_s64_to_strbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(s64)
#endif

#ifdef __int128
#ifndef c_s128_to_strbase
void test_s128_to_strbase(void)	{}
#else
DEFINETEST_S128_TO_STRBASE(s128)
#endif

#endif
#ifndef c_sint_to_strbase
void test_sint_to_strbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(sint)
#endif



#define DEFINETEST_UINT_TO_STRBASE(TYPE) \
void	print_test_##TYPE##_to_strbase(char const* test_name, int can_segfault,				\
		char const* expecting,																	\
		t_u32 number,																			\
		char const* base)																		\
{																								\
	TEST_PERFORM_RESULT(TYPE##_to_strbase, number, base)										\
	print_test_str(test_name, "_"#TYPE"_to_strbase", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS("base='%s', n=%d", base, number);											\
}																								\
void	test_##TYPE##_to_strbase(void)																													\
{																																						\
/*	| TEST FUNCTION          | TEST NAME                                 |CAN SEGV|  EXPECTING              | TEST ARGS								*/	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = min, dec)  ",	FALSE,                       "0",                   0,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = min, hex)  ",	FALSE,                       "0",                   0, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = min, oct)  ",	FALSE,                       "0",                   0,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = min, bin)  ",	FALSE,                       "0",                   0,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "1",                   1,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "1",                   1,               "+1");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      NULL,                   0,                "m");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      NULL,                   1,                "m");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                  "101010",                  42,               "01");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      NULL,                   0,              "mom");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "F",                  15, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "0",                   0,              "0az");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "aaa",                 111,       "_abcdefghi");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                    "rdmm",                  63,              "mdr");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                   "|*_*|",                 100,              "*|_");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                    ".._.",                  13,               "_.");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "42",                  42,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "42",                  42,       "012345678-");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "42",                  42,       "012345678+");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                       "0",                   0,              "0az");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "aaa",                 111,       "_abcdefghi");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, dec) ",	FALSE,                     "255",                 255,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, hex) ",	FALSE,                      "FF",                 255, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, oct) ",	FALSE,                     "377",                 255,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 8max, bin) ",	FALSE,                "11111111",                 255,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 8min)      ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 8max)      ",	FALSE,                 "256",                 256,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 8maxdigit) ",	FALSE,                  NULL,               99999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 8maxdigit) ",	FALSE,                  NULL,              -99999,               "01");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 16)																													\
	{																																				\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                   "12345",               12345,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                   "12345",               12345,       "012345678-");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                   "12345",               12345,       "012345678+");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      NULL,                 999,       "0123456739");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                   "c===3",               10007,       "=cbadef389");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                    "swag",                1234,       "0swag56789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "3e8",                1000, "0123456789abcdef");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                     "3E8",                1000, "0123456789abcdEf");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, dec)",	FALSE,                   "65535",               65535,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, hex)",	FALSE,                    "FFFF",               65535, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, oct)",	FALSE,                  "177777",               65535,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 16max, bin)",	FALSE,        "1111111111111111",               65535,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 16min)     ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 16max)     ",	FALSE,               "65536",               65536,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 16maxdigit)",	FALSE,                  NULL,             9999999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 16maxdigit)",	FALSE,                  NULL,            -9999999,               "01");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 32)																													\
	{																																				\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                  "*xurin",             +987123,       "grincheux*");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,                "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase                 ",	FALSE,              "2147483648",          2147483648,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, dec)",	FALSE,              "4294967295",          4294967295,       "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, hex)",	FALSE,                "FFFFFFFF",          4294967295, "0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, oct)",	FALSE,             "37777777777",          4294967295,         "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 32max, bin)",	FALSE, "11111111111111111111111111111111", 4294967295,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 32min)     ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 32max)     ",	FALSE,          "4294967296",          4294967296,       "0123456789");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 32maxdigit)",	FALSE,                  NULL,        999999999999,               "01");	\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 32maxdigit)",	FALSE,                  NULL,       -999999999999,               "01");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 64)																													\
	{																																				\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, dec)",	FALSE,  "18446744073709551615",18446744073709551615llu,      "0123456789");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, hex)",	FALSE,      "FFFFFFFFFFFFFFFF",18446744073709551615llu,"0123456789ABCDEF");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, oct)",	FALSE,"1777777777777777777777",18446744073709551615llu,        "01234567");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n = 64max, bin)",	FALSE,"1111111111111111111111111111111111111111111111111111111111111111", 18446744073709551615UL,"01");\
	if (g_test.flags.test_overflow) {																												\
		print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 64min)     ",	FALSE,                  "-1",                      -1,   "0123456789");	\
	/*	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 64max)     ",	FALSE,"18446744073709551616",  18446744073709551616UL,   "0123456789");*/\
	/*	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n > 64maxdigit)",	FALSE,                  NULL, 999999999999999999999LL,           "01");*/\
	/*	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (n < 64maxdigit)",	FALSE,                  NULL,-999999999999999999999LL,           "01");*/\
	}																																				\
	}}}																																				\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");	\
	print_test_##TYPE##_to_strbase(#TYPE"_to_strbase (null base)   ",	TRUE,                     segstr,                  42,               NULL);	\
}

#ifndef c_u8_to_strbase
void test_u8_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(u8)
#endif

#ifndef c_u16_to_strbase
void test_u16_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(u16)
#endif

#ifndef c_u32_to_strbase
void test_u32_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(u32)
#endif

#ifndef c_u64_to_strbase
void test_u64_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(u64)
#endif

#ifdef __int128
#ifndef c_u128_to_strbase
void test_u128_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(u128)
#endif

#endif
#ifndef c_uint_to_strbase
void test_uint_to_strbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(uint)
#endif





















/*
** ************************************************************************** *|
**                        Convert to Number Operations                        *|
** ************************************************************************** *|
*/

#define DEFINETEST_STR_TO_UINT(TYPE) \
void	print_test_str_to_##TYPE(char const* test_name, int can_segfault,						\
		t_##TYPE expecting,																	\
		char const* str)																		\
{																								\
	TEST_PERFORM_RESULT_TYPE(t_##TYPE, str_to_##TYPE, str)									\
	print_test_##TYPE(test_name, "_str_to_"#TYPE, result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS_ESCAPED(str)																\
}																								\
void test_str_to_##TYPE(void)																										\
{																																	\
/*	| TEST FUNCTION          | TEST NAME                      |CAN SEGV| EXPECTING                 | TEST ARGS					*/	\
	print_test_str_to_##TYPE("str_to_"#TYPE" (n = min)       ",	FALSE,                           0, "0"                          );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           1, "1"                          );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           2, "2"                          );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           3, "3"                          );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          10, "10"                         );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          42, "42"                         );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          42, "+42"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         125, "125\n12"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "--9999999"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          85, "   85"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          35, "\f35"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          56, "\n56"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          39, "\r39+"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         138, "\t138"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "- 45678978748f"             );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         111, "111"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         111, "+111"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "-111"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "  + 56"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "++43"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, " + 41dsf-+"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "def58453"                   );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         111, "111,78"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "-\r-397+"                   );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "---84648-+"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "&%64"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "  -2"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           2, "  +2"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           2, "  2"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "!789"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "#45"                        );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "$786"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "&789"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "*4456"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, ".1234"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "/1234"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "%1234"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, ",7"                         );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, ",,789"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "  + 563"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "++4653"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, " + 45631dsf-+"              );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\200 456"                   );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\255\2543"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\0 456"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\255 5"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\\//\v/789"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "0x123"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "0b1101"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "[124578"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "=0124578"                   );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "_456"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "##4567"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\124578"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\\256"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\\256\\"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, ".456"                       );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\\25627165465413"           );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "\2568"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE" (n = 8 max)     ",	FALSE,                         255, "255"                        );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 8 min)     ",	FALSE,                       0, "-1"                         );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 8 max)     ",	FALSE,                     256,  "256"                       );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 8 maxdigit)",	FALSE,                   99999,  "99999"                     );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 8 maxdigit)",	FALSE,                       0, "-99999"                     );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 16)																									\
	{																																\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         456, "456,78"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        5896, "  +5896df"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "-5435"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        5435, "+5435"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        8543, "   8543"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        3541, "\f3541"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        5643, "\n5643"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         397, "\r397"                      );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                       32000, "\v32000"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                         397, "\r397+"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        8513, "\t8513"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        9876, "\v9876-"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                       65435, "65435+--+"                  );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                        5486, "5486helllo"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                       30000, "30000f"                     );	\
	print_test_str_to_##TYPE("str_to_"#TYPE" (n = 16max)     ",	FALSE,                       65535, "65535"                      );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 16min)     ",	FALSE,                       0, "-32769"                     );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 16max)     ",	FALSE,                   65536, "65536"                      );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 16maxdigit)",	FALSE,                 9999999, "9999999"                    );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 16maxdigit)",	FALSE,                       0, "-9999999"                   );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 32)																									\
	{																																\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                      999999,  "999999"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                      999999, "+999999"                    );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                   123456789,  "123456789"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                   123456789, "+123456789"                 );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                  1000000000,  "1000000000"                );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                  1000000000, "+1000000000"                );	\
	print_test_str_to_##TYPE("str_to_"#TYPE" (n = 32max)     ",	FALSE,                  4294967295, "4294967295"                 );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 32min)     ",	FALSE,                       0, "-1"                         );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 32max)     ",	FALSE,              4294967296, "4294967296"                 );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n > 32maxdigit)",	FALSE,            999999999999, "999999999999"               );	\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 32maxdigit)",	FALSE,                       0, "-999999999999"              );	\
	}																																\
	if (sizeof(t_##TYPE) * 8 >= 64)																									\
	{																																\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,              25627165465413, "25627165465413"             );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                500000000000, "500000000000"               );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,            6513212312310531, "+6513212312310531"          );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                           0, "-3000000000"                );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                 +3000000000, "+3000000000"                );	\
	print_test_str_to_##TYPE("str_to_"#TYPE"                 ",	FALSE,                  3000000000,  "3000000000"                );	\
	print_test_str_to_##TYPE("str_to_"#TYPE" (n = 64min)     ",	FALSE,                           0, "0"                          );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 64min)     ",	FALSE,                       0, "-1"                         );	\
	/*	print_test_str_to_##TYPE("str_to_"#TYPE" (n > 64max)     ",	FALSE,  18446744073709551616UL, "18446744073709551616"       );*/\
	/*	print_test_str_to_##TYPE("str_to_"#TYPE" (n > 64maxdigit)",	FALSE, 999999999999999999999LL, "999999999999999999999"      );*/\
		print_test_str_to_##TYPE("str_to_"#TYPE" (n < 64maxdigit)",	FALSE,                       0, "-999999999999999999999"     );	\
	}																																\
	}}}																																\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (empty str)     ",	FALSE,                       0, ""                           );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (null str)      ",	SEGV,                        0, NULL                         );	\
}

#ifndef c_str_to_u8
void test_str_to_u8(void)	{}
#else
DEFINETEST_STR_TO_UINT(u8)
#endif

#ifndef c_str_to_u16
void test_str_to_u16(void)	{}
#else
DEFINETEST_STR_TO_UINT(u16)
#endif

#ifndef c_str_to_u32
void test_str_to_u32(void)	{}
#else
DEFINETEST_STR_TO_UINT(u32)
#endif

#ifndef c_str_to_u64
void test_str_to_u64(void)	{}
#else
DEFINETEST_STR_TO_UINT(u64)
#endif

#ifdef __int128
#ifndef c_str_to_u128
void test_str_to_u128(void)	{}
#else
DEFINETEST_STR_TO_UINT(u128)
#endif
#endif

#ifndef c_str_to_uint
void test_str_to_uint(void)	{}
#else
DEFINETEST_STR_TO_UINT(uint)
#endif



#define DEFINETEST_STR_TO_SINT(TYPE) \
void	print_test_str_to_##TYPE(char const* test_name, int can_segfault,					\
		t_##TYPE expecting,																	\
		char const* str)																	\
{																							\
	TEST_PERFORM_RESULT_TYPE(t_##TYPE, str_to_##TYPE, str)									\
	print_test_##TYPE(test_name, "_str_to_s"#TYPE, result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);															\
	TEST_PRINT_ARGS_ESCAPED(str)															\
}																							\
void test_str_to_##TYPE(void)																											\
{																																		\
/*	| TEST FUNCTION          | TEST NAME                         |CAN SEGV| EXPECTING                 | TEST ARGS					*/	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "0"                          );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           1, "1"                          );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          42, "42"                         );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         -42, "-42"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         125, "125\n12"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "--9999999"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          85, "   85"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          35, "\f35"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          56, "\n56"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          39, "\r39+"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         138, "\t138"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "- 45678978748f"             );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         111, "111"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        -111, "-111"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "  + 56"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "++43"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, " + 41dsf-+"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "def58453"                   );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         111, "111,78"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "-\r-397+"                   );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "---84648-+"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "&%64"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                          -2, "  -2"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           2, "  2"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "!789"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "#45"                        );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "$786"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "&789"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "*4456"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, ".1234"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "/1234"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "%1234"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, ",7"                         );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, ",,789"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "  + 563"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "++4653"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, " + 45631dsf-+"              );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\200 456"                   );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\255\2543"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\0 456"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\255 5"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\\//\v/789"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "0x123"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "0b1101"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "[124578"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "=0124578"                   );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "_456"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "##4567"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\124578"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\\256"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\\256\\"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, ".456"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\\25627165465413"           );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                           0, "\2568"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 8 min)     ",	FALSE,                        -128, "-128"                       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 8 max)     ",	FALSE,                         127, " 127"                       );	\
	if (g_test.flags.test_overflow) {																									\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 8 min)     ",	FALSE,                    -129, "-129"                       );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 8 max)     ",	FALSE,                     128, " 128"                       );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 8 maxdigit)",	FALSE,                  -99999, "-99999"                     );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 8 maxdigit)",	FALSE,                   99999, " 99999"                     );	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 16)																										\
	{																																	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         456, "456,78"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        5896, "  +5896df"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                       -5435, "-5435"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        8543, "   8543"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        3541, "\f3541"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        5643, "\n5643"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         397, "\r397"                      );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                       32000, "\v32000"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                         397, "\r397+"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        8513, "\t8513"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        9876, "\v9876-"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                       65435, "65435+--+"                  );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                        5486, "5486helllo"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                       30000, "30000f"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 16min)     ",	FALSE,                      -32768, "-32768"                     );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 16max)     ",	FALSE,                       32767, " 32767"                     );	\
	if (g_test.flags.test_overflow) {																									\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 16min)     ",	FALSE,                  -32769, "-32769"                     );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 16max)     ",	FALSE,                   32768,  "32768"                     );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 16maxdigit)",	FALSE,                -9999999, "-9999999"                   );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 16maxdigit)",	FALSE,                 9999999,  "9999999"                   );	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 32)																										\
	{																																	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                     -999999, "-999999"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                      999999,  "999999"                    );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                  -123456789, "-123456789"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                   123456789,  "123456789"                 );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                 -1000000000, "-1000000000"                );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                  1000000000,  "1000000000"                );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 32min)     ",	FALSE,                 -2147483648, "-2147483648"                );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 32max)     ",	FALSE,                  2147483647,  "2147483647"                );	\
	if (g_test.flags.test_overflow) {																									\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 32min)     ",	FALSE,             -2147483649, "-2147483649"                );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 32max)     ",	FALSE,              2147483648,  "2147483648"                );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 32maxdigit)",	FALSE,           -999999999999, "-999999999999"              );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 32maxdigit)",	FALSE,            999999999999,  "999999999999"              );	\
	}																																	\
	if (sizeof(t_##TYPE) * 8 >= 64)																										\
	{																																	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,              25627165465413,  "25627165465413"            );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,               -500000000000, "-500000000000"              );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,           -6513212312310531, "-6513212312310531"          );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                 -3000000000, "-3000000000"                );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE"                 ",	FALSE,                  3000000000,  "3000000000"                );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 64min)     ",	FALSE,      -9223372036854775808LL, "-9223372036854775808"       );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (n = 64max)     ",	FALSE,       9223372036854775807LL,  "9223372036854775807"       );	\
	if (g_test.flags.test_overflow) {																									\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 64min)     ",	FALSE,  -9223372036854775809LL, "-9223372036854775809"       );	\
		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 64max)     ",	FALSE,   9223372036854775808LL,  "9223372036854775808"       );	\
/*		print_test_str_to_##TYPE("str_to_s"#TYPE" (n < 64maxdigit)",	FALSE,-999999999999999999999LL, "-999999999999999999999"     );*/\
/*		print_test_str_to_##TYPE("str_to_s"#TYPE" (n > 64maxdigit)",	FALSE, 999999999999999999999LL,  "999999999999999999999"     );*/\
	}																																	\
	}}}																																	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (empty str)     ",	FALSE,                           0, ""                           );	\
	print_test_str_to_##TYPE("str_to_s"#TYPE" (null str)      ",	SEGV,                            0, NULL                         );	\
}

#ifndef c_str_to_s8
void test_str_to_s8(void)	{}
#else
DEFINETEST_STR_TO_SINT(s8)
#endif

#ifndef c_str_to_s16
void test_str_to_s16(void)	{}
#else
DEFINETEST_STR_TO_SINT(s16)
#endif

#ifndef c_str_to_s32
void test_str_to_s32(void)	{}
#else
DEFINETEST_STR_TO_SINT(s32)
#endif

#ifndef c_str_to_s64
void test_str_to_s64(void)	{}
#else
DEFINETEST_STR_TO_SINT(s64)
#endif

#ifdef __int128
#ifndef _str_to_s128
void test_str_to_s128(void)	{}
#else
DEFINETEST_STR_TO_SINT(s128)
#endif

#endif
#ifndef _str_to_sint
void test_str_to_sint(void)	{}
#else
DEFINETEST_STR_TO_SINT(sint)
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
**                       Convert Base String to Integer                       *|
** ************************************************************************** *|
*/

#define DEFINETEST_STRBASE_TO_UINT(TYPE) \
void	print_test_strbase_to_##TYPE(char const* test_name, int can_segfault,					\
		t_##TYPE expecting,																	\
		char const* number,																		\
		char const* base)																		\
{																								\
	TEST_PERFORM_RESULT_TYPE(t_##TYPE, strbase_to_##TYPE, number, base)						\
	print_test_##TYPE(test_name, "_strbase_to_"#TYPE, result_libccc, expecting, can_segfault);\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);											\
}																								\
void	test_strbase_to_##TYPE(void)																												\
{																																					\
/*	| TEST FUNCTION          | TEST NAME                             |CAN SEGV|      EXPECTING              | TEST ARGS							*/	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = min, dec)  ",	FALSE,                      0,                   "0",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = min, hex)  ",	FALSE,                      0,                   "0", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = min, oct)  ",	FALSE,                      0,                   "0",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = min, bin)  ",	FALSE,                      0,                   "0",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      1,                   "1",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "1",               "+1");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "m",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "m",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                  "mm",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                 "mmm",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     42,              "101010",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,              "101012",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "m",              "mom");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "o",              "mom");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     15,                   "F", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     42,                  "2A", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                   "0",              "0az");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                    111,                 "aaa",       "_abcdefghi");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     63,                "rdmm",              "mdr");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                    100,               "|*_*|",              "*|_");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     13,                ".._.",               "_.");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                     42,                  "42",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                  "42",       "012345678-");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                  "42",       "012345678+");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 8 max, dec)",	FALSE,                    255,                 "255",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 8 max, hex)",	FALSE,                    255,                  "FF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 8 max, oct)",	FALSE,                    255,                 "377",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 8 max, bin)",	FALSE,                    255,            "11111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 8 min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 8 max)     ",	FALSE,                256,                 "256",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 8 maxdigit)",	FALSE,             -99999,              "-99999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 8 maxdigit)",	FALSE,              99999,               "99999",       "0123456789");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 16)																													\
	{																																				\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                  12345,               "12345",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,               "12345",       "012345678-");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,               "12345",       "012345678+");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                      0,                 "999",       "0123456389");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                    999,                 "999",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                  10007,               "c===3",       "=cbadef389");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                   1234,                "swag",       "0swag56789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                   1000,                 "3e8", "0123456789abcdef");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 16max, dec)",	FALSE,                  65535,               "65535",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 16max, hex)",	FALSE,                  65535,                "FFFF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 16max, oct)",	FALSE,                  65535,              "177777",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 16max, bin)",	FALSE,                  65535,    "1111111111111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 16min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 16max)     ",	FALSE,              65536,               "65536",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 16maxdigit)",	FALSE,           -9999999,            "-9999999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 16maxdigit)",	FALSE,            9999999,             "9999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 32)																													\
	{																																				\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE"                 ",	FALSE,                +987123,              "*xurin",       "grincheux*");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 32max, dec)",	FALSE,             4294967295,          "4294967295",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 32max, hex)",	FALSE,             4294967295,            "FFFFFFFF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 32max, oct)",	FALSE,             4294967295,         "37777777777",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 32max, bin)",	FALSE,             4294967295,"11111111111111111111111111111111",   "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 32min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 32max)     ",	FALSE,         4294967296,          "4294967296",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 32maxdigit)",	FALSE,      -999999999999,       "-999999999999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 32maxdigit)",	FALSE,       999999999999,        "999999999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_##TYPE) * 8 >= 64)																													\
	{																																				\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 64max, dec)",	FALSE, 18446744073709551615UL,  "18446744073709551615",      "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 64max, hex)",	FALSE, 18446744073709551615UL,      "FFFFFFFFFFFFFFFF","0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 64max, oct)",	FALSE, 18446744073709551615UL,"1777777777777777777777",        "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n = 64max, bin)",	FALSE, 18446744073709551615UL,"1111111111111111111111111111111111111111111111111111111111111111","01");\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 64min)     ",FALSE,                      -1,                    "-1",  "0123456789");	\
	/*	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 64max)     ",FALSE,  18446744073709551616UL,  "18446744073709551616",  "0123456789");*/	\
	/*	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n < 64maxdigit)",FALSE,-999999999999999999999LL,"-999999999999999999999",  "0123456789");*/	\
	/*	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (n > 64maxdigit)",FALSE, 999999999999999999999LL, "999999999999999999999",  "0123456789");*/	\
	}																																				\
	}}}																																				\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (empty base)    ",	FALSE,                      0,                  "01",                 "");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (empty number)  ",	FALSE,                      0,                    "",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (both empty)    ",	FALSE,                      0,                    "",                 "");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (null base)     ",	SEGV,                       0,                  "01",               NULL);	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (null number)   ",	SEGV,                       0,                  NULL,               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_"#TYPE" (both null)     ",	SEGV,                       0,                  NULL,               NULL);	\
}

#ifndef c_strbase_to_u8
void test_strbase_to_u8(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(u8)
#endif

#ifndef c_strbase_to_u16
void test_strbase_to_u16(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(u16)
#endif

#ifndef c_strbase_to_u32
void test_strbase_to_u32(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(u32)
#endif

#ifndef c_strbase_to_u64
void test_strbase_to_u64(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(u64)
#endif

#ifdef __int128
#ifndef c_strbase_to_u128
void test_strbase_to_u128(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(u128)
#endif
#endif

#ifndef c_strbase_to_uint
void test_strbase_to_uint(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(uint)
#endif



#define DEFINETEST_STRBASE_TO_SINT(TYPE) \
void	print_test_strbase_to_##TYPE(char const* test_name, int can_segfault,					\
		t_##TYPE expecting,																		\
		char const* number,																		\
		char const* base)																		\
{																								\
	TEST_PERFORM_RESULT_TYPE(t_##TYPE, strbase_to_##TYPE, number, base)							\
	print_test_##TYPE(test_name, "_strbase_to_s"#TYPE, result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);																\
	TEST_PRINT_ARGS("base='%s', n='%s'", base, number);											\
}																								\
void	test_strbase_to_##TYPE(void)																													\
{																																						\
/*	| TEST FUNCTION              | TEST NAME                             |CAN SEGV|  EXPECTING          | TEST ARGS									*/	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "0",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     1,                    "1",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     2,                   "10",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "1",               "+1");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "m",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                   "mm",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                  "mmm",                "m");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    42,               "101010",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,               "101012",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "m",              "mom");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "o",              "mom");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    42,                   "2A", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "0",              "0az");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                   111,                  "aaa",       "_abcdefghi");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                  -111,                 "-aaa",       "_abcdefghi");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                   -15,                   "-F", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    63,                 "rdmm",              "mdr");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                   100,                "|*_*|",              "*|_");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    13,                 ".._.",               "_.");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    42,                   "2A", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                    42,                   "42",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "2",       "012345678-");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                    "2",       "012345678+");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 min, dec)",	FALSE,                  -128,                 "-128",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 max, dec)",	FALSE,                   127,                  "127",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 min, hex)",	FALSE,                  -128,                  "-80", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 max, hex)",	FALSE,                   127,                   "7F", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 min, oct)",	FALSE,                  -128,                 "-200",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 max, oct)",	FALSE,                   127,                  "177",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 min, bin)",	FALSE,                  -128,            "-10000000",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 8 max, bin)",	FALSE,                   127,              "1111111",               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 8 min)     ",	FALSE,              -129,                 "-129",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 8 max)     ",	FALSE,               128,                  "128",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 8 maxdigit)",	FALSE,            -99999,               "-99999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 8 maxdigit)",	FALSE,             99999,                "99999",       "0123456789");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 16)																														\
	{																																					\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                 12345,                "12345",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                "12345",       "012345678-");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                "12345",       "012345678+");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                     0,                  "999",       "01+3456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                 10007,                "c===3",       "=cbadef389");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                  1234,                 "swag",       "0swag56789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,                 -1000,                 "-3e8", "0123456789abcdef");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE"                 ",	FALSE,               +987123,               "*xurin",       "grincheux*");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16min, dec)",	FALSE,                -32768,               "-32768",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16max, dec)",	FALSE,                 32767,                "32767",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16min, hex)",	FALSE,                -32768,                "-8000", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16max, hex)",	FALSE,                 32767,                 "7FFF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16min, oct)",	FALSE,                -32768,              "-100000",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16max, oct)",	FALSE,                 32767,                "77777",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16min, bin)",	FALSE,                -32768,    "-1000000000000000",               "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 16max, bin)",	FALSE,                 32767,      "111111111111111",               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 16min)     ",	FALSE,            -32769,               "-32769",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 16max)     ",	FALSE,             32768,                "32768",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 16maxdigit)",	FALSE,          -9999999,             "-9999999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 16maxdigit)",	FALSE,           9999999,              "9999999",       "0123456789");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 32)																														\
	{																																					\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32min, dec)",	FALSE,           -2147483648,          "-2147483648",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32max, dec)",	FALSE,            2147483647,           "2147483647",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32min, hex)",	FALSE,           -2147483648,            "-80000000", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32max, hex)",	FALSE,            2147483647,             "7FFFFFFF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32min, oct)",	FALSE,           -2147483648,         "-20000000000",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32max, oct)",	FALSE,            2147483647,          "17777777777",         "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32min, bin)",	FALSE,           -2147483648,"-10000000000000000000000000000000",   "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 32max, bin)",	FALSE,            2147483647,  "1111111111111111111111111111111",   "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 32min)     ",	FALSE,       -2147483649,          "-2147483649",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 32max)     ",	FALSE,        2147483648,           "2147483648",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 32maxdigit)",	FALSE,     -999999999999,        "-999999999999",       "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 32maxdigit)",	FALSE,      999999999999,         "999999999999",       "0123456789");	\
	}																																					\
	if (sizeof(t_##TYPE) * 8 >= 64)																														\
	{																																					\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64min, dec)",	FALSE,  -9223372036854775808, "-9223372036854775808",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64max, dec)",	FALSE,   9223372036854775807,  "9223372036854775807",       "0123456789");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64min, hex)",	FALSE,  -9223372036854775808,    "-8000000000000000", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64max, hex)",	FALSE,   9223372036854775807,     "7FFFFFFFFFFFFFFF", "0123456789ABCDEF");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64min, oct)",	FALSE,  -9223372036854775808,"-1000000000000000000000",       "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64max, oct)",	FALSE,   9223372036854775807,  "777777777777777777777",       "01234567");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64min, bin)",	FALSE,  -9223372036854775808,"-1000000000000000000000000000000000000000000000000000000000000000","01");\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n = 64max, bin)",	FALSE,   9223372036854775807,  "111111111111111111111111111111111111111111111111111111111111111","01");\
	if (g_test.flags.test_overflow) {																													\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 64max)     ",FALSE,   9223372036854775808,   "9223372036854775808",    "0123456789");	\
		print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 64min)     ",FALSE,  -9223372036854775808,  "-9223372036854775808",    "0123456789");	\
	/*	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n < 64maxdigit)",FALSE, 999999999999999999999, "999999999999999999999",    "0123456789");*/	\
	/*	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (n > 64maxdigit)",FALSE,-999999999999999999999,"-999999999999999999999",    "0123456789");*/	\
	}																																					\
	}}}																																					\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (empty base)    ",	FALSE,                     0,                   "01",                "");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (empty number)  ",	FALSE,                     0,                     "",              "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (both empty)    ",	FALSE,                     0,                     "",                "");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (null base)     ",	SEGV,                      0,                   "01",              NULL);	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (null number)   ",	SEGV,                      0,                   NULL,              "01");	\
	print_test_strbase_to_##TYPE("strbase_to_s"#TYPE" (both null)     ",	SEGV,                      0,                   NULL,              NULL);	\
}

#ifndef c_strbase_to_s8
void test_strbase_to_s8(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(s8)
#endif

#ifndef c_strbase_to_s16
void test_strbase_to_s16(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(s16)
#endif

#ifndef c_strbase_to_s32
void test_strbase_to_s32(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(s32)
#endif

#ifndef c_strbase_to_s64
void test_strbase_to_s64(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(s64)
#endif

#ifdef __int128
#ifndef c_strbase_to_s128
void test_strbase_to_s128(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(s128)
#endif

#endif
#ifndef c_strbase_to_sint
void test_strbase_to_sint(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(sint)
#endif



#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_int(void)
{
	print_suite_title("int");

	print_nonstd();

	test_u8_to_str();
	test_u16_to_str();
	test_u32_to_str();
	test_u64_to_str();
//	test_u128_to_str();
	test_uint_to_str();

	test_s8_to_str();
	test_s16_to_str();
	test_s32_to_str();
	test_s64_to_str();
//	test_s128_to_str();
	test_sint_to_str();


	test_u8_to_strhex();
	test_u16_to_strhex();
	test_u32_to_strhex();
	test_u64_to_strhex();
//	test_u128_to_strhex();
	test_uint_to_strhex();


	test_s8_to_strbase();
	test_s16_to_strbase();
	test_s32_to_strbase();
	test_s64_to_strbase();
//	test_s128_to_strbase();
	test_sint_to_strbase();

	test_u8_to_strbase();
	test_u16_to_strbase();
	test_u32_to_strbase();
	test_u64_to_strbase();
//	test_u128_to_strbase();
	test_uint_to_strbase();



	test_str_to_s8();
	test_str_to_s16();
	test_str_to_s32();
	test_str_to_s64();
//	test_str_to_s128();
	test_str_to_sint();

	test_str_to_u8();
	test_str_to_u16();
	test_str_to_u32();
	test_str_to_u64();
//	test_str_to_u128();
	test_str_to_uint();


//	test_strhex_to_u8();
//	test_strhex_to_u16();
//	test_strhex_to_u32();
//	test_strhex_to_u64();
//	test_strhex_to_u128();
//	test_strhex_to_uint();


	test_strbase_to_s8();
	test_strbase_to_s16();
	test_strbase_to_s32();
	test_strbase_to_s64();
//	test_strbase_to_s128();
	test_strbase_to_sint();

	test_strbase_to_u8();
	test_strbase_to_u16();
	test_strbase_to_u32();
	test_strbase_to_u64();
//	test_strbase_to_u128();
	test_strbase_to_uint();

	return (OK);
}
