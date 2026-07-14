
#include <stdio.h>
#include <string.h>

#include "libccc.h"
#include "libccc/math.h"
#include "libccc/string.h"
#include "libccc/encode/xml.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(COND, MSG) \
	do { tests_run++; if (!(COND)) { tests_failed++; printf("FAIL: %s\n", MSG); } } while (0)

static char const* xml_doc =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<!DOCTYPE library SYSTEM \"library.dtd\">\n"
"<!-- a library catalog -->\n"
"<library name=\"City Library\" open=\"true\">\n"
"\t<address>\n"
"\t\t<street>42 Main St.</street>\n"
"\t\t<city>Springfield</city>\n"
"\t</address>\n"
"\t<book isbn=\"978-0000000001\">\n"
"\t\t<title>Tom &amp; Jerry &#x2014; a tale</title>\n"
"\t\t<pages>250</pages>\n"
"\t</book>\n"
"\t<book isbn=\"978-0000000002\">\n"
"\t\t<title><![CDATA[Code <XML> & more]]></title>\n"
"\t\t<pages>512</pages>\n"
"\t</book>\n"
"\t<book isbn=\"978-0000000003\">\n"
"\t\t<title>L&apos;\xC3\xA9toile</title>\n"
"\t\t<pages>99</pages>\n"
"\t</book>\n"
"\t<motto>Read <!-- inline comment --> every day</motto>\n"
"\t<closed/>\n"
"</library>\n";

int main(void)
{
	s_xml* xml = XML_FromString_Strict(xml_doc);
	CHECK(xml != NULL, "parse strict: whole document");
	if (xml == NULL)
		return (1);

	CHECK(XML_IsObject(xml), "document root wrapper is an object");
	s_xml* lib = XML_GetObjectItem(xml, "library");
	CHECK(lib && XML_IsObject(lib), "root element <library>");

	// attributes (with '@' key prefix)
	s_xml* attr = lib ? XML_GetObjectItem(lib, "@name") : NULL;
	CHECK(attr && XML_IsString(attr) && String_Equals(
		XML_GetValue_String(attr), "City Library"),
		"root attribute @name");
	attr = lib ? XML_GetObjectItem(lib, "@open") : NULL;
	CHECK(attr && XML_IsString(attr) && String_Equals(
		XML_GetValue_String(attr), "true"),
		"attribute values stay strings");

	// nested elements
	s_xml* city = XML_Get(lib, "[\"address\"][\"city\"]");
	CHECK(city && XML_IsString(city) && String_Equals(
		XML_GetValue_String(city), "Springfield"),
		"nested text-only element");

	// repeated <book> tags coalesced into an array
	s_xml* books = lib ? XML_GetObjectItem(lib, "book") : NULL;
	CHECK(books && XML_IsArray(books), "repeated tags coalesce into array");
	CHECK(books && XML_GetArrayLength(books) == 3, "array holds all 3 books");
	s_xml* book = books ? XML_GetArrayItem(books, 0) : NULL;
	CHECK(book && XML_IsObject(book) &&
		XML_GetObjectItem(book, "@isbn") &&
		String_Equals(XML_GetValue_String(XML_GetObjectItem(book, "@isbn")), "978-0000000001"),
		"array item keeps its attributes");
	CHECK(book && XML_GetObjectItem(book, "title") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(book, "title")), "Tom & Jerry \xE2\x80\x94 a tale"),
		"entities and character references decoded");
	book = books ? XML_GetArrayItem(books, 1) : NULL;
	CHECK(book && XML_GetObjectItem(book, "title") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(book, "title")), "Code <XML> & more"),
		"CDATA section is verbatim");
	book = books ? XML_GetArrayItem(books, 2) : NULL;
	CHECK(book && XML_GetObjectItem(book, "title") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(book, "title")), "L'\xC3\xA9toile"),
		"apostrophe entity and UTF-8 text");

	// text with inline comment (segments joined with a space)
	s_xml* motto = lib ? XML_GetObjectItem(lib, "motto") : NULL;
	CHECK(motto && XML_IsString(motto) && String_Equals(
		XML_GetValue_String(motto), "Read every day"),
		"inline comment removed from text");

	// empty self-closing element
	s_xml* closed = lib ? XML_GetObjectItem(lib, "closed") : NULL;
	CHECK(closed && XML_IsNull(closed), "empty element is null");

	// pretty-print, then re-parse: round-trip must preserve structure
	t_utf8* pretty = XML_ToString_Pretty(xml);
	CHECK(pretty != NULL, "print pretty");
	if (pretty)
	{
		printf("=== pretty ===\n%s\n", pretty);
		s_xml* reparsed = XML_FromString_Strict(pretty);
		CHECK(reparsed != NULL, "re-parse pretty output");
		CHECK(reparsed && XML_Equals(xml, reparsed, TRUE), "pretty round-trip equality");
		XML_Delete(reparsed);
		String_Delete(&pretty);
	}
	// minified print, then re-parse
	t_utf8* mini = XML_ToString_Minify(xml);
	CHECK(mini != NULL, "print minify");
	if (mini)
	{
		printf("=== minify ===\n%s\n\n", mini);
		s_xml* reparsed = XML_FromString_Strict(mini);
		CHECK(reparsed != NULL, "re-parse minified output");
		CHECK(reparsed && XML_Equals(xml, reparsed, TRUE), "minify round-trip equality");
		XML_Delete(reparsed);
		String_Delete(&mini);
	}
	XML_Delete(xml);

	// mixed content: text interleaved with child elements
	xml = XML_FromString_Strict("<p>hello <b>bold</b> world</p>");
	CHECK(xml != NULL, "parse mixed content");
	s_xml* para = xml ? XML_GetObjectItem(xml, "p") : NULL;
	CHECK(para && XML_GetObjectItem(para, "#text") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(para, "#text")), "hello world"),
		"mixed content text concatenated into #text");
	CHECK(para && XML_GetObjectItem(para, "b") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(para, "b")), "bold"),
		"mixed content child element");
	XML_Delete(xml);

	// escaping round-trip: build a tree by hand, print it, re-parse it
	xml = XML_CreateObject();
	s_xml* root = XML_CreateObject();
	XML_AddToObject_String(root, "@title", "5 < 6 & \"quotes\"");
	XML_AddToObject_String(root, "text", "  multi\nline & <edgy>  ");
	XML_AddToObject_Integer(root, "count", 42);
	XML_AddToObject_Float(root, "ratio", 0.5);
	XML_AddToObject_Boolean(root, "flag", TRUE);
	XML_AddToObject_Null(root, "nothing");
	XML_AddToObject_Item(xml, "data", root);
	t_utf8* printed = XML_ToString_Pretty(xml);
	CHECK(printed != NULL, "print hand-built tree");
	if (printed)
	{
		printf("=== hand-built ===\n%s\n", printed);
		s_xml* reparsed = XML_FromString_Strict(printed);
		CHECK(reparsed != NULL, "re-parse hand-built tree");
		s_xml* data = reparsed ? XML_GetObjectItem(reparsed, "data") : NULL;
		CHECK(data && XML_GetObjectItem(data, "@title") && String_Equals(
			XML_GetValue_String(XML_GetObjectItem(data, "@title")), "5 < 6 & \"quotes\""),
			"attribute escaping round-trip");
		CHECK(data && XML_GetObjectItem(data, "text") && String_Equals(
			XML_GetValue_String(XML_GetObjectItem(data, "text")), "  multi\nline & <edgy>  "),
			"text whitespace/escaping round-trip");
		CHECK(data && XML_GetObjectItem(data, "count") && String_Equals(
			XML_GetValue_String(XML_GetObjectItem(data, "count")), "42"),
			"numbers print as text (XML is untyped)");
		XML_Delete(reparsed);
		String_Delete(&printed);
	}
	XML_Delete(xml);

	// lenient-only syntax: unquoted + minimized attributes, several root elements
	xml = XML_FromString_Lenient("<input type=checkbox disabled/><input type=text/>");
	CHECK(xml != NULL, "parse lenient fragment");
	s_xml* inputs = xml ? XML_GetObjectItem(xml, "input") : NULL;
	CHECK(inputs && XML_IsArray(inputs) && XML_GetArrayLength(inputs) == 2,
		"lenient: multiple root elements coalesce");
	s_xml* input = inputs ? XML_GetArrayItem(inputs, 0) : NULL;
	CHECK(input && XML_GetObjectItem(input, "@type") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(input, "@type")), "checkbox"),
		"lenient: unquoted attribute value");
	CHECK(input && XML_GetObjectItem(input, "@disabled") && String_Equals(
		XML_GetValue_String(XML_GetObjectItem(input, "@disabled")), ""),
		"lenient: minimized attribute");
	XML_Delete(xml);

	// strict mode must reject lenient-only syntax
	CHECK(XML_FromString_Strict("<a b=1/>") == NULL, "strict: unquoted attribute rejected");
	CHECK(XML_FromString_Strict("<a/><b/>") == NULL, "strict: multiple roots rejected");
	CHECK(XML_FromString_Strict("<a>&foo;</a>") == NULL, "strict: unknown entity rejected");
	CHECK(XML_FromString_Strict("<a x=\"1\" x=\"2\"/>") == NULL, "strict: duplicate attribute rejected");
	CHECK(XML_FromString_Strict("<a><b></a></b>") == NULL, "mismatched close tags rejected");
	CHECK(XML_FromString_Strict("<a>") == NULL, "unclosed element rejected");

	// in-place minification
	{
		t_utf8 buffer[256];
		String_Copy(buffer,
			"<a>\n\t<!-- gone -->\n\t<b x=\"1\">  kept  </b>\n\t<c><![CDATA[ raw\n ]]></c>\n</a>\n");
		XML_Minify(buffer);
		CHECK(String_Equals(buffer,
			"<a><b x=\"1\">  kept  </b><c><![CDATA[ raw\n ]]></c></a>"),
			"XML_Minify in-place");
	}

	printf("%d/%d tests passed\n", tests_run - tests_failed, tests_run);
	return (tests_failed != 0);
}
