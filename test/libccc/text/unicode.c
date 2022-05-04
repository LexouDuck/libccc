
#include <locale.h>

#include "libccc.h"
#include "libccc/text/unicode.h"

#include "test.h"

#if 0 // test template

#ifndef c_utf
void test_utf(void)	{}
#warning "utf() test suite function defined, but the function isn't defined."
#else
void	print_test_utf(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	// TODO
}
void	test_utf(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	// TODO
}
#endif

#endif



#ifndef c_mblen
void test_mblen(void)	{}
#warning "mblen() test suite function defined, but the function isn't defined."
#else

void	print_test_mblen(char const* test_name, int can_segfault, t_char const* str, t_sint expecting_)
{
	TEST_INIT(sint)
	t_char const* c;
	t_size length = strlen(str);
	for (t_size i = 0; i < length; ++i)
	{
		c = (str + i);
		t_sint expecting;
		if (expecting_ == ERROR)
			expecting = ERROR;
		else
			expecting = (i % expecting_ ? -1 : expecting_);
		TEST_PERFORM(utf8len, c);
		TEST_PRINT(sint, utf8len, "c=\"%.*s\"", expecting_, c)
	}
}
void	test_mblen(void)
{
	setlocale(LC_ALL, "en_US.utf8");
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_mblen("mblen            ", FALSE,			"Hello World!"  , 1);
	print_test_mblen("mblen            ", FALSE,			test1           , 1);
	print_test_mblen("mblen            ", FALSE,			test2           , 1);
	print_test_mblen("mblen            ", FALSE,			test3           , 1);
	print_test_mblen("mblen            ", FALSE,			"a"             , 1);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c0   , 3);
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c1   , 3);
	print_test_mblen("mblen (unicode)  ", FALSE,			"Êàêçûïàœùîâ"   , 2 );
	print_test_mblen("mblen (unicode)  ", FALSE,			"ЯцкНичолсонсталинленинтроцкийхрущевмосква", 2 );
	print_test_mblen("mblen (unicode)  ", FALSE,			"お前はもう死んでいる愛私は実体の小さな学生です", 3 );
	print_test_mblen("mblen (unicode)  ", FALSE,			 "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃", 4 );
	print_test_mblen("mblen invalid seq", FALSE,			 "\x80\xC0\xE0\xF0\xF8\xFC\xFE\xFF\xFE\xFC\xF8\xF0\xE0\xC0", ERROR );
	print_test_mblen("mblen (empty str)", FALSE,			""              , 0);
	print_test_mblen("mblen (null str) ", SIGNAL_SIGSEGV,	NULL            , ERROR);
}
#endif

#ifndef c_mbnlen
void test_mbnlen(void)	{}
#warning "mbnlen() test suite function defined, but the function isn't defined."
#else

void	print_test_mbnlen(char const* test_name, int can_segfault, t_char const* str, t_size n, t_sint expecting_)
{
	TEST_INIT(sint)
	t_char const* c;
	t_size nlength = strlen(str);
	for (t_size i = 0; i < nlength; ++i)
	{
		c = (str + i);
		t_sint expecting;
		if (expecting_ == ERROR)
			expecting = ERROR;
		else
			expecting = (i % expecting_ ? -1 : expecting_);
		TEST_PERFORM(utf8nlen, c, n);
		TEST_PRINT(sint, utf8nlen, "c=\"%.*s\"", expecting_, c)
	}
}
void	test_mbnlen(void)
{
	setlocale(LC_ALL, "en_US.utf8");
//	| TEST FUNCTION  | TEST NAME               | CAN SEGV       | TEST ARGS
	print_test_mbnlen("mbnlen            "     , FALSE          , "Hello World!"                                             , SIZE_MAX , 1);
	print_test_mbnlen("mbnlen            "     , FALSE          , test1                                                      , SIZE_MAX , 1);
	print_test_mbnlen("mbnlen            "     , FALSE          , test2                                                      , SIZE_MAX , 1);
	print_test_mbnlen("mbnlen            "     , FALSE          , test3                                                      , SIZE_MAX , 1);
	print_test_mbnlen("mbnlen            "     , FALSE          , "a"                                                        , SIZE_MAX , 1);
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , teststr_cc_c0                                              , SIZE_MAX , 3);
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , teststr_cc_c1                                              , SIZE_MAX , 3);
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , "Êàêçûïàœùîâ"                                              , SIZE_MAX , 2 );
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , "ЯцкНичолсонсталинленинтроцкийхрущевмосква"                , SIZE_MAX , 2 );
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , "お前はもう死んでいる愛私は実体の小さな学生です"           , SIZE_MAX , 3 );
	print_test_mbnlen("mbnlen (unicode)  "     , FALSE          , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"                                        , SIZE_MAX , 4 );
	print_test_mbnlen("mbnlen invalid seq"     , FALSE          , "\x80\xC0\xE0\xF0\xF8\xFC\xFE\xFF\xFE\xFC\xF8\xF0\xE0\xC0" , SIZE_MAX , ERROR );
	print_test_mbnlen("mbnlen (empty str)"     , FALSE          , ""                                                         , SIZE_MAX , 0);
	print_test_mbnlen("mbnlen (null str) "     , SIGNAL_SIGSEGV , NULL                                                       , SIZE_MAX , ERROR);

	print_test_mbnlen("mbnlen n-limited to 1"  , FALSE          , "ЯцкНичолсонсталинленинтроцкийхрущевмосква"                , 1        , ERROR );
	print_test_mbnlen("mbnlen  "               , FALSE          , "ЯцкНичолсонсталинленинтроцкийхрущевмосква"                , 2        , 2);
	print_test_mbnlen("mbnlen n-limited to 2 " , FALSE          , "お前はもう死んでいる愛私は実体の小さな学生です"           , 2        , ERROR );
	print_test_mbnlen("mbnlen "                , FALSE          , "お前はもう死んでいる愛私は実体の小さな学生です"           , 3        , 3 );
	print_test_mbnlen("mbnlen n-limited to 3 " , FALSE          , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"                                        , 3        , ERROR );
	print_test_mbnlen("mbnlen "                , FALSE          , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"                                        , 4        , 4 );
}
#endif


#ifndef c_utf32encode_xff
void test_utf32encode_xff(void)	{}
#warning "utf32encode_xff() test suite function defined, but the function isn't defined."
#else
void	print_test_utf32encode_xff(char const* test_name, int can_segfault,
		t_ascii const* expecting_dest,
		t_size expecting,
		t_utf32 c)
{
	t_ascii dest_libccc[5];
	memset(dest_libccc, 0, 5);

	{
		TEST_INIT(size)
		TEST_PERFORM_DEST(utf32encode_xff, c)
		TEST_PRINT(size, utf32encode_xff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
	{
		TEST_INIT(str)
		test.expect = expecting_dest;
		test.result = dest_libccc;
		TEST_PRINT(str, utf32encode_xff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
}

void	test_utf32encode_xff(void)
{
//	| TEST FUNCTION         | TEST NAME            | CAN SEGV | EXPECTING DEST | EXPECTING RET | TEST ARG
	print_test_utf32encode_xff("\\0"                 , FALSE    , "\\x00"        , 4             , UTF32_FromUTF8("\0"));
	print_test_utf32encode_xff("ascii 'u' (\\x55)"   , FALSE    , "\\x55"        , 4             , UTF32_FromUTF8("\x55"));
	print_test_utf32encode_xff("177 (\\xB1)"         , FALSE    , "\\xB1"        , 4             , UTF32_FromUTF8("±"));
	print_test_utf32encode_xff("255 (\\xFF)"         , FALSE    , "\\xFF"        , 4             , UTF32_FromUTF8("ÿ"));
	print_test_utf32encode_xff("too big"             , FALSE    , ""             , ERROR         , UTF32_FromUTF8("愛"));
}
#endif

#ifndef c_utf32encode_uffff
void test_utf32encode_uffff(void)	{}
#warning "utf32encode_uffff() test suite function defined, but the function isn't defined."
#else
void	print_test_utf32encode_uffff(char const* test_name, int can_segfault,
		t_ascii const* expecting_dest,
		t_size expecting,
		t_utf32 c)
{
	t_ascii dest_libccc[7];
	memset(dest_libccc, 0, 7);

	{
		TEST_INIT(size)
		TEST_PERFORM_DEST(utf32encode_uffff, c)
		TEST_PRINT(size, utf32encode_uffff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
	{
		TEST_INIT(str)
		test.expect = expecting_dest;
		test.result = dest_libccc;
		TEST_PRINT(str, utf32encode_uffff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
}

void	test_utf32encode_uffff(void)
{
//	| TEST FUNCTION           | TEST NAME               | CAN SEGV | EXPECTING DEST   | EXPECTING RET | TEST ARG
	print_test_utf32encode_uffff("\\0"                    , FALSE    , "\\u0000"        , 6             , UTF32_FromUTF8("\0"));
	print_test_utf32encode_uffff("ascii 'u' (\\u0055)"    , FALSE    , "\\u0055"        , 6             , UTF32_FromUTF8("\x55"));
	print_test_utf32encode_uffff("177 (\\u00B1)"          , FALSE    , "\\u00B1"        , 6             , UTF32_FromUTF8("±"));
	print_test_utf32encode_uffff("255 (\\u00FF)"          , FALSE    , "\\u00FF"        , 6             , UTF32_FromUTF8("ÿ"));
	print_test_utf32encode_uffff("24859 (\\u611B)"        , FALSE    , "\\u611B"        , 6             , UTF32_FromUTF8("愛"));
	print_test_utf32encode_uffff("헐((\\uD5D0)"           , FALSE    , "\\uD5D0"        , 6             , UTF32_FromUTF8("헐"));
	print_test_utf32encode_uffff("max value (\\uFFFF)"    , FALSE    , "\\uFFFF"        , 6             , UTF32_FromUTF8("￿"));
	print_test_utf32encode_uffff("too big ((\\U00010000)" , FALSE    , ""               , ERROR         , UTF32_FromUTF8("𐀀"));
}
#endif

#ifndef c_utf32encode_Uffffffff
void test_utf32encode_Uffffffff(void)	{}
#warning "utf32encode_Uffffffff() test suite function defined, but the function isn't defined."
#else
void	print_test_utf32encode_Uffffffff(char const* test_name, int can_segfault,
		t_ascii const* expecting_dest,
		t_size expecting,
		t_utf32 c)
{
	t_ascii dest_libccc[11];
	memset(dest_libccc, 0, 11);

	{
		TEST_INIT(size)
		TEST_PERFORM_DEST(utf32encode_Uffffffff, c)
		TEST_PRINT(size, utf32encode_Uffffffff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
	{
		TEST_INIT(str)
		test.expect = expecting_dest;
		test.result = dest_libccc;
		test.function = "utf32_encodeUffffffff";
		TEST_PRINT(str, utf32_encodeUffffffff, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
}

void	test_utf32encode_Uffffffff(void)
{
//	| TEST FUNCTION               | TEST NAME                        | CAN SEGV | EXPECTING DEST   | EXPECTING RET | TEST ARG
	print_test_utf32encode_Uffffffff("\\0"                             , FALSE    , "\\U00000000"    , 10            , UTF32_FromUTF8("\0"));
	print_test_utf32encode_Uffffffff("ascii 'u' (\\U00000055)"         , FALSE    , "\\U00000055"    , 10            , UTF32_FromUTF8("\x55"));
	print_test_utf32encode_Uffffffff("177 (\\U000000B1)"               , FALSE    , "\\U000000B1"    , 10            , UTF32_FromUTF8("±"));
	print_test_utf32encode_Uffffffff("255 (\\U000000FF)"               , FALSE    , "\\U000000FF"    , 10            , UTF32_FromUTF8("ÿ"));
	print_test_utf32encode_Uffffffff("24859 (\\U0000611B)"             , FALSE    , "\\U0000611B"    , 10            , UTF32_FromUTF8("愛"));
	print_test_utf32encode_Uffffffff("헐((\\U000D5D0)"                 , FALSE    , "\\U0000D5D0"    , 10            , UTF32_FromUTF8("헐"));
	print_test_utf32encode_Uffffffff("<not a character> (\\U0000FFFF)" , FALSE    , "\\U0000FFFF"    , 10            , UTF32_FromUTF8("￿"));
	print_test_utf32encode_Uffffffff("𐀀 ((\\U00010000)"                , FALSE    , "\\U00010000"    , 10            , UTF32_FromUTF8("𐀀"));
	print_test_utf32encode_Uffffffff("😇 ((\\U0001F607)"               , FALSE    , "\\U0001F607"    , 10            , UTF32_FromUTF8("😇"));
}
#endif

#ifndef c_utf32encode_smart
void test_utf32encode_smart(void)	{}
#warning "utf32encode_smart() test suite function defined, but the function isn't defined."
#else
void	print_test_utf32encode_smart(char const* test_name, int can_segfault,
		t_ascii const* expecting_dest,
		t_size expecting,
		t_utf32 c)
{
	t_ascii dest_libccc[11];
	memset(dest_libccc, 0, 11);

	{
		TEST_INIT(size)
		TEST_PERFORM_DEST(utf32encode_smart, c)
		TEST_PRINT(size, utf32encode_smart, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
	{
		TEST_INIT(str)
		test.expect = expecting_dest;
		test.result = dest_libccc;
		TEST_PRINT(str, utf32encode_smart, "dest=\"%s\", c='%c'/%X", dest_libccc, c, c)
	}
}

void	test_utf32encode_smart(void)
{
//	| TEST FUNCTION           | TEST NAME                        | CAN SEGV | EXPECTING DEST   | EXPECTING RET | TEST ARG
	print_test_utf32encode_smart("\\0"                             , FALSE    , "\\x00"          , 4             , UTF32_FromUTF8("\0"));
	print_test_utf32encode_smart("ascii 'u' (\\U00000055)"         , FALSE    , "\\x55"          , 4             , UTF32_FromUTF8("\x55"));
	print_test_utf32encode_smart("177 (\\U000000B1)"               , FALSE    , "\\xB1"          , 4             , UTF32_FromUTF8("±"));
	print_test_utf32encode_smart("255 (\\U000000FF)"               , FALSE    , "\\xFF"          , 4             , UTF32_FromUTF8("ÿ"));
	print_test_utf32encode_smart("24859 (\\U0000611B)"             , FALSE    , "\\u611B"        , 6             , UTF32_FromUTF8("愛"));
	print_test_utf32encode_smart("헐((\\U000D5D0)"                 , FALSE    , "\\uD5D0"        , 6             , UTF32_FromUTF8("헐"));
	print_test_utf32encode_smart("<not a character> (\\U0000FFFF)" , FALSE    , "\\uFFFF"        , 6             , UTF32_FromUTF8("￿"));
	print_test_utf32encode_smart("𐀀 ((\\U00010000)"                , FALSE    , "\\U00010000"    , 10            , UTF32_FromUTF8("𐀀"));
	print_test_utf32encode_smart("😇 ((\\U0001F607)"               , FALSE    , "\\U0001F607"    , 10            , UTF32_FromUTF8("😇"));
}
#endif

#ifndef c_utf8scount
void test_utf8scount(void)	{}
#warning "utf8scount() test suite function defined, but the function isn't defined."
#else
void	print_test_utf8scount(char const* test_name, int can_segfault,
		t_sint expecting,
		char const* str)
{
	TEST_INIT(sint)
	TEST_PERFORM(utf8scount, str)
	TEST_PRINT(sint, utf8scount, "str=\"%32s\", expecting='%d'", str, expecting)
}
void	test_utf8scount(void)
{
//	| TEST FUNCTION  | TEST NAME                        | CAN SEGV      | EXPECT                    | TEST ARGS
	print_test_utf8scount("utf8scount            "      , FALSE          , 12                        , "Hello World!");
	print_test_utf8scount("utf8scount            "      , FALSE          , 22                        , test1);
	print_test_utf8scount("utf8scount            "      , FALSE          , 7                         , test2);
	print_test_utf8scount("utf8scount            "      , FALSE          , 26                        , test3);
	print_test_utf8scount("utf8scount            "      , FALSE          , 1                         , "a");
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 32                        , teststr_cc_c0);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 32                        , teststr_cc_c1);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 89                        , teststr_utf8_fr);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 49                        , teststr_utf8_ru);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 29                        , teststr_utf8_jp);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 15                        , teststr_utf8_ho);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 1                         , teststr_utf8_one_symbol_two_seq );
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , 1                         , teststr_utf8_one_symbol_three_seq );
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE          , teststr_utf8_hardcore_len , teststr_utf8_hardcore);
	print_test_utf8scount("utf8scount (empty str)"      , FALSE          , 0                         , "");
	print_test_utf8scount("utf8scount (null str) "      , SIGNAL_SIGSEGV , -1                        , NULL);
	print_test_utf8scount("utf8scount invalid unicode " , FALSE          , -1                        , "my string \xE0oopsy");
	print_test_utf8scount("utf8scount invalid unicode " , FALSE          , -1                        , "\xFF");
	print_test_utf8scount("utf8scount invalid unicode " , FALSE          , -1                        , "\xE0\xA0");
}
#endif


// TODO



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_text_unicode(void)
{
	print_suite_title("libccc/text/unicode");

	print_nonstd();

	test_mblen();
	// TODO

	test_utf32encode_xff();
	test_utf32encode_uffff();
	test_utf32encode_Uffffffff();
	test_utf32encode_smart();
		
	test_utf8scount();

	return (OK);
}
