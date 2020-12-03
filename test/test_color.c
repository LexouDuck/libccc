
#include "libft_color.h"

#include "test.h"



#ifdef			ft_color_
void	print_test_color_(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	s_timer t = {0};
	t_u32 result_libft;
	t_u32 result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_color_(str, c); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    color_(str, c); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strchr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
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



int		testsuite_color(void)
{
	print_suite_title("color");

	print_nonstd();

	// TODO

	return (OK);
}
