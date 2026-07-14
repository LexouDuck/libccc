
#include "libccc/encode/yaml.h"

#include "test.h"
#include "test_utils.h"



//! Defines a canonical YAML output value, in both `Pretty` (block) and `Minify` (flow) style
#define YAML_CANON(NAME, PRETTY, MIN) \
	t_utf8 const*	NAME		= PRETTY; \
	t_utf8 const*	NAME##_min	= MIN; \




/*============================================================================*\
||                              Testing Variables                             ||
\*============================================================================*/

// canonical scalar values (these also serve as parser inputs, where possible)

YAML_CANON(yaml_null			, "null\n"				, "null")
YAML_CANON(yaml_bool_1		, "true\n"				, "true")
YAML_CANON(yaml_bool_0		, "false\n"			, "false")

YAML_CANON(yaml_int_0			, "0\n"					, "0")
YAML_CANON(yaml_int_42		, "42\n"					, "42")
YAML_CANON(yaml_int_neg42		, "-42\n"				, "-42")
YAML_CANON(yaml_int_s64max		, "9223372036854775807\n"	, "9223372036854775807")
YAML_CANON(yaml_int_s64min		, "-9223372036854775808\n"	, "-9223372036854775808")

YAML_CANON(yaml_float_0			, "0.0\n"				, "0.0")
YAML_CANON(yaml_float_1_5		, "1.5\n"				, "1.5")
YAML_CANON(yaml_float_neg		, "-3.25\n"			, "-3.25")
YAML_CANON(yaml_float_exp		, "601999999999999995805696.0\n", "601999999999999995805696.0")
YAML_CANON(yaml_float_expneg	, "0.0015\n"			, "0.0015")
YAML_CANON(yaml_float_inf		, ".inf\n"				, ".inf")
YAML_CANON(yaml_float_ninf		, "-.inf\n"			, "-.inf")
YAML_CANON(yaml_float_nan		, ".nan\n"				, ".nan")

YAML_CANON(yaml_string			, "hello\n"			, "hello")
YAML_CANON(yaml_string_space	, "hello world\n"		, "hello world")
YAML_CANON(yaml_string_apos	, "it's\n"				, "it's")
YAML_CANON(yaml_string_quotes	, "say \"hi\"\n"			, "say \"hi\"")
YAML_CANON(yaml_string_bslash	, "a\\b\n"				, "a\\b")
YAML_CANON(yaml_string_utf8	, "h\xC3\xA9llo\n"			, "h\xC3\xA9llo")
YAML_CANON(yaml_string_eacute	, "\xC3\xA9\n"				, "\xC3\xA9")
YAML_CANON(yaml_string_esc_nl	, "\"a\\nb\"\n"			, "\"a\\nb\"")
YAML_CANON(yaml_string_esc_tab	, "\"a\\tb\"\n"			, "\"a\\tb\"")
YAML_CANON(yaml_string_ctrl	, "a: \"\\u0001\"\n"		, "{a: \"\\u0001\"}")
YAML_CANON(yaml_string_42		, "\"42\"\n"				, "\"42\"")
// strings which look like lenient-only booleans/floats are printed quoted, so that they stay strings
YAML_CANON(yaml_string_yes		, "\"yes\"\n"			, "\"yes\"")
YAML_CANON(yaml_string_no		, "\"no\"\n"				, "\"no\"")
YAML_CANON(yaml_string_on		, "\"on\"\n"				, "\"on\"")
YAML_CANON(yaml_string_off		, "\"off\"\n"			, "\"off\"")
YAML_CANON(yaml_string_inf		, "inf\n"				, "inf")
YAML_CANON(yaml_string_nan		, "nan\n"				, "nan")

// canonical collection values (these also serve as parser inputs, where possible)

YAML_CANON(yaml_map_simple		, "hello: world\n"					, "{hello: world}")
YAML_CANON(yaml_map_a1			, "a: 1\n"							, "{a: 1}")
YAML_CANON(yaml_map_a1_nested	, "a:\n  b: 1\n"						, "{a: {b: 1}}")
YAML_CANON(yaml_map_two			, "a: 1\nb: 2\n"						, "{a: 1,b: 2}")
YAML_CANON(yaml_map_nested		, "a:\n  b: 1\n  c: 2\n"				, "{a: {b: 1,c: 2}}")
YAML_CANON(yaml_map_nested2		, "a:\n  b:\n    c: deep\n"			, "{a: {b: {c: deep}}}")
YAML_CANON(yaml_map_nullval		, "a: null\nb: 1\n"					, "{a: null,b: 1}")
YAML_CANON(yaml_map_spacekey	, "my key: 1\n"						, "{my key: 1}")
YAML_CANON(yaml_map_ambig		, "hello: \"world: what\"\n"			, "{hello: \"world: what\"}")

YAML_CANON(yaml_seq_abc			, "- a\n- b\n- c\n"					, "[a,b,c]")
YAML_CANON(yaml_seq_123			, "- 1\n- 2\n- 3\n"					, "[1,2,3]")
YAML_CANON(yaml_seq_12			, "- 1\n- 2\n"						, "[1,2]")
YAML_CANON(yaml_seq_nested		, "- - 1\n  - 2\n- 3\n"				, "[[1,2],3]")
YAML_CANON(yaml_seq_maps		, "- a: 1\n- b: 2\n"					, "[{a: 1},{b: 2}]")
YAML_CANON(yaml_seq_compact		, "- a: 1\n  b: 2\n- c: 3\n"			, "[{a: 1,b: 2},{c: 3}]")
YAML_CANON(yaml_seq_flowmix		, "- a: 1\n- - 2\n  - 3\n"				, "[{a: 1},[2,3]]")
YAML_CANON(yaml_map_seq			, "list:\n  - 1\n  - 2\n"				, "{list: [1,2]}")
YAML_CANON(yaml_flow_in_block	, "key:\n  - 1\n  - 2\n"				, "{key: [1,2]}")
YAML_CANON(yaml_seq_flowstr		, "- a\n- b c\n- \"d\\ne\"\n"			, "[a,b c,\"d\\ne\"]")
YAML_CANON(yaml_arr_empty		, "[]\n"							, "[]")
YAML_CANON(yaml_obj_empty		, "{}\n"							, "{}")

YAML_CANON(yaml_block_lit		, "s: \"line1\\nline2\\n\"\n"			, "{s: \"line1\\nline2\\n\"}")
YAML_CANON(yaml_block_strip		, "s: \"line1\\nline2\"\n"				, "{s: \"line1\\nline2\"}")
YAML_CANON(yaml_block_keep		, "s: \"line1\\n\\n\"\n"					, "{s: \"line1\\n\\n\"}")
YAML_CANON(yaml_block_fold		, "s: \"line1 line2\\n\"\n"				, "{s: \"line1 line2\\n\"}")

// non-canonical parser inputs (these get normalized when printed back out)

t_utf8 const*	yaml_in_null_tilde		= "~";
t_utf8 const*	yaml_in_bool_1_mixed	= "True";
t_utf8 const*	yaml_in_bool_1_yes		= "yes";
t_utf8 const*	yaml_in_bool_0_no		= "no";
t_utf8 const*	yaml_in_bool_1_on		= "on";
t_utf8 const*	yaml_in_bool_0_off		= "off";
t_utf8 const*	yaml_in_int_pos42		= "+42";
t_utf8 const*	yaml_in_int_hex			= "0x2A";
t_utf8 const*	yaml_in_int_oct			= "0o52";
t_utf8 const*	yaml_in_int_bin			= "0b101010";
t_utf8 const*	yaml_in_float_exp		= "6.02e23";
t_utf8 const*	yaml_in_float_expneg	= "1.5e-3";
t_utf8 const*	yaml_in_float_inf		= "inf";
t_utf8 const*	yaml_in_float_nan		= "nan";
t_utf8 const*	yaml_in_str_sq			= "'hello world'";
t_utf8 const*	yaml_in_str_sq_esc		= "'it''s'";
t_utf8 const*	yaml_in_str_dq			= "\"hello\"";
t_utf8 const*	yaml_in_str_dq_quot	= "\"say \\\"hi\\\"\"";
t_utf8 const*	yaml_in_str_dq_bslash	= "\"a\\\\b\"";
t_utf8 const*	yaml_in_str_dq_u16		= "\"\\u00e9\"";
t_utf8 const*	yaml_in_str_sq_42		= "'42'";
t_utf8 const*	yaml_in_str_ambig		= "hello: world: what";
t_utf8 const*	yaml_in_ctrlchar		= "a: \x01\n";
t_utf8 const*	yaml_in_map_key_dq		= "\"my key\": 1\n";
t_utf8 const*	yaml_in_map_key_sq		= "'my key': 1\n";
t_utf8 const*	yaml_in_map_emptyval	= "a:\nb: 1\n";
t_utf8 const*	yaml_in_map_tabindent	= "a:\n\tb: 1\n";
t_utf8 const*	yaml_in_map_dup_keys	= "a: 1\na: 2\n";
t_utf8 const*	yaml_in_seq_inline		= "list:\n- 1\n- 2\n";
t_utf8 const*	yaml_in_seq_wide		= "-\n  - 1\n  - 2\n- 3\n";
t_utf8 const*	yaml_in_flow_arr		= "[1, 2, 3]";
t_utf8 const*	yaml_in_flow_arr_min	= "[1,2,3]";
t_utf8 const*	yaml_in_flow_obj		= "{a: 1, b: 2}";
t_utf8 const*	yaml_in_flow_nested	= "[{a: 1}, [2, 3]]";
t_utf8 const*	yaml_in_flow_in_block	= "key: [1, 2]\n";
t_utf8 const*	yaml_in_flow_str		= "[a, 'b c', \"d\\ne\"]";
t_utf8 const*	yaml_in_flow_trailing	= "[1, 2,]";
t_utf8 const*	yaml_in_comment_full	= "# comment\na: 1\n";
t_utf8 const*	yaml_in_comment_inline	= "a: 1 # comment\n";
t_utf8 const*	yaml_in_comment_only	= "# only a comment\n";
t_utf8 const*	yaml_in_block_lit		= "s: |\n  line1\n  line2\n";
t_utf8 const*	yaml_in_block_strip	= "s: |-\n  line1\n  line2\n";
t_utf8 const*	yaml_in_block_keep		= "s: |+\n  line1\n\n";
t_utf8 const*	yaml_in_block_fold		= "s: >\n  line1\n  line2\n";
t_utf8 const*	yaml_in_doc_start		= "---\na: 1\n";
t_utf8 const*	yaml_in_doc_both		= "---\na: 1\n...\n";
t_utf8 const*	yaml_in_directive		= "%YAML 1.2\n---\na: 1\n";

// invalid parser inputs (unsupported YAML features, and malformed strings)

t_utf8 const*	yaml_in_err_anchor		= "a: &anc 1\n";
t_utf8 const*	yaml_in_err_alias		= "a: *anc\n";
t_utf8 const*	yaml_in_err_tag			= "a: !!str hi\n";
t_utf8 const*	yaml_in_err_complexkey	= "? key\n: value\n";
t_utf8 const*	yaml_in_err_unclosed_sq	= "'unclosed";
t_utf8 const*	yaml_in_err_unclosed_dq	= "\"unclosed";
t_utf8 const*	yaml_in_err_unclosed_fl	= "[1, 2";
t_utf8 const*	yaml_in_err_badindent	= "a:\n  b: 1\n c: 2\n";



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#if !(defined(c_yamlparse) && defined(c_yamlprint))
void test_yaml(void)	{}
#else

#define DEFINETEST_YAML(STRICT, NSTRICT, MINIFY, _MIN) \
static t_utf8*	c_yaml_##STRICT##_##MINIFY(t_utf8* yaml) \
{ \
	s_yaml* tmp = YAML_FromString_##STRICT(yaml); \
	t_utf8* result = YAML_ToString_##MINIFY(tmp); \
	if (tmp != NULL)	YAML_Delete(tmp); \
	return (result); \
} \
void	print_test_yaml_##STRICT##_##MINIFY(char const* test_name, t_testflags flags,\
		char const* expecting, \
		char const* str) \
{ \
	TEST_INIT(str) \
	TEST_PERFORM(	yaml_##STRICT##_##MINIFY, (t_utf8*)str) \
	TEST_PRINT(str,	yaml_##STRICT##_##MINIFY, "str=\"%s\"", str) \
	TEST_FREE() \
} \
void	test_yaml_##STRICT##_##MINIFY(void) \
{ \
/*	| TEST FUNCTION                    | TEST NAME                                          | TESTFLAGS  | EXPECTING                              | TEST ARGS					*/ \
	print_test_yaml_##STRICT##_##MINIFY("null pointer               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									NULL); \
	print_test_yaml_##STRICT##_##MINIFY("empty string               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									""); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_null                  ("#STRICT" -> "#MINIFY")",FALSE,		yaml_null##_MIN,						yaml_null); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_null_tilde            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_null##_MIN,						yaml_in_null_tilde); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_1                ("#STRICT" -> "#MINIFY")",FALSE,		yaml_bool_1##_MIN,					yaml_bool_1); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_0                ("#STRICT" -> "#MINIFY")",FALSE,		yaml_bool_0##_MIN,					yaml_bool_0); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_1_mixed          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_bool_1##_MIN,					yaml_in_bool_1_mixed); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_1_yes            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_bool_1##_MIN:yaml_string_yes##_MIN,		yaml_in_bool_1_yes); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_0_no             ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_bool_0##_MIN:yaml_string_no##_MIN,		yaml_in_bool_0_no); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_1_on             ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_bool_1##_MIN:yaml_string_on##_MIN,		yaml_in_bool_1_on); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_bool_0_off            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_bool_0##_MIN:yaml_string_off##_MIN,		yaml_in_bool_0_off); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_0                 ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_0##_MIN,					yaml_int_0); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_42                ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_42##_MIN,					yaml_int_42); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_neg42             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_neg42##_MIN,				yaml_int_neg42); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_pos42             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_42##_MIN,					yaml_in_int_pos42); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_hex               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_42##_MIN,					yaml_in_int_hex); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_oct               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_42##_MIN,					yaml_in_int_oct); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_bin               ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_int_42##_MIN:NULL,				yaml_in_int_bin); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_s64max            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_s64max##_MIN,				yaml_int_s64max); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_int_s64min            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_int_s64min##_MIN,				yaml_int_s64min); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_0               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_0##_MIN,					yaml_float_0); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_1_5             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_1_5##_MIN,				yaml_float_1_5); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_neg             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_neg##_MIN,				yaml_float_neg); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_exp             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_exp##_MIN,				yaml_in_float_exp); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_expneg          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_expneg##_MIN,			yaml_in_float_expneg); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_inf             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_inf##_MIN,				yaml_float_inf); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_ninf            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_ninf##_MIN,				yaml_float_ninf); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_nan             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_float_nan##_MIN,				yaml_float_nan); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_inf_nodot       ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_float_inf##_MIN:yaml_string_inf##_MIN,	yaml_in_float_inf); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_float_nan_nodot       ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_float_nan##_MIN:yaml_string_nan##_MIN,	yaml_in_float_nan); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string                ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string##_MIN,					yaml_string); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_space          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_space##_MIN,			yaml_string_space); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_sq             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_space##_MIN,			yaml_in_str_sq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_sq_esc         ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_apos##_MIN,			yaml_in_str_sq_esc); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_dq             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string##_MIN,					yaml_in_str_dq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_esc_nl         ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_esc_nl##_MIN,			yaml_string_esc_nl); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_esc_tab        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_esc_tab##_MIN,			yaml_string_esc_tab); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_esc_quot       ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_quotes##_MIN,			yaml_in_str_dq_quot); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_esc_bslash     ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_bslash##_MIN,			yaml_in_str_dq_bslash); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_esc_unicode    ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_eacute##_MIN,			yaml_in_str_dq_u16); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_utf8           ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_utf8##_MIN,			yaml_string_utf8); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_42             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_42##_MIN,				yaml_in_str_sq_42); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_string_ctrlchar       ("#STRICT" -> "#MINIFY")",FALSE,		yaml_string_ctrl##_MIN,			yaml_in_ctrlchar); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_ambig             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_ambig##_MIN,				yaml_in_str_ambig); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_simple            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_simple##_MIN,				yaml_map_simple); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_two               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_two##_MIN,					yaml_map_two); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_nested            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_nested##_MIN,				yaml_map_nested); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_nested2           ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_nested2##_MIN,				yaml_map_nested2); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_emptyval          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_nullval##_MIN,				yaml_in_map_emptyval); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_key_dq            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_spacekey##_MIN,			yaml_in_map_key_dq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_key_sq            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_spacekey##_MIN,			yaml_in_map_key_sq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_tab_indent        ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_map_a1_nested##_MIN:NULL,		yaml_in_map_tabindent); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_dup_keys          ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_map_dup_keys); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_seq_abc               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_abc##_MIN,					yaml_seq_abc); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_seq_123               ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_123##_MIN,					yaml_seq_123); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_seq_nested            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_nested##_MIN,				yaml_in_seq_wide); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_seq_of_maps           ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_maps##_MIN,				yaml_seq_maps); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_seq_compact           ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_compact##_MIN,			yaml_seq_compact); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_of_seq            ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_seq##_MIN,					yaml_map_seq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_map_seq_inline        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_seq##_MIN,					yaml_in_seq_inline); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_arr              ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_123##_MIN,					yaml_in_flow_arr); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_arr_min          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_123##_MIN,					yaml_in_flow_arr_min); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_arr_empty        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_arr_empty##_MIN,				yaml_arr_empty); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_obj              ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_two##_MIN,					yaml_in_flow_obj); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_obj_empty        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_obj_empty##_MIN,				yaml_obj_empty); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_nested           ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_flowmix##_MIN,				yaml_in_flow_nested); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_in_block         ("#STRICT" -> "#MINIFY")",FALSE,		yaml_flow_in_block##_MIN,			yaml_in_flow_in_block); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_strings          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_seq_flowstr##_MIN,				yaml_in_flow_str); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_flow_trailing_comma   ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?yaml_seq_12##_MIN:NULL,				yaml_in_flow_trailing); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_comment_fullline      ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_a1##_MIN,					yaml_in_comment_full); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_comment_inline        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_a1##_MIN,					yaml_in_comment_inline); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_comment_only          ("#STRICT" -> "#MINIFY")",FALSE,		yaml_null##_MIN,						yaml_in_comment_only); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_blockscalar_literal   ("#STRICT" -> "#MINIFY")",FALSE,		yaml_block_lit##_MIN,				yaml_in_block_lit); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_blockscalar_strip     ("#STRICT" -> "#MINIFY")",FALSE,		yaml_block_strip##_MIN,				yaml_in_block_strip); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_blockscalar_keep      ("#STRICT" -> "#MINIFY")",FALSE,		yaml_block_keep##_MIN,				yaml_in_block_keep); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_blockscalar_folded    ("#STRICT" -> "#MINIFY")",FALSE,		yaml_block_fold##_MIN,				yaml_in_block_fold); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_document_start        ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_a1##_MIN,					yaml_in_doc_start); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_document_both         ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_a1##_MIN,					yaml_in_doc_both); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_directive             ("#STRICT" -> "#MINIFY")",FALSE,		yaml_map_a1##_MIN,					yaml_in_directive); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_anchor            ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_anchor); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_alias             ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_alias); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_tag               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_tag); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_complexkey        ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_complexkey); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_unclosed_sq       ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_unclosed_sq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_unclosed_dq       ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_unclosed_dq); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_unclosed_flow     ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_unclosed_fl); \
	print_test_yaml_##STRICT##_##MINIFY("yaml_err_badindent         ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									yaml_in_err_badindent); \
}
#endif

DEFINETEST_YAML(Lenient, TRUE,	Pretty,)
DEFINETEST_YAML(Lenient, TRUE,	Minify, _min)
DEFINETEST_YAML(Strict, FALSE,	Pretty,)
DEFINETEST_YAML(Strict, FALSE,	Minify, _min)

// TODO test other functions than just Parse/Print



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_encode_yaml(void)
{
	print_suite_title("libccc/encode/yaml");

	print_nonstd();

	test_yaml_Lenient_Pretty();
	test_yaml_Lenient_Minify();
	test_yaml_Strict_Pretty();
	test_yaml_Strict_Minify();

	return (OK);
}
