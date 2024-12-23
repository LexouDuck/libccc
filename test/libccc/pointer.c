
#include "libccc.h"
#include "libccc/pointer.h"
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



/*
** ************************************************************************** *|
**                        Convert Integers to Strings                         *|
** ************************************************************************** *|
*/

#ifndef c_sizetostr
void test_sizetostr(void)	{}
#warning "sizetostr() test suite function defined, but the function isn't defined."
#else
void	print_test_sizetostr(char const* test_name, t_testflags flags,
		char const* expecting,
		t_size number)
{
	TEST_INIT(str)
	TEST_PERFORM(	sizetostr, number)
	TEST_PRINT(str,	sizetostr, "%zu", number)
	TEST_FREE()
}
void	test_sizetostr(void)
{
//	| TEST FUNCTION       | TEST NAME                    |TESTFLAG| EXPECTING              | TEST ARGS
	print_test_sizetostr("sizetostr               ",	FALSE,                      "1", 1                     );
	print_test_sizetostr("sizetostr               ",	FALSE,                     "42", 42                    );
	print_test_sizetostr("sizetostr               ",	FALSE,                    "777", 777                   );
	print_test_sizetostr("sizetostr               ",	FALSE,                  "10000", 10000                 );
	print_test_sizetostr("sizetostr               ",	FALSE,              "123456789", 123456789             );
	print_test_sizetostr("sizetostr (n = min)     ",	FALSE,                      "0", 0                     );
	switch (sizeof(t_size))
	{
		case 1:	print_test_sizetostr("sizetostr (n = max)     ",	FALSE,                    "255", 255                   ); break;
		case 2:	print_test_sizetostr("sizetostr (n = max)     ",	FALSE,                  "65535", 65535                 ); break;
		case 4:	print_test_sizetostr("sizetostr (n = max)     ",	FALSE,             "4294967295", 4294967295            ); break;
		case 8:	print_test_sizetostr("sizetostr (n = max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL); break;
	}
	if (g_test.config.test_overflow)
	{
		print_test_sizetostr("sizetostr (n < min)     ",	FALSE,                     "-1", -1                    );
		switch (sizeof(t_size))
		{
			case 1:	print_test_sizetostr("sizetostr (n > max)     ",	FALSE,                    "256", 256                   ); break;
			case 2:	print_test_sizetostr("sizetostr (n > max)     ",	FALSE,                  "65536", 65536                 ); break;
			case 4:	print_test_sizetostr("sizetostr (n > max)     ",	FALSE,             "4294967296", 4294967296            ); break;
			case 8:	/*print_test_sizetostr("sizetostr (n > max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL);*/ break;
		}
		/*print_test_sizetostr("sizetostr (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);*/
		/*print_test_sizetostr("sizetostr (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);*/
	}
}
#endif



/*
** ************************************************************************** *|
**                        Convert to Number Operations                        *|
** ************************************************************************** *|
*/

#ifndef c_strtosize
void test_strtosize(void)	{}
#warning "strtosize() test suite function defined, but the function isn't defined."
#else
void	print_test_strtosize(char const* test_name, t_testflags flags,
		t_size expecting,
		char const* str)
{
	TEST_INIT(size)
	TEST_PERFORM(	strtosize, str)
	TEST_PRINT(size,strtosize, "str=\"%s\"", str)
}
void	test_strtosize(void)
{
//	| TEST FUNCTION      | TEST NAME                     |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_strtosize("strtosize",                       FALSE,                           0, "0"                          );
	print_test_strtosize("strtosize",                       FALSE,                           1, "1"                          );
	print_test_strtosize("strtosize",                       FALSE,                          42, "42"                         );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-42"                        );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-5435"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, "--9999999"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-2147483648"                );
	print_test_strtosize("strtosize",                       FALSE,                  2147483647, "2147483647"                 );
	print_test_strtosize("strtosize",                       FALSE,                        8543, "   8543"                    );
	print_test_strtosize("strtosize",                       FALSE,                        3541, "\f3541"                     );
	print_test_strtosize("strtosize",                       FALSE,                        5643, "\n5643"                     );
	print_test_strtosize("strtosize",                       FALSE,                         397, "\r397+"                     );
	print_test_strtosize("strtosize",                       FALSE,                        8513, "\t8513"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "- 45678978748f"             );
	print_test_strtosize("strtosize",                       FALSE,                           0, "swag123"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "(-(123"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "[12]123"                    );
	print_test_strtosize("strtosize",                       FALSE,                          45, "45_"                        );
	print_test_strtosize("strtosize",                       FALSE,                        9876, "\v9876-"                    );
	print_test_strtosize("strtosize",                       FALSE,                       65435, "65435+--+"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "def58453"                   );
	print_test_strtosize("strtosize",                       FALSE,                        5486, "5486helllo"                 );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\f-3541"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\n-5643"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-\r-397+"                   );
	print_test_strtosize("strtosize",                       FALSE,                           0, "---84648-+"                 );
	print_test_strtosize("strtosize",                       FALSE,                           0, "&%64"                       );
	print_test_strtosize("strtosize",                       FALSE,                         125, "125\n12"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "  -2"                       );
	print_test_strtosize("strtosize",                       FALSE,                           2, "  2"                        );
	print_test_strtosize("strtosize",                       FALSE,                           0, "!789"                       );
	print_test_strtosize("strtosize",                       FALSE,                           0, "#45"                        );
	print_test_strtosize("strtosize",                       FALSE,                           0, "$786"                       );
	print_test_strtosize("strtosize",                       FALSE,                           0, "&789"                       );
	print_test_strtosize("strtosize",                       FALSE,                           0, "*4456"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, ".1234"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, "/1234"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, "%1234"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, ",7"                         );
	print_test_strtosize("strtosize",                       FALSE,                           0, ",,789"                      );
	print_test_strtosize("strtosize",                       FALSE,                         456, "456,78"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, ".456"                       );
	print_test_strtosize("strtosize",                       FALSE,                        5896, "  +5896df"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "  + 563"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "++4653"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, " + 45631dsf-+"              );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\200 456"                   );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\255\2543"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\0 456"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\255 5"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\\//\v/789"                 );
	print_test_strtosize("strtosize",                       FALSE,                           0, "0x123"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, "0b1101"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\15124578"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\33124578"                  );
	print_test_strtosize("strtosize",                       FALSE,                           0, "[124578"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "=0124578"                   );
	print_test_strtosize("strtosize",                       FALSE,                           0, "_456"                       );
	print_test_strtosize("strtosize",                       FALSE,                           0, "##4567"                     );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\124578"                    );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\\256"                      );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\\256\\"                    );
	print_test_strtosize("strtosize",                       FALSE,              25627165465413, "25627165465413"             );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\\25627165465413"           );
	print_test_strtosize("strtosize",                       FALSE,                           0, "\2568"                      );
	print_test_strtosize("strtosize",                       FALSE,                       30000, "30000f"                     );
	print_test_strtosize("strtosize",                       FALSE,                         000, "-500000000000"              );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-6513212312310531"          );
	print_test_strtosize("strtosize",                       FALSE,                  2147483648,  "2147483648"                );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-2147483649"                );
	print_test_strtosize("strtosize",                       FALSE,                  3000000000,  "3000000000"                );
	print_test_strtosize("strtosize",                       FALSE,                           0, "-3000000000"                );
	print_test_strtosize("strtosize (n = max)     ",        FALSE,      18446744073709551615UL, "18446744073709551615"       );
	print_test_strtosize("strtosize (n = min)     ",        FALSE,                           0, "0"                          );
	print_test_strtosize("strtosize (empty str)   ",        FALSE,                           0, ""                           );
	print_test_strtosize("strtosize (null str)    ",        ALLOW_SIGSEGV,                  0, NULL                         );
	if (g_test.config.test_overflow)
	{
		print_test_strtosize("strtosize (n < min)     ",    FALSE,                           0, "-1"                         );
	/*	print_test_strtosize("strtosize (n > max)     ",    FALSE,      18446744073709551616UL, "18446744073709551616"       );*/
	/*	print_test_strtosize("strtosize (n > maxdigit)",    FALSE,     999999999999999999999LL, "999999999999999999999"      );*/
		print_test_strtosize("strtosize (n < maxdigit)",    FALSE,                           0, "-999999999999999999999"     );
	}
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



int		testsuite_pointer(void)
{
	print_suite_title("libccc/pointer");

	print_nonstd();


	test_sizetostr();

	test_strtosize();

	return (OK);
}
