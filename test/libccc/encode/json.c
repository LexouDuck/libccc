
#include "libccc/encode/json.h"

#include "test.h"



/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

t_utf8*	json_null	= "null";

t_utf8*	json_bool_0	= "false";
t_utf8*	json_bool_1	= "true";



t_utf8*	json_number_0	= "0";
t_utf8*	json_number_1	= "1";
t_utf8*	json_number_2	= "42";
t_utf8*	json_number_3	= "777";
t_utf8*	json_number_4	= "123456";
t_utf8*	json_number_0f	= "0.";
t_utf8*	json_number_1f	= "1.";
t_utf8*	json_number_2f	= "42.";
t_utf8*	json_number_3f	= "777.";
t_utf8*	json_number_4f	= "123456.";
t_utf8*	json_number_0f1	= "0.0";
t_utf8*	json_number_1f1	= "1.0";
t_utf8*	json_number_2f1	= "42.0";
t_utf8*	json_number_3f1	= "777.0";
t_utf8*	json_number_4f1	= "123456.7";
t_utf8*	json_number_0f2	= "0.00";
t_utf8*	json_number_1f2	= "1.00";
t_utf8*	json_number_2f2	= "42.00";
t_utf8*	json_number_3f2	= "777.00";
t_utf8*	json_number_4f2	= "123456.78";
t_utf8*	json_number_0f3	= "0.000";
t_utf8*	json_number_1f3	= "1.000";
t_utf8*	json_number_2f3	= "42.000";
t_utf8*	json_number_3f3	= "777.000";
t_utf8*	json_number_4f3	= "123456.789";
t_utf8*	json_number_fmin_lt = "-9007199254740991";
t_utf8*	json_number_fmin_eq = "-9007199254740992";
t_utf8*	json_number_fmin_gt = "-9007199254740993";
t_utf8*	json_number_fmax_lt = "9007199254740991";
t_utf8*	json_number_fmax_eq = "9007199254740992";
t_utf8*	json_number_fmax_gt = "9007199254740993";
t_utf8*	json_number_inf_u_lower_0 =  "inf";
t_utf8*	json_number_inf_p_lower_0 = "+inf";
t_utf8*	json_number_inf_n_lower_0 = "-inf";
t_utf8*	json_number_inf_u_lower_1 =  "infinity";
t_utf8*	json_number_inf_p_lower_1 = "+infinity";
t_utf8*	json_number_inf_n_lower_1 = "-infinity";
t_utf8*	json_number_inf_u_mixed_0 =  "Inf";
t_utf8*	json_number_inf_p_mixed_0 = "+Inf";
t_utf8*	json_number_inf_n_mixed_0 = "-Inf";
t_utf8*	json_number_inf_u_mixed_1 =  "Infinity";
t_utf8*	json_number_inf_p_mixed_1 = "+Infinity";
t_utf8*	json_number_inf_n_mixed_1 = "-Infinity";
t_utf8*	json_number_inf_u_upper_0 =  "INF";
t_utf8*	json_number_inf_p_upper_0 = "+INF";
t_utf8*	json_number_inf_n_upper_0 = "-INF";
t_utf8*	json_number_inf_u_upper_1 =  "INFINITY";
t_utf8*	json_number_inf_p_upper_1 = "+INFINITY";
t_utf8*	json_number_inf_n_upper_1 = "-INFINITY";
t_utf8*	json_number_nan_u_lower_0 =  "nan";
t_utf8*	json_number_nan_p_lower_0 = "+nan";
t_utf8*	json_number_nan_n_lower_0 = "-nan";
t_utf8*	json_number_nan_u_mixed_0 =  "NaN";
t_utf8*	json_number_nan_p_mixed_0 = "+NaN";
t_utf8*	json_number_nan_n_mixed_0 = "-NaN";
t_utf8*	json_number_nan_u_upper_0 =  "NAN";
t_utf8*	json_number_nan_p_upper_0 = "+NAN";
t_utf8*	json_number_nan_n_upper_0 = "-NAN";

t_utf8*	json_number_inf_u_utf8_0 =  "∞";
t_utf8*	json_number_inf_p_utf8_0 = "+∞";
t_utf8*	json_number_inf_n_utf8_0 = "-∞";
t_utf8*	json_number_inf_u_utf8_1 =  "\u221E";
t_utf8*	json_number_inf_p_utf8_1 = "+\u221E";
t_utf8*	json_number_inf_n_utf8_1 = "-\u221E";



t_utf8*	json_bigint_empty	= "n";
t_utf8*	json_bigint_0		= "0n";
t_utf8*	json_bigint_1		= "1n";
t_utf8*	json_bigint_2		= "42n";
t_utf8*	json_bigint_3		= "777n";
t_utf8*	json_bigint_4		= "123456n";
t_utf8*	json_bigint_0f		= "0.n";
t_utf8*	json_bigint_1f		= "1.n";
t_utf8*	json_bigint_2f		= "42.n";
t_utf8*	json_bigint_3f		= "777.n";
t_utf8*	json_bigint_4f		= "123456.n";
t_utf8*	json_bigint_0f1		= "0.0n";
t_utf8*	json_bigint_1f1		= "1.0n";
t_utf8*	json_bigint_2f1		= "42.0n";
t_utf8*	json_bigint_3f1		= "777.0n";
t_utf8*	json_bigint_4f1		= "123456.7n";
t_utf8*	json_bigint_0f2		= "0.00n";
t_utf8*	json_bigint_1f2		= "1.00n";
t_utf8*	json_bigint_2f2		= "42.00n";
t_utf8*	json_bigint_3f2		= "777.00n";
t_utf8*	json_bigint_4f2		= "123456.78n";
t_utf8*	json_bigint_0f3		= "0.000n";
t_utf8*	json_bigint_1f3		= "1.000n";
t_utf8*	json_bigint_2f3		= "42.000n";
t_utf8*	json_bigint_3f3		= "777.000n";
t_utf8*	json_bigint_4f3		= "123456.789n";
t_utf8*	json_bigint_fmin_lt	= "-9007199254740991n";
t_utf8*	json_bigint_fmin_eq	= "-9007199254740992n";
t_utf8*	json_bigint_fmin_gt	= "-9007199254740993n";
t_utf8*	json_bigint_fmax_lt	= "9007199254740991n";
t_utf8*	json_bigint_fmax_eq	= "9007199254740992n";
t_utf8*	json_bigint_fmax_gt	= "9007199254740993n";
t_utf8*	json_bigint_s64min_lt = "-9223372036854775807n";
t_utf8*	json_bigint_s64min_eq = "-9223372036854775808n";
t_utf8*	json_bigint_s64min_gt = "-9223372036854775809n";
t_utf8*	json_bigint_s64max_lt = "9223372036854775806n";
t_utf8*	json_bigint_s64max_eq = "9223372036854775807n";
t_utf8*	json_bigint_s64max_gt = "9223372036854775808n";
t_utf8*	json_bigint_bad_unan_lower	= "nann";
t_utf8*	json_bigint_bad_unan_upper	= "NANn";
t_utf8*	json_bigint_bad_uinf_lower	= "infn";
t_utf8*	json_bigint_bad_uinf_upper	= "INFn";
t_utf8*	json_bigint_bad_nnan_lower	= "-nann";
t_utf8*	json_bigint_bad_nnan_upper	= "-NANn";
t_utf8*	json_bigint_bad_ninf_lower	= "-infn";
t_utf8*	json_bigint_bad_ninf_upper	= "-INFn";
t_utf8*	json_bigint_bad_pnan_lower	= "+nann";
t_utf8*	json_bigint_bad_pnan_upper	= "+NANn";
t_utf8*	json_bigint_bad_pinf_lower	= "+infn";
t_utf8*	json_bigint_bad_pinf_upper	= "+INFn";



t_utf8*	json_string_empty	= "\"\"";
t_utf8*	json_string			= "\"Hello World!\"";
t_utf8*	json_string_cc_c0	= "\"␡␁␂␃␄␅␆␇␈␉␊␋␌␍␎␏␐␑␒␓␔␕␖␗␘␙␚␛␜␝␞␟\"";
t_utf8*	json_string_cc_c1	= "\"\"";
t_utf8*	json_string_utf8_fr	= "\"Être à même de ça, père de maïs sûr, d'où son âme\"";
t_utf8*	json_string_utf8_ru	= "\"Яцк Ничолсон.\"";
t_utf8*	json_string_utf8_jp	= "\"お前はもう死んでいる - 愛\"";
t_utf8*	json_string_utf8_ho = "\"�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻\"";


t_utf8*	json_array_empty	= "[]";
t_utf8*	json_array_min	= "[false,true,null]";
t_utf8*	json_array		= "\
[\
\n	false,\
\n	true,\
\n	null\
\n]";
t_utf8*	json_array_nested_min = "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\":1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";
t_utf8*	json_array_nested = "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\": 1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";



t_utf8*	json_object_empty	= "{}";
t_utf8*	json_object_min	= "{\"a\":false,\"b\":true,\"c\":null}";
t_utf8*	json_object		= "\
{\
\n	\"a\": false,\
\n	\"b\": true,\
\n	\"c\": null\
\n}";
t_utf8*	json_object_nested_min	= "{\"a\":{\"b\":{\"c\":{\"d\":{\"e\":{\"f\":{\"g\":{\"h\":{\"i\":{\"j\":{\"k\":{\"l\":{\"m\":{\"n\":{\"o\":{\"p\":{\"q\":{\"r\":{\"s\":{\"t\":{\"u\":{\"v\":{\"w\":{\"x\":{\"y\":{\"z\":\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
t_utf8*	json_object_nested	= "{\"a\": {\"b\": {\"c\": {\"d\": {\"e\": {\"f\": {\"g\": {\"h\": {\"i\": {\"j\": {\"k\": {\"l\": {\"m\": {\"n\": {\"o\": {\"p\": {\"q\": {\"r\": {\"s\": {\"t\": {\"u\": {\"v\": {\"w\": {\"x\": {\"y\": {\"z\": \"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";



t_utf8*	json_helloworld		=	"{\"hello\": \"world\"}";

t_utf8*	json_whitespace		=	"  {  \"hello\"  :  \"world\"  }  ";
t_utf8*	json_whitespace_tab	=	"\t{\t\"hello\"\t:\t\"world\"\t}\t";
t_utf8*	json_whitespace_nl	=	"\n{\n\"hello\"\n:\n\"world\"\n}\t";
t_utf8*	json_whitespace_cr	=	"\r{\r\"hello\"\r:\r\"world\"\r}\r";
t_utf8*	json_whitespace_ff	=	"\f{\f\"hello\"\f:\f\"world\"\f}\f";
t_utf8*	json_whitespace_vt	=	"\v{\v\"hello\"\v:\v\"world\"\v}\v";
t_utf8*	json_whitespace_all	=	"\t\f\r\n{\t\f\r\n\"hello\":\t\f\r\n\"world\"\t\f\r\n}\t\f\r\n";

t_utf8*	json_strange_sot	=	"\1{\"hello\":\1\"world\"\1}\n";
t_utf8*	json_strange_stx	=	"\2{\"hello\":\2\"world\"\2}\n";
t_utf8*	json_strange_etx	=	"\3{\"hello\":\3\"world\"\3}\n";
t_utf8*	json_strange_eot	=	"\4{\"hello\":\4\"world\"\4}\n";
t_utf8*	json_strange_esc	=	"\e{\"hello\":\e\"world\"\e}\n";
t_utf8*	json_strange_bs		=	"\b{\"hello\":\b\"world\"\b}\n";

t_utf8*	json_escape_sq1	=	"[\"test:\\\'.\"]";
t_utf8*	json_escape_sq2	=	"[\"test:\\\".\"]";
t_utf8*	json_escape_slb	=	"[\"test:\\\\.\"]";
t_utf8*	json_escape_slf	=	"[\"test:\\/.\"]";
t_utf8*	json_escape_spc	=	"[\"test:\\ .\"]";
t_utf8*	json_escape_tab	=	"[\"test:\\t.\"]";
t_utf8*	json_escape_nl	=	"[\"test:\\n.\"]";
t_utf8*	json_escape_cr	=	"[\"test:\\r.\"]";
t_utf8*	json_escape_ff	=	"[\"test:\\f.\"]";
t_utf8*	json_escape_vt	=	"[\"test:\\v.\"]";
t_utf8*	json_escape_esc	=	"[\"test:\\e.\"]";
t_utf8*	json_escape_bel	=	"[\"test:\\a.\"]";
t_utf8*	json_escape_bs	=	"[\"test:\\b.\"]";



t_utf8*	json_simple_min =
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
t_utf8*	json_simple = "\
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



t_utf8*	json_commas_min =
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
t_utf8*	json_commas = "\
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



t_utf8*	json_newline = "\n\n\
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



t_utf8*	json_complex_min =
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
t_utf8*	json_complex = "\
{\
\n	\"Attributes\": \
\n	{\
\n		\"SEX_ATTRIBUTE\": [{\"Values\": [{\"CHARACTER\": \"M\"}]}],\
\n		\"AGE_ATTRIBUTE\": [{\"Values\": [{\"INTEGER\": \"82\"}]}],\
\n		\"SPOUSE_ATTRIBUTE\": [{\"Values\": [{\"BOOLEAN\": \"FALSE\"}]}],\
\n		\"HEIGHT_ATTRIBUTE\": [{\"Values\": [{\"FLOAT\": \"176.5\"}]}],\
\n		\"OCCUPATION_ATTRIBUTE\": [{\"Values\": [{\"STRING\": \"actor\"}]}],\
\n		\"LABEL_ATTRIBUTE\": [{\"Values\": [{\"TEXT\": \"Яцк Ничолсон\"}]}],\
\n		\"BIRTHDAY_ATTRIBUTE\": [{\"Values\": [{\"TIME\": \"-1031788800\"}]}],\
\n		\"DOCUMENT_ATTRIBUTE\": [{\"Values\": [{\"WEB\": \"urn:isbn:0393350967\"}]}],\
\n		\"WEIGHT_ATTRIBUTE\": \
\n		[\
\n			{\
\n				\"Values\": [\"72\"],\
\n				\"Properties\": [[\
\n						\"listed\",\
\n						\"\",\
\n						\"\"\
\n					]]\
\n			},\
\n			{\
\n				\"Values\": [\"160\"],\
\n				\"Properties\": \
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
\n		\"LOCATION_ATTRIBUTE\": [{\"Values\": \
\n				[\
\n					{\"TEXT\": \"Los Angeles\"},\
\n					{\"TEXT\": \"Aspen\"},\
\n					{\"TEXT\": \"Malibu\"}\
\n				]}],\
\n		\"CHILD_ATTRIBUTE\": \
\n		[\
\n			{\
\n				\"Values\": [{\"TEXT\": \"Jennifer\"}],\
\n				\"Properties\": \
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
\n				\"Properties\": \
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
\n					]\
\n				]\
\n			},\
\n			{\"Values\": [{\"TEXT\": \"Honey\"}]},\
\n			{\"Values\": [{\"TEXT\": \"Lorraine\"}]},\
\n			{\
\n				\"Values\": [{\"TEXT\": \"Raymond\"}],\
\n				\"Properties\": \
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
\n	\"Properties\": \
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
\n	\"Values\": \
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
t_utf8*	c_jsoncode(t_utf8* json)
{
	s_json* tmp = JSON_Parse(json);
	t_utf8* result = JSON_Print(tmp);
	free(tmp);
	return (result);
}
void	print_test_json(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	jsoncode, (t_utf8*)str)
	TEST_PRINT(str,	jsoncode, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_json(void)
{
//	| TEST FUNCTION | TEST NAME                                   | CAN SEGV  | EXPECTING         | TEST ARGS
	print_test_json("null pointer              (lenient -> pretty)", FALSE,		NULL,						NULL);
	print_test_json("empty string              (lenient -> pretty)", FALSE,		NULL,						"");
	print_test_json("json_null                 (lenient -> pretty)", FALSE,		json_null,					json_null);
	print_test_json("json_bool_0               (lenient -> pretty)", FALSE,		json_bool_0,				json_bool_0);
	print_test_json("json_bool_1               (lenient -> pretty)", FALSE,		json_bool_1,				json_bool_1);
	print_test_json("json_number_0             (lenient -> pretty)", FALSE,		json_number_0,				json_number_0);
	print_test_json("json_number_1             (lenient -> pretty)", FALSE,		json_number_1,				json_number_1);
	print_test_json("json_number_2             (lenient -> pretty)", FALSE,		json_number_2,				json_number_2);
	print_test_json("json_number_3             (lenient -> pretty)", FALSE,		json_number_3,				json_number_3);
	print_test_json("json_number_4             (lenient -> pretty)", FALSE,		json_number_4,				json_number_4);
	print_test_json("json_number_0f            (lenient -> pretty)", FALSE,		json_number_0,				json_number_0f);
	print_test_json("json_number_1f            (lenient -> pretty)", FALSE,		json_number_1,				json_number_1f);
	print_test_json("json_number_2f            (lenient -> pretty)", FALSE,		json_number_2,				json_number_2f);
	print_test_json("json_number_3f            (lenient -> pretty)", FALSE,		json_number_3,				json_number_3f);
	print_test_json("json_number_4f            (lenient -> pretty)", FALSE,		json_number_4,				json_number_4f);
	print_test_json("json_number_0f1           (lenient -> pretty)", FALSE,		json_number_0,				json_number_0f1);
	print_test_json("json_number_1f1           (lenient -> pretty)", FALSE,		json_number_1,				json_number_1f1);
	print_test_json("json_number_2f1           (lenient -> pretty)", FALSE,		json_number_2,				json_number_2f1);
	print_test_json("json_number_3f1           (lenient -> pretty)", FALSE,		json_number_3,				json_number_3f1);
	print_test_json("json_number_4f1           (lenient -> pretty)", FALSE,		json_number_4f1,			json_number_4f1);
	print_test_json("json_number_0f2           (lenient -> pretty)", FALSE,		json_number_0,				json_number_0f2);
	print_test_json("json_number_1f2           (lenient -> pretty)", FALSE,		json_number_1,				json_number_1f2);
	print_test_json("json_number_2f2           (lenient -> pretty)", FALSE,		json_number_2,				json_number_2f2);
	print_test_json("json_number_3f2           (lenient -> pretty)", FALSE,		json_number_3,				json_number_3f2);
	print_test_json("json_number_4f2           (lenient -> pretty)", FALSE,		json_number_4f2,			json_number_4f2);
	print_test_json("json_number_0f3           (lenient -> pretty)", FALSE,		json_number_0,				json_number_0f3);
	print_test_json("json_number_1f3           (lenient -> pretty)", FALSE,		json_number_1,				json_number_1f3);
	print_test_json("json_number_2f3           (lenient -> pretty)", FALSE,		json_number_2,				json_number_2f3);
	print_test_json("json_number_3f3           (lenient -> pretty)", FALSE,		json_number_3,				json_number_3f3);
	print_test_json("json_number_4f3           (lenient -> pretty)", FALSE,		json_number_4f3,			json_number_4f3);
	print_test_json("json_number_fmin_lt       (lenient -> pretty)", FALSE,		json_number_fmin_lt,		json_number_fmin_lt);
	print_test_json("json_number_fmin_eq       (lenient -> pretty)", FALSE,		json_number_fmin_eq,		json_number_fmin_eq);
	print_test_json("json_number_fmin_gt       (lenient -> pretty)", FALSE,		json_number_fmin_eq,		json_number_fmin_gt);
	print_test_json("json_number_fmax_lt       (lenient -> pretty)", FALSE,		json_number_fmax_lt,		json_number_fmax_lt);
	print_test_json("json_number_fmax_eq       (lenient -> pretty)", FALSE,		json_number_fmax_eq,		json_number_fmax_eq);
	print_test_json("json_number_fmax_gt       (lenient -> pretty)", FALSE,		json_number_fmax_eq,		json_number_fmax_gt);
	print_test_json("json_number_inf_u_lower_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_lower_0);
	print_test_json("json_number_inf_p_lower_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_lower_0);
	print_test_json("json_number_inf_n_lower_0 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_lower_0);
	print_test_json("json_number_inf_u_lower_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_lower_1);
	print_test_json("json_number_inf_p_lower_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_lower_1);
	print_test_json("json_number_inf_n_lower_1 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_lower_1);
	print_test_json("json_number_inf_u_mixed_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_mixed_0);
	print_test_json("json_number_inf_p_mixed_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_mixed_0);
	print_test_json("json_number_inf_n_mixed_0 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_mixed_0);
	print_test_json("json_number_inf_u_mixed_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_mixed_1);
	print_test_json("json_number_inf_p_mixed_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_mixed_1);
	print_test_json("json_number_inf_n_mixed_1 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_mixed_1);
	print_test_json("json_number_inf_u_upper_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_upper_0);
	print_test_json("json_number_inf_p_upper_0 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_upper_0);
	print_test_json("json_number_inf_n_upper_0 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_upper_0);
	print_test_json("json_number_inf_u_upper_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_u_upper_1);
	print_test_json("json_number_inf_p_upper_1 (lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_number_inf_p_upper_1);
	print_test_json("json_number_inf_n_upper_1 (lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_number_inf_n_upper_1);
	print_test_json("json_number_nan_u_lower_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_u_lower_0);
	print_test_json("json_number_nan_p_lower_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_p_lower_0);
	print_test_json("json_number_nan_n_lower_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_n_lower_0);
	print_test_json("json_number_nan_u_mixed_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_u_mixed_0);
	print_test_json("json_number_nan_p_mixed_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_p_mixed_0);
	print_test_json("json_number_nan_n_mixed_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_n_mixed_0);
	print_test_json("json_number_nan_u_upper_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_u_upper_0);
	print_test_json("json_number_nan_p_upper_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_p_upper_0);
	print_test_json("json_number_nan_n_upper_0 (lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_number_nan_n_upper_0);
	print_test_json("json_number_inf_u_utf8_0  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_u_utf8_0);
	print_test_json("json_number_inf_p_utf8_0  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_p_utf8_0);
	print_test_json("json_number_inf_n_utf8_0  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_n_utf8_0);
	print_test_json("json_number_inf_u_utf8_1  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_u_utf8_1);
	print_test_json("json_number_inf_p_utf8_1  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_p_utf8_1);
	print_test_json("json_number_inf_n_utf8_1  (lenient -> pretty)", FALSE,		NULL,						json_number_inf_n_utf8_1);
	print_test_json("json_bigint_empty         (lenient -> pretty)", FALSE,		NULL,						json_bigint_empty);
	print_test_json("json_bigint_0             (lenient -> pretty)", FALSE,		json_bigint_0,				json_bigint_0);
	print_test_json("json_bigint_1             (lenient -> pretty)", FALSE,		json_bigint_1,				json_bigint_1);
	print_test_json("json_bigint_2             (lenient -> pretty)", FALSE,		json_bigint_2,				json_bigint_2);
	print_test_json("json_bigint_3             (lenient -> pretty)", FALSE,		json_bigint_3,				json_bigint_3);
	print_test_json("json_bigint_4             (lenient -> pretty)", FALSE,		json_bigint_4,				json_bigint_4);
	print_test_json("json_bigint_0f            (lenient -> pretty)", FALSE,		json_bigint_0,				json_bigint_0f);
	print_test_json("json_bigint_1f            (lenient -> pretty)", FALSE,		json_bigint_1,				json_bigint_1f);
	print_test_json("json_bigint_2f            (lenient -> pretty)", FALSE,		json_bigint_2,				json_bigint_2f);
	print_test_json("json_bigint_3f            (lenient -> pretty)", FALSE,		json_bigint_3,				json_bigint_3f);
	print_test_json("json_bigint_4f            (lenient -> pretty)", FALSE,		json_bigint_4,				json_bigint_4f);
	print_test_json("json_bigint_0f1           (lenient -> pretty)", FALSE,		json_bigint_0,				json_bigint_0f1);
	print_test_json("json_bigint_1f1           (lenient -> pretty)", FALSE,		json_bigint_1,				json_bigint_1f1);
	print_test_json("json_bigint_2f1           (lenient -> pretty)", FALSE,		json_bigint_2,				json_bigint_2f1);
	print_test_json("json_bigint_3f1           (lenient -> pretty)", FALSE,		json_bigint_3,				json_bigint_3f1);
	print_test_json("json_bigint_4f1           (lenient -> pretty)", FALSE,		json_bigint_4,				json_bigint_4f1);
	print_test_json("json_bigint_0f2           (lenient -> pretty)", FALSE,		json_bigint_0,				json_bigint_0f2);
	print_test_json("json_bigint_1f2           (lenient -> pretty)", FALSE,		json_bigint_1,				json_bigint_1f2);
	print_test_json("json_bigint_2f2           (lenient -> pretty)", FALSE,		json_bigint_2,				json_bigint_2f2);
	print_test_json("json_bigint_3f2           (lenient -> pretty)", FALSE,		json_bigint_3,				json_bigint_3f2);
	print_test_json("json_bigint_4f2           (lenient -> pretty)", FALSE,		json_bigint_4,				json_bigint_4f2);
	print_test_json("json_bigint_0f3           (lenient -> pretty)", FALSE,		json_bigint_0,				json_bigint_0f3);
	print_test_json("json_bigint_1f3           (lenient -> pretty)", FALSE,		json_bigint_1,				json_bigint_1f3);
	print_test_json("json_bigint_2f3           (lenient -> pretty)", FALSE,		json_bigint_2,				json_bigint_2f3);
	print_test_json("json_bigint_3f3           (lenient -> pretty)", FALSE,		json_bigint_3,				json_bigint_3f3);
	print_test_json("json_bigint_4f3           (lenient -> pretty)", FALSE,		json_bigint_4,				json_bigint_4f3);
	print_test_json("json_bigint_fmin_lt       (lenient -> pretty)", FALSE,		json_bigint_fmin_lt,		json_bigint_fmin_lt);
	print_test_json("json_bigint_fmin_eq       (lenient -> pretty)", FALSE,		json_bigint_fmin_eq,		json_bigint_fmin_eq);
	print_test_json("json_bigint_fmin_gt       (lenient -> pretty)", FALSE,		json_bigint_fmin_gt,		json_bigint_fmin_gt);
	print_test_json("json_bigint_fmax_lt       (lenient -> pretty)", FALSE,		json_bigint_fmax_lt,		json_bigint_fmax_lt);
	print_test_json("json_bigint_fmax_eq       (lenient -> pretty)", FALSE,		json_bigint_fmax_eq,		json_bigint_fmax_eq);
	print_test_json("json_bigint_fmax_gt       (lenient -> pretty)", FALSE,		json_bigint_fmax_gt,		json_bigint_fmax_gt);
	print_test_json("json_bigint_s64min_lt     (lenient -> pretty)", FALSE,		json_bigint_s64min_lt,		json_bigint_s64min_lt);
	print_test_json("json_bigint_s64min_eq     (lenient -> pretty)", FALSE,		json_bigint_s64min_eq,		json_bigint_s64min_eq);
	print_test_json("json_bigint_s64min_gt     (lenient -> pretty)", FALSE,		json_bigint_s64max_eq,		json_bigint_s64min_gt); // TODO change for VLQ bigint
	print_test_json("json_bigint_s64max_lt     (lenient -> pretty)", FALSE,		json_bigint_s64max_lt,		json_bigint_s64max_lt);
	print_test_json("json_bigint_s64max_eq     (lenient -> pretty)", FALSE,		json_bigint_s64max_eq,		json_bigint_s64max_eq);
	print_test_json("json_bigint_s64max_gt     (lenient -> pretty)", FALSE,		json_bigint_s64min_eq,		json_bigint_s64max_gt); // TODO change for VLQ bigint
	print_test_json("json_bigint_bad_uinf_lower(lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_bigint_bad_uinf_lower);
	print_test_json("json_bigint_bad_uinf_upper(lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_bigint_bad_uinf_upper);
	print_test_json("json_bigint_bad_ninf_lower(lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_bigint_bad_ninf_lower);
	print_test_json("json_bigint_bad_ninf_upper(lenient -> pretty)", FALSE,		json_number_inf_n_lower_0,	json_bigint_bad_ninf_upper);
	print_test_json("json_bigint_bad_pinf_lower(lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_bigint_bad_pinf_lower);
	print_test_json("json_bigint_bad_pinf_upper(lenient -> pretty)", FALSE,		json_number_inf_p_lower_0,	json_bigint_bad_pinf_upper);
	print_test_json("json_bigint_bad_unan_lower(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_unan_lower);
	print_test_json("json_bigint_bad_unan_upper(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_unan_upper);
	print_test_json("json_bigint_bad_nnan_lower(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_nnan_lower);
	print_test_json("json_bigint_bad_nnan_upper(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_nnan_upper);
	print_test_json("json_bigint_bad_pnan_lower(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_pnan_lower);
	print_test_json("json_bigint_bad_pnan_upper(lenient -> pretty)", FALSE,		json_number_nan_u_lower_0,	json_bigint_bad_pnan_upper);
	print_test_json("json_string_empty         (lenient -> pretty)", FALSE,		json_string_empty,			json_string_empty);
	print_test_json("json_string               (lenient -> pretty)", FALSE,		json_string,				json_string);
	print_test_json("json_string_cc_c0         (lenient -> pretty)", FALSE,		json_string_cc_c0,			json_string_cc_c0);
	print_test_json("json_string_cc_c1         (lenient -> pretty)", FALSE,		json_string_cc_c1,			json_string_cc_c1);
	print_test_json("json_string_utf8_fr       (lenient -> pretty)", FALSE,		json_string_utf8_fr,		json_string_utf8_fr);
	print_test_json("json_string_utf8_ru       (lenient -> pretty)", FALSE,		json_string_utf8_ru,		json_string_utf8_ru);
	print_test_json("json_string_utf8_jp       (lenient -> pretty)", FALSE,		json_string_utf8_jp,		json_string_utf8_jp);
	print_test_json("json_string_utf8_ho       (lenient -> pretty)", FALSE,		json_string_utf8_ho,		json_string_utf8_ho);
	print_test_json("json_array_empty          (lenient -> pretty)", FALSE,		json_array_empty,			json_array_empty);
	print_test_json("json_array                (lenient -> pretty)", FALSE,		json_array,					json_array);
	print_test_json("json_array_min            (lenient -> pretty)", FALSE,		json_array,					json_array_min);
	print_test_json("json_array_nested         (lenient -> pretty)", FALSE,		json_array_nested,			json_array_nested);
	print_test_json("json_array_nested_min     (lenient -> pretty)", FALSE,		json_array_nested,			json_array_nested_min);
	print_test_json("json_object_empty         (lenient -> pretty)", FALSE,		json_object_empty,			json_object_empty);
	print_test_json("json_object               (lenient -> pretty)", FALSE,		json_object,				json_object);
	print_test_json("json_object_min           (lenient -> pretty)", FALSE,		json_object,				json_object_min);
	print_test_json("json_object_nested        (lenient -> pretty)", FALSE,		json_object_nested,			json_object_nested);
	print_test_json("json_object_nested_min    (lenient -> pretty)", FALSE,		json_object_nested,			json_object_nested_min);
	print_test_json("json_whitespace           (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace);
	print_test_json("json_whitespace_tab       (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_tab);
	print_test_json("json_whitespace_nl        (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_nl);
	print_test_json("json_whitespace_cr        (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_cr);
	print_test_json("json_whitespace_ff        (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_ff);
	print_test_json("json_whitespace_vt        (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_vt);
	print_test_json("json_whitespace_all       (lenient -> pretty)", FALSE,		json_helloworld,			json_whitespace_all);
	print_test_json("json_simple               (lenient -> pretty)", FALSE,		json_simple,				json_simple);
	print_test_json("json_simple_min           (lenient -> pretty)", FALSE,		json_simple,				json_simple_min);
	print_test_json("json_commas               (lenient -> pretty)", FALSE,		json_simple,				json_commas);
	print_test_json("json_commas_min           (lenient -> pretty)", FALSE,		json_simple,				json_commas_min);
	print_test_json("json_newline              (lenient -> pretty)", FALSE,		json_simple,				json_newline);
	print_test_json("json_complex              (lenient -> pretty)", FALSE,		json_complex,				json_complex);
	print_test_json("json_complex_min          (lenient -> pretty)", FALSE,		json_complex,				json_complex_min);
#undef  LIBCONFIG_HANDLE_PARSINGERROR
#define LIBCONFIG_HANDLE_PARSINGERROR(...)	
	print_test_json("json_escape_sq1           (lenient -> pretty)", FALSE,		NULL,						json_escape_sq1);
	print_test_json("json_escape_sq2           (lenient -> pretty)", FALSE,		json_escape_sq2,			json_escape_sq2);
	print_test_json("json_escape_slb           (lenient -> pretty)", FALSE,		json_escape_slb,			json_escape_slb);
	print_test_json("json_escape_slf           (lenient -> pretty)", FALSE,		"[\"test:/.\"]",			json_escape_slf);
	print_test_json("json_escape_spc           (lenient -> pretty)", FALSE,		NULL,						json_escape_spc);
	print_test_json("json_escape_tab           (lenient -> pretty)", FALSE,		json_escape_tab,			json_escape_tab);
	print_test_json("json_escape_nl            (lenient -> pretty)", FALSE,		json_escape_nl,				json_escape_nl);
	print_test_json("json_escape_cr            (lenient -> pretty)", FALSE,		json_escape_cr,				json_escape_cr);
	print_test_json("json_escape_ff            (lenient -> pretty)", FALSE,		json_escape_ff,				json_escape_ff);
	print_test_json("json_escape_vt            (lenient -> pretty)", FALSE,		NULL,						json_escape_vt);
	print_test_json("json_escape_esc           (lenient -> pretty)", FALSE,		NULL,						json_escape_esc);
	print_test_json("json_escape_bel           (lenient -> pretty)", FALSE,		NULL,						json_escape_bel);
	print_test_json("json_escape_bs            (lenient -> pretty)", FALSE,		json_escape_bs,				json_escape_bs);
	print_test_json("json_strange_sot          (lenient -> pretty)", FALSE,		NULL,						json_strange_sot);
	print_test_json("json_strange_stx          (lenient -> pretty)", FALSE,		NULL,						json_strange_stx);
	print_test_json("json_strange_etx          (lenient -> pretty)", FALSE,		NULL,						json_strange_etx);
	print_test_json("json_strange_eot          (lenient -> pretty)", FALSE,		NULL,						json_strange_eot);
	print_test_json("json_strange_esc          (lenient -> pretty)", FALSE,		NULL,						json_strange_esc);
	print_test_json("json_strange_bs           (lenient -> pretty)", FALSE,		NULL,						json_strange_bs);
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
