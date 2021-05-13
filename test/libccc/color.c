
#include "libccc/color.h"

#include "test.h"



#ifndef c_color_
void test_color_(void)	{}
#else
void	print_test_color_(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_color_(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	print_test_color_("color_             ",	FALSE, test1, 'm');
	print_test_color_("color_             ",	FALSE, test1, '_');
	print_test_color_("color_ (null query)",	FALSE, test3, '\0');
	print_test_color_("color_ (null ptr)  ",	TRUE,  NULL,  'm');
}
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
