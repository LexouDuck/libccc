
#include "libccc/math.h"
#include "libccc/math/complex.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

//! The comparison margin used to check approximate-equality of complex test results
#define COMPLEX_TEST_PRECISION	((t_float)1e-6)

//! Some example complex number values, used as arguments in several tests below
static s_complex const	z_zero     = { .re =  0., .im =  0. };
static s_complex const	z_identity = { .re = +1., .im =  0. };
static s_complex const	z_i        = { .re =  0., .im = +1. };
static s_complex const	z_1_2      = { .re = +1., .im = +2. };
static s_complex const	z_3_4      = { .re = +3., .im = +4. };

static
t_bool	complex_test_component_equals(t_float result, t_float expect)
{
	if (result == expect)
		return (TRUE);
	if (Float_IsNaN(result) && Float_IsNaN(expect))
		return (TRUE);
	if (Float_IsNaN(result) || Float_IsNaN(expect))
		return (FALSE);
	t_float	scale = Float_Abs(expect);
	if (scale < 1.)
		scale = 1.;
	return (Float_Abs(result - expect) <= COMPLEX_TEST_PRECISION * scale);
}

//! Checks that `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_complex(char const* test_name,
	s_complex result,
	s_complex expect)
{
	t_bool	success = (
		complex_test_component_equals(result.re, expect.re) &&
		complex_test_component_equals(result.im, expect.im));
	g_test.suites[TESTSUITE_MATH_COMPLEX].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_COMPLEX].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: (re=%g, im=%g)\n", result.re, result.im);
		printf("\t- expect: (re=%g, im=%g)\n", expect.re, expect.im);
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}

//! Checks that a scalar `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_complex_float(char const* test_name,
	t_float result,
	t_float expect)
{
	t_bool	success = complex_test_component_equals(result, expect);
	g_test.suites[TESTSUITE_MATH_COMPLEX].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_COMPLEX].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: %g\n", result);
		printf("\t- expect: %g\n", expect);
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}

//! Checks that a boolean `result` matches `expect`, and tallies/prints the test result
static
void	print_test_complex_bool(char const* test_name,
	t_bool result,
	t_bool expect)
{
	t_bool	success = ((!result) == (!expect));
	g_test.suites[TESTSUITE_MATH_COMPLEX].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_COMPLEX].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: %s\n", (result ? "TRUE" : "FALSE"));
		printf("\t- expect: %s\n", (expect ? "TRUE" : "FALSE"));
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}



/*============================================================================*\
||                           Per-function Test Cases                          ||
\*============================================================================*/

static
void	test_complex(void)
{
	s_complex	z = Complex(1., -2.);
	print_test_complex("Complex() constructor",
		z, (s_complex){ .re = 1., .im = -2. });
	print_test_complex("COMPLEX_NULL",
		COMPLEX_NULL, z_zero);
}

static
void	test_complex_new(void)
{
	s_complex*	z = Complex_New(1., -2.);
	print_test_complex_bool("Complex_New (non-null return)", (z != NULL), TRUE);
	if (z)
	{
		print_test_complex("Complex_New (component values)",
			*z, (s_complex){ .re = 1., .im = -2. });
		free(z);
	}
}

static
void	test_complex_equals(void)
{
	print_test_complex_bool("Complex_Equals (equal)",          Complex_Equals(&z_1_2, &z_1_2), TRUE);
	print_test_complex_bool("Complex_Equals (different)",      Complex_Equals(&z_1_2, &z_3_4), FALSE);
	print_test_complex_bool("Complex_Equals (differs by .re)", Complex_Equals(&z_1_2, &(s_complex){ .re = 9., .im = 2. }), FALSE);
	print_test_complex_bool("Complex_Equals (differs by .im)", Complex_Equals(&z_1_2, &(s_complex){ .re = 1., .im = 9. }), FALSE);
	print_test_complex_bool("Complex_Equals (both zero)",      Complex_Equals(&z_zero, &(s_complex){ .re = 0., .im = 0. }), TRUE);
}

static
void	test_complex_add(void)
{
	print_test_complex("Complex_Add",
		Complex_Add(&z_1_2, &z_3_4),
		(s_complex){ .re = 4., .im = 6. });
	print_test_complex("Complex_Add (with zero)",
		Complex_Add(&z_1_2, &z_zero), z_1_2);
}

static
void	test_complex_sub(void)
{
	print_test_complex("Complex_Sub",
		Complex_Sub(&z_3_4, &z_1_2),
		(s_complex){ .re = 2., .im = 2. });
	print_test_complex("Complex_Sub (self)",
		Complex_Sub(&z_1_2, &z_1_2), z_zero);
}

static
void	test_complex_mul(void)
{
	// the fundamental property of the imaginary unit: i*i == -1
	print_test_complex("Complex_Mul (i*i = -1)",
		Complex_Mul(&z_i, &z_i), (s_complex){ .re = -1., .im = 0. });
	// general case: (1+2i)*(3+4i) == -5+10i
	print_test_complex("Complex_Mul (general case)",
		Complex_Mul(&z_1_2, &z_3_4),
		(s_complex){ .re = -5., .im = 10. });
	print_test_complex("Complex_Mul (by identity)",
		Complex_Mul(&z_1_2, &z_identity), z_1_2);
	// complex multiplication is commutative: z1*z2 == z2*z1
	print_test_complex("Complex_Mul (commutative)",
		Complex_Mul(&z_1_2, &z_3_4),
		Complex_Mul(&z_3_4, &z_1_2));
	// norm is multiplicative: |z1*z2| == |z1|*|z2|
	s_complex	product = Complex_Mul(&z_1_2, &z_3_4);
	print_test_complex_float("Complex_Mul (norm is multiplicative)",
		Complex_Norm(&product),
		Complex_Norm(&z_1_2) * Complex_Norm(&z_3_4));
}

static
void	test_complex_norm(void)
{
	print_test_complex_float("Complex_Norm (3+4i == 5)", Complex_Norm(&z_3_4), 5.);
	print_test_complex_float("Complex_Norm (unit i)",    Complex_Norm(&z_i), 1.);
	print_test_complex_float("Complex_Norm (zero)",      Complex_Norm(&z_zero), 0.);
	print_test_complex_float("Complex_Norm (1+2i)",      Complex_Norm(&z_1_2), Float_Root2(5.));
}

static
void	test_complex_conjugate(void)
{
	print_test_complex("Complex_Conjugate",
		Complex_Conjugate(&z_1_2),
		(s_complex){ .re = 1., .im = -2. });
	// z * conj(z) == |z|^2
	s_complex	conj = Complex_Conjugate(&z_3_4);
	print_test_complex("Complex_Conjugate (z * conj(z) == norm squared)",
		Complex_Mul(&z_3_4, &conj),
		(s_complex){ .re = 25., .im = 0. });
}

static
void	test_complex_inverse(void)
{
	s_complex	inverse = Complex_Inverse(&z_1_2);
	print_test_complex("Complex_Inverse (z * z^-1 == 1)",
		Complex_Mul(&z_1_2, &inverse), z_identity);
	print_test_complex("Complex_Inverse (of identity)",
		Complex_Inverse(&z_identity), z_identity);
	print_test_complex("Complex_Inverse (of i == -i)",
		Complex_Inverse(&z_i), (s_complex){ .re = 0., .im = -1. });
	print_test_complex("Complex_Inverse (of zero -> error)",
		Complex_Inverse(&z_zero), COMPLEX_ERROR);
}

static
void	test_complex_normalize(void)
{
	s_complex	normalized = Complex_Normalize(&z_3_4);
	print_test_complex_float("Complex_Normalize (norm == 1)",
		Complex_Norm(&normalized), 1.);
	print_test_complex("Complex_Normalize (direction preserved)",
		normalized,
		(s_complex){ .re = 3. / 5., .im = 4. / 5. });
	print_test_complex("Complex_Normalize (of zero -> error)",
		Complex_Normalize(&z_zero), COMPLEX_ERROR);
}

static
void	test_complex_div(void)
{
	// (z1 * z2) / z2 == z1
	s_complex	product = Complex_Mul(&z_1_2, &z_3_4);
	print_test_complex("Complex_Div ((z1*z2) / z2 == z1)",
		Complex_Div(&product, &z_3_4), z_1_2);
	// known value: (-5+10i) / (3+4i) == 1+2i
	print_test_complex("Complex_Div (general case)",
		Complex_Div(&(s_complex){ .re = -5., .im = 10. }, &z_3_4), z_1_2);
	print_test_complex("Complex_Div (z / z == 1)",
		Complex_Div(&z_1_2, &z_1_2), z_identity);
	print_test_complex("Complex_Div (z / 1 == z)",
		Complex_Div(&z_1_2, &z_identity), z_1_2);
	// division is equivalent to multiplying with the inverse
	s_complex	inverse = Complex_Inverse(&z_3_4);
	print_test_complex("Complex_Div (z1 / z2 == z1 * z2^-1)",
		Complex_Div(&z_1_2, &z_3_4),
		Complex_Mul(&z_1_2, &inverse));
	// dividing by i is equivalent to multiplying by -i: z / i == -i * z
	print_test_complex("Complex_Div (z / i == -i*z)",
		Complex_Div(&z_1_2, &z_i),
		(s_complex){ .re = 2., .im = -1. });
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_complex(void)
{
	print_suite_title("libccc/math/complex");

	test_complex();
	test_complex_new();
	test_complex_equals();
	test_complex_add();
	test_complex_sub();
	test_complex_mul();
	test_complex_norm();
	test_complex_conjugate();
	test_complex_inverse();
	test_complex_normalize();
	test_complex_div();

	return (OK);
}
