/*
**	Standalone test program for the libccc/text/regex.h module.
**	Build (from the libccc root folder):
**	  gcc test/standalone/regex.c -I./hdr -L./bin/release_linux_x86-64/static -lccc -o regex_test
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libccc/text/regex.h"

static int	tests_total = 0;
static int	tests_failed = 0;

// checks that `pattern` searches within `str` yielding a whole-match equal to `expect` (or no match, if `expect` is NULL)
static void	test_search(char const* pattern, t_regex_options options, char const* str, char const* expect)
{
	s_regex*		regex;
	s_regex_match	match;
	t_utf8*			found;

	tests_total++;
	regex = Regex_New(pattern, options);
	if (regex == NULL)
	{
		printf("FAIL: /%s/ did not compile\n", pattern);
		tests_failed++;
		return;
	}
	if (!Regex_Search(regex, str, 0, &match))
	{
		if (expect != NULL)
		{
			printf("FAIL: /%s/ on \"%s\": no match (expected \"%s\")\n", pattern, str, expect);
			tests_failed++;
		}
		Regex_Delete(&regex);
		return;
	}
	found = RegexMatch_GetCapture(&match, 0, str);
	if (expect == NULL)
	{
		printf("FAIL: /%s/ on \"%s\": matched \"%s\" (expected no match)\n", pattern, str, found);
		tests_failed++;
	}
	else if (found == NULL || strcmp(found, expect) != 0)
	{
		printf("FAIL: /%s/ on \"%s\": matched \"%s\" (expected \"%s\")\n", pattern, str, found ? found : "(null)", expect);
		tests_failed++;
	}
	if (found)	free(found);
	RegexMatch_Delete(&match);
	Regex_Delete(&regex);
}

// checks that `pattern` searches within `str` and that capture group `group` equals `expect`
static void	test_capture(char const* pattern, t_regex_options options, char const* str, t_uint group, char const* expect)
{
	s_regex*		regex;
	s_regex_match	match;
	t_utf8*			found;

	tests_total++;
	regex = Regex_New(pattern, options);
	if (regex == NULL)
	{
		printf("FAIL: /%s/ did not compile\n", pattern);
		tests_failed++;
		return;
	}
	if (!Regex_Search(regex, str, 0, &match))
	{
		printf("FAIL: /%s/ on \"%s\": no match\n", pattern, str);
		tests_failed++;
		Regex_Delete(&regex);
		return;
	}
	found = RegexMatch_GetCapture(&match, group, str);
	if (expect == NULL)
	{
		if (found != NULL)
		{
			printf("FAIL: /%s/ on \"%s\": group %u = \"%s\" (expected unmatched group)\n", pattern, str, (unsigned)group, found);
			tests_failed++;
		}
	}
	else if (found == NULL || strcmp(found, expect) != 0)
	{
		printf("FAIL: /%s/ on \"%s\": group %u = \"%s\" (expected \"%s\")\n", pattern, str, (unsigned)group, found ? found : "(null)", expect);
		tests_failed++;
	}
	if (found)	free(found);
	RegexMatch_Delete(&match);
	Regex_Delete(&regex);
}

// checks that `pattern` fails to compile
static void	test_badpattern(char const* pattern)
{
	s_regex*	regex;

	tests_total++;
	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex != NULL)
	{
		printf("FAIL: /%s/ compiled (expected a syntax error)\n", pattern);
		tests_failed++;
		Regex_Delete(&regex);
	}
}

// checks Regex_MatchEntire
static void	test_entire(char const* pattern, t_regex_options options, char const* str, int expect)
{
	s_regex*	regex;
	t_bool		result;

	tests_total++;
	regex = Regex_New(pattern, options);
	if (regex == NULL)
	{
		printf("FAIL: /%s/ did not compile\n", pattern);
		tests_failed++;
		return;
	}
	result = Regex_MatchEntire(regex, str);
	if ((result != 0) != (expect != 0))
	{
		printf("FAIL: /%s/ MatchEntire on \"%s\": %d (expected %d)\n", pattern, str, result, expect);
		tests_failed++;
	}
	Regex_Delete(&regex);
}

// checks Regex_ReplaceAll
static void	test_replace(char const* pattern, t_regex_options options, char const* str, char const* rep, char const* expect)
{
	s_regex*	regex;
	t_utf8*		result;

	tests_total++;
	regex = Regex_New(pattern, options);
	if (regex == NULL)
	{
		printf("FAIL: /%s/ did not compile\n", pattern);
		tests_failed++;
		return;
	}
	result = Regex_ReplaceAll(regex, str, rep);
	if (result == NULL || strcmp(result, expect) != 0)
	{
		printf("FAIL: /%s/ ReplaceAll(\"%s\", \"%s\") = \"%s\" (expected \"%s\")\n", pattern, str, rep, result ? result : "(null)", expect);
		tests_failed++;
	}
	if (result)	free(result);
	Regex_Delete(&regex);
}

// checks Regex_Split
static void	test_split(char const* pattern, char const* str, char const* expect_joined)
{
	s_regex*	regex;
	t_utf8**	parts;
	char		joined[1024];
	t_uint		i;

	tests_total++;
	regex = Regex_New(pattern, REGEX_OPTION_NONE);
	if (regex == NULL)
	{
		printf("FAIL: /%s/ did not compile\n", pattern);
		tests_failed++;
		return;
	}
	parts = Regex_Split(regex, str);
	joined[0] = '\0';
	if (parts)
	{
		for (i = 0; parts[i]; ++i)
		{
			if (i > 0)	strcat(joined, "|");
			strcat(joined, parts[i]);
			free(parts[i]);
		}
		free(parts);
	}
	if (strcmp(joined, expect_joined) != 0)
	{
		printf("FAIL: /%s/ Split(\"%s\") = \"%s\" (expected \"%s\")\n", pattern, str, joined, expect_joined);
		tests_failed++;
	}
	Regex_Delete(&regex);
}



int	main(void)
{
	// literals & basic escapes
	test_search("hello", 0, "say hello world", "hello");
	test_search("hello", 0, "say goodbye", NULL);
	test_search("a\\.b", 0, "xa.by", "a.b");
	test_search("a\\.b", 0, "xaXby", NULL);
	test_search("\\x41\\x{42}\\u0043", 0, "xABCy", "ABC");
	test_search("\\t\\n", 0, "a\t\nb", "\t\n");
	test_search("\\cI", 0, "a\tb", "\t");
	test_search("\\Qa.b*c\\E", 0, "xa.b*cy", "a.b*c");

	// char types & classes
	test_search("\\d+", 0, "abc 12345 def", "12345");
	test_search("\\w+", 0, "  foo_bar42  ", "foo_bar42");
	test_search("\\s+", 0, "ab \t cd", " \t ");
	test_search("\\D+", 0, "123abc456", "abc");
	test_search("[abc]+", 0, "zzabcaz", "abca");
	test_search("[^abc]+", 0, "abczzzabc", "zzz");
	test_search("[a-fA-F0-9]+", 0, "xyz DEADbeef42 uvw", "DEADbeef42");
	test_search("[[:digit:]]+", 0, "abc42def", "42");
	test_search("[[:^digit:]]+", 0, "42abc42", "abc");
	test_search("[\\d\\s]+", 0, "ab1 2 3cd", "1 2 3");
	test_search("[]x]+", 0, "ab]x]cd", "]x]");
	test_search("[a-]+", 0, "xy-a-z", "-a-");
	test_search("\\p{L}+", 0, "42abc42", "abc");
	test_search("\\p{Lu}+", 0, "aaBBBcc", "BBB");
	test_search("\\P{L}+", 0, "ab123cd", "123");
	test_search("\\h+", 0, "a \t b", " \t ");
	test_search("\\R", 0, "a\r\nb", "\r\n");

	// anchors
	test_search("^abc", 0, "abcdef", "abc");
	test_search("^bcd", 0, "abcdef", NULL);
	test_search("def$", 0, "abcdef", "def");
	test_search("abc$", 0, "abcdef", NULL);
	test_search("^abc$", 0, "abc", "abc");
	test_search("^b$", REGEX_OPTION_MULTILINE, "a\nb\nc", "b");
	test_search("^b$", 0, "a\nb\nc", NULL);
	test_search("\\bcat\\b", 0, "the cat sat", "cat");
	test_search("\\bcat\\b", 0, "concatenate", NULL);
	test_search("\\Bcat\\B", 0, "concatenate", "cat");
	test_search("\\Aabc", 0, "abcdef", "abc");
	test_search("def\\z", 0, "abcdef", "def");
	test_search("def\\Z", 0, "abcdef\n", "def");

	// quantifiers
	test_search("ab*c", 0, "xacx", "ac");
	test_search("ab*c", 0, "xabbbcx", "abbbc");
	test_search("ab+c", 0, "xacx", NULL);
	test_search("ab+c", 0, "xabbcx", "abbc");
	test_search("ab?c", 0, "xabcx", "abc");
	test_search("a{3}", 0, "aaaa", "aaa");
	test_search("a{2,3}", 0, "aaaa", "aaa");
	test_search("a{2,}", 0, "aaaa", "aaaa");
	test_search("a{5}", 0, "aaaa", NULL);
	test_search("<.+>", 0, "<a> <b>", "<a> <b>");
	test_search("<.+?>", 0, "<a> <b>", "<a>");
	test_search("<.+>", REGEX_OPTION_UNGREEDY, "<a> <b>", "<a>");
	test_search("a{2}", 0, "xaax", "aa");
	test_search("x{abc", 0, "yx{abcz", "x{abc"); // malformed {} is a literal

	// possessive quantifiers & atomic groups
	test_search("a*+a", 0, "aaa", NULL);
	test_search("a*a", 0, "aaa", "aaa");
	test_search("(?>a*)a", 0, "aaa", NULL);
	test_search("(?>ab|a)c", 0, "abc", "abc");
	test_search("(?>ab|a)bc", 0, "abc", NULL);

	// alternation & groups
	test_search("cat|dog", 0, "hotdog", "dog");
	test_search("(cat|dog)food", 0, "dogfood", "dogfood");
	test_capture("(a+)(b+)", 0, "xaabbbx", 1, "aa");
	test_capture("(a+)(b+)", 0, "xaabbbx", 2, "bbb");
	test_capture("(a(b(c)))", 0, "abc", 3, "c");
	test_capture("(a)|(b)", 0, "b", 2, "b");
	test_capture("(a)|(b)", 0, "b", 1, NULL); // group 1 did not participate
	test_search("(?:abc)+", 0, "xabcabcy", "abcabc");

	// named groups & backreferences
	test_capture("(?<word>\\w+) \\k<word>", 0, "hey hey you", 1, "hey");
	test_search("(\\w+) \\1", 0, "hey hey you", "hey hey");
	test_search("(\\w+) \\1", 0, "abc def", NULL);
	test_capture("(?P<year>\\d{4})-(?P<month>\\d{2})", 0, "on 2024-06-15", 2, "06");
	test_capture("(?'x'a+)(?'y'b+)", 0, "aabb", 2, "bb");
	test_search("(a|b)\\1", REGEX_OPTION_IGNORECASE, "bB", "bB");

	// lookarounds
	test_search("\\w+(?=;)", 0, "foo; bar", "foo");
	test_search("\\w+(?!;)", 0, "foo;", "fo");
	test_search("(?<=\\$)\\d+", 0, "price: $42 now", "42");
	test_search("(?<!\\$)\\b\\d+", 0, "$42 43", "43");
	test_search("(?<=ab+)c", 0, "xabbbc", "c"); // variable-length lookbehind
	test_search("(?<=^.{3})d", 0, "abcdef", "d");

	// inline options
	test_search("(?i)HELLO", 0, "say hello", "hello");
	test_search("(?i:HEL)LO", 0, "say helLO", "helLO");
	test_search("(?i:HEL)LO", 0, "say hello", NULL);
	test_search("a(?s:.)b", 0, "a\nb", "a\nb");
	test_search("a.b", 0, "a\nb", NULL);
	test_search("a.b", REGEX_OPTION_DOTALL, "a\nb", "a\nb");
	test_search("(?x) a  b\t# comment\nc", 0, "xabcy", "abc");

	// case-insensitive matching
	test_search("hello", REGEX_OPTION_IGNORECASE, "say HeLLo", "HeLLo");
	test_search("[a-z]+", REGEX_OPTION_IGNORECASE, "42ABC42", "ABC");
	test_search("[^a]+", REGEX_OPTION_IGNORECASE, "bbAbb", "bb"); // [^a] must not match 'A' when case-insensitive

	// UTF-8
	test_search("héllo", 0, "say héllo", "héllo");
	test_search("h.llo", 0, "say héllo", "héllo"); // '.' matches one multi-byte char
	test_search("[éà]+", 0, "xéàéy", "éàé");
	test_search("\\p{L}+", 0, "42héllo42", "héllo");
	test_search("é{2,3}", 0, "aééééb", "ééé");
	test_search("(?i)É", 0, "café é", "é");
	test_search("日本語", 0, "これは日本語です", "日本語");
	test_search("日.語", 0, "これは日本語です", "日本語");

	// entire-string matching
	test_entire("\\d+", 0, "12345", 1);
	test_entire("\\d+", 0, "123a5", 0);
	test_entire("a|ab", 0, "ab", 1); // must backtrack to find the full-span alternative

	// bad patterns
	test_badpattern("a(bc");
	test_badpattern("a)b*)");
	test_badpattern("a[bc");
	test_badpattern("*a");
	test_badpattern("\\q");
	test_badpattern("a{3,1}");
	test_badpattern("(?<name)");
	test_badpattern("\\p{NotARealProperty}");
	test_badpattern("\\5xy");
	test_badpattern("(?i_)x");

	// replace
	test_replace("world", 0, "hello world", "there", "hello there");
	test_replace("(\\w+)@(\\w+)", 0, "mail: bob@example", "$2 at $1", "mail: example at bob");
	test_replace("(?<user>\\w+)@(?<host>\\w+)", 0, "bob@example", "${host}/$<user>", "example/bob");
	test_replace("\\d+", 0, "a1b22c333", "<$0>", "a<1>b<22>c<333>");
	test_replace("a", 0, "aaa", "$$", "$$$");
	test_replace("nomatch", 0, "hello", "x", "hello");

	// split
	test_split(",\\s*", "a, b,c ,  d", "a|b|c |d");
	test_split("\\s+", "  foo   bar  baz ", "foo|bar|baz");
	test_split("x", "axbxc", "a|b|c");
	test_split("x", "xxaxx", "a");
	test_split("-", "no delimiters here", "no delimiters here");

	// group info
	{
		s_regex*	regex = Regex_New("(a)(?<foo>b)(?:c)(?<bar>d)", 0);
		tests_total++;
		if (regex == NULL
			|| Regex_GetGroupAmount(regex) != 3
			|| Regex_GetGroupIndex(regex, "foo") != 2
			|| Regex_GetGroupIndex(regex, "bar") != 3
			|| Regex_GetGroupIndex(regex, "baz") != -1
			|| Regex_GetGroupName(regex, 2) == NULL
			|| strcmp(Regex_GetGroupName(regex, 2), "foo") != 0
			|| Regex_GetGroupName(regex, 1) != NULL)
		{
			printf("FAIL: group info functions\n");
			tests_failed++;
		}
		Regex_Delete(&regex);
	}

	// SearchAll
	{
		t_uint			amount;
		s_regex*		regex = Regex_New("\\d+", 0);
		s_regex_match*	matches = Regex_SearchAll(regex, "a1b22c333", &amount);
		tests_total++;
		if (matches == NULL || amount != 3
			|| matches[0].length != 1 || matches[1].length != 2 || matches[2].length != 3)
		{
			printf("FAIL: SearchAll\n");
			tests_failed++;
		}
		if (matches)
		{
			for (t_uint i = 0; i < amount; ++i)
				RegexMatch_Delete(&matches[i]);
			free(matches);
		}
		Regex_Delete(&regex);
	}

	// catastrophic backtracking should abort safely (no hang/crash)
	{
		s_regex*	regex = Regex_New("(a+)+$", 0);
		tests_total++;
		if (Regex_Matches(regex, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"))
		{
			printf("FAIL: catastrophic pattern should not match\n");
			tests_failed++;
		}
		Regex_Delete(&regex);
	}

	printf("regex tests: %d/%d passed\n", tests_total - tests_failed, tests_total);
	return (tests_failed == 0 ? 0 : 1);
}
