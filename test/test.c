
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "libccc.h"
#include "libccc/math.h"
#include "libccc/sys/error.h"
#include "libccc/sys/time.h"

#include "test.h"



//! Returns `1` if all the global `g_test.suite` structs have `.run` set to `0`
static
int	check_no_test_suites(void)
{
	for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
	{
		if (g_test.suites[i].run)
			return (FALSE);
	}
	return (TRUE);
}

static
void	test_cccerrorhandler(e_cccerror error, t_char const* funcname, t_char const* message)
{
	t_char const* errorname = Error_CCC_Name(error);
	t_char const* error_msg = Error_CCC_Message(error);
	t_char* errorlog = String_Format(
		"libccc: "C_RED"error[CCC:%d:%s]"C_RESET": %s -> %s -> %s%s",
		error, errorname, funcname, error_msg, message,
		(message == NULL || message[0] == '\0' || message[String_Length(message) - 1] != '\n') ? "\n" : "");
	if (g_test.last_test_error == NULL)
		g_test.last_test_error = errorlog;
	else
	{
		size_t len_old = strlen(g_test.last_test_error);
		size_t len_new = strlen(errorlog);
		g_test.last_test_error = realloc(g_test.last_test_error, len_old + len_new + sizeof(""));
		memcpy(g_test.last_test_error + len_old, errorlog, strlen(errorlog));
		free(errorlog);
		errorlog = NULL;
	}
}

void	test_init(void)
{
	if (check_no_test_suites())
	{	// if no test suites have been specified, run all of them
		for (int i = 0; i < TEST_SUITE_AMOUNT; ++i)
		{
			g_test.suites[i].totals.tests = 0;
			g_test.suites[i].totals.failed = 0;
			g_test.suites[i].totals.warnings = 0;
			g_test.suites[i].run = TRUE;
		}
	}
	Error_SetAllHandlers(test_cccerrorhandler);
}

/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

static
void	print_test(
	char const*	test_name,
	char const*	function,
	char const*	args,
	char const*	result,
	char const*	expect,
	t_testflags	flags,
	int			error,
	char const*	warning)
{
	static char const*  previous = NULL;

	g_test.suites[g_test.current_suite].totals.tests += 1;
	g_test.last_test_failed = error;
	g_test.last_test_warned = (warning != NULL);
	if (g_test.config.verbose || error || warning)
	{
		if (args == NULL)
		{
			printf(", ");
		}
		else if (function)
		{
			if (previous && function && !str_equals_until(
				(previous[0] == '_' ? previous + 1 : previous),
				(function[0] == '_' ? function + 1 : function), ' '))
				printf("\n");
			if (flags & FLAG_SIGNALMASK)
				printf("%s - "C_YELLOW"can signal"C_RESET, test_name);
			else printf("%s", test_name);
			printf(" | ");
		}
	}
	if (g_test.last_test_failed ||
		g_test.last_test_warned ||
		g_test.config.verbose)
	{
		if (g_test.config.show_args && args)
		{
			printf("(%s)\t=> ", args);
		}
		if (g_test.config.show_errors && g_test.last_test_error)
		{
			printf("\n%s", g_test.last_test_error);
		}
	}
	if (g_test.last_test_error)
	{
		free(g_test.last_test_error);
		g_test.last_test_error = NULL;
	}

	if (error)
	{
		if (flags & FLAG_WARNING)
		{
			if (warning)
			{
				printf(C_YELLOW"Warning"C_RESET": %s\n", warning);
			}
			else
			{
				printf(C_YELLOW"Warning"C_RESET": failed test: %s\n"
					"- received: (%s)\n"
					"- expected: (%s)\n",
					function,
					result,
					expect);
			}
			g_test.suites[g_test.current_suite].totals.warnings += 1;
		}
		else
		{
			if (str_equals(expect, "(n/a)"))
				printf(C_RED"TEST COULD NOT BE PERFORMED\n"C_RESET);
			else printf(C_RED"TEST FAILED:\n");
			if (function[0] == '_')
			{
				static char const* expected = "Expected";
				int length_expected = (int)sizeof("Expected");
				int length_function = (int)strlen(function) + 1;
				length_expected = (length_expected > length_function) ? length_expected : length_function;
				length_function = length_expected - length_function + 1;
				printf(">%*.*s%s: (%s)\n"
						">%*.*s: (%s)\n"C_RESET,
					length_function,
					length_function,
					"c",
					function, result,
					length_expected,
					length_expected,
					expected, expect);
			}
			else
			{
				printf( ">c_%s: (%s)\n"
						">  %s: (%s)\n"C_RESET,
					function, result,
					function, expect);
			}
			g_test.suites[g_test.current_suite].totals.failed += 1;
		}
	}
	else if (warning)
	{
		printf(C_YELLOW"Warning"C_RESET": %s\n", warning);
		if (flags & FLAG_WARNING)
			g_test.suites[g_test.current_suite].totals.warnings += 1;
	}
	else if (g_test.config.verbose)
	{
		printf(C_GREEN"OK!"C_RESET"\n");
	}
	fflush(stdout);
	fflush(stderr);
	previous = function;
}



#define DEFINE_TESTFUNCTION_INT(NAME, SIGNED, BITS) \
void	print_test_##NAME(s_test_##NAME* test, char const* args)							\
{																							\
	int error;																				\
	if (test->result_sig)																	\
		error = !test->expect_sig;															\
	else if (test->expect_sig)																\
		error = !SHOULDHANDLE_ERROR_NULLPOINTER;													\
	else error = (test->result != test->expect);											\
	print_test(test->name, test->function, args,											\
		(test->result_sig ? signals[test->result_sig] : SIGNED##BITS##tostr(test->result)),	\
		(test->expect_sig ? signals[test->expect_sig] : SIGNED##BITS##tostr(test->expect)),	\
		test->flags,																		\
		error, NULL);																		\
}																							\

DEFINE_TESTFUNCTION_INT(bool,	u, 64)

DEFINE_TESTFUNCTION_INT( u8, 	u, 8)
DEFINE_TESTFUNCTION_INT(u16,	u, 16)
DEFINE_TESTFUNCTION_INT(u32,	u, 32)
DEFINE_TESTFUNCTION_INT(u64,	u, 64)
#if LIBCONFIG_USE_INT128
DEFINE_TESTFUNCTION_INT(u128,	u, 128)
#endif
DEFINE_TESTFUNCTION_INT(uint,	u, 64)

DEFINE_TESTFUNCTION_INT( s8, 	s, 8)
DEFINE_TESTFUNCTION_INT(s16,	s, 16)
DEFINE_TESTFUNCTION_INT(s32,	s, 32)
DEFINE_TESTFUNCTION_INT(s64,	s, 64)
#if LIBCONFIG_USE_INT128
DEFINE_TESTFUNCTION_INT(s128,	s, 128)
#endif
DEFINE_TESTFUNCTION_INT(sint,	s, 64)

DEFINE_TESTFUNCTION_INT(size,	u, 64)
DEFINE_TESTFUNCTION_INT(ptrdiff,s, 64)
DEFINE_TESTFUNCTION_INT(sintptr,s, 64)
DEFINE_TESTFUNCTION_INT(uintptr,u, 64)
DEFINE_TESTFUNCTION_INT(sintmax,s, 64)
DEFINE_TESTFUNCTION_INT(uintmax,u, 64)



// TODO implement print_test_fixed functions



#define F32_PRECISION_FORMAT	"%.8f"
#define F64_PRECISION_FORMAT	"%.16lf"
#define F80_PRECISION_FORMAT	"%.20Lf"
#define F128_PRECISION_FORMAT	"%.32Lf"

#define FLOAT_PRECISION_FORMAT	

#define DEFINE_TESTFUNCTION_FLOAT(NAME, BITS) \
void	print_test_##NAME(s_test_##NAME* test, char const* args)							\
{																							\
	char* tmp = NULL;																		\
	int warning = FALSE;																	\
	int error = FALSE;																		\
	char str_result[BITS];																	\
	char str_expect[BITS];																	\
	if (test->result_sig)																	\
		error = !test->expect_sig;															\
	else if (test->expect_sig)																\
		error = !SHOULDHANDLE_ERROR_NULLPOINTER;													\
	else error = (test->result != test->expect);											\
	if (isnan(test->result) && isnan(test->expect))											\
		error = FALSE;																		\
	snprintf(str_result, BITS, CONCAT(CONCAT(F,BITS),_PRECISION_FORMAT), test->result);		\
	snprintf(str_expect, BITS, CONCAT(CONCAT(F,BITS),_PRECISION_FORMAT), test->expect);		\
	if (error && !isnan(test->result) && !isnan(test->expect))								\
	{																						\
		if (ABS(test->result - test->expect) <=												\
			FLOAT_APPROX * MAX(ABS(test->result), ABS(test->expect)))						\
		{																					\
			error = FALSE;																	\
			warning = TRUE;																	\
		}																					\
	}																						\
	if (warning)																			\
	{																						\
		tmp = (char*)malloc(1 + 128);	if (tmp == NULL) return;							\
		size_t len = snprintf(tmp,	128, "Approximation error:\n"							\
				"- received: "CONCAT(CONCAT(F,BITS),_PRECISION_FORMAT)"\n"					\
				"- expected: "CONCAT(CONCAT(F,BITS),_PRECISION_FORMAT)"\n",					\
			test->result,																	\
			test->expect);																	\
		g_test.suites[g_test.current_suite].totals.warnings += 1;							\
		if (len == 0)																		\
			return;																			\
	}																						\
	print_test(test->name, test->function, args,											\
		(test->result_sig ? signals[test->result_sig] : str_result),						\
		(test->expect_sig ? signals[test->expect_sig] : str_expect),						\
		test->flags,																		\
		error, (warning ? tmp : NULL));														\
	if (tmp)	{ free(tmp); }																\
}																							\

DEFINE_TESTFUNCTION_FLOAT(f32, 32)
DEFINE_TESTFUNCTION_FLOAT(f64, 64)
#if LIBCONFIG_USE_FLOAT80
DEFINE_TESTFUNCTION_FLOAT(f80, 80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINE_TESTFUNCTION_FLOAT(f128, 128)
#endif
DEFINE_TESTFUNCTION_FLOAT(float, LIBCONFIG_FLOAT_BITS)



void	print_test_sign(s_test_sign* test, char const* args)
{
	char* tmp = NULL;
	int warning = FALSE;
	int error = FALSE;
	if (test->result_sig)
		error = !test->expect_sig;
	else if (test->expect_sig)
		error = !SHOULDHANDLE_ERROR_NULLPOINTER;
	else
	{
		test->result_sig = 0; // reuse this variable to store sign (-1, 0, +1)
		if (test->result < 0) test->result_sig = -1;
		if (test->result > 0) test->result_sig = +1;
		test->expect_sig = 0; // reuse this variable to store sign (-1, 0, +1)
		if (test->expect < 0) test->expect_sig = -1;
		if (test->expect > 0) test->expect_sig = +1;
		warning = (test->result != test->expect);
		if (warning)
			error = (test->result_sig != test->expect_sig);
		// reset both to their previous state
		test->result_sig = 0;
		test->expect_sig = 0;
	}
	if (warning)
	{
		tmp = (char*)malloc(1 + 128);	if (tmp == NULL) return;
		size_t len = snprintf(tmp,	128, "Return value differs, but sign is the same (got %ji, but expected %ji).",
			test->result,
			test->expect);
		if (len == 0)
			return;
	}
	print_test(test->name, test->function, args,
		(test->result_sig ? signals[test->result_sig] : s64tostr(test->result)),
		(test->expect_sig ? signals[test->expect_sig] : s64tostr(test->expect)),
		test->flags,
		error, (warning ? tmp : NULL));
	if (tmp)	free(tmp);
}



void	print_test_ptr(s_test_ptr* test, char const* args)
{
	char* tmp_result = ptrtostr(test->result);
	char* tmp_expect = ptrtostr(test->expect);
	int error;

	if (test->result_sig || test->expect_sig)
		error = (test->result_sig != test->expect_sig);
	else error = (test->result != test->expect);
	print_test(test->name, test->function, args,
		(test->result_sig ? signals[test->result_sig] : tmp_result),
		(test->expect_sig ? signals[test->expect_sig] : tmp_expect),
		test->flags,
		error, NULL);
	if (tmp_result)	free(tmp_result);
	if (tmp_expect)	free(tmp_expect);
}



void	print_test_mem(s_test_mem* test, char const* args)
{
	char* tmp_result = print_memory(test->result, test->length);
	char* tmp_expect = print_memory(test->expect, test->length);
	int error;

	if (test->result_sig || test->expect_sig)
		error = (test->result_sig != test->expect_sig);
	else if (test->result == NULL || test->expect == NULL)
		error = (test->result != test->expect);
	else
		error = memcmp(test->result, test->expect, test->length);
	print_test(test->name, test->function, args,
		(test->result_sig ? signals[test->result_sig] : tmp_result),
		(test->expect_sig ? signals[test->expect_sig] : tmp_expect),
		test->flags,
		error, NULL);
	if (tmp_result)	free(tmp_result);
	if (tmp_expect)	free(tmp_expect);
}



void	print_test_str(s_test_str* test, char const* args)
{
	char* tmp;
	char* tmp_result = (test->result == NULL ? NULL : (g_test.config.show_escaped ? strtoescape(test->result) : strdup(test->result)));
	char* tmp_expect = (test->expect == NULL ? NULL : (g_test.config.show_escaped ? strtoescape(test->expect) : strdup(test->expect)));
	int error;

	tmp = tmp_result;	tmp_result = strsurround(tmp_result, '\"', '\"');	if (tmp) { free(tmp); tmp = NULL; }
	tmp = tmp_expect;	tmp_expect = strsurround(tmp_expect, '\"', '\"');	if (tmp) { free(tmp); tmp = NULL; }
	if (test->result_sig || test->expect_sig)
		error = (test->result_sig != test->expect_sig);
	else if (test->result == NULL || test->expect == NULL)
		error = (test->result != test->expect);
	else
		error = !str_equals(test->result, test->expect);
	print_test(test->name, test->function, args,
		tmp_result ? tmp_result : "NULL",
		tmp_expect ? tmp_expect : "NULL",
		test->flags,
		error, NULL);
	if (tmp_result)	free(tmp_result);
	if (tmp_expect)	free(tmp_expect);
}



void	print_test_alloc(s_test_alloc* test, char const* args)
{
	char* tmp_result = print_memory(test->result, test->length);
	char* tmp_expect = print_memory(test->expect, test->length);
	int error = FALSE;
	size_t	i;

	if (test->result == NULL)
	{
		error = TRUE;
	}
	else for (i = 0; i < test->length; ++i)
	{
		if (test->result[i])
		{
			error = TRUE;
			break;
		}
	}
	print_test(test->name, test->function, args,
		tmp_result,
		tmp_expect,
		test->flags,
		error, NULL);
	if (tmp_result)	free(tmp_result);
	if (tmp_expect)	free(tmp_expect);
// TODO call print_test() here
/*
	if (error || g_test.config.verbose)
	{
		printf("\n%s -> ", test->name);
	}
	if (error)
	{
		printf(C_RED"\nError"C_RESET": ");
		if (test->result == NULL)
			printf("The call to c_%s(...) returned NULL.", test->function);
		else printf("Every char should be '\\0', but '%c' was read at index %zu.", test->result[i], i);
	}
	else if (g_test.config.verbose)
		printf(C_GREEN"OK!"C_RESET);
*/
}



#define PRINT_TEST_STRARR(WHICH) \
	length = 0;															\
	for (i = 0; test->expect[i]; ++i)									\
	{																	\
		length += strlen(test->expect[i]);								\
	}																	\
	if (!(str_expect = (char*)malloc(length + (i ? (i - 1) * 2 : 0))))	\
		goto failure;													\
	length = 0;															\
	for (i = 0; test->expect[i]; ++i)									\
	{																	\
		if (i != 0)														\
		{																\
			str_expect[length++] = ',';									\
			str_expect[length++] = ' ';									\
		}																\
		strcpy(str_expect + length, test->expect[i]);					\
		length += strlen(test->expect[i]);								\
	}																	\

void	print_test_strarr(s_test_strarr* test, char const* args)
{
	char*	str_result = NULL;
	char*	str_expect = NULL;
	int		error = FALSE;
	int		length;
	size_t	i;

	for (int i = 0; test->result[i] && test->expect[i]; ++i)
	{
		if (!str_equals(test->result[i], test->expect[i]))
		{
			error = TRUE;
			break;
		}
	}
	PRINT_TEST_STRARR(result)
	PRINT_TEST_STRARR(expect)
	print_test(test->name, test->function, args,
		str_result,
		str_expect,
		test->flags,
		error, NULL);
failure:
	if (str_result) free(str_result);
	if (str_expect) free(str_expect);
}

/*

#define PRINT_TEST_LIST(WHICH) \
	length = 0;															\
	for (i = 0; test->expect[i]; ++i)									\
	{																	\
		length += strlen(test->expect[i]);								\
	}																	\
	if (!(str_expect = (char*)malloc(length + (i ? (i - 1) * 2 : 0))))	\
		return;															\
	length = 0;															\
	for (i = 0; test->expect[i]; ++i)									\
	{																	\
		if (i != 0)														\
		{																\
			str_expect[length++] = ',';									\
			str_expect[length++] = ' ';									\
		}																\
		strcpy(str_expect + length, test->expect[i]);					\
		length += strlen(test->expect[i]);								\
	}																	\

void	print_test_list(s_test_list* test, char const* args)
{
	int error = FALSE;
	if (test->name)
	{
		if (test->flags)
			 printf("\n%s - "C_YELLOW"can segfault"C_RESET, test->name);
		else printf("\n%s", test->name);
		printf(" -> ");
	}
	else printf(", ");
	s_list* lst = (s_list*)test->result;
	t_u32 i = 0;
	if (lst)
	{
		while (test->expect[i])
		{
			if ((lst->item && test->expect[i]) ?
				(memcmp(lst->item, test->expect[i], item_size) != 0) :
				(lst->item != test->expect[i]))
				error = TRUE;
			lst = lst->next;
			++i;
		}
	}
	else if (test->expect)
		error = TRUE;
	if (error)
	{
		printf(C_RED"Error:\n");
		lst = (s_list*)test->result;
		printf(">c_%s: [", test->function);
		char* tmp;
		while (lst)
		{
			tmp = print_memory(lst->item, item_size);
			printf("%s{%s}", (lst == test->result ? "" : ", "), tmp);
			lst = lst->next;
			if (tmp)	free(tmp);
			tmp = NULL;
		}
		i = 0;
		printf("]\n> Expected: [");
		while (test->expect[i])
		{
			printf("%s{%s}", (i == 0 ? "" : ", "), test->expect[i]);
			++i;
		}
		printf("]\n"C_RESET);
	}
	else printf(C_GREEN"OK!"C_RESET);
}

*/

#define DATE_STR_BUFFER		512
#define DATE_STR_FORMAT	\
	"\n\t.hour      = %u," \
	"\n\t.min       = %u," \
	"\n\t.sec       = %u," \
	"\n\t.year      = %i," \
	"\n\t.month     = %i," \
	"\n\t.day_month = %u," \
	"\n\t.day_week  = %i," \
	"\n\t.day_year  = %i," \
	"\n\t.is_dst    = %s," \
	"\n\t.offset    = %i," \
	"\n"

void	print_test_date(s_test_date* test, char const* args)
{
	int error;
	char str_result[DATE_STR_BUFFER];
	char str_expect[DATE_STR_BUFFER];

	if (test->result_sig || test->expect_sig)
		error = (test->result_sig != test->expect_sig);
	else
		error = !( test->result.hour      == test->expect.hour
				&& test->result.min       == test->expect.min
				&& test->result.sec       == test->expect.sec
				&& test->result.year      == test->expect.year
				&& test->result.month     == test->expect.month
				&& test->result.day_month == test->expect.day_month
				&& test->result.day_week  == test->expect.day_week
				&& test->result.day_year  == test->expect.day_year
				&& test->result.is_dst    == test->expect.is_dst
				&& test->result.offset    == test->expect.offset);
	snprintf(str_result, DATE_STR_BUFFER, "{"DATE_STR_FORMAT"}", test->result.hour, test->result.min, test->result.sec, test->result.year, test->result.month, test->result.day_month, test->result.day_week, test->result.day_year, (test->result.is_dst ? "TRUE" : "FALSE"), test->result.offset);
	snprintf(str_expect, DATE_STR_BUFFER, "{"DATE_STR_FORMAT"}", test->expect.hour, test->expect.min, test->expect.sec, test->expect.year, test->expect.month, test->expect.day_month, test->expect.day_week, test->expect.day_year, (test->expect.is_dst ? "TRUE" : "FALSE"), test->expect.offset);
	print_test(test->name, test->function, args,
		str_result,
		str_expect,
		test->flags,
		error, NULL);
}
