
#include "libccc/encode/toml.h"

#include "test.h"



// the minimal boilerplate needed to store a single vlue in TOML
#define TOML_TEST(NAME, STR) \
	t_utf8 const*	NAME		= "\n\"\" = "STR"\n";	\
	t_utf8 const*	NAME##_min	= "\n\"\"="STR"\n";	\




/*
** ************************************************************************** *|
**                              Testing Variables                             *|
** ************************************************************************** *|
*/

TOML_TEST(toml_null	, "null")

TOML_TEST(toml_bool_0	, "false")
TOML_TEST(toml_bool_1	, "true")



TOML_TEST(toml_number_0				, "0")
TOML_TEST(toml_number_1				, "1")
TOML_TEST(toml_number_2				, "42")
TOML_TEST(toml_number_3				, "777")
TOML_TEST(toml_number_4				, "123456")
TOML_TEST(toml_number_0f			, "0.")
TOML_TEST(toml_number_1f			, "1.")
TOML_TEST(toml_number_2f			, "42.")
TOML_TEST(toml_number_3f			, "777.")
TOML_TEST(toml_number_4f			, "123456.")
TOML_TEST(toml_number_0f1			, "0.0")
TOML_TEST(toml_number_1f1			, "1.0")
TOML_TEST(toml_number_2f1			, "42.0")
TOML_TEST(toml_number_3f1			, "777.0")
TOML_TEST(toml_number_4f1			, "123456.7")
TOML_TEST(toml_number_0f2			, "0.00")
TOML_TEST(toml_number_1f2			, "1.00")
TOML_TEST(toml_number_2f2			, "42.00")
TOML_TEST(toml_number_3f2			, "777.00")
TOML_TEST(toml_number_4f2			, "123456.78")
TOML_TEST(toml_number_0f3			, "0.000")
TOML_TEST(toml_number_1f3			, "1.000")
TOML_TEST(toml_number_2f3			, "42.000")
TOML_TEST(toml_number_3f3			, "777.000")
TOML_TEST(toml_number_4f3			, "123456.789")
TOML_TEST(toml_number_fmin_lt		, "-9007199254740991")
TOML_TEST(toml_number_fmin_eq		, "-9007199254740992")
TOML_TEST(toml_number_fmin_gt		, "-9007199254740993")
TOML_TEST(toml_number_fmax_lt		, "9007199254740991")
TOML_TEST(toml_number_fmax_eq		, "9007199254740992")
TOML_TEST(toml_number_fmax_gt		, "9007199254740993")
TOML_TEST(toml_number_inf_u_lower_0	,  "inf")
TOML_TEST(toml_number_inf_p_lower_0	, "+inf")
TOML_TEST(toml_number_inf_n_lower_0	, "-inf")
TOML_TEST(toml_number_inf_u_lower_1	, "infinity")
TOML_TEST(toml_number_inf_p_lower_1	, "+infinity")
TOML_TEST(toml_number_inf_n_lower_1	, "-infinity")
TOML_TEST(toml_number_inf_u_mixed_0	,  "Inf")
TOML_TEST(toml_number_inf_p_mixed_0	, "+Inf")
TOML_TEST(toml_number_inf_n_mixed_0	, "-Inf")
TOML_TEST(toml_number_inf_u_mixed_1	,  "Infinity")
TOML_TEST(toml_number_inf_p_mixed_1	, "+Infinity")
TOML_TEST(toml_number_inf_n_mixed_1	, "-Infinity")
TOML_TEST(toml_number_inf_u_upper_0	,  "INF")
TOML_TEST(toml_number_inf_p_upper_0	, "+INF")
TOML_TEST(toml_number_inf_n_upper_0	, "-INF")
TOML_TEST(toml_number_inf_u_upper_1	,  "INFINITY")
TOML_TEST(toml_number_inf_p_upper_1	, "+INFINITY")
TOML_TEST(toml_number_inf_n_upper_1	, "-INFINITY")
TOML_TEST(toml_number_nan_u_lower_0	,  "nan")
TOML_TEST(toml_number_nan_p_lower_0	, "+nan")
TOML_TEST(toml_number_nan_n_lower_0	, "-nan")
TOML_TEST(toml_number_nan_u_mixed_0	,  "NaN")
TOML_TEST(toml_number_nan_p_mixed_0	, "+NaN")
TOML_TEST(toml_number_nan_n_mixed_0	, "-NaN")
TOML_TEST(toml_number_nan_u_upper_0	,  "NAN")
TOML_TEST(toml_number_nan_p_upper_0	, "+NAN")
TOML_TEST(toml_number_nan_n_upper_0	, "-NAN")

TOML_TEST(toml_number_inf_u_utf8_0	,  "∞")
TOML_TEST(toml_number_inf_p_utf8_0	, "+∞")
TOML_TEST(toml_number_inf_n_utf8_0	, "-∞")
TOML_TEST(toml_number_inf_u_utf8_1	,  "\u221E")
TOML_TEST(toml_number_inf_p_utf8_1	, "+\u221E")
TOML_TEST(toml_number_inf_n_utf8_1	, "-\u221E")



TOML_TEST(toml_bigint_empty			, "n")
TOML_TEST(toml_bigint_0				, "0n")
TOML_TEST(toml_bigint_1				, "1n")
TOML_TEST(toml_bigint_2				, "42n")
TOML_TEST(toml_bigint_3				, "777n")
TOML_TEST(toml_bigint_4				, "123456n")
TOML_TEST(toml_bigint_0f			, "0.n")
TOML_TEST(toml_bigint_1f			, "1.n")
TOML_TEST(toml_bigint_2f			, "42.n")
TOML_TEST(toml_bigint_3f			, "777.n")
TOML_TEST(toml_bigint_4f			, "123456.n")
TOML_TEST(toml_bigint_0f1			, "0.0n")
TOML_TEST(toml_bigint_1f1			, "1.0n")
TOML_TEST(toml_bigint_2f1			, "42.0n")
TOML_TEST(toml_bigint_3f1			, "777.0n")
TOML_TEST(toml_bigint_4f1			, "123456.7n")
TOML_TEST(toml_bigint_0f2			, "0.00n")
TOML_TEST(toml_bigint_1f2			, "1.00n")
TOML_TEST(toml_bigint_2f2			, "42.00n")
TOML_TEST(toml_bigint_3f2			, "777.00n")
TOML_TEST(toml_bigint_4f2			, "123456.78n")
TOML_TEST(toml_bigint_0f3			, "0.000n")
TOML_TEST(toml_bigint_1f3			, "1.000n")
TOML_TEST(toml_bigint_2f3			, "42.000n")
TOML_TEST(toml_bigint_3f3			, "777.000n")
TOML_TEST(toml_bigint_4f3			, "123456.789n")
TOML_TEST(toml_bigint_fmin_lt		, "-9007199254740991n")
TOML_TEST(toml_bigint_fmin_eq		, "-9007199254740992n")
TOML_TEST(toml_bigint_fmin_gt		, "-9007199254740993n")
TOML_TEST(toml_bigint_fmax_lt		, "9007199254740991n")
TOML_TEST(toml_bigint_fmax_eq		, "9007199254740992n")
TOML_TEST(toml_bigint_fmax_gt		, "9007199254740993n")
TOML_TEST(toml_bigint_s64min_lt		, "-9223372036854775807n")
TOML_TEST(toml_bigint_s64min_eq		, "-9223372036854775808n")
TOML_TEST(toml_bigint_s64min_gt		, "-9223372036854775809n")
TOML_TEST(toml_bigint_s64max_lt		, "9223372036854775806n")
TOML_TEST(toml_bigint_s64max_eq		, "9223372036854775807n")
TOML_TEST(toml_bigint_s64max_gt		, "9223372036854775808n")
TOML_TEST(toml_bigint_bad_unan_lower, "nann")
TOML_TEST(toml_bigint_bad_unan_upper, "NANn")
TOML_TEST(toml_bigint_bad_uinf_lower, "infn")
TOML_TEST(toml_bigint_bad_uinf_upper, "INFn")
TOML_TEST(toml_bigint_bad_nnan_lower, "-nann")
TOML_TEST(toml_bigint_bad_nnan_upper, "-NANn")
TOML_TEST(toml_bigint_bad_ninf_lower, "-infn")
TOML_TEST(toml_bigint_bad_ninf_upper, "-INFn")
TOML_TEST(toml_bigint_bad_pnan_lower, "+nann")
TOML_TEST(toml_bigint_bad_pnan_upper, "+NANn")
TOML_TEST(toml_bigint_bad_pinf_lower, "+infn")
TOML_TEST(toml_bigint_bad_pinf_upper, "+INFn")



TOML_TEST(toml_string_empty		, "\"\"")
TOML_TEST(toml_string			, "\"Hello World!\"")
TOML_TEST(toml_string_cc_c0		, "\"␡␁␂␃␄␅␆␇␈␉␊␋␌␍␎␏␐␑␒␓␔␕␖␗␘␙␚␛␜␝␞␟\"")
TOML_TEST(toml_string_cc_c1		, "\"\"")
TOML_TEST(toml_string_utf8_fr	, "\"Être à même de ça, d'air sûr, maïs de son père en main… D'où la paix sur l'île de son âme…\"")
TOML_TEST(toml_string_utf8_ru	, "\"Яцк Ничолсон.\"")
TOML_TEST(toml_string_utf8_jp	, "\"お前はもう死んでいる - 愛\"")
TOML_TEST(toml_string_utf8_ho	, "\"�𑢰����� 𐐔𐐯𐑅𐐨𐑉𐐯𐐻\"")


t_utf8*	toml_array_empty	= "[]";
t_utf8*	toml_array_min		= "[false,true,null]\n";
t_utf8*	toml_array			= "\
\n[\
\n	false,\
\n	true,\
\n	null\
\n]\
\n";
t_utf8*	toml_array_nested_min	= "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{swag=1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]\n";
t_utf8*	toml_array_nested		= "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[{swag = 1}]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]\n";



t_utf8*	toml_object_empty	= "_={}";
t_utf8*	toml_object_min		= "_={a=false,b=true,c=null}";
t_utf8*	toml_object			= "_=\
{\
\n	a = false,\
\n	b = true,\
\n	c = null\
\n}";
t_utf8*	toml_object_nested_min	= "_={a={b={c={d={e={f={g={h={i={j={k={l={m={n={o={p={q={r={s={t={u={v={w={x={y={z=\"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";
t_utf8*	toml_object_nested		= "_={a = {b = {c = {d = {e = {f = {g = {h = {i = {j = {k = {l = {m = {n = {o = {p = {q = {r = {s = {t = {u = {v = {w = {x = {y = {z = \"swag\"}}}}}}}}}}}}}}}}}}}}}}}}}}";

t_utf8*	toml_object_string_min =
"\n""type=11"
"\n""value="
	"\"\"\"{"
		"\\\"Label\\\":\\\"NAME\\\","
		"\\\"Attributes\\\":"
		"{"
			"\\\"PATTERN_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"ENTITY_PATTERN\\\"}]}],"
			"\\\"DESCRIPTION_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"DESC\\\"}]}],"
			"\\\"CHARACTERISTIC_ATTRIBUTE\\\":[],"
			"\\\"TEMPLATE_ATTRIBUTE\\\":[{}]"
		"}"
	"}\"\"\""
"\n";
t_utf8*	toml_object_string = "\
\n	type = 11,\
\n	value = \"{\\\"Label\\\":\\\"NAME\\\",\\\"Attributes\\\":{\\\"PATTERN_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"ENTITY_PATTERN\\\"}]}],\\\"DESCRIPTION_ATTRIBUTE\\\":[{\\\"Values\\\":[{\\\"STRING\\\":\\\"DESC\\\"}]}],\\\"CHARACTERISTIC_ATTRIBUTE\\\":[],\\\"TEMPLATE_ATTRIBUTE\\\":[{}]}}\"\
\n";



t_utf8*	toml_helloworld_min	= "hello=\"world\"";
t_utf8*	toml_helloworld		= "hello = \"world\"";

t_utf8*	toml_whitespace		= "  hello  =  \"world\"  ";
t_utf8*	toml_whitespace_tab	= "\thello\t=\t\"world\"\t";
t_utf8*	toml_whitespace_nl	= "\nhello\n=\n\"world\"\t";
t_utf8*	toml_whitespace_cr	= "\rhello\r=\r\"world\"\r";
t_utf8*	toml_whitespace_ff	= "\fhello\f=\f\"world\"\f";
t_utf8*	toml_whitespace_vt	= "\vhello\v=\v\"world\"\v";
t_utf8*	toml_whitespace_all	= "\t\f\r\n\"hello\"\t\f\r\n=\t\f\r\n\"world\"\t\f\r\n";

t_utf8*	toml_strange_sot	= "\1hello=\1\"world\"\1\n";
t_utf8*	toml_strange_stx	= "\2hello=\2\"world\"\2\n";
t_utf8*	toml_strange_etx	= "\3hello=\3\"world\"\3\n";
t_utf8*	toml_strange_eot	= "\4hello=\4\"world\"\4\n";
t_utf8*	toml_strange_esc	= "\ehello=\e\"world\"\e\n";
t_utf8*	toml_strange_bs		= "\bhello=\b\"world\"\b\n";

t_utf8*	toml_escape_sq1	= "[\".\\\'.\"]";
t_utf8*	toml_escape_sq2	= "[\".\\\".\"]";
t_utf8*	toml_escape_slb	= "[\".\\\\.\"]";
t_utf8*	toml_escape_slf	= "[\".\\/.\"]";
t_utf8*	toml_escape_spc	= "[\".\\ .\"]";
t_utf8*	toml_escape_tab	= "[\".\\t.\"]";
t_utf8*	toml_escape_nl	= "[\".\\n.\"]";
t_utf8*	toml_escape_cr	= "[\".\\r.\"]";
t_utf8*	toml_escape_ff	= "[\".\\f.\"]";
t_utf8*	toml_escape_vt	= "[\".\\v.\"]";
t_utf8*	toml_escape_esc	= "[\".\\e.\"]";
t_utf8*	toml_escape_bel	= "[\".\\a.\"]";
t_utf8*	toml_escape_bs	= "[\".\\b.\"]";



t_utf8*	toml_simple_min =
"\n""test_bool_0=false"
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
"\n";
t_utf8*	toml_simple = "\
\n	test_bool_0 = false\
\n	test_bool_1 = true\
\n	test_number = 0\
\n	test_string = \"\"\
\n	test_arrays = \
\n	[\
\n		false,\
\n		true,\
\n		0,\
\n		\"\"\
\n	]\
\n	[test_object]\
\n		nest_bool_0 = false\
\n		nest_bool_1 = true\
\n		nest_number = 0\
\n		nest_string = \"\"\
\n		nest_arrays = \
\n		[\
\n			123456,\
\n			\"hello\"\
\n		]\
\n		nest_object = null\
\n";



t_utf8*	toml_commas_min =
"\n""test_bool_0=false"
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
"\n";
t_utf8*	toml_commas = "\
\n	test_bool_0 = false\
\n	test_bool_1 = true\
\n	test_number = 0\
\n	test_string = \"\"\
\n	test_arrays = \
\n	[\
\n		false,\
\n		true,\
\n		0,\
\n		\"\",\
\n	]\
\n	[test_object]\
\n		nest_bool_0 = false\
\n		nest_bool_1 = true\
\n		nest_number = 0\
\n		nest_string = \"\"\
\n		nest_arrays = \
\n		[\
\n			123456,\
\n			\"hello\",\
\n		]\
\n		nest_object = null\
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



t_utf8*	toml_complex_min =
	"[Attributes]"
		"\n[[Attributes.SEX_ATTRIBUTE]]"
		"\n[[Attributes.SEX_ATTRIBUTE.Values]]"			"\nCHARACTER=\"M\""
		"\n[[Attributes.AGE_ATTRIBUTE]]"
		"\n[[Attributes.AGE_ATTRIBUTE.Values]]"			"\nINTEGER=\"82\""
		"\n[[Attributes.SPOUSE_ATTRIBUTE]]"
		"\n[[Attributes.SPOUSE_ATTRIBUTE.Values]]"		"\nBOOLEAN=\"FALSE\""
		"\n[[Attributes.HEIGHT_ATTRIBUTE]]"
		"\n[[Attributes.HEIGHT_ATTRIBUTE.Values]]"		"\nFLOAT=\"176.5\""
		"\n[[Attributes.OCCUPATION_ATTRIBUTE]]"
		"\n[[Attributes.OCCUPATION_ATTRIBUTE.Values]]"	"\nSTRING=\"actor\""
		"\n[[Attributes.LABEL_ATTRIBUTE]]"
		"\n[[Attributes.LABEL_ATTRIBUTE.Values]]"		"\nTEXT=\"Яцк Ничолсон\""
		"\n[[Attributes.BIRTHDAY_ATTRIBUTE]]"
		"\n[[Attributes.BIRTHDAY_ATTRIBUTE.Values]]"	"\nTIME=\"-1031788800\""
		"\n[[Attributes.DOCUMENT_ATTRIBUTE]]"
		"\n[[Attributes.DOCUMENT_ATTRIBUTE.Values]]"	"\nWEB=\"urn:isbn:0393350967\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE]]"
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=72\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n[[\"listed\",\"\",\"\"]]"
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=160\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]"
		"\n[[Attributes.LOCATION_ATTRIBUTE]]"
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Los Angeles\""
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Aspen\""
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Malibu\""
		"\n[[Attributes.CHILD_ATTRIBUTE]]"				
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Jennifer\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]"
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Caleb\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]"
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Honey\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Lorraine\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Raymond\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]"
	"\n[Properties]"
		"\n[\"known for\",\"most popular role\",\"The Shining\"]"
		"\n[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"]"
		"\n[\"fan of\",\"\",\"Bob Dylan\"]"
		"\n[\"also known for\",\"best performance\",\"Chinatown\"]"
	"\n[Values]"
		"\n[\"actor\",\"player\",\"filmmaker\"]"
;
t_utf8*	toml_complex =
	"[Attributes]"
		"\n[[Attributes.SEX_ATTRIBUTE]]"
		"\n[[Attributes.SEX_ATTRIBUTE.Values]]"			"\nCHARACTER=\"M\""
		"\n[[Attributes.AGE_ATTRIBUTE]]"
		"\n[[Attributes.AGE_ATTRIBUTE.Values]]"			"\nINTEGER=\"82\""
		"\n[[Attributes.SPOUSE_ATTRIBUTE]]"
		"\n[[Attributes.SPOUSE_ATTRIBUTE.Values]]"		"\nBOOLEAN=\"FALSE\""
		"\n[[Attributes.HEIGHT_ATTRIBUTE]]"
		"\n[[Attributes.HEIGHT_ATTRIBUTE.Values]]"		"\nFLOAT=\"176.5\""
		"\n[[Attributes.OCCUPATION_ATTRIBUTE]]"
		"\n[[Attributes.OCCUPATION_ATTRIBUTE.Values]]"	"\nSTRING=\"actor\""
		"\n[[Attributes.LABEL_ATTRIBUTE]]"
		"\n[[Attributes.LABEL_ATTRIBUTE.Values]]"		"\nTEXT=\"Яцк Ничолсон\""
		"\n[[Attributes.BIRTHDAY_ATTRIBUTE]]"
		"\n[[Attributes.BIRTHDAY_ATTRIBUTE.Values]]"	"\nTIME=\"-1031788800\""
		"\n[[Attributes.DOCUMENT_ATTRIBUTE]]"
		"\n[[Attributes.DOCUMENT_ATTRIBUTE.Values]]"	"\nWEB=\"urn:isbn:0393350967\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE]]"
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=72\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n[[\"listed\",\"\",\"\"]]"
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Values]]"		"\n\"INTEGER=160\""
		"\n[[Attributes.WEIGHT_ATTRIBUTE.Properties]]"	"\n[[\"reported\",\"\",\"\"],[\"pounds\",\"lbs\",\"352\"]]"
		"\n[[Attributes.LOCATION_ATTRIBUTE]]"
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Los Angeles\""
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Aspen\""
		"\n[[Attributes.LOCATION_ATTRIBUTE.Values]]"	"\nTEXT=\"Malibu\""
		"\n[[Attributes.CHILD_ATTRIBUTE]]"				
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Jennifer\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"\",\"1963\"],[\"Mother\",\"\",\"Sandra Knight\"]]"
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Caleb\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"\",\"1970\"],[\"Paternity\",\"open question 2\",\"not established\"],[\"Mother\",\"\",\"Susan Anspach\"]]"
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Honey\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Lorraine\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Values]]"		"\nTEXT=\"Raymond\""
		"\n[[Attributes.CHILD_ATTRIBUTE.Properties]]"	"\n[[\"Born\",\"youngest\",\"1992\"],[\"Mother\",\"\",\"Rebecca Broussard\"]"
	"\n[Properties]"
		"\n[\"known for\",\"most popular role\",\"The Shining\"]"
		"\n[\"fan of\",\"famous fan\",\"Los Angeles Lakers\"]"
		"\n[\"fan of\",\"\",\"Bob Dylan\"]"
		"\n[\"also known for\",\"best performance\",\"Chinatown\"]"
	"\n[Values]"
		"\n[\"actor\",\"player\",\"filmmaker\"]"
;



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
void	print_test_toml_##STRICT##_##MINIFY(char const* test_name, int can_segfault,\
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
/*	| TEST FUNCTION                    | TEST NAME                                          | CAN SEGV   | EXPECTING                              | TEST ARGS					*/	\
	print_test_toml_##STRICT##_##MINIFY("null pointer              ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									NULL);							\
	print_test_toml_##STRICT##_##MINIFY("empty string              ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									"");							\
	print_test_toml_##STRICT##_##MINIFY("toml_null                 ("#STRICT" -> "#MINIFY")", FALSE,		toml_null##_MIN,						toml_null);						\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_0               ("#STRICT" -> "#MINIFY")", FALSE,		toml_bool_0##_MIN,						toml_bool_0);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bool_1               ("#STRICT" -> "#MINIFY")", FALSE,		toml_bool_1##_MIN,						toml_bool_1);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_0             ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_0##_MIN,					toml_number_0);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_1             ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_1##_MIN,					toml_number_1);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_2             ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_2##_MIN,					toml_number_2);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_3             ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_3##_MIN,					toml_number_3);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_4             ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_4##_MIN,					toml_number_4);					\
	print_test_toml_##STRICT##_##MINIFY("toml_number_0f            ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_0##_MIN,					toml_number_0f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_1f            ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_1##_MIN,					toml_number_1f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_2f            ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_2##_MIN,					toml_number_2f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_3f            ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_3##_MIN,					toml_number_3f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_4f            ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_4##_MIN,					toml_number_4f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_0f1           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_0##_MIN,					toml_number_0f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_1f1           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_1##_MIN,					toml_number_1f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_2f1           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_2##_MIN,					toml_number_2f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_3f1           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_3##_MIN,					toml_number_3f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_4f1           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_4f1##_MIN,					toml_number_4f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_0f2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_0##_MIN,					toml_number_0f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_1f2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_1##_MIN,					toml_number_1f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_2f2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_2##_MIN,					toml_number_2f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_3f2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_3##_MIN,					toml_number_3f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_4f2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_4f2##_MIN,					toml_number_4f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_0f3           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_0##_MIN,					toml_number_0f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_1f3           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_1##_MIN,					toml_number_1f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_2f3           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_2##_MIN,					toml_number_2f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_3f3           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_3##_MIN,					toml_number_3f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_4f3           ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_4f3##_MIN,					toml_number_4f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmin_lt       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmin_lt##_MIN,				toml_number_fmin_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmin_eq       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmin_eq##_MIN,				toml_number_fmin_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmin_gt       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmin_eq##_MIN,				toml_number_fmin_gt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmax_lt       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmax_lt##_MIN,				toml_number_fmax_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmax_eq       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmax_eq##_MIN,				toml_number_fmax_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_fmax_gt       ("#STRICT" -> "#MINIFY")", FALSE,		toml_number_fmax_eq##_MIN,				toml_number_fmax_gt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_lower_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_lower_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_lower_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_lower_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_lower_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_lower_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_mixed_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_mixed_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_mixed_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_mixed_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_mixed_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_mixed_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_upper_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_u_upper_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_upper_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_number_inf_p_upper_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_upper_1 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_number_inf_n_upper_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_u_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_u_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_p_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_p_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_n_lower_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_n_lower_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_u_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_u_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_p_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_p_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_n_mixed_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_n_mixed_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_u_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_u_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_p_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_p_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_nan_n_upper_0 ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_number_nan_n_upper_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_u_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_p_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_utf8_0  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_n_utf8_0);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_u_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_u_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_p_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_p_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_number_inf_n_utf8_1  ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_number_inf_n_utf8_1);		\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_empty         ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_bigint_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_0             ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_0##_MIN:NULL,				toml_bigint_0);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_1             ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_1##_MIN:NULL,				toml_bigint_1);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_2             ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_2##_MIN:NULL,				toml_bigint_2);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_3             ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_3##_MIN:NULL,				toml_bigint_3);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_4             ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_4##_MIN:NULL,				toml_bigint_4);					\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_0f            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_0##_MIN:NULL,				toml_bigint_0f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_1f            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_1##_MIN:NULL,				toml_bigint_1f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_2f            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_2##_MIN:NULL,				toml_bigint_2f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_3f            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_3##_MIN:NULL,				toml_bigint_3f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_4f            ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_4##_MIN:NULL,				toml_bigint_4f);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_0f1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_0##_MIN:NULL,				toml_bigint_0f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_1f1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_1##_MIN:NULL,				toml_bigint_1f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_2f1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_2##_MIN:NULL,				toml_bigint_2f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_3f1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_3##_MIN:NULL,				toml_bigint_3f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_4f1           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_4##_MIN:NULL,				toml_bigint_4f1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_0f2           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_0##_MIN:NULL,				toml_bigint_0f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_1f2           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_1##_MIN:NULL,				toml_bigint_1f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_2f2           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_2##_MIN:NULL,				toml_bigint_2f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_3f2           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_3##_MIN:NULL,				toml_bigint_3f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_4f2           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_4##_MIN:NULL,				toml_bigint_4f2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_0f3           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_0##_MIN:NULL,				toml_bigint_0f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_1f3           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_1##_MIN:NULL,				toml_bigint_1f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_2f3           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_2##_MIN:NULL,				toml_bigint_2f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_3f3           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_3##_MIN:NULL,				toml_bigint_3f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_4f3           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_4##_MIN:NULL,				toml_bigint_4f3);				\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmin_lt       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmin_lt##_MIN:NULL,			toml_bigint_fmin_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmin_eq       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmin_eq##_MIN:NULL,			toml_bigint_fmin_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmin_gt       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmin_gt##_MIN:NULL,			toml_bigint_fmin_gt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmax_lt       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmax_lt##_MIN:NULL,			toml_bigint_fmax_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmax_eq       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmax_eq##_MIN:NULL,			toml_bigint_fmax_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_fmax_gt       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_fmax_gt##_MIN:NULL,			toml_bigint_fmax_gt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64min_lt     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64min_lt##_MIN:NULL,		toml_bigint_s64min_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64min_eq     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64min_eq##_MIN:NULL,		toml_bigint_s64min_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64min_gt     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64max_eq##_MIN:NULL,		toml_bigint_s64min_gt);/*TODO*/	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64max_lt     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64max_lt##_MIN:NULL,		toml_bigint_s64max_lt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64max_eq     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64max_eq##_MIN:NULL,		toml_bigint_s64max_eq);			\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_s64max_gt     ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_bigint_s64min_eq##_MIN:NULL,		toml_bigint_s64max_gt);/*TODO*/	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_uinf_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_bigint_bad_uinf_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_uinf_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_bigint_bad_uinf_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_ninf_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_bigint_bad_ninf_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_ninf_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_n_lower_0##_MIN:NULL,	toml_bigint_bad_ninf_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_pinf_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_bigint_bad_pinf_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_pinf_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_inf_p_lower_0##_MIN:NULL,	toml_bigint_bad_pinf_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_unan_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_unan_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_unan_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_unan_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_nnan_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_nnan_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_nnan_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_nnan_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_pnan_lower("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_pnan_lower);	\
	print_test_toml_##STRICT##_##MINIFY("toml_bigint_bad_pnan_upper("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_number_nan_u_lower_0##_MIN:NULL,	toml_bigint_bad_pnan_upper);	\
	print_test_toml_##STRICT##_##MINIFY("toml_string_empty         ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_empty##_MIN,				toml_string_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string               ("#STRICT" -> "#MINIFY")", FALSE,		toml_string##_MIN,						toml_string);					\
	print_test_toml_##STRICT##_##MINIFY("toml_string_cc_c0         ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_cc_c0##_MIN,				toml_string_cc_c0);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string_cc_c1         ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_cc_c1##_MIN,				toml_string_cc_c1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_fr       ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_utf8_fr##_MIN,				toml_string_utf8_fr);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_ru       ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_utf8_ru##_MIN,				toml_string_utf8_ru);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_jp       ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_utf8_jp##_MIN,				toml_string_utf8_jp);			\
	print_test_toml_##STRICT##_##MINIFY("toml_string_utf8_ho       ("#STRICT" -> "#MINIFY")", FALSE,		toml_string_utf8_ho##_MIN,				toml_string_utf8_ho);			\
	print_test_toml_##STRICT##_##MINIFY("toml_array_empty          ("#STRICT" -> "#MINIFY")", FALSE,		toml_array_empty,						toml_array_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array                ("#STRICT" -> "#MINIFY")", FALSE,		toml_array##_MIN,						toml_array);					\
	print_test_toml_##STRICT##_##MINIFY("toml_array_min            ("#STRICT" -> "#MINIFY")", FALSE,		toml_array##_MIN,						toml_array_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array_nested         ("#STRICT" -> "#MINIFY")", FALSE,		toml_array_nested##_MIN,				toml_array_nested);				\
	print_test_toml_##STRICT##_##MINIFY("toml_array_nested_min     ("#STRICT" -> "#MINIFY")", FALSE,		toml_array_nested##_MIN,				toml_array_nested_min);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_empty         ("#STRICT" -> "#MINIFY")", FALSE,		toml_object_empty,						toml_object_empty);				\
	print_test_toml_##STRICT##_##MINIFY("toml_object               ("#STRICT" -> "#MINIFY")", FALSE,		toml_object##_MIN,						toml_object);					\
	print_test_toml_##STRICT##_##MINIFY("toml_object_min           ("#STRICT" -> "#MINIFY")", FALSE,		toml_object##_MIN,						toml_object_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested        ("#STRICT" -> "#MINIFY")", FALSE,		toml_object_nested##_MIN,				toml_object_nested);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		toml_object_nested##_MIN,				toml_object_nested_min);		\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		toml_object_string##_MIN,				toml_object_string);			\
	print_test_toml_##STRICT##_##MINIFY("toml_object_nested_min    ("#STRICT" -> "#MINIFY")", FALSE,		toml_object_string##_MIN,				toml_object_string_min);		\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace           ("#STRICT" -> "#MINIFY")", FALSE,		toml_helloworld##_MIN,					toml_whitespace);				\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_tab       ("#STRICT" -> "#MINIFY")", FALSE,		toml_helloworld##_MIN,					toml_whitespace_tab);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_nl        ("#STRICT" -> "#MINIFY")", FALSE,		toml_helloworld##_MIN,					toml_whitespace_nl);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_cr        ("#STRICT" -> "#MINIFY")", FALSE,		toml_helloworld##_MIN,					toml_whitespace_cr);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_ff        ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_ff);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_vt        ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_vt);			\
	print_test_toml_##STRICT##_##MINIFY("toml_whitespace_all       ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_helloworld##_MIN:NULL,				toml_whitespace_all);			\
	print_test_toml_##STRICT##_##MINIFY("toml_simple               ("#STRICT" -> "#MINIFY")", FALSE,		toml_simple##_MIN,						toml_simple);					\
	print_test_toml_##STRICT##_##MINIFY("toml_simple_min           ("#STRICT" -> "#MINIFY")", FALSE,		toml_simple##_MIN,						toml_simple_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_commas               ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_simple##_MIN:NULL,					toml_commas);					\
	print_test_toml_##STRICT##_##MINIFY("toml_commas_min           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_simple##_MIN:NULL,					toml_commas_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_newline              ("#STRICT" -> "#MINIFY")", FALSE,		toml_simple##_MIN,						toml_newline);					\
	print_test_toml_##STRICT##_##MINIFY("toml_complex              ("#STRICT" -> "#MINIFY")", FALSE,		toml_complex##_MIN,						toml_complex);					\
	print_test_toml_##STRICT##_##MINIFY("toml_complex_min          ("#STRICT" -> "#MINIFY")", FALSE,		toml_complex##_MIN,						toml_complex_min);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_sq1           ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_escape_sq1);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_sq2           ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_sq2,						toml_escape_sq2);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_slb           ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_slb,						toml_escape_slb);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_slf           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_escape_slf:"[\"test:/.\"]",		toml_escape_slf);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_spc           ("#STRICT" -> "#MINIFY")", FALSE,NSTRICT?toml_escape_spc:NULL,					toml_escape_spc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_tab           ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_tab,						toml_escape_tab);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_nl            ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_nl,							toml_escape_nl);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_cr            ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_cr,							toml_escape_cr);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_ff            ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_ff,							toml_escape_ff);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_vt            ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_escape_vt);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_esc           ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_escape_esc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_bel           ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_escape_bel);				\
	print_test_toml_##STRICT##_##MINIFY("toml_escape_bs            ("#STRICT" -> "#MINIFY")", FALSE,		toml_escape_bs,							toml_escape_bs);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_sot          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_sot);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_stx          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_stx);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_etx          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_etx);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_eot          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_eot);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_esc          ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_esc);				\
	print_test_toml_##STRICT##_##MINIFY("toml_strange_bs           ("#STRICT" -> "#MINIFY")", FALSE,		NULL,									toml_strange_bs);				\
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

//	test_toml_Lenient_Pretty();
	test_toml_Lenient_Minify();
//	test_toml_Strict_Pretty();
//	test_toml_Strict_Minify();

	return (OK);
}
