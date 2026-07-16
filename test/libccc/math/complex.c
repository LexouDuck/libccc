
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



static
void	test_complex_pow(void)
{
	s_complex	squared = Complex_Mul(&z_1_2, &z_1_2);
	print_test_complex("Complex_Pow (z^2 == z*z)",
		Complex_Pow(&z_1_2, 2.), squared);
	print_test_complex("Complex_Pow (z^1 == z)",
		Complex_Pow(&z_1_2, 1.), z_1_2);
	print_test_complex("Complex_Pow (z^0 == 1)",
		Complex_Pow(&z_1_2, 0.), z_identity);
	print_test_complex("Complex_Pow (z^-1 == inverse)",
		Complex_Pow(&z_1_2, -1.), Complex_Inverse(&z_1_2));
	print_test_complex("Complex_Pow (real base: 4^0.5 == 2)",
		Complex_Pow(&(s_complex){ .re = 4., .im = 0. }, 0.5),
		(s_complex){ .re = 2., .im = 0. });
	print_test_complex("Complex_Pow ((-1)^0.5 == i)",
		Complex_Pow(&(s_complex){ .re = -1., .im = 0. }, 0.5), z_i);
	print_test_complex("Complex_Pow (0^2 == 0)",
		Complex_Pow(&z_zero, 2.), z_zero);
	print_test_complex("Complex_Pow (0^0 == 1)",
		Complex_Pow(&z_zero, 0.), z_identity);
	print_test_complex("Complex_Pow (0^-1 -> error)",
		Complex_Pow(&z_zero, -1.), COMPLEX_ERROR);
}

static
void	test_complex_root(void)
{
	s_complex	root = Complex_Root2(&z_1_2);
	print_test_complex("Complex_Root2 (sqrt(z)^2 == z)",
		Complex_Mul(&root, &root), z_1_2);
	print_test_complex("Complex_Root2 (sqrt(4) == 2)",
		Complex_Root2(&(s_complex){ .re = 4., .im = 0. }),
		(s_complex){ .re = 2., .im = 0. });
	print_test_complex("Complex_Root2 (sqrt(-1) == i)",
		Complex_Root2(&(s_complex){ .re = -1., .im = 0. }), z_i);
	print_test_complex("Complex_Root2 (sqrt(2i) == 1+i)",
		Complex_Root2(&(s_complex){ .re = 0., .im = 2. }),
		(s_complex){ .re = 1., .im = 1. });

	root = Complex_Root3(&z_1_2);
	s_complex	cube = Complex_Mul(&root, &root);
	print_test_complex("Complex_Root3 (cbrt(z)^3 == z)",
		Complex_Mul(&cube, &root), z_1_2);

	root = Complex_RootN(&z_1_2, 4);
	s_complex	tmp = Complex_Mul(&root, &root);
	print_test_complex("Complex_RootN (nrt(z,4)^4 == z)",
		Complex_Mul(&tmp, &tmp), z_1_2);
	print_test_complex("Complex_RootN (nrt(z,1) == z)",
		Complex_RootN(&z_1_2, 1), z_1_2);
	print_test_complex("Complex_RootN (nrt(z,0) -> error)",
		Complex_RootN(&z_1_2, 0), COMPLEX_ERROR);
}

static
void	test_complex_arg(void)
{
	print_test_complex_float("Complex_Arg (of 1 == 0)",       Complex_Arg(&z_identity), 0.);
	print_test_complex_float("Complex_Arg (of i == +PI/2)",   Complex_Arg(&z_i), +(t_float)PI / 2.);
	print_test_complex_float("Complex_Arg (of -i == -PI/2)",  Complex_Arg(&(s_complex){ .re = 0., .im = -1. }), -(t_float)PI / 2.);
	print_test_complex_float("Complex_Arg (of -1 == PI)",     Complex_Arg(&(s_complex){ .re = -1., .im = 0. }), (t_float)PI);
	print_test_complex_float("Complex_Arg (of 1+i == PI/4)",  Complex_Arg(&(s_complex){ .re = 1., .im = 1. }), (t_float)PI / 4.);
	print_test_complex_float("Complex_Arg (of zero == 0)",    Complex_Arg(&z_zero), 0.);
}

static
void	test_complex_proj(void)
{
	print_test_complex("Complex_Proj (of finite z == z)",
		Complex_Proj(&z_1_2), z_1_2);
	print_test_complex("Complex_Proj (of zero == zero)",
		Complex_Proj(&z_zero), z_zero);
	print_test_complex("Complex_Proj (of +INF real part)",
		Complex_Proj(&(s_complex){ .re = (t_float)INFINITY, .im = 2. }),
		(s_complex){ .re = (t_float)INFINITY, .im = 0. });
	print_test_complex("Complex_Proj (of -INF real part)",
		Complex_Proj(&(s_complex){ .re = -(t_float)INFINITY, .im = 2. }),
		(s_complex){ .re = (t_float)INFINITY, .im = 0. });
	print_test_complex("Complex_Proj (of INF imaginary part)",
		Complex_Proj(&(s_complex){ .re = 1., .im = (t_float)INFINITY }),
		(s_complex){ .re = (t_float)INFINITY, .im = 0. });
	// the sign of the imaginary part must be preserved
	s_complex	result = Complex_Proj(&(s_complex){ .re = 1., .im = -(t_float)INFINITY });
	print_test_complex_bool("Complex_Proj (preserves imaginary sign)",
		(result.im == 0. && 1. / result.im < 0.), TRUE);
}

static
void	test_complex_exp(void)
{
	print_test_complex("Complex_Exp (exp(0) == 1)",
		Complex_Exp(&z_zero), z_identity);
	print_test_complex("Complex_Exp (exp(1) == e)",
		Complex_Exp(&z_identity),
		(s_complex){ .re = Float_Exp(1.), .im = 0. });
	// Euler's identity: exp(i*PI) == -1
	print_test_complex("Complex_Exp (exp(PI*i) == -1)",
		Complex_Exp(&(s_complex){ .re = 0., .im = (t_float)PI }),
		(s_complex){ .re = -1., .im = 0. });
	print_test_complex("Complex_Exp (exp(PI/2*i) == i)",
		Complex_Exp(&(s_complex){ .re = 0., .im = (t_float)PI / 2. }), z_i);
	// exp preserves the norm relation: |exp(z)| == exp(z.re)
	s_complex	result = Complex_Exp(&z_1_2);
	print_test_complex_float("Complex_Exp (|exp(z)| == exp(z.re))",
		Complex_Norm(&result), Float_Exp(z_1_2.re));
	// exp turns addition into multiplication: exp(z1 + z2) == exp(z1) * exp(z2)
	s_complex	sum = Complex_Add(&z_1_2, &z_3_4);
	s_complex	exp_z1 = Complex_Exp(&z_1_2);
	s_complex	exp_z2 = Complex_Exp(&z_3_4);
	print_test_complex("Complex_Exp (exp(z1+z2) == exp(z1)*exp(z2))",
		Complex_Exp(&sum),
		Complex_Mul(&exp_z1, &exp_z2));
}

static
void	test_complex_log(void)
{
	print_test_complex("Complex_Log (log(1) == 0)",
		Complex_Log(&z_identity), z_zero);
	print_test_complex("Complex_Log (log(e) == 1)",
		Complex_Log(&(s_complex){ .re = Float_Exp(1.), .im = 0. }), z_identity);
	print_test_complex("Complex_Log (log(i) == PI/2*i)",
		Complex_Log(&z_i),
		(s_complex){ .re = 0., .im = (t_float)PI / 2. });
	print_test_complex("Complex_Log (log(-1) == PI*i)",
		Complex_Log(&(s_complex){ .re = -1., .im = 0. }),
		(s_complex){ .re = 0., .im = (t_float)PI });
	print_test_complex("Complex_Log (of zero -> error)",
		Complex_Log(&z_zero), COMPLEX_ERROR);
	// round-trip identities
	s_complex	log = Complex_Log(&z_1_2);
	print_test_complex("Complex_Log (exp(log(z)) == z)",
		Complex_Exp(&log), z_1_2);
	s_complex	exp = Complex_Exp(&(s_complex){ .re = 0.5, .im = -0.75 });
	print_test_complex("Complex_Log (log(exp(z)) == z)",
		Complex_Log(&exp), (s_complex){ .re = 0.5, .im = -0.75 });
}

static
void	test_complex_trig(void)
{
	// consistency with real-number trigonometry
	s_complex	z_real = { .re = 0.7, .im = 0. };
	print_test_complex("Complex_Cos (of real number)",
		Complex_Cos(&z_real), (s_complex){ .re = Float_Cos(0.7), .im = 0. });
	print_test_complex("Complex_Sin (of real number)",
		Complex_Sin(&z_real), (s_complex){ .re = Float_Sin(0.7), .im = 0. });
	print_test_complex("Complex_Tan (of real number)",
		Complex_Tan(&z_real), (s_complex){ .re = Float_Tan(0.7), .im = 0. });
	// cos of a pure imaginary number is real: cos(bi) == cosh(b)
	print_test_complex("Complex_Cos (cos(i*b) == cosh(b))",
		Complex_Cos(&(s_complex){ .re = 0., .im = 0.7 }),
		(s_complex){ .re = Float_CosH(0.7), .im = 0. });
	// pythagorean identity: sin(z)^2 + cos(z)^2 == 1
	s_complex	z_mixed = { .re = 0.5, .im = -0.75 };
	s_complex	sin = Complex_Sin(&z_mixed);
	s_complex	cos = Complex_Cos(&z_mixed);
	s_complex	sin2 = Complex_Mul(&sin, &sin);
	s_complex	cos2 = Complex_Mul(&cos, &cos);
	print_test_complex("Complex trig (sin^2 + cos^2 == 1)",
		Complex_Add(&sin2, &cos2), z_identity);
	// tan(z) == sin(z) / cos(z)
	print_test_complex("Complex_Tan (tan == sin/cos)",
		Complex_Tan(&z_mixed), Complex_Div(&sin, &cos));
	// inverse functions: round-trip identities
	s_complex	tmp;
	tmp = Complex_ArcCos(&z_mixed);
	print_test_complex("Complex_ArcCos (cos(acos(z)) == z)",
		Complex_Cos(&tmp), z_mixed);
	tmp = Complex_ArcCos(&z_1_2);
	print_test_complex("Complex_ArcCos (cos(acos(z)) == z, |z| > 1)",
		Complex_Cos(&tmp), z_1_2);
	tmp = Complex_ArcSin(&z_mixed);
	print_test_complex("Complex_ArcSin (sin(asin(z)) == z)",
		Complex_Sin(&tmp), z_mixed);
	tmp = Complex_ArcSin(&z_1_2);
	print_test_complex("Complex_ArcSin (sin(asin(z)) == z, |z| > 1)",
		Complex_Sin(&tmp), z_1_2);
	tmp = Complex_ArcTan(&z_mixed);
	print_test_complex("Complex_ArcTan (tan(atan(z)) == z)",
		Complex_Tan(&tmp), z_mixed);
	// inverse functions: consistency with real-number trigonometry
	z_real = (s_complex){ .re = 0.5, .im = 0. };
	print_test_complex("Complex_ArcCos (of real number)",
		Complex_ArcCos(&z_real), (s_complex){ .re = Float_ArcCos(0.5), .im = 0. });
	print_test_complex("Complex_ArcSin (of real number)",
		Complex_ArcSin(&z_real), (s_complex){ .re = Float_ArcSin(0.5), .im = 0. });
	print_test_complex("Complex_ArcTan (of real number)",
		Complex_ArcTan(&z_real), (s_complex){ .re = Float_ArcTan(0.5), .im = 0. });
}

static
void	test_complex_trig_hyperbolic(void)
{
	// consistency with real-number functions
	s_complex	z_real = { .re = 0.7, .im = 0. };
	print_test_complex("Complex_CosH (of real number)",
		Complex_CosH(&z_real), (s_complex){ .re = Float_CosH(0.7), .im = 0. });
	print_test_complex("Complex_SinH (of real number)",
		Complex_SinH(&z_real), (s_complex){ .re = Float_SinH(0.7), .im = 0. });
	print_test_complex("Complex_TanH (of real number)",
		Complex_TanH(&z_real), (s_complex){ .re = Float_TanH(0.7), .im = 0. });
	// hyperbolic identity: cosh(z)^2 - sinh(z)^2 == 1
	s_complex	z_mixed = { .re = 0.5, .im = -0.75 };
	s_complex	sinh = Complex_SinH(&z_mixed);
	s_complex	cosh = Complex_CosH(&z_mixed);
	s_complex	sinh2 = Complex_Mul(&sinh, &sinh);
	s_complex	cosh2 = Complex_Mul(&cosh, &cosh);
	print_test_complex("Complex trig (cosh^2 - sinh^2 == 1)",
		Complex_Sub(&cosh2, &sinh2), z_identity);
	// tanh(z) == sinh(z) / cosh(z)
	print_test_complex("Complex_TanH (tanh == sinh/cosh)",
		Complex_TanH(&z_mixed), Complex_Div(&sinh, &cosh));
	// consistency with the exponential function: sinh(z) == (exp(z) - exp(-z)) / 2
	s_complex	z_neg = { .re = -z_mixed.re, .im = -z_mixed.im };
	s_complex	exp_pos = Complex_Exp(&z_mixed);
	s_complex	exp_neg = Complex_Exp(&z_neg);
	s_complex	diff = Complex_Sub(&exp_pos, &exp_neg);
	print_test_complex("Complex_SinH (sinh == (exp(z) - exp(-z)) / 2)",
		Complex_SinH(&z_mixed),
		(s_complex){ .re = diff.re / 2., .im = diff.im / 2. });
	// inverse functions: round-trip identities
	s_complex	tmp;
	tmp = Complex_InvCosH(&z_mixed);
	print_test_complex("Complex_InvCosH (cosh(acosh(z)) == z)",
		Complex_CosH(&tmp), z_mixed);
	tmp = Complex_InvCosH(&z_1_2);
	print_test_complex("Complex_InvCosH (cosh(acosh(z)) == z, |z| > 1)",
		Complex_CosH(&tmp), z_1_2);
	tmp = Complex_InvSinH(&z_mixed);
	print_test_complex("Complex_InvSinH (sinh(asinh(z)) == z)",
		Complex_SinH(&tmp), z_mixed);
	tmp = Complex_InvSinH(&z_1_2);
	print_test_complex("Complex_InvSinH (sinh(asinh(z)) == z, |z| > 1)",
		Complex_SinH(&tmp), z_1_2);
	tmp = Complex_InvTanH(&(s_complex){ .re = 0.25, .im = -0.3 });
	print_test_complex("Complex_InvTanH (tanh(atanh(z)) == z)",
		Complex_TanH(&tmp), (s_complex){ .re = 0.25, .im = -0.3 });
	// inverse functions: consistency with real-number functions
	z_real = (s_complex){ .re = 0.5, .im = 0. };
	print_test_complex("Complex_InvSinH (of real number)",
		Complex_InvSinH(&z_real), (s_complex){ .re = Float_InvSinH(0.5), .im = 0. });
	print_test_complex("Complex_InvTanH (of real number)",
		Complex_InvTanH(&z_real), (s_complex){ .re = Float_InvTanH(0.5), .im = 0. });
	z_real = (s_complex){ .re = 2., .im = 0. };
	print_test_complex("Complex_InvCosH (of real number)",
		Complex_InvCosH(&z_real), (s_complex){ .re = Float_InvCosH(2.), .im = 0. });
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
	test_complex_pow();
	test_complex_root();
	test_complex_arg();
	test_complex_proj();
	test_complex_exp();
	test_complex_log();
	test_complex_trig();
	test_complex_trig_hyperbolic();

	return (OK);
}
