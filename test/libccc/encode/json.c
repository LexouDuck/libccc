
#include "libccc/encode/json.h"

#include "test.h"
#include "test_utils.h"



// the minimal boilerplate needed to store a single vlue in TOML
#define JSON_TEST(NAME, STR) \
	t_utf8 const*	NAME		= STR"\n"; \
	t_utf8 const*	NAME##_min	= STR""; \



/*============================================================================*\
||                              Testing Variables                             ||
\*============================================================================*/

JSON_TEST(json_null	, "null")

JSON_TEST(json_bool_0_lower	, "false")
JSON_TEST(json_bool_1_lower	, "true")
JSON_TEST(json_bool_0_upper	, "FALSE")
JSON_TEST(json_bool_1_upper	, "TRUE")
JSON_TEST(json_bool_0_mixed	, "False")
JSON_TEST(json_bool_1_mixed	, "True")
JSON_TEST(json_bool_0_weird	, "FaLsE")
JSON_TEST(json_bool_1_weird	, "TrUe")



JSON_TEST(json_bigint_empty_unsigned	, "")
JSON_TEST(json_bigint_0_unsigned		, "0")
JSON_TEST(json_bigint_1_unsigned		, "1")
JSON_TEST(json_bigint_2_unsigned		, "42")
JSON_TEST(json_bigint_3_unsigned		, "777")
JSON_TEST(json_bigint_4_unsigned		, "123456789")
JSON_TEST(json_bigint_empty_negative	, "-")
JSON_TEST(json_bigint_0_negative		, "-0")
JSON_TEST(json_bigint_1_negative		, "-1")
JSON_TEST(json_bigint_2_negative		, "-42")
JSON_TEST(json_bigint_3_negative		, "-777")
JSON_TEST(json_bigint_4_negative		, "-123456789")
JSON_TEST(json_bigint_empty_positive	, "+")
JSON_TEST(json_bigint_0_positive		, "+0")
JSON_TEST(json_bigint_1_positive		, "+1")
JSON_TEST(json_bigint_2_positive		, "+42")
JSON_TEST(json_bigint_3_positive		, "+777")
JSON_TEST(json_bigint_4_positive		, "+123456789")
JSON_TEST(json_bigint_fmin_lt			, "-9007199254740991")
JSON_TEST(json_bigint_fmin_eq			, "-9007199254740992")
JSON_TEST(json_bigint_fmin_gt			, "-9007199254740993")
JSON_TEST(json_bigint_fmax_lt			,  "9007199254740991")
JSON_TEST(json_bigint_fmax_eq			,  "9007199254740992")
JSON_TEST(json_bigint_fmax_gt			,  "9007199254740993")
JSON_TEST(json_bigint_s64min_lt			, "-9223372036854775807")
JSON_TEST(json_bigint_s64min_eq			, "-9223372036854775808")
JSON_TEST(json_bigint_s64min_gt			, "-9223372036854775809") // TODO
JSON_TEST(json_bigint_s64max_lt			,  "9223372036854775806")
JSON_TEST(json_bigint_s64max_eq			,  "9223372036854775807")
JSON_TEST(json_bigint_s64max_gt			,  "9223372036854775808") // TODO



JSON_TEST(json_number_0				, "0")
JSON_TEST(json_number_1				, "1")
JSON_TEST(json_number_2				, "42")
JSON_TEST(json_number_3				, "777")
JSON_TEST(json_number_4				, "123456")
JSON_TEST(json_number_0f			, "0.0")
JSON_TEST(json_number_1f			, "1.0")
JSON_TEST(json_number_2f			, "42.0")
JSON_TEST(json_number_3f			, "777.0")
JSON_TEST(json_number_4f			, "123456.0")
JSON_TEST(json_number_0f1			, "0.0")
JSON_TEST(json_number_1f1			, "1.0")
JSON_TEST(json_number_2f1			, "42.0")
JSON_TEST(json_number_3f1			, "777.0")
JSON_TEST(json_number_4f1			, "123456.7")
JSON_TEST(json_number_0f2			, "0.00")
JSON_TEST(json_number_1f2			, "1.00")
JSON_TEST(json_number_2f2			, "42.00")
JSON_TEST(json_number_3f2			, "777.00")
JSON_TEST(json_number_4f2			, "123456.78")
JSON_TEST(json_number_0f3			, "0.000")
JSON_TEST(json_number_1f3			, "1.000")
JSON_TEST(json_number_2f3			, "42.000")
JSON_TEST(json_number_3f3			, "777.000")
JSON_TEST(json_number_4f3			, "123456.789")
JSON_TEST(json_number_fmin_lt		, "-9007199254740991.0")
JSON_TEST(json_number_fmin_eq		, "-9007199254740992.0")
JSON_TEST(json_number_fmin_gt		, "-9007199254740993.0")
JSON_TEST(json_number_fmax_lt		,  "9007199254740991.0")
JSON_TEST(json_number_fmax_eq		,  "9007199254740992.0")
JSON_TEST(json_number_fmax_gt		,  "9007199254740993.0")
JSON_TEST(json_number_emin_lt		, "-9007199254740991e0")
JSON_TEST(json_number_emin_eq		, "-9007199254740992e0")
JSON_TEST(json_number_emin_gt		, "-9007199254740993e0")
JSON_TEST(json_number_emax_lt		,  "9007199254740991e0")
JSON_TEST(json_number_emax_eq		,  "9007199254740992e0")
JSON_TEST(json_number_emax_gt		,  "9007199254740993e0")
JSON_TEST(json_number_Emin_lt		, "-9007199254740991E0")
JSON_TEST(json_number_Emin_eq		, "-9007199254740992E0")
JSON_TEST(json_number_Emin_gt		, "-9007199254740993E0")
JSON_TEST(json_number_Emax_lt		,  "9007199254740991E0")
JSON_TEST(json_number_Emax_eq		,  "9007199254740992E0")
JSON_TEST(json_number_Emax_gt		,  "9007199254740993E0")

JSON_TEST(json_number_inf_u_lower_3		,  "inf")
JSON_TEST(json_number_inf_p_lower_3		, "+inf")
JSON_TEST(json_number_inf_n_lower_3		, "-inf")
JSON_TEST(json_number_inf_u_mixed_3		,  "Inf")
JSON_TEST(json_number_inf_p_mixed_3		, "+Inf")
JSON_TEST(json_number_inf_n_mixed_3		, "-Inf")
JSON_TEST(json_number_inf_u_upper_3		,  "INF")
JSON_TEST(json_number_inf_p_upper_3		, "+INF")
JSON_TEST(json_number_inf_n_upper_3		, "-INF")
JSON_TEST(json_number_inf_u_lower_8		,  "infinity")
JSON_TEST(json_number_inf_p_lower_8		, "+infinity")
JSON_TEST(json_number_inf_n_lower_8		, "-infinity")
JSON_TEST(json_number_inf_u_mixed_8		,  "Infinity")
JSON_TEST(json_number_inf_p_mixed_8		, "+Infinity")
JSON_TEST(json_number_inf_n_mixed_8		, "-Infinity")
JSON_TEST(json_number_inf_u_upper_8		,  "INFINITY")
JSON_TEST(json_number_inf_p_upper_8		, "+INFINITY")
JSON_TEST(json_number_inf_n_upper_8		, "-INFINITY")
JSON_TEST(json_number_inf_u_lower_bad	,  "inferior")
JSON_TEST(json_number_inf_p_lower_bad	, "+inferior")
JSON_TEST(json_number_inf_n_lower_bad	, "-inferior")
JSON_TEST(json_number_inf_u_mixed_bad	,  "Inferior")
JSON_TEST(json_number_inf_p_mixed_bad	, "+Inferior")
JSON_TEST(json_number_inf_n_mixed_bad	, "-Inferior")
JSON_TEST(json_number_inf_u_upper_bad	,  "INFERIOR")
JSON_TEST(json_number_inf_p_upper_bad	, "+INFERIOR")
JSON_TEST(json_number_inf_n_upper_bad	, "-INFERIOR")
JSON_TEST(json_number_inf_u_lower_evil	,  "infinityinfinity")
JSON_TEST(json_number_inf_p_lower_evil	, "+infinityinfinity")
JSON_TEST(json_number_inf_n_lower_evil	, "-infinityinfinity")
JSON_TEST(json_number_inf_u_mixed_evil	,  "InfinityInfinity")
JSON_TEST(json_number_inf_p_mixed_evil	, "+InfinityInfinity")
JSON_TEST(json_number_inf_n_mixed_evil	, "-InfinityInfinity")
JSON_TEST(json_number_inf_u_upper_evil	,  "INFINITYINFINITY")
JSON_TEST(json_number_inf_p_upper_evil	, "+INFINITYINFINITY")
JSON_TEST(json_number_inf_n_upper_evil	, "-INFINITYINFINITY")

JSON_TEST(json_number_nan_u_lower_3		,  "nan")
JSON_TEST(json_number_nan_p_lower_3		, "+nan")
JSON_TEST(json_number_nan_n_lower_3		, "-nan")
JSON_TEST(json_number_nan_u_mixed_3		,  "NaN")
JSON_TEST(json_number_nan_p_mixed_3		, "+NaN")
JSON_TEST(json_number_nan_n_mixed_3		, "-NaN")
JSON_TEST(json_number_nan_u_upper_3		,  "NAN")
JSON_TEST(json_number_nan_p_upper_3		, "+NAN")
JSON_TEST(json_number_nan_n_upper_3		, "-NAN")
JSON_TEST(json_number_nan_u_lower_bad	,  "nancheese")
JSON_TEST(json_number_nan_p_lower_bad	, "+nancheese")
JSON_TEST(json_number_nan_n_lower_bad	, "-nancheese")
JSON_TEST(json_number_nan_u_mixed_bad	,  "NaNCheese")
JSON_TEST(json_number_nan_p_mixed_bad	, "+NaNCheese")
JSON_TEST(json_number_nan_n_mixed_bad	, "-NaNCheese")
JSON_TEST(json_number_nan_u_upper_bad	,  "NANCHEESE")
JSON_TEST(json_number_nan_p_upper_bad	, "+NANCHEESE")
JSON_TEST(json_number_nan_n_upper_bad	, "-NANCHEESE")
JSON_TEST(json_number_nan_u_lower_evil	,  "nannan")
JSON_TEST(json_number_nan_p_lower_evil	, "+nannan")
JSON_TEST(json_number_nan_n_lower_evil	, "-nannan")
JSON_TEST(json_number_nan_u_mixed_evil	,  "NaNNaN")
JSON_TEST(json_number_nan_p_mixed_evil	, "+NaNNaN")
JSON_TEST(json_number_nan_n_mixed_evil	, "-NaNNaN")
JSON_TEST(json_number_nan_u_upper_evil	,  "NANNAN")
JSON_TEST(json_number_nan_p_upper_evil	, "+NANNAN")
JSON_TEST(json_number_nan_n_upper_evil	, "-NANNAN")

JSON_TEST(json_number_inf_u_utf8_0	,  "∞")
JSON_TEST(json_number_inf_p_utf8_0	, "+∞")
JSON_TEST(json_number_inf_n_utf8_0	, "-∞")
JSON_TEST(json_number_inf_u_utf8_1	,  "\u221E")
JSON_TEST(json_number_inf_p_utf8_1	, "+\u221E")
JSON_TEST(json_number_inf_n_utf8_1	, "-\u221E")



JSON_TEST(json_string_empty		, "\"\"")
JSON_TEST(json_string			, "\"Hello World!\"")
JSON_TEST(json_string_cc_c0		, "\"␡␁␂␃␄␅␆␇␈␉␊␋␌␍␎␏␐␑␒␓␔␕␖␗␘␙␚␛␜␝␞␟\"")
JSON_TEST(json_string_cc_c1		, "\"\"")
JSON_TEST(json_string_utf8_fr	, "\"Être à même de ça, d'air sûr — manger du maïs à l'œil… D'où la paix sur l'île de son âme…\"")
JSON_TEST(json_string_utf8_ru	, "\"Яцк Ничолсон\"")
JSON_TEST(json_string_utf8_jp	, "\"お前はもう死んでいる - 愛 - 私は実体の小さな学生です\"")
JSON_TEST(json_string_utf8_ho	, "\"�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻\"")

JSON_TEST(json_escape_sq1	, "\".\\\'.\"")	JSON_TEST(json_escstr_sq1	, "\".'.\"")
JSON_TEST(json_escape_sq2	, "\".\\\".\"")
JSON_TEST(json_escape_slb	, "\".\\\\.\"")
JSON_TEST(json_escape_slf	, "\".\\/.\"")	JSON_TEST(json_escstr_slf	, "\"./.\"")
JSON_TEST(json_escape_spc	, "\".\\ .\"")	JSON_TEST(json_escstr_spc	, "\".\\\\ .\"") // TODO inspect this test further
JSON_TEST(json_escape_tab	, "\".\\t.\"")
JSON_TEST(json_escape_nl	, "\".\\n.\"")
JSON_TEST(json_escape_cr	, "\".\\r.\"")
JSON_TEST(json_escape_ff	, "\".\\f.\"")
JSON_TEST(json_escape_vt	, "\".\\v.\"")	JSON_TEST(json_escstr_vt	, "\".\\u000B.\"")
JSON_TEST(json_escape_esc	, "\".\\e.\"")	JSON_TEST(json_escstr_esc	, "\".\\u001B.\"")
JSON_TEST(json_escape_bel	, "\".\\a.\"")	JSON_TEST(json_escstr_bel	, "\".\\u0007.\"")
JSON_TEST(json_escape_bs	, "\".\\b.\"")

JSON_TEST(json_escape_utf8_ru_u	, "\"\\u042F\\u0446\\u043A \\u041D\\u0438\\u0447\\u043E\\u043B\\u0441\\u043E\\u043D\"")
JSON_TEST(json_escape_utf8_ru_U	, "\"\\U0000042F\\U00000446\\U0000043A \\U0000041D\\U00000438\\U00000447\\U0000043E\\U0000043B\\U00000441\\U0000043E\\U0000043D\"")
JSON_TEST(json_escape_utf8_ru_x	, "\"\\xD0\\xAF\\xD1\\x86\\xD0\\xBA \\xD0\\x9D\\xD0\\xB8\\xD1\\x87\\xD0\\xBE\\xD0\\xBB\\xD1\\x81\\xD0\\xBE\\xD0\\xBD\"")



t_utf8 const*	json_array_empty_min	= "[]";
t_utf8 const*	json_array_empty		= "[]\n";
t_utf8 const*	json_array_min			= "[false,true,null]";
t_utf8 const*	json_array				= "\
[\
\n	false,\
\n	true,\
\n	null\
\n]\
\n";
t_utf8 const*	json_array_nested_min	= "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\":1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";
t_utf8 const*	json_array_nested		= "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{\"swag\": 1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]\n";



t_utf8 const*	json_object_empty_min	= "{}";
t_utf8 const*	json_object_empty		= "{}\n";
t_utf8 const*	json_object_min			= "{\"a\":false,\"b\":true,\"c\":null}";
t_utf8 const*	json_object				= "\
{\
\n	\"a\": false,\
\n	\"b\": true,\
\n	\"c\": null\
\n}\
\n";
t_utf8 const*	json_object_nested_min	= "{\"a\":{\"b\":{\"c\":{\"d\":{\"e\":{\"f\":{\"g\":{\"h\":{\"i\":{\"j\":{\"k\":{\"l\":{\"m\":{\"n\":{\"o\":{\"p\":{\"q\":{\"r\":{\"s\":{\"t\":{\"u\":{\"v\":{\"w\":{\"x\":{\"y\":{\"z\":\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
t_utf8 const*	json_object_nested		= "{\"a\": {\"b\": {\"c\": {\"d\": {\"e\": {\"f\": {\"g\": {\"h\": {\"i\": {\"j\": {\"k\": {\"l\": {\"m\": {\"n\": {\"o\": {\"p\": {\"q\": {\"r\": {\"s\": {\"t\": {\"u\": {\"v\": {\"w\": {\"x\": {\"y\": {\"z\": \"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}\n";

t_utf8 const*	json_object_string_min =
"{"
	"\"type\":11,"
	"\"value\":"
	"\"{"
		"\\\"Label\\\":\\\"NAME\\\","
		"\\\"Attributes\\\":"
		"{"
			"\\\"PATTERN_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"ENTITY_PATTERN\\\"}]}],"
			"\\\"DESCRIPTION_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"DESC\\\"}]}],"
			"\\\"CHARACTERISTIC_ATTRIBUTE\\\":[],"
			"\\\"TEMPLATE_ATTRIBUTE\\\":[{}]"
		"}"
	"}\""
"}";
t_utf8 const*	json_object_string =
"{\
\n	\"type\": 11,\
\n	\"value\": \"{\\\"Label\\\":\\\"NAME\\\",\\\"Attributes\\\":{\\\"PATTERN_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"ENTITY_PATTERN\\\"}]}],\\\"DESCRIPTION_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"DESC\\\"}]}],\\\"CHARACTERISTIC_ATTRIBUTE\\\":[],\\\"TEMPLATE_ATTRIBUTE\\\":[{}]}}\"\
\n}\
\n";



// TODO string literals ? (triple-quote """a""" or at @"a")

// TODO key name conflict tests (+ case-insensitive)



t_utf8 const*	json_helloworld_min	= "{\"hello\":\"world\"}";
t_utf8 const*	json_helloworld		= "{\"hello\": \"world\"}\n";

t_utf8 const*	json_whitespace		= "  {  \"hello\"  :  \"world\"  }  ";
t_utf8 const*	json_whitespace_tab	= "\t{\t\"hello\"\t:\t\"world\"\t}\t";
t_utf8 const*	json_whitespace_nl	= "\n{\n\"hello\"\n:\n\"world\"\n}\t";
t_utf8 const*	json_whitespace_cr	= "\r{\r\"hello\"\r:\r\"world\"\r}\r";
t_utf8 const*	json_whitespace_ff	= "\f{\f\"hello\"\f:\f\"world\"\f}\f";
t_utf8 const*	json_whitespace_vt	= "\v{\v\"hello\"\v:\v\"world\"\v}\v";
t_utf8 const*	json_whitespace_all	= "\t\f\r\n{\t\f\r\n\"hello\":\t\f\r\n\"world\"\t\f\r\n}\t\f\r\n";

t_utf8 const*	json_strange_sot	= "\1{\"hello\":\1\"world\"\1}\n";
t_utf8 const*	json_strange_stx	= "\2{\"hello\":\2\"world\"\2}\n";
t_utf8 const*	json_strange_etx	= "\3{\"hello\":\3\"world\"\3}\n";
t_utf8 const*	json_strange_eot	= "\4{\"hello\":\4\"world\"\4}\n";
t_utf8 const*	json_strange_esc	= "\x1B{\"hello\":\x1B\"world\"\x1B}\n";
t_utf8 const*	json_strange_bs		= "\b{\"hello\":\b\"world\"\b}\n";



t_utf8 const*	json_simple_min =
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
t_utf8 const*	json_simple = "\
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
\n";



t_utf8 const*	json_commas_min =
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
t_utf8 const*	json_commas = "\
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
\n";



t_utf8 const*	json_newline = "\n\n\
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



t_utf8 const*	json_config_min =
"{"
	"\"General Settings\":"
	"{"
		"\"background_pause\":false,"
		"\"background_input\":true"
	"},"
	"\"Video Settings\":"
	"{"
		"\"window_position\":"
		"{"
			"\"x\":-793,"
			"\"y\":75"
		"},"
		"\"window_size\":"
		"{"
			"\"x\":768,"
			"\"y\":720"
		"},"
		"\"window_maximized\":false,"
		"\"fullscreen\":false,"
		"\"keep_aspect_ratio\":true,"
		"\"vertical_sync\":false"
	"},"
	"\"Audio Settings\":"
	"{"
		"\"volume_master\":100,"
		"\"volume_music\":100,"
		"\"volume_sfx\":100,"
		"\"mute\":false"
	"},"
	"\"Input Mapping\":"
	"{"
		"\"joypad_up\":"    "{\"device_guid\":\"0003000000C82D000000600000000000\",\"device_id\":0,\"event\":\"jhat\",\"which\":0,\"value\":1},"
		"\"joypad_down\":"  "{\"device_guid\":\"00030000005E0400008E020000000078\",\"device_id\":0,\"event\":\"jhat\",\"which\":0,\"value\":4},"
		"\"joypad_left\":"  "{\"device_guid\":\"000300000025090000E8030000000000\",\"device_id\":0,\"event\":\"jhat\",\"which\":0,\"value\":8},"
		"\"joypad_right\":" "{\"device_guid\":\"00030000006F0E0000A6020000000078\",\"device_id\":0,\"event\":\"jhat\",\"which\":0,\"value\":2},"
		"\"joypad_A\":"     "{\"device_guid\":\"0003000000C82D000000600000000000\",\"device_id\":0,\"event\":\"jbutton\",\"value\":0},"
		"\"joypad_B\":"     "{\"device_guid\":\"00000000000000000000000000000000\",\"device_id\":0,\"event\":\"jbutton\",\"value\":1}"
	"}"
"}";
t_utf8 const*	json_config = "\
{\
\n	\"General Settings\": \
\n	{\
\n		\"background_pause\": false,\
\n		\"background_input\": true\
\n	},\
\n	\"Video Settings\": \
\n	{\
\n		\"window_position\": \
\n		{\
\n			\"x\": -793,\
\n			\"y\": 75\
\n		},\
\n		\"window_size\": \
\n		{\
\n			\"x\": 768,\
\n			\"y\": 720\
\n		},\
\n		\"window_maximized\": false,\
\n		\"fullscreen\": false,\
\n		\"keep_aspect_ratio\": true,\
\n		\"vertical_sync\": false\
\n	},\
\n	\"Audio Settings\": \
\n	{\
\n		\"volume_master\": 100,\
\n		\"volume_music\": 100,\
\n		\"volume_sfx\": 100,\
\n		\"mute\": false\
\n	},\
\n	\"Input Mapping\": \
\n	{\
\n		\"joypad_up\":"    " \n\t\t{\n\t\t\t\"device_guid\": \"0003000000C82D000000600000000000\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jhat\",\n\t\t\t\"which\": 0,\n\t\t\t\"value\": 1\n\t\t},\
\n		\"joypad_down\":"  " \n\t\t{\n\t\t\t\"device_guid\": \"00030000005E0400008E020000000078\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jhat\",\n\t\t\t\"which\": 0,\n\t\t\t\"value\": 4\n\t\t},\
\n		\"joypad_left\":"  " \n\t\t{\n\t\t\t\"device_guid\": \"000300000025090000E8030000000000\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jhat\",\n\t\t\t\"which\": 0,\n\t\t\t\"value\": 8\n\t\t},\
\n		\"joypad_right\":" " \n\t\t{\n\t\t\t\"device_guid\": \"00030000006F0E0000A6020000000078\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jhat\",\n\t\t\t\"which\": 0,\n\t\t\t\"value\": 2\n\t\t},\
\n		\"joypad_A\":"     " \n\t\t{\n\t\t\t\"device_guid\": \"0003000000C82D000000600000000000\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jbutton\",\n\t\t\t\"value\": 0\n\t\t},\
\n		\"joypad_B\":"     " \n\t\t{\n\t\t\t\"device_guid\": \"00000000000000000000000000000000\",\n\t\t\t\"device_id\": 0,\n\t\t\t\"event\": \"jbutton\",\n\t\t\t\"value\": 1\n\t\t}\
\n	}\
\n}\
\n";

t_utf8 const*	json_complex_min =
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
			"{\"Values\":[{\"TEXT\":\"Caleb\"}],\"Properties\":[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]},"
			"{\"Values\":[{\"TEXT\":\"Honey\"}]},"
			"{\"Values\":[{\"TEXT\":\"Lorraine\"}]},"
			"{\"Values\":[{\"TEXT\":\"Raymond\"}],\"Properties\":[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]]}"
		"]"
	"},"
	"\"Properties\":[[\"known for\",\"most popular role\",\"The Shining\"],[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"],[\"fan of\",\"\",\"Bob Dylan\"],[\"also known for\",\"best performance\",\"Chinatown\"]],"
	"\"Values\":[\"actor\",\"player\",\"filmmaker\"]"
"}";
t_utf8 const*	json_complex = "\
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
\n}\
\n";



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#if !(defined(c_jsonparse) && defined(c_jsonprint))
void test_json(void)	{}
#else

#define DEFINETEST_JSON(STRICT, NSTRICT, MINIFY, _MIN) \
static t_utf8*	c_json_##STRICT##_##MINIFY(t_utf8* json) \
{ \
	s_json* tmp = JSON_FromString_##STRICT(json); \
	t_utf8* result = JSON_ToString_##MINIFY(tmp); \
	if (tmp != NULL)	JSON_Delete(tmp); \
	return (result); \
} \
void	print_test_json_##STRICT##_##MINIFY(char const* test_name, t_testflags flags,\
		char const* expecting, \
		char const* str) \
{ \
	TEST_INIT(str) \
	TEST_PERFORM(	json_##STRICT##_##MINIFY, (t_utf8*)str) \
	TEST_PRINT(str,	json_##STRICT##_##MINIFY, "str=\"%s\"", str) \
	TEST_FREE() \
} \
void	test_json_##STRICT##_##MINIFY(void) \
{ \
/*	| TEST FUNCTION                    | TEST NAME                                          | TESTFLAGS  | EXPECTING                              | TEST ARGS					*/ \
	print_test_json_##STRICT##_##MINIFY("null pointer              ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									NULL); \
	print_test_json_##STRICT##_##MINIFY("empty string              ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									""); \
	print_test_json_##STRICT##_##MINIFY("json_null                 ("#STRICT" -> "#MINIFY")", FALSE,		json_null##_MIN,						json_null); \
	print_test_json_##STRICT##_##MINIFY("json_bool_0_lower         ("#STRICT" -> "#MINIFY")", FALSE,		json_bool_0_lower##_MIN,				json_bool_0_lower); \
	print_test_json_##STRICT##_##MINIFY("json_bool_1_lower         ("#STRICT" -> "#MINIFY")", FALSE,		json_bool_1_lower##_MIN,				json_bool_1_lower); \
	print_test_json_##STRICT##_##MINIFY("json_bool_0_upper         ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bool_0_lower##_MIN:NULL,			json_bool_0_upper); \
	print_test_json_##STRICT##_##MINIFY("json_bool_1_upper         ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bool_1_lower##_MIN:NULL,			json_bool_1_upper); \
	print_test_json_##STRICT##_##MINIFY("json_bool_0_mixed         ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bool_0_lower##_MIN:NULL,			json_bool_0_mixed); \
	print_test_json_##STRICT##_##MINIFY("json_bool_1_mixed         ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bool_1_lower##_MIN:NULL,			json_bool_1_mixed); \
	print_test_json_##STRICT##_##MINIFY("json_bool_0_weird         ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_bool_0_weird); \
	print_test_json_##STRICT##_##MINIFY("json_bool_1_weird         ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_bool_1_weird); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_empty_unsigned("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_bigint_empty_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_0_unsigned    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_0_unsigned##_MIN,			json_bigint_0_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_1_unsigned    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_1_unsigned##_MIN,			json_bigint_1_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_2_unsigned    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_2_unsigned##_MIN,			json_bigint_2_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_3_unsigned    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_3_unsigned##_MIN,			json_bigint_3_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_4_unsigned    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_4_unsigned##_MIN,			json_bigint_4_unsigned); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_empty_negative("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_bigint_empty_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_0_negative    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_0_unsigned##_MIN,			json_bigint_0_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_1_negative    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_1_negative##_MIN,			json_bigint_1_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_2_negative    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_2_negative##_MIN,			json_bigint_2_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_3_negative    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_3_negative##_MIN,			json_bigint_3_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_4_negative    ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_4_negative##_MIN,			json_bigint_4_negative); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_empty_positive("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_bigint_empty_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_0_positive    ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bigint_0_unsigned##_MIN:NULL,		json_bigint_0_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_1_positive    ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bigint_1_unsigned##_MIN:NULL,		json_bigint_1_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_2_positive    ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bigint_2_unsigned##_MIN:NULL,		json_bigint_2_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_3_positive    ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bigint_3_unsigned##_MIN:NULL,		json_bigint_3_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_4_positive    ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_bigint_4_unsigned##_MIN:NULL,		json_bigint_4_positive); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmin_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmin_lt##_MIN,				json_bigint_fmin_lt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmin_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmin_eq##_MIN,				json_bigint_fmin_eq); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmin_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmin_gt##_MIN,				json_bigint_fmin_gt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmax_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmax_lt##_MIN,				json_bigint_fmax_lt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmax_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmax_eq##_MIN,				json_bigint_fmax_eq); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_fmax_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_fmax_gt##_MIN,				json_bigint_fmax_gt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64min_lt     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64min_lt##_MIN,			json_bigint_s64min_lt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64min_eq     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64min_eq##_MIN,			json_bigint_s64min_eq); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64min_gt     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64max_eq##_MIN,			json_bigint_s64min_gt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64max_lt     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64max_lt##_MIN,			json_bigint_s64max_lt); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64max_eq     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64max_eq##_MIN,			json_bigint_s64max_eq); \
	print_test_json_##STRICT##_##MINIFY("json_bigint_s64max_gt     ("#STRICT" -> "#MINIFY")", FALSE,		json_bigint_s64min_eq##_MIN,			json_bigint_s64max_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_0             ("#STRICT" -> "#MINIFY")", FALSE,		json_number_0##_MIN,					json_number_0); \
	print_test_json_##STRICT##_##MINIFY("json_number_1             ("#STRICT" -> "#MINIFY")", FALSE,		json_number_1##_MIN,					json_number_1); \
	print_test_json_##STRICT##_##MINIFY("json_number_2             ("#STRICT" -> "#MINIFY")", FALSE,		json_number_2##_MIN,					json_number_2); \
	print_test_json_##STRICT##_##MINIFY("json_number_3             ("#STRICT" -> "#MINIFY")", FALSE,		json_number_3##_MIN,					json_number_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_4             ("#STRICT" -> "#MINIFY")", FALSE,		json_number_4##_MIN,					json_number_4); \
	print_test_json_##STRICT##_##MINIFY("json_number_0f            ("#STRICT" -> "#MINIFY")", FALSE,		json_number_0f##_MIN,					json_number_0f); \
	print_test_json_##STRICT##_##MINIFY("json_number_1f            ("#STRICT" -> "#MINIFY")", FALSE,		json_number_1f##_MIN,					json_number_1f); \
	print_test_json_##STRICT##_##MINIFY("json_number_2f            ("#STRICT" -> "#MINIFY")", FALSE,		json_number_2f##_MIN,					json_number_2f); \
	print_test_json_##STRICT##_##MINIFY("json_number_3f            ("#STRICT" -> "#MINIFY")", FALSE,		json_number_3f##_MIN,					json_number_3f); \
	print_test_json_##STRICT##_##MINIFY("json_number_4f            ("#STRICT" -> "#MINIFY")", FALSE,		json_number_4f##_MIN,					json_number_4f); \
	print_test_json_##STRICT##_##MINIFY("json_number_0f1           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_0f##_MIN,					json_number_0f1); \
	print_test_json_##STRICT##_##MINIFY("json_number_1f1           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_1f##_MIN,					json_number_1f1); \
	print_test_json_##STRICT##_##MINIFY("json_number_2f1           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_2f##_MIN,					json_number_2f1); \
	print_test_json_##STRICT##_##MINIFY("json_number_3f1           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_3f##_MIN,					json_number_3f1); \
	print_test_json_##STRICT##_##MINIFY("json_number_4f1           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_4f1##_MIN,					json_number_4f1); \
	print_test_json_##STRICT##_##MINIFY("json_number_0f2           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_0f##_MIN,					json_number_0f2); \
	print_test_json_##STRICT##_##MINIFY("json_number_1f2           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_1f##_MIN,					json_number_1f2); \
	print_test_json_##STRICT##_##MINIFY("json_number_2f2           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_2f##_MIN,					json_number_2f2); \
	print_test_json_##STRICT##_##MINIFY("json_number_3f2           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_3f##_MIN,					json_number_3f2); \
	print_test_json_##STRICT##_##MINIFY("json_number_4f2           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_4f2##_MIN,					json_number_4f2); \
	print_test_json_##STRICT##_##MINIFY("json_number_0f3           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_0f##_MIN,					json_number_0f3); \
	print_test_json_##STRICT##_##MINIFY("json_number_1f3           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_1f##_MIN,					json_number_1f3); \
	print_test_json_##STRICT##_##MINIFY("json_number_2f3           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_2f##_MIN,					json_number_2f3); \
	print_test_json_##STRICT##_##MINIFY("json_number_3f3           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_3f##_MIN,					json_number_3f3); \
	print_test_json_##STRICT##_##MINIFY("json_number_4f3           ("#STRICT" -> "#MINIFY")", FALSE,		json_number_4f3##_MIN,					json_number_4f3); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmin_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_lt##_MIN,				json_number_fmin_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmin_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_fmin_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmin_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_fmin_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmax_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_lt##_MIN,				json_number_fmax_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmax_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_fmax_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_fmax_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_fmax_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_emin_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_lt##_MIN,				json_number_emin_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_emin_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_emin_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_emin_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_emin_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_emax_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_lt##_MIN,				json_number_emax_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_emax_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_emax_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_emax_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_emax_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emin_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_lt##_MIN,				json_number_Emin_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emin_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_Emin_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emin_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmin_eq##_MIN,				json_number_Emin_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emax_lt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_lt##_MIN,				json_number_Emax_lt); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emax_eq       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_Emax_eq); \
	print_test_json_##STRICT##_##MINIFY("json_number_Emax_gt       ("#STRICT" -> "#MINIFY")", FALSE,		json_number_fmax_eq##_MIN,				json_number_Emax_gt); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_u_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_p_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_n_lower_3##_MIN:NULL,	json_number_inf_n_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_u_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_p_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_n_lower_3##_MIN:NULL,	json_number_inf_n_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_u_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_p_lower_3##_MIN:NULL,	json_number_inf_p_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_inf_n_lower_3##_MIN:NULL,	json_number_inf_n_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_lower_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_lower_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_lower_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_lower_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_lower_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_lower_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_mixed_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_mixed_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_mixed_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_mixed_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_mixed_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_mixed_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_upper_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_upper_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_upper_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_upper_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_upper_8 ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_upper_8); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_utf8_0); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_utf8_0); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_utf8_0); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_u_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_u_utf8_1); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_p_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_p_utf8_1); \
	print_test_json_##STRICT##_##MINIFY("json_number_inf_n_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_inf_n_utf8_1); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_u_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_p_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_lower_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_n_lower_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_u_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_p_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_mixed_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_n_mixed_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_u_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_p_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_upper_3 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_number_nan_u_lower_3##_MIN:NULL,	json_number_nan_n_upper_3); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_lower_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_lower_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_mixed_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_mixed_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_upper_bad  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_upper_bad); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_lower_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_lower_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_mixed_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_mixed_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_u_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_u_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_p_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_p_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_number_nan_n_upper_evil ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_number_nan_n_upper_evil); \
	print_test_json_##STRICT##_##MINIFY("json_string_empty         ("#STRICT" -> "#MINIFY")", FALSE,		json_string_empty##_MIN,				json_string_empty); \
	print_test_json_##STRICT##_##MINIFY("json_string               ("#STRICT" -> "#MINIFY")", FALSE,		json_string##_MIN,						json_string); \
	print_test_json_##STRICT##_##MINIFY("json_string_cc_c0         ("#STRICT" -> "#MINIFY")", FALSE,		json_string_cc_c0##_MIN,				json_string_cc_c0); \
	print_test_json_##STRICT##_##MINIFY("json_string_cc_c1         ("#STRICT" -> "#MINIFY")", FALSE,		json_string_cc_c1##_MIN,				json_string_cc_c1); \
	print_test_json_##STRICT##_##MINIFY("json_string_utf8_fr       ("#STRICT" -> "#MINIFY")", FALSE,		json_string_utf8_fr##_MIN,				json_string_utf8_fr); \
	print_test_json_##STRICT##_##MINIFY("json_string_utf8_ru       ("#STRICT" -> "#MINIFY")", FALSE,		json_string_utf8_ru##_MIN,				json_string_utf8_ru); \
	print_test_json_##STRICT##_##MINIFY("json_string_utf8_jp       ("#STRICT" -> "#MINIFY")", FALSE,		json_string_utf8_jp##_MIN,				json_string_utf8_jp); \
	print_test_json_##STRICT##_##MINIFY("json_string_utf8_ho       ("#STRICT" -> "#MINIFY")", FALSE,		json_string_utf8_ho##_MIN,				json_string_utf8_ho); \
	print_test_json_##STRICT##_##MINIFY("json_array_empty          ("#STRICT" -> "#MINIFY")", FALSE,		json_array_empty##_MIN,					json_array_empty); \
	print_test_json_##STRICT##_##MINIFY("json_array                ("#STRICT" -> "#MINIFY")", FALSE,		json_array##_MIN,						json_array); \
	print_test_json_##STRICT##_##MINIFY("json_array_min            ("#STRICT" -> "#MINIFY")", FALSE,		json_array##_MIN,						json_array_min); \
	print_test_json_##STRICT##_##MINIFY("json_array_nested         ("#STRICT" -> "#MINIFY")", FALSE,		json_array_nested##_MIN,				json_array_nested); \
	print_test_json_##STRICT##_##MINIFY("json_array_nested_min     ("#STRICT" -> "#MINIFY")", FALSE,		json_array_nested##_MIN,				json_array_nested_min); \
	print_test_json_##STRICT##_##MINIFY("json_object_empty         ("#STRICT" -> "#MINIFY")", FALSE,		json_object_empty##_MIN,				json_object_empty); \
	print_test_json_##STRICT##_##MINIFY("json_object               ("#STRICT" -> "#MINIFY")", FALSE,		json_object##_MIN,						json_object); \
	print_test_json_##STRICT##_##MINIFY("json_object_min           ("#STRICT" -> "#MINIFY")", FALSE,		json_object##_MIN,						json_object_min); \
	print_test_json_##STRICT##_##MINIFY("json_object_nested        ("#STRICT" -> "#MINIFY")", FALSE,		json_object_nested##_MIN,				json_object_nested); \
	print_test_json_##STRICT##_##MINIFY("json_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		json_object_nested##_MIN,				json_object_nested_min); \
	print_test_json_##STRICT##_##MINIFY("json_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		json_object_string##_MIN,				json_object_string); \
	print_test_json_##STRICT##_##MINIFY("json_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		json_object_string##_MIN,				json_object_string_min); \
	print_test_json_##STRICT##_##MINIFY("json_config               ("#STRICT" -> "#MINIFY")", FALSE,		json_config##_MIN,						json_config); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace           ("#STRICT" -> "#MINIFY")", FALSE,		json_helloworld##_MIN,					json_whitespace); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_tab       ("#STRICT" -> "#MINIFY")", FALSE,		json_helloworld##_MIN,					json_whitespace_tab); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_nl        ("#STRICT" -> "#MINIFY")", FALSE,		json_helloworld##_MIN,					json_whitespace_nl); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_cr        ("#STRICT" -> "#MINIFY")", FALSE,		json_helloworld##_MIN,					json_whitespace_cr); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_ff        ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_helloworld##_MIN:NULL,				json_whitespace_ff); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_vt        ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_helloworld##_MIN:NULL,				json_whitespace_vt); \
	print_test_json_##STRICT##_##MINIFY("json_whitespace_all       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_helloworld##_MIN:NULL,				json_whitespace_all); \
	print_test_json_##STRICT##_##MINIFY("json_simple               ("#STRICT" -> "#MINIFY")", FALSE,		json_simple##_MIN,						json_simple); \
	print_test_json_##STRICT##_##MINIFY("json_simple_min           ("#STRICT" -> "#MINIFY")", FALSE,		json_simple##_MIN,						json_simple_min); \
	print_test_json_##STRICT##_##MINIFY("json_commas               ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_simple##_MIN:NULL,					json_commas); \
	print_test_json_##STRICT##_##MINIFY("json_commas_min           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_simple##_MIN:NULL,					json_commas_min); \
	print_test_json_##STRICT##_##MINIFY("json_newline              ("#STRICT" -> "#MINIFY")", FALSE,		json_simple##_MIN,						json_newline); \
	print_test_json_##STRICT##_##MINIFY("json_complex              ("#STRICT" -> "#MINIFY")", FALSE,		json_complex##_MIN,						json_complex); \
	print_test_json_##STRICT##_##MINIFY("json_complex_min          ("#STRICT" -> "#MINIFY")", FALSE,		json_complex##_MIN,						json_complex_min); \
	print_test_json_##STRICT##_##MINIFY("json_escape_sq1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_escstr_sq1##_MIN:NULL,				json_escape_sq1); \
	print_test_json_##STRICT##_##MINIFY("json_escape_sq2           ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_sq2##_MIN,					json_escape_sq2); \
	print_test_json_##STRICT##_##MINIFY("json_escape_slb           ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_slb##_MIN,					json_escape_slb); \
	print_test_json_##STRICT##_##MINIFY("json_escape_slf           ("#STRICT" -> "#MINIFY")", FALSE,		json_escstr_slf##_MIN,					json_escape_slf); \
	print_test_json_##STRICT##_##MINIFY("json_escape_spc           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_escstr_spc##_MIN:NULL,				json_escape_spc); \
	print_test_json_##STRICT##_##MINIFY("json_escape_tab           ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_tab##_MIN,					json_escape_tab); \
	print_test_json_##STRICT##_##MINIFY("json_escape_nl            ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_nl##_MIN,					json_escape_nl); \
	print_test_json_##STRICT##_##MINIFY("json_escape_cr            ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_cr##_MIN,					json_escape_cr); \
	print_test_json_##STRICT##_##MINIFY("json_escape_ff            ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_ff##_MIN,					json_escape_ff); \
	print_test_json_##STRICT##_##MINIFY("json_escape_vt            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_escstr_vt##_MIN:NULL,				json_escape_vt); \
	print_test_json_##STRICT##_##MINIFY("json_escape_esc           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_escstr_esc##_MIN:NULL,				json_escape_esc); \
	print_test_json_##STRICT##_##MINIFY("json_escape_bel           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_escstr_bel##_MIN:NULL,				json_escape_bel); \
	print_test_json_##STRICT##_##MINIFY("json_escape_bs            ("#STRICT" -> "#MINIFY")", FALSE,		json_escape_bs##_MIN,					json_escape_bs); \
	print_test_json_##STRICT##_##MINIFY("json_escape_utf8_ru_x     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_string_utf8_ru##_MIN:NULL,			json_escape_utf8_ru_x); \
	print_test_json_##STRICT##_##MINIFY("json_escape_utf8_ru_u     ("#STRICT" -> "#MINIFY")", FALSE,		json_string_utf8_ru##_MIN,				json_escape_utf8_ru_u); \
	print_test_json_##STRICT##_##MINIFY("json_escape_utf8_ru_U     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?json_string_utf8_ru##_MIN:NULL,			json_escape_utf8_ru_U); \
	print_test_json_##STRICT##_##MINIFY("json_strange_sot          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_sot); \
	print_test_json_##STRICT##_##MINIFY("json_strange_stx          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_stx); \
	print_test_json_##STRICT##_##MINIFY("json_strange_etx          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_etx); \
	print_test_json_##STRICT##_##MINIFY("json_strange_eot          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_eot); \
	print_test_json_##STRICT##_##MINIFY("json_strange_esc          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_esc); \
	print_test_json_##STRICT##_##MINIFY("json_strange_bs           ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									json_strange_bs); \
}
#endif

DEFINETEST_JSON(Lenient, TRUE,	Pretty,)
DEFINETEST_JSON(Lenient, TRUE,	Minify, _min)
DEFINETEST_JSON(Strict, FALSE,	Pretty,)
DEFINETEST_JSON(Strict, FALSE,	Minify, _min)

// TODO test othe functions than just Parse/Print



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_encode_json(void)
{
	print_suite_title("libccc/encode/json");

	print_nonstd();

	test_json_Lenient_Pretty();
	test_json_Lenient_Minify();
	test_json_Strict_Pretty();
	test_json_Strict_Minify();

	return (OK);
}
