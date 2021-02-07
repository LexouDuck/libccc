
#include "libccc.h"
#include "libccc/sys/io.h"
#include "libccc/math/math.h"

#include "test.h"



#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Wimplicitly-unsigned-literal"
#pragma GCC diagnostic push // Disable GCC overflow warnings temporarily
#pragma GCC diagnostic ignored "-Wconstant-conversion"

/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifdef			c_bool_to_str
void	print_test_bool_to_str(char const* test_name, int can_segfault,
		char const* expecting,
		t_bool value,
		t_bool uppercase)
{
	TEST_PERFORM_RESULT(bool_to_str, value, uppercase)
	print_test_str(test_name, "_bool_to_str", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("value=%d, uppercase=%d", value, uppercase)
}
void	test_bool_to_str(void)
{
//	| TEST FUNCTION       | TEST NAME                   |CAN SEGV|EXPECTING| TEST ARGS
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",      1, TRUE);
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "FALSE",      0, TRUE);
	print_test_bool_to_str("bool_to_str               ",	FALSE,   "TRUE",     42, TRUE);
	print_test_bool_to_str("bool_to_str (n = max)     ",	FALSE,   "true",    255, FALSE);
	print_test_bool_to_str("bool_to_str (n = min)     ",	FALSE,  "false",      0, FALSE);
	if (g_test.flags.test_overflow)
	{
		print_test_bool_to_str("bool_to_str (n < min)     ",	FALSE,  "FALSE",     -1, TRUE);
		print_test_bool_to_str("bool_to_str (n > max)     ",	FALSE,   "TRUE",    256, TRUE);
		print_test_bool_to_str("bool_to_str (n > maxdigit)",	FALSE,   "TRUE", 999999, TRUE);
		print_test_bool_to_str("bool_to_str (n < maxdigit)",	FALSE,  "-TRUE",-999999, TRUE);
	}
}
#endif



/*
** ************************************************************************** *|
**                          Other Convert to Strings                          *|
** ************************************************************************** *|
*/

#ifdef			c_str_to_bool
void	print_test_str_to_bool(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, str_to_bool, str)
	// TODO implement
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS_ESCAPED(str)
}
void	test_str_to_bool(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif




#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop // Resets the GCC warning settings back to normal



int		testsuite_bool(void)
{
	print_suite_title("bool");

	print_nonstd();

#ifdef c_bool_to_str
	test_bool_to_str();
#endif

#ifdef c_str_to_bool
//	test_str_to_bool();
#endif

	return (OK);
}
