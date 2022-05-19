
#include "libccc/encode/toml.h"

#include "test.h"



// the minimal boilerplate needed to store a single vlue in TOML
#define TOML_TEST(NAME, STR) \
	t_utf8 const*	NAME		= "\n\"\" = "STR"\n";	\
	t_utf8 const*	NAME##_min	= "\"\"="STR"";			\




/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

TOML_TEST(toml_null	, "null")

TOML_TEST(toml_bool_0_lower	, "false")
TOML_TEST(toml_bool_1_lower	, "true")
TOML_TEST(toml_bool_0_upper	, "FALSE")
TOML_TEST(toml_bool_1_upper	, "TRUE")
TOML_TEST(toml_bool_0_mixed	, "False")
TOML_TEST(toml_bool_1_mixed	, "True")
TOML_TEST(toml_bool_0_weird	, "FaLsE")
TOML_TEST(toml_bool_1_weird	, "TrUe")



TOML_TEST(toml_integer_empty_unsigned	, "")
TOML_TEST(toml_integer_0_unsigned		, "0")
TOML_TEST(toml_integer_1_unsigned		, "1")
TOML_TEST(toml_integer_2_unsigned		, "42")
TOML_TEST(toml_integer_3_unsigned		, "777")
TOML_TEST(toml_integer_4_unsigned		, "123456789")
TOML_TEST(toml_integer_empty_negative	, "-")
TOML_TEST(toml_integer_0_negative		, "-0")
TOML_TEST(toml_integer_1_negative		, "-1")
TOML_TEST(toml_integer_2_negative		, "-42")
TOML_TEST(toml_integer_3_negative		, "-777")
TOML_TEST(toml_integer_4_negative		, "-123456789")
TOML_TEST(toml_integer_empty_positive	, "+")
TOML_TEST(toml_integer_0_positive		, "+0")
TOML_TEST(toml_integer_1_positive		, "+1")
TOML_TEST(toml_integer_2_positive		, "+42")
TOML_TEST(toml_integer_3_positive		, "+777")
TOML_TEST(toml_integer_4_positive		, "+123456789")
TOML_TEST(toml_integer_f64min_lt		, "-9007199254740991")
TOML_TEST(toml_integer_f64min_eq		, "-9007199254740992")
TOML_TEST(toml_integer_f64min_gt		, "-9007199254740993")
TOML_TEST(toml_integer_f64max_lt		,  "9007199254740991")
TOML_TEST(toml_integer_f64max_eq		,  "9007199254740992")
TOML_TEST(toml_integer_f64max_gt		,  "9007199254740993")
TOML_TEST(toml_integer_s64min_lt		, "-9223372036854775807")
TOML_TEST(toml_integer_s64min_eq		, "-9223372036854775808")
TOML_TEST(toml_integer_s64min_gt		, "-9223372036854775809")
TOML_TEST(toml_integer_s64max_lt		,  "9223372036854775806")
TOML_TEST(toml_integer_s64max_eq		,  "9223372036854775807")
TOML_TEST(toml_integer_s64max_gt		,  "9223372036854775808")



TOML_TEST(toml_floatpt_0				, "0e0")
TOML_TEST(toml_floatpt_1				, "1e0")
TOML_TEST(toml_floatpt_2				, "42e0")
TOML_TEST(toml_floatpt_3				, "777e0")
TOML_TEST(toml_floatpt_4				, "123456.0")
TOML_TEST(toml_floatpt_0f				, "0.")
TOML_TEST(toml_floatpt_1f				, "1.")
TOML_TEST(toml_floatpt_2f				, "42.")
TOML_TEST(toml_floatpt_3f				, "777.")
TOML_TEST(toml_floatpt_4f				, "123456.")
TOML_TEST(toml_floatpt_0f1				, "0.0")
TOML_TEST(toml_floatpt_1f1				, "1.0")
TOML_TEST(toml_floatpt_2f1				, "42.0")
TOML_TEST(toml_floatpt_3f1				, "777.0")
TOML_TEST(toml_floatpt_4f1				, "123456.7")
TOML_TEST(toml_floatpt_0f2				, "0.00")
TOML_TEST(toml_floatpt_1f2				, "1.00")
TOML_TEST(toml_floatpt_2f2				, "42.00")
TOML_TEST(toml_floatpt_3f2				, "777.00")
TOML_TEST(toml_floatpt_4f2				, "123456.78")
TOML_TEST(toml_floatpt_0f3				, "0.000")
TOML_TEST(toml_floatpt_1f3				, "1.000")
TOML_TEST(toml_floatpt_2f3				, "42.000")
TOML_TEST(toml_floatpt_3f3				, "777.000")
TOML_TEST(toml_floatpt_4f3				, "123456.789")
TOML_TEST(toml_floatpt_f64min_lt		, "-9007199254740991.0")
TOML_TEST(toml_floatpt_f64min_eq		, "-9007199254740992.0")
TOML_TEST(toml_floatpt_f64min_gt		, "-9007199254740993.0")
TOML_TEST(toml_floatpt_f64max_lt		,  "9007199254740991.0")
TOML_TEST(toml_floatpt_f64max_eq		,  "9007199254740992.0")
TOML_TEST(toml_floatpt_f64max_gt		,  "9007199254740993.0")
TOML_TEST(toml_floatpt_inf_u_lower_0	,  "inf")
TOML_TEST(toml_floatpt_inf_p_lower_0	, "+inf")
TOML_TEST(toml_floatpt_inf_n_lower_0	, "-inf")
TOML_TEST(toml_floatpt_inf_u_lower_1	,  "infinity")
TOML_TEST(toml_floatpt_inf_p_lower_1	, "+infinity")
TOML_TEST(toml_floatpt_inf_n_lower_1	, "-infinity")
TOML_TEST(toml_floatpt_inf_u_mixed_0	,  "Inf")
TOML_TEST(toml_floatpt_inf_p_mixed_0	, "+Inf")
TOML_TEST(toml_floatpt_inf_n_mixed_0	, "-Inf")
TOML_TEST(toml_floatpt_inf_u_mixed_1	,  "Infinity")
TOML_TEST(toml_floatpt_inf_p_mixed_1	, "+Infinity")
TOML_TEST(toml_floatpt_inf_n_mixed_1	, "-Infinity")
TOML_TEST(toml_floatpt_inf_u_upper_0	,  "INF")
TOML_TEST(toml_floatpt_inf_p_upper_0	, "+INF")
TOML_TEST(toml_floatpt_inf_n_upper_0	, "-INF")
TOML_TEST(toml_floatpt_inf_u_upper_1	,  "INFINITY")
TOML_TEST(toml_floatpt_inf_p_upper_1	, "+INFINITY")
TOML_TEST(toml_floatpt_inf_n_upper_1	, "-INFINITY")
TOML_TEST(toml_floatpt_nan_u_lower_0	,  "nan")
TOML_TEST(toml_floatpt_nan_p_lower_0	, "+nan")
TOML_TEST(toml_floatpt_nan_n_lower_0	, "-nan")
TOML_TEST(toml_floatpt_nan_u_mixed_0	,  "NaN")
TOML_TEST(toml_floatpt_nan_p_mixed_0	, "+NaN")
TOML_TEST(toml_floatpt_nan_n_mixed_0	, "-NaN")
TOML_TEST(toml_floatpt_nan_u_upper_0	,  "NAN")
TOML_TEST(toml_floatpt_nan_p_upper_0	, "+NAN")
TOML_TEST(toml_floatpt_nan_n_upper_0	, "-NAN")

TOML_TEST(toml_floatpt_inf_u_utf8_0	,  "∞")
TOML_TEST(toml_floatpt_inf_p_utf8_0	, "+∞")
TOML_TEST(toml_floatpt_inf_n_utf8_0	, "-∞")
TOML_TEST(toml_floatpt_inf_u_utf8_1	,  "\u221E")
TOML_TEST(toml_floatpt_inf_p_utf8_1	, "+\u221E")
TOML_TEST(toml_floatpt_inf_n_utf8_1	, "-\u221E")

// TODO float precision tests, using math constants



TOML_TEST(toml_string_empty		, "\"\"")
TOML_TEST(toml_string			, "\"Hello World!\"")
TOML_TEST(toml_string_cc_c0		, "\"␡␁␂␃␄␅␆␇␈␉␊␋␌␍␎␏␐␑␒␓␔␕␖␗␘␙␚␛␜␝␞␟\"")
TOML_TEST(toml_string_cc_c1		, "\"\"")
TOML_TEST(toml_string_utf8_fr	, "\"Être à même de ça, d'air sûr — manger du maïs à l'œil… D'où la paix sur l'île de son âme…\"")
TOML_TEST(toml_string_utf8_ru	, "\"Яцк Ничолсон\"")
TOML_TEST(toml_string_utf8_jp	, "\"お前はもう死んでいる - 愛 - 私は実体の小さな学生です\"")
TOML_TEST(toml_string_utf8_ho	, "\"�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻\"")

TOML_TEST(toml_escape_sq1	, "\".\\\'.\"")	TOML_TEST(toml_escstr_sq1	, "\".'.\"")
TOML_TEST(toml_escape_sq2	, "\".\\\".\"")
TOML_TEST(toml_escape_slb	, "\".\\\\.\"")
TOML_TEST(toml_escape_slf	, "\".\\/.\"")	TOML_TEST(toml_escstr_slf	, "\"./.\"")
TOML_TEST(toml_escape_spc	, "\".\\ .\"")	TOML_TEST(toml_escstr_spc	, "\".\\\\ .\"") // TODO inspect this test further
TOML_TEST(toml_escape_tab	, "\".\\t.\"")
TOML_TEST(toml_escape_nl	, "\".\\n.\"")
TOML_TEST(toml_escape_cr	, "\".\\r.\"")
TOML_TEST(toml_escape_ff	, "\".\\f.\"")
TOML_TEST(toml_escape_vt	, "\".\\v.\"")	TOML_TEST(toml_escstr_vt	, "\".\\u000B.\"")
TOML_TEST(toml_escape_esc	, "\".\\e.\"")	TOML_TEST(toml_escstr_esc	, "\".\\u001B.\"")
TOML_TEST(toml_escape_bel	, "\".\\a.\"")	TOML_TEST(toml_escstr_bel	, "\".\\u0007.\"")
TOML_TEST(toml_escape_bs	, "\".\\b.\"")

TOML_TEST(toml_escape_utf8_ru_u	, "\"\\u042F\\u0446\\u043A \\u041D\\u0438\\u0447\\u043E\\u043B\\u0441\\u043E\\u043D\"")
TOML_TEST(toml_escape_utf8_ru_U	, "\"\\U0000042F\\U00000446\\U0000043A \\U0000041D\\U00000438\\U00000447\\U0000043E\\U0000043B\\U00000441\\U0000043E\\U0000043D\"")
TOML_TEST(toml_escape_utf8_ru_x	, "\"\\xD0\\xAF\\xD1\\x86\\xD0\\xBA \\xD0\\x9D\\xD0\\xB8\\xD1\\x87\\xD0\\xBE\\xD0\\xBB\\xD1\\x81\\xD0\\xBE\\xD0\\xBD\"")



t_utf8*	toml_array_empty_min			= "_=[]";
t_utf8*	toml_array_empty				= "\n_ = []\n";
t_utf8*	toml_array_min					= "_=[false,true,null]";
t_utf8*	toml_array						= "\n_ = [ false, true, null ]\n";
t_utf8*	toml_array_nested_min			= "_=[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{swag=1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";
t_utf8*	toml_array_nested				= "\n_ = [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ { swag = 1 } ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ]\n";
/* TODO
t_utf8*	toml_inline_array_empty_min		= "_=[]";
t_utf8*	toml_inline_array_empty			= "\n_ = []\n";
t_utf8*	toml_inline_array_min			= "_=[false,true,null]\n";
t_utf8*	toml_inline_array				= "\n_ = [ false, true, null ]\n";
t_utf8*	toml_inline_array_nested_min	= "_=[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{swag=1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";
t_utf8*	toml_inline_array_nested		= "\n_ = [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ [ { swag = 1 } ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ] ]\n";
*/


t_utf8*	toml_object_empty_min			= "_={}";
t_utf8*	toml_object_empty				= "\n_ = {}\n";
t_utf8*	toml_object_min					= "_={a=false,b=true,c=null}";
t_utf8*	toml_object						= "\n_ = { a = false, b = true, c = null }\n";
t_utf8*	toml_object_nested_min			= "_={a={b={c={d={e={f={g={h={i={j={k={l={m={n={o={p={q={r={s={t={u={v={w={x={y={z=\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
t_utf8*	toml_object_nested				= "\n_ = { a = { b = { c = { d = { e = { f = { g = { h = { i = { j = { k = { l = { m = { n = { o = { p = { q = { r = { s = { t = { u = { v = { w = { x = { y = { z = \"swag\" } } } } } } } } } } } } } } } } } } } } } } } } } }\n";
/* TODO
t_utf8*	toml_inline_object_empty_min	= "_={}";
t_utf8*	toml_inline_object_empty		= "\n_ = {}\n";
t_utf8*	toml_inline_object_min			= "_={a=false,b=true,c=null}\n";
t_utf8*	toml_inline_object				= "\n_ = { a = false, b = true, c = null }\n";
t_utf8*	toml_inline_object_nested_min	= "_={a={b={c={d={e={f={g={h={i={j={k={l={m={n={o={p={q={r={s={t={u={v={w={x={y={z=\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
t_utf8*	toml_inline_object_nested		= "\n_ = { a = { b = { c = { d = { e = { f = { g = { h = { i = { j = { k = { l = { m = { n = { o = { p = { q = { r = { s = { t = { u = { v = { w = { x = { y = { z = \"swag\" } } } } } } } } } } } } } } } } } } } } } } } } } }\n";
*/



t_utf8*	toml_object_string_min =
	"type=11"
"\n""value="
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
;
t_utf8*	toml_object_string = "\
\ntype = 11\
\nvalue = \"{\\\"Label\\\":\\\"NAME\\\",\\\"Attributes\\\":{\\\"PATTERN_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"ENTITY_PATTERN\\\"}]}],\\\"DESCRIPTION_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"DESC\\\"}]}],\\\"CHARACTERISTIC_ATTRIBUTE\\\":[],\\\"TEMPLATE_ATTRIBUTE\\\":[{}]}}\"\
\n";

// TODO triple-quote literal string tests

// TODO comment handling tests



t_utf8*	toml_helloworld_min	= "hello=\"world\"";
t_utf8*	toml_helloworld		= "\nhello = \"world\"\n";

t_utf8*	toml_whitespace		= "  hello  =  \"world\"  \n";
t_utf8*	toml_whitespace_tab	= "\thello\t=\t\"world\"\t\n";
t_utf8*	toml_whitespace_nl	= "\nhello\n=\n\"world\"\t\n";
t_utf8*	toml_whitespace_cr	= "\rhello\r=\r\"world\"\r\n";
t_utf8*	toml_whitespace_ff	= "\fhello\f=\f\"world\"\f\n";
t_utf8*	toml_whitespace_vt	= "\vhello\v=\v\"world\"\v\n";
t_utf8*	toml_whitespace_all	= "\t\f\r\n\"hello\"\t\f\r\n=\t\f\r\n\"world\"\t\f\r\n";

t_utf8*	toml_strange_sot	= "\1hello=\1\"world\"\1\n";
t_utf8*	toml_strange_stx	= "\2hello=\2\"world\"\2\n";
t_utf8*	toml_strange_etx	= "\3hello=\3\"world\"\3\n";
t_utf8*	toml_strange_eot	= "\4hello=\4\"world\"\4\n";
t_utf8*	toml_strange_esc	= "\x1Bhello=\x1B\"world\"\x1B\n";
t_utf8*	toml_strange_bs		= "\bhello=\b\"world\"\b\n";



t_utf8*	toml_simple_min =
	"test_bool_0=false"
"\n""test_bool_1=true"
"\n""test_number=0"
"\n""test_string=\"\""
"\n""test_arrays=[false,true,0,\"\"]"
"\n""[test_object]"
"\n"	"nest_bool_0=false"
"\n"	"nest_bool_1=true"
"\n"	"nest_number=0"
"\n"	"nest_string=\"\""
"\n"	"nest_arrays=[123456,\"hello\"]"
"\n"	"nest_object=null"
;
t_utf8*	toml_simple = "\
\ntest_bool_0 = false\
\ntest_bool_1 = true\
\ntest_number = 0\
\ntest_string = \"\"\
\ntest_arrays = [ false, true, 0, \"\" ]\
\n\
\n[test_object]\
\n\
\n	nest_bool_0 = false\
\n	nest_bool_1 = true\
\n	nest_number = 0\
\n	nest_string = \"\"\
\n	nest_arrays = [ 123456, \"hello\" ]\
\n	nest_object = null\
\n";



t_utf8*	toml_commas_min =
	"test_bool_0=false"
"\n""test_bool_1=true"
"\n""test_number=0"
"\n""test_string=\"\""
"\n""test_arrays=[false,true,0,\"\",]"
"\n""[test_object]"
"\n"	"nest_bool_0=false"
"\n"	"nest_bool_1=true"
"\n"	"nest_number=0"
"\n"	"nest_string=\"\""
"\n"	"nest_arrays=[123456,\"hello\",]"
"\n"	"nest_object=null"
;
t_utf8*	toml_commas = "\
\ntest_bool_0 = false\
\ntest_bool_1 = true\
\ntest_number = 0\
\ntest_string = \"\"\
\ntest_arrays = \
\n[\
\n	false,\
\n	true,\
\n	0,\
\n	\"\",\
\n]\
\n\
\n[test_object]\
\n\
\n	nest_bool_0 = false\
\n	nest_bool_1 = true\
\n	nest_number = 0\
\n	nest_string = \"\"\
\n	nest_arrays = \
\n	[\
\n		123456,\
\n		\"hello\",\
\n	]\
\n	nest_object = null\
\n";



t_utf8*	toml_newline = "\n\n\
\n\ntest_bool_0\n=\nfalse\
\n\ntest_bool_1\n=\ntrue\
\n\ntest_number\n=\n0\
\n\ntest_string\n=\n\"\"\
\n\ntest_arrays\n=\n\
\n\n[\
\n\n\nfalse\n,\
\n\n\ntrue\n,\
\n\n\n0\n,\
\n\n\n\"\"\
\n\n]\
\n\n[test_object]\
\n\n\nnest_bool_0\n=\nfalse\n\n\
\n\n\nnest_bool_1\n=\ntrue\n\n\
\n\n\nnest_number\n=\n0\n\n\
\n\n\nnest_string\n=\n\"\"\
\n\n\nnest_arrays\n=\n\
\n\n\n[\
\n\n\n\n123456\n,\
\n\n\n\n\"hello\"\
\n\n\n]\
\n\n\nnest_object\t=\tnull\
\n\n";



t_utf8*	toml_config_min =
	"[\"General Settings\"]"
"\n""background_pause"  "=false"
"\n""background_input"  "=true"
"\n""[\"Video Settings\"]"
"\n""window_position"   "={x=-793,y=75}"
"\n""window_size"       "={x=768,y=720}"
"\n""window_maximized"  "=false"
"\n""fullscreen"        "=false"
"\n""keep_aspect_ratio" "=true"
"\n""vertical_sync"     "=false"
"\n""[\"Audio Settings\"]"
"\n""volume_master" "=100"
"\n""volume_music"  "=100"
"\n""volume_sfx"    "=100"
"\n""mute"          "=false"
"\n""[\"Input Mapping\"]"
"\n""joypad_up"     "={device_guid=\"0003000000C82D000000600000000000\",device_id=0,event=\"jhat\",which=0,value=1}"
"\n""joypad_down"   "={device_guid=\"00030000005E0400008E020000000078\",device_id=0,event=\"jhat\",which=0,value=4}"
"\n""joypad_left"   "={device_guid=\"000300000025090000E8030000000000\",device_id=0,event=\"jhat\",which=0,value=8}"
"\n""joypad_right"  "={device_guid=\"00030000006F0E0000A6020000000078\",device_id=0,event=\"jhat\",which=0,value=2}"
"\n""joypad_A"      "={device_guid=\"0003000000C82D000000600000000000\",device_id=0,event=\"jbutton\",value=0}"
"\n""joypad_B"      "={device_guid=\"00000000000000000000000000000000\",device_id=0,event=\"jbutton\",value=1}"
;
t_utf8*	toml_config = "\
\n[\"General Settings\"]\
\n\
\n	background_pause = false\
\n	background_input = true\
\n\
\n[\"Video Settings\"]\
\n\
\n	window_position"   " = { x = -793, y = 75 }\
\n	window_size"       " = { x = 768, y = 720 }\
\n	window_maximized"  " = false\
\n	fullscreen"        " = false\
\n	keep_aspect_ratio" " = true\
\n	vertical_sync"     " = false\
\n\
\n[\"Audio Settings\"]\
\n\
\n	volume_master" " = 100\
\n	volume_music"  " = 100\
\n	volume_sfx"    " = 100\
\n	mute"          " = false\
\n\
\n[\"Input Mapping\"]\
\n\
\n	joypad_up"    " = { device_guid = \"0003000000C82D000000600000000000\", device_id = 0, event = \"jhat\", which = 0, value = 1 }\
\n	joypad_down"  " = { device_guid = \"00030000005E0400008E020000000078\", device_id = 0, event = \"jhat\", which = 0, value = 4 }\
\n	joypad_left"  " = { device_guid = \"000300000025090000E8030000000000\", device_id = 0, event = \"jhat\", which = 0, value = 8 }\
\n	joypad_right" " = { device_guid = \"00030000006F0E0000A6020000000078\", device_id = 0, event = \"jhat\", which = 0, value = 2 }\
\n	joypad_A"     " = { device_guid = \"0003000000C82D000000600000000000\", device_id = 0, event = \"jbutton\", value = 0 }\
\n	joypad_B"     " = { device_guid = \"00000000000000000000000000000000\", device_id = 0, event = \"jbutton\", value = 1 }\
\n";



t_utf8*	toml_complex_min =
	"[Attributes]"
"\n"	"[[Attributes.SEX_ATTRIBUTE]]"
"\n"	"[[Attributes.SEX_ATTRIBUTE.Values]]"			"\nCHARACTER=\"M\""
"\n"	"[[Attributes.AGE_ATTRIBUTE]]"
"\n"	"[[Attributes.AGE_ATTRIBUTE.Values]]"			"\nINTEGER=\"82\""
"\n"	"[[Attributes.SPOUSE_ATTRIBUTE]]"
"\n"	"[[Attributes.SPOUSE_ATTRIBUTE.Values]]"		"\nBOOLEAN=\"FALSE\""
"\n"	"[[Attributes.HEIGHT_ATTRIBUTE]]"
"\n"	"[[Attributes.HEIGHT_ATTRIBUTE.Values]]"		"\nFLOAT=\"176.5\""
"\n"	"[[Attributes.OCCUPATION_ATTRIBUTE]]"
"\n"	"[[Attributes.OCCUPATION_ATTRIBUTE.Values]]"	"\nSTRING=\"actor\""
"\n"	"[[Attributes.LABEL_ATTRIBUTE]]"
"\n"	"[[Attributes.LABEL_ATTRIBUTE.Values]]"			"\nTEXT=\"Яцк Ничолсон\""
"\n"	"[[Attributes.BIRTHDAY_ATTRIBUTE]]"
"\n"	"[[Attributes.BIRTHDAY_ATTRIBUTE.Values]]"		"\nTIME=\"-1031788800\""
"\n"	"[[Attributes.DOCUMENT_ATTRIBUTE]]"
"\n"	"[[Attributes.DOCUMENT_ATTRIBUTE.Values]]"		"\nWEB=\"urn:isbn:0393350967\""
"\n"	"[[Attributes.WEIGHT_ATTRIBUTE]]"
"\n"	"[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=72\""
"\n"	"[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"listed\",\"\",\"\"]]"
"\n"	"[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=160\""
"\n"	"[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]"
"\n"	"[[Attributes.LOCATION_ATTRIBUTE]]"
"\n"	"[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Los Angeles\""
"\n"	"[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Aspen\""
"\n"	"[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Malibu\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE]]"				
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Jennifer\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]"
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Caleb\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]"
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Honey\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Lorraine\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Raymond\""
"\n"	"[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]"
"\n""[Properties]"
"\n"	"\"\"=[\"known for\",\"most popular role\",\"The Shining\"]"
"\n"	"\"\"=[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"]"
"\n"	"\"\"=[\"fan of\",\"\",\"Bob Dylan\"]"
"\n"	"\"\"=[\"also known for\",\"best performance\",\"Chinatown\"]"
"\n""[Values]"
"\n"	"\"\"=[\"actor\",\"player\",\"filmmaker\"]"
;
t_utf8*	toml_complex = "\
\n[Attributes]\
\n\
\n	[[Attributes.SEX_ATTRIBUTE]]\
\n	[[Attributes.SEX_ATTRIBUTE.Values]]"		"\nCHARACTER=\"M\"\
\n	[[Attributes.AGE_ATTRIBUTE]]\
\n	[[Attributes.AGE_ATTRIBUTE.Values]]"		"\nINTEGER=\"82\"\
\n	[[Attributes.SPOUSE_ATTRIBUTE]]\
\n	[[Attributes.SPOUSE_ATTRIBUTE.Values]]"		"\nBOOLEAN=\"FALSE\"\
\n	[[Attributes.HEIGHT_ATTRIBUTE]]\
\n	[[Attributes.HEIGHT_ATTRIBUTE.Values]]"		"\nFLOAT=\"176.5\"\
\n	[[Attributes.OCCUPATION_ATTRIBUTE]]\
\n	[[Attributes.OCCUPATION_ATTRIBUTE.Values]]"	"\nSTRING=\"actor\"\
\n	[[Attributes.LABEL_ATTRIBUTE]]\
\n	[[Attributes.LABEL_ATTRIBUTE.Values]]"		"\nTEXT=\"Яцк Ничолсон\"\
\n	[[Attributes.BIRTHDAY_ATTRIBUTE]]\
\n	[[Attributes.BIRTHDAY_ATTRIBUTE.Values]]"	"\nTIME=\"-1031788800\"\
\n	[[Attributes.DOCUMENT_ATTRIBUTE]]\
\n	[[Attributes.DOCUMENT_ATTRIBUTE.Values]]"	"\nWEB=\"urn:isbn:0393350967\"\
\n	[[Attributes.WEIGHT_ATTRIBUTE]]\
\n	[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=72\"\
\n	[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"listed\",\"\",\"\"]]\
\n	[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=160\"\
\n	[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]\
\n	[[Attributes.LOCATION_ATTRIBUTE]]\
\n	[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Los Angeles\"\
\n	[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Aspen\"\
\n	[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Malibu\"\
\n	[[Attributes.CHILD_ATTRIBUTE]]\
\n	[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Jennifer\"\
\n	[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]\
\n	[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Caleb\"\
\n	[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]\
\n	[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Honey\"\
\n	[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Lorraine\"\
\n	[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Raymond\"\
\n	[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n\"\"=[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]\
\n\
\n[Properties]\
\n\
\n	\"\"=[\"known for\",\"most popular role\",\"The Shining\"]\
\n	\"\"=[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"]\
\n	\"\"=[\"fan of\",\"\",\"Bob Dylan\"]\
\n	\"\"=[\"also known for\",\"best performance\",\"Chinatown\"]\
\n\
\n[Values]\
\n\
\n	\"\"=[\"actor\",\"player\",\"filmmaker\"]\
\n";



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/



#if !(defined(c_tomlparse) && defined(c_tomlprint))
void test_toml(void)	{}
#else

#define DEFINETEST_TOML(STRICT, NSTRICT, MINIFY, _MIN) \
static t_utf8*	c_toml_##STRICT##_##MINIFY(t_utf8* toml)	\
{															\
	s_toml* tmp = TOML_FromString_##STRICT(toml);			\
	t_utf8* result = TOML_ToString_##MINIFY(tmp);			\
	free(tmp);												\
	return (result);										\
}															\
void	print_test_toml_##STRICT##_##MINIFY(char const* test_name, t_testflags flags,\
		char const* expecting,														\
		char const* str)															\
{																					\
	TEST_INIT(str)																	\
	TEST_PERFORM(	toml_##STRICT##_##MINIFY, (t_utf8*)str)							\
	TEST_PRINT(str,	toml_##STRICT##_##MINIFY, "str=\"%s\"", str)					\
	TEST_FREE()																		\
}																					\
void	test_toml_##STRICT##_##MINIFY(void)																																			\
{																																													\
/*	| TEST FUNCTION                    | TEST NAME                                          | TESTFLAGS  | EXPECTING                              | TEST ARGS					*/	\
	print_test_toml_##STRICT##_##MINIFY("null pointer               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									NULL);							\
	print_test_toml_##STRICT##_##MINIFY("empty string               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									"");							\
	print_test_toml_##STRICT##_##MINIFY("toml_null                  ("#STRICT" -> "#MINIFY")",FALSE,		toml_null##_MIN,						toml_null);						\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_0_lower          ("#STRICT" -> "#MINIFY")",FALSE,		toml_bool_0_lower##_MIN,				toml_bool_0_lower);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_1_lower          ("#STRICT" -> "#MINIFY")",FALSE,		toml_bool_1_lower##_MIN,				toml_bool_1_lower);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_0_upper          ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_bool_0_lower##_MIN:NULL,			toml_bool_0_upper);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_1_upper          ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_bool_1_lower##_MIN:NULL,			toml_bool_1_upper);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_0_mixed          ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_bool_0_lower##_MIN:NULL,			toml_bool_0_mixed);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_1_mixed          ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_bool_1_lower##_MIN:NULL,			toml_bool_1_mixed);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_0_weird          ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_bool_0_weird);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_1_weird          ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_bool_1_weird);				\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_empty_unsigned("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_integer_empty_unsigned);	\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_0_unsigned    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_0_unsigned##_MIN,			toml_integer_0_unsigned);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_1_unsigned    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_1_unsigned##_MIN,			toml_integer_1_unsigned);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_2_unsigned    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_2_unsigned##_MIN,			toml_integer_2_unsigned);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_3_unsigned    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_3_unsigned##_MIN,			toml_integer_3_unsigned);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_4_unsigned    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_4_unsigned##_MIN,			toml_integer_4_unsigned);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_empty_negative("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_integer_empty_negative);	\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_0_negative    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_0_unsigned##_MIN,			toml_integer_0_negative);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_1_negative    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_1_negative##_MIN,			toml_integer_1_negative);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_2_negative    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_2_negative##_MIN,			toml_integer_2_negative);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_3_negative    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_3_negative##_MIN,			toml_integer_3_negative);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_4_negative    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_4_negative##_MIN,			toml_integer_4_negative);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_empty_positive("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_integer_empty_positive);	\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_0_positive    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_0_unsigned##_MIN,			toml_integer_0_positive);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_1_positive    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_1_unsigned##_MIN,			toml_integer_1_positive);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_2_positive    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_2_unsigned##_MIN,			toml_integer_2_positive);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_3_positive    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_3_unsigned##_MIN,			toml_integer_3_positive);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_4_positive    ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_4_unsigned##_MIN,			toml_integer_4_positive);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64min_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64min_lt##_MIN,			toml_integer_f64min_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64min_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64min_eq##_MIN,			toml_integer_f64min_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64min_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64min_gt##_MIN,			toml_integer_f64min_gt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64max_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64max_lt##_MIN,			toml_integer_f64max_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64max_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64max_eq##_MIN,			toml_integer_f64max_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_f64max_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_f64max_gt##_MIN,			toml_integer_f64max_gt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64min_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64min_lt##_MIN,			toml_integer_s64min_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64min_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64min_eq##_MIN,			toml_integer_s64min_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64min_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64max_eq##_MIN,			toml_integer_s64min_gt);/*TODO*/\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64max_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64max_lt##_MIN,			toml_integer_s64max_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64max_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64max_eq##_MIN,			toml_integer_s64max_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_integer_s64max_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_integer_s64min_eq##_MIN,			toml_integer_s64max_gt);/*TODO*/\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_0             ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_0f1##_MIN,					toml_floatpt_0);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_1             ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_1f1##_MIN,					toml_floatpt_1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_2             ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_2f1##_MIN,					toml_floatpt_2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_3             ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_3f1##_MIN,					toml_floatpt_3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_4             ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_4##_MIN,					toml_floatpt_4);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_0f            ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_0f1##_MIN,					toml_floatpt_0f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_1f            ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_1f1##_MIN,					toml_floatpt_1f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_2f            ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_2f1##_MIN,					toml_floatpt_2f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_3f            ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_3f1##_MIN,					toml_floatpt_3f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_4f            ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_4##_MIN,					toml_floatpt_4f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_0f1           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_0f1##_MIN,					toml_floatpt_0f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_1f1           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_1f1##_MIN,					toml_floatpt_1f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_2f1           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_2f1##_MIN,					toml_floatpt_2f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_3f1           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_3f1##_MIN,					toml_floatpt_3f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_4f1           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_4f1##_MIN,					toml_floatpt_4f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_0f2           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_0f1##_MIN,					toml_floatpt_0f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_1f2           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_1f1##_MIN,					toml_floatpt_1f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_2f2           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_2f1##_MIN,					toml_floatpt_2f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_3f2           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_3f1##_MIN,					toml_floatpt_3f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_4f2           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_4f2##_MIN,					toml_floatpt_4f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_0f3           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_0f1##_MIN,					toml_floatpt_0f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_1f3           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_1f1##_MIN,					toml_floatpt_1f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_2f3           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_2f1##_MIN,					toml_floatpt_2f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_3f3           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_3f1##_MIN,					toml_floatpt_3f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_4f3           ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_4f3##_MIN,					toml_floatpt_4f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64min_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64min_lt##_MIN,			toml_floatpt_f64min_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64min_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64min_eq##_MIN,			toml_floatpt_f64min_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64min_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64min_eq##_MIN,			toml_floatpt_f64min_gt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64max_lt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64max_lt##_MIN,			toml_floatpt_f64max_lt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64max_eq     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64max_eq##_MIN,			toml_floatpt_f64max_eq);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_f64max_gt     ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_f64max_eq##_MIN,			toml_floatpt_f64max_gt);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_inf_p_lower_0##_MIN,		toml_floatpt_inf_u_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_inf_p_lower_0##_MIN,		toml_floatpt_inf_p_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_inf_n_lower_0##_MIN,		toml_floatpt_inf_n_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_lower_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_u_lower_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_lower_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_p_lower_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_lower_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_n_lower_0##_MIN:NULL,	toml_floatpt_inf_n_lower_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_u_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_p_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_n_lower_0##_MIN:NULL,	toml_floatpt_inf_n_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_mixed_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_u_mixed_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_mixed_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_p_mixed_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_mixed_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_n_lower_0##_MIN:NULL,	toml_floatpt_inf_n_mixed_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_u_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_p_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_n_lower_0##_MIN:NULL,	toml_floatpt_inf_n_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_upper_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_u_upper_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_upper_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_p_lower_0##_MIN:NULL,	toml_floatpt_inf_p_upper_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_upper_1 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_inf_n_lower_0##_MIN:NULL,	toml_floatpt_inf_n_upper_1);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_u_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_nan_u_lower_0##_MIN,		toml_floatpt_nan_u_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_p_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_nan_u_lower_0##_MIN,		toml_floatpt_nan_p_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_n_lower_0 ("#STRICT" -> "#MINIFY")",FALSE,		toml_floatpt_nan_u_lower_0##_MIN,		toml_floatpt_nan_n_lower_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_u_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_u_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_p_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_p_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_n_mixed_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_n_mixed_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_u_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_u_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_p_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_p_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_nan_n_upper_0 ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_floatpt_nan_u_lower_0##_MIN:NULL,	toml_floatpt_nan_n_upper_0);	\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_utf8_0  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_u_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_utf8_0  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_p_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_utf8_0  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_n_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_u_utf8_1  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_u_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_p_utf8_1  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_p_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_floatpt_inf_n_utf8_1  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_floatpt_inf_n_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_string_empty          ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_empty##_MIN,				toml_string_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string                ("#STRICT" -> "#MINIFY")",FALSE,		toml_string##_MIN,						toml_string);					\
	print_test_toml_##STRICT##_##MINIFY("toml_string_cc_c0          ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_cc_c0##_MIN,				toml_string_cc_c0);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string_cc_c1          ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_cc_c1##_MIN,				toml_string_cc_c1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_fr        ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_fr##_MIN,				toml_string_utf8_fr);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_ru        ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_ru##_MIN,				toml_string_utf8_ru);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_jp        ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_jp##_MIN,				toml_string_utf8_jp);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_ho        ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_ho##_MIN,				toml_string_utf8_ho);			\
	print_test_toml_##STRICT##_##MINIFY("toml_array_empty           ("#STRICT" -> "#MINIFY")",FALSE,		toml_array_empty##_MIN,					toml_array_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array                 ("#STRICT" -> "#MINIFY")",FALSE,		toml_array##_MIN,						toml_array);					\
	print_test_toml_##STRICT##_##MINIFY("toml_array_min             ("#STRICT" -> "#MINIFY")",FALSE,		toml_array##_MIN,						toml_array_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array_nested          ("#STRICT" -> "#MINIFY")",FALSE,		toml_array_nested##_MIN,				toml_array_nested);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array_nested_min      ("#STRICT" -> "#MINIFY")",FALSE,		toml_array_nested##_MIN,				toml_array_nested_min);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_empty          ("#STRICT" -> "#MINIFY")",FALSE,		toml_object_empty##_MIN,				toml_object_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_object                ("#STRICT" -> "#MINIFY")",FALSE,		toml_object##_MIN,						toml_object);					\
	print_test_toml_##STRICT##_##MINIFY("toml_object_min            ("#STRICT" -> "#MINIFY")",FALSE,		toml_object##_MIN,						toml_object_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested         ("#STRICT" -> "#MINIFY")",FALSE,		toml_object_nested##_MIN,				toml_object_nested);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min     ("#STRICT" -> "#MINIFY")",FALSE,		toml_object_nested##_MIN,				toml_object_nested_min);		\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min     ("#STRICT" -> "#MINIFY")",FALSE,		toml_object_string##_MIN,				toml_object_string);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min     ("#STRICT" -> "#MINIFY")",FALSE,		toml_object_string##_MIN,				toml_object_string_min);		\
	print_test_toml_##STRICT##_##MINIFY("toml_config                ("#STRICT" -> "#MINIFY")",FALSE,		toml_config##_MIN,						toml_config);					\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace            ("#STRICT" -> "#MINIFY")",FALSE,		toml_helloworld##_MIN,					toml_whitespace);				\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_tab        ("#STRICT" -> "#MINIFY")",FALSE,		toml_helloworld##_MIN,					toml_whitespace_tab);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_nl         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_nl);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_cr         ("#STRICT" -> "#MINIFY")",FALSE,		toml_helloworld##_MIN,					toml_whitespace_cr);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_ff         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_ff);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_vt         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_vt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_all        ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_all);			\
	print_test_toml_##STRICT##_##MINIFY("toml_simple                ("#STRICT" -> "#MINIFY")",FALSE,		toml_simple##_MIN,						toml_simple);					\
	print_test_toml_##STRICT##_##MINIFY("toml_simple_min            ("#STRICT" -> "#MINIFY")",FALSE,		toml_simple##_MIN,						toml_simple_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_commas                ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_simple##_MIN:NULL,					toml_commas);					\
	print_test_toml_##STRICT##_##MINIFY("toml_commas_min            ("#STRICT" -> "#MINIFY")",FALSE,		toml_simple##_MIN,						toml_commas_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_newline               ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_simple##_MIN:NULL,					toml_newline);					\
/*	print_test_toml_##STRICT##_##MINIFY("toml_complex               ("#STRICT" -> "#MINIFY")",FALSE,		toml_complex##_MIN,						toml_complex);					TODO */\
/*	print_test_toml_##STRICT##_##MINIFY("toml_complex_min           ("#STRICT" -> "#MINIFY")",FALSE,		toml_complex##_MIN,						toml_complex_min);				TODO */\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_sq1            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_sq1##_MIN:NULL,				toml_escape_sq1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_sq2            ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_sq2##_MIN,					toml_escape_sq2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_slb            ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_slb##_MIN,					toml_escape_slb);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_slf            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_slf##_MIN:NULL,				toml_escape_slf);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_spc            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_spc##_MIN:NULL,				toml_escape_spc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_tab            ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_tab##_MIN,					toml_escape_tab);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_nl             ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_nl##_MIN,					toml_escape_nl);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_cr             ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_cr##_MIN,					toml_escape_cr);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_ff             ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_ff##_MIN,					toml_escape_ff);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_vt             ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_vt##_MIN:NULL,				toml_escape_vt);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_esc            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_esc##_MIN:NULL,				toml_escape_esc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_bel            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_escstr_bel##_MIN:NULL,				toml_escape_bel);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_bs             ("#STRICT" -> "#MINIFY")",FALSE,		toml_escape_bs##_MIN,					toml_escape_bs);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_utf8_ru_x      ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?toml_string_utf8_ru##_MIN:NULL,			toml_escape_utf8_ru_x);			\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_utf8_ru_u      ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_ru##_MIN,				toml_escape_utf8_ru_u);			\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_utf8_ru_U      ("#STRICT" -> "#MINIFY")",FALSE,		toml_string_utf8_ru##_MIN,				toml_escape_utf8_ru_U);			\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_sot           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_sot);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_stx           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_stx);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_etx           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_etx);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_eot           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_eot);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_esc           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_esc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_bs            ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									toml_strange_bs);				\
}
#endif

DEFINETEST_TOML(Lenient, TRUE,	Pretty,)
DEFINETEST_TOML(Lenient, TRUE,	Minify, _min)
DEFINETEST_TOML(Strict, FALSE,	Pretty,)
DEFINETEST_TOML(Strict, FALSE,	Minify, _min)

// TODO test othe functions than just Parse/Print



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_encode_toml(void)
{
	print_suite_title("libccc/encode/toml");

	print_nonstd();

	test_toml_Lenient_Pretty();
	test_toml_Lenient_Minify();
	test_toml_Strict_Pretty();
	test_toml_Strict_Minify();

	return (OK);
}
