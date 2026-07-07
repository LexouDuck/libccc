
#include <ctype.h>
#include <string.h>

#include "libccc/string.h"
#include "libccc/text/escape.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                          Basic String Operations                           ||
\*============================================================================*/

#ifndef c_strtoesc
void test_strtoesc(void)	{}
#warning "strtoesc() test suite function defined, but the function isn't defined."
#else
void	print_test_strtoesc(char const* test_name, t_testflags flags,
		t_size expected_out_len,
		t_size expected_out_readlen,
		char const* expecting,

		t_size max_writelen,
		t_char const* str,
		t_char const* charset,
		t_char const* const* aliases,
		f_force_encoding_for force_encoding_for,
		f_char_encoder char_encoder)
{
	t_size out_len;
	t_size out_readlen;

#define STRTOESC_ARGS "str=\"%s\", max_writelen='" SF_SIZE "', charset=\"%s\"", str, max_writelen, charset
	{
		TEST_INIT(str)
		TEST_PERFORM(strtoesc_e, &out_len, &out_readlen, max_writelen, str, charset, aliases, force_encoding_for, char_encoder)
		TEST_PRINT(str, strtoesc_e, STRTOESC_ARGS)
		TEST_FREE()
	}
	{
		TEST_INIT(size)
		test.result =          out_len;
		test.expect = expected_out_len;
		TEST_PRINT(size, strtoesc_e out_len, STRTOESC_ARGS)
	}
	{
		TEST_INIT(size)
		test.result =          out_readlen;
		test.expect = expected_out_readlen;
		TEST_PRINT(size, strtoesc_e out_readlen, STRTOESC_ARGS)
	}
}
void	test_strtoesc(void)
{
	t_char const* charset_ascii   =     "\\"   "'"   "\""   "/"   "?"  "\a"  "\b"  "\t"  "\n"  "\v"  "\f"  "\r" "\x1B" ;
	t_char const* aliases_ascii[] = { "\\\\","\\'","\\\"","\\/","\\?","\\a","\\b","\\t","\\n","\\v","\\f","\\r","\\e" };
	t_char const* charset_empty = "";
	t_char const* aliases_empty[] = { };
	t_char const* charset_a = "a";
	t_char const* aliases_a[] = { "backslash a" };
	t_char const* charset_withmultibyte = "나중 ";
	t_char const* aliases_witmultibyte[] = { "너", "중 (not 中)", "<space>" };
	t_char const* charset_abc = "abc";
	t_char const* aliases_c_null_a[] = { "C", NULL, "A" };
	t_char const* charset_invalid = "abc" "\xE0" "de";
	//                                     ^~~~ 11100000, invalid UTF8 start byte. In a different string to avoid warning

//	| TEST FUNCTION    | TEST NAME                                                                    |TESTFLAG| EXPECTING                 | TEST ARGS
	print_test_strtoesc("strtoesc simple"                                                             , FALSE, 13 , 13 , "hello world !" , SIZE_ERROR , "hello world !" , charset_ascii , aliases_ascii , NULL , ESCAPE_ENCODER_xFF);
//	print_test_strtoesc("strtoesc empty"                                                              , FALSE, 0  , 0  , ""              , SIZE_ERROR , ""              , charset_ascii , aliases_ascii , NULL , ESCAPE_ENCODER_xFF);
	print_test_strtoesc("strtoesc basic escapes"                                                      , FALSE, 47,  41, "\\tThis\\nis a text \\\\with \\v escaped\\\"symbols \\\'" , SIZE_ERROR, "\tThis\nis a text \\with \v escaped\"symbols \'", charset_ascii, aliases_ascii, NULL, NULL );
	print_test_strtoesc("strtoesc one escape"                                                         , FALSE,  2,   1, "\\\\" , SIZE_ERROR, "\\", charset_ascii, aliases_ascii, NULL, NULL);
	print_test_strtoesc("strtoesc only escapes"                                                       , FALSE, 18,   9, "\\\\\\n\\t\\e\\r\\v\\v\\v\\v" , SIZE_ERROR, "\\\n\t\x1B\r\v\v\v\v", charset_ascii, aliases_ascii, NULL, NULL);
	print_test_strtoesc("strtoesc encoded char"                                                       , FALSE, 24,  12,   "\\u751F\\u65E5\\u5FEB\\u6A02", SIZE_ERROR                             , "生日快樂", charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER_uFFFF                                        );
	print_test_strtoesc("strtoesc encoded char too big"                                               , FALSE, SIZE_ERROR, 5, NULL,         SIZE_ERROR, "@⍇\n𒍅¨쫊󿿿?????????????"   , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER_uFFFF);
	print_test_strtoesc("strtoesc max_writelen limited"                                               , FALSE,  3,   3, "TOT"                    ,  3 , "TOTO MANGE DU FOIN"          , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in middle of multi-byte char: 1 byte"          , FALSE, 14,  12, "Ich hei\\xDFe J"        , 15 , "Ich heiße Jürgen Volkswagen" , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in middle of multi-byte char: 2 bytes"         , FALSE, 14,  12, "Ich hei\\xDFe J"        , 16 , "Ich heiße Jürgen Volkswagen" , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in middle of multi-byte char: last byte"       , FALSE, 14,  12, "Ich hei\\xDFe J"        , 17 , "Ich heiße Jürgen Volkswagen" , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited right after multi-byte char"                   , FALSE, 18,  14, "Ich hei\\xDFe J\\xFC"   , 18 , "Ich heiße Jürgen Volkswagen" , charset_ascii, aliases_ascii, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in middle of alias : 1 byte"                   , FALSE, 24, 4, "backslash albackslash ak", 25 , "alakazam", charset_a, aliases_a, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited in middle of alias : 5 bytes"                  , FALSE, 24, 4, "backslash albackslash ak", 30 , "alakazam", charset_a, aliases_a, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited in middle of alias : last byte"                , FALSE, 24, 4, "backslash albackslash ak", 34 , "alakazam", charset_a, aliases_a, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited right after alias"                             , FALSE, 35, 5, "backslash albackslash akbackslash a", 35, "alakazam", charset_a, aliases_a, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited in encoding 1"                                 , FALSE, 10, 4, "\\U0001F600"       , 11, "😀㈎π", charset_a, aliases_a, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in encoding 2"                                 , FALSE, 10, 4, "\\U0001F600"       , 13, "😀㈎π", charset_a, aliases_a, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited in encoding 3"                                 , FALSE, 10, 4, "\\U0001F600"       , 15, "😀㈎π", charset_a, aliases_a, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc max_writelen limited right after encoding"                          , FALSE, 16, 7, "\\U0001F600\\u320E", 16, "😀㈎π", charset_a, aliases_a, ForceEncodingFor_NonASCII, ESCAPE_ENCODER);
	print_test_strtoesc("strtoesc multibyte charset and alias"                                        , FALSE, 45, 23, "너는<space>너중 (not 中)에<space>만너", SIZE_ERROR, "나는 나중에 만나", charset_withmultibyte, aliases_witmultibyte, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited multibyte charset and alias"                    , FALSE, 32, 16, "너는<space>너중 (not 中)에", 34, "나는 나중에 만나", charset_withmultibyte, aliases_witmultibyte, NULL, NULL);
	print_test_strtoesc("strtoesc max_writelen limited multibyte charset and alias in middle of alias" , FALSE, 16, 10, "너는<space>너", 28, "나는 나중에 만나", charset_withmultibyte, aliases_witmultibyte, NULL, NULL);
	print_test_strtoesc("strtoesc null alias", FALSE, 60, 54, "Aurious to see if my \\x62C\\x62y hCndles null CliCs AorreAtly", SIZE_ERROR, "curious to see if my baby handles null alias correctly", charset_abc, aliases_c_null_a, NULL, ESCAPE_ENCODER_xFF);
	print_test_strtoesc("strtoesc invalid mb sequence in charset", FALSE, SIZE_ERROR, SIZE_ERROR, NULL, SIZE_ERROR, "my charset :(", charset_invalid, aliases_ascii, NULL, ESCAPE_ENCODER_xFF);
	print_test_strtoesc("strtoesc empty charset and aliases", FALSE, 27, 27, "This call does nothing 😀", SIZE_ERROR, "This call does nothing 😀", charset_empty, aliases_empty, NULL, NULL);

	// regression test: codepoints whose low byte is 0x00 (like U+1F600) used to
	// falsely match the charset string's '\0' terminator (reading a garbage alias)
	print_test_strtoesc("strtoesc low-byte-0x00 codepoint passthrough", FALSE, 6, 6, "a\xF0\x9F\x98\x80""b", SIZE_ERROR, "a\xF0\x9F\x98\x80""b", charset_ascii, aliases_ascii, NULL, NULL);
	// a NULL `char_encoder` is allowed, but must cleanly fail if a char needs encoding
	print_test_strtoesc("strtoesc null encoder (needed)  ", FALSE, SIZE_ERROR, 2, NULL,  SIZE_ERROR, "xxbxx", charset_abc, aliases_c_null_a, NULL, NULL);
	print_test_strtoesc("strtoesc null encoder (unneeded)", FALSE, 3, 3, "xyz", SIZE_ERROR, "xyz",   charset_abc, aliases_c_null_a, NULL, NULL);
	// error cases: NULL arguments
	print_test_strtoesc("strtoesc null str    ", FALSE, SIZE_ERROR, SIZE_ERROR, NULL, SIZE_ERROR, NULL,    charset_ascii, aliases_ascii, NULL, NULL);
	print_test_strtoesc("strtoesc null charset", FALSE, SIZE_ERROR, SIZE_ERROR, NULL, SIZE_ERROR, "hello", NULL,          aliases_ascii, NULL, NULL);
	print_test_strtoesc("strtoesc null aliases", FALSE, SIZE_ERROR, SIZE_ERROR, NULL, SIZE_ERROR, "hello", charset_ascii, NULL,          NULL, NULL);
}
#endif

#ifndef c_strtoesc_e
void test_strtoescbuf(void)	{}
#warning "strtoescbuf() test suite function defined, but the function isn't defined."
#else
//! NOTE: this checks that the "Buf" variant fills the `dest` buffer with all
//! successfully-escaped content so far, even when the call fails with an error
static char*	c_gen_strtoescbuf_partial(void)
{
	t_char	buffer[64] = "UNTOUCHED";
	t_char const* charset = "abc";
	t_char const* aliases[] = { "A", NULL, "C" };
	t_size	out_readlen = 0;
	// the 'b' char has a NULL alias and needs encoding, but no encoder is given: error
	t_size	result = StringASCII_ToEscapedBuf_e(buffer, &out_readlen, sizeof(buffer), "xaxbxx", charset, aliases, NULL, NULL);
	char	serialized[96];
	snprintf(serialized, sizeof(serialized), "ret=" SF_SIZE ", read=" SF_SIZE ", buffer=\"%s\"",
		result, out_readlen, buffer);
	return (strdup(serialized));
}
void	print_test_strtoescbuf(char const* test_name, t_testflags flags,
		char const* expecting)
{
	TEST_INIT(str)
	TEST_PERFORM(gen_strtoescbuf_partial)
	TEST_PRINT(str, strtoescbuf_e, "str=\"xaxbxx\", charset=\"abc\", char_encoder=NULL")
	TEST_FREE()
}
void	test_strtoescbuf(void)
{
//	| TEST FUNCTION        | TEST NAME                        |TESTFLAG| EXPECTING
	print_test_strtoescbuf("strtoescbuf (partial on error)",	FALSE,	"ret=" "0" ", read=" "3" ", buffer=\"xAx\"");
}
#endif

#ifndef c_strtoasciiesc
void test_strtoasciiesc(void)	{}
#warning "strtoasciiesc() test suite function defined, but the function isn't defined."
#else
void	print_test_strtoasciiesc(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(strtoasciiesc, str)
	TEST_PRINT(str, strtoasciiesc, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_strtoasciiesc(void)
{
//	| TEST FUNCTION         | TEST NAME                         | TESTFLAGS| EXPECTING                                                   | TEST ARGS
	print_test_strtoasciiesc("strtoasciiesc no escape"          , FALSE    , "hello world !"                                             , "hello world !"                                   );
	// DZ_ON_REFACTOR_OF_SIZE_ERROR: uncomment next test
	// print_test_strtoasciiesc("strtoasciiesc empty string"    , FALSE    , ""                                                          , ""                                                );
	print_test_strtoasciiesc("strtoasciiesc basic escapes"      , FALSE    , "\\tThis\\nis a text \\\\with \\v escaped\\\"symbols \\\'"  , "\tThis\nis a text \\with \v escaped\"symbols \'" );
	print_test_strtoasciiesc("strtoasciiesc all escapes"        , FALSE    , "hard \\\\\\'\\\"\\/?\\a\\b\\t\\n\\v\\f\\r\\e string"       , "hard \\'\"/?\a\b\t\n\v\f\r\e string"             );
	print_test_strtoasciiesc("strtoasciiesc encoded char"       , FALSE    , "\\u751F\\u65E5\\u5FEB\\u6A02"                              , "生日快樂"                                         );
	print_test_strtoasciiesc("strtoasciiesc harder encoded char", FALSE    , "\\U00012345,\\u2347\\n\\xA8\\uCACA"                        , "𒍅,⍇\n¨쫊"                                       );
	print_test_strtoasciiesc("strtoasciiesc DEL char"           , FALSE    , "del: \\x7F !"                                             , "del: \x7F !"                                    );
	print_test_strtoasciiesc("strtoasciiesc low-byte-0x00 char"  , FALSE    , "a\\U0001F600b"                                            , "a\xF0\x9F\x98\x80""b"                        );
	print_test_strtoasciiesc("strtoasciiesc NULL"               , TRUE     , NULL                                                        , NULL                                              );
}
#endif

#ifndef c_strtojsonesc
void test_strtojsonesc(void)	{}
#warning "strtojsonesc() test suite function defined, but the function isn't defined."
#else
void	print_test_strtojsonesc(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(strtojsonesc, str)
	TEST_PRINT(str, strtojsonesc, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_strtojsonesc(void)
{
//	| TEST FUNCTION        | TEST NAME                    | TESTFLAGS| EXPECTING                                          | TEST ARGS
	print_test_strtojsonesc("strtojsonesc no escape"      , FALSE    , "hello world !"                                    , "hello world !"                              );
	// DZ_ON_REFACTOR_OF_SIZE_ERROR: uncomment next test
	// print_test_strtojsonesc("strtojsonesc empty string", FALSE    , ""                                                 , ""                                           );
	print_test_strtojsonesc("strtojsonesc basic escapes"  , FALSE    , "\\tThis\\nis a text \\\\with escaped\\\"symbols '", "\tThis\nis a text \\with escaped\"symbols '");
	print_test_strtojsonesc("strtojsonesc all escapes"    , FALSE    , "hard '\\\"/?\\b\\t\\n\\f\\r string"               , "hard '\"/?\b\t\n\f\r string"                );

	print_test_strtojsonesc("strtojsonesc utf8 char"      , FALSE    , "生日快樂!"                                        , "生日快樂!"                                  );
	print_test_strtojsonesc("strtojsonesc char encoding"  , FALSE    , "Weird \\u000B non \\u0007\\u001B printables"      , "Weird \v non \a\e printables"               );
	print_test_strtojsonesc("strtojsonesc DEL and SOH"    , FALSE    , "a\\u007Fb\\u0001c"                              , "a\x7F""b\x01""c"                          );
	print_test_strtojsonesc("strtojsonesc solidus"        , FALSE    , "path/to/file"                                     , "path/to/file"                               );
	print_test_strtojsonesc("strtojsonesc NULL"           , TRUE     , NULL                                               , NULL);
}

#endif

#ifndef c_esctostr
void test_esctostr(void)	{}
#warning "esctostr() test suite function defined, but the function isn't defined."
#else
void	print_test_esctostr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		t_bool escape_any)
{
	TEST_INIT(str)
	TEST_PERFORM(esctostr, str, escape_any)
	TEST_PRINT(str, esctostr, "str=\"%s\", escape_any=%s", str, (escape_any ? "TRUE" : "FALSE"))
	TEST_FREE()
}
void	test_esctostr(void)
{
//	| TEST FUNCTION    | TEST NAME                       |TESTFLAG| EXPECTING                                         | TEST ARGS
	print_test_esctostr("esctostr 1"                     , FALSE  , "Hello world!"                                     , "Hello world!"                                                      , TRUE);
	print_test_esctostr("esctostr 2"                     , FALSE  , "Hello\tworld!"                                    , "Hello\\tworld!"                                                    , TRUE);
	print_test_esctostr("esctostr 3"                     , FALSE  , "Th\tes\ve""\xA7""ar\ee㈎\t\tunicode😇characters\a", "Th\\tes\\ve\\xA7ar\\ee\\u320E\\t\\tunicode\\U0001f607characters\\a", TRUE);
	print_test_esctostr("esctostr 4"                     , FALSE  , "Th\tes\ve""\xA7""ar\ee㈎\t\tunicode😇characters\a", "Th\\tes\\ve\\xA7ar\\ee\\u320E\\t\\tunicode\\U0001f607characters\\a", FALSE);
	print_test_esctostr("esctostr all sequences"         , FALSE  , "\\'\"\a\b\t\n\v\f\r\e"                            , "\\\\\\'\\\"\\a\\b\\t\\n\\v\\f\\r\\e"                               , FALSE);
	print_test_esctostr("esctostr escape_any TRUE"       , FALSE  , "wc3oui-oui dans son \t\a\bi!@"                    , "\\w\\c\\3oui-oui dans son \\t\\a\\b\\i\\!\\@"                      , TRUE);
	print_test_esctostr("esctostr escape_any FALSE"      , FALSE  , "\\w\\c\\3oui-oui dans son \t\a\b\\i\\!\\@"        , "\\w\\c\\3oui-oui dans son \\t\\a\\b\\i\\!\\@"                      , FALSE);
	print_test_esctostr("esctostr escape_any TRUE"       , FALSE  , NULL                                               , "\\w\\c\\3oui-oui dans son \\t\\a\\x\\i\\!\\@"                      , TRUE);
	print_test_esctostr("esctostr escape_any FALSE"      , FALSE  , NULL                                               , "\\w\\c\\3oui-oui dans son \\t\\a\\x\\i\\!\\@"                      , FALSE);
	print_test_esctostr("esctostr encoded char UPPERCASE", FALSE  , "These""\xA7""are㈎unicode😇characters"            , "These\\xA7are\\u320Eunicode\\U0001F607characters"                  , TRUE);
	print_test_esctostr("esctostr encoded char UPPERCASE", FALSE  , "These""\xA7""are㈎unicode😇characters"            , "These\\xA7are\\u320Eunicode\\U0001F607characters"                  , FALSE);
	print_test_esctostr("esctostr encoded char lowercase", FALSE  , "These""\xA7""are㈎unicode😇characters"            , "These\\xa7are\\u320eunicode\\U0001f607characters"                  , TRUE);
	print_test_esctostr("esctostr encoded char lowercase", FALSE  , "These""\xA7""are㈎unicode😇characters"            , "These\\xa7are\\u320eunicode\\U0001f607characters"                  , FALSE);
	// These do not work and crash the test suite
	print_test_esctostr("esctostr error invalid seq 1"   , FALSE  , NULL                                               , "\\xA"                                                              , FALSE);
	print_test_esctostr("esctostr error invalid seq 2"   , FALSE  , NULL                                               , "\\xAG"                                                             , FALSE);
	print_test_esctostr("esctostr error invalid seq 3"   , FALSE  , NULL                                               , "\\xLOL"                                                            , FALSE);
	print_test_esctostr("esctostr error invalid seq 4"   , FALSE  , NULL                                               , "\\uE0"                                                             , FALSE);
	print_test_esctostr("esctostr error invalid seq 5"   , FALSE  , NULL                                               , "\\uE0Y2"                                                           , FALSE);
	print_test_esctostr("esctostr error invalid seq 6"   , FALSE  , NULL                                               , "\\uE02Y"                                                           , FALSE);
	print_test_esctostr("esctostr error invalid seq 7"   , FALSE  , NULL                                               , "\\UE023"                                                           , FALSE);
	print_test_esctostr("esctostr error invalid seq 8"   , FALSE  , NULL                                               , "\\U0234ABC"                                                        , FALSE);
	print_test_esctostr("esctostr error invalid seq 9"   , FALSE  , NULL                                               , "\\U0234GBCD"                                                       , FALSE);
	// UTF-16 surrogate pair handling: a "\uXXXX\uXXXX" pair must produce a single
	// (4-byte) UTF-8 character, and lone/mismatched surrogates must fail cleanly
	print_test_esctostr("esctostr surrogate pair"         , FALSE  , "\xF0\x9F\x98\x80"                             , "\\uD83D\\uDE00"                                                 , FALSE);
	print_test_esctostr("esctostr surrogate pair (mixed)" , FALSE  , "hi \xF0\x9F\x98\x80 yo"                       , "hi \\uD83D\\uDE00 yo"                                           , FALSE);
	print_test_esctostr("esctostr lone high surrogate"    , FALSE  , NULL                                               , "\\uD83D"                                                          , FALSE);
	print_test_esctostr("esctostr lone low surrogate"     , FALSE  , NULL                                               , "\\uDE00"                                                          , FALSE);
	print_test_esctostr("esctostr surrogate + garbage"    , FALSE  , NULL                                               , "\\uD83Dxx"                                                        , FALSE);
	print_test_esctostr("esctostr surrogate codepoint \\U", FALSE , NULL                                               , "\\U0000D800"                                                      , FALSE);
	// unicode codepoint boundary values (noncharacters/out-of-range are rejected by the UTF-8 encoder)
	print_test_esctostr("esctostr replacement char"       , FALSE  , "\xEF\xBF\xBD"                                  , "\\uFFFD"                                                          , FALSE);
	print_test_esctostr("esctostr noncharacter U+FFFF"    , FALSE  , NULL                                               , "\\uFFFF"                                                          , FALSE);
	print_test_esctostr("esctostr noncharacter U+10FFFF"  , FALSE  , NULL                                               , "\\U0010FFFF"                                                      , FALSE);
	print_test_esctostr("esctostr beyond unicode range"   , FALSE  , NULL                                               , "\\U00110000"                                                      , FALSE);
	print_test_esctostr("esctostr NULL"                  , TRUE   , NULL                                               , NULL                                                                , TRUE);
}
#endif

#if !(defined(c_strtoasciiesc) && defined(c_esctostr))
void test_escroundtrip(void)	{}
#warning "escroundtrip() test suite function defined, but the function isn't defined."
#else
//! NOTE: escaping a string and then unescaping the result must reproduce the original
static char*	c_gen_escroundtrip(char const* str)
{
	t_ascii*	escaped = c_strtoasciiesc(str);
	t_ascii*	result;
	if (escaped == NULL)
		return (strdup("(escape failed)"));
	result = c_esctostr(escaped, FALSE);
	c_strdel(&escaped);
	if (result == NULL)
		return (strdup("(unescape failed)"));
	return (result);
}
void	print_test_escroundtrip(char const* test_name, t_testflags flags,
		char const* expecting)
{
	char const* str = expecting; // the round-trip must reproduce the original string
	TEST_INIT(str)
	TEST_PERFORM(gen_escroundtrip, str)
	TEST_PRINT(str, escroundtrip, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_escroundtrip(void)
{
//	| TEST FUNCTION          | TEST NAME                     |TESTFLAG| EXPECTING (= input, reproduced by the round-trip)
	print_test_escroundtrip("escroundtrip (plain)         ",	FALSE,	"Omae wa mou shindeiru.");
	print_test_escroundtrip("escroundtrip (basic escapes) ",	FALSE,	"N\tA\nN\vI\r?!\a\b");
	print_test_escroundtrip("escroundtrip (quotes+slashes)",	FALSE,	"say \"nani\", '\\path\\to/file'");
	print_test_escroundtrip("escroundtrip (unicode)       ",	FALSE,	"\xE3\x81\x8A\xE5\x89\x8D");
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_escape(void)
{
	print_suite_title("libccc/text/escape");

	print_nonstd();

	test_strtoesc();
	test_strtoescbuf();
	test_strtoasciiesc();
	test_strtojsonesc();
	test_esctostr();
	test_escroundtrip();

	return (0);
}
