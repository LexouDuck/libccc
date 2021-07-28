
#include "libccc.h"
#include "libccc/format.h"
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
**                        Convert Integers to Strings                         *|
** ************************************************************************** *|
*/

#define DEFINETEST_UINT_TO_STR(BITS) \
void	print_test_u##BITS##tostr(char const* test_name, int can_segfault,		\
		char const* expecting,													\
		t_u##BITS number)														\
{																				\
	TEST_INIT(str)																\
	TEST_PERFORM(	u##BITS##tostr, number)										\
	TEST_PRINT(str, u##BITS##tostr, "n="SF_U##BITS, number)						\
	TEST_FREE()																	\
}																				\
void	test_u##BITS##tostr(void)																							\
{																															\
/*	| TEST FUNCTION          | TEST NAME                      |CAN SEGV| EXPECTING             | TEST ARGS			*/		\
	print_test_u##BITS##tostr("u"#BITS"tostr (n = min)       ",	FALSE,                      "0", 0                     );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                      "1", 1                     );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                      "9", 9                     );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                     "10", 10                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                     "11", 11                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                     "42", 42                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                     "99", 99                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "100", 100                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "111", 111                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "123", 123                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "127", 127                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "128", 128                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "129", 129                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n = 8max)      ",	FALSE,                    "255", 255                   );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 8min)      ",	FALSE,                     "-1", -1                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 8max)      ",	FALSE,                    "256", 256                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 8maxdigit) ",	FALSE,                  "99999", 99999                 );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 8maxdigit) ",	FALSE,                 "-99999",-99999                 );	\
	}																														\
	if (sizeof(t_u##BITS) * 8 >= 16)																						\
	{																														\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                    "777", 777                   );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                   "7777", 7777                  );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,                  "10000", 10000                 );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n = 16max)     ",	FALSE,                  "65535", 65535                 );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 16min)     ",	FALSE,                     "-1", -1                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 16max)     ",	FALSE,                  "65536", 65536                 );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 16maxdigit)",	FALSE,                "9999999", 9999999               );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 16maxdigit)",	FALSE,               "-9999999",-9999999               );	\
	}																														\
	if (sizeof(t_u##BITS) * 8 >= 32)																						\
	{																														\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,              "123456789", 123456789             );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,              "555555555", 555555555             );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,              "987654321", 987654321             );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n = 32max)     ",	FALSE,             "4294967295", 4294967295            );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 32min)     ",	FALSE,                     "-1", -1                    );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 32max)     ",	FALSE,             "4294967296", 4294967296            );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n > 32maxdigit)",	FALSE,           "999999999999", 999999999999          );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 32maxdigit)",	FALSE,          "-999999999999",-999999999999          );	\
	}																														\
	if (sizeof(t_u##BITS) * 8 >= 64)																						\
	{																														\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,             "9876543210", 9876543210ul          );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,           "999999999999", 999999999999ul        );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,        "999999999999000", 999999999999000ul     );	\
	print_test_u##BITS##tostr("u"#BITS"tostr                 ",	FALSE,     "999999999999000999", 999999999999000999ul  );	\
	print_test_u##BITS##tostr("u"#BITS"tostr (n = 64max)     ",	FALSE,   "18446744073709551615", 18446744073709551615ul);	\
	if (g_test.flags.test_overflow) {																						\
	print_test_u##BITS##tostr("u"#BITS"tostr (n < 64min)     ",	FALSE,                     "-1", -1                    );	\
/*	print_test_u##BITS##tostr("u"#BITS"tostr (n > 64max)     ",	FALSE,   "18446744073709551616", 18446744073709551616ul); */\
/*	print_test_u##BITS##tostr("u"#BITS"tostr (n > 64maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999ul);*/\
/*	print_test_u##BITS##tostr("u"#BITS"tostr (n < 64maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999ul);*/\
	}																														\
	}}}																														\
}

#ifndef c_u8tostr
void test_u8tostr(void)	{}
#else
DEFINETEST_UINT_TO_STR(8)
#endif

#ifndef c_u16tostr
void test_u16tostr(void)	{}
#else
DEFINETEST_UINT_TO_STR(16)
#endif

#ifndef c_u32tostr
void test_u32tostr(void)	{}
#else
DEFINETEST_UINT_TO_STR(32)
#endif

#ifndef c_u64tostr
void test_u64tostr(void)	{}
#else
DEFINETEST_UINT_TO_STR(64)
#endif

#ifdef __int128
#ifndef c_u128tostr
void test_u128tostr(void)	{}
#else
DEFINETEST_UINT_TO_STR(128)
#endif
#endif



#define DEFINETEST_SINT_TO_STR(BITS) \
void	print_test_s##BITS##tostr(char const* test_name, int can_segfault,		\
		char const* expecting,													\
		t_s##BITS number)														\
{																				\
	TEST_INIT(str)																\
	TEST_PERFORM(	s##BITS##tostr, number)										\
	TEST_PRINT(str, s##BITS##tostr, "n="SF_S##BITS, number)						\
	TEST_FREE()																	\
}																				\
void	test_s##BITS##tostr(void)																							\
{																															\
/*	| TEST FUNCTION          | TEST NAME                     |CAN SEGV| EXPECTING              | TEST ARGS				*/	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                      "1", 1                      );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                     "-1",-1                      );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                     "10", 10                     );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                    "-10",-10                     );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                      "0", 0                      );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                     "42", 42                     );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                    "111", 111                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                   "-111",-111                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 8min)      ",	FALSE,                   "-128",-128                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 8max)      ",	FALSE,                    "127", 127                    );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 8min)      ",	FALSE,                   "-129",-129                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 8max)      ",	FALSE,                    "128", 128                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 8maxdigit) ",	FALSE,                  "99999", 99999                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 8maxdigit) ",	FALSE,                 "-99999",-99999                  );	\
	}																														\
	if (sizeof(t_s##BITS) * 8 >= 16)																						\
	{																														\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                    "777", 777                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                   "-666",-666                    );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                 "-10000",-10000                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,                  "10000",+10000                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 16min)     ",	FALSE,                 "-32768",-32768                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 16max)     ",	FALSE,                  "32767", 32767                  );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 16min)     ",	FALSE,                 "-32769",-32769                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 16max)     ",	FALSE,                  "32768", 32768                  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 16maxdigit)",	FALSE,                "9999999", 9999999                );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 16maxdigit)",	FALSE,               "-9999999",-9999999                );	\
	}																														\
	if (sizeof(t_s##BITS) * 8 >= 32)																						\
	{																														\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,             "-123456789",-123456789              );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,              "123456789", 123456789              );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,             "-987654321",-987654321              );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,              "987654321", 987654321              );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 32min)     ",	FALSE,            "-2147483648",-2147483648             );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 32max)     ",	FALSE,             "2147483647", 2147483647             );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 32min)     ",	FALSE,            "-2147483649",-2147483649             );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 32max)     ",	FALSE,             "2147483648", 2147483648             );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 32maxdigit)",	FALSE,           "999999999999", 999999999999           );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 32maxdigit)",	FALSE,          "-999999999999",-999999999999           );	\
	}																														\
	if (sizeof(t_s##BITS) * 8 >= 64)																						\
	{																														\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,             "2147483648", 2147483648ll           );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,            "-2147483649",-2147483649ll           );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,            "-9876543210",-9876543210ll           );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,             "9876543210", 9876543210ll           );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,           "999999999999", 999999999999ll         );	\
	print_test_s##BITS##tostr("s"#BITS"tostr                 ",	FALSE,          "-999999999999",-999999999999ll         );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 64min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808ll  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n = 64max)     ",	FALSE,    "9223372036854775807", 9223372036854775807ll  );	\
	if (g_test.flags.test_overflow) {																						\
	print_test_s##BITS##tostr("s"#BITS"tostr (n < 64min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809ll  );	\
	print_test_s##BITS##tostr("s"#BITS"tostr (n > 64max)     ",	FALSE,    "9223372036854775808", 9223372036854775808ll  );	\
/*	print_test_s##BITS##tostr("s"#BITS"tostr (n > 64maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999ll);*/\
/*	print_test_s##BITS##tostr("s"#BITS"tostr (n < 64maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999ll);*/\
	}																														\
	}}}																														\
}

#ifndef c_s8tostr
void test_s8tostr(void)	{}
#else
DEFINETEST_SINT_TO_STR(8)
#endif

#ifndef c_s16tostr
void test_s16tostr(void)	{}
#else
DEFINETEST_SINT_TO_STR(16)
#endif

#ifndef c_s32tostr
void test_s32tostr(void)	{}
#else
DEFINETEST_SINT_TO_STR(32)
#endif

#ifndef c_s64tostr
void test_s64tostr(void)	{}
#else
DEFINETEST_SINT_TO_STR(64)
#endif

#ifdef __int128
#ifndef c_s128tostr
void test_s128tostr(void)	{}
#else
DEFINETEST_SINT_TO_STR(128)
#endif
#endif



/*
** ************************************************************************** *|
**                       Convert to Hexadecimal String                        *|
** ************************************************************************** *|
*/

#define DEFINETEST_UINT_TO_STRHEX(BITS) \
void	print_test_u##BITS##tostrhex(char const* test_name, int can_segfault,		\
		char const* expecting,														\
		t_u##BITS number)															\
{																					\
	TEST_INIT(str)																	\
	TEST_PERFORM(	u##BITS##tostrhex, number, FALSE)								\
	TEST_PRINT(str, u##BITS##tostrhex, "prefix=%s, n="SF_U##BITS"", BOOL_TOSTRING(FALSE), number)	\
	TEST_FREE()																		\
}																					\
void	test_u##BITS##tostrhex(void)																								\
{																																	\
/*	| TEST FUNCTION             | TEST NAME                          |CAN SEGV| EXPECTING              | TEST ARGS				*/	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n = min)       ",	FALSE,                      "0", 0                     );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                      "1", 1                     );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                      "2", 2                     );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                      "3", 3                     );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                      "F", 15                    );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                     "10", 16                    );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                     "2A", 42                    );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                     "6F", 111                   );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n = 8max)      ",	FALSE,                     "FF", 255                   );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 8min)      ",	FALSE,                 "-1", -1                    );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 8max)      ",	FALSE,                "100", 256                   );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 8maxdigit) ",	FALSE,              "1869F", 99999                 );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 8maxdigit) ",	FALSE,             "-1869F",-99999                 );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 16)																								\
	{																																\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                    "30A", 778                   );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                   "2710", 10000                 );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n = 16max)     ",	FALSE,                   "FFFF", 65535                 );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 16min)     ",	FALSE,                 "-1", -1                    );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 16max)     ",	FALSE,              "10000", 65536                 );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 16maxdigit)",	FALSE,             "98967F", 9999999               );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 16maxdigit)",	FALSE,            "-98967F",-9999999               );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 32)																								\
	{																																\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,                "75BCD15", 123456789             );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,               "3ADE68B1", 987654321             );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n = 32max)     ",	FALSE,               "FFFFFFFF", 4294967295            );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 32min)     ",	FALSE,                 "-1", -1                    );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 32max)     ",	FALSE,          "100000000", 4294967296            );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 32maxdigit)",	FALSE,         "E8D4A50FFF", 999999999999          );	\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 32maxdigit)",	FALSE,         "E8D4A51000", 1000000000000         );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 64)																								\
	{																																\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,              "24CB016EA", 9876543210ul          );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,             "E8D4A50FFF", 999999999999ul        );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex                 ",	FALSE,             "E8D4A51000", 1000000000000ul       );	\
	print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n = 64max)     ",	FALSE,       "FFFFFFFFFFFFFFFF", 18446744073709551615ul);	\
	if (g_test.flags.test_overflow) {																								\
		print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 64min)     ",	FALSE,                 "-1", -1                    );	\
		/*print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 64max)     ",	FALSE,  "10000000000000000", 18446744073709551616ul);*/	\
		/*print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n > 64maxdigit)",	FALSE,                  "0", 999999999999999999999ul);*/\
		/*print_test_u##BITS##tostrhex("u"#BITS"tostrhex (n < 64maxdigit)",	FALSE,                  "0",-999999999999999999999ul);*/\
	}																																\
	}}}																																\
}

#ifndef c_u8tostrhex
void test_u8tostrhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(8)
#endif

#ifndef c_u16tostrhex
void test_u16tostrhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(16)
#endif

#ifndef c_u32tostrhex
void test_u32tostrhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(32)
#endif

#ifndef c_u64tostrhex
void test_u64tostrhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(64)
#endif

#ifdef __int128
#ifndef c_u128tostrhex
void test_u128tostrhex(void)	{}
#else
DEFINETEST_UINT_TO_STRHEX(128)
#endif
#endif



/*
** ************************************************************************** *|
**                       Convert Integer to Base String                       *|
** ************************************************************************** *|
*/

#define DEFINETEST_SINT_TO_STRBASE(BITS) \
void	print_test_s##BITS##tostrbase(char const* test_name, int can_segfault,		\
		char const* expecting,														\
		t_s##BITS number,															\
		char const* base)															\
{																					\
	TEST_INIT(str)																	\
	TEST_PERFORM(	s##BITS##tostrbase, number, base)								\
	TEST_PRINT(str, s##BITS##tostrbase, "base=\"%s\", n="SF_S##BITS, base, number)	\
	TEST_FREE()																		\
}																					\
void	test_s##BITS##tostrbase(void)																													\
{																																						\
/*	| TEST FUNCTION              | TEST NAME                          |CAN SEGV| EXPECTING                | TEST ARGS								*/	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                         "1",                   1,               "01");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,                   1,               "+1");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,                   0,                "m");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,                   1,                "m");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                    "101010",                  42,               "01");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,                   0,              "mom");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                         "0",                   0,              "0az");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                       "aaa",                 111,       "_abcdefghi");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                      "-aaa",                -111,       "_abcdefghi");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        "-F",                 -15, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                      "rdmm",                  63,              "mdr");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                     "|*_*|",                 100,              "*|_");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                      ".._.",                  13,               "_.");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        "42",                  42,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,               12345,       "012345678-");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,               12345,       "012345678+");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        NULL,                 999,       "01+3456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8min, dec) ",	FALSE,                      "-128",                -128,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8max, dec) ",	FALSE,                       "127",                 127,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8min, hex) ",	FALSE,                       "-80",                -128, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8max, hex) ",	FALSE,                        "7F",                 127, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8min, oct) ",	FALSE,                      "-200",                -128,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8max, oct) ",	FALSE,                       "177",                 127,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8min, bin) ",	FALSE,                 "-10000000",                -128,               "01");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 8max, bin) ",	FALSE,                   "1111111",                 127,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 8min)      ",	FALSE,                  "-129",                -129,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 8max)      ",	FALSE,                   "128",                 128,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 8maxdigit) ",	FALSE,                    NULL,               99999,               "01");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 8maxdigit) ",	FALSE,                    NULL,              -99999,               "01");	\
	}																																					\
	if (sizeof(t_s##BITS) * 8 >= 16)																													\
	{																																					\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                     "12345",               12345,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                     "12345",               12345,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                     "c===3",               10007,       "=cbadef389");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                      "swag",                1234,       "0swag56789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                      "-3e8",               -1000, "0123456789abcdef");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                        "2A",                  42, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16min, dec)",	FALSE,                    "-32768",              -32768,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16max, dec)",	FALSE,                     "32767",               32767,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16min, hex)",	FALSE,                     "-8000",              -32768, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16max, hex)",	FALSE,                      "7FFF",               32767, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16min, oct)",	FALSE,                   "-100000",              -32768,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16max, oct)",	FALSE,                     "77777",               32767,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16min, bin)",	FALSE,         "-1000000000000000",              -32768,               "01");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 16max, bin)",	FALSE,           "111111111111111",               32767,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 16min)     ",	FALSE,                "-32769",              -32769,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 16max)     ",	FALSE,                 "32768",               32768,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 16maxdigit)",	FALSE,                    NULL,             9999999,               "01");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 16maxdigit)",	FALSE,                    NULL,            -9999999,               "01");	\
	}																																					\
	if (sizeof(t_s##BITS) * 8 >= 32)																													\
	{																																					\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                    "*xurin",             +987123,       "grincheux*");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                 "abcdefghi",           123456789,       " abcdefghi");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32min, dec)",	FALSE,               "-2147483648",         -2147483648,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32max, dec)",	FALSE,                "2147483647",          2147483647,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32min, hex)",	FALSE,                 "-80000000",         -2147483648, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32max, hex)",	FALSE,                  "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32min, oct)",	FALSE,              "-20000000000",         -2147483648,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32max, oct)",	FALSE,               "17777777777",          2147483647,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32min, bin)",	FALSE,"-10000000000000000000000000000000",  -2147483648,               "01");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 32max, bin)",	FALSE,  "1111111111111111111111111111111",   2147483647,               "01");	\
	if (g_test.flags.test_overflow) {																													\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 32min)     ",	FALSE,           "-2147483649",         -2147483649,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 32max)     ",	FALSE,            "2147483648",          2147483648,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 32maxdigit)",	FALSE,                    NULL,        999999999999,               "01");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 32maxdigit)",	FALSE,                    NULL,       -999999999999,               "01");	\
	}																																					\
	if (sizeof(t_s##BITS) * 8 >= 64)																													\
	{																																					\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,                  "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,               "-2147483648",         -2147483648,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase                 ",	FALSE,               "-2147483648",         -2147483648,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64min, dec)",	FALSE,      "-9223372036854775808",-9223372036854775808,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64max, dec)",	FALSE,       "9223372036854775807", 9223372036854775807,       "0123456789");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64min, hex)",	FALSE,         "-8000000000000000",-9223372036854775808, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64max, hex)",	FALSE,          "7FFFFFFFFFFFFFFF", 9223372036854775807, "0123456789ABCDEF");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64min, oct)",	FALSE,   "-1000000000000000000000",-9223372036854775808,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64max, oct)",	FALSE,     "777777777777777777777", 9223372036854775807,         "01234567");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64min, bin)",	FALSE,"-1000000000000000000000000000000000000000000000000000000000000000",-9223372036854775808,"01");\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n = 64max, bin)",	FALSE,  "111111111111111111111111111111111111111111111111111111111111111", 9223372036854775807,"01");\
	if (g_test.flags.test_overflow) {																													\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 64min)     ",	FALSE,  "-9223372036854775808",-9223372036854775808,       "0123456789");	\
		print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 64max)     ",	FALSE,   "9223372036854775808", 9223372036854775808,       "0123456789");	\
	/*	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n > 64maxdigit)",	FALSE,                  NULL, 999999999999999999999,               "01");*/	\
	/*	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (n < 64maxdigit)",	FALSE,                  NULL,-999999999999999999999,               "01");*/	\
	}																																					\
	}}}																																					\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (empty base)    ",	FALSE,                        NULL,                  42,                 "");	\
	print_test_s##BITS##tostrbase("s"#BITS"tostrbase (null base)     ",	SIGNAL_SIGSEGV,               NULL,                  42,               NULL);	\
}

#ifndef c_s8tostrbase
void test_s8tostrbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(8)
#endif

#ifndef c_s16tostrbase
void test_s16tostrbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(16)
#endif

#ifndef c_s32tostrbase
void test_s32tostrbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(32)
#endif

#ifndef c_s64tostrbase
void test_s64tostrbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(64)
#endif

#ifdef __int128
#ifndef c_s128tostrbase
void test_s128tostrbase(void)	{}
#else
DEFINETEST_SINT_TO_STRBASE(128)
#endif
#endif



#define DEFINETEST_UINT_TO_STRBASE(BITS) \
void	print_test_u##BITS##tostrbase(char const* test_name, int can_segfault,		\
		char const* expecting,														\
		t_u##BITS number,															\
		char const* base)															\
{																					\
	TEST_INIT(str)																	\
	TEST_PERFORM(	u##BITS##tostrbase, number, base)								\
	TEST_PRINT(str, u##BITS##tostrbase, "base=\"%s\", n="SF_U##BITS, base, number)	\
	TEST_FREE()																		\
}																					\
void	test_u##BITS##tostrbase(void)																												\
{																																					\
/*	| TEST FUNCTION              | TEST NAME                         |CAN SEGV|  EXPECTING              | TEST ARGS								*/	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = min, dec)  ",	FALSE,                       "0",                   0,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = min, hex)  ",	FALSE,                       "0",                   0, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = min, oct)  ",	FALSE,                       "0",                   0,         "01234567");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = min, bin)  ",	FALSE,                       "0",                   0,               "01");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                       "1",                   1,               "01");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                       "1",                   1,               "+1");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      NULL,                   0,                "m");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      NULL,                   1,                "m");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                  "101010",                  42,               "01");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      NULL,                   0,              "mom");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                       "F",                  15, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                       "0",                   0,              "0az");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                     "aaa",                 111,       "_abcdefghi");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                    "rdmm",                  63,              "mdr");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                   "|*_*|",                 100,              "*|_");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                    ".._.",                  13,               "_.");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      "42",                  42,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      "42",                  42,       "012345678-");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      "42",                  42,       "012345678+");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                       "0",                   0,              "0az");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                     "aaa",                 111,       "_abcdefghi");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 8max, dec) ",	FALSE,                     "255",                 255,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 8max, hex) ",	FALSE,                      "FF",                 255, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 8max, oct) ",	FALSE,                     "377",                 255,         "01234567");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 8max, bin) ",	FALSE,                "11111111",                 255,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 8min)      ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 8max)      ",	FALSE,                 "256",                 256,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 8maxdigit) ",	FALSE,                  NULL,               99999,               "01");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 8maxdigit) ",	FALSE,                  NULL,              -99999,               "01");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 16)																												\
	{																																				\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                   "12345",               12345,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                   "12345",               12345,       "012345678-");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                   "12345",               12345,       "012345678+");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      NULL,                 999,       "0123456739");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                   "c===3",               10007,       "=cbadef389");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                    "swag",                1234,       "0swag56789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                     "3e8",                1000, "0123456789abcdef");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                     "3E8",                1000, "0123456789abcdEf");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                      "2A",                  42, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 16max, dec)",	FALSE,                   "65535",               65535,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 16max, hex)",	FALSE,                    "FFFF",               65535, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 16max, oct)",	FALSE,                  "177777",               65535,         "01234567");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 16max, bin)",	FALSE,        "1111111111111111",               65535,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 16min)     ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 16max)     ",	FALSE,               "65536",               65536,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 16maxdigit)",	FALSE,                  NULL,             9999999,               "01");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 16maxdigit)",	FALSE,                  NULL,            -9999999,               "01");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 32)																												\
	{																																				\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                  "*xurin",             +987123,       "grincheux*");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,                "7FFFFFFF",          2147483647, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase                 ",	FALSE,              "2147483648",          2147483648,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 32max, dec)",	FALSE,              "4294967295",          4294967295,       "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 32max, hex)",	FALSE,                "FFFFFFFF",          4294967295, "0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 32max, oct)",	FALSE,             "37777777777",          4294967295,         "01234567");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 32max, bin)",	FALSE, "11111111111111111111111111111111", 4294967295,               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 32min)     ",	FALSE,                  "-1",                  -1,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 32max)     ",	FALSE,          "4294967296",          4294967296,       "0123456789");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 32maxdigit)",	FALSE,                  NULL,        999999999999,               "01");	\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 32maxdigit)",	FALSE,                  NULL,       -999999999999,               "01");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 64)																												\
	{																																				\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 64max, dec)",	FALSE,  "18446744073709551615",18446744073709551615llu,      "0123456789");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 64max, hex)",	FALSE,      "FFFFFFFFFFFFFFFF",18446744073709551615llu,"0123456789ABCDEF");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 64max, oct)",	FALSE,"1777777777777777777777",18446744073709551615llu,        "01234567");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n = 64max, bin)",	FALSE,"1111111111111111111111111111111111111111111111111111111111111111", 18446744073709551615UL,"01");\
	if (g_test.flags.test_overflow) {																												\
		print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 64min)     ",	FALSE,                  "-1",                      -1,   "0123456789");	\
	/*	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 64max)     ",	FALSE,"18446744073709551616",  18446744073709551616UL,   "0123456789");*/\
	/*	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n > 64maxdigit)",	FALSE,                  NULL, 999999999999999999999LL,           "01");*/\
	/*	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (n < 64maxdigit)",	FALSE,                  NULL,-999999999999999999999LL,           "01");*/\
	}																																				\
	}}}																																				\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");	\
	print_test_u##BITS##tostrbase("u"#BITS"tostrbase (null base)   ",	SIGNAL_SIGSEGV,             NULL,                  42,               NULL);	\
}

#ifndef c_u8tostrbase
void test_u8tostrbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(8)
#endif

#ifndef c_u16tostrbase
void test_u16tostrbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(16)
#endif

#ifndef c_u32tostrbase
void test_u32tostrbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(32)
#endif

#ifndef c_u64tostrbase
void test_u64tostrbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(64)
#endif

#ifdef __int128
#ifndef c_u128tostrbase
void test_u128tostrbase(void)	{}
#else
DEFINETEST_UINT_TO_STRBASE(128)
#endif
#endif








/*
** ************************************************************************** *|
**                        Convert to Number Operations                        *|
** ************************************************************************** *|
*/

#define DEFINETEST_STR_TO_UINT(BITS) \
void	print_test_strtou##BITS(char const* test_name, int can_segfault,	\
		t_u##BITS expecting,												\
		char const* str)													\
{																			\
	TEST_INIT(u##BITS)														\
	TEST_PERFORM(		strtou##BITS, str)									\
	TEST_PRINT(u##BITS,	strtou##BITS, "str=\"%s\"", str)					\
}																			\
void test_strtou##BITS(void)																										\
{																																	\
/*	| TEST FUNCTION        | TEST NAME                       |CAN SEGV| EXPECTING                 | TEST ARGS					*/	\
	print_test_strtou##BITS("strtou"#BITS" (n = min)       ",	FALSE,                           0, "0"                          );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           1, "1"                          );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           2, "2"                          );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           3, "3"                          );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          10, "10"                         );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          42, "42"                         );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          42, "+42"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         125, "125\n12"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "--9999999"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          85, "   85"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          35, "\f35"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          56, "\n56"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          39, "\r39+"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         138, "\t138"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "- 45678978748f"             );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         111, "111"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         111, "+111"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "-111"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "  + 56"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "++43"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, " + 41dsf-+"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "def58453"                   );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         111, "111,78"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "-\r-397+"                   );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "---84648-+"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "&%64"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "  -2"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           2, "  +2"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           2, "  2"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "!789"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "#45"                        );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "$786"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "&789"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "*4456"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, ".1234"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "/1234"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "%1234"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, ",7"                         );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, ",,789"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "  + 563"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "++4653"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, " + 45631dsf-+"              );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\200 456"                   );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\255\2543"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\0 456"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\255 5"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\\//\v/789"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                       0x123, "0x123"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                      0b1101, "0b1101"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "[124578"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "=0124578"                   );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "_456"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "##4567"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\124578"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\\256"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\\256\\"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, ".456"                       );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\\25627165465413"           );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "\2568"                      );	\
	print_test_strtou##BITS("strtou"#BITS" (n = 8 max)     ",	FALSE,                         255, "255"                        );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtou##BITS("strtou"#BITS" (n < 8 min)     ",	FALSE,                       0, "-1"                         );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 8 max)     ",	FALSE,                     256,  "256"                       );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 8 maxdigit)",	FALSE,                   99999,  "99999"                     );	\
		print_test_strtou##BITS("strtou"#BITS" (n < 8 maxdigit)",	FALSE,                       0, "-99999"                     );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 16)																								\
	{																																\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         456, "456,78"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        5896, "  +5896df"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "-5435"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        5435, "+5435"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        8543, "   8543"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        3541, "\f3541"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        5643, "\n5643"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         397, "\r397"                      );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                       32000, "\v32000"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                         397, "\r397+"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        8513, "\t8513"                     );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        9876, "\v9876-"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                       65435, "65435+--+"                  );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                        5486, "5486helllo"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                       30000, "30000f"                     );	\
	print_test_strtou##BITS("strtou"#BITS" (n = 16max)     ",	FALSE,                       65535, "65535"                      );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtou##BITS("strtou"#BITS" (n < 16min)     ",	FALSE,                       0, "-32769"                     );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 16max)     ",	FALSE,                   65536, "65536"                      );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 16maxdigit)",	FALSE,                 9999999, "9999999"                    );	\
		print_test_strtou##BITS("strtou"#BITS" (n < 16maxdigit)",	FALSE,                       0, "-9999999"                   );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 32)																								\
	{																																\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                      999999,  "999999"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                      999999, "+999999"                    );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                   123456789,  "123456789"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                   123456789, "+123456789"                 );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                  1000000000,  "1000000000"                );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                  1000000000, "+1000000000"                );	\
	print_test_strtou##BITS("strtou"#BITS" (n = 32max)     ",	FALSE,                  4294967295, "4294967295"                 );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtou##BITS("strtou"#BITS" (n < 32min)     ",	FALSE,                       0, "-1"                         );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 32max)     ",	FALSE,              4294967296, "4294967296"                 );	\
		print_test_strtou##BITS("strtou"#BITS" (n > 32maxdigit)",	FALSE,            999999999999, "999999999999"               );	\
		print_test_strtou##BITS("strtou"#BITS" (n < 32maxdigit)",	FALSE,                       0, "-999999999999"              );	\
	}																																\
	if (sizeof(t_u##BITS) * 8 >= 64)																								\
	{																																\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,              25627165465413, "25627165465413"             );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                500000000000, "500000000000"               );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,            6513212312310531, "+6513212312310531"          );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                           0, "-3000000000"                );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                 +3000000000, "+3000000000"                );	\
	print_test_strtou##BITS("strtou"#BITS"                 ",	FALSE,                  3000000000,  "3000000000"                );	\
	print_test_strtou##BITS("strtou"#BITS" (n = 64min)     ",	FALSE,                           0, "0"                          );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtou##BITS("strtou"#BITS" (n < 64min)     ",	FALSE,                       0, "-1"                         );	\
	/*	print_test_strtou##BITS("strtou"#BITS" (n > 64max)     ",	FALSE,  18446744073709551616UL, "18446744073709551616"       );*/\
	/*	print_test_strtou##BITS("strtou"#BITS" (n > 64maxdigit)",	FALSE, 999999999999999999999LL, "999999999999999999999"      );*/\
		print_test_strtou##BITS("strtou"#BITS" (n < 64maxdigit)",	FALSE,                       0, "-999999999999999999999"     );	\
	}																																\
	}}}																																\
	print_test_strtou##BITS("strtos"#BITS" (empty str)     ",	FALSE,                       0, ""                           );		\
	print_test_strtou##BITS("strtos"#BITS" (null str)      ",	SEGV,                        0, NULL                         );		\
}

#ifndef c_strtou8
void test_strtou8(void)	{}
#else
DEFINETEST_STR_TO_UINT(8)
#endif

#ifndef c_strtou16
void test_strtou16(void)	{}
#else
DEFINETEST_STR_TO_UINT(16)
#endif

#ifndef c_strtou32
void test_strtou32(void)	{}
#else
DEFINETEST_STR_TO_UINT(32)
#endif

#ifndef c_strtou64
void test_strtou64(void)	{}
#else
DEFINETEST_STR_TO_UINT(64)
#endif

#ifdef __int128
#ifndef c_strtou128
void test_strtou128(void)	{}
#else
DEFINETEST_STR_TO_UINT(128)
#endif
#endif



#define DEFINETEST_STR_TO_SINT(BITS) \
void	print_test_strtos##BITS(char const* test_name, int can_segfault,	\
		t_s##BITS expecting,												\
		char const* str)													\
{																			\
	TEST_INIT(s##BITS)														\
	TEST_PERFORM(		strtos##BITS, str)									\
	TEST_PRINT(s##BITS,	strtos##BITS, "str=\"%s\"", str)					\
}																			\
void test_strtos##BITS(void)																										\
{																																	\
/*	| TEST FUNCTION       | TEST NAME                         |CAN SEGV| EXPECTING                 | TEST ARGS					*/	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "0"                          );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           1, "1"                          );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          42, "42"                         );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         -42, "-42"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         125, "125\n12"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "--9999999"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          85, "   85"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          35, "\f35"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          56, "\n56"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          39, "\r39+"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         138, "\t138"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "- 45678978748f"             );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         111, "111"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        -111, "-111"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "  + 56"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "++43"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, " + 41dsf-+"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "swag123"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "(-(123"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "[12]123"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "def58453"                   );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          45, "45_"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         111, "111,78"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "-\r-397+"                   );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "---84648-+"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "&%64"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                          -2, "  -2"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           2, "  2"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "!789"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "#45"                        );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "$786"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "&789"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "*4456"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, ".1234"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "/1234"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "%1234"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, ",7"                         );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, ",,789"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "  + 563"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "++4653"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, " + 45631dsf-+"              );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\200 456"                   );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\255\2543"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\0 456"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\255 5"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\\//\v/789"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                       0x123, "0x123"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                      0b1101, "0b1101"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\15124578"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\33124578"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "[124578"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "=0124578"                   );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "_456"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "##4567"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\124578"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\\256"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\\256\\"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, ".456"                       );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\\25627165465413"           );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                           0, "\2568"                      );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 8 min)     ",	FALSE,                        -128, "-128"                       );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 8 max)     ",	FALSE,                         127, " 127"                       );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtos##BITS("strtos"#BITS" (n < 8 min)     ",	FALSE,                    -129, "-129"                       );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 8 max)     ",	FALSE,                     128, " 128"                       );	\
		print_test_strtos##BITS("strtos"#BITS" (n < 8 maxdigit)",	FALSE,                  -99999, "-99999"                     );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 8 maxdigit)",	FALSE,                   99999, " 99999"                     );	\
	}																																\
	if (sizeof(t_s##BITS) * 8 >= 16)																								\
	{																																\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         456, "456,78"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        5896, "  +5896df"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                       -5435, "-5435"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        8543, "   8543"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        3541, "\f3541"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        5643, "\n5643"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         397, "\r397"                      );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                       32000, "\v32000"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                         397, "\r397+"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        8513, "\t8513"                     );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        9876, "\v9876-"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                       65435, "65435+--+"                  );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                        5486, "5486helllo"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                       30000, "30000f"                     );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 16min)     ",	FALSE,                      -32768, "-32768"                     );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 16max)     ",	FALSE,                       32767, " 32767"                     );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtos##BITS("strtos"#BITS" (n < 16min)     ",	FALSE,                  -32769, "-32769"                     );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 16max)     ",	FALSE,                   32768,  "32768"                     );	\
		print_test_strtos##BITS("strtos"#BITS" (n < 16maxdigit)",	FALSE,                -9999999, "-9999999"                   );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 16maxdigit)",	FALSE,                 9999999,  "9999999"                   );	\
	}																																\
	if (sizeof(t_s##BITS) * 8 >= 32)																								\
	{																																\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                     -999999, "-999999"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                      999999,  "999999"                    );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                  -123456789, "-123456789"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                   123456789,  "123456789"                 );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                 -1000000000, "-1000000000"                );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                  1000000000,  "1000000000"                );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 32min)     ",	FALSE,                 -2147483648, "-2147483648"                );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 32max)     ",	FALSE,                  2147483647,  "2147483647"                );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtos##BITS("strtos"#BITS" (n < 32min)     ",	FALSE,             -2147483649, "-2147483649"                );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 32max)     ",	FALSE,              2147483648,  "2147483648"                );	\
		print_test_strtos##BITS("strtos"#BITS" (n < 32maxdigit)",	FALSE,           -999999999999, "-999999999999"              );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 32maxdigit)",	FALSE,            999999999999,  "999999999999"              );	\
	}																																\
	if (sizeof(t_s##BITS) * 8 >= 64)																								\
	{																																\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,              25627165465413,  "25627165465413"            );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,               -500000000000, "-500000000000"              );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,           -6513212312310531, "-6513212312310531"          );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                 -3000000000, "-3000000000"                );	\
	print_test_strtos##BITS("strtos"#BITS"                 ",	FALSE,                  3000000000,  "3000000000"                );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 64min)     ",	FALSE,      -9223372036854775808LL, "-9223372036854775808"       );	\
	print_test_strtos##BITS("strtos"#BITS" (n = 64max)     ",	FALSE,       9223372036854775807LL,  "9223372036854775807"       );	\
	if (g_test.flags.test_overflow) {																								\
		print_test_strtos##BITS("strtos"#BITS" (n < 64min)     ",	FALSE,  -9223372036854775809LL, "-9223372036854775809"       );	\
		print_test_strtos##BITS("strtos"#BITS" (n > 64max)     ",	FALSE,   9223372036854775808LL,  "9223372036854775808"       );	\
/*		print_test_strtos##BITS("strtos"#BITS" (n < 64maxdigit)",	FALSE,-999999999999999999999LL, "-999999999999999999999"     );*/\
/*		print_test_strtos##BITS("strtos"#BITS" (n > 64maxdigit)",	FALSE, 999999999999999999999LL,  "999999999999999999999"     );*/\
	}																																\
	}}}																																\
	print_test_strtos##BITS("strtos"#BITS" (empty str)     ",	FALSE,                           0, ""                           );	\
	print_test_strtos##BITS("strtos"#BITS" (null str)      ",	SEGV,                            0, NULL                         );	\
}

#ifndef c_strtos8
void test_strtos8(void)	{}
#else
DEFINETEST_STR_TO_SINT(8)
#endif

#ifndef c_strtos16
void test_strtos16(void)	{}
#else
DEFINETEST_STR_TO_SINT(16)
#endif

#ifndef c_strtos32
void test_strtos32(void)	{}
#else
DEFINETEST_STR_TO_SINT(32)
#endif

#ifndef c_strtos64
void test_strtos64(void)	{}
#else
DEFINETEST_STR_TO_SINT(64)
#endif

#ifdef __int128
#ifndef c_strtos128
void test_strtos128(void)	{}
#else
DEFINETEST_STR_TO_SINT(128)
#endif
#endif



#define DEFINETEST_STRHEX_TO_UINT(BITS) \
void	print_test_strhextou##BITS(char const* test_name, int can_segfault,	\
		t_u##BITS expecting,												\
		char const* str)													\
{																			\
	TEST_INIT(u##BITS)														\
	TEST_PERFORM(		strhextou##BITS, str)								\
	TEST_PRINT(u##BITS,	strhextou##BITS, "str=\"%s\"", str)					\
}																			\
void	test_strhextou##BITS(void)														\
{																						\
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS			*/	\
/*	TODO */																				\
}																						\

#ifndef c_strhextou8
void test_strhextou8(void)	{}
#else
DEFINETEST_STRHEX_TO_UINT(8)
#endif

#ifndef c_strhextou16
void test_strhextou16(void)	{}
#else
DEFINETEST_STRHEX_TO_UINT(16)
#endif

#ifndef c_strhextou32
void test_strhextou32(void)	{}
#else
DEFINETEST_STRHEX_TO_UINT(32)
#endif

#ifndef c_strhextou64
void test_strhextou64(void)	{}
#else
DEFINETEST_STRHEX_TO_UINT(64)
#endif

#ifdef __int128
#ifndef c_strhextou128
void test_strhextou128(void)	{}
#else
DEFINETEST_STRHEX_TO_UINT(128)
#endif
#endif










/*
** ************************************************************************** *|
**                       Convert Base String to Integer                       *|
** ************************************************************************** *|
*/

#define DEFINETEST_STRBASE_TO_UINT(BITS) \
void	print_test_strbasetou##BITS(char const* test_name, int can_segfault,		\
		t_u##BITS expecting,														\
		char const* number,															\
		char const* base)															\
{																					\
	TEST_INIT(u##BITS)																\
	TEST_PERFORM(		strbasetou##BITS, number, base)								\
	TEST_PRINT(u##BITS,	strbasetou##BITS, "base=\"%s\", str=\"%s\"", base, number)	\
}																					\
void	test_strbasetou##BITS(void)																												\
{																																					\
/*	| TEST FUNCTION          | TEST NAME                             |CAN SEGV|      EXPECTING              | TEST ARGS							*/	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = min, dec)  ",	FALSE,                      0,                   "0",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = min, hex)  ",	FALSE,                      0,                   "0", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = min, oct)  ",	FALSE,                      0,                   "0",         "01234567");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = min, bin)  ",	FALSE,                      0,                   "0",               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      1,                   "1",               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "1",               "+1");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "m",                "m");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "m",                "m");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                  "mm",                "m");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                 "mmm",                "m");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     42,              "101010",               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,              "101012",               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "m",              "mom");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "o",              "mom");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     15,                   "F", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     42,                  "2A", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                   "0",              "0az");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                    111,                 "aaa",       "_abcdefghi");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     63,                "rdmm",              "mdr");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                    100,               "|*_*|",              "*|_");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     13,                ".._.",               "_.");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                     42,                  "42",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                  "42",       "012345678-");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                  "42",       "012345678+");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 8 max, dec)",	FALSE,                    255,                 "255",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 8 max, hex)",	FALSE,                    255,                  "FF", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 8 max, oct)",	FALSE,                    255,                 "377",         "01234567");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 8 max, bin)",	FALSE,                    255,            "11111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 8 min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 8 max)     ",	FALSE,                256,                 "256",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 8 maxdigit)",	FALSE,             -99999,              "-99999",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 8 maxdigit)",	FALSE,              99999,               "99999",       "0123456789");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 16)																												\
	{																																				\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                  12345,               "12345",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,               "12345",       "012345678-");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,               "12345",       "012345678+");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                      0,                 "999",       "0123456389");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                    999,                 "999",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                  10007,               "c===3",       "=cbadef389");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                   1234,                "swag",       "0swag56789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                   1000,                 "3e8", "0123456789abcdef");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 16max, dec)",	FALSE,                  65535,               "65535",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 16max, hex)",	FALSE,                  65535,                "FFFF", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 16max, oct)",	FALSE,                  65535,              "177777",         "01234567");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 16max, bin)",	FALSE,                  65535,    "1111111111111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 16min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 16max)     ",	FALSE,              65536,               "65536",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 16maxdigit)",	FALSE,           -9999999,            "-9999999",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 16maxdigit)",	FALSE,            9999999,             "9999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 32)																												\
	{																																				\
	print_test_strbasetou##BITS("strbasetou"#BITS"                 ",	FALSE,                +987123,              "*xurin",       "grincheux*");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 32max, dec)",	FALSE,             4294967295,          "4294967295",       "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 32max, hex)",	FALSE,             4294967295,            "FFFFFFFF", "0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 32max, oct)",	FALSE,             4294967295,         "37777777777",         "01234567");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 32max, bin)",	FALSE,             4294967295,"11111111111111111111111111111111",   "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 32min)     ",	FALSE,                 -1,                  "-1",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 32max)     ",	FALSE,         4294967296,          "4294967296",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 32maxdigit)",	FALSE,      -999999999999,       "-999999999999",       "0123456789");	\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n > 32maxdigit)",	FALSE,       999999999999,        "999999999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_u##BITS) * 8 >= 64)																												\
	{																																				\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 64max, dec)",	FALSE, 18446744073709551615UL,  "18446744073709551615",      "0123456789");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 64max, hex)",	FALSE, 18446744073709551615UL,      "FFFFFFFFFFFFFFFF","0123456789ABCDEF");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 64max, oct)",	FALSE, 18446744073709551615UL,"1777777777777777777777",        "01234567");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (n = 64max, bin)",	FALSE, 18446744073709551615UL,"1111111111111111111111111111111111111111111111111111111111111111","01");\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetou##BITS("strbasetou"#BITS" (n < 64min)     ",FALSE,                      -1,                    "-1",  "0123456789");	\
	/*	print_test_strbasetou##BITS("strbasetou"#BITS" (n > 64max)     ",FALSE,  18446744073709551616UL,  "18446744073709551616",  "0123456789");*/	\
	/*	print_test_strbasetou##BITS("strbasetou"#BITS" (n < 64maxdigit)",FALSE,-999999999999999999999LL,"-999999999999999999999",  "0123456789");*/	\
	/*	print_test_strbasetou##BITS("strbasetou"#BITS" (n > 64maxdigit)",FALSE, 999999999999999999999LL, "999999999999999999999",  "0123456789");*/	\
	}																																				\
	}}}																																				\
	print_test_strbasetou##BITS("strbasetou"#BITS" (empty base)    ",	FALSE,                      0,                  "01",                 "");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (empty number)  ",	FALSE,                      0,                    "",               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (both empty)    ",	FALSE,                      0,                    "",                 "");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (null base)     ",	SEGV,                       0,                  "01",               NULL);	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (null number)   ",	SEGV,                       0,                  NULL,               "01");	\
	print_test_strbasetou##BITS("strbasetou"#BITS" (both null)     ",	SEGV,                       0,                  NULL,               NULL);	\
}

#ifndef c_strbasetou8
void test_strbasetou8(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(8)
#endif

#ifndef c_strbasetou16
void test_strbasetou16(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(16)
#endif

#ifndef c_strbasetou32
void test_strbasetou32(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(32)
#endif

#ifndef c_strbasetou64
void test_strbasetou64(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(64)
#endif

#ifdef __int128
#ifndef c_strbasetou128
void test_strbasetou128(void)	{}
#else
DEFINETEST_STRBASE_TO_UINT(128)
#endif
#endif



#define DEFINETEST_STRBASE_TO_SINT(BITS) \
void	print_test_strbasetos##BITS(char const* test_name, int can_segfault,		\
		t_s##BITS expecting,														\
		char const* number,															\
		char const* base)															\
{																					\
	TEST_INIT(s##BITS)																\
	TEST_PERFORM(		strbasetos##BITS, number, base)								\
	TEST_PRINT(s##BITS,	strbasetos##BITS, "base=\"%s\", str=\"%s\"", base, number)	\
}																					\
void	test_strbasetos##BITS(void)																													\
{																																					\
/*	| TEST FUNCTION            | TEST NAME                           |CAN SEGV|  EXPECTING          | TEST ARGS									*/	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "0",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     1,                    "1",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     2,                   "10",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "1",               "+1");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "m",                "m");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                   "mm",                "m");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                  "mmm",                "m");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    42,               "101010",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,               "101012",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "m",              "mom");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "o",              "mom");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    42,                   "2A", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "0",              "0az");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                   111,                  "aaa",       "_abcdefghi");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                  -111,                 "-aaa",       "_abcdefghi");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                   -15,                   "-F", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    63,                 "rdmm",              "mdr");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                   100,                "|*_*|",              "*|_");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    13,                 ".._.",               "_.");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    42,                   "2A", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                    42,                   "42",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "2",       "012345678-");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                    "2",       "012345678+");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 min, dec)",	FALSE,                  -128,                 "-128",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 max, dec)",	FALSE,                   127,                  "127",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 min, hex)",	FALSE,                  -128,                  "-80", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 max, hex)",	FALSE,                   127,                   "7F", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 min, oct)",	FALSE,                  -128,                 "-200",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 max, oct)",	FALSE,                   127,                  "177",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 min, bin)",	FALSE,                  -128,            "-10000000",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 8 max, bin)",	FALSE,                   127,              "1111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 8 min)     ",	FALSE,              -129,                 "-129",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 8 max)     ",	FALSE,               128,                  "128",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 8 maxdigit)",	FALSE,            -99999,               "-99999",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 8 maxdigit)",	FALSE,             99999,                "99999",       "0123456789");	\
	}																																				\
	if (sizeof(t_s##BITS) * 8 >= 16)																												\
	{																																				\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                 12345,                "12345",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                "12345",       "012345678-");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                "12345",       "012345678+");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                     0,                  "999",       "01+3456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                 10007,                "c===3",       "=cbadef389");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                  1234,                 "swag",       "0swag56789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,                 -1000,                 "-3e8", "0123456789abcdef");	\
	print_test_strbasetos##BITS("strbasetos"#BITS"                 ",	FALSE,               +987123,               "*xurin",       "grincheux*");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16min, dec)",	FALSE,                -32768,               "-32768",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16max, dec)",	FALSE,                 32767,                "32767",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16min, hex)",	FALSE,                -32768,                "-8000", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16max, hex)",	FALSE,                 32767,                 "7FFF", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16min, oct)",	FALSE,                -32768,              "-100000",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16max, oct)",	FALSE,                 32767,                "77777",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16min, bin)",	FALSE,                -32768,    "-1000000000000000",               "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 16max, bin)",	FALSE,                 32767,      "111111111111111",               "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 16min)     ",	FALSE,            -32769,               "-32769",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 16max)     ",	FALSE,             32768,                "32768",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 16maxdigit)",	FALSE,          -9999999,             "-9999999",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 16maxdigit)",	FALSE,           9999999,              "9999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_s##BITS) * 8 >= 32)																												\
	{																																				\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32min, dec)",	FALSE,           -2147483648,          "-2147483648",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32max, dec)",	FALSE,            2147483647,           "2147483647",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32min, hex)",	FALSE,           -2147483648,            "-80000000", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32max, hex)",	FALSE,            2147483647,             "7FFFFFFF", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32min, oct)",	FALSE,           -2147483648,         "-20000000000",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32max, oct)",	FALSE,            2147483647,          "17777777777",         "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32min, bin)",	FALSE,           -2147483648,"-10000000000000000000000000000000",   "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 32max, bin)",	FALSE,            2147483647,  "1111111111111111111111111111111",   "01");	\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 32min)     ",	FALSE,       -2147483649,          "-2147483649",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 32max)     ",	FALSE,        2147483648,           "2147483648",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 32maxdigit)",	FALSE,     -999999999999,        "-999999999999",       "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 32maxdigit)",	FALSE,      999999999999,         "999999999999",       "0123456789");	\
	}																																				\
	if (sizeof(t_s##BITS) * 8 >= 64)																												\
	{																																				\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64min, dec)",	FALSE,  -9223372036854775808, "-9223372036854775808",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64max, dec)",	FALSE,   9223372036854775807,  "9223372036854775807",       "0123456789");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64min, hex)",	FALSE,  -9223372036854775808,    "-8000000000000000", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64max, hex)",	FALSE,   9223372036854775807,     "7FFFFFFFFFFFFFFF", "0123456789ABCDEF");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64min, oct)",	FALSE,  -9223372036854775808,"-1000000000000000000000",       "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64max, oct)",	FALSE,   9223372036854775807,  "777777777777777777777",       "01234567");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64min, bin)",	FALSE,  -9223372036854775808,"-1000000000000000000000000000000000000000000000000000000000000000","01");\
	print_test_strbasetos##BITS("strbasetos"#BITS" (n = 64max, bin)",	FALSE,   9223372036854775807,  "111111111111111111111111111111111111111111111111111111111111111","01");\
	if (g_test.flags.test_overflow) {																												\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n > 64max)     ",FALSE,   9223372036854775808,   "9223372036854775808",    "0123456789");	\
		print_test_strbasetos##BITS("strbasetos"#BITS" (n < 64min)     ",FALSE,  -9223372036854775808,  "-9223372036854775808",    "0123456789");	\
	/*	print_test_strbasetos##BITS("strbasetos"#BITS" (n < 64maxdigit)",FALSE, 999999999999999999999, "999999999999999999999",    "0123456789");*/	\
	/*	print_test_strbasetos##BITS("strbasetos"#BITS" (n > 64maxdigit)",FALSE,-999999999999999999999,"-999999999999999999999",    "0123456789");*/	\
	}																																				\
	}}}																																				\
	print_test_strbasetos##BITS("strbasetos"#BITS" (empty base)    ",	FALSE,                     0,                   "01",                "");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (empty number)  ",	FALSE,                     0,                     "",              "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (both empty)    ",	FALSE,                     0,                     "",                "");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (null base)     ",	SEGV,                      0,                   "01",              NULL);	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (null number)   ",	SEGV,                      0,                   NULL,              "01");	\
	print_test_strbasetos##BITS("strbasetos"#BITS" (both null)     ",	SEGV,                      0,                   NULL,              NULL);	\
}

#ifndef c_strbasetos8
void test_strbasetos8(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(8)
#endif

#ifndef c_strbasetos16
void test_strbasetos16(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(16)
#endif

#ifndef c_strbasetos32
void test_strbasetos32(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(32)
#endif

#ifndef c_strbasetos64
void test_strbasetos64(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(64)
#endif

#ifdef __int128
#ifndef c_strbasetos128
void test_strbasetos128(void)	{}
#else
DEFINETEST_STRBASE_TO_SINT(128)
#endif
#endif



// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
// Resets the clang warning settings back to normal
#pragma clang diagnostic pop
#pragma clang diagnostic pop



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_int(void)
{
	print_suite_title("libccc/int");

	print_nonstd();

	test_u8tostr();
	test_u16tostr();
	test_u32tostr();
	test_u64tostr();
	test_u128tostr();

	test_s8tostr();
	test_s16tostr();
	test_s32tostr();
	test_s64tostr();
	test_s128tostr();


	test_u8tostrhex();
	test_u16tostrhex();
	test_u32tostrhex();
	test_u64tostrhex();
	test_u128tostrhex();
/* TODO
	test_u8tostrhex();
	test_u16tostrhex();
	test_u32tostrhex();
	test_u64tostrhex();
	test_u128tostrhex();
	*/


	test_s8tostrbase();
	test_s16tostrbase();
	test_s32tostrbase();
	test_s64tostrbase();
	test_s128tostrbase();

	test_u8tostrbase();
	test_u16tostrbase();
	test_u32tostrbase();
	test_u64tostrbase();
	test_u128tostrbase();



	test_strtos8();
	test_strtos16();
	test_strtos32();
	test_strtos64();
	test_strtos128();

	test_strtou8();
	test_strtou16();
	test_strtou32();
	test_strtou64();
	test_strtou128();


//	test_strhextou8();
//	test_strhextou16();
//	test_strhextou32();
//	test_strhextou64();
//	test_strhextou128();


	test_strbasetos8();
	test_strbasetos16();
	test_strbasetos32();
	test_strbasetos64();
	test_strbasetos128();

	test_strbasetou8();
	test_strbasetou16();
	test_strbasetou32();
	test_strbasetou64();
	test_strbasetou128();

	return (OK);
}
