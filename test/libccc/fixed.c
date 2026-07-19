
#include "libccc.h"
#include "libccc/fixed.h"
#include "libccc/string.h"
#include "libccc/text/format.h"
#include "libccc/sys/io.h"
#include "libccc/math.h"

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
||                             Utility functions                              ||
\*============================================================================*/

//! Constructs a fixed-point value from a raw integer expression
#define QRAW(BITS, EXPR)	((t_q##BITS){ (t_s##BITS)(EXPR) })


//! Per-type helpers to compute expected values with independent (wide, saturating) arithmetic
#define DEFINEFUNC_FIXED_TESTUTILS(BITS, WB) \
static \
t_q##BITS	testref_q##BITS##_saturate(t_s64 raw) \
{ \
	if ((t_s##WB)raw > (t_s##WB)Q##BITS##_MAX_VAL._) \
		return (Q##BITS##_MAX); \
	if ((t_s##WB)raw < (t_s##WB)Q##BITS##_MIN_VAL._) \
		return (Q##BITS##_MIN); \
	return ((t_q##BITS){ (t_s##BITS)raw }); \
} \
static \
t_q##BITS	testref_q##BITS##_from(t_s64 numerator, t_s64 denominator) \
{ \
	if (denominator == 0) \
		return (Q##BITS##_ERROR); \
	return (testref_q##BITS##_saturate(numerator * (t_s64)Q##BITS##_DENOM / denominator)); \
} \
static \
t_q##BITS	testref_q##BITS##_fromfloat(t_f64 number) \
{ \
	if (F64_IsNaN(number)) \
		return (Q##BITS##_ERROR); \
	if (F64_IsInf(number)) \
		return ((number < 0) ? Q##BITS##_MIN : Q##BITS##_MAX); \
	if (number > (t_f64)Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM) \
		return (Q##BITS##_MAX); \
	if (number < (t_f64)Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM) \
		return (Q##BITS##_MIN); \
	if (number != 0. && F64_Abs(number) < 1. / Q##BITS##_DENOM) \
		return ((t_q##BITS){ 0 }); \
	return ((t_q##BITS){ (t_s##BITS)( \
		(t_s##BITS)(F64_Trunc(number) * Q##BITS##_DENOM) + \
		(t_s##BITS)(F64_Mod(number, 1.) * Q##BITS##_DENOM)) }); \
} \

DEFINEFUNC_FIXED_TESTUTILS(8, 64)
DEFINEFUNC_FIXED_TESTUTILS(16, 64)
DEFINEFUNC_FIXED_TESTUTILS(32, 64)
DEFINEFUNC_FIXED_TESTUTILS(64, 64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXED_TESTUTILS(128, 128)
#endif



/*============================================================================*\
||                       Convert Fixed-point to Strings                       ||
\*============================================================================*/

#define DEFINETEST_FIXED_TO_STR(BITS) \
void	print_test_q##BITS##tostr(char const* test_name, t_testflags flags, \
		char const* expecting, \
		t_q##BITS number) \
{ \
	TEST_INIT(str) \
	TEST_PERFORM(	q##BITS##tostr, number) \
	TEST_PRINT(str,	q##BITS##tostr, "number=" SF_Q##BITS, number) \
	TEST_FREE() \
} \
void	test_q##BITS##tostr(void) \
{ \
	t_s64 const	raw_values[] = { \
		0, +1, -1, +2, -2, +3, -3, \
		(t_s64)(Q##BITS##_DENOM / 2), \
		-(t_s64)(Q##BITS##_DENOM / 2), \
		(t_s64)Q##BITS##_DENOM, \
		-(t_s64)Q##BITS##_DENOM, \
		(t_s64)(Q##BITS##_DENOM * 3 / 2), \
		-(t_s64)(Q##BITS##_DENOM * 3 / 2), \
		(t_s64)(Q##BITS##_DENOM * 2), \
		(t_s64)(Q##BITS##_DENOM * 5 / 2), \
		(t_s64)(Q##BITS##_DENOM * 10), \
		-(t_s64)(Q##BITS##_DENOM * 10), \
		(t_s64)(Q##BITS##_DENOM * 31), \
		-(t_s64)(Q##BITS##_DENOM * 31), \
		(t_s64)Q##BITS##_MAX_VAL._, \
		(t_s64)Q##BITS##_MIN_VAL._, \
	}; \
	for (t_uint i = 0; i < (sizeof(raw_values) / sizeof(raw_values[0])); ++i) \
	{ \
		t_q##BITS const	number = QRAW(BITS, raw_values[i]); \
		char*	expected = String_Format(SF_S64".("SF_S64"/"SF_S64")", \
			(t_s64)(number._ / Q##BITS##_DENOM), \
			(t_s64)(number._ % Q##BITS##_DENOM), \
			(t_s64)Q##BITS##_DENOM); \
		print_test_q##BITS##tostr("q"#BITS"tostr ",	FALSE, expected, number); \
		free(expected); \
	} \
	print_test_q##BITS##tostr("q"#BITS"tostr (nan) ",	FALSE, "NAN",       Q##BITS##_ERROR); \
	print_test_q##BITS##tostr("q"#BITS"tostr (+inf)",	FALSE, "+INFINITY", Q##BITS##_MAX); \
	print_test_q##BITS##tostr("q"#BITS"tostr (-inf)",	FALSE, "-INFINITY", Q##BITS##_MIN); \
} \

DEFINETEST_FIXED_TO_STR(8)
DEFINETEST_FIXED_TO_STR(16)
DEFINETEST_FIXED_TO_STR(32)
DEFINETEST_FIXED_TO_STR(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_TO_STR(128)
#endif



/*============================================================================*\
||                       Convert Strings to Fixed-point                       ||
\*============================================================================*/

#define DEFINETEST_STR_TO_FIXED(BITS) \
void	print_test_strtoq##BITS(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		char const* str) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		strtoq##BITS, str) \
	TEST_PRINT(q##BITS,	strtoq##BITS, "str=\"%s\"", str) \
} \
void	test_strtoq##BITS(void) \
{ \
	t_s64 const	d = (t_s64)Q##BITS##_DENOM; \
/*	| TEST FUNCTION           | TEST NAME                |TESTFLAG| EXPECTING                                        | TEST ARGS         */ \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(0),                      "0"               ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(d),                      "1"               ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(-d),                     "-1"              ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(d * 2),                  "+2"              ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(d * 10),                 "10"              ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(d * 25),                 "25"              ); \
	print_test_strtoq##BITS("strtoq"#BITS"               ",	FALSE, testref_q##BITS##_saturate(d * -25),                "-25"             ); \
	print_test_strtoq##BITS("strtoq"#BITS" (whitespace)  ",	FALSE, testref_q##BITS##_saturate(d * 5),                  "   5"            ); \
	print_test_strtoq##BITS("strtoq"#BITS" (whitespace)  ",	FALSE, testref_q##BITS##_saturate(d * 3),                  "\t\n 3"          ); \
	print_test_strtoq##BITS("strtoq"#BITS" (saturate)    ",	FALSE, testref_q##BITS##_saturate(d * 125),                "125"             ); \
	print_test_strtoq##BITS("strtoq"#BITS" (saturate)    ",	FALSE, testref_q##BITS##_saturate(d * -125),               "-125"            ); \
	if ((t_u64)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM) < ((t_u64)S64_MAX / 2)) \
	{ \
		char*	str_over  = String_Format(SF_S64, (t_s64)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM) + 1); \
		char*	str_under = String_Format(SF_S64, (t_s64)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM) - 1); \
		print_test_strtoq##BITS("strtoq"#BITS" (saturate)    ",	FALSE, Q##BITS##_MAX, str_over ); \
		print_test_strtoq##BITS("strtoq"#BITS" (saturate)    ",	FALSE, Q##BITS##_MIN, str_under); \
		free(str_over); \
		free(str_under); \
	} \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(d + 2 * d / 4),          "1.(2/4)"         ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(d / 2),                  "(1/2)"           ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(3 * d / 4),              "(3/4)"           ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(-3 * d / 4),             "(-3/4)"          ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(d / 3),                  "(1/3)"           ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(d * 2 + d / 2),          "2.(1/2)"         ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(-d + -2 * d / 4),        "-1.(-2/4)"       ); \
	print_test_strtoq##BITS("strtoq"#BITS" (fraction)    ",	FALSE, testref_q##BITS##_saturate(d * 3 + d / 2),          " 3. (1 / 2)"     ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    ""                ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "abc"             ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "1.5"             ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "(1/0)"           ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "5)"              ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "--3"             ); \
	print_test_strtoq##BITS("strtoq"#BITS" (error)       ",	FALSE, Q##BITS##_ERROR,                                    "(1/)"            ); \
} \

DEFINETEST_STR_TO_FIXED(8)
DEFINETEST_STR_TO_FIXED(16)
DEFINETEST_STR_TO_FIXED(32)
DEFINETEST_STR_TO_FIXED(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_STR_TO_FIXED(128)
#endif



/*============================================================================*\
||                    Create Fixed-point from a fraction                      ||
\*============================================================================*/

#define DEFINETEST_FIXED_FROM(BITS) \
void	print_test_q##BITS##from(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_s##BITS numerator, \
		t_s##BITS denominator) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		toq##BITS, numerator, denominator) \
	TEST_PRINT(q##BITS,	toq##BITS, "numerator=" SF_S64 ", denominator=" SF_S64, (t_s64)numerator, (t_s64)denominator) \
} \
void	test_q##BITS##from(void) \
{ \
	t_s64 const	numerators[]   = { 0, +1, -1, +2, +3, +5, +7, +10, +42, -42, +100, -100 }; \
	t_s64 const	denominators[] = { 1, 2, 3, 4, -4, 7, 100 }; \
	for (t_uint i = 0; i < (sizeof(numerators)   / sizeof(numerators[0]));   ++i) \
	for (t_uint j = 0; j < (sizeof(denominators) / sizeof(denominators[0])); ++j) \
	{ \
		t_s64 const	numerator   = numerators[i]; \
		t_s64 const	denominator = denominators[j]; \
		if (numerator   > (t_s64)S##BITS##_MAX || numerator   < (t_s64)S##BITS##_MIN)	continue; \
		if (denominator > (t_s64)S##BITS##_MAX || denominator < (t_s64)S##BITS##_MIN)	continue; \
		print_test_q##BITS##from("q"#BITS"from ",	FALSE, \
			testref_q##BITS##_from(numerator, denominator), \
			(t_s##BITS)numerator, (t_s##BITS)denominator); \
	} \
/*	| TEST FUNCTION            | TEST NAME               |TESTFLAG| EXPECTING       | TEST ARGS                        */ \
	print_test_q##BITS##from("q"#BITS"from (div by 0)",	FALSE, Q##BITS##_ERROR,     10,             0                  ); \
	print_test_q##BITS##from("q"#BITS"from (saturate)",	FALSE, Q##BITS##_MAX,       S##BITS##_MAX,  1                  ); \
	print_test_q##BITS##from("q"#BITS"from (saturate)",	FALSE, Q##BITS##_MIN,       S##BITS##_MIN,  1                  ); \
	print_test_q##BITS##from("q"#BITS"from (tiny)    ",	FALSE, QRAW(BITS, 0),       1,              S##BITS##_MAX      ); \
	print_test_q##BITS##from("q"#BITS"from (one)     ",	FALSE, QRAW(BITS, Q##BITS##_DENOM), S##BITS##_MAX, S##BITS##_MAX ); \
} \

DEFINETEST_FIXED_FROM(8)
DEFINETEST_FIXED_FROM(16)
DEFINETEST_FIXED_FROM(32)
DEFINETEST_FIXED_FROM(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_FROM(128)
#endif



/*============================================================================*\
||                       Integer part / Fraction part                         ||
\*============================================================================*/

#define DEFINETEST_FIXED_INTEGERPART(BITS) \
void	print_test_q##BITS##_integerpart(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_q##BITS number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		q##BITS##_integerpart, number) \
	TEST_PRINT(q##BITS,	q##BITS##_integerpart, "number=" SF_Q##BITS, number) \
} \
void	test_q##BITS##_integerpart(void) \
{ \
	t_s64 const	raw_values[] = { \
		0, +1, -1, +2, -2, +3, -3, \
		(t_s64)(Q##BITS##_DENOM / 2),      -(t_s64)(Q##BITS##_DENOM / 2), \
		(t_s64)Q##BITS##_DENOM,            -(t_s64)Q##BITS##_DENOM, \
		(t_s64)(Q##BITS##_DENOM * 3 / 2),  -(t_s64)(Q##BITS##_DENOM * 3 / 2), \
		(t_s64)(Q##BITS##_DENOM * 5 / 2),  -(t_s64)(Q##BITS##_DENOM * 5 / 2), \
		(t_s64)(Q##BITS##_DENOM * 10),     -(t_s64)(Q##BITS##_DENOM * 10), \
		(t_s64)Q##BITS##_MAX_VAL._,        (t_s64)Q##BITS##_MIN_VAL._, \
	}; \
	for (t_uint i = 0; i < (sizeof(raw_values) / sizeof(raw_values[0])); ++i) \
	{ \
		t_s64 const	raw = raw_values[i]; \
		print_test_q##BITS##_integerpart("q"#BITS"_integerpart ",	FALSE, \
			QRAW(BITS, (raw / (t_s64)Q##BITS##_DENOM) * (t_s64)Q##BITS##_DENOM), \
			QRAW(BITS, raw)); \
	} \
	print_test_q##BITS##_integerpart("q"#BITS"_integerpart (nan) ",	FALSE, Q##BITS##_ERROR, Q##BITS##_ERROR); \
	print_test_q##BITS##_integerpart("q"#BITS"_integerpart (+inf)",	FALSE, Q##BITS##_MAX,   Q##BITS##_MAX  ); \
	print_test_q##BITS##_integerpart("q"#BITS"_integerpart (-inf)",	FALSE, Q##BITS##_MIN,   Q##BITS##_MIN  ); \
} \

DEFINETEST_FIXED_INTEGERPART(8)
DEFINETEST_FIXED_INTEGERPART(16)
DEFINETEST_FIXED_INTEGERPART(32)
DEFINETEST_FIXED_INTEGERPART(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_INTEGERPART(128)
#endif

#define DEFINETEST_FIXED_FRACTIONPART(BITS) \
void	print_test_q##BITS##_fractionpart(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_q##BITS number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		q##BITS##_fractionpart, number) \
	TEST_PRINT(q##BITS,	q##BITS##_fractionpart, "number=" SF_Q##BITS, number) \
} \
void	test_q##BITS##_fractionpart(void) \
{ \
	t_s64 const	raw_values[] = { \
		0, +1, -1, +2, -2, +3, -3, \
		(t_s64)(Q##BITS##_DENOM / 2),      -(t_s64)(Q##BITS##_DENOM / 2), \
		(t_s64)Q##BITS##_DENOM,            -(t_s64)Q##BITS##_DENOM, \
		(t_s64)(Q##BITS##_DENOM * 3 / 2),  -(t_s64)(Q##BITS##_DENOM * 3 / 2), \
		(t_s64)(Q##BITS##_DENOM * 5 / 2),  -(t_s64)(Q##BITS##_DENOM * 5 / 2), \
		(t_s64)(Q##BITS##_DENOM * 10),     -(t_s64)(Q##BITS##_DENOM * 10), \
		(t_s64)Q##BITS##_MAX_VAL._,        (t_s64)Q##BITS##_MIN_VAL._, \
	}; \
	for (t_uint i = 0; i < (sizeof(raw_values) / sizeof(raw_values[0])); ++i) \
	{ \
		t_s64 const	raw = raw_values[i]; \
		print_test_q##BITS##_fractionpart("q"#BITS"_fractionpart ",	FALSE, \
			QRAW(BITS, raw % (t_s64)Q##BITS##_DENOM), \
			QRAW(BITS, raw)); \
	} \
	print_test_q##BITS##_fractionpart("q"#BITS"_fractionpart (nan) ",	FALSE, Q##BITS##_ERROR, Q##BITS##_ERROR); \
	print_test_q##BITS##_fractionpart("q"#BITS"_fractionpart (+inf)",	FALSE, QRAW(BITS, 0),   Q##BITS##_MAX  ); \
	print_test_q##BITS##_fractionpart("q"#BITS"_fractionpart (-inf)",	FALSE, QRAW(BITS, 0),   Q##BITS##_MIN  ); \
} \

DEFINETEST_FIXED_FRACTIONPART(8)
DEFINETEST_FIXED_FRACTIONPART(16)
DEFINETEST_FIXED_FRACTIONPART(32)
DEFINETEST_FIXED_FRACTIONPART(64)
#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_FRACTIONPART(128)
#endif



/*============================================================================*\
||                     Convert Integers to Fixed-point                        ||
\*============================================================================*/

/*
**	NOTE: `WB` is the amount of bits for the "wide" intermediate integer type
**	used to compute expected values without overflow (64, or 128 for the largest types).
*/

#define DEFINETEST_UINT_TO_FIXED(BITS, FROM, WB) \
void	print_test_u##FROM##toq##BITS(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_u##FROM number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		u##FROM##toq##BITS, number) \
	TEST_PRINT(q##BITS,	u##FROM##toq##BITS, "number=" SF_U64, (t_u64)number) \
} \
void	test_u##FROM##toq##BITS(void) \
{ \
	t_u64 const	values[] = { \
		0, 1, 2, 3, 10, 31, 32, 42, 100, 111, \
		127, 128, 255, 256, \
		32767, 32768, 65535, 65536, \
		2147483647llu, 2147483648llu, 4294967295llu, 4294967296llu, \
		140737488355327llu, 140737488355328llu, /* 2^47-1, 2^47 */ \
		9223372036854775807llu, /* 2^63-1 */ \
	}; \
	for (t_uint i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) \
	{ \
		t_u64 const	value = values[i]; \
		if (value > (t_u64)U##FROM##_MAX) \
			continue; \
		t_q##BITS const	expected = (((t_u##WB)value > (t_u##WB)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)) ? \
			Q##BITS##_MAX : QRAW(BITS, (t_s##WB)value * (t_s##WB)Q##BITS##_DENOM)); \
		print_test_u##FROM##toq##BITS("u"#FROM"toq"#BITS" ",	FALSE, expected, (t_u##FROM)value); \
	} \
} \

#define DEFINETEST_SINT_TO_FIXED(BITS, FROM, WB) \
void	print_test_s##FROM##toq##BITS(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_s##FROM number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		s##FROM##toq##BITS, number) \
	TEST_PRINT(q##BITS,	s##FROM##toq##BITS, "number=" SF_S64, (t_s64)number) \
} \
void	test_s##FROM##toq##BITS(void) \
{ \
	t_s64 const	values[] = { \
		0, +1, -1, +2, -2, +3, -3, +10, -10, \
		+31, -31, +32, -32, +42, -42, +100, -100, +111, -111, \
		+127, -127, -128, +128, +255, +256, \
		+32767, -32767, -32768, +32768, +65535, +65536, \
		+2147483647ll, -2147483647ll, -2147483648ll, +2147483648ll, \
		+140737488355327ll, -140737488355327ll, /* +/- (2^47-1) */ \
		+9223372036854775807ll, -9223372036854775807ll - 1, \
	}; \
	for (t_uint i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) \
	{ \
		t_s64 const	value = values[i]; \
		if (value > (t_s64)S##FROM##_MAX || value < (t_s64)S##FROM##_MIN) \
			continue; \
		t_q##BITS	expected; \
		if ((t_s##WB)value > (t_s##WB)(Q##BITS##_MAX_VAL._ / Q##BITS##_DENOM)) \
			expected = Q##BITS##_MAX; \
		else if ((t_s##WB)value < (t_s##WB)(Q##BITS##_MIN_VAL._ / Q##BITS##_DENOM)) \
			expected = Q##BITS##_MIN; \
		else \
			expected = QRAW(BITS, (t_s##WB)value * (t_s##WB)Q##BITS##_DENOM); \
		print_test_s##FROM##toq##BITS("s"#FROM"toq"#BITS" ",	FALSE, expected, (t_s##FROM)value); \
	} \
} \

DEFINETEST_UINT_TO_FIXED(8, 8, 64)
DEFINETEST_UINT_TO_FIXED(8, 16, 64)
DEFINETEST_UINT_TO_FIXED(8, 32, 64)
DEFINETEST_UINT_TO_FIXED(8, 64, 64)

DEFINETEST_UINT_TO_FIXED(16, 8, 64)
DEFINETEST_UINT_TO_FIXED(16, 16, 64)
DEFINETEST_UINT_TO_FIXED(16, 32, 64)
DEFINETEST_UINT_TO_FIXED(16, 64, 64)

DEFINETEST_UINT_TO_FIXED(32, 8, 64)
DEFINETEST_UINT_TO_FIXED(32, 16, 64)
DEFINETEST_UINT_TO_FIXED(32, 32, 64)
DEFINETEST_UINT_TO_FIXED(32, 64, 64)

DEFINETEST_UINT_TO_FIXED(64, 8, 64)
DEFINETEST_UINT_TO_FIXED(64, 16, 64)
DEFINETEST_UINT_TO_FIXED(64, 32, 64)
DEFINETEST_UINT_TO_FIXED(64, 64, 64)

#if LIBCONFIG_USE_INT128
DEFINETEST_UINT_TO_FIXED(8, 128, 128)
DEFINETEST_UINT_TO_FIXED(16, 128, 128)
DEFINETEST_UINT_TO_FIXED(32, 128, 128)
DEFINETEST_UINT_TO_FIXED(64, 128, 128)
DEFINETEST_UINT_TO_FIXED(128, 8, 128)
DEFINETEST_UINT_TO_FIXED(128, 16, 128)
DEFINETEST_UINT_TO_FIXED(128, 32, 128)
DEFINETEST_UINT_TO_FIXED(128, 64, 128)
DEFINETEST_UINT_TO_FIXED(128, 128, 128)
#endif


DEFINETEST_SINT_TO_FIXED(8, 8, 64)
DEFINETEST_SINT_TO_FIXED(8, 16, 64)
DEFINETEST_SINT_TO_FIXED(8, 32, 64)
DEFINETEST_SINT_TO_FIXED(8, 64, 64)

DEFINETEST_SINT_TO_FIXED(16, 8, 64)
DEFINETEST_SINT_TO_FIXED(16, 16, 64)
DEFINETEST_SINT_TO_FIXED(16, 32, 64)
DEFINETEST_SINT_TO_FIXED(16, 64, 64)

DEFINETEST_SINT_TO_FIXED(32, 8, 64)
DEFINETEST_SINT_TO_FIXED(32, 16, 64)
DEFINETEST_SINT_TO_FIXED(32, 32, 64)
DEFINETEST_SINT_TO_FIXED(32, 64, 64)

DEFINETEST_SINT_TO_FIXED(64, 8, 64)
DEFINETEST_SINT_TO_FIXED(64, 16, 64)
DEFINETEST_SINT_TO_FIXED(64, 32, 64)
DEFINETEST_SINT_TO_FIXED(64, 64, 64)

#if LIBCONFIG_USE_INT128
DEFINETEST_SINT_TO_FIXED(8, 128, 128)
DEFINETEST_SINT_TO_FIXED(16, 128, 128)
DEFINETEST_SINT_TO_FIXED(32, 128, 128)
DEFINETEST_SINT_TO_FIXED(64, 128, 128)
DEFINETEST_SINT_TO_FIXED(128, 8, 128)
DEFINETEST_SINT_TO_FIXED(128, 16, 128)
DEFINETEST_SINT_TO_FIXED(128, 32, 128)
DEFINETEST_SINT_TO_FIXED(128, 64, 128)
DEFINETEST_SINT_TO_FIXED(128, 128, 128)
#endif




/*============================================================================*\
||                Convert Fixed-point to other Fixed-point types              ||
\*============================================================================*/

#define DEFINETEST_FIXED_TO_FIXED(BITS, FROM, WB) \
void	print_test_q##FROM##toq##BITS(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_q##FROM number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		q##FROM##toq##BITS, number) \
	TEST_PRINT(q##BITS,	q##FROM##toq##BITS, "number=" SF_Q##FROM, number) \
} \
void	test_q##FROM##toq##BITS(void) \
{ \
	t_s64 const	raw_values[] = { \
		0, +1, -1, +2, -2, +3, -3, \
		(t_s64)(Q##FROM##_DENOM / 2),      -(t_s64)(Q##FROM##_DENOM / 2), \
		(t_s64)(Q##FROM##_DENOM * 1),      -(t_s64)(Q##FROM##_DENOM * 1), \
		(t_s64)(Q##FROM##_DENOM * 3 / 2),  -(t_s64)(Q##FROM##_DENOM * 3 / 2), \
		(t_s64)(Q##FROM##_DENOM * 5 / 2),  -(t_s64)(Q##FROM##_DENOM * 5 / 2), \
		(t_s64)(Q##FROM##_DENOM * 31),     -(t_s64)(Q##FROM##_DENOM * 31), \
		(t_s64)(Q##FROM##_DENOM * 42),     -(t_s64)(Q##FROM##_DENOM * 42), \
		(t_s64)(Q##FROM##_DENOM * 2000),   -(t_s64)(Q##FROM##_DENOM * 2000), \
		(t_s64)(Q##FROM##_DENOM * 600000), -(t_s64)(Q##FROM##_DENOM * 600000), \
	}; \
	for (t_uint i = 0; i < (sizeof(raw_values) / sizeof(raw_values[0])); ++i) \
	{ \
		t_s64 const	raw = raw_values[i]; \
		if (raw > (t_s64)Q##FROM##_MAX_VAL._ || raw < (t_s64)Q##FROM##_MIN_VAL._) \
			continue; \
		/* rescale the raw value from the source scale to the destination scale (truncated toward zero) */ \
		t_s##WB const	value = \
			(t_s##WB)(raw / (t_s64)Q##FROM##_DENOM) * Q##BITS##_DENOM + \
			(t_s##WB)(raw % (t_s64)Q##FROM##_DENOM) * Q##BITS##_DENOM / Q##FROM##_DENOM; \
		t_q##BITS	expected; \
		if (value > (t_s##WB)Q##BITS##_MAX_VAL._) \
			expected = Q##BITS##_MAX; \
		else if (value < (t_s##WB)Q##BITS##_MIN_VAL._) \
			expected = Q##BITS##_MIN; \
		else \
			expected = QRAW(BITS, value); \
		print_test_q##FROM##toq##BITS("q"#FROM"toq"#BITS" ",	FALSE, expected, (t_q##FROM){ (t_s##FROM)raw }); \
	} \
/*	| TEST FUNCTION               | TEST NAME                 |TESTFLAG| EXPECTING       | TEST ARGS       */ \
	print_test_q##FROM##toq##BITS("q"#FROM"toq"#BITS" (nan) ",	FALSE, Q##BITS##_ERROR,    Q##FROM##_ERROR  ); \
	print_test_q##FROM##toq##BITS("q"#FROM"toq"#BITS" (+inf)",	FALSE, Q##BITS##_MAX,      Q##FROM##_MAX    ); \
	print_test_q##FROM##toq##BITS("q"#FROM"toq"#BITS" (-inf)",	FALSE, Q##BITS##_MIN,      Q##FROM##_MIN    ); \
} \

DEFINETEST_FIXED_TO_FIXED(8, 8, 64)
DEFINETEST_FIXED_TO_FIXED(8, 16, 64)
DEFINETEST_FIXED_TO_FIXED(8, 32, 64)
DEFINETEST_FIXED_TO_FIXED(8, 64, 64)

DEFINETEST_FIXED_TO_FIXED(16, 8, 64)
DEFINETEST_FIXED_TO_FIXED(16, 16, 64)
DEFINETEST_FIXED_TO_FIXED(16, 32, 64)
DEFINETEST_FIXED_TO_FIXED(16, 64, 64)

DEFINETEST_FIXED_TO_FIXED(32, 8, 64)
DEFINETEST_FIXED_TO_FIXED(32, 16, 64)
DEFINETEST_FIXED_TO_FIXED(32, 32, 64)
DEFINETEST_FIXED_TO_FIXED(32, 64, 64)

DEFINETEST_FIXED_TO_FIXED(64, 8, 64)
DEFINETEST_FIXED_TO_FIXED(64, 16, 64)
DEFINETEST_FIXED_TO_FIXED(64, 32, 64)
DEFINETEST_FIXED_TO_FIXED(64, 64, 64)

#if LIBCONFIG_USE_INT128
DEFINETEST_FIXED_TO_FIXED(8, 128, 128)
DEFINETEST_FIXED_TO_FIXED(16, 128, 128)
DEFINETEST_FIXED_TO_FIXED(32, 128, 128)
DEFINETEST_FIXED_TO_FIXED(64, 128, 128)
DEFINETEST_FIXED_TO_FIXED(128, 8, 128)
DEFINETEST_FIXED_TO_FIXED(128, 16, 128)
DEFINETEST_FIXED_TO_FIXED(128, 32, 128)
DEFINETEST_FIXED_TO_FIXED(128, 64, 128)
DEFINETEST_FIXED_TO_FIXED(128, 128, 128)
#endif


/*============================================================================*\
||                 Convert Floating-point to Fixed-point                      ||
\*============================================================================*/

#define DEFINETEST_FLOAT_TO_FIXED(BITS, FROM) \
void	print_test_f##FROM##toq##BITS(char const* test_name, t_testflags flags, \
		t_q##BITS expecting, \
		t_f##FROM number) \
{ \
	TEST_INIT(q##BITS) \
	TEST_PERFORM(		f##FROM##toq##BITS, number) \
	TEST_PRINT(q##BITS,	f##FROM##toq##BITS, "number=%g", (double)number) \
} \
void	test_f##FROM##toq##BITS(void) \
{ \
	t_f64 const	values[] = { \
		0., \
		+1.,        -1., \
		+0.25,      -0.25, \
		+0.5,       -0.5, \
		+1.5,       -1.5, \
		+2.75,      -2.75, \
		+10.125,    -10.125, \
		+31.,       -31., \
		+42.0625,   -42.0625, \
		+100.5,     -100.5, \
		+2000.5,    -2000.5, \
		+123456.75, -123456.75, \
		+1e9,       -1e9, \
		+1e18,      -1e18, \
		+0.001,     -0.001, \
		+1e-9,      -1e-9, \
	}; \
	for (t_uint i = 0; i < (sizeof(values) / sizeof(values[0])); ++i) \
	{ \
		t_f##FROM const	value = (t_f##FROM)values[i]; \
		print_test_f##FROM##toq##BITS("f"#FROM"toq"#BITS" ",	FALSE, \
			testref_q##BITS##_fromfloat((t_f64)value), (t_f##FROM)value); \
	} \
/*	| TEST FUNCTION               | TEST NAME                 |TESTFLAG| EXPECTING       | TEST ARGS               */ \
	print_test_f##FROM##toq##BITS("f"#FROM"toq"#BITS" (nan) ",	FALSE, Q##BITS##_ERROR,    (t_f##FROM)NAN       ); \
	print_test_f##FROM##toq##BITS("f"#FROM"toq"#BITS" (+inf)",	FALSE, Q##BITS##_MAX,      (t_f##FROM)+INFINITY ); \
	print_test_f##FROM##toq##BITS("f"#FROM"toq"#BITS" (-inf)",	FALSE, Q##BITS##_MIN,      (t_f##FROM)-INFINITY ); \
} \

DEFINETEST_FLOAT_TO_FIXED(8, 32)
DEFINETEST_FLOAT_TO_FIXED(16, 32)
DEFINETEST_FLOAT_TO_FIXED(32, 32)
DEFINETEST_FLOAT_TO_FIXED(64, 32)

DEFINETEST_FLOAT_TO_FIXED(8, 64)
DEFINETEST_FLOAT_TO_FIXED(16, 64)
DEFINETEST_FLOAT_TO_FIXED(32, 64)
DEFINETEST_FLOAT_TO_FIXED(64, 64)

#if LIBCONFIG_USE_INT128
DEFINETEST_FLOAT_TO_FIXED(128, 32)
DEFINETEST_FLOAT_TO_FIXED(128, 64)
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



int		testsuite_fixed(void)
{
	print_suite_title("libccc/fixed");

	print_nonstd();

	test_q8tostr();
	test_q16tostr();
	test_q32tostr();
	test_q64tostr();
#if LIBCONFIG_USE_INT128
	test_q128tostr();
#endif

	test_strtoq8();
	test_strtoq16();
	test_strtoq32();
	test_strtoq64();
#if LIBCONFIG_USE_INT128
	test_strtoq128();
#endif

	test_q8from();
	test_q16from();
	test_q32from();
	test_q64from();
#if LIBCONFIG_USE_INT128
	test_q128from();
#endif

	test_q8_integerpart();
	test_q16_integerpart();
	test_q32_integerpart();
	test_q64_integerpart();
#if LIBCONFIG_USE_INT128
	test_q128_integerpart();
#endif

	test_q8_fractionpart();
	test_q16_fractionpart();
	test_q32_fractionpart();
	test_q64_fractionpart();
#if LIBCONFIG_USE_INT128
	test_q128_fractionpart();
#endif

	test_u8toq8();
	test_u16toq8();
	test_u32toq8();
	test_u64toq8();
	test_u8toq16();
	test_u16toq16();
	test_u32toq16();
	test_u64toq16();
	test_u8toq32();
	test_u16toq32();
	test_u32toq32();
	test_u64toq32();
	test_u8toq64();
	test_u16toq64();
	test_u32toq64();
	test_u64toq64();
#if LIBCONFIG_USE_INT128
	test_u128toq8();
	test_u128toq16();
	test_u128toq32();
	test_u128toq64();
	test_u8toq128();
	test_u16toq128();
	test_u32toq128();
	test_u64toq128();
	test_u128toq128();
#endif

	test_s8toq8();
	test_s16toq8();
	test_s32toq8();
	test_s64toq8();
	test_s8toq16();
	test_s16toq16();
	test_s32toq16();
	test_s64toq16();
	test_s8toq32();
	test_s16toq32();
	test_s32toq32();
	test_s64toq32();
	test_s8toq64();
	test_s16toq64();
	test_s32toq64();
	test_s64toq64();
#if LIBCONFIG_USE_INT128
	test_s128toq8();
	test_s128toq16();
	test_s128toq32();
	test_s128toq64();
	test_s8toq128();
	test_s16toq128();
	test_s32toq128();
	test_s64toq128();
	test_s128toq128();
#endif

	test_q8toq8();
	test_q16toq8();
	test_q32toq8();
	test_q64toq8();
	test_q8toq16();
	test_q16toq16();
	test_q32toq16();
	test_q64toq16();
	test_q8toq32();
	test_q16toq32();
	test_q32toq32();
	test_q64toq32();
	test_q8toq64();
	test_q16toq64();
	test_q32toq64();
	test_q64toq64();
#if LIBCONFIG_USE_INT128
	test_q128toq8();
	test_q128toq16();
	test_q128toq32();
	test_q128toq64();
	test_q8toq128();
	test_q16toq128();
	test_q32toq128();
	test_q64toq128();
	test_q128toq128();
#endif

	test_f32toq8();
	test_f32toq16();
	test_f32toq32();
	test_f32toq64();
	test_f64toq8();
	test_f64toq16();
	test_f64toq32();
	test_f64toq64();
#if LIBCONFIG_USE_INT128
	test_f32toq128();
	test_f64toq128();
#endif

	return (OK);
}
