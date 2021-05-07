
#include "libccc/encode/json.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

char*	json_simple = "\
{\
	\"test_bool_0\": false,\
	\"test_bool_1\": true,\
	\"test_number\": 0,\
	\"test_string\": \"\",\
	\"test_array\":  [false, true, 0, \"\"],\
	\"test_object\":\
	{\
		\"nest_bool_0\": false,\
		\"nest_bool_1\": true,\
		\"nest_number\": 0,\
		\"nest_string\": \"\",\
		\"nest_array\":  [123456, \"hello\"],\
		\"test_object\": null\
	}\
}\
";

char*	json_nested = "\
[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\":1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]\
";



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/



#if !(defined(c_jsonparse) && defined(c_jsonprint))
void test_json(void)	{}
#else
static char*	c_jsoncode(char* json)
{
	s_json* tmp = JSON_Parse(json);
	char* result = JSON_Print(tmp);
	free(tmp);
	return (result);
}
void	print_test_json(char const* test_name, int can_segfault,
		char const* expecting,
		char* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	jsoncode, str)
	TEST_PRINT(str,	jsoncode, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_json(void)
{
//	| TEST FUNCTION     | TEST NAME           | CAN SEGV  | TEST ARGS
	print_test_json("json(parse/print)        ", FALSE,    json_simple, json_simple);
	print_test_json("json(parse/print)        ", FALSE,    json_nested, json_nested);
	// TODO more tests
}
#endif



// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_encode_json(void)
{
	print_suite_title("libccc/encode/json");

	print_nonstd();

	test_json();

	return (OK);
}
