
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
**                     Convert Floating-point to Strings                      *|
** ************************************************************************** *|
*/

#ifdef			c_f32_to_str_p
void	print_test_f32_to_str_p(char const* test_name, int can_segfault,
		char const* expecting,
		t_f32 number,
		t_u8 precision)
{
	TEST_PERFORM_RESULT(f32_to_str_p, number, precision)
	print_test_str(test_name, "_f32_to_str_p", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%g", number)
}
void	test_f32_to_str_p(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                      "1", 1                    , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                    "1.0", 1                    , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                 "1.0000", 1                    , 4);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                      "2", 2                    , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                    "2.0", 2                    , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,     "2.0000000000000000", 2                    , 16);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                      "0", 0                    , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                     "-1", -1                   , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                   "-1.0", -1                   , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                  "-1.00", -1                   , 2);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                     "42", 42                   , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,              "0.3333333", 0.33333333           , 7);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,               "3.141592", 0x1.921FB54442D18p+1 , 6);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,               "6.283185", 0x1.921FB54442D18p+2 , 6);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,             "2.71828182", 0x1.5BF0A8B145769p+1 , 8);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,           "1.4142135623", 0x1.6A09E667F3BCDp+0 , 12);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                  "10000", 10000                , 0);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,                "10000.0", 10000                , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,              "123456789", 123456789            , 1);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,         "69696969696969", 69696969696969.      , 10);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,        "-69696969696969",-69696969696969.      , 10);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,            "0.000000003", 0.000000003          , 10);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,           "-0.000000003",-0.000000003          , 10);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,     "0.0000000000000001", 0.0000000000000001   , 10);
	print_test_f32_to_str_p("f32_to_str_p               ",	FALSE,    "-0.0000000000000001",-0.0000000000000001   , 10);
// TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f32_to_str_p("f32_to_str_p (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807.  , 10);
	print_test_f32_to_str_p("f32_to_str_p (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808.  , 10);
	print_test_f32_to_str_p("f32_to_str_p (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808.  , 10);
	print_test_f32_to_str_p("f32_to_str_p (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809.  , 10);
	print_test_f32_to_str_p("f32_to_str_p (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999., 10);
	print_test_f32_to_str_p("f32_to_str_p (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999., 10);
	print_test_f32_to_str_p("f32_to_str_p (n > +huge)   ",	FALSE,        "1.0000000000e20", 1.0000000000e20       , 10);
	print_test_f32_to_str_p("f32_to_str_p (n < -huge)   ",	FALSE,       "-1.0000000000e20",-1.0000000000e20       , 10);
	print_test_f32_to_str_p("f32_to_str_p (n < +tiny)   ",	FALSE,        "1.000000000e-20", 1.000000000e-20       , 9);
	print_test_f32_to_str_p("f32_to_str_p (n > -tiny)   ",	FALSE,       "-1.000000000e-20",-1.000000000e-20       , 9);
	print_test_f32_to_str_p("f32_to_str_p (n > +inf)    ",	FALSE,              "+INFINITY", 1.00000e100           , 5);
	print_test_f32_to_str_p("f32_to_str_p (n < -inf)    ",	FALSE,              "-INFINITY",-1.00000e100           , 5);
	print_test_f32_to_str_p("f32_to_str_p (+inf)        ",	FALSE,              "+INFINITY", INFINITY              , 1);
	print_test_f32_to_str_p("f32_to_str_p (-inf)        ",	FALSE,              "-INFINITY",-INFINITY              , 1);
	print_test_f32_to_str_p("f32_to_str_p (nan)         ",	FALSE,                    "NaN", NAN                   , 1);
}
#endif



#ifdef			c_f64_to_str_p
void	print_test_f64_to_str_p(char const* test_name, int can_segfault,
		char const* expecting,
		t_f64 number,
		t_u8 precision)
{
	TEST_PERFORM_RESULT(f64_to_str_p, number, precision)
	print_test_str(test_name, "_f64_to_str_p", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("%g", number)
}
void	test_f64_to_str_p(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                      "1", 1                    , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                    "1.0", 1                    , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                 "1.0000", 1                    , 4);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                      "2", 2                    , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                    "2.0", 2                    , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,     "2.0000000000000000", 2                    , 16);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                      "0", 0                    , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                     "-1", -1                   , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                   "-1.0", -1                   , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                  "-1.00", -1                   , 2);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                     "42", 42                   , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,              "0.3333333", 0.33333333           , 7);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,               "3.141592", 0x1.921FB54442D18p+1 , 6);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,               "6.283185", 0x1.921FB54442D18p+2 , 6);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,             "2.71828182", 0x1.5BF0A8B145769p+1 , 8);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,           "1.4142135623", 0x1.6A09E667F3BCDp+0 , 12);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                  "10000", 10000                , 0);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,                "10000.0", 10000                , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,              "123456789", 123456789            , 1);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,         "69696969696969", 69696969696969.      , 10);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,        "-69696969696969",-69696969696969.      , 10);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,            "0.000000003", 0.000000003          , 10);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,           "-0.000000003",-0.000000003          , 10);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,     "0.0000000000000001", 0.0000000000000001   , 10);
	print_test_f64_to_str_p("f64_to_str_p               ",	FALSE,    "-0.0000000000000001",-0.0000000000000001   , 10);
// TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f64_to_str_p("f64_to_str_p (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807.  , 10);
	print_test_f64_to_str_p("f64_to_str_p (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808.  , 10);
	print_test_f64_to_str_p("f64_to_str_p (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808.  , 10);
	print_test_f64_to_str_p("f64_to_str_p (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809.  , 10);
	print_test_f64_to_str_p("f64_to_str_p (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999., 10);
	print_test_f64_to_str_p("f64_to_str_p (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999., 10);
	print_test_f64_to_str_p("f64_to_str_p (n > +huge)   ",	FALSE,        "1.0000000000e20", 1.0e20                , 10);
	print_test_f64_to_str_p("f64_to_str_p (n < -huge)   ",	FALSE,       "-1.0000000000e20",-1.0e20                , 10);
	print_test_f64_to_str_p("f64_to_str_p (n < +tiny)   ",	FALSE,        "1.000000000e-20", 1.0e-20               , 9);
	print_test_f64_to_str_p("f64_to_str_p (n > -tiny)   ",	FALSE,       "-1.000000000e-20",-1.0e-20               , 9);
	print_test_f64_to_str_p("f64_to_str_p (n > +inf)    ",	FALSE,              "+INFINITY", 1.0e100               , 5);
	print_test_f64_to_str_p("f64_to_str_p (n < -inf)    ",	FALSE,              "-INFINITY",-1.0e100               , 5);
	print_test_f64_to_str_p("f64_to_str_p (+inf)        ",	FALSE,              "+INFINITY", INFINITY              , 1);
	print_test_f64_to_str_p("f64_to_str_p (-inf)        ",	FALSE,              "-INFINITY",-INFINITY              , 1);
	print_test_f64_to_str_p("f64_to_str_p (nan)         ",	FALSE,                    "NaN", NAN                   , 1);
}
#endif



/*
** ************************************************************************** *|
**                     Convert Strings to Floating-point                      *|
** ************************************************************************** *|
*/

#ifdef			c_str_to_f32
void	print_test_str_to_f32(char const* test_name, int can_segfault,
		t_f32 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_f32, str_to_f32, str)
	print_test_f32(test_name, "_str_to_f32", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void	test_str_to_f32(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
	print_test_str_to_f32("str_to_f32",               	FALSE,                           0, "0"                          );
	print_test_str_to_f32("str_to_f32",               	FALSE,                           1, "1"                          );
	print_test_str_to_f32("str_to_f32",               	FALSE,                          42, "42"                         );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         +42, "+42"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         1e0, "1e0"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         1e1, "1e1"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         1e2, "1e2"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        1e-1, "1e-1"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        1e-2, "1e-2"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        1e10, "1e10"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        1e10, "1e11"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        3.25, "+3.25"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        3.69, "3.69"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       -4.07, "-4.07"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "--9999999"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_f32("str_to_f32",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "- 45678978748f"             );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "swag123"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "exp"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "eXp"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "eXP"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "EXP"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "0xp"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "0XP"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x0, "0x0p"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x0, "0X0P"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x0p0, "0x0p0"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x0p0, "0X0P0"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x0p1, "0x0p1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x0p1, "0X0P1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x1, "0x1p"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x1, "0X1P"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p0, "0x1p0"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p0, "0X1P0"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p1, "0x1p1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p1, "0X1P1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p1, "0x1P1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p1, "0X1p1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x2, "0x2p"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0x2, "0X2P"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p2, "0x1p2"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x1p2, "0X1P2"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x2p1, "0x2p1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x2p1, "0X2P1"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x2p2, "0x2p2"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x2p2, "0X2P2"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                      0x7p05, "0x7p05"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                      0x7p05, "0X7P05"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                     0x10p01, "0x10p01"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                     0x10p01, "0X10P01"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "(-(123"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "[12]123"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                          45, "45_"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "def58453"                   );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "5486helllo"                 );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "-\r-397+"                   );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "---84648-+"                 );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "&%64"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "125\n12"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                           2, "  2"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "!789"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "#45"                        );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "$786"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "&789"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "*4456"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       .1234, ".1234"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "/1234"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "%1234"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         0.7, ",7"                         );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, ",,789"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                      456.78, "456,78"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0.456, ".456"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "  + 563"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "++4653"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, " + 45631dsf-+"              );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\200 456"                   );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\255\2543"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\0 456"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\255 5"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\\//\v/789"                 );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       0x123, "0x123"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\15124578"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\33124578"                  );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "[124578"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "=0124578"                   );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "_456"                       );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "##4567"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\124578"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\\256"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\\256\\"                    );
	print_test_str_to_f32("str_to_f32",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\\25627165465413"           );
	print_test_str_to_f32("str_to_f32",               	FALSE,                         NAN, "\2568"                      );
	print_test_str_to_f32("str_to_f32",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_f32("str_to_f32",               	FALSE,               -500000000000, "-500000000000"              );
	print_test_str_to_f32("str_to_f32",               	FALSE,           -6513212312310531, "-6513212312310531"          );
	print_test_str_to_f32("str_to_f32",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_f32("str_to_f32",               	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_f32("str_to_f32",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_f32("str_to_f32",               	FALSE,                 -3000000000, "-3000000000"                );
	print_test_str_to_f32("str_to_f32 (n = s64_max) ",	FALSE,        9223372036854775807.,  "9223372036854775807"       );
	print_test_str_to_f32("str_to_f32 (n = s64_min) ",	FALSE,       -9223372036854775807., "-9223372036854775807"       );
	print_test_str_to_f32("str_to_f32 (n > s64_max) ",	FALSE,        9223372036854775808.,  "9223372036854775808"       );
	print_test_str_to_f32("str_to_f32 (n < s64_min) ",	FALSE,       -9223372036854775809., "-9223372036854775809"       );
	print_test_str_to_f32("str_to_f32 (n > maxdigit)",	FALSE,     9999999999999999999999.,  "9999999999999999999999"    );
	print_test_str_to_f32("str_to_f32 (n < maxdigit)",	FALSE,    -9999999999999999999999., "-9999999999999999999999"    );
	print_test_str_to_f32("str_to_f32  (inf, lower) ",	FALSE,                    INFINITY,  "inf"                       );
	print_test_str_to_f32("str_to_f32 (+inf, lower) ",	FALSE,                   +INFINITY, "+inf"                       );
	print_test_str_to_f32("str_to_f32 (-inf, lower) ",	FALSE,                   -INFINITY, "-inf"                       );
	print_test_str_to_f32("str_to_f32  (infy, lower)",	FALSE,                    INFINITY,  "infinity"                  );
	print_test_str_to_f32("str_to_f32 (+infy, lower)",	FALSE,                   +INFINITY, "+infinity"                  );
	print_test_str_to_f32("str_to_f32 (-infy, lower)",	FALSE,                   -INFINITY, "-infinity"                  );
	print_test_str_to_f32("str_to_f32  (inf, upper) ",	FALSE,                    INFINITY,  "INF"                       );
	print_test_str_to_f32("str_to_f32 (+inf, upper) ",	FALSE,                   +INFINITY, "+INF"                       );
	print_test_str_to_f32("str_to_f32 (-inf, upper) ",	FALSE,                   -INFINITY, "-INF"                       );
	print_test_str_to_f32("str_to_f32  (infy, upper)",	FALSE,                    INFINITY,  "INFINITY"                  );
	print_test_str_to_f32("str_to_f32 (+infy, upper)",	FALSE,                   +INFINITY, "+INFINITY"                  );
	print_test_str_to_f32("str_to_f32 (-infy, upper)",	FALSE,                   -INFINITY, "-INFINITY"                  );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "NAN"                        );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "NAN"                        );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "NaN"                        );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "nan"                        );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "Nan"                        );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "0xNAN"                      );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "0xNANP"                     );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "0xNANP0"                    );
	print_test_str_to_f32("str_to_f32 (NaN)         ",	FALSE,                         NAN, "drop yer nan"               );
	print_test_str_to_f32("str_to_f32 (empty str)   ",	FALSE,                         NAN, ""                           );
	print_test_str_to_f32("str_to_f32 (null str)    ",	SEGV,                            0, NULL                         );
}
#endif



#ifdef			c_str_to_f64
void	print_test_str_to_f64(char const* test_name, int can_segfault,
		t_f64 expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_f64, str_to_f64, str)
	print_test_f64(test_name, "_str_to_f64", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void test_str_to_f64(void)
{
//	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS
	print_test_str_to_f64("str_to_f64",               	FALSE,                           0, "0"                          );
	print_test_str_to_f64("str_to_f64",               	FALSE,                           1, "1"                          );
	print_test_str_to_f64("str_to_f64",               	FALSE,                          42, "42"                         );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         +42, "+42"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         1e0, "1e0"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         1e1, "1e1"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         1e2, "1e2"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        1e-1, "1e-1"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        1e-2, "1e-2"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        1e10, "1e10"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        1e10, "1e11"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3.25, "+3.25"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3.69, "3.69"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -4.07, "-4.07"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "--9999999"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_f64("str_to_f64",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "- 45678978748f"             );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "swag123"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "exp"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "eXp"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "eXP"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "EXP"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "0xp"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "0XP"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x0, "0x0p"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x0, "0X0P"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p0, "0x0p0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p0, "0X0P0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p1, "0x0p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p1, "0X0P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x1, "0x1p"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x1, "0X1P"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p0, "0x1p0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p0, "0X1P0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0x1p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0X1P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0x1P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0X1p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x2, "0x2p"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x2, "0X2P"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p2, "0x1p2"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p2, "0X1P2"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x2p1, "0x2p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x2p1, "0X2P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x2p2, "0x2p2"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x2p2, "0X2P2"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                      0x7p05, "0x7p05"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                      0x7p05, "0X7P05"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                     0x10p01, "0x10p01"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                     0x10p01, "0X10P01"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "(-(123"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "[12]123"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                          45, "45_"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "def58453"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "5486helllo"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "-\r-397+"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "---84648-+"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "&%64"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "125\n12"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                           2, "  2"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "!789"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "#45"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "$786"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "&789"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "*4456"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       .1234, ".1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "/1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "%1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0.7, ",7"                         );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, ",,789"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                      456.78, "456,78"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0.456, ".456"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "  + 563"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "++4653"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, " + 45631dsf-+"              );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\200 456"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\255\2543"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\0 456"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\255 5"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\\//\v/789"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x123, "0x123"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\15124578"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\33124578"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "[124578"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "=0124578"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "_456"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "##4567"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\124578"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\\256"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\\256\\"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\\25627165465413"           );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         NAN, "\2568"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,               -500000000000, "-500000000000"              );
	print_test_str_to_f64("str_to_f64",               	FALSE,           -6513212312310531, "-6513212312310531"          );
	print_test_str_to_f64("str_to_f64",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_f64("str_to_f64",               	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_f64("str_to_f64",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_f64("str_to_f64",               	FALSE,                 -3000000000, "-3000000000"                );
	print_test_str_to_f64("str_to_f64 (n = s64_max) ",	FALSE,        9223372036854775807.,  "9223372036854775807"       );
	print_test_str_to_f64("str_to_f64 (n = s64_min) ",	FALSE,       -9223372036854775807., "-9223372036854775807"       );
	print_test_str_to_f64("str_to_f64 (n > s64_max) ",	FALSE,        9223372036854775808.,  "9223372036854775808"       );
	print_test_str_to_f64("str_to_f64 (n < s64_min) ",	FALSE,       -9223372036854775809., "-9223372036854775809"       );
	print_test_str_to_f64("str_to_f64 (n > maxdigit)",	FALSE,     9999999999999999999999.,  "9999999999999999999999"    );
	print_test_str_to_f64("str_to_f64 (n < maxdigit)",	FALSE,    -9999999999999999999999., "-9999999999999999999999"    );
	print_test_str_to_f64("str_to_f64  (inf, lower) ",	FALSE,                    INFINITY,  "inf"                       );
	print_test_str_to_f64("str_to_f64 (+inf, lower) ",	FALSE,                   +INFINITY, "+inf"                       );
	print_test_str_to_f64("str_to_f64 (-inf, lower) ",	FALSE,                   -INFINITY, "-inf"                       );
	print_test_str_to_f64("str_to_f64  (infy, lower)",	FALSE,                    INFINITY,  "infinity"                  );
	print_test_str_to_f64("str_to_f64 (+infy, lower)",	FALSE,                   +INFINITY, "+infinity"                  );
	print_test_str_to_f64("str_to_f64 (-infy, lower)",	FALSE,                   -INFINITY, "-infinity"                  );
	print_test_str_to_f64("str_to_f64  (inf, upper) ",	FALSE,                    INFINITY,  "INF"                       );
	print_test_str_to_f64("str_to_f64 (+inf, upper) ",	FALSE,                   +INFINITY, "+INF"                       );
	print_test_str_to_f64("str_to_f64 (-inf, upper) ",	FALSE,                   -INFINITY, "-INF"                       );
	print_test_str_to_f64("str_to_f64  (infy, upper)",	FALSE,                    INFINITY,  "INFINITY"                  );
	print_test_str_to_f64("str_to_f64 (+infy, upper)",	FALSE,                   +INFINITY, "+INFINITY"                  );
	print_test_str_to_f64("str_to_f64 (-infy, upper)",	FALSE,                   -INFINITY, "-INFINITY"                  );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "NAN"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "NAN"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "NaN"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "nan"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "Nan"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "0xNAN"                      );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "0xNANP"                     );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "0xNANP0"                    );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                         NAN, "drop yer nan"               );
	print_test_str_to_f64("str_to_f64 (empty str)   ",	FALSE,                         NAN, ""                           );
	print_test_str_to_f64("str_to_f64 (null str)    ",	SEGV,                            0, NULL                         );
	if (g_test.flags.test_overflow)
	{
	}
}
#endif



#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



int		testsuite_float(void)
{
	print_suite_title("float");

	print_nonstd();

#ifdef c_f32_to_str_p
	test_f32_to_str_p();
#endif
#ifdef c_f64_to_str_p
	test_f64_to_str_p();
#endif



#ifdef c_str_to_f32
//	test_str_to_f32();
#endif
#ifdef c_str_to_f64
//	test_str_to_f64();
#endif

	return (OK);
}
