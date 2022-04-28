
#include "libccc.h"
#include "libccc/text/regex.h"

#include "test.h"

#if 0 // test template

#ifndef c_regex_
void test_regex_(void)	{}
#warning "regex_() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_regex_(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	// TODO
}
#endif

#endif

// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_text_regex(void)
{
	print_suite_title("libccc/text/regex");

	print_nonstd();

	// TODO

	return (OK);
}
