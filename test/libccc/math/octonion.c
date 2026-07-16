
#include "libccc/math.h"
#include "libccc/math/octonion.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                             Testing Utilities                              ||
\*============================================================================*/

//! The comparison margin used to check approximate-equality of octonion test results
#define OCTONION_TEST_PRECISION	((t_float)1e-6)

//! Some example octonion values, used as arguments in several tests below
static s_octonion const	o_zero     = { .s =  0., .i =  0., .j =  0., .k =  0., .l =  0., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_identity = { .s = +1., .i =  0., .j =  0., .k =  0., .l =  0., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_i        = { .s =  0., .i = +1., .j =  0., .k =  0., .l =  0., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_j        = { .s =  0., .i =  0., .j = +1., .k =  0., .l =  0., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_k        = { .s =  0., .i =  0., .j =  0., .k = +1., .l =  0., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_l        = { .s =  0., .i =  0., .j =  0., .k =  0., .l = +1., .m =  0., .n =  0., .o =  0. };
static s_octonion const	o_m        = { .s =  0., .i =  0., .j =  0., .k =  0., .l =  0., .m = +1., .n =  0., .o =  0. };
static s_octonion const	o_n        = { .s =  0., .i =  0., .j =  0., .k =  0., .l =  0., .m =  0., .n = +1., .o =  0. };
static s_octonion const	o_o        = { .s =  0., .i =  0., .j =  0., .k =  0., .l =  0., .m =  0., .n =  0., .o = +1. };
static s_octonion const	o_12345678 = { .s = +1., .i = +2., .j = +3., .k = +4., .l = +5., .m = +6., .n = +7., .o = +8. };
static s_octonion const	o_87654321 = { .s = +8., .i = +7., .j = +6., .k = +5., .l = +4., .m = +3., .n = +2., .o = +1. };
static s_octonion const	o_mixed    = { .s = +0.5, .i = -0.25, .j = +0.75, .k = -0.5, .l = +0.25, .m = -0.75, .n = +0.5, .o = -0.25 };
static s_octonion const	o_small    = { .s = +0.2, .i = +0.15, .j = -0.1, .k = +0.25, .l = -0.2, .m = +0.1, .n = -0.15, .o = +0.05 };

static
t_bool	octonion_test_component_equals(t_float result, t_float expect)
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
	return (Float_Abs(result - expect) <= OCTONION_TEST_PRECISION * scale);
}

//! Checks that `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_octonion(char const* test_name,
	s_octonion result,
	s_octonion expect)
{
	t_bool	success = (
		octonion_test_component_equals(result.s, expect.s) &&
		octonion_test_component_equals(result.i, expect.i) &&
		octonion_test_component_equals(result.j, expect.j) &&
		octonion_test_component_equals(result.k, expect.k) &&
		octonion_test_component_equals(result.l, expect.l) &&
		octonion_test_component_equals(result.m, expect.m) &&
		octonion_test_component_equals(result.n, expect.n) &&
		octonion_test_component_equals(result.o, expect.o));
	g_test.suites[TESTSUITE_MATH_OCTONION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_OCTONION].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: (s=%g, i=%g, j=%g, k=%g, l=%g, m=%g, n=%g, o=%g)\n", result.s, result.i, result.j, result.k, result.l, result.m, result.n, result.o);
		printf("\t- expect: (s=%g, i=%g, j=%g, k=%g, l=%g, m=%g, n=%g, o=%g)\n", expect.s, expect.i, expect.j, expect.k, expect.l, expect.m, expect.n, expect.o);
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}

//! Checks that a scalar `result` matches `expect` (approximately), and tallies/prints the test result
static
void	print_test_octonion_float(char const* test_name,
	t_float result,
	t_float expect)
{
	t_bool	success = octonion_test_component_equals(result, expect);
	g_test.suites[TESTSUITE_MATH_OCTONION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_OCTONION].totals.failed += 1;
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
void	print_test_octonion_bool(char const* test_name,
	t_bool result,
	t_bool expect)
{
	t_bool	success = ((!result) == (!expect));
	g_test.suites[TESTSUITE_MATH_OCTONION].totals.tests += 1;
	if (!success)
	{
		g_test.suites[TESTSUITE_MATH_OCTONION].totals.failed += 1;
		printf(ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET ": %s\n", test_name);
		printf("\t- result: %s\n", (result ? "TRUE" : "FALSE"));
		printf("\t- expect: %s\n", (expect ? "TRUE" : "FALSE"));
	}
	else if (g_test.config.verbose)
	{
		printf(ANSI_COLOR_FG_GREEN "TEST PASSED" ANSI_RESET ": %s\n", test_name);
	}
}

//! Returns the given octonion, with every component negated
static
s_octonion	octonion_test_negate(s_octonion const* o)
{
	return ((s_octonion){ .s = -o->s, .i = -o->i, .j = -o->j, .k = -o->k, .l = -o->l, .m = -o->m, .n = -o->n, .o = -o->o });
}



/*============================================================================*\
||                           Per-function Test Cases                          ||
\*============================================================================*/

static
void	test_octonion(void)
{
	s_octonion	o = Octonion(1., -2., 3., -4., 5., -6., 7., -8.);
	print_test_octonion("Octonion() constructor",
		o, (s_octonion){ .s = 1., .i = -2., .j = 3., .k = -4., .l = 5., .m = -6., .n = 7., .o = -8. });
	print_test_octonion("OCTONION_NULL",
		OCTONION_NULL, o_zero);
}

static
void	test_octonion_new(void)
{
	s_octonion*	o = Octonion_New(1., -2., 3., -4., 5., -6., 7., -8.);
	print_test_octonion_bool("Octonion_New (non-null return)", (o != NULL), TRUE);
	if (o)
	{
		print_test_octonion("Octonion_New (component values)",
			*o, (s_octonion){ .s = 1., .i = -2., .j = 3., .k = -4., .l = 5., .m = -6., .n = 7., .o = -8. });
		free(o);
	}
}

static
void	test_octonion_equals(void)
{
	print_test_octonion_bool("Octonion_Equals (equal)",         Octonion_Equals(&o_12345678, &o_12345678), TRUE);
	print_test_octonion_bool("Octonion_Equals (different)",     Octonion_Equals(&o_12345678, &o_87654321), FALSE);
	print_test_octonion_bool("Octonion_Equals (differs by .s)", Octonion_Equals(&o_12345678, &(s_octonion){ .s = 9., .i = 2., .j = 3., .k = 4., .l = 5., .m = 6., .n = 7., .o = 8. }), FALSE);
	print_test_octonion_bool("Octonion_Equals (differs by .l)", Octonion_Equals(&o_12345678, &(s_octonion){ .s = 1., .i = 2., .j = 3., .k = 4., .l = 9., .m = 6., .n = 7., .o = 8. }), FALSE);
	print_test_octonion_bool("Octonion_Equals (differs by .o)", Octonion_Equals(&o_12345678, &(s_octonion){ .s = 1., .i = 2., .j = 3., .k = 4., .l = 5., .m = 6., .n = 7., .o = 9. }), FALSE);
	print_test_octonion_bool("Octonion_Equals (both zero)",     Octonion_Equals(&o_zero, &OCTONION_NULL), TRUE);
}

static
void	test_octonion_add(void)
{
	print_test_octonion("Octonion_Add",
		Octonion_Add(&o_12345678, &o_87654321),
		(s_octonion){ .s = 9., .i = 9., .j = 9., .k = 9., .l = 9., .m = 9., .n = 9., .o = 9. });
	print_test_octonion("Octonion_Add (with zero)",
		Octonion_Add(&o_12345678, &o_zero), o_12345678);
}

static
void	test_octonion_sub(void)
{
	print_test_octonion("Octonion_Sub",
		Octonion_Sub(&o_87654321, &o_12345678),
		(s_octonion){ .s = 7., .i = 5., .j = 3., .k = 1., .l = -1., .m = -3., .n = -5., .o = -7. });
	print_test_octonion("Octonion_Sub (self)",
		Octonion_Sub(&o_12345678, &o_12345678), o_zero);
}

static
void	test_octonion_mul(void)
{
	// every imaginary unit squares to -1
	s_octonion	neg_identity = octonion_test_negate(&o_identity);
	print_test_octonion("Octonion_Mul (i*i = -1)", Octonion_Mul(&o_i, &o_i), neg_identity);
	print_test_octonion("Octonion_Mul (j*j = -1)", Octonion_Mul(&o_j, &o_j), neg_identity);
	print_test_octonion("Octonion_Mul (k*k = -1)", Octonion_Mul(&o_k, &o_k), neg_identity);
	print_test_octonion("Octonion_Mul (l*l = -1)", Octonion_Mul(&o_l, &o_l), neg_identity);
	print_test_octonion("Octonion_Mul (m*m = -1)", Octonion_Mul(&o_m, &o_m), neg_identity);
	print_test_octonion("Octonion_Mul (n*n = -1)", Octonion_Mul(&o_n, &o_n), neg_identity);
	print_test_octonion("Octonion_Mul (o*o = -1)", Octonion_Mul(&o_o, &o_o), neg_identity);
	// the quaternion subalgebra: i,j,k behave like quaternions
	print_test_octonion("Octonion_Mul (i*j = +k)", Octonion_Mul(&o_i, &o_j), o_k);
	print_test_octonion("Octonion_Mul (j*k = +i)", Octonion_Mul(&o_j, &o_k), o_i);
	print_test_octonion("Octonion_Mul (k*i = +j)", Octonion_Mul(&o_k, &o_i), o_j);
	// products involving the upper units (this codebase's basis convention)
	print_test_octonion("Octonion_Mul (i*l = +m)", Octonion_Mul(&o_i, &o_l), o_m);
	print_test_octonion("Octonion_Mul (j*l = +n)", Octonion_Mul(&o_j, &o_l), o_n);
	print_test_octonion("Octonion_Mul (k*l = +o)", Octonion_Mul(&o_k, &o_l), o_o);
	print_test_octonion("Octonion_Mul (l*m = +i)", Octonion_Mul(&o_l, &o_m), o_i);
	print_test_octonion("Octonion_Mul (l*n = +j)", Octonion_Mul(&o_l, &o_n), o_j);
	print_test_octonion("Octonion_Mul (l*o = +k)", Octonion_Mul(&o_l, &o_o), o_k);
	// imaginary units anti-commute
	print_test_octonion("Octonion_Mul (j*i = -k)", Octonion_Mul(&o_j, &o_i), octonion_test_negate(&o_k));
	print_test_octonion("Octonion_Mul (l*i = -m)", Octonion_Mul(&o_l, &o_i), octonion_test_negate(&o_m));
	print_test_octonion("Octonion_Mul (o*l = -k)", Octonion_Mul(&o_o, &o_l), octonion_test_negate(&o_k));
	// octonion multiplication is NOT associative: (i*j)*l == +o, but i*(j*l) == -o
	s_octonion	ij = Octonion_Mul(&o_i, &o_j);
	s_octonion	jl = Octonion_Mul(&o_j, &o_l);
	print_test_octonion("Octonion_Mul ((i*j)*l == +o)", Octonion_Mul(&ij, &o_l), o_o);
	print_test_octonion("Octonion_Mul (i*(j*l) == -o)", Octonion_Mul(&o_i, &jl), octonion_test_negate(&o_o));
	// general case
	print_test_octonion("Octonion_Mul (general case)",
		Octonion_Mul(&o_12345678, &o_87654321),
		(s_octonion){ .s = -104., .i = 14., .j = 12., .k = 10., .l = 152., .m = 42., .n = 4., .o = 74. });
	print_test_octonion("Octonion_Mul (by identity)",
		Octonion_Mul(&o_12345678, &o_identity), o_12345678);
	// norm is multiplicative: |o1*o2| == |o1|*|o2| (octonions form a composition algebra)
	s_octonion	product = Octonion_Mul(&o_12345678, &o_87654321);
	print_test_octonion_float("Octonion_Mul (norm is multiplicative)",
		Octonion_Norm(&product),
		Octonion_Norm(&o_12345678) * Octonion_Norm(&o_87654321));
}

static
void	test_octonion_norm(void)
{
	print_test_octonion_float("Octonion_Norm (1..8)",   Octonion_Norm(&o_12345678), Float_Root2(204.));
	print_test_octonion_float("Octonion_Norm (unit l)", Octonion_Norm(&o_l), 1.);
	print_test_octonion_float("Octonion_Norm (zero)",   Octonion_Norm(&o_zero), 0.);
	print_test_octonion_float("Octonion_Norm (3-4-5)",  Octonion_Norm(&(s_octonion){ .s = 0., .i = 0., .j = 0., .k = 0., .l = 3., .m = 0., .n = 0., .o = 4. }), 5.);
}

static
void	test_octonion_conjugate(void)
{
	print_test_octonion("Octonion_Conjugate",
		Octonion_Conjugate(&o_12345678),
		(s_octonion){ .s = 1., .i = -2., .j = -3., .k = -4., .l = -5., .m = -6., .n = -7., .o = -8. });
	// o * conj(o) == |o|^2
	s_octonion	conj = Octonion_Conjugate(&o_12345678);
	print_test_octonion("Octonion_Conjugate (o * conj(o) == norm squared)",
		Octonion_Mul(&o_12345678, &conj),
		(s_octonion){ .s = 204., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
}

static
void	test_octonion_inverse(void)
{
	s_octonion	inverse = Octonion_Inverse(&o_12345678);
	print_test_octonion("Octonion_Inverse (o * o^-1 == 1)",
		Octonion_Mul(&o_12345678, &inverse), o_identity);
	print_test_octonion("Octonion_Inverse (o^-1 * o == 1)",
		Octonion_Mul(&inverse, &o_12345678), o_identity);
	print_test_octonion("Octonion_Inverse (of identity)",
		Octonion_Inverse(&o_identity), o_identity);
	print_test_octonion("Octonion_Inverse (of zero -> error)",
		Octonion_Inverse(&o_zero), OCTONION_ERROR);
}

static
void	test_octonion_normalize(void)
{
	s_octonion	normalized = Octonion_Normalize(&o_12345678);
	print_test_octonion_float("Octonion_Normalize (norm == 1)",
		Octonion_Norm(&normalized), 1.);
	print_test_octonion("Octonion_Normalize (direction preserved)",
		normalized,
		(s_octonion){
			.s = 1. / Float_Root2(204.),
			.i = 2. / Float_Root2(204.),
			.j = 3. / Float_Root2(204.),
			.k = 4. / Float_Root2(204.),
			.l = 5. / Float_Root2(204.),
			.m = 6. / Float_Root2(204.),
			.n = 7. / Float_Root2(204.),
			.o = 8. / Float_Root2(204.) });
	print_test_octonion("Octonion_Normalize (of zero -> error)",
		Octonion_Normalize(&o_zero), OCTONION_ERROR);
}

static
void	test_octonion_div(void)
{
	// right division: (o1 * o2) / o2 == o1
	s_octonion	product = Octonion_Mul(&o_12345678, &o_87654321);
	print_test_octonion("Octonion_Div ((o1*o2) / o2 == o1)",
		Octonion_Div(&product, &o_87654321), o_12345678);
	print_test_octonion("Octonion_Div (o / o == 1)",
		Octonion_Div(&o_12345678, &o_12345678), o_identity);
	print_test_octonion("Octonion_Div (o / 1 == o)",
		Octonion_Div(&o_12345678, &o_identity), o_12345678);
	// division is equivalent to multiplying with the inverse (on the right)
	s_octonion	inverse = Octonion_Inverse(&o_87654321);
	print_test_octonion("Octonion_Div (o1 / o2 == o1 * o2^-1)",
		Octonion_Div(&o_12345678, &o_87654321),
		Octonion_Mul(&o_12345678, &inverse));
}

static
void	test_octonion_pow(void)
{
	s_octonion	squared = Octonion_Mul(&o_12345678, &o_12345678);
	print_test_octonion("Octonion_Pow (o^2 == o*o)",
		Octonion_Pow(&o_12345678, 2.), squared);
	print_test_octonion("Octonion_Pow (o^1 == o)",
		Octonion_Pow(&o_12345678, 1.), o_12345678);
	print_test_octonion("Octonion_Pow (o^0 == 1)",
		Octonion_Pow(&o_12345678, 0.), o_identity);
	print_test_octonion("Octonion_Pow (o^-1 == inverse)",
		Octonion_Pow(&o_12345678, -1.), Octonion_Inverse(&o_12345678));
	print_test_octonion("Octonion_Pow (real base: 4^0.5 == 2)",
		Octonion_Pow(&(s_octonion){ .s = 4., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }, 0.5),
		(s_octonion){ .s = 2., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Pow ((-1)^0.5 == i, axis convention)",
		Octonion_Pow(&(s_octonion){ .s = -1., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }, 0.5), o_i);
	print_test_octonion("Octonion_Pow (0^2 == 0)",
		Octonion_Pow(&o_zero, 2.), o_zero);
	print_test_octonion("Octonion_Pow (0^0 == 1)",
		Octonion_Pow(&o_zero, 0.), o_identity);
	print_test_octonion("Octonion_Pow (0^-1 -> error)",
		Octonion_Pow(&o_zero, -1.), OCTONION_ERROR);
}

static
void	test_octonion_root(void)
{
	s_octonion	root = Octonion_Root2(&o_12345678);
	print_test_octonion("Octonion_Root2 (sqrt(o)^2 == o)",
		Octonion_Mul(&root, &root), o_12345678);
	print_test_octonion("Octonion_Root2 (sqrt(4) == 2)",
		Octonion_Root2(&(s_octonion){ .s = 4., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }),
		(s_octonion){ .s = 2., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Root2 (sqrt(-1) == i, axis convention)",
		Octonion_Root2(&(s_octonion){ .s = -1., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }), o_i);

	root = Octonion_Root3(&o_12345678);
	s_octonion	cube = Octonion_Mul(&root, &root);
	print_test_octonion("Octonion_Root3 (cbrt(o)^3 == o)",
		Octonion_Mul(&cube, &root), o_12345678);

	root = Octonion_RootN(&o_12345678, 4);
	s_octonion	tmp = Octonion_Mul(&root, &root);
	print_test_octonion("Octonion_RootN (nrt(o,4)^4 == o)",
		Octonion_Mul(&tmp, &tmp), o_12345678);
	print_test_octonion("Octonion_RootN (nrt(o,1) == o)",
		Octonion_RootN(&o_12345678, 1), o_12345678);
	print_test_octonion("Octonion_RootN (nrt(o,0) -> error)",
		Octonion_RootN(&o_12345678, 0), OCTONION_ERROR);
}

static
void	test_octonion_arg(void)
{
	print_test_octonion_float("Octonion_Arg (of 1 == 0)",       Octonion_Arg(&o_identity), 0.);
	print_test_octonion_float("Octonion_Arg (of i == PI/2)",    Octonion_Arg(&o_i), (t_float)PI / 2.);
	print_test_octonion_float("Octonion_Arg (of l == PI/2)",    Octonion_Arg(&o_l), (t_float)PI / 2.);
	print_test_octonion_float("Octonion_Arg (of -1 == PI)",     Octonion_Arg(&(s_octonion){ .s = -1., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }), (t_float)PI);
	print_test_octonion_float("Octonion_Arg (of 1+o == PI/4)",  Octonion_Arg(&(s_octonion){ .s = 1., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 1. }), (t_float)PI / 4.);
	print_test_octonion_float("Octonion_Arg (of zero -> error)", Octonion_Arg(&o_zero), NAN);
}

static
void	test_octonion_exp(void)
{
	print_test_octonion("Octonion_Exp (exp(0) == 1)",
		Octonion_Exp(&o_zero), o_identity);
	print_test_octonion("Octonion_Exp (exp(1) == e)",
		Octonion_Exp(&o_identity),
		(s_octonion){ .s = Float_Exp(1.), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	// Euler's identity: exp(PI * u) == -1, for any imaginary unit u
	s_octonion	neg_identity = octonion_test_negate(&o_identity);
	print_test_octonion("Octonion_Exp (exp(PI*i) == -1)",
		Octonion_Exp(&(s_octonion){ .s = 0., .i = (t_float)PI, .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }), neg_identity);
	print_test_octonion("Octonion_Exp (exp(PI*l) == -1)",
		Octonion_Exp(&(s_octonion){ .s = 0., .i = 0., .j = 0., .k = 0., .l = (t_float)PI, .m = 0., .n = 0., .o = 0. }), neg_identity);
	// exp preserves the norm relation: |exp(o)| == exp(o.s)
	s_octonion	result = Octonion_Exp(&o_mixed);
	print_test_octonion_float("Octonion_Exp (|exp(o)| == exp(o.s))",
		Octonion_Norm(&result), Float_Exp(o_mixed.s));
}

static
void	test_octonion_log(void)
{
	print_test_octonion("Octonion_Log (log(1) == 0)",
		Octonion_Log(&o_identity), o_zero);
	print_test_octonion("Octonion_Log (log(e) == 1)",
		Octonion_Log(&(s_octonion){ .s = Float_Exp(1.), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }), o_identity);
	print_test_octonion("Octonion_Log (log(l) == PI/2*l)",
		Octonion_Log(&o_l),
		(s_octonion){ .s = 0., .i = 0., .j = 0., .k = 0., .l = (t_float)PI / 2., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Log (log(-1) == PI*i, axis convention)",
		Octonion_Log(&(s_octonion){ .s = -1., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. }),
		(s_octonion){ .s = 0., .i = (t_float)PI, .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Log (of zero -> error)",
		Octonion_Log(&o_zero), OCTONION_ERROR);
	// round-trip identities
	s_octonion	log = Octonion_Log(&o_12345678);
	print_test_octonion("Octonion_Log (exp(log(o)) == o)",
		Octonion_Exp(&log), o_12345678);
	s_octonion	exp = Octonion_Exp(&o_mixed);
	print_test_octonion("Octonion_Log (log(exp(o)) == o)",
		Octonion_Log(&exp), o_mixed);
}

static
void	test_octonion_trig(void)
{
	// consistency with real-number trigonometry
	s_octonion	o_real = { .s = 0.7, .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. };
	print_test_octonion("Octonion_Cos (of real octonion)",
		Octonion_Cos(&o_real), (s_octonion){ .s = Float_Cos(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Sin (of real octonion)",
		Octonion_Sin(&o_real), (s_octonion){ .s = Float_Sin(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_Tan (of real octonion)",
		Octonion_Tan(&o_real), (s_octonion){ .s = Float_Tan(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	// pythagorean identity: sin(o)^2 + cos(o)^2 == 1
	s_octonion	sin = Octonion_Sin(&o_mixed);
	s_octonion	cos = Octonion_Cos(&o_mixed);
	s_octonion	sin2 = Octonion_Mul(&sin, &sin);
	s_octonion	cos2 = Octonion_Mul(&cos, &cos);
	print_test_octonion("Octonion trig (sin^2 + cos^2 == 1)",
		Octonion_Add(&sin2, &cos2), o_identity);
	// tan(o) == sin(o) / cos(o)
	print_test_octonion("Octonion_Tan (tan == sin/cos)",
		Octonion_Tan(&o_mixed), Octonion_Div(&sin, &cos));
	// inverse functions: round-trip identities
	s_octonion	tmp;
	tmp = Octonion_ArcCos(&o_mixed);
	print_test_octonion("Octonion_ArcCos (cos(acos(o)) == o)",
		Octonion_Cos(&tmp), o_mixed);
	tmp = Octonion_ArcCos(&o_12345678);
	print_test_octonion("Octonion_ArcCos (cos(acos(o)) == o, |o| > 1)",
		Octonion_Cos(&tmp), o_12345678);
	tmp = Octonion_ArcSin(&o_mixed);
	print_test_octonion("Octonion_ArcSin (sin(asin(o)) == o)",
		Octonion_Sin(&tmp), o_mixed);
	tmp = Octonion_ArcSin(&o_12345678);
	print_test_octonion("Octonion_ArcSin (sin(asin(o)) == o, |o| > 1)",
		Octonion_Sin(&tmp), o_12345678);
	tmp = Octonion_ArcTan(&o_mixed);
	print_test_octonion("Octonion_ArcTan (tan(atan(o)) == o)",
		Octonion_Tan(&tmp), o_mixed);
	// inverse functions: consistency with real-number trigonometry
	o_real = (s_octonion){ .s = 0.5, .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. };
	print_test_octonion("Octonion_ArcCos (of real octonion)",
		Octonion_ArcCos(&o_real), (s_octonion){ .s = Float_ArcCos(0.5), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_ArcSin (of real octonion)",
		Octonion_ArcSin(&o_real), (s_octonion){ .s = Float_ArcSin(0.5), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_ArcTan (of real octonion)",
		Octonion_ArcTan(&o_real), (s_octonion){ .s = Float_ArcTan(0.5), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
}

static
void	test_octonion_trig_hyperbolic(void)
{
	// consistency with real-number functions
	s_octonion	o_real = { .s = 0.7, .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. };
	print_test_octonion("Octonion_CosH (of real octonion)",
		Octonion_CosH(&o_real), (s_octonion){ .s = Float_CosH(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_SinH (of real octonion)",
		Octonion_SinH(&o_real), (s_octonion){ .s = Float_SinH(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_TanH (of real octonion)",
		Octonion_TanH(&o_real), (s_octonion){ .s = Float_TanH(0.7), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	// hyperbolic identity: cosh(o)^2 - sinh(o)^2 == 1
	s_octonion	sinh = Octonion_SinH(&o_mixed);
	s_octonion	cosh = Octonion_CosH(&o_mixed);
	s_octonion	sinh2 = Octonion_Mul(&sinh, &sinh);
	s_octonion	cosh2 = Octonion_Mul(&cosh, &cosh);
	print_test_octonion("Octonion trig (cosh^2 - sinh^2 == 1)",
		Octonion_Sub(&cosh2, &sinh2), o_identity);
	// tanh(o) == sinh(o) / cosh(o)
	print_test_octonion("Octonion_TanH (tanh == sinh/cosh)",
		Octonion_TanH(&o_mixed), Octonion_Div(&sinh, &cosh));
	// consistency with the exponential function: sinh(o) == (exp(o) - exp(-o)) / 2
	s_octonion	o_neg = octonion_test_negate(&o_mixed);
	s_octonion	exp_pos = Octonion_Exp(&o_mixed);
	s_octonion	exp_neg = Octonion_Exp(&o_neg);
	s_octonion	diff = Octonion_Sub(&exp_pos, &exp_neg);
	print_test_octonion("Octonion_SinH (sinh == (exp(o) - exp(-o)) / 2)",
		Octonion_SinH(&o_mixed),
		(s_octonion){ .s = diff.s / 2., .i = diff.i / 2., .j = diff.j / 2., .k = diff.k / 2., .l = diff.l / 2., .m = diff.m / 2., .n = diff.n / 2., .o = diff.o / 2. });
	// inverse functions: round-trip identities
	s_octonion	tmp;
	tmp = Octonion_InvCosH(&o_mixed);
	print_test_octonion("Octonion_InvCosH (cosh(acosh(o)) == o)",
		Octonion_CosH(&tmp), o_mixed);
	tmp = Octonion_InvCosH(&o_12345678);
	print_test_octonion("Octonion_InvCosH (cosh(acosh(o)) == o, |o| > 1)",
		Octonion_CosH(&tmp), o_12345678);
	tmp = Octonion_InvSinH(&o_mixed);
	print_test_octonion("Octonion_InvSinH (sinh(asinh(o)) == o)",
		Octonion_SinH(&tmp), o_mixed);
	tmp = Octonion_InvSinH(&o_12345678);
	print_test_octonion("Octonion_InvSinH (sinh(asinh(o)) == o, |o| > 1)",
		Octonion_SinH(&tmp), o_12345678);
	tmp = Octonion_InvTanH(&o_small);
	print_test_octonion("Octonion_InvTanH (tanh(atanh(o)) == o)",
		Octonion_TanH(&tmp), o_small);
	// inverse functions: consistency with real-number functions
	o_real = (s_octonion){ .s = 0.5, .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. };
	print_test_octonion("Octonion_InvSinH (of real octonion)",
		Octonion_InvSinH(&o_real), (s_octonion){ .s = Float_InvSinH(0.5), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	print_test_octonion("Octonion_InvTanH (of real octonion)",
		Octonion_InvTanH(&o_real), (s_octonion){ .s = Float_InvTanH(0.5), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
	o_real = (s_octonion){ .s = 2., .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. };
	print_test_octonion("Octonion_InvCosH (of real octonion)",
		Octonion_InvCosH(&o_real), (s_octonion){ .s = Float_InvCosH(2.), .i = 0., .j = 0., .k = 0., .l = 0., .m = 0., .n = 0., .o = 0. });
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_octonion(void)
{
	print_suite_title("libccc/math/octonion");

	test_octonion();
	test_octonion_new();
	test_octonion_equals();
	test_octonion_add();
	test_octonion_sub();
	test_octonion_mul();
	test_octonion_norm();
	test_octonion_conjugate();
	test_octonion_inverse();
	test_octonion_normalize();
	test_octonion_div();
	test_octonion_pow();
	test_octonion_root();
	test_octonion_arg();
	test_octonion_exp();
	test_octonion_log();
	test_octonion_trig();
	test_octonion_trig_hyperbolic();

	return (OK);
}
