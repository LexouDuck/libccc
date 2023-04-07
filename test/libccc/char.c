
#include <ctype.h>

#include "libccc/char.h"

#include "test.h"



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int	testsuite_char(void)
{
	print_suite_title("libccc/char");
/*
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if ((g_test.suites[i].run == FALSE && g_test.suites[i].name && strcmp(g_test.suites[i].name, "text/char_ascii")   == 0) ||
			(g_test.suites[i].run == FALSE && g_test.suites[i].name && strcmp(g_test.suites[i].name, "text/char_unicode") == 0))
		{
			g_test.suites[i].run = TRUE;
		}
	}
*/
	return (OK);
}
