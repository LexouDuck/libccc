
#include <stdio.h>
#include <string.h>

#include "libccc.h"
#include "libccc/math.h"
#include "libccc/string.h"
#include "libccc/encode/yaml.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(COND, MSG) \
	do { tests_run++; if (!(COND)) { tests_failed++; printf("FAIL: %s\n", MSG); } } while (0)

static char const* yaml_doc =
"# top comment\n"
"---\n"
"name: libccc\n"
"version: 1.0\n"
"stable: true\n"
"nothing: ~\n"
"count: 0x1A\n"
"ratio: -2.5e1\n"
"infinity: .inf\n"
"quoted: \"hello\\tworld \\u00e9\"\n"
"single: 'it''s ok'\n"
"literal: |\n"
"  line one\n"
"  line two\n"
"folded: >-\n"
"  folded\n"
"  text\n"
"deps:\n"
"  - alpha\n"
"  - beta\n"
"  - name: gamma   # inline comment\n"
"    optional: true\n"
"nested:\n"
"  inner:\n"
"    value: 42\n"
"flow_list: [1, 2, 3]\n"
"flow_map: {a: 1, b: \"two\"}\n"
"...\n";

int main(void)
{
	s_yaml* yaml = YAML_FromString_Strict(yaml_doc);
	CHECK(yaml != NULL, "parse strict: whole document");
	if (yaml == NULL)
		return (printf("parse error:\n%s\n", "(null result)"), 1);

	CHECK(YAML_IsObject(yaml), "root is a mapping");
	CHECK(YAML_GetObjectItem(yaml, "name") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(yaml, "name")), "libccc"),
		"plain scalar string");
	CHECK(YAML_GetObjectItem(yaml, "version") &&
		YAML_GetValue_Float(YAML_GetObjectItem(yaml, "version")) == 1.0,
		"float scalar");
	CHECK(YAML_GetObjectItem(yaml, "stable") &&
		YAML_GetValue_Boolean(YAML_GetObjectItem(yaml, "stable")),
		"boolean scalar");
	CHECK(YAML_GetObjectItem(yaml, "nothing") &&
		YAML_IsNull(YAML_GetObjectItem(yaml, "nothing")),
		"null scalar (~)");
	CHECK(YAML_GetObjectItem(yaml, "count") &&
		YAML_GetValue_Integer(YAML_GetObjectItem(yaml, "count")) == 26,
		"hexadecimal integer");
	CHECK(YAML_GetObjectItem(yaml, "ratio") &&
		YAML_GetValue_Float(YAML_GetObjectItem(yaml, "ratio")) == -25.0,
		"scientific-notation float");
	CHECK(YAML_GetObjectItem(yaml, "infinity") &&
		IS_INFINITY(YAML_GetValue_Float(YAML_GetObjectItem(yaml, "infinity"))),
		".inf float");
	CHECK(YAML_GetObjectItem(yaml, "quoted") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(yaml, "quoted")), "hello\tworld \xC3\xA9"),
		"double-quoted escapes");
	CHECK(YAML_GetObjectItem(yaml, "single") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(yaml, "single")), "it's ok"),
		"single-quoted '' escape");
	CHECK(YAML_GetObjectItem(yaml, "literal") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(yaml, "literal")), "line one\nline two\n"),
		"literal block scalar |");
	CHECK(YAML_GetObjectItem(yaml, "folded") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(yaml, "folded")), "folded text"),
		"folded block scalar >-");

	s_yaml* deps = YAML_GetObjectItem(yaml, "deps");
	CHECK(deps && YAML_IsArray(deps), "block sequence");
	CHECK(deps && YAML_GetArrayLength(deps) == 3, "block sequence length");
	s_yaml* item = deps ? YAML_GetArrayItem(deps, 2) : NULL;
	CHECK(item && YAML_IsObject(item), "compact `- key: value` item");
	CHECK(item && YAML_GetObjectItem(item, "optional") &&
		YAML_GetValue_Boolean(YAML_GetObjectItem(item, "optional")),
		"compact item second key");

	s_yaml* inner = YAML_Get(yaml, "[\"nested\"][\"inner\"][\"value\"]");
	CHECK(inner && YAML_GetValue_Integer(inner) == 42, "nested mapping via keypath");

	s_yaml* flow_list = YAML_GetObjectItem(yaml, "flow_list");
	CHECK(flow_list && YAML_IsArray(flow_list) && YAML_GetArrayLength(flow_list) == 3,
		"flow sequence");
	s_yaml* flow_map = YAML_GetObjectItem(yaml, "flow_map");
	CHECK(flow_map && YAML_IsObject(flow_map) &&
		YAML_GetObjectItem(flow_map, "b") && String_Equals(
		YAML_GetValue_String(YAML_GetObjectItem(flow_map, "b")), "two"),
		"flow mapping");

	// pretty-print, then re-parse: round-trip must preserve structure
	t_utf8* pretty = YAML_ToString_Pretty(yaml);
	CHECK(pretty != NULL, "print pretty");
	if (pretty)
	{
		printf("=== pretty ===\n%s\n", pretty);
		s_yaml* reparsed = YAML_FromString_Strict(pretty);
		CHECK(reparsed != NULL, "re-parse pretty output");
		CHECK(reparsed && YAML_Equals(yaml, reparsed, TRUE), "pretty round-trip equality");
		YAML_Delete(reparsed);
		String_Delete(&pretty);
	}
	// minified (flow-style) print, then re-parse
	t_utf8* mini = YAML_ToString_Minify(yaml);
	CHECK(mini != NULL, "print minify");
	if (mini)
	{
		printf("=== minify ===\n%s\n", mini);
		s_yaml* reparsed = YAML_FromString_Strict(mini);
		CHECK(reparsed != NULL, "re-parse minified output");
		CHECK(reparsed && YAML_Equals(yaml, reparsed, TRUE), "minify round-trip equality");
		YAML_Delete(reparsed);
		String_Delete(&mini);
	}
	YAML_Delete(yaml);

	// lenient-only scalars
	s_yaml* lenient = YAML_FromString_Lenient("enabled: yes\nmask: 0b1010\n");
	CHECK(lenient != NULL, "parse lenient");
	CHECK(lenient && YAML_GetObjectItem(lenient, "enabled") &&
		YAML_GetValue_Boolean(YAML_GetObjectItem(lenient, "enabled")),
		"lenient yes/no boolean");
	CHECK(lenient && YAML_GetObjectItem(lenient, "mask") &&
		YAML_GetValue_Integer(YAML_GetObjectItem(lenient, "mask")) == 10,
		"lenient binary integer");
	YAML_Delete(lenient);

	// strict mode must reject yes/no
	s_yaml* strict = YAML_FromString_Strict("enabled: yes\n");
	CHECK(strict && YAML_GetObjectItem(strict, "enabled") &&
		YAML_IsString(YAML_GetObjectItem(strict, "enabled")),
		"strict: `yes` stays a string");
	YAML_Delete(strict);

	// unsupported features must fail cleanly
	s_yaml* bad = YAML_FromString_Strict("anchor: &a value\n");
	CHECK(bad == NULL, "anchors are rejected");

	// top-level sequence document
	s_yaml* seq = YAML_FromString_Strict("- 1\n- 2\n- sub:\n    - a\n    - b\n");
	CHECK(seq && YAML_IsArray(seq) && YAML_GetArrayLength(seq) == 3,
		"top-level block sequence");
	YAML_Delete(seq);

	// empty document
	s_yaml* empty = YAML_FromString_Strict("# only a comment\n");
	CHECK(empty && YAML_IsNull(empty), "empty document is null");
	YAML_Delete(empty);

	printf("\n%d/%d tests passed\n", tests_run - tests_failed, tests_run);
	return (tests_failed != 0);
}
