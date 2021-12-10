
#include "libccc/string.h"
#include "libccc/encode/common.h"
#include "libccc/encode/toml.h"

#include "test.h"



// Disable certain GCC warnings temporarily
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
// Disable certain clang warnings temporarily
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"

#if 0 // test template

#ifndef c_kvt_
void test_kvt_(void)	{}
#warning "kvt_() test suite function defined, but the function isn't defined."
#else
void	print_test_kvt_(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_kvt_(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	// TODO
}
#endif

#endif

#ifndef c_kvtget
void test_kvtget(void)	{}
#warning "kvtget() test suite function defined, but the function isn't defined."
#else
void	print_test_kvtget(char const* test_name, int can_segfault, \
		s_kvt const*	expecting,			\
		s_kvt const*	item,				\
		t_char const*	format, ...)		\
{											\
	t_char* str;							\
	va_list va_args;						\
	va_start(va_args, format);				\
	str = String_Format_VA(format, va_args);\
	va_end(va_args);						\
	if (str == NULL)	return;				\
	TEST_INIT(ptr)							\
	TEST_PERFORM(	kvtget, item, str)		\
	TEST_PRINT(ptr,	kvtget, str)			\
	String_Delete(&str);					\
}
void	test_kvtget(void)
{
	s_kvt* kvt = TOML_FromString(
	"\n""test_bool_0 = false"
	"\n""test_bool_1 = true"
	"\n""test_number = 0"
	"\n""test_string = \"\""
	"\n""test_arrays = [false, true, 0, \"\"]"
	"\n""[test_object]"
	"\n"	"nest_bool_0 = false"
	"\n"	"nest_bool_1 = true"
	"\n"	"nest_number = 0"
	"\n"	"nest_string = \"\""
	"\n"	"nest_arrays = [123456, \"hello\"]"
	"\n"	"nest_object = null");
	kvt->type = DYNAMICTYPE_OBJECT;
	s_kvt*	kvt_test_bool_0		= KVT_GetObjectItem	(kvt, "test_bool_0");
	s_kvt*	kvt_test_bool_1		= KVT_GetObjectItem	(kvt, "test_bool_1");
	s_kvt*	kvt_test_number		= KVT_GetObjectItem	(kvt, "test_number");
	s_kvt*	kvt_test_string		= KVT_GetObjectItem	(kvt, "test_string");
	s_kvt*	kvt_test_arrays		= KVT_GetObjectItem	(kvt, "test_arrays");
	s_kvt*	kvt_test_arrays_0	= KVT_GetArrayItem	(kvt_test_arrays, 0);
	s_kvt*	kvt_test_arrays_1	= KVT_GetArrayItem	(kvt_test_arrays, 1);
	s_kvt*	kvt_test_arrays_2	= KVT_GetArrayItem	(kvt_test_arrays, 2);
	s_kvt*	kvt_test_arrays_3	= KVT_GetArrayItem	(kvt_test_arrays, 3);
	s_kvt*	kvt_test_object		= KVT_GetObjectItem	(kvt, "test_object");
	s_kvt*	kvt_nest_bool_0		= KVT_GetObjectItem	(kvt_test_object, "nest_bool_0");
	s_kvt*	kvt_nest_bool_1		= KVT_GetObjectItem	(kvt_test_object, "nest_bool_1");
	s_kvt*	kvt_nest_number		= KVT_GetObjectItem	(kvt_test_object, "nest_number");
	s_kvt*	kvt_nest_string		= KVT_GetObjectItem	(kvt_test_object, "nest_string");
	s_kvt*	kvt_nest_arrays		= KVT_GetObjectItem	(kvt_test_object, "nest_arrays");
	s_kvt*	kvt_nest_arrays_0	= KVT_GetArrayItem	(kvt_nest_arrays, 0);
	s_kvt*	kvt_nest_arrays_1	= KVT_GetArrayItem	(kvt_nest_arrays, 1);
	s_kvt*	kvt_nest_object		= KVT_GetObjectItem	(kvt_test_object, "nest_object");
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| EXPECTING		| TEST ARGS
	// TODO
	print_test_kvtget("kvtget                ", FALSE,	kvt,				kvt, "");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_bool_0,	kvt, "test_bool_0");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_bool_1,	kvt, "test_bool_1");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_number,	kvt, "test_number");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_string,	kvt, "test_string");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_arrays,	kvt, "test_arrays");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_arrays_0,	kvt, "test_arrays 0");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_arrays_1,	kvt, "test_arrays 1");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_arrays_2,	kvt, "test_arrays 2");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_arrays_3,	kvt, "test_arrays 3");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_test_object,	kvt, "test_object");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_bool_0,	kvt, "test_object nest_bool_0");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_bool_1,	kvt, "test_object nest_bool_1");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_number,	kvt, "test_object nest_number");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_string,	kvt, "test_object nest_string");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_arrays,	kvt, "test_object nest_arrays");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_arrays_0,	kvt, "test_object nest_arrays 0");
	print_test_kvtget("kvtget (spaces syntax)", FALSE,	kvt_nest_arrays_1,	kvt, "test_object nest_arrays 1");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_object,	kvt, "test_object nest_object");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_bool_0,	kvt, "test_bool_0");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_bool_1,	kvt, "test_bool_1");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_number,	kvt, "test_number");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_string,	kvt, "test_string");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_arrays,	kvt, "test_arrays");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_arrays_0,	kvt, "test_arrays.0");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_arrays_1,	kvt, "test_arrays.1");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_arrays_2,	kvt, "test_arrays.2");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_arrays_3,	kvt, "test_arrays.3");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_test_object,	kvt, "test_object");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_bool_0,	kvt, "test_object.nest_bool_0");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_bool_1,	kvt, "test_object.nest_bool_1");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_number,	kvt, "test_object.nest_number");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_string,	kvt, "test_object.nest_string");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_arrays,	kvt, "test_object.nest_arrays");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_arrays_0,	kvt, "test_object.nest_arrays.0");
	print_test_kvtget("kvtget (period syntax)", FALSE,	kvt_nest_arrays_1,	kvt, "test_object.nest_arrays.1");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_object,	kvt, "test_object.nest_object");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_bool_0,	kvt, ".test_bool_0");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_bool_1,	kvt, ".test_bool_1");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_number,	kvt, ".test_number");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_string,	kvt, ".test_string");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_arrays,	kvt, ".test_arrays");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_arrays_0,	kvt, ".test_arrays[0]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_arrays_1,	kvt, ".test_arrays[1]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_arrays_2,	kvt, ".test_arrays[2]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_arrays_3,	kvt, ".test_arrays[3]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_test_object,	kvt, ".test_object");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_bool_0,	kvt, ".test_object.nest_bool_0");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_bool_1,	kvt, ".test_object.nest_bool_1");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_number,	kvt, ".test_object.nest_number");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_string,	kvt, ".test_object.nest_string");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_arrays,	kvt, ".test_object.nest_arrays");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_arrays_0,	kvt, ".test_object.nest_arrays[0]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_arrays_1,	kvt, ".test_object.nest_arrays[1]");
	print_test_kvtget("kvtget (struct syntax)", FALSE,	kvt_nest_object,	kvt, ".test_object.nest_object");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_bool_0,	kvt, "[\"test_bool_0\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_bool_1,	kvt, "[\"test_bool_1\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_number,	kvt, "[\"test_number\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_string,	kvt, "[\"test_string\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_arrays,	kvt, "[\"test_arrays\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_arrays_0,	kvt, "[\"test_arrays\"][0]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_arrays_1,	kvt, "[\"test_arrays\"][1]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_arrays_2,	kvt, "[\"test_arrays\"][2]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_arrays_3,	kvt, "[\"test_arrays\"][3]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_test_object,	kvt, "[\"test_object\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_bool_0,	kvt, "[\"test_object\"][\"nest_bool_0\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_bool_1,	kvt, "[\"test_object\"][\"nest_bool_1\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_number,	kvt, "[\"test_object\"][\"nest_number\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_string,	kvt, "[\"test_object\"][\"nest_string\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_arrays,	kvt, "[\"test_object\"][\"nest_arrays\"]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_arrays_0,	kvt, "[\"test_object\"][\"nest_arrays\"][0]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_arrays_1,	kvt, "[\"test_object\"][\"nest_arrays\"][1]");
	print_test_kvtget("kvtget (brackt syntax)", FALSE,	kvt_nest_object,	kvt, "[\"test_object\"][\"nest_object\"]");
}
#endif



// Resets the GCC warning settings back to normal
#pragma GCC diagnostic pop
// Resets the clang warning settings back to normal
#pragma clang diagnostic pop



// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_encode_kvt(void)
{
	print_suite_title("libccc/encode/kvt");

	print_nonstd();

	test_kvtget();

	// TODO

	return (OK);
}
