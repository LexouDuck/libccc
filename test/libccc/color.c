
#include "libccc/image/color.h"

#include "test.h"

#if 0 // test template

#ifndef c_color_
void test_color_(void)	{}
#warning "color_() test suite function defined, but the function isn't defined."
#else
void	print_test_color_(char const* test_name, t_testflags flags,
		char const* str,
		char c)
{
	// TODO
}
void	test_color_(void)
{
//	| TEST FUNCTION  | TEST NAME             |TESTFLAG| TEST ARGS
	print_test_color_("color_             ",	FALSE, test1, 'm');
	print_test_color_("color_             ",	FALSE, test1, '_');
	print_test_color_("color_ (null query)",	FALSE, test3, '\0');
	print_test_color_("color_ (null ptr)  ",	TRUE,  NULL,  'm');
}
#endif

#endif

// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_color(void)
{
	print_suite_title("libccc/color");

	print_nonstd();

	// TODO

	return (OK);
}
