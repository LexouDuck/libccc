
#include "libccc.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"

#if 0 // test template

#ifndef c_format_
void test_format_(void)	{}
#warning "format_() test suite function defined, but the function isn't defined."
#else
void	print_test_format_(char const* test_name, t_testflags flags,
		char const* str,
		char c)
{
	// TODO
}
void	test_format_(void)
{
//	| TEST FUNCTION  | TEST NAME             |TESTFLAG| TEST ARGS
	// TODO
}
#endif

#endif

// TODO



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_format(void)
{
	print_suite_title("libccc/text/format");

	// TODO

	return (OK);
}
