
#include <ctype.h>

#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



/*
**	Test data:
**
**	mbsarr1_as_str: "お前はもう死んでいる" (split by 'う' -> mbsarr1)
**	mbsarr2_as_str: "なはなはな"           (split by 'は' -> mbsarr2)
**	mbsarr3_as_str: "生きろ。x生きろ。xx生きろ。" (split by "x" -> keeps empty parts)
*/

static t_utf8 const*	mbsarr_empty[1] = { NULL };

static t_utf8 const*	mbsarr1_as_str = (t_utf8 const*)"お前はもう死んでいる";
static t_utf8 const*	mbsarr1[3] = {
	(t_utf8 const*)"お前はも",
	(t_utf8 const*)"死んでいる",
	NULL
};

static t_utf8 const*	mbsarr2_as_str = (t_utf8 const*)"なはなはな";
static t_utf8 const*	mbsarr2[4] = {
	(t_utf8 const*)"な",
	(t_utf8 const*)"な",
	(t_utf8 const*)"な",
	NULL
};

static t_utf8 const*	mbsarr3_as_str = (t_utf8 const*)"生きろ。x生きろ。xx生きろ。";
static t_utf8 const*	mbsarr3[5] = {
	(t_utf8 const*)"生きろ。",
	(t_utf8 const*)"生きろ。",
	(t_utf8 const*)"",
	(t_utf8 const*)"生きろ。",
	NULL
};

static t_utf8 const*	mbsarr_jp_divided[5] = {
	(t_utf8 const*)"お前は",
	(t_utf8 const*)"もう死",
	(t_utf8 const*)"んでい",
	(t_utf8 const*)"る",
	NULL
};

static t_utf8 const*	mbsarr_emoji_divided[4] = {
	(t_utf8 const*)"a\xF0\x9F\x98\x80",
	(t_utf8 const*)"b\xE3\x88\x8E",
	(t_utf8 const*)"c",
	NULL
};



/*============================================================================*\
||                        Basic StringArray Operations                        ||
\*============================================================================*/



#ifndef c_mbsarrlen
void test_mbsarrlen(void)	{}
#warning "mbsarrlen() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrlen(char const* test_name, t_testflags flags,
		t_uint			expecting,
		t_utf8 const**	strarr)
{
	TEST_INIT(uint)
	TEST_PERFORM(	mbsarrlen, strarr)
	TEST_PRINT(uint,mbsarrlen, "strarr=%p", (void*)strarr)
}
void	test_mbsarrlen(void)
{
//	| TEST FUNCTION    | TEST NAME                  | TESTFLAGS      | EXPECTING | TEST ARGS
	print_test_mbsarrlen("mbsarrlen              ",   FALSE          , 2,          mbsarr1);
	print_test_mbsarrlen("mbsarrlen              ",   FALSE          , 3,          mbsarr2);
	print_test_mbsarrlen("mbsarrlen              ",   FALSE          , 4,          mbsarr3);
	print_test_mbsarrlen("mbsarrlen (empty)      ",   FALSE          , 0,          mbsarr_empty);
	print_test_mbsarrlen("mbsarrlen (null)       ",   ALLOW_SIGSEGV  , 0,          NULL);
}
#endif



#ifndef c_mbsarrlens
void test_mbsarrlens(void)	{}
#warning "mbsarrlens() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrlens(char const* test_name, t_testflags flags,
		t_size			expecting,
		t_utf8 const**	strarr,
		t_uint			n)
{
	TEST_INIT(size)
	TEST_PERFORM(	mbsarrlens, strarr, n)
	TEST_PRINT(size,mbsarrlens, "strarr=%p, n=" SF_UINT, (void*)strarr, n)
}
void	test_mbsarrlens(void)
{
//	| TEST FUNCTION      | TEST NAME                   | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrlens("mbsarrlens             ",     FALSE     , 27,         mbsarr1, 2);
	print_test_mbsarrlens("mbsarrlens (capped)    ",     FALSE     , 12,         mbsarr1, 1);
	print_test_mbsarrlens("mbsarrlens (n too big) ",     FALSE     ,  9,         mbsarr2, 99);
}
#endif



/*============================================================================*\
||                          String Splitting Operations                       ||
\*============================================================================*/



#ifndef c_mbssplit_char
void test_mbssplit_char(void)	{}
#warning "mbssplit_char() test suite function defined, but the function isn't defined."
#else
void	print_test_mbssplit_char(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const*	str,
		t_utf32			c)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbssplit_char, str, c)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbssplit_char, "str=\"%s\", c=U+%4.4X", str, c)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbssplit_char(void)
{
//	| TEST FUNCTION         | TEST NAME                        | TESTFLAGS      | EXPECTING     | TEST ARGS
	print_test_mbssplit_char("mbssplit_char (multibyte sep)",    FALSE          , mbsarr1,        mbsarr1_as_str, 0x3046/*う*/);
	print_test_mbssplit_char("mbssplit_char (multibyte sep)",    FALSE          , mbsarr2,        mbsarr2_as_str, 0x306F/*は*/);
	print_test_mbssplit_char("mbssplit_char (sep at edges) ",    FALSE          , mbsarr_empty,   (t_utf8 const*)"ははは", 0x306F/*は*/);
	print_test_mbssplit_char("mbssplit_char (null str)     ",    ALLOW_SIGSEGV  , NULL,           NULL, 'a');
}
#endif



#ifndef c_mbssplit_cset
void test_mbssplit_cset(void)	{}
#warning "mbssplit_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbssplit_cset(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const*	str,
		t_utf8 const*	sep_chars)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbssplit_cset, str, sep_chars)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbssplit_cset, "str=\"%s\", sep_chars=\"%s\"", str, sep_chars)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbssplit_cset(void)
{
	static t_utf8 const*	expect_jp[4] = {
		(t_utf8 const*)"お前はも",
		(t_utf8 const*)"死ん",
		(t_utf8 const*)"いる",
		NULL
	};
//	| TEST FUNCTION         | TEST NAME                    | TESTFLAGS      | EXPECTING | TEST ARGS
	print_test_mbssplit_cset("mbssplit_cset            ",    FALSE          , expect_jp,  mbsarr1_as_str, (t_utf8 const*)"うで");
	print_test_mbssplit_cset("mbssplit_cset            ",    FALSE          , mbsarr2,    mbsarr2_as_str, (t_utf8 const*)"は");
	print_test_mbssplit_cset("mbssplit_cset (null str) ",    ALLOW_SIGSEGV  , NULL,       NULL, (t_utf8 const*)"a");
	print_test_mbssplit_cset("mbssplit_cset (null sep) ",    ALLOW_SIGSEGV  , NULL,       mbsarr1_as_str, NULL);
}
#endif



#ifndef c_mbssplit_str
void test_mbssplit_str(void)	{}
#warning "mbssplit_str() test suite function defined, but the function isn't defined."
#else
void	print_test_mbssplit_str(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const*	str,
		t_utf8 const*	sep)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbssplit_str, str, sep)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbssplit_str, "str=\"%s\", sep=\"%s\"", str, sep)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbssplit_str(void)
{
	static t_utf8 const*	expect_jp[3] = {
		(t_utf8 const*)"お前はもう",
		(t_utf8 const*)"いる",
		NULL
	};
	static t_utf8 const*	expect_overlap[3] = {
		(t_utf8 const*)"",
		(t_utf8 const*)"|aa",
		NULL
	};
//	| TEST FUNCTION        | TEST NAME                          | TESTFLAGS      | EXPECTING       | TEST ARGS
	print_test_mbssplit_str("mbssplit_str (multibyte sep)   ",    FALSE          , expect_jp,        mbsarr1_as_str, (t_utf8 const*)"死んで");
	print_test_mbssplit_str("mbssplit_str (keeps empty part)",    FALSE          , mbsarr3,          mbsarr3_as_str, (t_utf8 const*)"x");
	print_test_mbssplit_str("mbssplit_str (overlap)         ",    FALSE          , expect_overlap,   (t_utf8 const*)"|||aa", (t_utf8 const*)"||");
	print_test_mbssplit_str("mbssplit_str (null str)        ",    ALLOW_SIGSEGV  , NULL,             NULL, (t_utf8 const*)"a");
	print_test_mbssplit_str("mbssplit_str (null sep)        ",    ALLOW_SIGSEGV  , NULL,             mbsarr1_as_str, NULL);
}
#endif



#ifndef c_mbsdivide
void test_mbsdivide(void)	{}
#warning "mbsdivide() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsdivide(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const*	str,
		t_size			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbsdivide, str, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbsdivide, "str=\"%s\", n=" SF_SIZE, str, n)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbsdivide(void)
{
	static t_utf8 const*	teststr_emoji = (t_utf8 const*)"a\xF0\x9F\x98\x80" "b\xE3\x88\x8E" "c";
//	| TEST FUNCTION      | TEST NAME                          | TESTFLAGS      | EXPECTING            | TEST ARGS
	print_test_mbsdivide("mbsdivide (glyph chunks)       ",     FALSE          , mbsarr_jp_divided,     mbsarr1_as_str, 3);
	print_test_mbsdivide("mbsdivide (mixed glyph sizes)  ",     FALSE          , mbsarr_emoji_divided,  teststr_emoji, 2);
	print_test_mbsdivide("mbsdivide (null str)           ",     ALLOW_SIGSEGV  , NULL,                  NULL, 2);
}
#endif



/*============================================================================*\
||                         StringArray Content Operations                     ||
\*============================================================================*/



#ifndef c_mbsarrequ
void test_mbsarrequ(void)	{}
#warning "mbsarrequ() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrequ(char const* test_name, t_testflags flags,
		t_bool			expecting,
		t_utf8 const**	strarr1,
		t_utf8 const**	strarr2)
{
	TEST_INIT(bool)
	TEST_PERFORM(	mbsarrequ, strarr1, strarr2)
	TEST_PRINT(bool,mbsarrequ, "strarr1=%p, strarr2=%p", (void*)strarr1, (void*)strarr2)
}
void	test_mbsarrequ(void)
{
	static t_utf8 const*	same_as_mbsarr2[4] = {
		(t_utf8 const*)"な",
		(t_utf8 const*)"な",
		(t_utf8 const*)"な",
		NULL
	};
	static t_utf8 const*	different[4] = {
		(t_utf8 const*)"な",
		(t_utf8 const*)"X",
		(t_utf8 const*)"な",
		NULL
	};
//	| TEST FUNCTION      | TEST NAME                          | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrequ("mbsarrequ (equal content)      ",     FALSE     , TRUE ,      mbsarr2, same_as_mbsarr2);
	print_test_mbsarrequ("mbsarrequ (same pointer)       ",     FALSE     , TRUE ,      mbsarr2, mbsarr2);
	print_test_mbsarrequ("mbsarrequ (different content)  ",     FALSE     , FALSE,      mbsarr2, different);
	print_test_mbsarrequ("mbsarrequ (different lengths)  ",     FALSE     , FALSE,      mbsarr2, mbsarr1);
	print_test_mbsarrequ("mbsarrequ (empty vs empty)     ",     FALSE     , TRUE ,      mbsarr_empty, mbsarr_empty);
}
#endif



#ifndef c_mbsarrfindi
void test_mbsarrfindi(void)	{}
#warning "mbsarrfindi() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrfindi(char const* test_name, t_testflags flags,
		t_sint			expecting,
		t_utf8 const**	strarr,
		t_utf8 const*	str)
{
	TEST_INIT(sint)
	TEST_PERFORM(	mbsarrfindi, strarr, str)
	TEST_PRINT(sint,mbsarrfindi, "strarr=%p, str=\"%s\"", (void*)strarr, str)
}
void	test_mbsarrfindi(void)
{
//	| TEST FUNCTION        | TEST NAME                 | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrfindi("mbsarrfindi           ",     FALSE     , 1,          mbsarr1, (t_utf8 const*)"死んでいる");
	print_test_mbsarrfindi("mbsarrfindi (first)   ",     FALSE     , 0,          mbsarr2, (t_utf8 const*)"な");
	print_test_mbsarrfindi("mbsarrfindi (empty)   ",     FALSE     , 2,          mbsarr3, (t_utf8 const*)"");
	print_test_mbsarrfindi("mbsarrfindi (absent)  ",     FALSE     , ERROR,      mbsarr1, (t_utf8 const*)"zz");
}
#endif



#ifndef c_mbsarrcount_char
void test_mbsarrcount_char(void)	{}
#warning "mbsarrcount_char() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrcount_char(char const* test_name, t_testflags flags,
		t_uint			expecting,
		t_utf8 const**	strarr,
		t_utf32			c)
{
	TEST_INIT(uint)
	TEST_PERFORM(	mbsarrcount_char, strarr, c)
	TEST_PRINT(uint,mbsarrcount_char, "strarr=%p, c=U+%4.4X", (void*)strarr, c)
}
void	test_mbsarrcount_char(void)
{
//	| TEST FUNCTION             | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrcount_char("mbsarrcount_char          ",     FALSE     , 3,          mbsarr2, 0x306A/*な*/);
	print_test_mbsarrcount_char("mbsarrcount_char (1 match)",     FALSE     , 1,          mbsarr1, 0x3093/*ん*/);
	print_test_mbsarrcount_char("mbsarrcount_char (absent) ",     FALSE     , 0,          mbsarr2, 'z');
}
#endif



#ifndef c_mbsarrcount_cset
void test_mbsarrcount_cset(void)	{}
#warning "mbsarrcount_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrcount_cset(char const* test_name, t_testflags flags,
		t_uint			expecting,
		t_utf8 const**	strarr,
		t_utf8 const*	cset)
{
	TEST_INIT(uint)
	TEST_PERFORM(	mbsarrcount_cset, strarr, cset)
	TEST_PRINT(uint,mbsarrcount_cset, "strarr=%p, cset=\"%s\"", (void*)strarr, cset)
}
void	test_mbsarrcount_cset(void)
{
//	| TEST FUNCTION             | TEST NAME                | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrcount_cset("mbsarrcount_cset     ",      FALSE     , 3,          mbsarr1, (t_utf8 const*)"おんる");
	print_test_mbsarrcount_cset("mbsarrcount_cset     ",      FALSE     , 3,          mbsarr2, (t_utf8 const*)"なは");
}
#endif



#ifndef c_mbsarrcount_str
void test_mbsarrcount_str(void)	{}
#warning "mbsarrcount_str() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrcount_str(char const* test_name, t_testflags flags,
		t_uint			expecting,
		t_utf8 const**	strarr,
		t_utf8 const*	query)
{
	TEST_INIT(uint)
	TEST_PERFORM(	mbsarrcount_str, strarr, query)
	TEST_PRINT(uint,mbsarrcount_str, "strarr=%p, query=\"%s\"", (void*)strarr, query)
}
void	test_mbsarrcount_str(void)
{
//	| TEST FUNCTION            | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrcount_str("mbsarrcount_str          ",     FALSE     , 3,          mbsarr3, (t_utf8 const*)"生きろ。");
	print_test_mbsarrcount_str("mbsarrcount_str (partial)",     FALSE     , 1,          mbsarr1, (t_utf8 const*)"んでい");
	print_test_mbsarrcount_str("mbsarrcount_str (absent) ",     FALSE     , 0,          mbsarr1, (t_utf8 const*)"zz");
}
#endif



/*============================================================================*\
||                        StringArray Transform Operations                    ||
\*============================================================================*/



#ifndef c_mbsarrconcat
void test_mbsarrconcat(void)	{}
#warning "mbsarrconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrconcat(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const**	strarr1,
		t_utf8 const**	strarr2)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbsarrconcat, strarr1, strarr2)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbsarrconcat, "strarr1=%p, strarr2=%p", (void*)strarr1, (void*)strarr2)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbsarrconcat(void)
{
	static t_utf8 const*	expect[6] = {
		(t_utf8 const*)"お前はも",
		(t_utf8 const*)"死んでいる",
		(t_utf8 const*)"な",
		(t_utf8 const*)"な",
		(t_utf8 const*)"な",
		NULL
	};
//	| TEST FUNCTION         | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrconcat("mbsarrconcat              ",     FALSE     , expect,     mbsarr1, mbsarr2);
	print_test_mbsarrconcat("mbsarrconcat (lhs empty)  ",     FALSE     , mbsarr2,    mbsarr_empty, mbsarr2);
	print_test_mbsarrconcat("mbsarrconcat (rhs empty)  ",     FALSE     , mbsarr1,    mbsarr1, mbsarr_empty);
}
#endif



#ifndef c_mbsarrsub
void test_mbsarrsub(void)	{}
#warning "mbsarrsub() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrsub(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const**	strarr,
		t_uint			start,
		t_uint			length)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbsarrsub, strarr, start, length)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbsarrsub, "strarr=%p, start=" SF_UINT ", length=" SF_UINT, (void*)strarr, start, length)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbsarrsub(void)
{
	static t_utf8 const*	expect[3] = {
		(t_utf8 const*)"",
		(t_utf8 const*)"生きろ。",
		NULL
	};
//	| TEST FUNCTION      | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrsub("mbsarrsub                ",     FALSE     , expect,     mbsarr3, 2, 2);
	print_test_mbsarrsub("mbsarrsub (whole)        ",     FALSE     , mbsarr2,    mbsarr2, 0, 3);
	// NOTE: out-of-bounds cases (which return NULL) are covered by test/standalone/utf8_strings.c,
	// because print_test_strarr() does not support a NULL result/expect without ALLOW_SIGSEGV.
}
#endif



#ifndef c_mbsarrrev
void test_mbsarrrev(void)	{}
#warning "mbsarrrev() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrrev(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const**	strarr)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbsarrrev, strarr)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbsarrrev, "strarr=%p", (void*)strarr)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbsarrrev(void)
{
	static t_utf8 const*	expect[3] = {
		(t_utf8 const*)"死んでいる",
		(t_utf8 const*)"お前はも",
		NULL
	};
//	| TEST FUNCTION      | TEST NAME                | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrrev("mbsarrrev            ",     FALSE     , expect,     mbsarr1);
	print_test_mbsarrrev("mbsarrrev (palindrome)",    FALSE     , mbsarr2,    mbsarr2);
}
#endif



#ifndef c_mbsarrpadl
void test_mbsarrpadl(void)	{}
#warning "mbsarrpadl() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsarrpadl(char const* test_name, t_testflags flags,
		t_utf8 const**	expecting,
		t_utf8 const**	strarr,
		t_utf32			c,
		t_uint			n)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_mbsarrpadl, strarr, c, n)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	mbsarrpadl, "strarr=%p, c=U+%4.4X, n=" SF_UINT, (void*)strarr, c, n)
	TEST_FREE_RESULT(c_mbsarrfree)
}
void	test_mbsarrpadl(void)
{
	static t_utf8 const*	expect[4] = {
		(t_utf8 const*)"ーーな",
		(t_utf8 const*)"ーーな",
		(t_utf8 const*)"ーーな",
		NULL
	};
//	| TEST FUNCTION       | TEST NAME       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsarrpadl("mbsarrpadl   ",     FALSE     , expect,     mbsarr2, 0x30FC/*ー*/, 3);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int	testsuite_text_stringarray_utf8(void)
{
	print_suite_title("libccc/text/stringarray/utf8");

	print_nonstd();

	test_mbsarrlen();
	test_mbsarrlens();

	test_mbssplit_char();
	test_mbssplit_cset();
	test_mbssplit_str();
	test_mbsdivide();

	test_mbsarrequ();
	test_mbsarrfindi();
	test_mbsarrcount_char();
	test_mbsarrcount_cset();
	test_mbsarrcount_str();

	test_mbsarrconcat();
	test_mbsarrsub();
	test_mbsarrrev();
	test_mbsarrpadl();

	return (OK);
}
