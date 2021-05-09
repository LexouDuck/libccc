
#include "libccc/encode/json.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

char*	json_null	= "null";

char*	json_bool_0	= "false";
char*	json_bool_1	= "true";



char*	json_number_0	= "0";
char*	json_number_1	= "1";
char*	json_number_2	= "42";
char*	json_number_3	= "777";
char*	json_number_4	= "123456";
char*	json_number_0f	= "0.";
char*	json_number_1f	= "1.";
char*	json_number_2f	= "42.";
char*	json_number_3f	= "777.";
char*	json_number_4f	= "123456.";
char*	json_number_0f1	= "0.0";
char*	json_number_1f1	= "1.0";
char*	json_number_2f1	= "42.0";
char*	json_number_3f1	= "777.0";
char*	json_number_4f1	= "123456.7";
char*	json_number_0f2	= "0.00";
char*	json_number_1f2	= "1.00";
char*	json_number_2f2	= "42.00";
char*	json_number_3f2	= "777.00";
char*	json_number_4f2	= "123456.78";
char*	json_number_0f3	= "0.000";
char*	json_number_1f3	= "1.000";
char*	json_number_2f3	= "42.000";
char*	json_number_3f3	= "777.000";
char*	json_number_4f3	= "123456.789";
char*	json_number_fmin_lt = "-9007199254740991";
char*	json_number_fmin_eq = "-9007199254740992";
char*	json_number_fmin_gt = "-9007199254740993";
char*	json_number_fmax_lt = "9007199254740991";
char*	json_number_fmax_eq = "9007199254740992";
char*	json_number_fmax_gt = "9007199254740993";



char*	json_string_empty	= "\"\"";
char*	json_string			= "\"Hello World!\"";
char*	json_string_utf8_fr	= "\"Être à même de ça, père de maïs sûr, d'où son âme\"";
char*	json_string_utf8_ru	= "\"Яцк Ничолсон.\"";
char*	json_string_utf8_jp	= "\"お前はもう死んでいる - 愛\"";
char*	json_string_utf8_ho = "\"�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻\"";


char*	json_array_empty	= "[]";
char*	json_array_min	= "[false,true,null]";
char*	json_array		= "\
[\
\n	false,\
\n	true,\
\n	null\
\n]";
char*	json_array_nested_min = "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\":1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";
char*	json_array_nested = "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\": 1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";



char*	json_object_empty	= "{}";
char*	json_object_min	= "{\"a\":false,\"b\":true,\"c\":null}";
char*	json_object		= "\
{\
\n	\"a\": false,\
\n	\"b\": true,\
\n	\"c\": null\
\n}";
char*	json_object_nested_min	= "{\"a\":{\"b\":{\"c\":{\"d\":{\"e\":{\"f\":{\"g\":{\"h\":{\"i\":{\"j\":{\"k\":{\"l\":{\"m\":{\"n\":{\"o\":{\"p\":{\"q\":{\"r\":{\"s\":{\"t\":{\"u\":{\"v\":{\"w\":{\"x\":{\"y\":{\"z\":\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
char*	json_object_nested	= "{\"a\": {\"b\": {\"c\": {\"d\": {\"e\": {\"f\": {\"g\": {\"h\": {\"i\": {\"j\": {\"k\": {\"l\": {\"m\": {\"n\": {\"o\": {\"p\": {\"q\": {\"r\": {\"s\": {\"t\": {\"u\": {\"v\": {\"w\": {\"x\": {\"y\": {\"z\": \"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";



char*	json_helloworld		=	"{\"hello\": \"world\"}";

char*	json_whitespace		=	"  {  \"hello\"  :  \"world\"  }  ";
char*	json_whitespace_tab	=	"\t{\t\"hello\"\t:\t\"world\"\t}\t";
char*	json_whitespace_nl	=	"\n{\n\"hello\"\n:\n\"world\"\n}\t";
char*	json_whitespace_cr	=	"\r{\r\"hello\"\r:\r\"world\"\r}\r";
char*	json_whitespace_ff	=	"\f{\f\"hello\"\f:\f\"world\"\f}\f";
char*	json_whitespace_vt	=	"\v{\v\"hello\"\v:\v\"world\"\v}\v";
char*	json_whitespace_all	=	"\t\f\r\n{\t\f\r\n\"hello\":\t\f\r\n\"world\"\t\f\r\n}\t\f\r\n";

char*	json_strange_sot	=	"\1{\"hello\":\1\"world\"\1}\n";
char*	json_strange_stx	=	"\2{\"hello\":\2\"world\"\2}\n";
char*	json_strange_etx	=	"\3{\"hello\":\3\"world\"\3}\n";
char*	json_strange_eot	=	"\4{\"hello\":\4\"world\"\4}\n";
char*	json_strange_esc	=	"\e{\"hello\":\e\"world\"\e}\n";
char*	json_strange_bs		=	"\b{\"hello\":\b\"world\"\b}\n";

char*	json_escape_sq1	=	"[\"test:\\\'.\"]";
char*	json_escape_sq2	=	"[\"test:\\\".\"]";
char*	json_escape_slb	=	"[\"test:\\\\.\"]";
char*	json_escape_slf	=	"[\"test:\\/.\"]";
char*	json_escape_spc	=	"[\"test:\\ .\"]";
char*	json_escape_tab	=	"[\"test:\\t.\"]";
char*	json_escape_nl	=	"[\"test:\\n.\"]";
char*	json_escape_cr	=	"[\"test:\\r.\"]";
char*	json_escape_ff	=	"[\"test:\\f.\"]";
char*	json_escape_vt	=	"[\"test:\\v.\"]";
char*	json_escape_esc	=	"[\"test:\\e.\"]";
char*	json_escape_bs	=	"[\"test:\\b.\"]";



char*	json_simple_min =
"{"
	"\"test_bool_0\":false,"
	"\"test_bool_1\":true,"
	"\"test_number\":0,"
	"\"test_string\":\"\","
	"\"test_arrays\":[false,true,0,\"\"],"
	"\"test_object\":"
	"{"
		"\"nest_bool_0\":false,"
		"\"nest_bool_1\":true,"
		"\"nest_number\":0,"
		"\"nest_string\":\"\","
		"\"nest_arrays\":[123456,\"hello\"],"
		"\"nest_object\":null"
	"}"
"}";
char*	json_simple = "\
{\
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



char*	json_commas_min =
"{"
	"\"test_bool_0\":false,"
	"\"test_bool_1\":true,"
	"\"test_number\":0,"
	"\"test_string\":\"\","
	"\"test_arrays\":[false,true,0,\"\",],"
	"\"test_object\":"
	"{"
		"\"nest_bool_0\":false,"
		"\"nest_bool_1\":true,"
		"\"nest_number\":0,"
		"\"nest_string\":\"\","
		"\"nest_arrays\":[123456,\"hello\",],"
		"\"nest_object\":null,"
	"},"
"}";
char*	json_commas = "\
{\
\n	\"test_bool_0\": false,\
\n	\"test_bool_1\": true,\
\n	\"test_number\": 0,\
\n	\"test_string\": \"\",\
\n	\"test_arrays\": \
\n	[\
\n		false,\
\n		true,\
\n		0,\
\n		\"\",\
\n	],\
\n	\"test_object\":\
\n	{\
\n		\"nest_bool_0\": false,\
\n		\"nest_bool_1\": true,\
\n		\"nest_number\": 0,\
\n		\"nest_string\": \"\",\
\n		\"nest_arrays\": \
\n		[\
\n			123456,\
\n			\"hello\",\
\n		],\
\n		\"nest_object\": null,\
\n	},\
\n}\
";



char*	json_newline = "\n\n\
\n{\
\n\n\"test_bool_0\":\nfalse,\
\n\n\"test_bool_1\":\ntrue,\
\n\n\"test_number\":\n0,\
\n\n\"test_string\":\n\"\",\
\n\n\"test_arrays\":\n\
\n\n[\
\n\n\nfalse\n,\
\n\n\ntrue\n,\
\n\n\n0\n,\
\n\n\n\"\"\
\n\n],\
\n\n\"test_object\"\n:\
\n\n{\
\n\n\n\"nest_bool_0\"\n:\nfalse\n\n,\
\n\n\n\"nest_bool_1\"\n:\ntrue\n\n,\
\n\n\n\"nest_number\"\n:\n0\n\n,\
\n\n\n\"nest_string\"\n:\n\"\",\
\n\n\n\"nest_arrays\"\n:\n\
\n\n\n[\
\n\n\n\n123456\n,\
\n\n\n\n\"hello\"\
\n\n\n],\
\n\n\n\"nest_object\":\t null\
\n\n}\
\n}\
\n\n";



char*	json_complex_min =
"{"
	"\"Attributes\":"
	"{"
		"\"SEX_ATTRIBUTE\":"		"[{\"Values\":[{\"CHARACTER\":\"M\"}]}],"
		"\"AGE_ATTRIBUTE\":"		"[{\"Values\":[{\"INTEGER\":\"82\"}]}],"
		"\"SPOUSE_ATTRIBUTE\":"		"[{\"Values\":[{\"BOOLEAN\":\"FALSE\"}]}],"
		"\"HEIGHT_ATTRIBUTE\":"		"[{\"Values\":[{\"FLOAT\":\"176.5\"}]}],"
		"\"OCCUPATION_ATTRIBUTE\":"	"[{\"Values\":[{\"STRING\":\"actor\"}]}],"
		"\"LABEL_ATTRIBUTE\":"		"[{\"Values\":[{\"TEXT\":\"Яцк Ничолсон\"}]}],"
		"\"BIRTHDAY_ATTRIBUTE\":"	"[{\"Values\":[{\"TIME\":\"-1031788800\"}]}],"
		"\"DOCUMENT_ATTRIBUTE\":"	"[{\"Values\":[{\"WEB\":\"urn:isbn:0393350967\"}]}],"
		"\"WEIGHT_ATTRIBUTE\":"
		"["
			"{\"Values\":[\"72\"],"
			"\"Properties\":[[\"listed\",\"\",\"\"]]},"
			"{\"Values\":[\"160\"],"
			"\"Properties\":[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]}"
		"],"
		"\"LOCATION_ATTRIBUTE\":"	"[{\"Values\":[{\"TEXT\":\"Los Angeles\"},{\"TEXT\":\"Aspen\"},{\"TEXT\":\"Malibu\"}]}],"
		"\"CHILD_ATTRIBUTE\":"
		"["
			"{\"Values\":[{\"TEXT\":\"Jennifer\"}],\"Properties\":[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]},"
			"{\"Values\":[{\"TEXT\":\"Caleb\"}],\"Properties\":[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"],]},"
			"{\"Values\":[{\"TEXT\":\"Honey\"}]},"
			"{\"Values\":[{\"TEXT\":\"Lorraine\"}]},"
			"{\"Values\":[{\"TEXT\":\"Raymond\"}],\"Properties\":[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]]}"
		"]"
	"},"
	"\"Properties\":[[\"known for\",\"most popular role\",\"The Shining\"],[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"],[\"fan of\",\"\",\"Bob Dylan\"],[\"also known for\",\"best performance\",\"Chinatown\"]],"
	"\"Values\":[\"actor\",\"player\",\"filmmaker\"]"
"}";
char*	json_complex = "\
{\
\n	\"Attributes\":\
\n	{\
\n		\"SEX_ATTRIBUTE\": [{\"Values\": [{\"CHARACTER\": \"M\"}]}],\
\n		\"AGE_ATTRIBUTE\": [{\"Values\": [{\"INTEGER\": \"82\"}]}],\
\n		\"SPOUSE_ATTRIBUTE\": [{\"Values\": [{\"BOOLEAN\": \"FALSE\"}]}],\
\n		\"HEIGHT_ATTRIBUTE\": [{\"Values\": [{\"FLOAT\": \"176.5\"}]}],\
\n		\"OCCUPATION_ATTRIBUTE\": [{\"Values\": [{\"STRING\": \"actor\"}]}],\
\n		\"LABEL_ATTRIBUTE\": [{\"Values\": [{\"TEXT\": \"Яцк Ничолсон\"}]}],\
\n		\"BIRTHDAY_ATTRIBUTE\": [{\"Values\": [{\"TIME\": \"-1031788800\"}]}],\
\n		\"DOCUMENT_ATTRIBUTE\": [{\"Values\": [{\"WEB\": \"urn:isbn:0393350967\"}]}],\
\n		\"WEIGHT_ATTRIBUTE\":\
\n		[\
\n			{\
\n				\"Values\": [\"72\"],\
\n				\"Properties\":\
\n				[\
\n					[\
\n						\"listed\",\
\n						\"\",\
\n						\"\"\
\n					]\
\n				]\
\n			},\
\n			{\
\n				\"Values\": [\"160\"],\
\n				\"Properties\":\
\n				[\
\n					[\
\n						\"reported\",\
\n						\"\",\
\n						\"\"\
\n					],\
\n					[\
\n						\"pounds\",\
\n						\"lbs\",\
\n						\"352\"\
\n					]\
\n				]\
\n			}\
\n		],\
\n		\"LOCATION_ATTRIBUTE\":\
\n		[\
\n			{\
\n				\"Values\":\
\n				[\
\n					{\"TEXT\": \"Los Angeles\"},\
\n					{\"TEXT\": \"Aspen\"},\
\n					{\"TEXT\": \"Malibu\"}\
\n				]\
\n			}\
\n		],\
\n		\"CHILD_ATTRIBUTE\":\
\n		[\
\n			{\
\n				\"Values\": [{\"TEXT\": \"Jennifer\"}],\
\n				\"Properties\":\
\n				[\
\n					[\
\n						\"Born\",\
\n						\"\",\
\n						\"1963\"\
\n					],\
\n					[\
\n						\"Mother\",\
\n						\"\",\
\n						\"Sandra Knight\"\
\n					]\
\n				]\
\n			},\
\n			{\
\n				\"Values\": [{\"TEXT\": \"Caleb\"}],\
\n				\"Properties\":\
\n				[\
\n					[\
\n						\"Born\",\
\n						\"\",\
\n						\"1970\"\
\n					],\
\n					[\
\n						\"Paternity\",\
\n						\"open question 2\",\
\n						\"not established\"\
\n					],\
\n					[\
\n						\"Mother\",\
\n						\"\",\
\n						\"Susan Anspach\"\
\n					],\
\n				]\
\n			},\
\n			{\"Values\": [{\"TEXT\": \"Honey\"}]},\
\n			{\"Values\": [{\"TEXT\": \"Lorraine\"}]},\
\n			{\
\n				\"Values\": [{\"TEXT\": \"Raymond\"}],\
\n				\"Properties\":\
\n				[\
\n					[\
\n						\"Born\",\
\n						\"youngest\",\
\n						\"1992\"\
\n					],\
\n					[\
\n						\"Mother\",\
\n						\"\",\
\n						\"Rebecca Broussard\"\
\n					]\
\n				]\
\n			}\
\n		]\
\n	},\
\n	\"Properties\":\
\n	[\
\n		[\
\n			\"known for\",\
\n			\"most popular role\",\
\n			\"The Shining\"\
\n		],\
\n		[\
\n			\"fan of\",\
\n			\"famous fan\",\
\n			\"Los Angeles Lakers\"\
\n		],\
\n		[\
\n			\"fan of\",\
\n			\"\",\
\n			\"Bob Dylan\"\
\n		],\
\n		[\
\n			\"also known for\",\
\n			\"best performance\",\
\n			\"Chinatown\"\
\n		]\
\n	],\
\n	\"Values\":\
\n	[\
\n		\"actor\",\
\n		\"player\",\
\n		\"filmmaker\"\
\n	]\
\n}";



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/



#if !(defined(c_jsonparse) && defined(c_jsonprint))
void test_json(void)	{}
#else
static
char*	c_jsoncode(char* json)
{
	s_json* tmp = JSON_Parse(json);
	char* result = JSON_Print(tmp);
	free(tmp);
	return (result);
}
void	print_test_json(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	jsoncode, (char*)str)
	TEST_PRINT(str,	jsoncode, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_json(void)
{
//	| TEST FUNCTION | TEST NAME                                            | CAN SEGV  | EXPECTING         | TEST ARGS
	print_test_json("null pointer           (parse lenient / print pretty)", FALSE,		NULL,				NULL);
	print_test_json("empty string           (parse lenient / print pretty)", FALSE,		NULL,				"");
	print_test_json("json_null              (parse lenient / print pretty)", FALSE,		json_null,			json_null);
	print_test_json("json_bool_0            (parse lenient / print pretty)", FALSE,		json_bool_0,		json_bool_0);
	print_test_json("json_bool_1            (parse lenient / print pretty)", FALSE,		json_bool_1,		json_bool_1);
	print_test_json("json_number_0          (parse lenient / print pretty)", FALSE,		json_number_0,		json_number_0);
	print_test_json("json_number_1          (parse lenient / print pretty)", FALSE,		json_number_1,		json_number_1);
	print_test_json("json_number_2          (parse lenient / print pretty)", FALSE,		json_number_2,		json_number_2);
	print_test_json("json_number_3          (parse lenient / print pretty)", FALSE,		json_number_3,		json_number_3);
	print_test_json("json_number_4          (parse lenient / print pretty)", FALSE,		json_number_4,		json_number_4);
	print_test_json("json_number_0f         (parse lenient / print pretty)", FALSE,		json_number_0,		json_number_0f);
	print_test_json("json_number_1f         (parse lenient / print pretty)", FALSE,		json_number_1,		json_number_1f);
	print_test_json("json_number_2f         (parse lenient / print pretty)", FALSE,		json_number_2,		json_number_2f);
	print_test_json("json_number_3f         (parse lenient / print pretty)", FALSE,		json_number_3,		json_number_3f);
	print_test_json("json_number_4f         (parse lenient / print pretty)", FALSE,		json_number_4,		json_number_4f);
	print_test_json("json_number_0f1        (parse lenient / print pretty)", FALSE,		json_number_0,		json_number_0f1);
	print_test_json("json_number_1f1        (parse lenient / print pretty)", FALSE,		json_number_1,		json_number_1f1);
	print_test_json("json_number_2f1        (parse lenient / print pretty)", FALSE,		json_number_2,		json_number_2f1);
	print_test_json("json_number_3f1        (parse lenient / print pretty)", FALSE,		json_number_3,		json_number_3f1);
	print_test_json("json_number_4f1        (parse lenient / print pretty)", FALSE,		json_number_4f1,	json_number_4f1);
	print_test_json("json_number_0f2        (parse lenient / print pretty)", FALSE,		json_number_0,		json_number_0f2);
	print_test_json("json_number_1f2        (parse lenient / print pretty)", FALSE,		json_number_1,		json_number_1f2);
	print_test_json("json_number_2f2        (parse lenient / print pretty)", FALSE,		json_number_2,		json_number_2f2);
	print_test_json("json_number_3f2        (parse lenient / print pretty)", FALSE,		json_number_3,		json_number_3f2);
	print_test_json("json_number_4f2        (parse lenient / print pretty)", FALSE,		json_number_4f2,	json_number_4f2);
	print_test_json("json_number_0f3        (parse lenient / print pretty)", FALSE,		json_number_0,		json_number_0f3);
	print_test_json("json_number_1f3        (parse lenient / print pretty)", FALSE,		json_number_1,		json_number_1f3);
	print_test_json("json_number_2f3        (parse lenient / print pretty)", FALSE,		json_number_2,		json_number_2f3);
	print_test_json("json_number_3f3        (parse lenient / print pretty)", FALSE,		json_number_3,		json_number_3f3);
	print_test_json("json_number_4f3        (parse lenient / print pretty)", FALSE,		json_number_4f3,	json_number_4f3);
	print_test_json("json_number_fmin_lt    (parse lenient / print pretty)", FALSE,		json_number_fmin_lt,json_number_fmin_lt);
	print_test_json("json_number_fmin_eq    (parse lenient / print pretty)", FALSE,		json_number_fmin_eq,json_number_fmin_eq);
	print_test_json("json_number_fmin_gt    (parse lenient / print pretty)", FALSE,		json_number_fmin_eq,json_number_fmin_gt);
	print_test_json("json_number_fmax_lt    (parse lenient / print pretty)", FALSE,		json_number_fmax_lt,json_number_fmax_lt);
	print_test_json("json_number_fmax_eq    (parse lenient / print pretty)", FALSE,		json_number_fmax_eq,json_number_fmax_eq);
	print_test_json("json_number_fmax_gt    (parse lenient / print pretty)", FALSE,		json_number_fmax_eq,json_number_fmax_gt);
	print_test_json("json_string_empty      (parse lenient / print pretty)", FALSE,		json_string_empty,	json_string_empty);
	print_test_json("json_string            (parse lenient / print pretty)", FALSE,		json_string,		json_string);
	print_test_json("json_string_utf8_fr    (parse lenient / print pretty)", FALSE,		json_string_utf8_fr,json_string_utf8_fr);
	print_test_json("json_string_utf8_ru    (parse lenient / print pretty)", FALSE,		json_string_utf8_ru,json_string_utf8_ru);
	print_test_json("json_string_utf8_jp    (parse lenient / print pretty)", FALSE,		json_string_utf8_jp,json_string_utf8_jp);
	print_test_json("json_string_utf8_ho    (parse lenient / print pretty)", FALSE,		json_string_utf8_ho,json_string_utf8_ho);
	print_test_json("json_array_empty       (parse lenient / print pretty)", FALSE,		json_array_empty,	json_array_empty);
	print_test_json("json_array             (parse lenient / print pretty)", FALSE,		json_array,			json_array);
	print_test_json("json_array_min         (parse lenient / print pretty)", FALSE,		json_array,			json_array_min);
	print_test_json("json_array_nested      (parse lenient / print pretty)", FALSE,		json_array_nested,	json_array_nested);
	print_test_json("json_array_nested_min  (parse lenient / print pretty)", FALSE,		json_array_nested,	json_array_nested_min);
	print_test_json("json_object_empty      (parse lenient / print pretty)", FALSE,		json_object_empty,	json_object_empty);
	print_test_json("json_object            (parse lenient / print pretty)", FALSE,		json_object,		json_object);
	print_test_json("json_object_min        (parse lenient / print pretty)", FALSE,		json_object,		json_object_min);
	print_test_json("json_object_nested     (parse lenient / print pretty)", FALSE,		json_object_nested,	json_object_nested);
	print_test_json("json_object_nested_min (parse lenient / print pretty)", FALSE,		json_object_nested,	json_object_nested_min);
	print_test_json("json_whitespace        (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace);
	print_test_json("json_whitespace_cr     (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_tab);
	print_test_json("json_whitespace_cr     (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_nl);
	print_test_json("json_whitespace_cr     (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_cr);
	print_test_json("json_whitespace_ff     (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_ff);
	print_test_json("json_whitespace_vt     (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_vt);
	print_test_json("json_whitespace_all    (parse lenient / print pretty)", FALSE,		json_helloworld,	json_whitespace_all);
	print_test_json("json_simple            (parse lenient / print pretty)", FALSE,		json_simple,		json_simple);
	print_test_json("json_simple_min        (parse lenient / print pretty)", FALSE,		json_simple,		json_simple_min);
	print_test_json("json_commas            (parse lenient / print pretty)", FALSE,		json_simple,		json_commas);
	print_test_json("json_commas_min        (parse lenient / print pretty)", FALSE,		json_simple,		json_commas_min);
	print_test_json("json_newline           (parse lenient / print pretty)", FALSE,		json_simple,		json_newline);
	print_test_json("json_complex           (parse lenient / print pretty)", FALSE,		json_complex,		json_complex);
	print_test_json("json_complex_min       (parse lenient / print pretty)", FALSE,		json_complex,		json_complex_min);
#undef  LIBCONFIG_HANDLE_PARSINGERROR
#define LIBCONFIG_HANDLE_PARSINGERROR(...)	
	print_test_json("json_escape_sq1        (parse lenient / print pretty)", FALSE,		json_escape_sq1,	json_escape_sq1);
	print_test_json("json_escape_sq2        (parse lenient / print pretty)", FALSE,		json_escape_sq2,	json_escape_sq2);
	print_test_json("json_escape_slb        (parse lenient / print pretty)", FALSE,		json_escape_slb,	json_escape_slb);
	print_test_json("json_escape_slf        (parse lenient / print pretty)", FALSE,		json_escape_slf,	json_escape_slf);
	print_test_json("json_escape_spc        (parse lenient / print pretty)", FALSE,		json_escape_spc,	json_escape_spc);
	print_test_json("json_escape_tab        (parse lenient / print pretty)", FALSE,		json_escape_tab,	json_escape_tab);
	print_test_json("json_escape_nl         (parse lenient / print pretty)", FALSE,		json_escape_nl,		json_escape_nl);
	print_test_json("json_escape_cr         (parse lenient / print pretty)", FALSE,		json_escape_cr,		json_escape_cr);
	print_test_json("json_escape_ff         (parse lenient / print pretty)", FALSE,		json_escape_ff,		json_escape_ff);
	print_test_json("json_escape_vt         (parse lenient / print pretty)", FALSE,		json_escape_vt,		json_escape_vt);
	print_test_json("json_escape_esc        (parse lenient / print pretty)", FALSE,		json_escape_esc,	json_escape_esc);
	print_test_json("json_escape_bs         (parse lenient / print pretty)", FALSE,		json_escape_bs,		json_escape_bs);
	print_test_json("json_escape_sot        (parse lenient / print pretty)", FALSE,		NULL,				json_strange_sot);
	print_test_json("json_escape_stx        (parse lenient / print pretty)", FALSE,		NULL,				json_strange_stx);
	print_test_json("json_escape_etx        (parse lenient / print pretty)", FALSE,		NULL,				json_strange_etx);
	print_test_json("json_escape_eot        (parse lenient / print pretty)", FALSE,		NULL,				json_strange_eot);
	print_test_json("json_escape_esc        (parse lenient / print pretty)", FALSE,		NULL,				json_strange_esc);
	print_test_json("json_escape_bs         (parse lenient / print pretty)", FALSE,		NULL,				json_strange_bs);
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
