
#include "libccc/encode/xml.h"

#include "test.h"
#include "test_utils.h"



//! The XML declaration line, printed at the start of any `Pretty` output
#define XML_DECL	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

//! Defines a canonical XML output value, in both `Pretty` (indented) and `Minify` style
#define XML_CANON(NAME, PRETTY, MIN) \
	t_utf8 const*	NAME		= XML_DECL PRETTY; \
	t_utf8 const*	NAME##_min	= MIN; \

//! Defines a canonical XML output value which prints identically on a single line in both styles
#define XML_CANON_1(NAME, STR) \
	t_utf8 const*	NAME		= XML_DECL STR "\n"; \
	t_utf8 const*	NAME##_min	= STR; \




/*============================================================================*\
||                              Testing Variables                             ||
\*============================================================================*/

// canonical single-line documents (these also serve as parser inputs, where possible)

XML_CANON_1(xml_selfclose		, "<a/>")
XML_CANON_1(xml_text			, "<a>hello</a>")
XML_CANON_1(xml_text_spaces	, "<a>hello world</a>")
XML_CANON_1(xml_text_number	, "<a>42</a>")
XML_CANON_1(xml_text_utf8		, "<a>h\xC3\xA9llo</a>")
XML_CANON_1(xml_text_joined	, "<a>x y</a>")
XML_CANON_1(xml_name_ns		, "<ns:a>x</ns:a>")
XML_CANON_1(xml_name_dashdot	, "<a-b.c/>")
XML_CANON_1(xml_ent_all5		, "<a>&lt;&gt;&amp;'\"</a>")
XML_CANON_1(xml_ent_mixed		, "<a>Tom &amp; Jerry</a>")
XML_CANON_1(xml_ent_verbatim	, "<a>&amp;foo;</a>")
XML_CANON_1(xml_ent_amp_raw	, "<a>&amp;amp</a>")
XML_CANON_1(xml_ent_bare_amp	, "<a>a &amp; b</a>")
XML_CANON_1(xml_charref_A		, "<a>A</a>")
XML_CANON_1(xml_charref_utf8	, "<a>\xE2\x80\x94</a>")
XML_CANON_1(xml_charref_nl		, "<a>&#10;</a>")
XML_CANON_1(xml_cdata			, "<a>&lt;raw&gt;&amp;</a>")
XML_CANON_1(xml_cdata_ws		, "<a>&#32; x &#32;</a>")
XML_CANON_1(xml_cdata_brackets	, "<a>a]]b</a>")
XML_CANON_1(xml_cdata_mix		, "<a>befo re</a>")
XML_CANON_1(xml_cdata_end		, "<a>x]]&gt;y</a>")
XML_CANON_1(xml_attr_one		, "<a x=\"1\"/>")
XML_CANON_1(xml_attr_two		, "<a x=\"1\" y=\"2\"/>")
XML_CANON_1(xml_attr_empty		, "<a x=\"\"/>")
XML_CANON_1(xml_attr_2nd		, "<a x=\"2\"/>")
XML_CANON_1(xml_attr_entity	, "<a x=\"&quot;q&quot;\"/>")
XML_CANON_1(xml_attr_apos		, "<a x=\"it's\"/>")
XML_CANON_1(xml_attr_normal	, "<a x=\"a b c\"/>")
XML_CANON_1(xml_attr_escaped	, "<a x=\"a&lt;b\"/>")
XML_CANON_1(xml_attr_and_text	, "<a x=\"1\">hi</a>")

// canonical multi-line documents (whose `Pretty` form differs from the `Minify` form)

XML_CANON(xml_nested			,
	"<a>\n"
	"\t<b>1</b>\n"
	"</a>\n"							, "<a><b>1</b></a>")
XML_CANON(xml_nested_deep		,
	"<a>\n"
	"\t<b>\n"
	"\t\t<c>deep</c>\n"
	"\t</b>\n"
	"</a>\n"							, "<a><b><c>deep</c></b></a>")
XML_CANON(xml_siblings			,
	"<a>\n"
	"\t<b>1</b>\n"
	"\t<c>2</c>\n"
	"</a>\n"							, "<a><b>1</b><c>2</c></a>")
XML_CANON(xml_repeat			,
	"<r>\n"
	"\t<i>1</i>\n"
	"\t<i>2</i>\n"
	"</r>\n"							, "<r><i>1</i><i>2</i></r>")
XML_CANON(xml_repeat_three		,
	"<r>\n"
	"\t<i>1</i>\n"
	"\t<i>2</i>\n"
	"\t<i>3</i>\n"
	"</r>\n"							, "<r><i>1</i><i>2</i><i>3</i></r>")
XML_CANON(xml_repeat_gap		,
	"<r>\n"
	"\t<i>1</i>\n"
	"\t<i>2</i>\n"
	"\t<x/>\n"
	"</r>\n"							, "<r><i>1</i><i>2</i><x/></r>")
XML_CANON(xml_repeat_objects	,
	"<r>\n"
	"\t<i k=\"1\"/>\n"
	"\t<i k=\"2\"/>\n"
	"</r>\n"							, "<r><i k=\"1\"/><i k=\"2\"/></r>")
XML_CANON(xml_mixed			,
	"<p>\n"
	"\thello world\n"
	"\t<b>bold</b>\n"
	"</p>\n"							, "<p>hello world<b>bold</b></p>")
XML_CANON(xml_two_roots		,
	"<root>\n"
	"\t<a/>\n"
	"\t<b/>\n"
	"</root>\n"						, "<root><a/><b/></root>")
XML_CANON(xml_two_roots_same	,
	"<a>1</a>\n"
	"<a>2</a>\n"						, "<a>1</a><a>2</a>")

// non-canonical parser inputs (these get normalized when printed back out)

t_utf8 const*	xml_in_selfclose_sp		= "<a />";
t_utf8 const*	xml_in_empty_pair			= "<a></a>";
t_utf8 const*	xml_in_text_trim			= "<a>  hello  </a>";
t_utf8 const*	xml_in_text_multiline	= "<a>\n\thello\n</a>";
t_utf8 const*	xml_in_text_comment		= "<a>x<!--c-->y</a>";
t_utf8 const*	xml_in_ent_all5			= "<a>&lt;&gt;&amp;&apos;&quot;</a>";
t_utf8 const*	xml_in_charref_dec		= "<a>&#65;</a>";
t_utf8 const*	xml_in_charref_hex		= "<a>&#x41;</a>";
t_utf8 const*	xml_in_charref_hex_uc	= "<a>&#X41;</a>";
t_utf8 const*	xml_in_charref_utf8		= "<a>&#x2014;</a>";
t_utf8 const*	xml_in_ent_unknown		= "<a>&foo;</a>";
t_utf8 const*	xml_in_ent_unterminated	= "<a>&amp</a>";
t_utf8 const*	xml_in_bare_amp			= "<a>a & b</a>";
t_utf8 const*	xml_in_cdata				= "<a><![CDATA[<raw>&]]></a>";
t_utf8 const*	xml_in_cdata_ws			= "<a><![CDATA[  x  ]]></a>";
t_utf8 const*	xml_in_cdata_brackets	= "<a><![CDATA[a]]b]]></a>";
t_utf8 const*	xml_in_cdata_empty		= "<a><![CDATA[]]></a>";
t_utf8 const*	xml_in_cdata_mix			= "<a>be<![CDATA[fo]]>re</a>";
t_utf8 const*	xml_in_cdata_end			= "<a>x]]>y</a>";
t_utf8 const*	xml_in_attr_sq			= "<a x='1'/>";
t_utf8 const*	xml_in_attr_normalize	= "<a x=\"a\nb\tc\"/>";
t_utf8 const*	xml_in_attr_rawlt			= "<a x=\"a<b\"/>";
t_utf8 const*	xml_in_attr_unquoted		= "<a x=1/>";
t_utf8 const*	xml_in_attr_minimized	= "<a x/>";
t_utf8 const*	xml_in_attr_dup			= "<a x=\"1\" x=\"2\"/>";
t_utf8 const*	xml_in_attr_ws_eq			= "<a x = \"1\"/>";
t_utf8 const*	xml_in_ws_between			= "<a>\n\t<b>1</b>\n</a>";
t_utf8 const*	xml_in_comment_before	= "<!--c--><a/>";
t_utf8 const*	xml_in_comment_inside	= "<a><!--c--></a>";
t_utf8 const*	xml_in_comment_dashes	= "<a><!-- a -- b --></a>";
t_utf8 const*	xml_in_decl				= "<?xml version=\"1.0\"?><a/>";
t_utf8 const*	xml_in_pi					= "<?php echo ?><a/>";
t_utf8 const*	xml_in_doctype			= "<!DOCTYPE a><a/>";
t_utf8 const*	xml_in_doctype_system	= "<!DOCTYPE a SYSTEM \"x>y\"><a/>";
t_utf8 const*	xml_in_doctype_subset	= "<!DOCTYPE a [<!ENTITY x \"y\">]><a/>";
t_utf8 const*	xml_in_bom				= "\xEF\xBB\xBF<a/>";
t_utf8 const*	xml_in_epilog_comment	= "<a/><!--after-->";
t_utf8 const*	xml_in_close_tag_space	= "<a></a >";
t_utf8 const*	xml_in_two_roots			= "<a/><b/>";
t_utf8 const*	xml_in_two_roots_same	= "<a>1</a><a>2</a>";

t_utf8 const*	xml_repeat_gap_input	= "<r><i>1</i><x/><i>2</i></r>";
t_utf8 const*	xml_mixed_input		= "<p>hello <b>bold</b> world</p>";

// invalid parser inputs (malformed XML strings)

t_utf8 const*	xml_in_err_text_root	= "hello";
t_utf8 const*	xml_in_err_unclosed		= "<a>";
t_utf8 const*	xml_in_err_mismatch		= "<a></b>";
t_utf8 const*	xml_in_err_crossing		= "<a><b></a></b>";
t_utf8 const*	xml_in_err_garbage		= "<a/>x";
t_utf8 const*	xml_in_err_space_name	= "< a></a>";
t_utf8 const*	xml_in_err_digit_name	= "<1a/>";
t_utf8 const*	xml_in_err_markup		= "<a><!X></a>";
t_utf8 const*	xml_in_err_comment_eof	= "<a><!--never";
t_utf8 const*	xml_in_err_empty_ref	= "<a>&#;</a>";
t_utf8 const*	xml_in_err_attr_nosp	= "<a x=\"1\"y=\"2\"/>";
t_utf8 const*	xml_in_err_gt_in_attr	= "<a x=\"1\">2\"/>";



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



#if !(defined(c_xmlparse) && defined(c_xmlprint))
void test_xml(void)	{}
#else

#define DEFINETEST_XML(STRICT, NSTRICT, MINIFY, _MIN) \
static t_utf8*	c_xml_##STRICT##_##MINIFY(t_utf8* xml) \
{ \
	s_xml* tmp = XML_FromString_##STRICT(xml); \
	t_utf8* result = XML_ToString_##MINIFY(tmp); \
	if (tmp != NULL)	XML_Delete(tmp); \
	return (result); \
} \
void	print_test_xml_##STRICT##_##MINIFY(char const* test_name, t_testflags flags,\
		char const* expecting, \
		char const* str) \
{ \
	TEST_INIT(str) \
	TEST_PERFORM(	xml_##STRICT##_##MINIFY, (t_utf8*)str) \
	TEST_PRINT(str,	xml_##STRICT##_##MINIFY, "str=\"%s\"", str) \
	TEST_FREE() \
} \
void	test_xml_##STRICT##_##MINIFY(void) \
{ \
/*	| TEST FUNCTION                   | TEST NAME                                          | TESTFLAGS  | EXPECTING                              | TEST ARGS					*/ \
	print_test_xml_##STRICT##_##MINIFY("null pointer               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									NULL); \
	print_test_xml_##STRICT##_##MINIFY("empty string               ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									""); \
	print_test_xml_##STRICT##_##MINIFY("xml_selfclose              ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_selfclose); \
	print_test_xml_##STRICT##_##MINIFY("xml_selfclose_space        ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_selfclose_sp); \
	print_test_xml_##STRICT##_##MINIFY("xml_empty_pair             ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_empty_pair); \
	print_test_xml_##STRICT##_##MINIFY("xml_text                   ("#STRICT" -> "#MINIFY")",FALSE,		xml_text##_MIN,						xml_text); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_spaces            ("#STRICT" -> "#MINIFY")",FALSE,		xml_text_spaces##_MIN,				xml_text_spaces); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_trim              ("#STRICT" -> "#MINIFY")",FALSE,		xml_text##_MIN,						xml_in_text_trim); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_multiline         ("#STRICT" -> "#MINIFY")",FALSE,		xml_text##_MIN,						xml_in_text_multiline); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_segments_joined   ("#STRICT" -> "#MINIFY")",FALSE,		xml_text_joined##_MIN,				xml_in_text_comment); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_number            ("#STRICT" -> "#MINIFY")",FALSE,		xml_text_number##_MIN,				xml_text_number); \
	print_test_xml_##STRICT##_##MINIFY("xml_text_utf8              ("#STRICT" -> "#MINIFY")",FALSE,		xml_text_utf8##_MIN,				xml_text_utf8); \
	print_test_xml_##STRICT##_##MINIFY("xml_name_namespace         ("#STRICT" -> "#MINIFY")",FALSE,		xml_name_ns##_MIN,					xml_name_ns); \
	print_test_xml_##STRICT##_##MINIFY("xml_name_dashdot           ("#STRICT" -> "#MINIFY")",FALSE,		xml_name_dashdot##_MIN,				xml_name_dashdot); \
	print_test_xml_##STRICT##_##MINIFY("xml_entities_all5          ("#STRICT" -> "#MINIFY")",FALSE,		xml_ent_all5##_MIN,					xml_in_ent_all5); \
	print_test_xml_##STRICT##_##MINIFY("xml_entities_mixed         ("#STRICT" -> "#MINIFY")",FALSE,		xml_ent_mixed##_MIN,				xml_ent_mixed); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_decimal        ("#STRICT" -> "#MINIFY")",FALSE,		xml_charref_A##_MIN,				xml_in_charref_dec); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_hex            ("#STRICT" -> "#MINIFY")",FALSE,		xml_charref_A##_MIN,				xml_in_charref_hex); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_hex_upper      ("#STRICT" -> "#MINIFY")",FALSE,		xml_charref_A##_MIN,				xml_in_charref_hex_uc); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_utf8           ("#STRICT" -> "#MINIFY")",FALSE,		xml_charref_utf8##_MIN,				xml_in_charref_utf8); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_newline        ("#STRICT" -> "#MINIFY")",FALSE,		xml_charref_nl##_MIN,				xml_charref_nl); \
	print_test_xml_##STRICT##_##MINIFY("xml_charref_empty          ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_empty_ref); \
	print_test_xml_##STRICT##_##MINIFY("xml_entity_unknown         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_ent_verbatim##_MIN:NULL,				xml_in_ent_unknown); \
	print_test_xml_##STRICT##_##MINIFY("xml_entity_unterminated    ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_ent_amp_raw##_MIN:NULL,				xml_in_ent_unterminated); \
	print_test_xml_##STRICT##_##MINIFY("xml_entity_bare_ampersand  ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_ent_bare_amp##_MIN:NULL,				xml_in_bare_amp); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata                  ("#STRICT" -> "#MINIFY")",FALSE,		xml_cdata##_MIN,						xml_in_cdata); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata_whitespace       ("#STRICT" -> "#MINIFY")",FALSE,		xml_cdata_ws##_MIN,					xml_in_cdata_ws); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata_brackets         ("#STRICT" -> "#MINIFY")",FALSE,		xml_cdata_brackets##_MIN,			xml_in_cdata_brackets); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata_empty            ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_cdata_empty); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata_text_mix         ("#STRICT" -> "#MINIFY")",FALSE,		xml_cdata_mix##_MIN,				xml_in_cdata_mix); \
	print_test_xml_##STRICT##_##MINIFY("xml_cdata_end_in_text      ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_cdata_end##_MIN:NULL,				xml_in_cdata_end); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_one               ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_one##_MIN,					xml_attr_one); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_two               ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_two##_MIN,					xml_attr_two); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_singlequote       ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_one##_MIN,					xml_in_attr_sq); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_empty_value       ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_empty##_MIN,				xml_attr_empty); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_entities          ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_entity##_MIN,				xml_attr_entity); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_apostrophe        ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_apos##_MIN,				xml_attr_apos); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_ws_normalization  ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_normal##_MIN,				xml_in_attr_normalize); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_raw_lt            ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_attr_escaped##_MIN:NULL,				xml_in_attr_rawlt); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_unquoted          ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_attr_one##_MIN:NULL,					xml_in_attr_unquoted); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_minimized         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_attr_empty##_MIN:NULL,				xml_in_attr_minimized); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_duplicate         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_attr_2nd##_MIN:NULL,					xml_in_attr_dup); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_no_whitespace     ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_attr_nosp); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_ws_around_equals  ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_one##_MIN,					xml_in_attr_ws_eq); \
	print_test_xml_##STRICT##_##MINIFY("xml_attr_and_text          ("#STRICT" -> "#MINIFY")",FALSE,		xml_attr_and_text##_MIN,				xml_attr_and_text); \
	print_test_xml_##STRICT##_##MINIFY("xml_nested                 ("#STRICT" -> "#MINIFY")",FALSE,		xml_nested##_MIN,					xml_nested); \
	print_test_xml_##STRICT##_##MINIFY("xml_nested_deep            ("#STRICT" -> "#MINIFY")",FALSE,		xml_nested_deep##_MIN,				xml_nested_deep); \
	print_test_xml_##STRICT##_##MINIFY("xml_nested_min             ("#STRICT" -> "#MINIFY")",FALSE,		xml_nested##_MIN,					xml_nested_min); \
	print_test_xml_##STRICT##_##MINIFY("xml_siblings               ("#STRICT" -> "#MINIFY")",FALSE,		xml_siblings##_MIN,					xml_siblings); \
	print_test_xml_##STRICT##_##MINIFY("xml_repeat_coalesce        ("#STRICT" -> "#MINIFY")",FALSE,		xml_repeat##_MIN,					xml_repeat); \
	print_test_xml_##STRICT##_##MINIFY("xml_repeat_three           ("#STRICT" -> "#MINIFY")",FALSE,		xml_repeat_three##_MIN,				xml_repeat_three); \
	print_test_xml_##STRICT##_##MINIFY("xml_repeat_reordering      ("#STRICT" -> "#MINIFY")",FALSE,		xml_repeat_gap##_MIN,				xml_repeat_gap_input); \
	print_test_xml_##STRICT##_##MINIFY("xml_repeat_objects         ("#STRICT" -> "#MINIFY")",FALSE,		xml_repeat_objects##_MIN,			xml_repeat_objects); \
	print_test_xml_##STRICT##_##MINIFY("xml_mixed_content          ("#STRICT" -> "#MINIFY")",FALSE,		xml_mixed##_MIN,						xml_mixed_input); \
	print_test_xml_##STRICT##_##MINIFY("xml_ws_between_tags        ("#STRICT" -> "#MINIFY")",FALSE,		xml_nested##_MIN,					xml_in_ws_between); \
	print_test_xml_##STRICT##_##MINIFY("xml_comment_before_root    ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_comment_before); \
	print_test_xml_##STRICT##_##MINIFY("xml_comment_inside         ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_comment_inside); \
	print_test_xml_##STRICT##_##MINIFY("xml_comment_double_dash    ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_selfclose##_MIN:NULL,				xml_in_comment_dashes); \
	print_test_xml_##STRICT##_##MINIFY("xml_declaration            ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_decl); \
	print_test_xml_##STRICT##_##MINIFY("xml_processing_instruction ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_pi); \
	print_test_xml_##STRICT##_##MINIFY("xml_doctype                ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_doctype); \
	print_test_xml_##STRICT##_##MINIFY("xml_doctype_system         ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_doctype_system); \
	print_test_xml_##STRICT##_##MINIFY("xml_doctype_subset         ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_selfclose##_MIN:NULL,				xml_in_doctype_subset); \
	print_test_xml_##STRICT##_##MINIFY("xml_byteordermark          ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_bom); \
	print_test_xml_##STRICT##_##MINIFY("xml_epilog_comment         ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_epilog_comment); \
	print_test_xml_##STRICT##_##MINIFY("xml_close_tag_space        ("#STRICT" -> "#MINIFY")",FALSE,		xml_selfclose##_MIN,				xml_in_close_tag_space); \
	print_test_xml_##STRICT##_##MINIFY("xml_two_roots              ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_two_roots##_MIN:NULL,				xml_in_two_roots); \
	print_test_xml_##STRICT##_##MINIFY("xml_two_roots_same_tag     ("#STRICT" -> "#MINIFY")",FALSE,NSTRICT?xml_two_roots_same##_MIN:NULL,			xml_in_two_roots_same); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_text_at_root       ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_text_root); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_unclosed           ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_unclosed); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_mismatched_close   ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_mismatch); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_crossing_tags      ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_crossing); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_trailing_garbage   ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_garbage); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_space_before_name  ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_space_name); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_digit_name         ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_digit_name); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_unknown_markup     ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_markup); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_comment_unclosed   ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_comment_eof); \
	print_test_xml_##STRICT##_##MINIFY("xml_err_quote_in_text      ("#STRICT" -> "#MINIFY")",FALSE,		NULL,									xml_in_err_gt_in_attr); \
}
#endif

DEFINETEST_XML(Lenient, TRUE,	Pretty,)
DEFINETEST_XML(Lenient, TRUE,	Minify, _min)
DEFINETEST_XML(Strict, FALSE,	Pretty,)
DEFINETEST_XML(Strict, FALSE,	Minify, _min)

// TODO test other functions than just Parse/Print (e.g. the in-place XML_Minify())



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_encode_xml(void)
{
	print_suite_title("libccc/encode/xml");

	print_nonstd();

	test_xml_Lenient_Pretty();
	test_xml_Lenient_Minify();
	test_xml_Strict_Pretty();
	test_xml_Strict_Minify();

	return (OK);
}
