
#include "test.h"



/*
**	char*	ft_s8_to_str(t_s8 n);
*/
void	print_test_s8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s8 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s8_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s8_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s8_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "1", 1    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,     "42", 42   );
	print_test_s8_to_str("s8_to_str               ",	FALSE,      "0", 0    );
	print_test_s8_to_str("s8_to_str               ",	FALSE,    "111", 111  );
	print_test_s8_to_str("s8_to_str               ",	FALSE,   "-111",-111  );
	print_test_s8_to_str("s8_to_str (n = max)     ",	FALSE,    "127", 127  );
	print_test_s8_to_str("s8_to_str (n = min)     ",	FALSE,   "-128",-128  );
#ifdef __TEST_OVERFLOW
	print_test_s8_to_str("s8_to_str (n > max)     ",	FALSE,    "128", 128  );
	print_test_s8_to_str("s8_to_str (n < min)     ",	FALSE,   "-129",-129  );
	print_test_s8_to_str("s8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
	print_test_s8_to_str("s8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
#endif
}



/*
**	char*	ft_s16_to_str(t_s16 n);
*/
void	print_test_s16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s16 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s16_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s16_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s16_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "1", 1      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,       "42", 42     );
	print_test_s16_to_str("s16_to_str               ",	FALSE,        "0", 0      );
	print_test_s16_to_str("s16_to_str               ",	FALSE,      "777", 777    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,     "-666",-666    );
	print_test_s16_to_str("s16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_s16_to_str("s16_to_str               ",	FALSE,   "-10000",-10000  );
	print_test_s16_to_str("s16_to_str (n = max)     ",	FALSE,    "32767", 32767  );
	print_test_s16_to_str("s16_to_str (n = min)     ",	FALSE,   "-32768",-32768  );
#ifdef __TEST_OVERFLOW
	print_test_s16_to_str("s16_to_str (n > max)     ",	FALSE,    "32768", 32768  );
	print_test_s16_to_str("s16_to_str (n < min)     ",	FALSE,   "-32769",-32769  );
	print_test_s16_to_str("s16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
	print_test_s16_to_str("s16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
#endif
}



/*
**	char*	ft_s32_to_str(t_s32 n);
*/
void	print_test_s32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s32_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS */
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "1", 1           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,            "42", 42          );
	print_test_s32_to_str("s32_to_str               ",	FALSE,             "0", 0           );
	print_test_s32_to_str("s32_to_str               ",	FALSE,           "777", 777         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,          "-666",-666         );
	print_test_s32_to_str("s32_to_str               ",	FALSE,        "-10000",-10000       );
	print_test_s32_to_str("s32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_s32_to_str("s32_to_str (n = max)     ",	FALSE,    "2147483647", 2147483647  );
	print_test_s32_to_str("s32_to_str (n = min)     ",	FALSE,   "-2147483648",-2147483648  );
#ifdef __TEST_OVERFLOW
	print_test_s32_to_str("s32_to_str (n > max)     ",	FALSE,    "2147483648", 2147483648  );
	print_test_s32_to_str("s32_to_str (n < min)     ",	FALSE,   "-2147483649",-2147483649  );
	print_test_s32_to_str("s32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
	print_test_s32_to_str("s32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
#endif
}



/*
**	char*	ft_s64_to_str(t_s64 n);
*/
void	print_test_s64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_s64 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s64_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_s64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
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
	print_test_s64_to_str("s64_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807LL );
	print_test_s64_to_str("s64_to_str (n = min)     ",	FALSE,   "-9223372036854775807",-9223372036854775807LL );
#ifdef __TEST_OVERFLOW
	print_test_s64_to_str("s64_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808LL  );
	print_test_s64_to_str("s64_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809LL  );
	print_test_s64_to_str("s64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999LL);
	print_test_s64_to_str("s64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999LL);
#endif
}



/*
**	char*	ft_u8_to_str(t_u8 n);
*/
void	print_test_u8_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u8 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u8_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u8_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u8_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u8_to_str("u8_to_str               ",	FALSE,      "1", 1    );
	print_test_u8_to_str("u8_to_str               ",	FALSE,     "42", 42   );
	print_test_u8_to_str("u8_to_str               ",	FALSE,    "111", 111  );
	print_test_u8_to_str("u8_to_str (n = max)     ",	FALSE,    "255", 255  );
	print_test_u8_to_str("u8_to_str (n = min)     ",	FALSE,      "0", 0    );
#ifdef __TEST_OVERFLOW
	print_test_u8_to_str("u8_to_str (n > max)     ",	FALSE,    "256", 256  );
	print_test_u8_to_str("u8_to_str (n < min)     ",	FALSE,     "-1", -1   );
	print_test_u8_to_str("u8_to_str (n > maxdigit)",	FALSE,  "99999", 99999);
	print_test_u8_to_str("u8_to_str (n < maxdigit)",	FALSE, "-99999",-99999);
#endif
}



/*
**	char*	ft_u16_to_str(t_u16 n);
*/
void	print_test_u16_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u16 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u16_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u16_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u16_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u16_to_str("u16_to_str               ",	FALSE,        "1", 1      );
	print_test_u16_to_str("u16_to_str               ",	FALSE,       "42", 42     );
	print_test_u16_to_str("u16_to_str               ",	FALSE,      "777", 777    );
	print_test_u16_to_str("u16_to_str               ",	FALSE,    "10000", 10000  );
	print_test_u16_to_str("u16_to_str (n = max)     ",	FALSE,    "65535", 65535  );
	print_test_u16_to_str("u16_to_str (n = min)     ",	FALSE,        "0", 0      );
#ifdef __TEST_OVERFLOW
	print_test_u16_to_str("u16_to_str (n > max)     ",	FALSE,    "65536", 65536  );
	print_test_u16_to_str("u16_to_str (n < min)     ",	FALSE,       "-1", -1     );
	print_test_u16_to_str("u16_to_str (n > maxdigit)",	FALSE,  "9999999", 9999999);
	print_test_u16_to_str("u16_to_str (n < maxdigit)",	FALSE, "-9999999",-9999999);
#endif
}



/*
**	char*	ft_u32_to_str(t_u32 n);
*/
void	print_test_u32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u32_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS */
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "1", 1           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,            "42", 42          );
	print_test_u32_to_str("u32_to_str               ",	FALSE,             "0", 0           );
	print_test_u32_to_str("u32_to_str               ",	FALSE,           "777", 777         );
	print_test_u32_to_str("u32_to_str               ",	FALSE,         "10000", 10000       );
	print_test_u32_to_str("u32_to_str               ",	FALSE,     "123456789", 123456789   );
	print_test_u32_to_str("u32_to_str (n = max)     ",	FALSE,    "4294967295", 4294967295  );
	print_test_u32_to_str("u32_to_str (n = min)     ",	FALSE,             "0", 0           );
#ifdef __TEST_OVERFLOW
	print_test_u32_to_str("u32_to_str (n > max)     ",	FALSE,    "4294967296", 4294967296  );
	print_test_u32_to_str("u32_to_str (n < min)     ",	FALSE,            "-1", -1          );
	print_test_u32_to_str("u32_to_str (n > maxdigit)",	FALSE,  "999999999999", 999999999999);
	print_test_u32_to_str("u32_to_str (n < maxdigit)",	FALSE, "-999999999999",-999999999999);
#endif
}



/*
**	char*	ft_u64_to_str(t_u64 n);
*/
void	print_test_u64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_u64 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u64_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_u64_to_str("u64_to_str               ",	FALSE,                      "1", 1                     );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                     "42", 42                    );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                    "777", 777                   );
	print_test_u64_to_str("u64_to_str               ",	FALSE,                  "10000", 10000                 );
	print_test_u64_to_str("u64_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_u64_to_str("u64_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_u64_to_str("u64_to_str (n = max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL);
	print_test_u64_to_str("u64_to_str (n = min)     ",	FALSE,                      "0", 0                     );
#ifdef __TEST_OVERFLOW
	print_test_u64_to_str("u64_to_str (n > max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL);
	print_test_u64_to_str("u64_to_str (n < min)     ",	FALSE,                     "-1", -1                    );
	print_test_u64_to_str("u64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);
	print_test_u64_to_str("u64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);
#endif
}



/*
**	char*	ft_f32_to_str(t_f32 n, t_u8 precision);
*/
void	print_test_f32_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_f32 number,
		t_u8 precision)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_f32_to_str(number, precision); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_f32_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_f32_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_f32_to_str("f32_to_str               ",	FALSE,                      "1", 1                    , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                     "42", 42                   , 0);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                      "0", 0                    , 0);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                     "-1", -1                   , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f32_to_str("f32_to_str               ",	FALSE,                  "10000", 10000                , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f32_to_str("f32_to_str               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f32_to_str("f32_to_str               ",	FALSE,              "123456789", 123456789            , 1);
	print_test_f32_to_str("f32_to_str               ",	FALSE,     "696969696969696969", 696969696969696969.  , 10);
	print_test_f32_to_str("f32_to_str               ",	FALSE,    "-696969696969696969",-696969696969696969.  , 10);
	print_test_f32_to_str("f32_to_str               ",	FALSE,            "0.000000003", 0.000000003          , 10);
	print_test_f32_to_str("f32_to_str               ",	FALSE,           "-0.000000003",-0.000000003          , 10);
	print_test_f32_to_str("f32_to_str               ",	FALSE,     "0.0000000000000001", 0.0000000000000001   , 10);
	print_test_f32_to_str("f32_to_str               ",	FALSE,    "-0.0000000000000001",-0.0000000000000001   , 10);
// TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f32_to_str("f32_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807.  , 10);
	print_test_f32_to_str("f32_to_str (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808.  , 10);
	print_test_f32_to_str("f32_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808.  , 10);
	print_test_f32_to_str("f32_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809.  , 10);
	print_test_f32_to_str("f32_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999., 10);
	print_test_f32_to_str("f32_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999., 10);
	print_test_f32_to_str("f32_to_str (n > +huge)   ",	FALSE,        "1.0000000000e20", 1.0000000000e20       , 10);
	print_test_f32_to_str("f32_to_str (n < -huge)   ",	FALSE,       "-1.0000000000e20",-1.0000000000e20       , 10);
	print_test_f32_to_str("f32_to_str (n < +tiny)   ",	FALSE,        "1.000000000e-20", 1.000000000e-20       , 9);
	print_test_f32_to_str("f32_to_str (n > -tiny)   ",	FALSE,       "-1.000000000e-20",-1.000000000e-20       , 9);
	print_test_f32_to_str("f32_to_str (n > +inf)    ",	FALSE,              "+INFINITY", 1.00000e100           , 5);
	print_test_f32_to_str("f32_to_str (n < -inf)    ",	FALSE,              "-INFINITY",-1.00000e100           , 5);
	print_test_f32_to_str("f32_to_str (+inf)        ",	FALSE,              "+INFINITY", INFINITY              , 1);
	print_test_f32_to_str("f32_to_str (-inf)        ",	FALSE,              "-INFINITY",-INFINITY              , 1);
	print_test_f32_to_str("f32_to_str (nan)         ",	FALSE,                    "NaN", NOT_A_NUMBER          , 1);
}



/*
**	char*	ft_f64_to_str(t_f64 n, t_u8 precision);
*/
void	print_test_f64_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_f32 number,
		t_u8 precision)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_f64_to_str(number, precision); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_f64_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_f64_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_f64_to_str("f64_to_str               ",	FALSE,                      "1", 1                    , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                     "42", 42                   , 0);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                   "42.0", 42                   , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "42.00", 42                   , 2);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                      "0", 0                    , 0);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                    "0.0", 0                    , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "0.000", 0                    , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                     "-1", -1                   , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                    "0.5", 0.5                  , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "0.001", 0.001                , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                "0.33333", 0.33333333           , 5);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                 "-777.1", -777.1               , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,               "3.141592", 3.141592             , 6);
	print_test_f64_to_str("f64_to_str               ",	FALSE,                  "10000", 10000                , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,              "10000.000", 10000                , 3);
	print_test_f64_to_str("f64_to_str               ",	FALSE,     "10000.000000000000", 10000                , 12);
	print_test_f64_to_str("f64_to_str               ",	FALSE,              "123456789", 123456789            , 1);
	print_test_f64_to_str("f64_to_str               ",	FALSE,     "696969696969696969", 696969696969696969.  , 10);
	print_test_f64_to_str("f64_to_str               ",	FALSE,    "-696969696969696969",-696969696969696969.  , 10);
	print_test_f64_to_str("f64_to_str               ",	FALSE,            "0.000000003", 0.000000003          , 10);
	print_test_f64_to_str("f64_to_str               ",	FALSE,           "-0.000000003",-0.000000003          , 10);
	print_test_f64_to_str("f64_to_str               ",	FALSE,     "0.0000000000000001", 0.0000000000000001   , 10);
	print_test_f64_to_str("f64_to_str               ",	FALSE,    "-0.0000000000000001",-0.0000000000000001   , 10);
// TODO make it so these tests are ok, they arent because the float conversion functions use a u64 tmp variable
	print_test_f64_to_str("f64_to_str (n = max)     ",	FALSE,    "9223372036854775807", 9223372036854775807.  , 10);
	print_test_f64_to_str("f64_to_str (n = min)     ",	FALSE,   "-9223372036854775808",-9223372036854775808.  , 10);
	print_test_f64_to_str("f64_to_str (n > max)     ",	FALSE,    "9223372036854775808", 9223372036854775808.  , 10);
	print_test_f64_to_str("f64_to_str (n < min)     ",	FALSE,   "-9223372036854775809",-9223372036854775809.  , 10);
	print_test_f64_to_str("f64_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999., 10);
	print_test_f64_to_str("f64_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999., 10);
	print_test_f64_to_str("f64_to_str (n > +huge)   ",	FALSE,        "1.0000000000e20", 1.0000000000e20       , 10);
	print_test_f64_to_str("f64_to_str (n < -huge)   ",	FALSE,       "-1.0000000000e20",-1.0000000000e20       , 10);
	print_test_f64_to_str("f64_to_str (n < +tiny)   ",	FALSE,        "1.000000000e-20", 1.000000000e-20       , 9);
	print_test_f64_to_str("f64_to_str (n > -tiny)   ",	FALSE,       "-1.000000000e-20",-1.000000000e-20       , 9);
	print_test_f64_to_str("f64_to_str (n > +inf)    ",	FALSE,              "+INFINITY", 1.00000e100           , 5);
	print_test_f64_to_str("f64_to_str (n < -inf)    ",	FALSE,              "-INFINITY",-1.00000e100           , 5);
	print_test_f64_to_str("f64_to_str (+inf)        ",	FALSE,              "+INFINITY", INFINITY              , 1);
	print_test_f64_to_str("f64_to_str (-inf)        ",	FALSE,              "-INFINITY",-INFINITY              , 1);
	print_test_f64_to_str("f64_to_str (nan)         ",	FALSE,                    "NaN", NOT_A_NUMBER          , 1);
}



/*
**	t_s8	ft_str_to_s8(char const *str);
*/
void	print_test_str_to_s8(char const* test_name, int can_segfault,
		t_s8 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s8 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s8(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s8(test_name, "_str_to_s8", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s8()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_s8("str_to_s8 (n > max)     ",	FALSE,                         128, " 128"                       );
	print_test_str_to_s8("str_to_s8 (n < min)     ",	FALSE,                        -129, "-129"                       );
	print_test_str_to_s8("str_to_s8 (n > maxdigit)",	FALSE,                       99999, " 99999"                     );
	print_test_str_to_s8("str_to_s8 (n < maxdigit)",	FALSE,                      -99999, "-99999"                     );
#endif
}



/*
**	t_s16	ft_str_to_s16(char const *str);
*/
void	print_test_str_to_s16(char const* test_name, int can_segfault,
		t_s16 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s16 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s16(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s16(test_name, "_str_to_s16", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s16()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "0"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           1, "1"                          );
	print_test_str_to_s16("str_to_s16",               	FALSE,                          42, "42"                         );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         -42, "-42"                        );
	print_test_str_to_s16("str_to_s16",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_s16("str_to_s16",               	FALSE,                           0, "- 45678978748f"             );
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_s16("str_to_s16 (n > max)     ",	FALSE,                       32768,  "32768"                     );
	print_test_str_to_s16("str_to_s16 (n < min)     ",	FALSE,                      -32769, "-32769"                     );
	print_test_str_to_s16("str_to_s16 (n > maxdigit)",	FALSE,                     9999999,  "9999999"                   );
	print_test_str_to_s16("str_to_s16 (n < maxdigit)",	FALSE,                    -9999999, "-9999999"                   );
#endif
}



/*
**	t_s32	ft_str_to_s32(char const *str);
*/
void	print_test_str_to_s32(char const* test_name, int can_segfault,
		t_s32 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s32 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s32(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s32(test_name, "_str_to_s32", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s32()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_s32("str_to_s32 (n > max)     ",	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_s32("str_to_s32 (n < min)     ",	FALSE,                 -2147483649, "-2147483649"                );
	print_test_str_to_s32("str_to_s32 (n > maxdigit)",	FALSE,                999999999999,  "999999999999"              );
	print_test_str_to_s32("str_to_s32 (n < maxdigit)",	FALSE,               -999999999999, "-999999999999"              );
#endif
}



/*
**	t_s64	ft_str_to_s64(char const *str);
*/
void	print_test_str_to_s64(char const* test_name, int can_segfault,
		t_s64 expecting,
		char const* number)
{
	t_timer t = {0};
	t_s64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_s64(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_s64(test_name, "_str_to_s64", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_s64()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_s64("str_to_s64 (n > max)     ",	FALSE,       9223372036854775808LL,  "9223372036854775808"       );
	print_test_str_to_s64("str_to_s64 (n < min)     ",	FALSE,      -9223372036854775809LL, "-9223372036854775809"       );
	print_test_str_to_s64("str_to_s64 (n > maxdigit)",	FALSE,     999999999999999999999LL,  "999999999999999999999"     );
	print_test_str_to_s64("str_to_s64 (n < maxdigit)",	FALSE,    -999999999999999999999LL, "-999999999999999999999"     );
#endif
}



/*
**	t_u8	ft_str_to_u8(char const *str);
*/
void	print_test_str_to_u8(char const* test_name, int can_segfault,
		t_u8 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u8 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_u8(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u8(test_name, "_str_to_u8", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_u8()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_u8("str_to_u8 (n > max)     ",	FALSE,                         256,  "256"                       );
	print_test_str_to_u8("str_to_u8 (n < min)     ",	FALSE,                           0, "-1"                         );
	print_test_str_to_u8("str_to_u8 (n > maxdigit)",	FALSE,                       99999,  "99999"                     );
	print_test_str_to_u8("str_to_u8 (n < maxdigit)",	FALSE,                           0, "-99999"                     );
#endif
}



/*
**	t_u16	ft_str_to_u16(char const *str);
*/
void	print_test_str_to_u16(char const* test_name, int can_segfault,
		t_u16 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u16 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_u16(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u16(test_name, "_str_to_u16", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_u16()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_u16("str_to_u16 (n > max)     ",	FALSE,                       65536, "65536"                      );
	print_test_str_to_u16("str_to_u16 (n < min)     ",	FALSE,                           0, "-32769"                     );
	print_test_str_to_u16("str_to_u16 (n > maxdigit)",	FALSE,                     9999999, "9999999"                    );
	print_test_str_to_u16("str_to_u16 (n < maxdigit)",	FALSE,                           0, "-9999999"                   );
#endif
}



/*
**	t_u32	ft_str_to_u32(char const *str);
*/
void	print_test_str_to_u32(char const* test_name, int can_segfault,
		t_u32 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u32 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_u32(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u32(test_name, "_str_to_u32", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_u32()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
#ifdef __TEST_OVERFLOW
	print_test_str_to_u32("str_to_u32 (n > max)     ",	FALSE,                  4294967296, "4294967296"                 );
	print_test_str_to_u32("str_to_u32 (n < min)     ",	FALSE,                           0, "-1"                         );
	print_test_str_to_u32("str_to_u32 (n > maxdigit)",	FALSE,                999999999999, "999999999999"               );
	print_test_str_to_u32("str_to_u32 (n < maxdigit)",	FALSE,                           0, "-999999999999"              );
#endif
}



/*
**	t_u64	ft_str_to_u64(char const *str);
*/
void	print_test_str_to_u64(char const* test_name, int can_segfault,
		t_u64 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_u64(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u64(test_name, "_str_to_u64", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_u64()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
	print_test_str_to_u64("str_to_u64 (n = max)     ",	FALSE,      18446744073709551615UL, "18446744073709551615"       );
	print_test_str_to_u64("str_to_u64 (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_u64("str_to_u64 (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_u64("str_to_u64 (null str)    ",	SEGV,                            0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_u64("str_to_u64 (n > max)     ",	FALSE,      18446744073709551616UL, "18446744073709551616"       );
	print_test_str_to_u64("str_to_u64 (n < min)     ",	FALSE,                           0, "-1"                         );
	print_test_str_to_u64("str_to_u64 (n > maxdigit)",	FALSE,     999999999999999999999LL, "999999999999999999999"      );
	print_test_str_to_u64("str_to_u64 (n < maxdigit)",	FALSE,                           0, "-999999999999999999999"     );
#endif
}



/*
**	t_f32	ft_str_to_f32(char const *str);
*/
void	print_test_str_to_f32(char const* test_name, int can_segfault,
		t_f32 expecting,
		char const* number)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_str_to_f32(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	t_f64	ft_str_to_f64(char const *str);
*/
void	print_test_str_to_f64(char const* test_name, int can_segfault,
		t_f64 expecting,
		char const* number)
{
	t_timer t = {0};
	t_f64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_f64(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_f64(test_name, "_str_to_f64", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void test_str_to_f64()
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING                   | TEST ARGS */
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
	print_test_str_to_f64("str_to_f64",               	FALSE,                        1e10, "1e10"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -5435, "-5435"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3.25, "+3.25"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3.69, "3.69"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -4.07, "-4.07"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "--9999999"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                 -2147483648, "-2147483648"                );
	print_test_str_to_f64("str_to_f64",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "- 45678978748f"             );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "swag123"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "exp"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "0xp"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x0, "0x0p"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p0, "0x0p0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p1, "0x0p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p0, "0x1p0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0x1p1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                     0x10p01, "0x10p01"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "EXP"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "0XP"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0x0, "0X0P"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p0, "0X0P0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x0p1, "0X0P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p0, "0X1P0"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x1p1, "0X1P1"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                      0x7p05, "0X7P05"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "(-(123"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "[12]123"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                          45, "45_"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "def58453"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "5486helllo"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -3541, "\f-3541"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       -5643, "\n-5643"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "-\r-397+"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "---84648-+"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "&%64"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "125\n12"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                          -2, "  -2"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                           2, "  2"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "!789"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "#45"                        );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "$786"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "&789"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "*4456"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       .1234, ".1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "/1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "%1234"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                         0.7, ",7"                         );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, ",,789"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                      456.78, "456,78"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0.456, ".456"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "  + 563"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "++4653"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, " + 45631dsf-+"              );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\200 456"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\255\2543"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\0 456"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\255 5"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\\//\v/789"                 );
	print_test_str_to_f64("str_to_f64",               	FALSE,                       0x123, "0x123"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\15124578"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\33124578"                  );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "[124578"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "=0124578"                   );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "_456"                       );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "##4567"                     );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\124578"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\\256"                      );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\\256\\"                    );
	print_test_str_to_f64("str_to_f64",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\\25627165465413"           );
	print_test_str_to_f64("str_to_f64",               	FALSE,                NOT_A_NUMBER, "\2568"                      );
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
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "NOT_A_NUMBER"               );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "NAN"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "NaN"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "nan"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "Nan"                        );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "0xNAN"                      );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "0xNANP"                     );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "0xNANP0"                    );
	print_test_str_to_f64("str_to_f64 (NaN)         ",	FALSE,                NOT_A_NUMBER, "drop yer nan"               );
	print_test_str_to_f64("str_to_f64 (empty str)   ",	FALSE,                NOT_A_NUMBER, ""                           );
	print_test_str_to_f64("str_to_f64 (null str)    ",	SEGV,                            0, NULL                         );
#ifdef __TEST_OVERFLOW
#endif
}



/*
**	char*	ft_bool_to_str(t_bool value);
*/
void	print_test_bool_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_bool number,
		t_bool uppercase)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_bool_to_str(number, uppercase); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_bool_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_bool_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION       | TEST NAME                   |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",      1, TRUE);
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "FALSE",      0, TRUE);
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",     42, TRUE);
	print_test_bool_to_str("bool_to_str (n = max)     ",	FALSE,   "true",    255, FALSE);
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "false",      0, FALSE);
#ifdef __TEST_OVERFLOW
	print_test_bool_to_str("bool_to_str (n > max)     ",	FALSE,   "TRUE",    256, TRUE);
	print_test_bool_to_str("bool_to_str (n < min)     ",	FALSE,  "FALSE",     -1, TRUE);
	print_test_bool_to_str("bool_to_str (n > maxdigit)",	FALSE,   "TRUE", 999999, TRUE);
	print_test_bool_to_str("bool_to_str (n < maxdigit)",	FALSE,  "-TRUE",-999999, TRUE);
#endif
}



/*
**	char*	ft_size_to_str(size_t n);
*/
void	print_test_size_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		size_t number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_size_to_str(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_size_to_str", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_size_to_str(void)
{
printf("\n");
/*	| TEST FUNCTION       | TEST NAME                    |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_size_to_str("size_to_str               ",	FALSE,                      "1", 1                     );
	print_test_size_to_str("size_to_str               ",	FALSE,                     "42", 42                    );
	print_test_size_to_str("size_to_str               ",	FALSE,                    "777", 777                   );
	print_test_size_to_str("size_to_str               ",	FALSE,                  "10000", 10000                 );
	print_test_size_to_str("size_to_str               ",	FALSE,              "123456789", 123456789             );
	print_test_size_to_str("size_to_str               ",	FALSE,           "999999999999", 999999999999          );
	print_test_size_to_str("size_to_str (n = max)     ",	FALSE,   "18446744073709551615", 18446744073709551615UL);
	print_test_size_to_str("size_to_str (n = min)     ",	FALSE,                      "0", 0                     );
#ifdef __TEST_OVERFLOW
	print_test_size_to_str("size_to_str (n > max)     ",	FALSE,   "18446744073709551616", 18446744073709551616UL);
	print_test_size_to_str("size_to_str (n < min)     ",	FALSE,                     "-1", -1                    );
	print_test_size_to_str("size_to_str (n > maxdigit)",	FALSE,  "999999999999999999999", 999999999999999999999UL);
	print_test_size_to_str("size_to_str (n < maxdigit)",	FALSE, "-999999999999999999999",-999999999999999999999UL);
#endif
}



/*
**	t_bool	ft_str_to_bool(char const *str);
*/
void	print_test_str_to_bool(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_str_to_bool(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	size_t	ft_str_to_size(char const *str);
*/
void	print_test_str_to_size(char const* test_name, int can_segfault,
		size_t expecting,
		char const* number)
{
	t_timer t = {0};
	t_u64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_str_to_size(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_size(test_name, "_str_to_size", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* expect = str_to_escape(number);
	printf(" -> {%s}", expect);
	if (expect) free(expect);
}
void	test_str_to_size(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                     |CAN SEGV| EXPECTING                 | TEST ARGS */
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "0"                          );
	print_test_str_to_size("str_to_size",               	FALSE,                           1, "1"                          );
	print_test_str_to_size("str_to_size",               	FALSE,                          42, "42"                         );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-42"                        );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-5435"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "--9999999"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-2147483648"                );
	print_test_str_to_size("str_to_size",               	FALSE,                  2147483647, "2147483647"                 );
	print_test_str_to_size("str_to_size",               	FALSE,                        8543, "   8543"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                        3541, "\f3541"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                        5643, "\n5643"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                         397, "\r397+"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                        8513, "\t8513"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "- 45678978748f"             );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "swag123"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "(-(123"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "[12]123"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                          45, "45_"                        );
	print_test_str_to_size("str_to_size",               	FALSE,                        9876, "\v9876-"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                       65435, "65435+--+"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "def58453"                   );
	print_test_str_to_size("str_to_size",               	FALSE,                        5486, "5486helllo"                 );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\f-3541"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\n-5643"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-\r-397+"                   );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "---84648-+"                 );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "&%64"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                         125, "125\n12"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "  -2"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                           2, "  2"                        );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "!789"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "#45"                        );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "$786"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "&789"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "*4456"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, ".1234"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "/1234"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "%1234"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, ",7"                         );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, ",,789"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                         456, "456,78"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, ".456"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                        5896, "  +5896df"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "  + 563"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "++4653"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, " + 45631dsf-+"              );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\200 456"                   );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\255\2543"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\0 456"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\255 5"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\\//\v/789"                 );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "0x123"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "0b1101"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\15124578"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\33124578"                  );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "[124578"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "=0124578"                   );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "_456"                       );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "##4567"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\124578"                    );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\\256"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\\256\\"                    );
	print_test_str_to_size("str_to_size",               	FALSE,              25627165465413, "25627165465413"             );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\\25627165465413"           );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "\2568"                      );
	print_test_str_to_size("str_to_size",               	FALSE,                       30000, "30000f"                     );
	print_test_str_to_size("str_to_size",               	FALSE,                         000, "-500000000000"              );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-6513212312310531"          );
	print_test_str_to_size("str_to_size",               	FALSE,                  2147483648,  "2147483648"                );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-2147483649"                );
	print_test_str_to_size("str_to_size",               	FALSE,                  3000000000,  "3000000000"                );
	print_test_str_to_size("str_to_size",               	FALSE,                           0, "-3000000000"                );
	print_test_str_to_size("str_to_size (n = max)     ",	FALSE,      18446744073709551615UL, "18446744073709551615"       );
	print_test_str_to_size("str_to_size (n = min)     ",	FALSE,                           0, "0"                          );
	print_test_str_to_size("str_to_size (empty str)   ",	FALSE,                           0, ""                           );
	print_test_str_to_size("str_to_size (null str)    ",	TRUE | (1 << 2),                 0, NULL                         );
#ifdef __TEST_OVERFLOW
	print_test_str_to_size("str_to_size (n > max)     ",	FALSE,      18446744073709551616UL, "18446744073709551616"       );
	print_test_str_to_size("str_to_size (n < min)     ",	FALSE,                           0, "-1"                         );
	print_test_str_to_size("str_to_size (n > maxdigit)",	FALSE,     999999999999999999999LL, "999999999999999999999"      );
	print_test_str_to_size("str_to_size (n < maxdigit)",	FALSE,                           0, "-999999999999999999999"     );
#endif
}



/*
**	char*	ft_u8_to_hex(t_s8 n);
*/
void	print_test_u8_to_hex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u8_to_hex(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u8_to_hex", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u8_to_hex(void)
{
printf("\n");
/*	| TEST FUNCTION     | TEST NAME                 |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u8_to_hex("u8_to_hex               ",	FALSE,      "1", 1    );
	print_test_u8_to_hex("u8_to_hex               ",	FALSE,     "2A", 42   );
	print_test_u8_to_hex("u8_to_hex               ",	FALSE,     "6F", 111  );
	print_test_u8_to_hex("u8_to_hex (n = max)     ",	FALSE,     "FF", 255  );
	print_test_u8_to_hex("u8_to_hex (n = min)     ",	FALSE,      "0", 0    );
#ifdef __TEST_OVERFLOW
	print_test_u8_to_hex("u8_to_hex (n > max)     ",	FALSE,    "100", 256  );
	print_test_u8_to_hex("u8_to_hex (n < min)     ",	FALSE,     "-1", -1   );
	print_test_u8_to_hex("u8_to_hex (n > maxdigit)",	FALSE,  "1869F", 99999);
	print_test_u8_to_hex("u8_to_hex (n < maxdigit)",	FALSE, "-1869F",-99999);
#endif
}



/*
**	char*	ft_u16_to_hex(t_s16 n);
*/
void	print_test_u16_to_hex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u16_to_hex(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u16_to_hex", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u16_to_hex(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_u16_to_hex("u16_to_hex               ",	FALSE,        "1", 1      );
	print_test_u16_to_hex("u16_to_hex               ",	FALSE,       "2A", 42     );
	print_test_u16_to_hex("u16_to_hex               ",	FALSE,      "309", 777    );
	print_test_u16_to_hex("u16_to_hex               ",	FALSE,     "2710", 10000  );
	print_test_u16_to_hex("u16_to_hex (n = max)     ",	FALSE,     "FFFF", 65535  );
	print_test_u16_to_hex("u16_to_hex (n = min)     ",	FALSE,        "0", 0      );
#ifdef __TEST_OVERFLOW
	print_test_u16_to_hex("u16_to_hex (n > max)     ",	FALSE,    "10000", 65536  );
	print_test_u16_to_hex("u16_to_hex (n < min)     ",	FALSE,       "-1", -1     );
	print_test_u16_to_hex("u16_to_hex (n > maxdigit)",	FALSE,   "98967F", 9999999);
	print_test_u16_to_hex("u16_to_hex (n < maxdigit)",	FALSE,  "-98967F",-9999999);
#endif
}



/*
**	char*	ft_u32_to_hex(t_s32 n);
*/
void	print_test_u32_to_hex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u32_to_hex(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u32_to_hex", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u32_to_hex(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING     | TEST ARGS */
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,             "1", 1           );
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,            "2A", 42          );
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,             "0", 0           );
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,           "30A", 778         );
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,          "2710", 10000       );
	print_test_u32_to_hex("u32_to_hex               ",	FALSE,       "75BCD15", 123456789   );
	print_test_u32_to_hex("u32_to_hex (n = max)     ",	FALSE,      "FFFFFFFF", 4294967295  );
	print_test_u32_to_hex("u32_to_hex (n = min)     ",	FALSE,             "0", 0           );
#ifdef __TEST_OVERFLOW
	print_test_u32_to_hex("u32_to_hex (n > max)     ",	FALSE,     "100000000", 4294967296  );
	print_test_u32_to_hex("u32_to_hex (n < min)     ",	FALSE,            "-1", -1          );
	print_test_u32_to_hex("u32_to_hex (n > maxdigit)",	FALSE,    "E8D4A50FFF", 999999999999);
	print_test_u32_to_hex("u32_to_hex (n < maxdigit)",	FALSE,   "-E8D4A50FFF",-999999999999);
#endif
}



/*
**	char*	ft_u64_to_hex(t_s64 n);
*/
void	print_test_u64_to_hex(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u64_to_hex(number); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u64_to_hex", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {%s}", expecting);
}
void	test_u64_to_hex(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                 |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,                      "1", 1                     );
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,                     "2A", 42                    );
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,                    "30A", 778                   );
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,                   "2710", 10000                 );
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,                "75BCD15", 123456789             );
	print_test_u64_to_hex("u64_to_hex               ",	FALSE,             "E8D4A50FFF", 999999999999L         );
	print_test_u64_to_hex("u64_to_hex (n = max)     ",	FALSE,       "FFFFFFFFFFFFFFFF", 18446744073709551615UL);
	print_test_u64_to_hex("u64_to_hex (n = min)     ",	FALSE,                      "0", 0                     );
#ifdef __TEST_OVERFLOW
	print_test_u64_to_hex("u64_to_hex (n > max)     ",	FALSE,      "10000000000000000", 18446744073709551616UL);
	print_test_u64_to_hex("u64_to_hex (n < min)     ",	FALSE,                     "-1", -1                    );
	print_test_u64_to_hex("u64_to_hex (n > maxdigit)",	FALSE,                      "0", 999999999999999999999UL);
	print_test_u64_to_hex("u64_to_hex (n < maxdigit)",	FALSE,                      "0",-999999999999999999999UL);
#endif
}



/*
**	t_u8	ft_hex_to_u8(char const *str);
*/
void	print_test_hex_to_u8(char const* test_name, int can_segfault,
		t_u8 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u8 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_hex_to_u8(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u8(test_name, "_hex_to_u8", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_hex_to_u8(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	t_u16	ft_hex_to_u16(char const *str);
*/
void	print_test_hex_to_u16(char const* test_name, int can_segfault,
		t_u16 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u16 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_hex_to_u16(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u16(test_name, "_hex_to_u16", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_hex_to_u16(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	t_u32	ft_hex_to_u32(char const *str);
*/
void	print_test_hex_to_u32(char const* test_name, int can_segfault,
		t_u32 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u32 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_hex_to_u32(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u32(test_name, "_hex_to_u32", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_hex_to_u32(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	t_u64	ft_hex_to_u64(char const *str);
*/
void	print_test_hex_to_u64(char const* test_name, int can_segfault,
		t_u64 expecting,
		char const* number)
{
	t_timer t = {0};
	t_u64 result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_hex_to_u64(number); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_u64(test_name, "_hex_to_u64", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_hex_to_u64(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char*	ft_s8_to_strbase(t_s8 n);
*/
void	print_test_s8_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s8 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s8_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s8_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_s8_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_s8_to_strbase("s8_to_strbase (n = max, dec)",	FALSE,         "127",         127,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n = min, dec)",	FALSE,        "-128",        -128,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n = max, hex)",	FALSE,          "7F",         127, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase (n = min, hex)",	FALSE,         "-80",        -128, "0123456789ABCDEF");
	print_test_s8_to_strbase("s8_to_strbase (n = max, bin)",	FALSE,     "1111111",         127,               "01");
	print_test_s8_to_strbase("s8_to_strbase (n = min, bin)",	FALSE,   "-10000000",        -128,               "01");
	print_test_s8_to_strbase("s8_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_s8_to_strbase("s8_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_s8_to_strbase("s8_to_strbase (n > max)     ",	FALSE,         "128",         128,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n < min)     ",	FALSE,        "-129",        -129,       "0123456789");
	print_test_s8_to_strbase("s8_to_strbase (n > maxdigit)",	FALSE,          NULL,       99999,               "01");
	print_test_s8_to_strbase("s8_to_strbase (n < maxdigit)",	FALSE,          NULL,      -99999,               "01");
#endif
}



/*
**	char*	ft_s16_to_strbase(t_s16 n);
*/
void	print_test_s16_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s16 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s16_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s16_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_s16_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_s16_to_strbase("s16_to_strbase (n = max, dec)",	FALSE,       "32767",       32767,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n = min, dec)",	FALSE,      "-32768",      -32768,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n = max, hex)",	FALSE,        "7FFF",       32767, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase (n = min, hex)",	FALSE,       "-8000",      -32768, "0123456789ABCDEF");
	print_test_s16_to_strbase("s16_to_strbase (n = max, bin)",	FALSE,  "111111111111111",  32767,               "01");
	print_test_s16_to_strbase("s16_to_strbase (n = min, bin)",	FALSE,"-1000000000000000", -32768,               "01");
	print_test_s16_to_strbase("s16_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_s16_to_strbase("s16_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_s16_to_strbase("s16_to_strbase (n > max)     ",	FALSE,       "32768",       32768,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n < min)     ",	FALSE,      "-32769",      -32769,       "0123456789");
	print_test_s16_to_strbase("s16_to_strbase (n > maxdigit)",	FALSE,          NULL,     9999999,               "01");
	print_test_s16_to_strbase("s16_to_strbase (n < maxdigit)",	FALSE,          NULL,    -9999999,               "01");
#endif
}



/*
**	char*	ft_s32_to_strbase(t_s32 n);
*/
void	print_test_s32_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s32 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s32_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s32_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_s32_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING                   | TEST ARGS */
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
	print_test_s32_to_strbase("s32_to_strbase (n = max, dec)",	FALSE,              "2147483647",          2147483647,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n = min, dec)",	FALSE,             "-2147483648",         -2147483648,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n = max, hex)",	FALSE,                "7FFFFFFF",          2147483647, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase (n = min, hex)",	FALSE,               "-80000000",         -2147483648, "0123456789ABCDEF");
	print_test_s32_to_strbase("s32_to_strbase (n = max, bin)",	FALSE,  "1111111111111111111111111111111", 2147483647,               "01");
	print_test_s32_to_strbase("s32_to_strbase (n = min, bin)",	FALSE,"-10000000000000000000000000000000",-2147483648,               "01");
	print_test_s32_to_strbase("s32_to_strbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");
	print_test_s32_to_strbase("s32_to_strbase (null base)   ",	TRUE,                     segstr,                  42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_s32_to_strbase("s32_to_strbase (n > max)     ",	FALSE,              "2147483648",          2147483648,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n < min)     ",	FALSE,             "-2147483649",         -2147483649,       "0123456789");
	print_test_s32_to_strbase("s32_to_strbase (n > maxdigit)",	FALSE,                      NULL,        999999999999,               "01");
	print_test_s32_to_strbase("s32_to_strbase (n < maxdigit)",	FALSE,                      NULL,       -999999999999,               "01");
#endif
}



/*
**	char*	ft_s64_to_strbase(t_s64 n);
*/
void	print_test_s64_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_s64 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_s64_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_s64_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_s64_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_s64_to_strbase("s64_to_strbase (n = max, dec)",	FALSE,   "9223372036854775807",  9223372036854775807,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n = min, dec)",	FALSE,  "-9223372036854775807", -9223372036854775807,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n = max, hex)",	FALSE,      "7FFFFFFFFFFFFFFF",  9223372036854775807, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase (n = min, hex)",	FALSE,     "-7FFFFFFFFFFFFFFF", -9223372036854775807, "0123456789ABCDEF");
	print_test_s64_to_strbase("s64_to_strbase (n = max, bin)",	FALSE, "111111111111111111111111111111111111111111111111111111111111111", 9223372036854775807,"01");
	print_test_s64_to_strbase("s64_to_strbase (n = min, bin)",	FALSE,"-111111111111111111111111111111111111111111111111111111111111111",-9223372036854775807,"01");
	print_test_s64_to_strbase("s64_to_strbase (empty base)  ",	FALSE,                    NULL,                   42,                 "");
	print_test_s64_to_strbase("s64_to_strbase (null base)   ",	TRUE,                   segstr,                   42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_s64_to_strbase("s64_to_strbase (n > max)     ",	FALSE, "9223372036854775808",    9223372036854775808,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n < min)     ",	FALSE,"-9223372036854775808",   -9223372036854775808,       "0123456789");
	print_test_s64_to_strbase("s64_to_strbase (n > maxdigit)",	FALSE,                  NULL,  999999999999999999999,               "01");
	print_test_s64_to_strbase("s64_to_strbase (n < maxdigit)",	FALSE,                  NULL, -999999999999999999999,               "01");
#endif
}



/*
**	char*	ft_u8_to_strbase(t_u8 n);
*/
void	print_test_u8_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u8 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u8_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u8_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_u8_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_u8_to_strbase("u8_to_strbase (n = max, dec)",	FALSE,         "255",         255,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n = min, dec)",	FALSE,           "0",           0,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n = max, hex)",	FALSE,          "FF",         255, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase (n = min, hex)",	FALSE,           "0",           0, "0123456789ABCDEF");
	print_test_u8_to_strbase("u8_to_strbase (n = max, bin)",	FALSE,    "11111111",         255,               "01");
	print_test_u8_to_strbase("u8_to_strbase (n = min, bin)",	FALSE,           "0",           0,               "01");
	print_test_u8_to_strbase("u8_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_u8_to_strbase("u8_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_u8_to_strbase("u8_to_strbase (n > max)     ",	FALSE,         "256",         256,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n < min)     ",	FALSE,          "-1",          -1,       "0123456789");
	print_test_u8_to_strbase("u8_to_strbase (n > maxdigit)",	FALSE,          NULL,       99999,               "01");
	print_test_u8_to_strbase("u8_to_strbase (n < maxdigit)",	FALSE,          NULL,      -99999,               "01");
#endif
}



/*
**	char*	ft_u16_to_strbase(t_u16 n);
*/
void	print_test_u16_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u16 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u16_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u16_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_u16_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_u16_to_strbase("u16_to_strbase (n = max, dec)",	FALSE,       "65535",       65535,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n = min, dec)",	FALSE,           "0",           0,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n = max, hex)",	FALSE,        "FFFF",       65535, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase (n = min, hex)",	FALSE,           "0",           0, "0123456789ABCDEF");
	print_test_u16_to_strbase("u16_to_strbase (n = max, bin)",	FALSE,  "111111111111111",  65535,               "01");
	print_test_u16_to_strbase("u16_to_strbase (n = min, bin)",	FALSE,           "0",           0,               "01");
	print_test_u16_to_strbase("u16_to_strbase (empty base)  ",	FALSE,          NULL,          42,                 "");
	print_test_u16_to_strbase("u16_to_strbase (null base)   ",	TRUE,         segstr,          42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_u16_to_strbase("u16_to_strbase (n > max)     ",	FALSE,       "65536",       65536,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n < min)     ",	FALSE,          "-1",          -1,       "0123456789");
	print_test_u16_to_strbase("u16_to_strbase (n > maxdigit)",	FALSE,          NULL,     9999999,               "01");
	print_test_u16_to_strbase("u16_to_strbase (n < maxdigit)",	FALSE,          NULL,    -9999999,               "01");
#endif
}



/*
**	char*	ft_u32_to_strbase(t_u32 n);
*/
void	print_test_u32_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u32 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u32_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u32_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_u32_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING                   | TEST ARGS */
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
	print_test_u32_to_strbase("u32_to_strbase (n = max, dec)",	FALSE,              "4294967295",          4294967295,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n = min, dec)",	FALSE,                       "0",                   0,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n = max, hex)",	FALSE,                "FFFFFFFF",          4294967295, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase (n = min, hex)",	FALSE,                       "0",                   0, "0123456789ABCDEF");
	print_test_u32_to_strbase("u32_to_strbase (n = max, bin)",	FALSE,  "1111111111111111111111111111111", 4294967295,               "01");
	print_test_u32_to_strbase("u32_to_strbase (n = min, bin)",	FALSE,                       "0",                   0,               "01");
	print_test_u32_to_strbase("u32_to_strbase (empty base)  ",	FALSE,                      NULL,                  42,                 "");
	print_test_u32_to_strbase("u32_to_strbase (null base)   ",	TRUE,                     segstr,                  42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_u32_to_strbase("u32_to_strbase (n > max)     ",	FALSE,              "4294967296",          4294967296,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n < min)     ",	FALSE,                      "-1",                  -1,       "0123456789");
	print_test_u32_to_strbase("u32_to_strbase (n > maxdigit)",	FALSE,                      NULL,        999999999999,               "01");
	print_test_u32_to_strbase("u32_to_strbase (n < maxdigit)",	FALSE,                      NULL,       -999999999999,               "01");
#endif
}



/*
**	char*	ft_u64_to_strbase(t_u64 n);
*/
void	print_test_u64_to_strbase(char const* test_name, int can_segfault,
		char const* expecting,
		t_u64 number,
		char const* base)
{
	t_timer t = {0};
	char* result;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = ft_u64_to_strbase(number, base); timer_clock(&t.end1); } else result = segstr;
	print_test_str(test_name, "_u64_to_strbase", result, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	printf(" -> {base:%s, %s}", base, expecting);
}
void	test_u64_to_strbase(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                      |CAN SEGV|  EXPECTING  | TEST ARGS */
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
	print_test_u64_to_strbase("u64_to_strbase (n = max, dec)",	FALSE, "18446744073709551615", 18446744073709551615UL,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n = min, dec)",	FALSE,                    "0",                      0,       "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n = max, hex)",	FALSE,     "FFFFFFFFFFFFFFFF", 18446744073709551615UL, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase (n = min, hex)",	FALSE,                    "0",                      0, "0123456789ABCDEF");
	print_test_u64_to_strbase("u64_to_strbase (n = max, bin)",	FALSE, "1111111111111111111111111111111111111111111111111111111111111111", 18446744073709551615UL,"01");
	print_test_u64_to_strbase("u64_to_strbase (n = min, bin)",	FALSE,                     "0",                     0,               "01");
	print_test_u64_to_strbase("u64_to_strbase (empty base)  ",	FALSE,                    NULL,                    42,                 "");
	print_test_u64_to_strbase("u64_to_strbase (null base)   ",	TRUE,                   segstr,                    42,               NULL);
#ifdef __TEST_OVERFLOW
	print_test_u64_to_strbase("u64_to_strbase (n > max)     ",	FALSE, "18446744073709551616",   18446744073709551616UL,     "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n < min)     ",	FALSE,                   "-1",                       -1,     "0123456789");
	print_test_u64_to_strbase("u64_to_strbase (n > maxdigit)",	FALSE,                   NULL,  999999999999999999999LL,             "01");
	print_test_u64_to_strbase("u64_to_strbase (n < maxdigit)",	FALSE,                   NULL, -999999999999999999999LL,             "01");
#endif
}



int		test_convert(void)
{

printf("\n");

	printf("       .---------------------------.       \n");
	printf("---==={  LIBFT TEST: libft_convert  }===---\n");
	printf("       '---------------------------'       \n");

	print_nonstd();

	test_s8_to_str();
	test_s16_to_str();
	test_s32_to_str();
	test_s64_to_str();

	test_u8_to_str();
	test_u16_to_str();
	test_u32_to_str();
	test_u64_to_str();

	test_f32_to_str();
	test_f64_to_str();

	test_bool_to_str();
	test_size_to_str();

	test_u8_to_hex();
	test_u16_to_hex();
	test_u32_to_hex();
	test_u64_to_hex();

	test_s8_to_strbase();
	test_s16_to_strbase();
	test_s32_to_strbase();
	test_s64_to_strbase();

	test_u8_to_strbase();
	test_u16_to_strbase();
	test_u32_to_strbase();
	test_u64_to_strbase();



	test_str_to_s8();
	test_str_to_s16();
	test_str_to_s32();
	test_str_to_s64();

	test_str_to_u8();
	test_str_to_u16();
	test_str_to_u32();
	test_str_to_u64();

//	test_str_to_f32();
	test_str_to_f64();

//	test_str_to_bool();
	test_str_to_size();

//	test_hex_to_u8();
//	test_hex_to_u16();
//	test_hex_to_u32();
//	test_hex_to_u64();

//	test_strbase_to_s8();
//	test_strbase_to_s16();
//	test_strbase_to_s32();
//	test_strbase_to_s64();

//	test_strbase_to_u8();
//	test_strbase_to_u16();
//	test_strbase_to_u32();
//	test_strbase_to_u64();

printf("\n");

	return (OK);
}
