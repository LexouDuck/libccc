
#include "libccc.h"
#include "libccc/text/unicode.h"

#include "test.h"

#if 0 // test template

#ifndef c_utf
void test_utf(void)	{}
#warning "utf() test suite function defined, but the function isn't defined."
#else
void	print_test_utf(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_utf(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	// TODO
}
#endif

#endif



#ifndef c_mblen
void test_mblen(void)	{}
#warning "mblen() test suite function defined, but the function isn't defined."
#else
void	print_test_mblen(char const* test_name, int can_segfault,
		t_char const* str,
		t_size n)
{
	TEST_INIT(sint)
	t_size length = strlen(str);
	t_char const* c;
	if (length > n)
		length = n;
	for (t_size i = 0; i < length; ++i)
	{
		c = (str + i);
		mblen(NULL, 0); // reset the `mbtowcs()` conversion state
		TEST_PERFORM_LIBC(		mblen, c, n)
		TEST_PRINT_LIBC(sint,	mblen, "c=\"%.4s\", n=%zu", c, n)
	}
}
void	test_mblen(void)
{
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_mblen("mblen            ", FALSE,			"Hello World!",  (t_size)-1);
	print_test_mblen("mblen            ", FALSE,			test1,           (t_size)-1);
	print_test_mblen("mblen            ", FALSE,			test2,           (t_size)-1);
	print_test_mblen("mblen            ", FALSE,			test3,           (t_size)-1);
	print_test_mblen("mblen            ", FALSE,			"a",             (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c0,   (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c1,   (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_fr, (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ru, (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_jp, (t_size)-1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ho, (t_size)-1);
	print_test_mblen("mblen (empty str)", FALSE,			"",              (t_size)-1);
	print_test_mblen("mblen (null str) ", SIGNAL_SIGSEGV,	NULL,            (t_size)-1);
}
#endif



// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_text_unicode(void)
{
	print_suite_title("libccc/text/unicode");

	print_nonstd();

	test_mblen();
	// TODO

	return (OK);
}
