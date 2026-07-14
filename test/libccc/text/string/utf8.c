
#include <ctype.h>
#include <string.h>

#include "libccc/text/string/utf8.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



/*
**	Test strings (with byte offsets of each symbol, for `Find` result pointers):
**
**	teststr_jp:    "お前はもう死んでいる" 10 symbols, 30 bytes (each symbol is 3 bytes)
**	                お:0 前:3 は:6 も:9 う:12 死:15 ん:18 で:21 い:24 る:27
**	teststr_mixed: "Omae wa 死んでいる!"  14 symbols, 24 bytes
**	                O:0 m:1 a:2 e:3 ' ':4 w:5 a:6 ' ':7 死:8 ん:11 で:14 い:17 る:20 !:23
**	teststr_emoji: "a😀b㈎c"              5 symbols, 10 bytes
**	                a:0 😀:1(4 bytes) b:5 ㈎:6(3 bytes) c:9
**	teststr_nana:  "なはなはな"           5 symbols, 15 bytes
**	                な:0 は:3 な:6 は:9 な:12
*/
static t_utf8 const* teststr_jp    = (t_utf8 const*)"お前はもう死んでいる";
static t_utf8 const* teststr_mixed = (t_utf8 const*)"Omae wa 死んでいる!";
static t_utf8 const* teststr_emoji = (t_utf8 const*)"a\xF0\x9F\x98\x80""b\xE3\x88\x8E""c";
static t_utf8 const* teststr_nana  = (t_utf8 const*)"なはなはな";



/*============================================================================*\
||                             String Length/Chars                            ||
\*============================================================================*/

#ifndef c_mbslen
void test_mbslen(void)	{}
#warning "mbslen() test suite function defined, but the function isn't defined."
#else
void	print_test_mbslen(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str)
{
	TEST_INIT(size)
	TEST_PERFORM(mbslen, str)
	TEST_PRINT(size, mbslen, "str=\"%s\"", str)
}
void	test_mbslen(void)
{
//	| TEST FUNCTION  | TEST NAME                  | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbslen("mbslen (jp, 3-byte chars) ", FALSE        , 30        , teststr_jp);
	print_test_mbslen("mbslen (mixed ascii/jp)   ", FALSE        , 24        , teststr_mixed);
	print_test_mbslen("mbslen (emoji, 4-byte)    ", FALSE        , 10        , teststr_emoji);
	print_test_mbslen("mbslen (ascii only)       ", FALSE        , 22        , (t_utf8 const*)"Omae wa mou shindeiru.");
	print_test_mbslen("mbslen (empty)            ", FALSE        , 0         , (t_utf8 const*)"");
	print_test_mbslen("mbslen (null)             ", ALLOW_SIGSEGV, 0         , NULL);
}
#endif

#ifndef c_mbsnlen
void test_mbsnlen(void)	{}
#warning "mbsnlen() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsnlen(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str,
		t_size n)
{
	TEST_INIT(size)
	TEST_PERFORM(mbsnlen, str, n)
	TEST_PRINT(size, mbsnlen, "str=\"%s\", n=" SF_SIZE, str, n)
}
void	test_mbsnlen(void)
{
//	| TEST FUNCTION   | TEST NAME                | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbsnlen("mbsnlen (n < length)    ", FALSE        , 7         , teststr_jp, 7);
	print_test_mbsnlen("mbsnlen (n > length)    ", FALSE        , 30        , teststr_jp, 100);
	print_test_mbsnlen("mbsnlen (n = 0)         ", FALSE        , 0         , teststr_jp, 0);
	print_test_mbsnlen("mbsnlen (empty)         ", FALSE        , 0         , (t_utf8 const*)"", 5);
	print_test_mbsnlen("mbsnlen (null)          ", ALLOW_SIGSEGV, 0         , NULL, 5);
}
#endif

#ifndef c_mbsclen
void test_mbsclen(void)	{}
#warning "mbsclen() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsclen(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str)
{
	TEST_INIT(size)
	TEST_PERFORM(mbsclen, str)
	TEST_PRINT(size, mbsclen, "str=\"%s\"", str)
}
void	test_mbsclen(void)
{
	// NOTE: regression tests: `StringUTF8_Chars()` used to return the byte-length instead of the symbol count
//	| TEST FUNCTION   | TEST NAME                  | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbsclen("mbsclen (jp, 3-byte chars)", FALSE        , 10        , teststr_jp);
	print_test_mbsclen("mbsclen (mixed ascii/jp)  ", FALSE        , 14        , teststr_mixed);
	print_test_mbsclen("mbsclen (emoji, 4-byte)   ", FALSE        , 5         , teststr_emoji);
	print_test_mbsclen("mbsclen (ascii only)      ", FALSE        , 22        , (t_utf8 const*)"Omae wa mou shindeiru.");
	print_test_mbsclen("mbsclen (empty)           ", FALSE        , 0         , (t_utf8 const*)"");
	print_test_mbsclen("mbsclen (null)            ", ALLOW_SIGSEGV, 0         , NULL);
}
#endif

#ifndef c_mbsnclen
void test_mbsnclen(void)	{}
#warning "mbsnclen() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsnclen(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str,
		t_size n)
{
	TEST_INIT(size)
	TEST_PERFORM(mbsnclen, str, n)
	TEST_PRINT(size, mbsnclen, "str=\"%s\", n=" SF_SIZE, str, n)
}
void	test_mbsnclen(void)
{
//	| TEST FUNCTION    | TEST NAME                | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbsnclen("mbsnclen (n < chars)    ", FALSE        , 3         , teststr_jp, 3);
	print_test_mbsnclen("mbsnclen (n > chars)    ", FALSE        , 10        , teststr_jp, 100);
	print_test_mbsnclen("mbsnclen (emoji, n = 2) ", FALSE        , 2         , teststr_emoji, 2);
	print_test_mbsnclen("mbsnclen (empty)        ", FALSE        , 0         , (t_utf8 const*)"", 3);
	print_test_mbsnclen("mbsnclen (null)         ", ALLOW_SIGSEGV, 0         , NULL, 3);
}
#endif



/*============================================================================*\
||                             String Comparisons                             ||
\*============================================================================*/

#ifndef c_mbsequ
void test_mbsequ(void)	{}
#warning "mbsequ() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_utf8 const* str1,
		t_utf8 const* str2)
{
	TEST_INIT(bool)
	TEST_PERFORM(mbsequ, str1, str2)
	TEST_PRINT(bool, mbsequ, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_mbsequ(void)
{
//	| TEST FUNCTION  | TEST NAME                 | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbsequ("mbsequ (equal, jp)       ", FALSE        , TRUE      , teststr_jp, (t_utf8 const*)"お前はもう死んでいる");
	print_test_mbsequ("mbsequ (equal, emoji)    ", FALSE        , TRUE      , teststr_emoji, (t_utf8 const*)"a\xF0\x9F\x98\x80""b\xE3\x88\x8E""c");
	print_test_mbsequ("mbsequ (different)       ", FALSE        , FALSE     , teststr_jp, teststr_mixed);
	print_test_mbsequ("mbsequ (prefix, longer)  ", FALSE        , FALSE     , (t_utf8 const*)"abc", (t_utf8 const*)"ab");
	print_test_mbsequ("mbsequ (prefix, shorter) ", FALSE        , FALSE     , (t_utf8 const*)"ab", (t_utf8 const*)"abc");
	print_test_mbsequ("mbsequ (both empty)      ", FALSE        , TRUE      , (t_utf8 const*)"", (t_utf8 const*)"");
	print_test_mbsequ("mbsequ (one empty)       ", FALSE        , FALSE     , (t_utf8 const*)"", (t_utf8 const*)"a");
	print_test_mbsequ("mbsequ (null str1)       ", ALLOW_SIGSEGV, FALSE     , NULL, teststr_jp);
	print_test_mbsequ("mbsequ (null str2)       ", ALLOW_SIGSEGV, FALSE     , teststr_jp, NULL);
}
#endif

#ifndef c_mbsnequ
void test_mbsnequ(void)	{}
#warning "mbsnequ() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsnequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_utf8 const* str1,
		t_utf8 const* str2,
		t_size n)
{
	TEST_INIT(bool)
	TEST_PERFORM(mbsnequ, str1, str2, n)
	TEST_PRINT(bool, mbsnequ, "str1=\"%s\", str2=\"%s\", n=" SF_SIZE, str1, str2, n)
}
void	test_mbsnequ(void)
{
//	| TEST FUNCTION   | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsnequ("mbsnequ (matching prefix)   ", FALSE     , TRUE      , (t_utf8 const*)"abcdef", (t_utf8 const*)"abcXYZ", 3);
	print_test_mbsnequ("mbsnequ (differing at n)    ", FALSE     , FALSE     , (t_utf8 const*)"abcdef", (t_utf8 const*)"abcXYZ", 4);
	print_test_mbsnequ("mbsnequ (n = 0)             ", FALSE     , TRUE      , teststr_jp, teststr_mixed, 0);
	print_test_mbsnequ("mbsnequ (jp matching prefix)", FALSE     , TRUE      , (t_utf8 const*)"死んでいる", (t_utf8 const*)"死んだのか", 6);
	print_test_mbsnequ("mbsnequ (n > both lengths)  ", FALSE     , FALSE     , (t_utf8 const*)"abc", (t_utf8 const*)"ab", 10);
}
#endif

#ifndef c_mbsiequ
void test_mbsiequ(void)	{}
#warning "mbsiequ() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsiequ(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_utf8 const* str1,
		t_utf8 const* str2)
{
	TEST_INIT(bool)
	TEST_PERFORM(mbsiequ, str1, str2)
	TEST_PRINT(bool, mbsiequ, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_mbsiequ(void)
{
//	| TEST FUNCTION   | TEST NAME                    | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsiequ("mbsiequ (mixed case)        ", FALSE     , TRUE      , (t_utf8 const*)"HeLLo", (t_utf8 const*)"hello");
	print_test_mbsiequ("mbsiequ (full uppercase)    ", FALSE     , TRUE      , (t_utf8 const*)"HELLO", (t_utf8 const*)"hello");
	print_test_mbsiequ("mbsiequ (actually different)", FALSE     , FALSE     , (t_utf8 const*)"hella", (t_utf8 const*)"hello");
	print_test_mbsiequ("mbsiequ (jp, no case)       ", FALSE     , TRUE      , teststr_jp, (t_utf8 const*)"お前はもう死んでいる");
	print_test_mbsiequ("mbsiequ (both empty)        ", FALSE     , TRUE      , (t_utf8 const*)"", (t_utf8 const*)"");
	print_test_mbsiequ("mbsiequ (accented case)     ", FALSE     , TRUE      , (t_utf8 const*)"ÉCLAIR", (t_utf8 const*)"éclair");
	print_test_mbsiequ("mbsiequ (accented case)     ", FALSE     , TRUE      , (t_utf8 const*)"ÁÈîȮŪ", (t_utf8 const*)"áèîȯū");
	print_test_mbsiequ("mbsiequ (accented diff)     ", FALSE     , FALSE     , (t_utf8 const*)"ÁÈîȮŪ", (t_utf8 const*)"àèîȯū");
}
#endif

#ifndef c_mbscmp
void test_mbscmp(void)	{}
#warning "mbscmp() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		t_utf8 const* str1,
		t_utf8 const* str2)
{
	TEST_INIT(sign)
	TEST_PERFORM(mbscmp, str1, str2)
	TEST_PRINT(sign, mbscmp, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_mbscmp(void)
{
	// NOTE: regression tests: `StringUTF8_Compare()` used to return `0` for prefix cases
	// like ("abc" vs "ab"), and read uninitialized memory when a given string was empty
//	| TEST FUNCTION  | TEST NAME                  | TESTFLAGS    | EXPECTING | TEST ARGS
	print_test_mbscmp("mbscmp (equal)            ", FALSE        , 0         , (t_utf8 const*)"abc", (t_utf8 const*)"abc");
	print_test_mbscmp("mbscmp (prefix, longer)   ", FALSE        , +1        , (t_utf8 const*)"abc", (t_utf8 const*)"ab");
	print_test_mbscmp("mbscmp (prefix, shorter)  ", FALSE        , -1        , (t_utf8 const*)"ab", (t_utf8 const*)"abc");
	print_test_mbscmp("mbscmp (both empty)       ", FALSE        , 0         , (t_utf8 const*)"", (t_utf8 const*)"");
	print_test_mbscmp("mbscmp (empty vs nonempty)", FALSE        , -1        , (t_utf8 const*)"", (t_utf8 const*)"a");
	print_test_mbscmp("mbscmp (nonempty vs empty)", FALSE        , +1        , (t_utf8 const*)"a", (t_utf8 const*)"");
	print_test_mbscmp("mbscmp (jp equal)         ", FALSE        , 0         , teststr_jp, (t_utf8 const*)"お前はもう死んでいる");
	print_test_mbscmp("mbscmp (jp ordering <)    ", FALSE        , -1        , (t_utf8 const*)"あ", (t_utf8 const*)"い");
	print_test_mbscmp("mbscmp (jp ordering >)    ", FALSE        , +1        , (t_utf8 const*)"い", (t_utf8 const*)"あ");
	print_test_mbscmp("mbscmp (null str1)        ", ALLOW_SIGSEGV, -1        , NULL, teststr_jp);
	print_test_mbscmp("mbscmp (null str2)        ", ALLOW_SIGSEGV, +1        , teststr_jp, NULL);
}
#endif

#ifndef c_mbsncmp
void test_mbsncmp(void)	{}
#warning "mbsncmp() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsncmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		t_utf8 const* str1,
		t_utf8 const* str2,
		t_size n)
{
	TEST_INIT(sign)
	TEST_PERFORM(mbsncmp, str1, str2, n)
	TEST_PRINT(sign, mbsncmp, "str1=\"%s\", str2=\"%s\", n=" SF_SIZE, str1, str2, n)
}
void	test_mbsncmp(void)
{
//	| TEST FUNCTION   | TEST NAME                  | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsncmp("mbsncmp (n = 0)           ", FALSE     , 0         , teststr_jp, teststr_mixed, 0);
	print_test_mbsncmp("mbsncmp (equal prefix)    ", FALSE     , 0         , (t_utf8 const*)"abcdef", (t_utf8 const*)"abcxyz", 3);
	print_test_mbsncmp("mbsncmp (differing at n)  ", FALSE     , -1        , (t_utf8 const*)"abcdef", (t_utf8 const*)"abcxyz", 4);
	print_test_mbsncmp("mbsncmp (diff before n)   ", FALSE     , -1        , (t_utf8 const*)"abc", (t_utf8 const*)"abd", 3);
	print_test_mbsncmp("mbsncmp (prefix, n beyond)", FALSE     , +1        , (t_utf8 const*)"abc", (t_utf8 const*)"ab", 5);
}
#endif

#ifndef c_mbsicmp
void test_mbsicmp(void)	{}
#warning "mbsicmp() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsicmp(char const* test_name, t_testflags flags,
		t_sint expecting,
		t_utf8 const* str1,
		t_utf8 const* str2)
{
	TEST_INIT(sign)
	TEST_PERFORM(mbsicmp, str1, str2)
	TEST_PRINT(sign, mbsicmp, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_mbsicmp(void)
{
//	| TEST FUNCTION   | TEST NAME                  | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsicmp("mbsicmp (case-equal)      ", FALSE     , 0         , (t_utf8 const*)"HELLO", (t_utf8 const*)"hello");
	print_test_mbsicmp("mbsicmp (case-different >)", FALSE     , +1        , (t_utf8 const*)"Hellp", (t_utf8 const*)"hello");
	print_test_mbsicmp("mbsicmp (prefix, shorter) ", FALSE     , -1        , (t_utf8 const*)"hell", (t_utf8 const*)"HELLO");
	print_test_mbsicmp("mbsicmp (both empty)      ", FALSE     , 0         , (t_utf8 const*)"", (t_utf8 const*)"");
}
#endif



/*============================================================================*\
||                          String Counting/Finding                           ||
\*============================================================================*/

#ifndef c_mbscount_char
void test_mbscount_char(void)	{}
#warning "mbscount_char() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscount_char(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str,
		t_utf32 c)
{
	TEST_INIT(size)
	TEST_PERFORM(mbscount_char, str, c)
	TEST_PRINT(size, mbscount_char, "str=\"%s\", c=U+%04X", str, c)
}
void	test_mbscount_char(void)
{
//	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbscount_char("mbscount_char (jp, multiple)  ", FALSE     , 3         , teststr_nana, 0x306A);// 'な'
	print_test_mbscount_char("mbscount_char (jp, single)    ", FALSE     , 1         , teststr_jp, 0x3044);// 'い'
	print_test_mbscount_char("mbscount_char (4-byte emoji)  ", FALSE     , 1         , teststr_emoji, 0x1F600);// '😀'
	print_test_mbscount_char("mbscount_char (ascii in mixed)", FALSE     , 2         , teststr_mixed, 'a');
	print_test_mbscount_char("mbscount_char (absent)        ", FALSE     , 0         , teststr_jp, 'z');
	print_test_mbscount_char("mbscount_char (empty str)     ", FALSE     , 0         , (t_utf8 const*)"", 'a');
}
#endif

#ifndef c_mbscount_cset
void test_mbscount_cset(void)	{}
#warning "mbscount_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscount_cset(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(size)
	TEST_PERFORM(mbscount_cset, str, charset)
	TEST_PRINT(size, mbscount_cset, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_mbscount_cset(void)
{
	// NOTE: regression tests: charset matching used to be done byte-wise, so multi-byte
	// symbols in the charset would falsely match other symbols sharing the same bytes
//	| TEST FUNCTION        | TEST NAME                        | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbscount_cset("mbscount_cset (ascii vowels)   ", FALSE     , 3         , teststr_mixed, (t_utf8 const*)"aeiou");
	print_test_mbscount_cset("mbscount_cset (jp charset)     ", FALSE     , 2         , teststr_jp, (t_utf8 const*)"んで");
	print_test_mbscount_cset("mbscount_cset (all jp symbols) ", FALSE     , 5         , teststr_nana, (t_utf8 const*)"なは");
	print_test_mbscount_cset("mbscount_cset (empty charset)  ", FALSE     , 0         , teststr_jp, (t_utf8 const*)"");
	print_test_mbscount_cset("mbscount_cset (empty str)      ", FALSE     , 0         , (t_utf8 const*)"", (t_utf8 const*)"abc");
}
#endif

#ifndef c_mbscount_str
void test_mbscount_str(void)	{}
#warning "mbscount_str() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscount_str(char const* test_name, t_testflags flags,
		t_size expecting,
		t_utf8 const* str,
		t_utf8 const* query)
{
	TEST_INIT(size)
	TEST_PERFORM(mbscount_str, str, query)
	TEST_PRINT(size, mbscount_str, "str=\"%s\", query=\"%s\"", str, query)
}
void	test_mbscount_str(void)
{
	// NOTE: regression tests: an occurrence at the very end of the string used to not be counted
//	| TEST FUNCTION       | TEST NAME                          | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbscount_str("mbscount_str (jp, incl. tail)    ", FALSE     , 2         , (t_utf8 const*)"ななこなな", (t_utf8 const*)"なな");
	print_test_mbscount_str("mbscount_str (jp, several)       ", FALSE     , 2         , teststr_nana, (t_utf8 const*)"なは");
	print_test_mbscount_str("mbscount_str (overlapping + tail)", FALSE     , 3         , (t_utf8 const*)"aaaa", (t_utf8 const*)"aa");
	print_test_mbscount_str("mbscount_str (single, jp)        ", FALSE     , 1         , teststr_jp, (t_utf8 const*)"死んで");
	print_test_mbscount_str("mbscount_str (whole string)      ", FALSE     , 1         , teststr_jp, (t_utf8 const*)"お前はもう死んでいる");
	print_test_mbscount_str("mbscount_str (absent)            ", FALSE     , 0         , teststr_jp, (t_utf8 const*)"ドリー");
	print_test_mbscount_str("mbscount_str (empty query)       ", FALSE     , 0         , teststr_jp, (t_utf8 const*)"");
}
#endif

#ifndef c_mbschr
void test_mbschr(void)	{}
#warning "mbschr() test suite function defined, but the function isn't defined."
#else
void	print_test_mbschr(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c)
{
	TEST_INIT(ptr)
	TEST_PERFORM(mbschr, str, c)
	TEST_PRINT(ptr, mbschr, "str=\"%s\", c=U+%04X", str, c)
}
void	test_mbschr(void)
{
//	| TEST FUNCTION  | TEST NAME                | TESTFLAGS | EXPECTING        | TEST ARGS
	print_test_mbschr("mbschr (jp, 3-byte char)", FALSE     , teststr_jp + 15  , teststr_jp, 0x6B7B);// '死'
	print_test_mbschr("mbschr (4-byte emoji)   ", FALSE     , teststr_emoji + 1, teststr_emoji, 0x1F600);// '😀'
	print_test_mbschr("mbschr (ascii in mixed) ", FALSE     , teststr_mixed + 2, teststr_mixed, 'a');
	print_test_mbschr("mbschr (last char)      ", FALSE     , teststr_mixed + 23, teststr_mixed, '!');
	print_test_mbschr("mbschr (absent)         ", FALSE     , NULL             , teststr_jp, 'z');
}
#endif

#ifndef c_mbschrset
void test_mbschrset(void)	{}
#warning "mbschrset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbschrset(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(ptr)
	TEST_PERFORM(mbschrset, str, charset)
	TEST_PRINT(ptr, mbschrset, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_mbschrset(void)
{
	// NOTE: regression tests: charset matching used to be done byte-wise, so a jp charset
	// would falsely match the first jp symbol of the string (via the shared 0xE3 lead byte)
//	| TEST FUNCTION     | TEST NAME                  | TESTFLAGS | EXPECTING        | TEST ARGS
	print_test_mbschrset("mbschrset (jp charset)    ", FALSE     , teststr_jp + 18  , teststr_jp, (t_utf8 const*)"んで");
	print_test_mbschrset("mbschrset (mixed str)     ", FALSE     , teststr_mixed + 8, teststr_mixed, (t_utf8 const*)"死ん");
	print_test_mbschrset("mbschrset (ascii charset) ", FALSE     , teststr_mixed + 4, teststr_mixed, (t_utf8 const*)" !");
	print_test_mbschrset("mbschrset (absent)        ", FALSE     , NULL             , teststr_jp, (t_utf8 const*)"zx");
	print_test_mbschrset("mbschrset (empty charset) ", FALSE     , NULL             , teststr_jp, (t_utf8 const*)"");
}
#endif

#ifndef c_mbsstr
void test_mbsstr(void)	{}
#warning "mbsstr() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsstr(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* query)
{
	TEST_INIT(ptr)
	TEST_PERFORM(mbsstr, str, query)
	TEST_PRINT(ptr, mbsstr, "str=\"%s\", query=\"%s\"", str, query)
}
void	test_mbsstr(void)
{
//	| TEST FUNCTION  | TEST NAME               | TESTFLAGS | EXPECTING         | TEST ARGS
	print_test_mbsstr("mbsstr (jp substring)  ", FALSE     , teststr_jp + 15   , teststr_jp, (t_utf8 const*)"死んで");
	print_test_mbsstr("mbsstr (jp suffix)     ", FALSE     , teststr_jp + 24   , teststr_jp, (t_utf8 const*)"いる");
	print_test_mbsstr("mbsstr (whole string)  ", FALSE     , teststr_jp        , teststr_jp, (t_utf8 const*)"お前はもう死んでいる");
	print_test_mbsstr("mbsstr (ascii in mixed)", FALSE     , teststr_mixed + 5 , teststr_mixed, (t_utf8 const*)"wa");
	print_test_mbsstr("mbsstr (absent)        ", FALSE     , NULL              , teststr_jp, (t_utf8 const*)"ドリー");
}
#endif

#ifndef c_mbsrchr
void test_mbsrchr(void)	{}
#warning "mbsrchr() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsrchr(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c)
{
	TEST_INIT(ptr)
	TEST_PERFORM(mbsrchr, str, c)
	TEST_PRINT(ptr, mbsrchr, "str=\"%s\", c=U+%04X", str, c)
}
void	test_mbsrchr(void)
{
//	| TEST FUNCTION   | TEST NAME                 | TESTFLAGS | EXPECTING          | TEST ARGS
	print_test_mbsrchr("mbsrchr (jp, last of 3)  ", FALSE     , teststr_nana + 12  , teststr_nana, 0x306A);// 'な'
	print_test_mbsrchr("mbsrchr (ascii in mixed) ", FALSE     , teststr_mixed + 6  , teststr_mixed, 'a');
	print_test_mbsrchr("mbsrchr (single match)   ", FALSE     , teststr_jp + 15    , teststr_jp, 0x6B7B);// '死'
	print_test_mbsrchr("mbsrchr (absent)         ", FALSE     , NULL               , teststr_jp, 'z');
}
#endif

#ifndef c_mbsrchrset
void test_mbsrchrset(void)	{}
#warning "mbsrchrset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsrchrset(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(ptr)
	TEST_PERFORM(mbsrchrset, str, charset)
	TEST_PRINT(ptr, mbsrchrset, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_mbsrchrset(void)
{
//	| TEST FUNCTION      | TEST NAME                   | TESTFLAGS | EXPECTING        | TEST ARGS
	print_test_mbsrchrset("mbsrchrset (jp, last of 2) ", FALSE     , teststr_nana + 9 , teststr_nana, (t_utf8 const*)"は");
	print_test_mbsrchrset("mbsrchrset (jp charset)    ", FALSE     , teststr_jp + 21  , teststr_jp, (t_utf8 const*)"んで");
	print_test_mbsrchrset("mbsrchrset (absent)        ", FALSE     , NULL             , teststr_jp, (t_utf8 const*)"zx");
	// NOTE: this documents current behavior: an empty charset returns a pointer to the string's '\0' terminator
	print_test_mbsrchrset("mbsrchrset (empty charset) ", FALSE     , teststr_jp + 30  , teststr_jp, (t_utf8 const*)"");
}
#endif





/*============================================================================*\
||                     String Creation/Deletion Operations                    ||
\*============================================================================*/

#ifndef c_mbscnew
void test_mbscnew(void)	{}
#warning "mbscnew() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscnew(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_size n,
		t_utf8 c)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbscnew, n, c)
	TEST_PRINT(str,	mbscnew, "n=" SF_SIZE ", c='%c'", n, c)
	TEST_FREE()
}
void	test_mbscnew(void)
{
//	| TEST FUNCTION    | TEST NAME              | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbscnew("mbscnew            ",     FALSE     , (t_utf8 const*)"xxx", 3, 'x');
	print_test_mbscnew("mbscnew (n = 0)    ",     FALSE     , (t_utf8 const*)"",    0, 'x');
}
#endif



#ifndef c_mbsdup
void test_mbsdup(void)	{}
#warning "mbsdup() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsdup(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsdup, str)
	TEST_PRINT(str,	mbsdup, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_mbsdup(void)
{
//	| TEST FUNCTION   | TEST NAME              | TESTFLAGS      | EXPECTING     | TEST ARGS
	print_test_mbsdup("mbsdup (jp)        ",     FALSE          , teststr_jp    , teststr_jp);
	print_test_mbsdup("mbsdup (empty)     ",     FALSE          , (t_utf8 const*)"", (t_utf8 const*)"");
	print_test_mbsdup("mbsdup (null)      ",     ALLOW_SIGSEGV  , NULL          , NULL);
}
#endif



#ifndef c_mbsndup
void test_mbsndup(void)	{}
#warning "mbsndup() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsndup(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_size n)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsndup, str, n)
	TEST_PRINT(str,	mbsndup, "str=\"%s\", n=" SF_SIZE, str, n)
	TEST_FREE()
}
void	test_mbsndup(void)
{
//	| TEST FUNCTION    | TEST NAME                     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsndup("mbsndup (whole)           ",     FALSE     , teststr_jp,               teststr_jp, 30);
	print_test_mbsndup("mbsndup (glyph boundary)  ",     FALSE     , (t_utf8 const*)"お前"  ,  teststr_jp, 6);
	print_test_mbsndup("mbsndup (mid-glyph)       ",     FALSE     , (t_utf8 const*)"お前"  ,  teststr_jp, 8);
	print_test_mbsndup("mbsndup (n too large)     ",     FALSE     , teststr_jp,               teststr_jp, 999);
	print_test_mbsndup("mbsndup (emoji mid-glyph) ",     FALSE     , (t_utf8 const*)"a"     ,  teststr_emoji, 3);
}
#endif



#ifndef c_mbschrdup
void test_mbschrdup(void)	{}
#warning "mbschrdup() test suite function defined, but the function isn't defined."
#else
void	print_test_mbschrdup(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbschrdup, str, c)
	TEST_PRINT(str,	mbschrdup, "str=\"%s\", c=U+%4.4X", str, c)
	TEST_FREE()
}
void	test_mbschrdup(void)
{
//	| TEST FUNCTION      | TEST NAME                 | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbschrdup("mbschrdup (jp)        ",     FALSE     , (t_utf8 const*)"お前はも", teststr_jp, 0x3046/*う*/);
	print_test_mbschrdup("mbschrdup (absent)    ",     FALSE     , teststr_jp,                teststr_jp, 'z');
	print_test_mbschrdup("mbschrdup (ascii)     ",     FALSE     , (t_utf8 const*)"a\xF0\x9F\x98\x80", teststr_emoji, 'b');
}
#endif



#ifndef c_mbscstdup
void test_mbscstdup(void)	{}
#warning "mbscstdup() test suite function defined, but the function isn't defined."
#else
void	print_test_mbscstdup(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbscstdup, str, charset)
	TEST_PRINT(str,	mbscstdup, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_mbscstdup(void)
{
//	| TEST FUNCTION      | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbscstdup("mbscstdup           ",     FALSE     , (t_utf8 const*)"お前はも", teststr_jp, (t_utf8 const*)"んう");
	print_test_mbscstdup("mbscstdup (absent)  ",     FALSE     , teststr_jp,                teststr_jp, (t_utf8 const*)"zx");
}
#endif



#ifndef c_mbsstrdup
void test_mbsstrdup(void)	{}
#warning "mbsstrdup() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsstrdup(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* target)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsstrdup, str, target)
	TEST_PRINT(str,	mbsstrdup, "str=\"%s\", target=\"%s\"", str, target)
	TEST_FREE()
}
void	test_mbsstrdup(void)
{
//	| TEST FUNCTION      | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsstrdup("mbsstrdup           ",     FALSE     , (t_utf8 const*)"お前はもう", teststr_jp, (t_utf8 const*)"死んで");
	print_test_mbsstrdup("mbsstrdup (absent)  ",     FALSE     , teststr_jp,                  teststr_jp, (t_utf8 const*)"qq");
}
#endif



/*============================================================================*\
||                          String Editing Operations                         ||
\*============================================================================*/

#ifndef c_mbssub
void test_mbssub(void)	{}
#warning "mbssub() test suite function defined, but the function isn't defined."
#else
void	print_test_mbssub(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_size index,
		t_size n)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbssub, str, index, n)
	TEST_PRINT(str,	mbssub, "str=\"%s\", index=" SF_SIZE ", n=" SF_SIZE, str, index, n)
	TEST_FREE()
}
void	test_mbssub(void)
{
//	| TEST FUNCTION   | TEST NAME                  | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbssub("mbssub                 ",     FALSE     , (t_utf8 const*)"死んで", teststr_jp, 15, 9);
	print_test_mbssub("mbssub (zero length)   ",     FALSE     , (t_utf8 const*)"",       teststr_jp, 15, 0);
	print_test_mbssub("mbssub (index too big) ",     FALSE     , NULL,                    teststr_jp, 31, 1);
	print_test_mbssub("mbssub (len too big)   ",     FALSE     , NULL,                    teststr_jp, 15, 16);
}
#endif



#ifndef c_mbsrev
void test_mbsrev(void)	{}
#warning "mbsrev() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsrev(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsrev, str)
	TEST_PRINT(str,	mbsrev, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_mbsrev(void)
{
//	| TEST FUNCTION   | TEST NAME              | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsrev("mbsrev (glyph order) ",   FALSE     , (t_utf8 const*)"るいでん死うもは前お", teststr_jp);
	print_test_mbsrev("mbsrev (mixed sizes) ",   FALSE     , (t_utf8 const*)"c\xE3\x88\x8E" "b\xF0\x9F\x98\x80" "a", teststr_emoji);
	print_test_mbsrev("mbsrev (empty)       ",   FALSE     , (t_utf8 const*)"", (t_utf8 const*)"");
}
#endif



#ifndef c_mbsinsert
void test_mbsinsert(void)	{}
#warning "mbsinsert() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsinsert(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* dest,
		t_utf8 const* src,
		t_size index)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsinsert, dest, src, index)
	TEST_PRINT(str,	mbsinsert, "dest=\"%s\", src=\"%s\", index=" SF_SIZE, dest, src, index)
	TEST_FREE()
}
void	test_mbsinsert(void)
{
//	| TEST FUNCTION      | TEST NAME                  | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsinsert("mbsinsert              ",     FALSE     , (t_utf8 const*)"お前はる",   (t_utf8 const*)"おはる", (t_utf8 const*)"前", 3);
	print_test_mbsinsert("mbsinsert (at start)   ",     FALSE     , (t_utf8 const*)"るab",       (t_utf8 const*)"ab", (t_utf8 const*)"る", 0);
	print_test_mbsinsert("mbsinsert (at end)     ",     FALSE     , (t_utf8 const*)"abる",       (t_utf8 const*)"ab", (t_utf8 const*)"る", 2);
	print_test_mbsinsert("mbsinsert (bad index)  ",     FALSE     , NULL,                        (t_utf8 const*)"ab", (t_utf8 const*)"る", 3);
}
#endif



#ifndef c_mbsremove
void test_mbsremove(void)	{}
#warning "mbsremove() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsremove(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* query)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsremove, str, query)
	TEST_PRINT(str,	mbsremove, "str=\"%s\", query=\"%s\"", str, query)
	TEST_FREE()
}
void	test_mbsremove(void)
{
//	| TEST FUNCTION      | TEST NAME                | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsremove("mbsremove            ",     FALSE     , (t_utf8 const*)"はは",         teststr_nana, (t_utf8 const*)"な");
	print_test_mbsremove("mbsremove (string)   ",     FALSE     , (t_utf8 const*)"お前はもういる", teststr_jp, (t_utf8 const*)"死んで");
	print_test_mbsremove("mbsremove (absent)   ",     FALSE     , teststr_jp,                    teststr_jp, (t_utf8 const*)"zz");
	print_test_mbsremove("mbsremove (empty)    ",     FALSE     , teststr_jp,                    teststr_jp, (t_utf8 const*)"");
}
#endif



#ifndef c_mbsrep_str
void test_mbsrep_str(void)	{}
#warning "mbsrep_str() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsrep_str(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* str_old,
		t_utf8 const* str_new)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsrep_str, str, str_old, str_new)
	TEST_PRINT(str,	mbsrep_str, "str=\"%s\", old=\"%s\", new=\"%s\"", str, str_old, str_new)
	TEST_FREE()
}
void	test_mbsrep_str(void)
{
//	| TEST FUNCTION       | TEST NAME                 | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsrep_str("mbsrep_str            ",     FALSE     , (t_utf8 const*)"お前はもう生きている", teststr_jp, (t_utf8 const*)"死んで", (t_utf8 const*)"生きて");
	print_test_mbsrep_str("mbsrep_str (shrink)   ",     FALSE     , (t_utf8 const*)"__な",                teststr_nana, (t_utf8 const*)"なは", (t_utf8 const*)"_");
	print_test_mbsrep_str("mbsrep_str (absent)   ",     FALSE     , teststr_jp,                           teststr_jp, (t_utf8 const*)"zz", (t_utf8 const*)"yy");
}
#endif



#ifndef c_mbsrep_cset
void test_mbsrep_cset(void)	{}
#warning "mbsrep_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsrep_cset(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* cset_old,
		t_utf8 const* cset_new)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsrep_cset, str, cset_old, cset_new)
	TEST_PRINT(str,	mbsrep_cset, "str=\"%s\", old=\"%s\", new=\"%s\"", str, cset_old, cset_new)
	TEST_FREE()
}
void	test_mbsrep_cset(void)
{
//	| TEST FUNCTION        | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsrep_cset("mbsrep_cset                 ",     FALSE     , (t_utf8 const*)"はなはなは", teststr_nana, (t_utf8 const*)"なは", (t_utf8 const*)"はな");
	print_test_mbsrep_cset("mbsrep_cset (size change)   ",     FALSE     , (t_utf8 const*)"aはaはa",    teststr_nana, (t_utf8 const*)"な", (t_utf8 const*)"a");
	print_test_mbsrep_cset("mbsrep_cset (bad counts)    ",     FALSE     , NULL,                        teststr_nana, (t_utf8 const*)"なは", (t_utf8 const*)"a");
	print_test_mbsrep_cset("mbsrep_cset (duplicates)    ",     FALSE     , NULL,                        teststr_nana, (t_utf8 const*)"なな", (t_utf8 const*)"ab");
}
#endif



#ifndef c_mbstrim
void test_mbstrim(void)	{}
#warning "mbstrim() test suite function defined, but the function isn't defined."
#else
void	print_test_mbstrim(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbstrim, str, charset)
	TEST_PRINT(str,	mbstrim, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_mbstrim(void)
{
//	| TEST FUNCTION    | TEST NAME                | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbstrim("mbstrim              ",     FALSE     , (t_utf8 const*)"おはよ", (t_utf8 const*)"ななおはよなな", (t_utf8 const*)"な");
	print_test_mbstrim("mbstrim (untouched)  ",     FALSE     , teststr_jp,              teststr_jp, (t_utf8 const*)"z");
	print_test_mbstrim("mbstrim (everything) ",     FALSE     , (t_utf8 const*)"",       teststr_nana, (t_utf8 const*)"なは");
}
#endif



#ifndef c_mbstriml
void test_mbstriml(void)	{}
#warning "mbstriml() test suite function defined, but the function isn't defined."
#else
void	print_test_mbstriml(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbstriml, str, charset)
	TEST_PRINT(str,	mbstriml, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_mbstriml(void)
{
//	| TEST FUNCTION     | TEST NAME     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbstriml("mbstriml    ",   FALSE     , (t_utf8 const*)"おはよなな", (t_utf8 const*)"ななおはよなな", (t_utf8 const*)"な");
}
#endif



#ifndef c_mbstrimr
void test_mbstrimr(void)	{}
#warning "mbstrimr() test suite function defined, but the function isn't defined."
#else
void	print_test_mbstrimr(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbstrimr, str, charset)
	TEST_PRINT(str,	mbstrimr, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_mbstrimr(void)
{
//	| TEST FUNCTION     | TEST NAME     | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbstrimr("mbstrimr    ",   FALSE     , (t_utf8 const*)"ななおはよ", (t_utf8 const*)"ななおはよなな", (t_utf8 const*)"な");
	print_test_mbstrimr("mbstrimr    ",   FALSE     , (t_utf8 const*)"ab",         (t_utf8 const*)"abでで",         (t_utf8 const*)"で");
}
#endif



#ifndef c_mbspad
void test_mbspad(void)	{}
#warning "mbspad() test suite function defined, but the function isn't defined."
#else
void	print_test_mbspad(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbspad, str, c, length)
	TEST_PRINT(str,	mbspad, "str=\"%s\", c=U+%4.4X, length=" SF_SIZE, str, c, length)
	TEST_FREE()
}
void	test_mbspad(void)
{
//	| TEST FUNCTION   | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbspad("mbspad (grow)       ",     FALSE     , (t_utf8 const*)"-お--",     (t_utf8 const*)"お", '-', 4);
	print_test_mbspad("mbspad (shrink)     ",     FALSE     , (t_utf8 const*)"もう死ん", teststr_jp, '-', 4);
	print_test_mbspad("mbspad (same size)  ",     FALSE     , teststr_jp,                 teststr_jp, '-', 10);
}
#endif



#ifndef c_mbspadl
void test_mbspadl(void)	{}
#warning "mbspadl() test suite function defined, but the function isn't defined."
#else
void	print_test_mbspadl(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbspadl, str, c, length)
	TEST_PRINT(str,	mbspadl, "str=\"%s\", c=U+%4.4X, length=" SF_SIZE, str, c, length)
	TEST_FREE()
}
void	test_mbspadl(void)
{
//	| TEST FUNCTION    | TEST NAME                       | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbspadl("mbspadl (grow, multibyte)   ",     FALSE     , (t_utf8 const*)"ははab", (t_utf8 const*)"ab", 0x306F/*は*/, 4);
	print_test_mbspadl("mbspadl (shrink keeps right)",     FALSE     , (t_utf8 const*)"でいる",  teststr_jp, '_', 3);
}
#endif



#ifndef c_mbspadr
void test_mbspadr(void)	{}
#warning "mbspadr() test suite function defined, but the function isn't defined."
#else
void	print_test_mbspadr(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbspadr, str, c, length)
	TEST_PRINT(str,	mbspadr, "str=\"%s\", c=U+%4.4X, length=" SF_SIZE, str, c, length)
	TEST_FREE()
}
void	test_mbspadr(void)
{
//	| TEST FUNCTION    | TEST NAME                      | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbspadr("mbspadr (grow, multibyte)  ",     FALSE     , (t_utf8 const*)"abはは", (t_utf8 const*)"ab", 0x306F/*は*/, 4);
	print_test_mbspadr("mbspadr (shrink keeps left)",     FALSE     , (t_utf8 const*)"お前は",  teststr_jp, '_', 3);
}
#endif



/*============================================================================*\
||                          String Checking Operations                        ||
\*============================================================================*/

#ifndef c_mbshas
void test_mbshas(void)	{}
#warning "mbshas() test suite function defined, but the function isn't defined."
#else
void	print_test_mbshas(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(bool)
	TEST_PERFORM(	mbshas, str, charset)
	TEST_PRINT(bool,mbshas, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_mbshas(void)
{
//	| TEST FUNCTION   | TEST NAME           | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbshas("mbshas (true)   ",     FALSE     , TRUE ,      teststr_jp, (t_utf8 const*)"z死");
	print_test_mbshas("mbshas (false)  ",     FALSE     , FALSE,      teststr_jp, (t_utf8 const*)"zx");
}
#endif



#ifndef c_mbshasonly
void test_mbshasonly(void)	{}
#warning "mbshasonly() test suite function defined, but the function isn't defined."
#else
void	print_test_mbshasonly(char const* test_name, t_testflags flags,
		t_bool expecting,
		t_utf8 const* str,
		t_utf8 const* charset)
{
	TEST_INIT(bool)
	TEST_PERFORM(	mbshasonly, str, charset)
	TEST_PRINT(bool,mbshasonly, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_mbshasonly(void)
{
//	| TEST FUNCTION       | TEST NAME               | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbshasonly("mbshasonly (true)   ",     FALSE     , TRUE ,      teststr_nana, (t_utf8 const*)"なは");
	print_test_mbshasonly("mbshasonly (false)  ",     FALSE     , FALSE,      teststr_jp,   (t_utf8 const*)"なは");
	print_test_mbshasonly("mbshasonly (empty)  ",     FALSE     , TRUE ,      (t_utf8 const*)"", (t_utf8 const*)"なは");
}
#endif



/*============================================================================*\
||                        String Concatenation Operations                     ||
\*============================================================================*/

#ifndef c_mbsconcat
void test_mbsconcat(void)	{}
#warning "mbsconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsconcat(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str1,
		t_utf8 const* str2)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsconcat, str1, str2)
	TEST_PRINT(str,	mbsconcat, "str1=\"%s\", str2=\"%s\"", str1, str2)
	TEST_FREE()
}
void	test_mbsconcat(void)
{
//	| TEST FUNCTION      | TEST NAME              | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsconcat("mbsconcat          ",     FALSE     , (t_utf8 const*)"お前はもう", (t_utf8 const*)"お前", (t_utf8 const*)"はもう");
	print_test_mbsconcat("mbsconcat (empty)  ",     FALSE     , teststr_jp,                  teststr_jp, (t_utf8 const*)"");
}
#endif



#ifndef c_mbsjoin
void test_mbsjoin(void)	{}
#warning "mbsjoin() test suite function defined, but the function isn't defined."
#else
void	print_test_mbsjoin(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const** strarr,
		t_utf8 const* sep)
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsjoin, strarr, sep)
	TEST_PRINT(str,	mbsjoin, "sep=\"%s\"", sep)
	TEST_FREE()
}
void	test_mbsjoin(void)
{
	static t_utf8 const*	strarr[4] = { (t_utf8 const*)"お", (t_utf8 const*)"前", (t_utf8 const*)"は", NULL };
//	| TEST FUNCTION    | TEST NAME             | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsjoin("mbsjoin           ",     FALSE     , (t_utf8 const*)"お・前・は", strarr, (t_utf8 const*)"・");
	print_test_mbsjoin("mbsjoin (empty sep)",    FALSE     , (t_utf8 const*)"お前は",     strarr, (t_utf8 const*)"");
}
#endif



/*============================================================================*\
||                        String Functional Operations                        ||
\*============================================================================*/

#ifndef c_mbsmap
void test_mbsmap(void)	{}
#warning "mbsmap() test suite function defined, but the function isn't defined."
#else
static t_utf32	test_mbsmap_na_to_ha(t_utf32 c)	{ return (c == 0x306A/*な*/ ? 0x306F/*は*/ : c); }
static t_utf32	test_mbsmap_b_to_emoji(t_utf32 c)	{ return (c == 'b' ? 0x1F600/*😀*/ : c); }
void	print_test_mbsmap(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_utf32 (*map)(t_utf32 c))
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsmap, str, map)
	TEST_PRINT(str,	mbsmap, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_mbsmap(void)
{
//	| TEST FUNCTION   | TEST NAME              | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsmap("mbsmap (same size)  ",    FALSE     , (t_utf8 const*)"ははははは", teststr_nana, test_mbsmap_na_to_ha);
	print_test_mbsmap("mbsmap (grows)      ",    FALSE     , (t_utf8 const*)"a\xF0\x9F\x98\x80\xF0\x9F\x98\x80\xE3\x88\x8E" "c", teststr_emoji, test_mbsmap_b_to_emoji);
}
#endif



#ifndef c_mbsfilter
void test_mbsfilter(void)	{}
#warning "mbsfilter() test suite function defined, but the function isn't defined."
#else
static t_bool	test_mbsfilter_ascii(t_utf32 c)		{ return (c < 0x80); }
static t_bool	test_mbsfilter_multibyte(t_utf32 c)	{ return (c >= 0x80); }
void	print_test_mbsfilter(char const* test_name, t_testflags flags,
		t_utf8 const* expecting,
		t_utf8 const* str,
		t_bool (*filter)(t_utf32 c))
{
	TEST_INIT(str)
	TEST_PERFORM(	mbsfilter, str, filter)
	TEST_PRINT(str,	mbsfilter, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_mbsfilter(void)
{
//	| TEST FUNCTION      | TEST NAME                   | TESTFLAGS | EXPECTING | TEST ARGS
	print_test_mbsfilter("mbsfilter (keep ascii)  ",     FALSE     , (t_utf8 const*)"abc", teststr_emoji, test_mbsfilter_ascii);
	print_test_mbsfilter("mbsfilter (keep others) ",     FALSE     , (t_utf8 const*)"\xF0\x9F\x98\x80\xE3\x88\x8E", teststr_emoji, test_mbsfilter_multibyte);
}
#endif


/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int	testsuite_text_string_utf8(void)
{
	print_suite_title("libccc/text/string/utf8");

	print_nonstd();

	test_mbslen();
	test_mbsnlen();
	test_mbsclen();
	test_mbsnclen();

	test_mbsequ();
	test_mbsnequ();
	test_mbsiequ();
	test_mbscmp();
	test_mbsncmp();
	test_mbsicmp();

	test_mbscount_char();
	test_mbscount_cset();
	test_mbscount_str();
	test_mbschr();
	test_mbschrset();
	test_mbsstr();
	test_mbsrchr();
	test_mbsrchrset();

	test_mbscnew();
	test_mbsdup();
	test_mbsndup();
	test_mbschrdup();
	test_mbscstdup();
	test_mbsstrdup();

	test_mbssub();
	test_mbsrev();
	test_mbsinsert();
	test_mbsremove();
	test_mbsrep_str();
	test_mbsrep_cset();

	test_mbstrim();
	test_mbstriml();
	test_mbstrimr();
	test_mbspad();
	test_mbspadl();
	test_mbspadr();

	test_mbshas();
	test_mbshasonly();

	test_mbsconcat();
	test_mbsjoin();

	test_mbsmap();
	test_mbsfilter();

	return (OK);
}
