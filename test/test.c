
#include <ctype.h>
#include <math.h>

#include "libccc/math/math.h"
#include "libccc/sys/time.h"

#include "test.h"



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
	int			can_sig,
	int			error,
	char const*	warning)
{
	static char const*  previous = NULL;

	g_test.totals.tests += 1;
	if (error)
	{
		g_test.totals.failed += 1;
	}
	g_test.last_test_failed = error;
	if (g_test.flags.verbose || error || warning)
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
			if (can_sig & 1)
				printf("\n%s - "C_YELLOW"can segfault"C_RESET, test_name);
			else printf("\n%s", test_name);
			printf(" | ");
		}
	}
	if (g_test.flags.show_args && args && (g_test.flags.verbose || g_test.last_test_failed))
	{
		printf("(%s)\t=> ", args);
	}
	if (error)
	{
		if (str_equals(expect, "(n/a)"))
			printf(C_RED"TEST COULD NOT BE PERFORMED\n"C_RESET);
		else printf(C_RED"Error:\n");
		if (function[0] == '_')
		{
			char*	expected = str_padleft("Expected", ' ', strlen(function) + 1);
			printf(">c%s: (%s)\n>%s: (%s)"C_RESET,
				function, result,
				expected, expect);
			free(expected);
		}
		else
		{
			printf(">c_%s: (%s)\n>  %s: (%s)"C_RESET,
				function, result,
				function, expect);
		}
	}
	else if (warning)
	{
		printf(C_YELLOW"Warning"C_RESET": %s", warning);
	}
	else if (g_test.flags.verbose)
	{
		printf(C_GREEN"OK!"C_RESET);
	}
	fflush(stdout);
	fflush(stderr);
	previous = function;
}



#define DEFINE_TESTFUNCTION_INT(NAME, SIGNED) \
void	print_test_##NAME(s_test_##NAME* test, char const* args)								\
{																								\
	int error;																					\
	if (test->result_sig)																		\
		error = !test->expect_sig;																\
	else if (test->expect_sig)																	\
		error = !LIBCONFIG_HANDLE_NULLPOINTERS;													\
	else error = (test->result != test->expect);												\
	print_test(test->name, test->function, args,												\
		(test->result_sig ? signals[test->result_sig] : int_##SIGNED##tostr(test->result)),	\
		(test->expect_sig ? signals[test->expect_sig] : int_##SIGNED##tostr(test->expect)),	\
		test->can_sig,																			\
		error, NULL);																			\
}																								\

DEFINE_TESTFUNCTION_INT(bool,	u)

DEFINE_TESTFUNCTION_INT( u8, 	u)
DEFINE_TESTFUNCTION_INT(u16,	u)
DEFINE_TESTFUNCTION_INT(u32,	u)
DEFINE_TESTFUNCTION_INT(u64,	u)
#ifdef __int128
DEFINE_TESTFUNCTION_INT(u128,	u)
#endif
DEFINE_TESTFUNCTION_INT(uint,	u)

DEFINE_TESTFUNCTION_INT( s8, 	s)
DEFINE_TESTFUNCTION_INT(s16,	s)
DEFINE_TESTFUNCTION_INT(s32,	s)
DEFINE_TESTFUNCTION_INT(s64,	s)
#ifdef __int128
DEFINE_TESTFUNCTION_INT(s128,	s)
#endif
DEFINE_TESTFUNCTION_INT(sint,	s)

DEFINE_TESTFUNCTION_INT(size,	u)
DEFINE_TESTFUNCTION_INT(ptrdiff,s)
DEFINE_TESTFUNCTION_INT(sintptr,s)
DEFINE_TESTFUNCTION_INT(uintptr,u)
DEFINE_TESTFUNCTION_INT(sintmax,s)
DEFINE_TESTFUNCTION_INT(uintmax,u)



// TODO implement print_test_fixed functions



#define F32_PRECISION_FORMAT	"%.8f"
#define F64_PRECISION_FORMAT	"%.16f"
#define F80_PRECISION_FORMAT	"%.20f"
#define F128_PRECISION_FORMAT	"%.32f"

#define FLOAT_PRECISION_FORMAT	CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_PRECISION_FORMAT)

#define DEFINE_TESTFUNCTION_FLOAT(NAME, SIZE) \
void	print_test_##NAME(s_test_##NAME* test, char const* args)		\
{																		\
	int error;															\
	char str_result[SIZE];												\
	char str_expect[SIZE];												\
	if (test->result_sig)												\
		error = !test->expect_sig;										\
	else if (test->expect_sig)											\
		error = !LIBCONFIG_HANDLE_NULLPOINTERS;							\
	else error = (test->result != test->expect);						\
	if (isnan(test->result) && isnan(test->expect))						\
		error = FALSE;													\
	snprintf(str_result, SIZE, FLOAT_PRECISION_FORMAT, test->result);	\
	snprintf(str_expect, SIZE, FLOAT_PRECISION_FORMAT, test->expect);	\
	print_test(test->name, test->function, args,						\
		(test->result_sig ? signals[test->result_sig] : str_result),	\
		(test->expect_sig ? signals[test->expect_sig] : str_expect),	\
		test->can_sig,													\
		error, NULL);													\
}																		\

DEFINE_TESTFUNCTION_FLOAT(f32, 32)
DEFINE_TESTFUNCTION_FLOAT(f64, 64)
#ifdef __float80
DEFINE_TESTFUNCTION_FLOAT(f80, 80)
#endif
#ifdef __float128
DEFINE_TESTFUNCTION_FLOAT(f128, 128)
#endif
DEFINE_TESTFUNCTION_FLOAT(float, sizeof(t_float) * 8)



void	print_test_sign(s_test_sign* test, char const* args)
{
	int warning = FALSE;
	int error = FALSE;
	if (test->result_sig)
		error = !test->expect_sig;
	else if (test->expect_sig)
		error = !LIBCONFIG_HANDLE_NULLPOINTERS;
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
	print_test(test->name, test->function, args,
		(test->result_sig ? signals[test->result_sig] : int_stostr(test->result)),
		(test->expect_sig ? signals[test->expect_sig] : int_stostr(test->expect)),
		test->can_sig,
		error, warning ? "return value differed, but sign was the same." : NULL);
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
		test->can_sig,
		error, NULL);
	free(tmp_result);
	free(tmp_expect);
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
		test->can_sig,
		error, NULL);
	free(tmp_result);
	free(tmp_expect);
}



void	print_test_str(s_test_str* test, char const* args)
{
	char* tmp_result = test->result == NULL ? NULL : (strlen(test->result) < STRING_ESCAPE_THRESHOLD ? strtoescape(test->result) : strdup(test->result));
	char* tmp_expect = test->expect == NULL ? NULL : (strlen(test->expect) < STRING_ESCAPE_THRESHOLD ? strtoescape(test->expect) : strdup(test->expect));
	int error;

	if (test->result_sig || test->expect_sig)
		error = (test->result_sig != test->expect_sig);
	else if (test->result == NULL || test->expect == NULL)
		error = (test->result != test->expect);
	else
		error = !str_equals(test->result, test->expect);
	print_test(test->name, test->function, args,
		tmp_result,
		tmp_expect,
		test->can_sig,
		error, NULL);
	free(tmp_result);
	free(tmp_expect);
}



void	print_test_alloc(s_test_alloc* test, char const* args)
{
	char* tmp_result = print_memory(test->result, test->length);
	char* tmp_expect = print_memory(test->expect, test->length);
	int		error = FALSE;
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
		test->can_sig,
		error, NULL);
	free(tmp_result);
	free(tmp_expect);
// TODO call print_test() here
/*
	if (error || g_test.flags.verbose)
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
	else if (g_test.flags.verbose)
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
	char*	str_result;
	char*	str_expect;
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
		test->can_sig,
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
		if (test->can_sig)
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
			free(tmp);
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
	"\n\t.offset    = %i\n" \

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
		test->can_sig,
		error, NULL);
}
