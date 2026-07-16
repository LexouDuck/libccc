
#include "libccc/math.h"
#include "libccc/math/quaternion.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

//! The comparison margin used to check approximate-equality of quaternion test results
#define QUATERNION_TEST_PRECISION	((t_float)1e-6)

//! Some example quaternion values, used as arguments in several tests below
static s_quaternion const	q_zero     = { .s =  0., .i =  0., .j =  0., .k =  0. };
static s_quaternion const	q_identity = { .s = +1., .i =  0., .j =  0., .k =  0. };
static s_quaternion const	q_i        = { .s =  0., .i = +1., .j =  0., .k =  0. };
static s_quaternion const	q_j        = { .s =  0., .i =  0., .j = +1., .k =  0. };
static s_quaternion const	q_k        = { .s =  0., .i =  0., .j =  0., .k = +1. };
static s_quaternion const	q_1234     = { .s = +1., .i = +2., .j = +3., .k = +4. };
static s_quaternion const	q_5678     = { .s = +5., .i = +6., .j = +7., .k = +8. };
static s_quaternion const	q_mixed    = { .s = +0.5, .i = -0.25, .j = +0.75, .k = -0.5 };
static s_quaternion const	q_small    = { .s = +0.2, .i = +0.3, .j = -0.1, .k = +0.25 };

static
t_bool	quaternion_test_component_equals(t_float result, t_float expect)
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
	return (Float_Abs(result - expect) <= QUATERNION_TEST_PRECISION * scale);
}

//! Checks that `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_quaternion(char const* test_name,
	s_quaternion result,
	s_quaternion expect)
{
	t_bool	success = (
		quaternion_test_component_equals(result.s, expect.s) &&
		quaternion_test_component_equals(result.i, expect.i) &&
		quaternion_test_component_equals(result.j, expect.j) &&
		quaternion_test_component_equals(result.k, expect.k));
	g_test.suites[TESTSUITE_MATH_QUATERNION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_QUATERNION].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: (s=%g, i=%g, j=%g, k=%g)\n", result.s, result.i, result.j, result.k);
		printf("\t- expect: (s=%g, i=%g, j=%g, k=%g)\n", expect.s, expect.i, expect.j, expect.k);
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}

//! Checks that a scalar `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_quaternion_float(char const* test_name,
	t_float result,
	t_float expect)
{
	t_bool	success = quaternion_test_component_equals(result, expect);
	g_test.suites[TESTSUITE_MATH_QUATERNION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_QUATERNION].totals.failed += 1;
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
void	print_test_quaternion_bool(char const* test_name,
	t_bool result,
	t_bool expect)
{
	t_bool	success = ((!result) == (!expect));
	g_test.suites[TESTSUITE_MATH_QUATERNION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_QUATERNION].totals.failed += 1;
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
void	test_quaternion(void)
{
	s_quaternion	q = Quaternion(1., -2., 3., -4.);
	print_test_quaternion("Quaternion() constructor",
		q, (s_quaternion){ .s = 1., .i = -2., .j = 3., .k = -4. });
	print_test_quaternion("QUATERNION_NULL",
		QUATERNION_NULL, q_zero);
}

static
void	test_quaternion_new(void)
{
	s_quaternion*	q = Quaternion_New(1., -2., 3., -4.);
	print_test_quaternion_bool("Quaternion_New (non-null return)", (q != NULL), TRUE);
	if (q)
	{
		print_test_quaternion("Quaternion_New (component values)",
			*q, (s_quaternion){ .s = 1., .i = -2., .j = 3., .k = -4. });
		free(q);
	}
}

static
void	test_quaternion_equals(void)
{
	print_test_quaternion_bool("Quaternion_Equals (equal)",         Quaternion_Equals(&q_1234, &q_1234), TRUE);
	print_test_quaternion_bool("Quaternion_Equals (different)",     Quaternion_Equals(&q_1234, &q_5678), FALSE);
	print_test_quaternion_bool("Quaternion_Equals (differs by .s)", Quaternion_Equals(&q_1234, &(s_quaternion){ .s = 9., .i = 2., .j = 3., .k = 4. }), FALSE);
	print_test_quaternion_bool("Quaternion_Equals (differs by .i)", Quaternion_Equals(&q_1234, &(s_quaternion){ .s = 1., .i = 9., .j = 3., .k = 4. }), FALSE);
	print_test_quaternion_bool("Quaternion_Equals (differs by .j)", Quaternion_Equals(&q_1234, &(s_quaternion){ .s = 1., .i = 2., .j = 9., .k = 4. }), FALSE);
	print_test_quaternion_bool("Quaternion_Equals (differs by .k)", Quaternion_Equals(&q_1234, &(s_quaternion){ .s = 1., .i = 2., .j = 3., .k = 9. }), FALSE);
	print_test_quaternion_bool("Quaternion_Equals (both zero)",     Quaternion_Equals(&q_zero, &QUATERNION_NULL), TRUE);
}

static
void	test_quaternion_add(void)
{
	print_test_quaternion("Quaternion_Add",
		Quaternion_Add(&q_1234, &q_5678),
		(s_quaternion){ .s = 6., .i = 8., .j = 10., .k = 12. });
	print_test_quaternion("Quaternion_Add (with zero)",
		Quaternion_Add(&q_1234, &q_zero), q_1234);
}

static
void	test_quaternion_sub(void)
{
	print_test_quaternion("Quaternion_Sub",
		Quaternion_Sub(&q_5678, &q_1234),
		(s_quaternion){ .s = 4., .i = 4., .j = 4., .k = 4. });
	print_test_quaternion("Quaternion_Sub (self)",
		Quaternion_Sub(&q_1234, &q_1234), q_zero);
}

static
void	test_quaternion_mul(void)
{
	// Hamilton's fundamental products
	print_test_quaternion("Quaternion_Mul (i*i = -1)", Quaternion_Mul(&q_i, &q_i), (s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Mul (j*j = -1)", Quaternion_Mul(&q_j, &q_j), (s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Mul (k*k = -1)", Quaternion_Mul(&q_k, &q_k), (s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Mul (i*j = +k)", Quaternion_Mul(&q_i, &q_j), q_k);
	print_test_quaternion("Quaternion_Mul (j*k = +i)", Quaternion_Mul(&q_j, &q_k), q_i);
	print_test_quaternion("Quaternion_Mul (k*i = +j)", Quaternion_Mul(&q_k, &q_i), q_j);
	print_test_quaternion("Quaternion_Mul (j*i = -k)", Quaternion_Mul(&q_j, &q_i), (s_quaternion){ .s = 0., .i = 0., .j = 0., .k = -1. });
	print_test_quaternion("Quaternion_Mul (k*j = -i)", Quaternion_Mul(&q_k, &q_j), (s_quaternion){ .s = 0., .i = -1., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Mul (i*k = -j)", Quaternion_Mul(&q_i, &q_k), (s_quaternion){ .s = 0., .i = 0., .j = -1., .k = 0. });
	// general case
	print_test_quaternion("Quaternion_Mul (general case)",
		Quaternion_Mul(&q_1234, &q_5678),
		(s_quaternion){ .s = -60., .i = 12., .j = 30., .k = 24. });
	print_test_quaternion("Quaternion_Mul (by identity)",
		Quaternion_Mul(&q_1234, &q_identity), q_1234);
	// norm is multiplicative: |q1*q2| == |q1|*|q2|
	s_quaternion	product = Quaternion_Mul(&q_1234, &q_5678);
	print_test_quaternion_float("Quaternion_Mul (norm is multiplicative)",
		Quaternion_Norm(&product),
		Quaternion_Norm(&q_1234) * Quaternion_Norm(&q_5678));
}

static
void	test_quaternion_norm(void)
{
	print_test_quaternion_float("Quaternion_Norm (1,2,3,4)",  Quaternion_Norm(&q_1234), Float_Root2(30.));
	print_test_quaternion_float("Quaternion_Norm (unit i)",   Quaternion_Norm(&q_i), 1.);
	print_test_quaternion_float("Quaternion_Norm (zero)",     Quaternion_Norm(&q_zero), 0.);
	print_test_quaternion_float("Quaternion_Norm (3-4-5)",    Quaternion_Norm(&(s_quaternion){ .s = 0., .i = 3., .j = 4., .k = 0. }), 5.);
}

static
void	test_quaternion_conjugate(void)
{
	print_test_quaternion("Quaternion_Conjugate",
		Quaternion_Conjugate(&q_1234),
		(s_quaternion){ .s = 1., .i = -2., .j = -3., .k = -4. });
	// q * conj(q) == |q|^2
	s_quaternion	conj = Quaternion_Conjugate(&q_1234);
	print_test_quaternion("Quaternion_Conjugate (q * conj(q) == norm squared)",
		Quaternion_Mul(&q_1234, &conj),
		(s_quaternion){ .s = 30., .i = 0., .j = 0., .k = 0. });
}

static
void	test_quaternion_inverse(void)
{
	s_quaternion	inverse = Quaternion_Inverse(&q_1234);
	print_test_quaternion("Quaternion_Inverse (q * q^-1 == 1)",
		Quaternion_Mul(&q_1234, &inverse), q_identity);
	print_test_quaternion("Quaternion_Inverse (q^-1 * q == 1)",
		Quaternion_Mul(&inverse, &q_1234), q_identity);
	print_test_quaternion("Quaternion_Inverse (of identity)",
		Quaternion_Inverse(&q_identity), q_identity);
	print_test_quaternion("Quaternion_Inverse (of zero -> error)",
		Quaternion_Inverse(&q_zero), QUATERNION_ERROR);
}

static
void	test_quaternion_normalize(void)
{
	s_quaternion	normalized = Quaternion_Normalize(&q_1234);
	print_test_quaternion_float("Quaternion_Normalize (norm == 1)",
		Quaternion_Norm(&normalized), 1.);
	print_test_quaternion("Quaternion_Normalize (direction preserved)",
		normalized,
		(s_quaternion){
			.s = 1. / Float_Root2(30.),
			.i = 2. / Float_Root2(30.),
			.j = 3. / Float_Root2(30.),
			.k = 4. / Float_Root2(30.) });
	print_test_quaternion("Quaternion_Normalize (of zero -> error)",
		Quaternion_Normalize(&q_zero), QUATERNION_ERROR);
}

static
void	test_quaternion_div(void)
{
	// right division: (q1 * q2) / q2 == q1
	s_quaternion	product = Quaternion_Mul(&q_1234, &q_5678);
	print_test_quaternion("Quaternion_Div ((q1*q2) / q2 == q1)",
		Quaternion_Div(&product, &q_5678), q_1234);
	print_test_quaternion("Quaternion_Div (q / q == 1)",
		Quaternion_Div(&q_1234, &q_1234), q_identity);
	print_test_quaternion("Quaternion_Div (q / 1 == q)",
		Quaternion_Div(&q_1234, &q_identity), q_1234);
	// division is equivalent to multiplying with the inverse (on the right)
	s_quaternion	inverse = Quaternion_Inverse(&q_5678);
	print_test_quaternion("Quaternion_Div (q1 / q2 == q1 * q2^-1)",
		Quaternion_Div(&q_1234, &q_5678),
		Quaternion_Mul(&q_1234, &inverse));
}

static
void	test_quaternion_pow(void)
{
	s_quaternion	squared = Quaternion_Mul(&q_1234, &q_1234);
	print_test_quaternion("Quaternion_Pow (q^2 == q*q)",
		Quaternion_Pow(&q_1234, 2.), squared);
	print_test_quaternion("Quaternion_Pow (q^1 == q)",
		Quaternion_Pow(&q_1234, 1.), q_1234);
	print_test_quaternion("Quaternion_Pow (q^0 == 1)",
		Quaternion_Pow(&q_1234, 0.), q_identity);
	print_test_quaternion("Quaternion_Pow (q^-1 == inverse)",
		Quaternion_Pow(&q_1234, -1.), Quaternion_Inverse(&q_1234));
	print_test_quaternion("Quaternion_Pow (real base: 4^0.5 == 2)",
		Quaternion_Pow(&(s_quaternion){ .s = 4., .i = 0., .j = 0., .k = 0. }, 0.5),
		(s_quaternion){ .s = 2., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Pow ((-1)^0.5 == i, axis convention)",
		Quaternion_Pow(&(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. }, 0.5), q_i);
	print_test_quaternion("Quaternion_Pow (0^2 == 0)",
		Quaternion_Pow(&q_zero, 2.), q_zero);
	print_test_quaternion("Quaternion_Pow (0^0 == 1)",
		Quaternion_Pow(&q_zero, 0.), q_identity);
	print_test_quaternion("Quaternion_Pow (0^-1 -> error)",
		Quaternion_Pow(&q_zero, -1.), QUATERNION_ERROR);
}

static
void	test_quaternion_root(void)
{
	s_quaternion	root = Quaternion_Root2(&q_1234);
	print_test_quaternion("Quaternion_Root2 (sqrt(q)^2 == q)",
		Quaternion_Mul(&root, &root), q_1234);
	print_test_quaternion("Quaternion_Root2 (sqrt(4) == 2)",
		Quaternion_Root2(&(s_quaternion){ .s = 4., .i = 0., .j = 0., .k = 0. }),
		(s_quaternion){ .s = 2., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Root2 (sqrt(-1) == i, axis convention)",
		Quaternion_Root2(&(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. }), q_i);

	root = Quaternion_Root3(&q_1234);
	s_quaternion	cube = Quaternion_Mul(&root, &root);
	print_test_quaternion("Quaternion_Root3 (cbrt(q)^3 == q)",
		Quaternion_Mul(&cube, &root), q_1234);

	root = Quaternion_RootN(&q_1234, 4);
	s_quaternion	tmp = Quaternion_Mul(&root, &root);
	print_test_quaternion("Quaternion_RootN (nrt(q,4)^4 == q)",
		Quaternion_Mul(&tmp, &tmp), q_1234);
	print_test_quaternion("Quaternion_RootN (nrt(q,1) == q)",
		Quaternion_RootN(&q_1234, 1), q_1234);
	print_test_quaternion("Quaternion_RootN (nrt(q,0) -> error)",
		Quaternion_RootN(&q_1234, 0), QUATERNION_ERROR);
}

static
void	test_quaternion_arg(void)
{
	print_test_quaternion_float("Quaternion_Arg (of 1 == 0)",       Quaternion_Arg(&q_identity), 0.);
	print_test_quaternion_float("Quaternion_Arg (of i == PI/2)",    Quaternion_Arg(&q_i), (t_float)PI / 2.);
	print_test_quaternion_float("Quaternion_Arg (of -1 == PI)",     Quaternion_Arg(&(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. }), (t_float)PI);
	print_test_quaternion_float("Quaternion_Arg (of 1+i == PI/4)",  Quaternion_Arg(&(s_quaternion){ .s = 1., .i = 1., .j = 0., .k = 0. }), (t_float)PI / 4.);
	print_test_quaternion_float("Quaternion_Arg (of 1+j == PI/4)",  Quaternion_Arg(&(s_quaternion){ .s = 1., .i = 0., .j = 1., .k = 0. }), (t_float)PI / 4.);
	print_test_quaternion_float("Quaternion_Arg (of zero -> error)", Quaternion_Arg(&q_zero), NAN);
}

static
void	test_quaternion_exp(void)
{
	print_test_quaternion("Quaternion_Exp (exp(0) == 1)",
		Quaternion_Exp(&q_zero), q_identity);
	print_test_quaternion("Quaternion_Exp (exp(1) == e)",
		Quaternion_Exp(&q_identity),
		(s_quaternion){ .s = Float_Exp(1.), .i = 0., .j = 0., .k = 0. });
	// Euler's identity: exp(i*PI) == -1 (and likewise for any unit vector axis)
	print_test_quaternion("Quaternion_Exp (exp(PI*i) == -1)",
		Quaternion_Exp(&(s_quaternion){ .s = 0., .i = (t_float)PI, .j = 0., .k = 0. }),
		(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Exp (exp(PI*j) == -1)",
		Quaternion_Exp(&(s_quaternion){ .s = 0., .i = 0., .j = (t_float)PI, .k = 0. }),
		(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. });
	// exp preserves the norm relation: |exp(q)| == exp(q.s)
	s_quaternion	result = Quaternion_Exp(&q_mixed);
	print_test_quaternion_float("Quaternion_Exp (|exp(q)| == exp(q.s))",
		Quaternion_Norm(&result), Float_Exp(q_mixed.s));
}

static
void	test_quaternion_log(void)
{
	print_test_quaternion("Quaternion_Log (log(1) == 0)",
		Quaternion_Log(&q_identity), q_zero);
	print_test_quaternion("Quaternion_Log (log(e) == 1)",
		Quaternion_Log(&(s_quaternion){ .s = Float_Exp(1.), .i = 0., .j = 0., .k = 0. }), q_identity);
	print_test_quaternion("Quaternion_Log (log(i) == PI/2*i)",
		Quaternion_Log(&q_i),
		(s_quaternion){ .s = 0., .i = (t_float)PI / 2., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Log (log(-1) == PI*i, axis convention)",
		Quaternion_Log(&(s_quaternion){ .s = -1., .i = 0., .j = 0., .k = 0. }),
		(s_quaternion){ .s = 0., .i = (t_float)PI, .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Log (of zero -> error)",
		Quaternion_Log(&q_zero), QUATERNION_ERROR);
	// round-trip identities
	s_quaternion	log = Quaternion_Log(&q_1234);
	print_test_quaternion("Quaternion_Log (exp(log(q)) == q)",
		Quaternion_Exp(&log), q_1234);
	s_quaternion	exp = Quaternion_Exp(&q_mixed);
	print_test_quaternion("Quaternion_Log (log(exp(q)) == q)",
		Quaternion_Log(&exp), q_mixed);
}

static
void	test_quaternion_trig(void)
{
	// consistency with real-number trigonometry
	s_quaternion	q_real = { .s = 0.7, .i = 0., .j = 0., .k = 0. };
	print_test_quaternion("Quaternion_Cos (of real quaternion)",
		Quaternion_Cos(&q_real), (s_quaternion){ .s = Float_Cos(0.7), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Sin (of real quaternion)",
		Quaternion_Sin(&q_real), (s_quaternion){ .s = Float_Sin(0.7), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_Tan (of real quaternion)",
		Quaternion_Tan(&q_real), (s_quaternion){ .s = Float_Tan(0.7), .i = 0., .j = 0., .k = 0. });
	// pythagorean identity: sin(q)^2 + cos(q)^2 == 1
	s_quaternion	sin = Quaternion_Sin(&q_mixed);
	s_quaternion	cos = Quaternion_Cos(&q_mixed);
	s_quaternion	sin2 = Quaternion_Mul(&sin, &sin);
	s_quaternion	cos2 = Quaternion_Mul(&cos, &cos);
	print_test_quaternion("Quaternion trig (sin^2 + cos^2 == 1)",
		Quaternion_Add(&sin2, &cos2), q_identity);
	// tan(q) == sin(q) / cos(q)
	print_test_quaternion("Quaternion_Tan (tan == sin/cos)",
		Quaternion_Tan(&q_mixed), Quaternion_Div(&sin, &cos));
	// inverse functions: round-trip identities
	s_quaternion	tmp;
	tmp = Quaternion_ArcCos(&q_mixed);
	print_test_quaternion("Quaternion_ArcCos (cos(acos(q)) == q)",
		Quaternion_Cos(&tmp), q_mixed);
	tmp = Quaternion_ArcCos(&q_1234);
	print_test_quaternion("Quaternion_ArcCos (cos(acos(q)) == q, |q| > 1)",
		Quaternion_Cos(&tmp), q_1234);
	tmp = Quaternion_ArcSin(&q_mixed);
	print_test_quaternion("Quaternion_ArcSin (sin(asin(q)) == q)",
		Quaternion_Sin(&tmp), q_mixed);
	tmp = Quaternion_ArcSin(&q_1234);
	print_test_quaternion("Quaternion_ArcSin (sin(asin(q)) == q, |q| > 1)",
		Quaternion_Sin(&tmp), q_1234);
	tmp = Quaternion_ArcTan(&q_mixed);
	print_test_quaternion("Quaternion_ArcTan (tan(atan(q)) == q)",
		Quaternion_Tan(&tmp), q_mixed);
	// inverse functions: consistency with real-number trigonometry
	q_real = (s_quaternion){ .s = 0.5, .i = 0., .j = 0., .k = 0. };
	print_test_quaternion("Quaternion_ArcCos (of real quaternion)",
		Quaternion_ArcCos(&q_real), (s_quaternion){ .s = Float_ArcCos(0.5), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_ArcSin (of real quaternion)",
		Quaternion_ArcSin(&q_real), (s_quaternion){ .s = Float_ArcSin(0.5), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_ArcTan (of real quaternion)",
		Quaternion_ArcTan(&q_real), (s_quaternion){ .s = Float_ArcTan(0.5), .i = 0., .j = 0., .k = 0. });
}

static
void	test_quaternion_trig_hyperbolic(void)
{
	// consistency with real-number functions
	s_quaternion	q_real = { .s = 0.7, .i = 0., .j = 0., .k = 0. };
	print_test_quaternion("Quaternion_CosH (of real quaternion)",
		Quaternion_CosH(&q_real), (s_quaternion){ .s = Float_CosH(0.7), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_SinH (of real quaternion)",
		Quaternion_SinH(&q_real), (s_quaternion){ .s = Float_SinH(0.7), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_TanH (of real quaternion)",
		Quaternion_TanH(&q_real), (s_quaternion){ .s = Float_TanH(0.7), .i = 0., .j = 0., .k = 0. });
	// hyperbolic identity: cosh(q)^2 - sinh(q)^2 == 1
	s_quaternion	sinh = Quaternion_SinH(&q_mixed);
	s_quaternion	cosh = Quaternion_CosH(&q_mixed);
	s_quaternion	sinh2 = Quaternion_Mul(&sinh, &sinh);
	s_quaternion	cosh2 = Quaternion_Mul(&cosh, &cosh);
	print_test_quaternion("Quaternion trig (cosh^2 - sinh^2 == 1)",
		Quaternion_Sub(&cosh2, &sinh2), q_identity);
	// tanh(q) == sinh(q) / cosh(q)
	print_test_quaternion("Quaternion_TanH (tanh == sinh/cosh)",
		Quaternion_TanH(&q_mixed), Quaternion_Div(&sinh, &cosh));
	// consistency with the exponential function: sinh(q) == (exp(q) - exp(-q)) / 2
	s_quaternion	q_neg = { .s = -q_mixed.s, .i = -q_mixed.i, .j = -q_mixed.j, .k = -q_mixed.k };
	s_quaternion	exp_pos = Quaternion_Exp(&q_mixed);
	s_quaternion	exp_neg = Quaternion_Exp(&q_neg);
	s_quaternion	diff = Quaternion_Sub(&exp_pos, &exp_neg);
	print_test_quaternion("Quaternion_SinH (sinh == (exp(q) - exp(-q)) / 2)",
		Quaternion_SinH(&q_mixed),
		(s_quaternion){ .s = diff.s / 2., .i = diff.i / 2., .j = diff.j / 2., .k = diff.k / 2. });
	// inverse functions: round-trip identities
	s_quaternion	tmp;
	tmp = Quaternion_InvCosH(&q_mixed);
	print_test_quaternion("Quaternion_InvCosH (cosh(acosh(q)) == q)",
		Quaternion_CosH(&tmp), q_mixed);
	tmp = Quaternion_InvCosH(&q_1234);
	print_test_quaternion("Quaternion_InvCosH (cosh(acosh(q)) == q, |q| > 1)",
		Quaternion_CosH(&tmp), q_1234);
	tmp = Quaternion_InvSinH(&q_mixed);
	print_test_quaternion("Quaternion_InvSinH (sinh(asinh(q)) == q)",
		Quaternion_SinH(&tmp), q_mixed);
	tmp = Quaternion_InvSinH(&q_1234);
	print_test_quaternion("Quaternion_InvSinH (sinh(asinh(q)) == q, |q| > 1)",
		Quaternion_SinH(&tmp), q_1234);
	tmp = Quaternion_InvTanH(&q_small);
	print_test_quaternion("Quaternion_InvTanH (tanh(atanh(q)) == q)",
		Quaternion_TanH(&tmp), q_small);
	// inverse functions: consistency with real-number functions
	q_real = (s_quaternion){ .s = 0.5, .i = 0., .j = 0., .k = 0. };
	print_test_quaternion("Quaternion_InvSinH (of real quaternion)",
		Quaternion_InvSinH(&q_real), (s_quaternion){ .s = Float_InvSinH(0.5), .i = 0., .j = 0., .k = 0. });
	print_test_quaternion("Quaternion_InvTanH (of real quaternion)",
		Quaternion_InvTanH(&q_real), (s_quaternion){ .s = Float_InvTanH(0.5), .i = 0., .j = 0., .k = 0. });
	q_real = (s_quaternion){ .s = 2., .i = 0., .j = 0., .k = 0. };
	print_test_quaternion("Quaternion_InvCosH (of real quaternion)",
		Quaternion_InvCosH(&q_real), (s_quaternion){ .s = Float_InvCosH(2.), .i = 0., .j = 0., .k = 0. });
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_quaternion(void)
{
	print_suite_title("libccc/math/quaternion");

	test_quaternion();
	test_quaternion_new();
	test_quaternion_equals();
	test_quaternion_add();
	test_quaternion_sub();
	test_quaternion_mul();
	test_quaternion_norm();
	test_quaternion_conjugate();
	test_quaternion_inverse();
	test_quaternion_normalize();
	test_quaternion_div();
	test_quaternion_pow();
	test_quaternion_root();
	test_quaternion_arg();
	test_quaternion_exp();
	test_quaternion_log();
	test_quaternion_trig();
	test_quaternion_trig_hyperbolic();

	return (OK);
}
