
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/text/regex.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                              Wrapper functions                             ||
\*============================================================================*/
/*
**	The regex API is not a single function call per operation (compile, execute,
**	extract, cleanup), so these static wrappers each perform one full operation,
**	with a signature that the TEST_PERFORM_() macro can invoke directly.
**	Sentinel string results are used so that a `NULL` result always has a single
**	unambiguous meaning for each wrapper.
*/

static char const*	regex_sentinel_error   = "<compile error>";
static char const*	regex_sentinel_nomatch = "<no match>";
static char const*	regex_sentinel_none    = "<none>";

//! Searches `str` with `pattern`: returns the whole match (or NULL if no match)
static
char*	regex_search(char const* pattern, t_regex_options options, char const* str)
{
	s_regex*		regex;
	s_regex_match	match;
	char*			result;

	regex = Regex_New(pattern, options);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	if (!Regex_Search(regex, str, 0, &match))
	{
		Regex_Delete(&regex);
		return (NULL);
	}
	result = RegexMatch_GetCapture(&match, 0, str);
	RegexMatch_Delete(&match);
	Regex_Delete(&regex);
	return (result);
}

//! Searches `str` with `pattern`: returns the contents of capture group `group` (or NULL if the group did not participate)
static
char*	regex_capture(char const* pattern, t_regex_options options, char const* str, t_uint group)
{
	s_regex*		regex;
	s_regex_match	match;
	char*			result;

	regex = Regex_New(pattern, options);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	if (!Regex_Search(regex, str, 0, &match))
	{
		Regex_Delete(&regex);
		return (StringUTF8_Duplicate(regex_sentinel_nomatch));
	}
	result = RegexMatch_GetCapture(&match, group, str);
	RegexMatch_Delete(&match);
	Regex_Delete(&regex);
	return (result);
}

//! Returns TRUE if `pattern` compiles without a syntax error
static
t_bool	regex_compiles(char const* pattern)
{
	s_regex*	regex;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (FALSE);
	Regex_Delete(&regex);
	return (TRUE);
}

//! Returns TRUE if `pattern` matches the entirety of `str`
static
t_bool	regex_entire(char const* pattern, t_regex_options options, char const* str)
{
	s_regex*	regex;
	t_bool		result;

	regex = Regex_New(pattern, options);
	if (regex == NULL)
		return (FALSE);
	result = Regex_MatchEntire(regex, str);
	Regex_Delete(&regex);
	return (result);
}

//! Returns TRUE if `pattern` matches anywhere within `str`
static
t_bool	regex_matches(char const* pattern, char const* str)
{
	s_regex*	regex;
	t_bool		result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (FALSE);
	result = Regex_Matches(regex, str);
	Regex_Delete(&regex);
	return (result);
}

//! Returns TRUE if `pattern` matches at exactly the byte offset `offset` of `str`
static
t_bool	regex_match_at(char const* pattern, char const* str, t_size offset)
{
	s_regex*		regex;
	s_regex_match	match;
	t_bool			result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (FALSE);
	result = Regex_Match(regex, str, offset, &match);
	if (result)
		RegexMatch_Delete(&match);
	Regex_Delete(&regex);
	return (result);
}

//! Replaces the first occurrence of `pattern` in `str` with `replacement`
static
char*	regex_replace(char const* pattern, t_regex_options options, char const* str, char const* replacement)
{
	s_regex*	regex;
	char*		result;

	regex = Regex_New(pattern, options);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	result = Regex_Replace(regex, str, replacement);
	Regex_Delete(&regex);
	return (result);
}

//! Replaces every occurrence of `pattern` in `str` with `replacement`
static
char*	regex_replaceall(char const* pattern, t_regex_options options, char const* str, char const* replacement)
{
	s_regex*	regex;
	char*		result;

	regex = Regex_New(pattern, options);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	result = Regex_ReplaceAll(regex, str, replacement);
	Regex_Delete(&regex);
	return (result);
}

//! Splits `str` on every occurrence of `pattern`
static
char**	regex_split(char const* pattern, char const* str)
{
	s_regex*	regex;
	t_utf8**	result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (NULL);
	result = Regex_Split(regex, str);
	Regex_Delete(&regex);
	return ((char**)result);
}

//! Returns the amount of capture groups in `pattern` (or -1 if it does not compile)
static
t_sint	regex_groupamount(char const* pattern)
{
	s_regex*	regex;
	t_sint		result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (-1);
	result = (t_sint)Regex_GetGroupAmount(regex);
	Regex_Delete(&regex);
	return (result);
}

//! Returns the group index for the named group `name` in `pattern` (or -1 if absent)
static
t_sint	regex_groupindex(char const* pattern, char const* name)
{
	s_regex*	regex;
	t_sint		result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (-1);
	result = Regex_GetGroupIndex(regex, name);
	Regex_Delete(&regex);
	return (result);
}

//! Returns the name of capture group `index` in `pattern` (or NULL if the group is unnamed)
static
char*	regex_groupname(char const* pattern, t_uint index)
{
	s_regex*		regex;
	t_utf8 const*	name;
	char*			result;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	name = Regex_GetGroupName(regex, index);
	result = (name == NULL ? NULL : StringUTF8_Duplicate(name));
	Regex_Delete(&regex);
	return (result);
}

//! Searches every occurrence of `pattern` in `str`: returns the spans as a "index:length,..." string
static
char*	regex_searchall_spans(char const* pattern, char const* str)
{
	s_regex*		regex;
	s_regex_match*	matches;
	t_uint			amount;
	char			buffer[256];
	t_size			written;
	t_uint			i;

	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
		return (StringUTF8_Duplicate(regex_sentinel_error));
	matches = Regex_SearchAll(regex, str, &amount);
	Regex_Delete(&regex);
	if (matches == NULL || amount == 0)
	{
		if (matches)
			Memory_Free(matches);
		return (StringUTF8_Duplicate(regex_sentinel_none));
	}
	written = 0;
	for (i = 0; i < amount; ++i)
	{
		written += (t_size)snprintf(buffer + written, sizeof(buffer) - written,
			"%s" SF_SIZE ":" SF_SIZE, (i == 0 ? "" : ","),
			matches[i].index, matches[i].length);
		RegexMatch_Delete(&matches[i]);
	}
	Memory_Free(matches);
	return (StringUTF8_Duplicate(buffer));
}



/*============================================================================*\
||                              Search Operations                             ||
\*============================================================================*/



#ifndef c_regsearch
void test_regex_search(void)	{}
#warning "regsearch() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_search(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		t_regex_options	options,
		char const*		str)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_search, pattern, options, str)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	regsearch, "pattern=\"%s\", options=%u, str=\"%s\"", pattern, (unsigned)options, str)
	TEST_FREE()
}
void	test_regex_search(void)
{
//	| TEST FUNCTION         | TEST NAME                        | TESTFLAGS | EXPECTING     | TEST ARGS
	// literals & basic escapes
	print_test_regex_search("regex: literal            ",        FALSE     , "hello",        "hello", 0, "say hello world");
	print_test_regex_search("regex: literal (no match) ",        FALSE     , NULL,           "hello", 0, "say goodbye");
	print_test_regex_search("regex: escaped dot        ",        FALSE     , "a.b",          "a\\.b", 0, "xa.by");
	print_test_regex_search("regex: escaped dot        ",        FALSE     , NULL,           "a\\.b", 0, "xaXby");
	print_test_regex_search("regex: hex/unicode escapes",        FALSE     , "ABC",          "\\x41\\x{42}\\u0043", 0, "xABCy");
	print_test_regex_search("regex: control escapes    ",        FALSE     , "\t\n",         "\\t\\n", 0, "a\t\nb");
	print_test_regex_search("regex: caret notation     ",        FALSE     , "\t",           "\\cI", 0, "a\tb");
	print_test_regex_search("regex: quoted literal     ",        FALSE     , "a.b*c",        "\\Qa.b*c\\E", 0, "xa.b*cy");
	// char types & classes
	print_test_regex_search("regex: \\d+               ",        FALSE     , "12345",        "\\d+", 0, "abc 12345 def");
	print_test_regex_search("regex: \\w+               ",        FALSE     , "foo_bar42",    "\\w+", 0, "  foo_bar42  ");
	print_test_regex_search("regex: \\s+               ",        FALSE     , " \t ",         "\\s+", 0, "ab \t cd");
	print_test_regex_search("regex: \\D+               ",        FALSE     , "abc",          "\\D+", 0, "123abc456");
	print_test_regex_search("regex: charset            ",        FALSE     , "abca",         "[abc]+", 0, "zzabcaz");
	print_test_regex_search("regex: negated charset    ",        FALSE     , "zzz",          "[^abc]+", 0, "abczzzabc");
	print_test_regex_search("regex: charset ranges     ",        FALSE     , "DEADbeef42",   "[a-fA-F0-9]+", 0, "xyz DEADbeef42 uvw");
	print_test_regex_search("regex: posix class        ",        FALSE     , "42",           "[[:digit:]]+", 0, "abc42def");
	print_test_regex_search("regex: negated posix class",        FALSE     , "abc",          "[[:^digit:]]+", 0, "42abc42");
	print_test_regex_search("regex: class in charset   ",        FALSE     , "1 2 3",        "[\\d\\s]+", 0, "ab1 2 3cd");
	print_test_regex_search("regex: leading ] literal  ",        FALSE     , "]x]",          "[]x]+", 0, "ab]x]cd");
	print_test_regex_search("regex: trailing - literal ",        FALSE     , "-a-",          "[a-]+", 0, "xy-a-z");
	print_test_regex_search("regex: \\p{L}             ",        FALSE     , "abc",          "\\p{L}+", 0, "42abc42");
	print_test_regex_search("regex: \\p{Lu}            ",        FALSE     , "BBB",          "\\p{Lu}+", 0, "aaBBBcc");
	print_test_regex_search("regex: \\P{L}             ",        FALSE     , "123",          "\\P{L}+", 0, "ab123cd");
	print_test_regex_search("regex: \\h horizontal ws  ",        FALSE     , " \t ",         "\\h+", 0, "a \t b");
	print_test_regex_search("regex: \\R linebreak      ",        FALSE     , "\r\n",         "\\R", 0, "a\r\nb");
	// anchors
	print_test_regex_search("regex: ^ anchor           ",        FALSE     , "abc",          "^abc", 0, "abcdef");
	print_test_regex_search("regex: ^ anchor (no match)",        FALSE     , NULL,           "^bcd", 0, "abcdef");
	print_test_regex_search("regex: $ anchor           ",        FALSE     , "def",          "def$", 0, "abcdef");
	print_test_regex_search("regex: $ anchor (no match)",        FALSE     , NULL,           "abc$", 0, "abcdef");
	print_test_regex_search("regex: ^...$              ",        FALSE     , "abc",          "^abc$", 0, "abc");
	print_test_regex_search("regex: multiline anchors  ",        FALSE     , "b",            "^b$", REGEX_OPTION_MULTILINE, "a\nb\nc");
	print_test_regex_search("regex: no multiline       ",        FALSE     , NULL,           "^b$", 0, "a\nb\nc");
	print_test_regex_search("regex: \\b word boundary  ",        FALSE     , "cat",          "\\bcat\\b", 0, "the cat sat");
	print_test_regex_search("regex: \\b word boundary  ",        FALSE     , NULL,           "\\bcat\\b", 0, "concatenate");
	print_test_regex_search("regex: \\B non-boundary   ",        FALSE     , "cat",          "\\Bcat\\B", 0, "concatenate");
	print_test_regex_search("regex: \\A anchor         ",        FALSE     , "abc",          "\\Aabc", 0, "abcdef");
	print_test_regex_search("regex: \\z anchor         ",        FALSE     , "def",          "def\\z", 0, "abcdef");
	print_test_regex_search("regex: \\Z anchor         ",        FALSE     , "def",          "def\\Z", 0, "abcdef\n");
	// quantifiers
	print_test_regex_search("regex: * quantifier       ",        FALSE     , "ac",           "ab*c", 0, "xacx");
	print_test_regex_search("regex: * quantifier       ",        FALSE     , "abbbc",        "ab*c", 0, "xabbbcx");
	print_test_regex_search("regex: + quantifier       ",        FALSE     , NULL,           "ab+c", 0, "xacx");
	print_test_regex_search("regex: + quantifier       ",        FALSE     , "abbc",         "ab+c", 0, "xabbcx");
	print_test_regex_search("regex: ? quantifier       ",        FALSE     , "abc",          "ab?c", 0, "xabcx");
	print_test_regex_search("regex: {n} quantifier     ",        FALSE     , "aaa",          "a{3}", 0, "aaaa");
	print_test_regex_search("regex: {n,m} quantifier   ",        FALSE     , "aaa",          "a{2,3}", 0, "aaaa");
	print_test_regex_search("regex: {n,} quantifier    ",        FALSE     , "aaaa",         "a{2,}", 0, "aaaa");
	print_test_regex_search("regex: {n} too many       ",        FALSE     , NULL,           "a{5}", 0, "aaaa");
	print_test_regex_search("regex: greedy             ",        FALSE     , "<a> <b>",      "<.+>", 0, "<a> <b>");
	print_test_regex_search("regex: lazy               ",        FALSE     , "<a>",          "<.+?>", 0, "<a> <b>");
	print_test_regex_search("regex: ungreedy option    ",        FALSE     , "<a>",          "<.+>", REGEX_OPTION_UNGREEDY, "<a> <b>");
	print_test_regex_search("regex: {n} exact          ",        FALSE     , "aa",           "a{2}", 0, "xaax");
	print_test_regex_search("regex: malformed {} literal",       FALSE     , "x{abc",        "x{abc", 0, "yx{abcz");
	// possessive quantifiers & atomic groups
	print_test_regex_search("regex: possessive         ",        FALSE     , NULL,           "a*+a", 0, "aaa");
	print_test_regex_search("regex: backtracking       ",        FALSE     , "aaa",          "a*a", 0, "aaa");
	print_test_regex_search("regex: atomic group       ",        FALSE     , NULL,           "(?>a*)a", 0, "aaa");
	print_test_regex_search("regex: atomic group alt   ",        FALSE     , "abc",          "(?>ab|a)c", 0, "abc");
	print_test_regex_search("regex: atomic group alt   ",        FALSE     , NULL,           "(?>ab|a)bc", 0, "abc");
	// alternation & groups
	print_test_regex_search("regex: alternation        ",        FALSE     , "dog",          "cat|dog", 0, "hotdog");
	print_test_regex_search("regex: group alternation  ",        FALSE     , "dogfood",      "(cat|dog)food", 0, "dogfood");
	print_test_regex_search("regex: non-capture group  ",        FALSE     , "abcabc",       "(?:abc)+", 0, "xabcabcy");
	// backreferences
	print_test_regex_search("regex: backreference      ",        FALSE     , "hey hey",      "(\\w+) \\1", 0, "hey hey you");
	print_test_regex_search("regex: backreference      ",        FALSE     , NULL,           "(\\w+) \\1", 0, "abc def");
	print_test_regex_search("regex: backref ignorecase ",        FALSE     , "bB",           "(a|b)\\1", REGEX_OPTION_IGNORECASE, "bB");
	// lookarounds
	print_test_regex_search("regex: lookahead          ",        FALSE     , "foo",          "\\w+(?=;)", 0, "foo; bar");
	print_test_regex_search("regex: negative lookahead ",        FALSE     , "fo",           "\\w+(?!;)", 0, "foo;");
	print_test_regex_search("regex: lookbehind         ",        FALSE     , "42",           "(?<=\\$)\\d+", 0, "price: $42 now");
	print_test_regex_search("regex: negative lookbehind",        FALSE     , "43",           "(?<!\\$)\\b\\d+", 0, "$42 43");
	print_test_regex_search("regex: var-length lookbehind",      FALSE     , "c",            "(?<=ab+)c", 0, "xabbbc");
	print_test_regex_search("regex: anchored lookbehind",        FALSE     , "d",            "(?<=^.{3})d", 0, "abcdef");
	// inline options
	print_test_regex_search("regex: (?i) inline        ",        FALSE     , "hello",        "(?i)HELLO", 0, "say hello");
	print_test_regex_search("regex: (?i:) scoped       ",        FALSE     , "helLO",        "(?i:HEL)LO", 0, "say helLO");
	print_test_regex_search("regex: (?i:) scoped       ",        FALSE     , NULL,           "(?i:HEL)LO", 0, "say hello");
	print_test_regex_search("regex: (?s:) scoped       ",        FALSE     , "a\nb",         "a(?s:.)b", 0, "a\nb");
	print_test_regex_search("regex: dot excludes \\n   ",        FALSE     , NULL,           "a.b", 0, "a\nb");
	print_test_regex_search("regex: dotall option      ",        FALSE     , "a\nb",         "a.b", REGEX_OPTION_DOTALL, "a\nb");
	print_test_regex_search("regex: (?x) extended      ",        FALSE     , "abc",          "(?x) a  b\t# comment\nc", 0, "xabcy");
	// case-insensitive matching
	print_test_regex_search("regex: ignorecase option  ",        FALSE     , "HeLLo",        "hello", REGEX_OPTION_IGNORECASE, "say HeLLo");
	print_test_regex_search("regex: ignorecase charset ",        FALSE     , "ABC",          "[a-z]+", REGEX_OPTION_IGNORECASE, "42ABC42");
	print_test_regex_search("regex: ignorecase negation",        FALSE     , "bb",           "[^a]+", REGEX_OPTION_IGNORECASE, "bbAbb");
	// UTF-8
	print_test_regex_search("regex: utf8 literal       ",        FALSE     , "héllo",        "héllo", 0, "say héllo");
	print_test_regex_search("regex: utf8 dot           ",        FALSE     , "héllo",        "h.llo", 0, "say héllo");
	print_test_regex_search("regex: utf8 charset       ",        FALSE     , "éàé",          "[éà]+", 0, "xéàéy");
	print_test_regex_search("regex: utf8 \\p{L}        ",        FALSE     , "héllo",        "\\p{L}+", 0, "42héllo42");
	print_test_regex_search("regex: utf8 quantifier    ",        FALSE     , "ééé",          "é{2,3}", 0, "aééééb");
	print_test_regex_search("regex: utf8 ignorecase    ",        FALSE     , "é",            "(?i)É", 0, "café é");
	print_test_regex_search("regex: utf8 japanese      ",        FALSE     , "日本語",       "日本語", 0, "これは日本語です");
	print_test_regex_search("regex: utf8 japanese dot  ",        FALSE     , "日本語",       "日.語", 0, "これは日本語です");
}
#endif



#ifndef c_regcapture
void test_regex_capture(void)	{}
#warning "regcapture() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_capture(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		t_regex_options	options,
		char const*		str,
		t_uint			group)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_capture, pattern, options, str, group)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	regcapture, "pattern=\"%s\", options=%u, str=\"%s\", group=" SF_UINT, pattern, (unsigned)options, str, group)
	TEST_FREE()
}
void	test_regex_capture(void)
{
//	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_capture("regex: capture group 1      ",     FALSE     , "aa",       "(a+)(b+)", 0, "xaabbbx", 1);
	print_test_regex_capture("regex: capture group 2      ",     FALSE     , "bbb",      "(a+)(b+)", 0, "xaabbbx", 2);
	print_test_regex_capture("regex: nested groups        ",     FALSE     , "c",        "(a(b(c)))", 0, "abc", 3);
	print_test_regex_capture("regex: alternation group    ",     FALSE     , "b",        "(a)|(b)", 0, "b", 2);
	print_test_regex_capture("regex: non-participating    ",     FALSE     , NULL,       "(a)|(b)", 0, "b", 1);
	print_test_regex_capture("regex: named group + backref",     FALSE     , "hey",      "(?<word>\\w+) \\k<word>", 0, "hey hey you", 1);
	print_test_regex_capture("regex: python-style names   ",     FALSE     , "06",       "(?P<year>\\d{4})-(?P<month>\\d{2})", 0, "on 2024-06-15", 2);
	print_test_regex_capture("regex: quote-style names    ",     FALSE     , "bb",       "(?'x'a+)(?'y'b+)", 0, "aabb", 2);
}
#endif



/*============================================================================*\
||                            Compilation Operations                          ||
\*============================================================================*/



#ifndef c_regnew
void test_regex_compile(void)	{}
#warning "regnew() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_compile(char const* test_name, t_testflags flags,
		t_bool			expecting,
		char const*		pattern)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, regex_compiles, pattern)
	test.expect = expecting;
	TEST_PRINT(bool,regnew, "pattern=\"%s\"", pattern)
}
void	test_regex_compile(void)
{
//	| TEST FUNCTION          | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_compile("regex: valid pattern        ",     FALSE     , TRUE ,      "(a)(?<foo>b)c*");
	print_test_regex_compile("regex: unclosed group       ",     FALSE     , FALSE,      "a(bc");
	print_test_regex_compile("regex: unmatched paren      ",     FALSE     , FALSE,      "a)b*)");
	print_test_regex_compile("regex: unclosed charset     ",     FALSE     , FALSE,      "a[bc");
	print_test_regex_compile("regex: quantifier w/o atom  ",     FALSE     , FALSE,      "*a");
	print_test_regex_compile("regex: bad escape           ",     FALSE     , FALSE,      "\\q");
	print_test_regex_compile("regex: reversed range {3,1} ",     FALSE     , FALSE,      "a{3,1}");
	print_test_regex_compile("regex: unclosed group name  ",     FALSE     , FALSE,      "(?<name)");
	print_test_regex_compile("regex: bad unicode property ",     FALSE     , FALSE,      "\\p{NotARealProperty}");
	print_test_regex_compile("regex: dangling backref     ",     FALSE     , FALSE,      "\\5xy");
	print_test_regex_compile("regex: bad inline option    ",     FALSE     , FALSE,      "(?i_)x");
}
#endif



/*============================================================================*\
||                              Match Operations                              ||
\*============================================================================*/



#ifndef c_regmatchall
void test_regex_matchentire(void)	{}
#warning "regmatchall() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_matchentire(char const* test_name, t_testflags flags,
		t_bool			expecting,
		char const*		pattern,
		t_regex_options	options,
		char const*		str)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, regex_entire, pattern, options, str)
	test.expect = expecting;
	TEST_PRINT(bool,regmatchall, "pattern=\"%s\", options=%u, str=\"%s\"", pattern, (unsigned)options, str)
}
void	test_regex_matchentire(void)
{
//	| TEST FUNCTION              | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_matchentire("regex: entire match       ",     FALSE     , TRUE ,      "\\d+", 0, "12345");
	print_test_regex_matchentire("regex: partial only       ",     FALSE     , FALSE,      "\\d+", 0, "123a5");
	print_test_regex_matchentire("regex: entire backtracking",     FALSE     , TRUE ,      "a|ab", 0, "ab");
}
#endif



#ifndef c_regmatch
void test_regex_match(void)	{}
#warning "regmatch() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_match(char const* test_name, t_testflags flags,
		t_bool			expecting,
		char const*		pattern,
		char const*		str,
		t_size			offset)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, regex_match_at, pattern, str, offset)
	test.expect = expecting;
	TEST_PRINT(bool,regmatch, "pattern=\"%s\", str=\"%s\", offset=" SF_SIZE, pattern, str, offset)
}
void	test_regex_match(void)
{
//	| TEST FUNCTION        | TEST NAME                        | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_match("regex: anchored at offset    ",     FALSE     , TRUE ,      "hello", "say hello", 4);
	print_test_regex_match("regex: anchored (wrong pos)  ",     FALSE     , FALSE,      "hello", "say hello", 0);
	print_test_regex_match("regex: anchored utf8         ",     FALSE     , TRUE ,      "h.llo", "say héllo", 4);
}
#endif



#ifndef c_regmatches
void test_regex_matches(void)	{}
#warning "regmatches() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_matches(char const* test_name, t_testflags flags,
		t_bool			expecting,
		char const*		pattern,
		char const*		str)
{
	TEST_INIT(bool)
	TEST_PERFORM_(result, regex_matches, pattern, str)
	test.expect = expecting;
	TEST_PRINT(bool,regmatches, "pattern=\"%s\", str=\"%s\"", pattern, str)
}
void	test_regex_matches(void)
{
//	| TEST FUNCTION          | TEST NAME                            | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_matches("regex: matches anywhere          ",     FALSE     , TRUE ,      "l+o", "hello");
	print_test_regex_matches("regex: matches nothing           ",     FALSE     , FALSE,      "xyz", "hello");
	// catastrophic backtracking must abort safely (no hang), and report no match
	print_test_regex_matches("regex: catastrophic backtracking ",     FALSE     , FALSE,      "(a+)+$", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");
}
#endif



/*============================================================================*\
||                             Replace Operations                             ||
\*============================================================================*/



#ifndef c_regreplaceall
void test_regex_replaceall(void)	{}
#warning "regreplaceall() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_replaceall(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		t_regex_options	options,
		char const*		str,
		char const*		replacement)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_replaceall, pattern, options, str, replacement)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	regreplaceall, "pattern=\"%s\", options=%u, str=\"%s\", replacement=\"%s\"", pattern, (unsigned)options, str, replacement)
	TEST_FREE()
}
void	test_regex_replaceall(void)
{
//	| TEST FUNCTION             | TEST NAME                     | TESTFLAGS | EXPECTING              | TEST ARGS
	print_test_regex_replaceall("regex: replace literal    ",     FALSE     , "hello there",           "world", 0, "hello world", "there");
	print_test_regex_replaceall("regex: $n substitution    ",     FALSE     , "mail: example at bob",  "(\\w+)@(\\w+)", 0, "mail: bob@example", "$2 at $1");
	print_test_regex_replaceall("regex: named substitution ",     FALSE     , "example/bob",           "(?<user>\\w+)@(?<host>\\w+)", 0, "bob@example", "${host}/$<user>");
	print_test_regex_replaceall("regex: $0 whole match     ",     FALSE     , "a<1>b<22>c<333>",       "\\d+", 0, "a1b22c333", "<$0>");
	print_test_regex_replaceall("regex: $$ escape          ",     FALSE     , "$$$",                   "a", 0, "aaa", "$$");
	print_test_regex_replaceall("regex: no match untouched ",     FALSE     , "hello",                 "nomatch", 0, "hello", "x");
}
#endif



#ifndef c_regreplace
void test_regex_replace(void)	{}
#warning "regreplace() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_replace(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		t_regex_options	options,
		char const*		str,
		char const*		replacement)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_replace, pattern, options, str, replacement)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	regreplace, "pattern=\"%s\", options=%u, str=\"%s\", replacement=\"%s\"", pattern, (unsigned)options, str, replacement)
	TEST_FREE()
}
void	test_regex_replace(void)
{
//	| TEST FUNCTION          | TEST NAME                        | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_replace("regex: replace first only    ",     FALSE     , "Xaa",      "a", 0, "aaa", "X");
	print_test_regex_replace("regex: replace with capture  ",     FALSE     , "[1]b22",   "(\\d+)", 0, "1b22", "[$1]");
}
#endif



/*============================================================================*\
||                              Split Operations                              ||
\*============================================================================*/



#ifndef c_regsplit
void test_regex_split(void)	{}
#warning "regsplit() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_split(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		pattern,
		char const*		str)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, regex_split, pattern, str)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	regsplit, "pattern=\"%s\", str=\"%s\"", pattern, str)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_regex_split(void)
{
	static char const*	expect_commas[5] = { "a", "b", "c ", "d", NULL };
	static char const*	expect_spaces[4] = { "foo", "bar", "baz", NULL };
	static char const*	expect_x[4]      = { "a", "b", "c", NULL };
	static char const*	expect_edges[2]  = { "a", NULL };
	static char const*	expect_whole[2]  = { "no delimiters here", NULL };
//	| TEST FUNCTION        | TEST NAME                     | TESTFLAGS | EXPECTING     | TEST ARGS
	print_test_regex_split("regex: split on pattern   ",     FALSE     , expect_commas,  ",\\s*", "a, b,c ,  d");
	print_test_regex_split("regex: split on whitespace",     FALSE     , expect_spaces,  "\\s+", "  foo   bar  baz ");
	print_test_regex_split("regex: split on literal   ",     FALSE     , expect_x,       "x", "axbxc");
	print_test_regex_split("regex: split seps at edges",     FALSE     , expect_edges,   "x", "xxaxx");
	print_test_regex_split("regex: split no delimiters",     FALSE     , expect_whole,   "-", "no delimiters here");
}
#endif



/*============================================================================*\
||                            Group Info Operations                           ||
\*============================================================================*/



#ifndef c_reggroups
void test_regex_groupamount(void)	{}
#warning "reggroups() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_groupamount(char const* test_name, t_testflags flags,
		t_sint			expecting,
		char const*		pattern)
{
	TEST_INIT(sint)
	TEST_PERFORM_(result, regex_groupamount, pattern)
	test.expect = expecting;
	TEST_PRINT(sint,reggroups, "pattern=\"%s\"", pattern)
}
void	test_regex_groupamount(void)
{
//	| TEST FUNCTION              | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_groupamount("regex: group amount      ",     FALSE     , 3,          "(a)(?<foo>b)(?:c)(?<bar>d)");
	print_test_regex_groupamount("regex: no groups         ",     FALSE     , 0,          "abc");
	print_test_regex_groupamount("regex: nested groups     ",     FALSE     , 3,          "(a(b(c)))");
}
#endif



#ifndef c_reggroupindex
void test_regex_groupindex(void)	{}
#warning "reggroupindex() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_groupindex(char const* test_name, t_testflags flags,
		t_sint			expecting,
		char const*		pattern,
		char const*		name)
{
	TEST_INIT(sint)
	TEST_PERFORM_(result, regex_groupindex, pattern, name)
	test.expect = expecting;
	TEST_PRINT(sint,reggroupindex, "pattern=\"%s\", name=\"%s\"", pattern, name)
}
void	test_regex_groupindex(void)
{
//	| TEST FUNCTION             | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_groupindex("regex: named group index  ",     FALSE     , 2,          "(a)(?<foo>b)(?:c)(?<bar>d)", "foo");
	print_test_regex_groupindex("regex: named group index  ",     FALSE     , 3,          "(a)(?<foo>b)(?:c)(?<bar>d)", "bar");
	print_test_regex_groupindex("regex: unknown group name ",     FALSE     , -1,         "(a)(?<foo>b)(?:c)(?<bar>d)", "baz");
}
#endif



#ifndef c_reggroupname
void test_regex_groupname(void)	{}
#warning "reggroupname() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_groupname(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		t_uint			index)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_groupname, pattern, index)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	reggroupname, "pattern=\"%s\", index=" SF_UINT, pattern, index)
	TEST_FREE()
}
void	test_regex_groupname(void)
{
//	| TEST FUNCTION            | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_regex_groupname("regex: group name         ",     FALSE     , "foo",      "(a)(?<foo>b)(?:c)(?<bar>d)", 2);
	print_test_regex_groupname("regex: unnamed group      ",     FALSE     , NULL,       "(a)(?<foo>b)(?:c)(?<bar>d)", 1);
}
#endif



#ifndef c_regsearchall
void test_regex_searchall(void)	{}
#warning "regsearchall() test suite function defined, but the function isn't defined."
#else
void	print_test_regex_searchall(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const*		pattern,
		char const*		str)
{
	TEST_INIT(str)
	TEST_PERFORM_(result, regex_searchall_spans, pattern, str)
	test.expect = (char*)expecting;
	TEST_PRINT(str,	regsearchall, "pattern=\"%s\", str=\"%s\"", pattern, str)
	TEST_FREE()
}
void	test_regex_searchall(void)
{
//	| TEST FUNCTION            | TEST NAME                     | TESTFLAGS | EXPECTING       | TEST ARGS
	print_test_regex_searchall("regex: searchall spans    ",     FALSE     , "1:1,3:2,6:3",    "\\d+", "a1b22c333");
	print_test_regex_searchall("regex: searchall no match ",     FALSE     , "<none>",         "\\d+", "abc");
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_regex(void)
{
	print_suite_title("libccc/text/regex");

	print_nonstd();

	test_regex_compile();

	test_regex_search();
	test_regex_capture();

	test_regex_match();
	test_regex_matches();
	test_regex_matchentire();

	test_regex_replace();
	test_regex_replaceall();

	test_regex_split();

	test_regex_groupamount();
	test_regex_groupindex();
	test_regex_groupname();
	test_regex_searchall();

	return (OK);
}
