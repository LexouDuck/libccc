
#include <locale.h>

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

int	utf8len(char const* str)
{
	t_u8 c = str[0];
	if (c & (1 << 7)) // multi-byte character
	{
		if (c & (1 << 6)) // 2-byte character
		{
			if (c & (1 << 5)) // 3-byte character
			{
				if (c & (1 << 4)) // 4-byte character
				{
					if (c & (1 << 3))
					{
						return (-1);
					}
					else return (4);
				}
				else return (3);
			}
			else return (2);
		}
		else return (-1);
	}
	else if (c == '\0')
	{
		return (0);
	}
	else return (1);
}

void	print_test_mblen(char const* test_name, int can_segfault,
		t_char const* str)
{
	TEST_INIT(sint)
	t_char const* c;
	t_size length = strlen(str);
	for (t_size i = 0; i < length; ++i)
	{
		c = (str + i);
		mblen(NULL, 0); // reset the `mbtowcs()` conversion state
		TEST_PERFORM_LIBC(		utf8len, c)
		TEST_PRINT_LIBC(sint,	utf8len, "c=\"%.4s\"", c)
	}
}
void	test_mblen(void)
{
	setlocale(LC_ALL, "en_US.utf8");
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_mblen("mblen            ", FALSE,			"Hello World!"  );
	print_test_mblen("mblen            ", FALSE,			test1           );
	print_test_mblen("mblen            ", FALSE,			test2           );
	print_test_mblen("mblen            ", FALSE,			test3           );
	print_test_mblen("mblen            ", FALSE,			"a"             );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c0   );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c1   );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_fr );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ru );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_jp );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ho );
	print_test_mblen("mblen (empty str)", FALSE,			""              );
	print_test_mblen("mblen (null str) ", SIGNAL_SIGSEGV,	NULL            );
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
