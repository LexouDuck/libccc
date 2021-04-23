
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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wliteral-range"



/*
** ************************************************************************** *|
**                     Convert Floating-point to Strings                      *|
** ************************************************************************** *|
*/

#define DEFINETEST_FLOAT_TO_STR(TYPE) \
void	print_test_##TYPE##tostr(char const* test_name, int can_segfault,					\
		char const* expecting,																\
		t_##TYPE number,																	\
		t_u8 precision)																		\
{																							\
	TEST_PERFORM_RESULT(TYPE##tostr, number, precision)									\
	print_test_str(test_name, "_"#TYPE"tostr", result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);															\
	TEST_PRINT_ARGS("%+#.*g, p=%u", precision, number, precision)							\
}																							\
void	test_##TYPE##tostr(void)																								\
{																																\
/*	| TEST FUNCTION           | TEST NAME                     |CAN SEGV| EXPECTING              | TEST ARGS				*/		\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                       "1", 1.                   , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                     "1.0", 1.                   , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                    "1.00", 1.                   , 2);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "1.000", 1.                   , 3);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                  "1.0000", 1.                   , 4);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                       "2", 2.                   , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                     "2.0", 2.                   , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,      "2.0000000000000000", 2.                   , 16);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                       "0", 0.                   , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                     "0.0", 0.                   , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "0.000", 0.                   , 3);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                      "-1", -1.                  , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                    "-1.0", -1.                  , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "-1.00", -1.                  , 2);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                      "42", 42.                  , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                    "42.0", 42.                  , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "42.00", 42.                  , 2);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                     "-42", -42.                 , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "-42.0", -42.                 , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                  "-42.00", -42.                 , 2);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                     "0.5", 0.5                  , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "0.001", 0.001                , 3);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                 "0.33333", 0.33333333           , 5);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,               "0.3333333", 0.33333333           , 7);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                  "-777.1", -777.1               , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                "3.141592", 3.141592             , 6);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "10000", 10000.               , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                 "10000.0", 10000.               , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,               "10000.000", 10000.               , 3);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,      "10000.000000000000", 10000.               , 12);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "7e+09", 6969696969.          , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                  "-7e+09",-6969696969.          , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                   "7e+11", 696969696969.        , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                  "-7e+11",-696969696969.        , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,             "0.000000003", 0.000000003          , 9);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,            "-0.000000003",-0.000000003          , 9);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,            "0.0000000030", 0.000000003          , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,           "-0.0000000030",-0.000000003          , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                "1.414214", 0x1.6A09E667F3BCDp+0 , 6);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                "3.141593", 0x1.921FB54442D18p+1 , 6);	\
	print_test_##TYPE##tostr(#TYPE"tostr               ",	FALSE,                "6.283185", 0x1.921FB54442D18p+2 , 6);	\
/*// TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable */			\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64max)   ",	FALSE,        "9.2233720369e+18", 9223372036854775807.  , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n = 64min)   ",	FALSE,       "-9.2233720369e+18",-9223372036854775808.  , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > 64max)   ",	FALSE,        "9.2233720369e+18", 9223372036854775808.  , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < 64min)   ",	FALSE,       "-9.2233720369e+18",-9223372036854775809.  , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > maxdigit)",	FALSE,           "1.0000000e+21", 999999999999999999999., 7);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < maxdigit)",	FALSE,          "-1.0000000e+21",-999999999999999999999., 7);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?               "123456792" :               "123456789"), 123456789.           , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?             "123456792.0" :             "123456789.0"), 123456789.           , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?               "3.1415927" :               "3.1415927"), 0x1.921FB54442D18p+1 , 7);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?              "3.14159274" :              "3.14159265"), 0x1.921FB54442D18p+1 , 8);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?              "2.71828175" :              "2.71828183"), 0x1.5BF0A8B145769p+1 , 8);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?          "1.414213538170" :          "1.414213562373"), 0x1.6A09E667F3BCDp+0 , 12);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?                "69696968" :                "69696969"), 69696969.            , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?               "-69696968" :               "-69696969"),-69696969.            , 0);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ? "1.00000001686238353e-16" : "9.99999999999999979e-17"), 0.0000000000000001   , 17);	\
	print_test_##TYPE##tostr(#TYPE"tostr (precision)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?"-1.00000001686238353e-16" :"-9.99999999999999979e-17"),-0.0000000000000001   , 17);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > +huge)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?        "1.0000000200e+20" :        "1.0000000000e+20"), 1.0e20               , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < -huge)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?       "-1.0000000200e+20" :       "-1.0000000000e+20"),-1.0e20               , 10);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < +tiny)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?         "9.999999683e-21" :         "1.000000000e-20"), 1.0e-20              , 9);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > -tiny)   ",	FALSE,(sizeof(t_##TYPE) <= 4 ?        "-9.999999683e-21" :        "-1.000000000e-20"),-1.0e-20              , 9);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > +inf)    ",	FALSE,               "+INFINITY", 1.0e100               , 5);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < -inf)    ",	FALSE,               "-INFINITY",-1.0e100               , 5);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n > +inf)    ",	FALSE,               "+INFINITY", 1.0e1000              , 5);	\
	print_test_##TYPE##tostr(#TYPE"tostr (n < -inf)    ",	FALSE,               "-INFINITY",-1.0e1000              , 5);	\
	print_test_##TYPE##tostr(#TYPE"tostr (+inf)        ",	FALSE,               "+INFINITY", INFINITY              , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr (-inf)        ",	FALSE,               "-INFINITY",-INFINITY              , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr (+nan)        ",	FALSE,                     "NAN", NAN                   , 1);	\
	print_test_##TYPE##tostr(#TYPE"tostr (-nan)        ",	FALSE,                     "NAN",-NAN                   , 1);	\
}

#ifndef c_f32tostr
void test_f32tostr(void)	{}
#else
DEFINETEST_FLOAT_TO_STR(f32)
#endif

#ifndef c_f64tostr
void test_f64tostr(void)	{}
#else
DEFINETEST_FLOAT_TO_STR(f64)
#endif

#if !defined(c_f80tostr) || !defined(__float80)
void test_f80tostr(void)	{}
#else
DEFINETEST_FLOAT_TO_STR(f80)
#endif

#if !defined(c_f128tostr) || !defined(__float128)
void test_f128tostr(void)	{}
#else
DEFINETEST_FLOAT_TO_STR(f128)
#endif

#ifndef c_floattostr
void test_floattostr(void)	{}
#else
DEFINETEST_FLOAT_TO_STR(float)
#endif

/*

#ifndef c_f32tostrexp
void test_f32tostrexp(void)	{}
#else
DEFINETEST_FLOAT_TO_STREXP(f32)
#endif

#ifndef c_f64tostrexp
void test_f64tostrexp(void)	{}
#else
DEFINETEST_FLOAT_TO_STREXP(f64)
#endif

#ifn defined(c_f80tostrexp) && defined(__float80)
void test_f80tostrexp(void)	{}
#else
DEFINETEST_FLOAT_TO_STREXP(f80)
#endif

#ifn defined(c_f128tostrexp) && defined(__float128)
void test_f128tostrexp(void)	{}
#else
DEFINETEST_FLOAT_TO_STREXP(f128)
#endif

#ifndef c_floattostrexp
void test_floattostrexp(void)	{}
#else
DEFINETEST_FLOAT_TO_STREXP(float)
#endif



#ifndef c_f32tostrdec
void test_f32tostrdec(void)	{}
#else
DEFINETEST_FLOAT_TO_STRDEC(f32)
#endif

#ifndef c_f64tostrdec
void test_f64tostrdec(void)	{}
#else
DEFINETEST_FLOAT_TO_STRDEC(f64)
#endif

#ifn defined(c_f80tostrdec) && defined(__float80)
void test_f80tostrdec(void)	{}
#else
DEFINETEST_FLOAT_TO_STRDEC(f80)
#endif

#ifn defined(c_f128tostrdec) && defined(__float128)
void test_f128tostrdec(void)	{}
#else
DEFINETEST_FLOAT_TO_STRDEC(f128)
#endif

#ifndef c_floattostrdec
void test_floattostrdec(void)	{}
#else
DEFINETEST_FLOAT_TO_STRDEC(float)
#endif



#ifndef c_f32tostrhex
void test_f32tostrhex(void)	{}
#else
DEFINETEST_FLOAT_TO_STRHEX(f32)
#endif

#ifndef c_f64tostrhex
void test_f64tostrhex(void)	{}
#else
DEFINETEST_FLOAT_TO_STRHEX(f64)
#endif

#ifn defined(c_f80tostrhex) && defined(__float80)
void test_f80tostrhex(void)	{}
#else
DEFINETEST_FLOAT_TO_STRHEX(f80)
#endif

#ifn defined(c_f128tostrhex) && defined(__float128)
void test_f128tostrhex(void)	{}
#else
DEFINETEST_FLOAT_TO_STRHEX(f128)
#endif

#ifndef c_floattostrhex
void test_floattostrhex(void)	{}
#else
DEFINETEST_FLOAT_TO_STRHEX(float)
#endif



#ifndef c_f32tostrbin
void test_f32tostrbin(void)	{}
#else
DEFINETEST_FLOAT_TO_STRBIN(f32) // TODO
#endif

#ifndef c_f64tostrbin
void test_f64tostrbin(void)	{}
#else
DEFINETEST_FLOAT_TO_STRBIN(f64) // TODO
#endif

#ifn defined(c_f80tostrbin) && defined(__float80)
void test_f80tostrbin(void)	{}
#else
DEFINETEST_FLOAT_TO_STRBIN(f80) // TODO
#endif

#ifn defined(c_f128tostrbin) && defined(__float128)
void test_f128tostrbin(void)	{}
#else
DEFINETEST_FLOAT_TO_STRBIN(f128) // TODO
#endif

#ifndef c_floattostrbin
void test_floattostrbin(void)	{}
#else
DEFINETEST_FLOAT_TO_STRBIN(float) // TODO
#endif

*/

/*
** ************************************************************************** *|
**                     Convert Strings to Floating-point                      *|
** ************************************************************************** *|
*/

#define DEFINETEST_STR_TO_FLOAT(TYPE) \
void	print_test_strto##TYPE(char const* test_name, int can_segfault,					\
		t_##TYPE expecting,																	\
		char const* str)																	\
{																							\
	TEST_PERFORM_RESULT_TYPE(t_##TYPE, strto##TYPE, str)									\
	print_test_##TYPE(test_name, "_strto"#TYPE, result_libccc, expecting, can_segfault);	\
	print_timer_result(&t, FALSE);															\
	TEST_PRINT_ARGS_ESCAPED(str)															\
}																							\
void	test_strto##TYPE(void)																									\
{																																	\
/*	| TEST FUNCTION  | TEST NAME                              |CAN SEGV| EXPECTING                | TEST ARGS					*/	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          0., "0"                          );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          1., "1"                          );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          2., "2"                          );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          0., "0."                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          1., "1."                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          2., "2."                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          0., "0.0"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          1., "1.0"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          2., "2.0"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          0., "0.00"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          1., "1.00"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          2., "2.00"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         42., "42"                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        -42., "-42"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        +42., "+42"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         42., "42."                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        -42., "-42."                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        +42., "+42."                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         42., "42.0"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        -42., "-42.0"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        +42., "+42.0"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       -5435, "-5435"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        3.25, "+3.25"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        3.69, "3.69"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       -4.07, "-4.07"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "--9999999"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                -2147483648., "-2147483648"                );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                 2147483647., "2147483647"                 );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        8543, "   8543"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        3541, "\f3541"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        5643, "\n5643"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         397, "\r397+"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        8513, "\t8513"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "- 45678978748f"             );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "swag123"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,        0x1.921FB54442D18p+1, "3.141592653589793238462643383279502884197169399375105820974");	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,        0x1.921FB54442D18p+2, "6.283185307179586476925286766559005768394338798750211641949");	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,        0x1.45F306DC9C883p-2, "0.318309886183790671537767526745028724068919291480912897495");	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,        0x1.45F306DC9C883p-3, "0.159154943091895335768883763372514362034459645740456448747");	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e0,   "1e0"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e1,   "1e1"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e2,   "1e2"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e3,   "1e3"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e01,  "1e01"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e02,  "1e02"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e03,  "1e03"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e10,  "1e10"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e11,  "1e11"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e12,  "1e12"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+0,  "1e+0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+1,  "1e+1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+2,  "1e+2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+3,  "1e+3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+01, "1e+01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+02, "1e+02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+03, "1e+03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+10, "1e+10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+11, "1e+11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+12, "1e+12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-0,  "1e-0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-1,  "1e-1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-2,  "1e-2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-3,  "1e-3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-01, "1e-01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-02, "1e-02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-03, "1e-03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-10, "1e-10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-11, "1e-11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-12, "1e-12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e0,  " 1e0"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e1,  " 1e1"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e2,  " 1e2"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e3,  " 1e3"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e01, " 1e01"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e02, " 1e02"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e03, " 1e03"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e10, " 1e10"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e11, " 1e11"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e12, " 1e12"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+0, " 1e+0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+1, " 1e+1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+2, " 1e+2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+3, " 1e+3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+01," 1e+01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+02," 1e+02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+03," 1e+03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+10," 1e+10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+11," 1e+11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e+12," 1e+12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-0, " 1e-0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-1, " 1e-1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-2, " 1e-2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-3, " 1e-3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-01," 1e-01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-02," 1e-02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-03," 1e-03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-10," 1e-10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-11," 1e-11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                       1e-12," 1e-12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e0,   "+1e0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e1,   "+1e1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e2,   "+1e2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e3,   "+1e3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e01,  "+1e01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e02,  "+1e02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e03,  "+1e03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e10,  "+1e10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e11,  "+1e11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e12,  "+1e12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+0,  "+1e+0"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+1,  "+1e+1"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+2,  "+1e+2"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+3,  "+1e+3"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+01, "+1e+01"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+02, "+1e+02"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+03, "+1e+03"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+10, "+1e+10"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+11, "+1e+11"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e+12, "+1e+12"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-0,  "+1e-0"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-1,  "+1e-1"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-2,  "+1e-2"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-3,  "+1e-3"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-01, "+1e-01"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-02, "+1e-02"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-03, "+1e-03"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-10, "+1e-10"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-11, "+1e-11"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      +1e-12, "+1e-12"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e0,   "-1e0"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e1,   "-1e1"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e2,   "-1e2"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e3,   "-1e3"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e01,  "-1e01"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e02,  "-1e02"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e03,  "-1e03"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e10,  "-1e10"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e11,  "-1e11"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e12,  "-1e12"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+0,  "-1e+0"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+1,  "-1e+1"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+2,  "-1e+2"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+3,  "-1e+3"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+01, "-1e+01"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+02, "-1e+02"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+03, "-1e+03"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+10, "-1e+10"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+11, "-1e+11"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e+12, "-1e+12"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-0,  "-1e-0"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-1,  "-1e-1"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-2,  "-1e-2"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-3,  "-1e-3"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-01, "-1e-01"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-02, "-1e-02"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-03, "-1e-03"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-10, "-1e-10"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-11, "-1e-11"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                      -1e-12, "-1e-12"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e0,    "777.777e0"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e1,    "777.777e1"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e2,    "777.777e2"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e3,    "777.777e3"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e01,   "777.777e01"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e02,   "777.777e02"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e03,   "777.777e03"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e10,   "777.777e10"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e11,   "777.777e11"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e12,   "777.777e12"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+0,   "777.777e+0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+1,   "777.777e+1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+2,   "777.777e+2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+3,   "777.777e+3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+01,  "777.777e+01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+02,  "777.777e+02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+03,  "777.777e+03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+10,  "777.777e+10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+11,  "777.777e+11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e+12,  "777.777e+12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-0,   "777.777e-0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-1,   "777.777e-1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-2,   "777.777e-2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-3,   "777.777e-3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-01,  "777.777e-01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-02,  "777.777e-02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-03,  "777.777e-03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-10,  "777.777e-10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-11,  "777.777e-11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                 777.777e-12,  "777.777e-12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e0,   "+777.777e0"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e1,   "+777.777e1"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e2,   "+777.777e2"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e3,   "+777.777e3"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e01,  "+777.777e01"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e02,  "+777.777e02"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e03,  "+777.777e03"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e10,  "+777.777e10"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e11,  "+777.777e11"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e12,  "+777.777e12"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+0,  "+777.777e+0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+1,  "+777.777e+1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+2,  "+777.777e+2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+3,  "+777.777e+3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+01, "+777.777e+01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+02, "+777.777e+02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+03, "+777.777e+03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+10, "+777.777e+10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+11, "+777.777e+11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e+12, "+777.777e+12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-0,  "+777.777e-0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-1,  "+777.777e-1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-2,  "+777.777e-2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-3,  "+777.777e-3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-01, "+777.777e-01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-02, "+777.777e-02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-03, "+777.777e-03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-10, "+777.777e-10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-11, "+777.777e-11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                +777.777e-12, "+777.777e-12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e0,   "-777.777e0"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e1,   "-777.777e1"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e2,   "-777.777e2"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e3,   "-777.777e3"                 );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e01,  "-777.777e01"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e02,  "-777.777e02"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e03,  "-777.777e03"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e10,  "-777.777e10"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e11,  "-777.777e11"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e12,  "-777.777e12"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+0,  "-777.777e+0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+1,  "-777.777e+1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+2,  "-777.777e+2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+3,  "-777.777e+3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+01, "-777.777e+01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+02, "-777.777e+02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+03, "-777.777e+03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+10, "-777.777e+10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+11, "-777.777e+11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e+12, "-777.777e+12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-0,  "-777.777e-0"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-1,  "-777.777e-1"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-2,  "-777.777e-2"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-3,  "-777.777e-3"                );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-01, "-777.777e-01"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-02, "-777.777e-02"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-03, "-777.777e-03"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-10, "-777.777e-10"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-11, "-777.777e-11"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp)",        	FALSE,                -777.777e-12, "-777.777e-12"               );	\
	print_test_strto##TYPE("strto"#TYPE" (exp, invalid)",	FALSE,                         NAN, "exp"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp, invalid)",	FALSE,                         NAN, "eXp"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp, invalid)",	FALSE,                         NAN, "eXP"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (exp, invalid)",	FALSE,                         NAN, "EXP"                        );	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0xp"                        );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0XP"                        );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0x0p"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0X0P"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0x0p0"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0X0P0"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x0p1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X0P1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0x1p"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0X1P"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0x1p0"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p0, "0X1P0"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x1p1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X1P1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X1.p1"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x1.P1"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X1.0p1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x1.0P1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X1.1p1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x1.1P1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X0.1p1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x0.1P1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X0.0p1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x0.0P1"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0X0.p1"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p1, "0x0.P1"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                         0x2, "0x2p"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                         0x2, "0X2P"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p2, "0x1p2"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x1p2, "0X1P2"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x2p1, "0x2p1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x2p1, "0X2P1"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x2p2, "0x2p2"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x2p2, "0X2P2"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                      0x7p05, "0x7p05"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                      0x7p05, "0X7P05"                     );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                     0x10p01, "0x10p01"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                     0x10p01, "0X10P01"                    );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,                       0x123, "0x123"                      );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,        0x1.921FB54442D18p+1, "0x1.921FB54442D18p+1"       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,        0x1.921FB54442D18p+2, "0x1.921FB54442D18p+2"       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,        0x1.45F306DC9C883p-2, "0x1.45F306DC9C883p-2"       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (hex)",        	FALSE,        0x1.45F306DC9C883p-3, "0x1.45F306DC9C883p-3"       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (bin)",        	FALSE,                          0., "0b0"                        );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (bin)",        	FALSE,                          1., "0b1"                        );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (bin)",        	FALSE,                          2., "0b10"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (bin)",        	FALSE,                          3., "0b11"                       );*/	\
/*	print_test_strto##TYPE("strto"#TYPE" (bin)",        	FALSE,                         13., "0b1101"                     );*/	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "(-(123"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "[12]123"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "45_"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        9876, "\v9876-"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "65435+--+"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "def58453"                   );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "5486helllo"                 );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       -3541, "\f-3541"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       -5643, "\n-5643"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "-\r-397+"                   );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "---84648-+"                 );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "&%64"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "125\n12"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                          -2, "  -2"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                           2, "  2"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "!789"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "#45"                        );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "$786"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "&789"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "*4456"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       .1234, ".1234"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "/1234"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "%1234"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, ",7"                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "7,"                         );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "7,25"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, ",,789"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "456,78"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                       0.456, ".456"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        456., "456."                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                      456.78, "456.78"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                        5896, "  +5896df"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "  + 563"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "++4653"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, " + 45631dsf-+"              );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\200 456"                   );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\255\2543"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\0 456"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\255 5"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\\//\v/789"                 );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\15124578"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\33124578"                  );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "[124578"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "=0124578"                   );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "_456"                       );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "##4567"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\124578"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\\256"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\\256\\"                    );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,             25627165465413., "25627165465413"             );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\\25627165465413"           );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                         NAN, "\2568"                      );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                      30000., "30000f"                     );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,              -500000000000., "-500000000000"              );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,          -6513212312310531., "-6513212312310531"          );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                 2147483648.,  "2147483648"                );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                -2147483649., "-2147483649"                );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                 3000000000.,  "3000000000"                );	\
	print_test_strto##TYPE("strto"#TYPE,                	FALSE,                -3000000000., "-3000000000"                );	\
	print_test_strto##TYPE("strto"#TYPE" (n = s64_max) ",	FALSE,        9223372036854775807.,  "9223372036854775807"       );	\
	print_test_strto##TYPE("strto"#TYPE" (n = s64_min) ",	FALSE,       -9223372036854775807., "-9223372036854775807"       );	\
	print_test_strto##TYPE("strto"#TYPE" (n > s64_max) ",	FALSE,        9223372036854775808.,  "9223372036854775808"       );	\
	print_test_strto##TYPE("strto"#TYPE" (n < s64_min) ",	FALSE,       -9223372036854775809., "-9223372036854775809"       );	\
	print_test_strto##TYPE("strto"#TYPE" (n > maxdigit)",	FALSE,     9999999999999999999999.,  "9999999999999999999999"    );	\
	print_test_strto##TYPE("strto"#TYPE" (n < maxdigit)",	FALSE,    -9999999999999999999999., "-9999999999999999999999"    );	\
	print_test_strto##TYPE("strto"#TYPE"  (inf, lower) ",	FALSE,                    INFINITY,  "inf"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (+inf, lower) ",	FALSE,                   +INFINITY, "+inf"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (-inf, lower) ",	FALSE,                   -INFINITY, "-inf"                       );	\
	print_test_strto##TYPE("strto"#TYPE"  (infy, lower)",	FALSE,                    INFINITY,  "infinity"                  );	\
	print_test_strto##TYPE("strto"#TYPE" (+infy, lower)",	FALSE,                   +INFINITY, "+infinity"                  );	\
	print_test_strto##TYPE("strto"#TYPE" (-infy, lower)",	FALSE,                   -INFINITY, "-infinity"                  );	\
	print_test_strto##TYPE("strto"#TYPE"  (inf, upper) ",	FALSE,                    INFINITY,  "INF"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (+inf, upper) ",	FALSE,                   +INFINITY, "+INF"                       );	\
	print_test_strto##TYPE("strto"#TYPE" (-inf, upper) ",	FALSE,                   -INFINITY, "-INF"                       );	\
	print_test_strto##TYPE("strto"#TYPE"  (infy, upper)",	FALSE,                    INFINITY,  "INFINITY"                  );	\
	print_test_strto##TYPE("strto"#TYPE" (+infy, upper)",	FALSE,                   +INFINITY, "+INFINITY"                  );	\
	print_test_strto##TYPE("strto"#TYPE" (-infy, upper)",	FALSE,                   -INFINITY, "-INFINITY"                  );	\
	print_test_strto##TYPE("strto"#TYPE"  (inf, utf8 \u221E)",	FALSE,                INFINITY,  "\u221E"                    );	\
	print_test_strto##TYPE("strto"#TYPE" (+inf, utf8 \u221E)",	FALSE,               +INFINITY, "+\u221E"                    );	\
	print_test_strto##TYPE("strto"#TYPE" (-inf, utf8 \u221E)",	FALSE,               -INFINITY, "-\u221E"                    );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "NAN"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "NAN"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "NaN"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "nan"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "Nan"                        );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "0xNAN"                      );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "0xNANP"                     );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "0xNANP0"                    );	\
	print_test_strto##TYPE("strto"#TYPE" (NaN)         ",	FALSE,                         NAN, "drop yer nan"               );	\
	print_test_strto##TYPE("strto"#TYPE" (empty str)   ",	FALSE,                         NAN, ""                           );	\
	print_test_strto##TYPE("strto"#TYPE" (null str)    ",	SEGV,                            0, NULL                         );	\
}

#ifndef c_strtof32
void test_strtof32(void)	{}
#else
DEFINETEST_STR_TO_FLOAT(f32)
#endif

#ifndef c_strtof64
void test_strtof64(void)	{}
#else
DEFINETEST_STR_TO_FLOAT(f64)
#endif

#if !defined(c_strtof80) || !defined(__float80)
void test_strtof80(void)	{}
#else
DEFINETEST_STR_TO_FLOAT(f80)
#endif

#if !defined(c_strtof128) || !defined(__float128)
void test_strtof128(void)	{}
#else
DEFINETEST_STR_TO_FLOAT(f128)
#endif

#ifndef c_strtofloat
void test_strtofloat(void)	{}
#else
DEFINETEST_STR_TO_FLOAT(float)
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
#pragma clang diagnostic pop



int		testsuite_float(void)
{
	print_suite_title("float");

	print_nonstd();

	test_f32tostr();
	test_f64tostr();
	test_f80tostr();
	test_f128tostr();
	test_floattostr();



	test_strtof32();
	test_strtof64();
	test_strtof80();
	test_strtof128();
	test_strtofloat();

	return (OK);
}
