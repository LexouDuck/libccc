
#include "libccc/text/format.h"
#include "libccc/float.h"
#include "libccc/math/float.h"

#include "test.h"
#include "test_utils.h"



#if 0 // test template

#define DEFINETEST_FLOAT_(BITS) \
void	print_test_f##BITS##(char const* test_name, t_testflags flags, \
		t_f##BITS	expecting, \
		t_f##BITS	x, \
		t_f##BITS	y) \
{ \
	TEST_INIT(f##BITS) \
	TEST_PERFORM_LIBC(	f##BITS##, x, y) \
	TEST_PRINT(f##BITS,	f##BITS##, "x="SF_F##BITS", y="SF_F##BITS, x, y) \
} \
void	test_f##BITS##(void) \
{ \
/*	| TEST FUNCTION        | TEST NAME        |TESTFLAG| EXPECTING           | TEST ARGS */ \
/*	print_test_f##BITS##("u"#BITS"     ",	FALSE,               (0 + 0), 0, 0      );	*/ \
}

#ifndef c_f32
void test_f32(void)	{}
#warning "f32() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FLOAT_(32)
#endif

#ifndef c_f64
void test_f64(void)	{}
#warning "f64() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FLOAT_(64)
#endif

#ifndef c_f80
void test_f80(void)	{}
#warning "f80() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FLOAT_(80)
#endif

#if LIBCONFIG_USE_INT128
#ifndef c_f128
void test_f128(void)	{}
#warning "f128() test suite function defined, but the function isn't defined."
#else
DEFINETEST_FLOAT_(128)
#endif
#endif

#endif



#undef  TEST
#define TEST(BITS, LHS, OPERATOR, RHS) \
	EXCEPTION(BITS, LHS, OPERATOR, RHS) ((LHS) OPERATOR (RHS)), (LHS), (RHS)

#undef  EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	



#define DEFINETEST_FLOAT_OPERATOR(OP, FUNCNAME, BITS) \
void	print_test_f##BITS##FUNCNAME(char const* test_name, t_testflags flags, \
		t_f##BITS	expecting, \
		t_f##BITS	x, \
		t_f##BITS	y) \
{ \
	TEST_INIT(f##BITS) \
	TEST_PERFORM(		f##BITS##FUNCNAME, x, y) \
	TEST_PRINT(f##BITS,	f##BITS##FUNCNAME, "x=" SF_F##BITS ", y=" SF_F##BITS, x, y)\
} \
void	test_f##BITS##FUNCNAME(void) \
{ \
/*	| TEST FUNCTION             | TEST NAME                      |TESTFLAG| TEST */ \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS,  0.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.0,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +1.5,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.0,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, +2.5,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.0,OP,-0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.0,OP,-0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.5,OP,-0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -0.5,OP,-0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.0,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -1.5,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.0,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP, 0.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP, 0.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, -2.5,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.0,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,+1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,+1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,+2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,+2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,-1.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,-1.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,-2.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,-2.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,10.0) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME"              ",	FALSE, TEST(BITS, 10.5,OP,10.5) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=min;y= 0) ",	FALSE, TEST(BITS, F##BITS##_MIN, OP,  0.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=min;y=-1) ",	FALSE, TEST(BITS, F##BITS##_MIN, OP, -1.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=min;y=-2) ",	FALSE, TEST(BITS, F##BITS##_MIN, OP, -2.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=max;y= 0) ",	FALSE, TEST(BITS, F##BITS##_MAX, OP,  0.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=max;y=+1) ",	FALSE, TEST(BITS, F##BITS##_MAX, OP, +1.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=max;y=+2) ",	FALSE, TEST(BITS, F##BITS##_MAX, OP, +2.) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x= 0;y=min) ",	FALSE, TEST(BITS,  0., OP, F##BITS##_MIN) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=-1;y=min) ",	FALSE, TEST(BITS, -1., OP, F##BITS##_MIN) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=-2;y=min) ",	FALSE, TEST(BITS, -2., OP, F##BITS##_MIN) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x= 0;y=max) ",	FALSE, TEST(BITS,  0., OP, F##BITS##_MAX) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=+1;y=max) ",	FALSE, TEST(BITS, +1., OP, F##BITS##_MAX) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=+2;y=max) ",	FALSE, TEST(BITS, +2., OP, F##BITS##_MAX) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=min;y=min)",	FALSE, TEST(BITS, F##BITS##_MIN, OP, F##BITS##_MIN) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=min;y=max)",	FALSE, TEST(BITS, F##BITS##_MIN, OP, F##BITS##_MAX) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=max;y=min)",	FALSE, TEST(BITS, F##BITS##_MAX, OP, F##BITS##_MIN) ); \
	print_test_f##BITS##FUNCNAME("f"#BITS#FUNCNAME" (x=max;y=max)",	FALSE, TEST(BITS, F##BITS##_MAX, OP, F##BITS##_MAX) ); \
}

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(+, add, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(+, add, 32)

DEFINETEST_FLOAT_OPERATOR(+, add, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(+, add, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(+, add, 128)
#endif

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(-, sub, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(-, sub, 32)

DEFINETEST_FLOAT_OPERATOR(-, sub, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(-, sub, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(-, sub, 128)
#endif

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(*, mul, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(*, mul, 32)

DEFINETEST_FLOAT_OPERATOR(*, mul, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(*, mul, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(*, mul, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0.) ? ((LHS == 0.) ? F##BITS##_ERROR : (F##BITS##_MAX * F##BITS##_Sgn(LHS))) :

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(/, div, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(/, div, 32)

DEFINETEST_FLOAT_OPERATOR(/, div, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(/, div, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(/, div, 128)
#endif

/*

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0.) ? ((LHS == 0.) ? F##BITS##_ERROR : (F##BITS##_MAX * F##BITS##_Sgn(LHS))) :

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(%, mod, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(%, mod, 32)

DEFINETEST_FLOAT_OPERATOR(%, mod, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(%, mod, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(%, mod, 128)
#endif

#undef EXCEPTION
#define EXCEPTION(BITS, LHS, OP, RHS)	(RHS == 0.) ? ((LHS == 0.) ? F##BITS##_ERROR : (F##BITS##_MAX * F##BITS##_Sgn(LHS))) :

#if LIBCONFIG_USE_FLOAT16
DEFINETEST_FLOAT_OPERATOR(%, rem, 16)
#endif
DEFINETEST_FLOAT_OPERATOR(%, rem, 32)

DEFINETEST_FLOAT_OPERATOR(%, rem, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_FLOAT_OPERATOR(%, rem, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_FLOAT_OPERATOR(%, rem, 128)
#endif

*/



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_float(void)
{
	print_suite_title("libccc/math/float");

	print_nonstd();

#if LIBCONFIG_USE_FLOAT16

	#if !LIBCONFIG_USE_FLOAT80 && !LIBCONFIG_USE_FLOAT128
		#define RUNTESTSUITE(FUNCNAME) \
			test_f16##FUNCNAME(); \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \

	#elif LIBCONFIG_USE_FLOAT80
		#define RUNTESTSUITE(FUNCNAME) \
			test_f16##FUNCNAME(); \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \
			test_f80##FUNCNAME(); \

	#elif LIBCONFIG_USE_FLOAT128
		#define RUNTESTSUITE(FUNCNAME) \
			test_f16##FUNCNAME(); \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \
			test_f128##FUNCNAME(); \

	#endif

#else

	#if !LIBCONFIG_USE_FLOAT80 && !LIBCONFIG_USE_FLOAT128
		#define RUNTESTSUITE(FUNCNAME) \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \

	#elif LIBCONFIG_USE_FLOAT80
		#define RUNTESTSUITE(FUNCNAME) \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \
			test_f80##FUNCNAME(); \

	#elif LIBCONFIG_USE_FLOAT128
		#define RUNTESTSUITE(FUNCNAME) \
			test_f32##FUNCNAME(); \
			test_f64##FUNCNAME(); \
			test_f128##FUNCNAME(); \

	#endif

#endif

//	RUNTESTSUITE(isnan)
//	RUNTESTSUITE(isinf)
//	RUNTESTSUITE(abs)
//	RUNTESTSUITE(sgn)
//	RUNTESTSUITE(min)
//	RUNTESTSUITE(max)
	RUNTESTSUITE(add)
	RUNTESTSUITE(sub)
	RUNTESTSUITE(mul)
	RUNTESTSUITE(div)
//	RUNTESTSUITE(mod)
//	RUNTESTSUITE(rem)
//	RUNTESTSUITE(pow)
//	RUNTESTSUITE(root2)
//	RUNTESTSUITE(root3)
//	RUNTESTSUITE(rootn)
//	RUNTESTSUITE(hypot)
//	RUNTESTSUITE(exp)
//	RUNTESTSUITE(exp2)
//	RUNTESTSUITE(exp10)
//	RUNTESTSUITE(log)
//	RUNTESTSUITE(log2)
//	RUNTESTSUITE(log10)
//	RUNTESTSUITE(erf)
//	RUNTESTSUITE(erfc)
//	RUNTESTSUITE(gamma)
//	RUNTESTSUITE(lngamma)
//	RUNTESTSUITE(sin)
//	RUNTESTSUITE(cos)
//	RUNTESTSUITE(tan)
//	RUNTESTSUITE(asin)
//	RUNTESTSUITE(acos)
//	RUNTESTSUITE(atan)
//	RUNTESTSUITE(atan2)
//	RUNTESTSUITE(sinh)
//	RUNTESTSUITE(cosh)
//	RUNTESTSUITE(tanh)
//	RUNTESTSUITE(asinh)
//	RUNTESTSUITE(acosh)
//	RUNTESTSUITE(atanh)

	return (OK);
}
