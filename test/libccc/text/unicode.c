
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

int	utf8len(char const* str)
{
	t_u8 c = str[0];
	if (c & (1 << 7)) // multi-byte character
	{
		if (c & (1 << 6)) // 2-byte character
		{
			if (c & (1 << 5)) // 3-byte character
			{
				if (c & (1 << 4)) // 4-byte character
				{
					if (c & (1 << 3))
					{
						return (-1);
					}
					else return (4);
				}
				else return (3);
			}
			else return (2);
		}
		else return (-1);
	}
	else if (c == '\0')
	{
		return (0);
	}
	else return (1);
}

void	print_test_mblen(char const* test_name, int can_segfault,
		t_char const* str)
{
	TEST_INIT(sint)
	t_char const* c;
	t_size length = strlen(str);
	for (t_size i = 0; i < length; ++i)
	{
		c = (str + i);
		mblen(NULL, 0); // reset the `mbtowcs()` conversion state
		TEST_PERFORM_LIBC(		utf8len, c)
		TEST_PRINT_LIBC(sint,	utf8len, "c=\"%.4s\"", c)
	}
}
void	test_mblen(void)
{
	setlocale(LC_ALL, "en_US.utf8");
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_mblen("mblen            ", FALSE,			"Hello World!"  );
	print_test_mblen("mblen            ", FALSE,			test1           );
	print_test_mblen("mblen            ", FALSE,			test2           );
	print_test_mblen("mblen            ", FALSE,			test3           );
	print_test_mblen("mblen            ", FALSE,			"a"             );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c0   );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_cc_c1   );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_fr );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ru );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_jp );
	print_test_mblen("mblen (unicode)  ", FALSE,			teststr_utf8_ho );
	print_test_mblen("mblen (empty str)", FALSE,			""              );
	print_test_mblen("mblen (null str) ", SIGNAL_SIGSEGV,	NULL            );
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

	return (OK);
}
