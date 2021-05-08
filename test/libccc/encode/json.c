
#include "libccc/encode/json.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

char*	json_simple = "\
\n{\
\n	\"test_bool_0\": false,\
\n	\"test_bool_1\": true,\
\n	\"test_number\": 0,\
\n	\"test_string\": \"\",\
\n	\"test_arrays\": \
\n	[\
\n		false,\
\n		true,\
\n		0,\
\n		\"\"\
\n	],\
\n	\"test_object\": \
\n	{\
\n		\"nest_bool_0\": false,\
\n		\"nest_bool_1\": true,\
\n		\"nest_number\": 0,\
\n		\"nest_string\": \"\",\
\n		\"nest_arrays\": \
\n		[\
\n			123456,\
\n			\"hello\"\
\n		],\
\n		\"nest_object\": null\
\n	}\
\n}\
";

char*	json_nested = "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\": 1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";

char*	json_complex = "\
\n{\
\n	\"Attributes\": {\
\n		\"SEX_ATTRIBUTE\":	[{\"Values\": [{\"CHARACTER\": \"M\"}]}],\
\n		\"AGE_ATTRIBUTE\":	[{\"Values\": [{\"INTEGER\": \"82\"}]}],\
\n		\"SPOUSE_ATTRIBUTE\":	[{\"Values\": [{\"BOOLEAN\": \"FALSE\"}]}],\
\n		\"HEIGHT_ATTRIBUTE\":	[{\"Values\": [{\"FLOAT\": \"176.5\"}]}],\
\n		\"OCCUPATION_ATTRIBUTE\":	[{\"Values\": [{\"STRING\": \"actor\"}]}],\
\n		\"LABEL_ATTRIBUTE\":	[{\"Values\": [{\"TEXT\": \"Яцк Ничолсон\"}]}],\
\n		\"BIRTHDAY_ATTRIBUTE\":	[{\"Values\": [{\"TIME\": \"-1031788800\"}]}],\
\n		\"DOCUMENT_ATTRIBUTE\":	[{\"Values\": [{\"WEB\": \"urn:isbn:0393350967\"}]}],\
\n		\"WEIGHT_ATTRIBUTE\":	[\
\n			{\
\n				\"Values\":	[\"72\"],\
\n				\"Properties\":	[\
\n					[\"listed\", \"\", \"\"]\
\n				]\
\n			},\
\n			{\
\n				\"Values\":	[\"160\"],\
\n				\"Properties\":	[\
\n					[\"reported\", \"\", \"\"],\
\n					[\"pounds\", \"lbs\", \"352\"]\
\n				]\
\n			}\
\n		],\
\n		\"LOCATION_ATTRIBUTE\":	[{\"Values\":	[\
\n			{\"TEXT\":	\"Los Angeles\"},\
\n			{\"TEXT\":	\"Aspen\"},\
\n			{\"TEXT\":	\"Malibu\"}]}\
\n		],\
\n		\"CHILD_ATTRIBUTE\":	[\
\n			{\
\n				\"Values\":	[{\"TEXT\":	\"Jennifer\"}],\
\n				\"Properties\":	[\
\n					[\"Born\", \"\", \"1963\"],\
\n					[\"Mother\", \"\", \"Sandra Knight\"]\
\n				]\
\n			},\
\n			{\
\n				\"Values\":	[{\"TEXT\":	\"Caleb\"}],\
\n				\"Properties\": [\
\n					[\"Born\", \"\", \"1970\"],\
\n					[\"Paternity\", \"open question 2\", \"not established\"],\
\n					[\"Mother\", \"\", \"Susan Anspach\"],\
\n				]\
\n			},\
\n			{\"Values\":	[{\"TEXT\":	\"Honey\"}]},\
\n			{\"Values\":	[{\"TEXT\":	\"Lorraine\"}]},\
\n			{\
\n				\"Values\": [{\"TEXT\":	\"Raymond\"}],\
\n				\"Properties\": [\
\n					[\"Born\", \"youngest\", \"1992\"],\
\n					[\"Mother\", \"\", \"Rebecca Broussard\"]\
\n				]\
\n			}\
\n		]\
\n	},\
\n	\"Properties\":	[\
\n		[\"known for\", \"most popular role\", \"The Shining\"],\
\n		[\"fan of\", \"famous fan\", \"Los Angeles Lakers\"],\
\n		[\"fan of\", \"\", \"Bob Dylan\"],\
\n		[\"also known for\", \"best performance\", \"Chinatown\"]\
\n	],\
\n	\"Values\": [\"actor\", \"player\", \"filmmaker\"]\
\n}";



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
//	| TEST FUNCTION | TEST NAME                        | CAN SEGV  | TEST ARGS
	print_test_json("json(parse strict / print pretty)", FALSE,		json_simple, json_simple);
	print_test_json("json(parse strict / print pretty)", FALSE,		json_nested, json_nested);
	print_test_json("json(parse strict / print pretty)", FALSE,		json_complex, json_complex);
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
