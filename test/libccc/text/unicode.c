
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

void	print_test_mblen(char const* test_name, int can_segfault, t_utf8 const* str, t_sint expecting)
{
	TEST_INIT(sint)
	t_utf8 const* c;
	t_size length = strlen(str);
	int step = (expecting != ERROR ? expecting : 1);

	for (t_size i = 0; i < length; i += step)
	{
		c = (str + i);
		TEST_PERFORM(utf8len, c);
		TEST_PRINT(sint, utf8len, "c=\"%.*s\"", step, c)
	}
}
void	test_mblen(void)
{
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_mblen("mblen            " , FALSE          , "Hello World!"                                   , 1);
	print_test_mblen("mblen            " , FALSE          , test1                                            , 1);
	print_test_mblen("mblen            " , FALSE          , test2                                            , 1);
	print_test_mblen("mblen            " , FALSE          , test3                                            , 1);
	print_test_mblen("mblen            " , FALSE          , "a"                                              , 1);
	print_test_mblen("mblen (unicode)  " , FALSE          , teststr_cc_c0                                    , 3);
	print_test_mblen("mblen (unicode)  " , FALSE          , teststr_cc_c1                                    , 3);
	print_test_mblen("mblen (unicode)  " , FALSE          , "Êàêçûïàœùîâ"                                    , 2 );
	print_test_mblen("mblen (unicode)  " , FALSE          , "ЯцкНичолсонсталинленинтроцкийхрущевмосква"      , 2 );
	print_test_mblen("mblen (unicode)  " , FALSE          , "お前はもう死んでいる愛私は実体の小さな学生です" , 3 );
	print_test_mblen("mblen (unicode)  " , FALSE          , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"                              , 4 );
	print_test_mblen("mblen invalid seq" , FALSE          , "\xA9\xF9"                                       , ERROR );
	print_test_mblen("mblen invalid seq" , FALSE          , "\xF9"                                           , ERROR );
	print_test_mblen("mblen (empty str)" , FALSE          , ""                                               , 0);
	print_test_mblen("mblen (null str) " , SIGNAL_SIGSEGV , NULL                                             , ERROR);
}
#endif

#ifndef c_mbisseqvalid
void test_mbisseqvalid(void)	{}
#warning "mbisseqvalid() test suite function defined, but the function isn't defined."
#else

void	print_test_mbisseqvalid(char const* test_name, int can_segfault, t_utf8 const* str, t_bool expecting, t_size expecting_length)
{
	int step = (expecting_length != SIZE_ERROR ? expecting_length : 1);

	for (t_size i = 0; i < (str ? strlen(str) : 1); i += step)
	{
		t_utf8 const* c = str + i;
		t_size out_length;

		{
			TEST_INIT(bool)
			TEST_PERFORM(mbisseqvalid, c, &out_length);
			TEST_PRINT(bool, mbisseqvalid, "c=\"%.*s\", first byte='%hhX'", step, c, *c)
		}

		{
			TEST_INIT(size)
			test.result = out_length;
			test.expect = expecting_length;
			TEST_PRINT(size, utf8mbisseqvalid out_length, "c=\"%.*s\", first byte='%hhX'", step, c, *c);
		}
	}
}
void	test_mbisseqvalid(void)
{
//	| TEST FUNCTION   | TEST NAME            | CAN SEGV       | TEST ARGS
	print_test_mbisseqvalid("mbisseqvalid            "  , FALSE         , "Hello World!"                                  , TRUE , 1);
	print_test_mbisseqvalid("mbisseqvalid            "  , FALSE         , test1                                           , TRUE , 1);
	print_test_mbisseqvalid("mbisseqvalid            "  , FALSE         , test2                                           , TRUE , 1);
	print_test_mbisseqvalid("mbisseqvalid            "  , FALSE         , test3                                           , TRUE , 1);
	print_test_mbisseqvalid("mbisseqvalid            "  , FALSE         , "a"                                             , TRUE , 1);
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , teststr_cc_c0                                   , TRUE , 3);
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , teststr_cc_c1                                   , TRUE , 3);
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , "Êàêçûïàœùîâ"                                   , TRUE , 2 );
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , "ЯцкНичолсонсталинленинтроцкийхрущевмосква"     , TRUE , 2 );
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , "お前はもう死んでいる愛私は実体の小さな学生です", TRUE , 3 );
	print_test_mbisseqvalid("mbisseqvalid (unicode)  "  , FALSE         , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"                             , TRUE , 4 );
	print_test_mbisseqvalid("mbisseqvalid invalid seq 1", FALSE         , "\xA9\xF9"                                      , FALSE, SIZE_ERROR );
	print_test_mbisseqvalid("mbisseqvalid invalid seq 2", FALSE         , "\xE0\xA0"                                      , FALSE, SIZE_ERROR );
	print_test_mbisseqvalid("mbisseqvalid (empty str)"  , FALSE         , ""                                              , TRUE , 0);
	print_test_mbisseqvalid("mbisseqvalid (null str) "  , SIGNAL_SIGSEGV, NULL                                            , FALSE, SIZE_ERROR);
}
#endif

#ifndef c_mbisstrvalid
void test_mbisstrvalid(void)	{}
#warning "mbisstrvalid() test suite function defined, but the function isn't defined."
#else

void	print_test_mbisstrvalid(char const* test_name, int can_segfault, t_utf8 const* str, t_bool expecting, t_size expecting_symcount, t_size expecting_bytecount)
{
	t_size actual_symcount;
	t_size actual_bytecount;

	{
		TEST_INIT(bool)
		TEST_PERFORM(mbisstrvalid, str, &actual_symcount, &actual_bytecount);
		TEST_PRINT(bool, mbisstrvalid, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}

	{
		TEST_INIT(size)
		test.result =    actual_symcount;
		test.expect = expecting_symcount;
		TEST_PRINT(size, mbisstrvalid out_symcount, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}
	{
		TEST_INIT(size)
		test.result =    actual_bytecount;
		test.expect = expecting_bytecount;
		TEST_PRINT(size, mbisstrvalid out_bytecount, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}
}
void	test_mbisstrvalid(void)
{
//	| TEST FUNCTION        | TEST NAME                  | CAN SEGV      | TEST ARGS
	print_test_mbisstrvalid("mbisstrvalid            "  , FALSE         , "Hello World!"             , TRUE , 12                       , 12);
	print_test_mbisstrvalid("mbisstrvalid            "  , FALSE         , test1                      , TRUE , test1_len - 1            , test1_len - 1);
	print_test_mbisstrvalid("mbisstrvalid            "  , FALSE         , test2                      , TRUE , test2_len - 1            , test2_len - 1);
	print_test_mbisstrvalid("mbisstrvalid            "  , FALSE         , test3                      , TRUE , test3_len - 1            , test3_len - 1);
	print_test_mbisstrvalid("mbisstrvalid            "  , FALSE         , "a"                        , TRUE , 1                        , 1);
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_cc_c0              , TRUE , 32                       , 96);
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_cc_c1              , TRUE , 32                       , 96);
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_utf8_fr            , TRUE , 89                       , 106);
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_utf8_ru            , TRUE , 49                       , 90);
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_utf8_jp            , TRUE , 29                       , 75 );
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃" , TRUE , 17                       , 68 );
	print_test_mbisstrvalid("mbisstrvalid (unicode)  "  , FALSE         , teststr_utf8_hardcore      , TRUE , teststr_utf8_hardcore_len, teststr_utf8_hardcore_bytelen - 1 );
	print_test_mbisstrvalid("mbisstrvalid invalid seq 1", FALSE         , "\xA9\xF9"                 , FALSE, 0                        , 0 );
	print_test_mbisstrvalid("mbisstrvalid invalid seq 2", FALSE         , "\xE0\xA0"                 , FALSE, 0                        , 0 );
	print_test_mbisstrvalid("mbisstrvalid invalid seq 2", FALSE         , "𐑉𐐯𐐻🨀🨁🨂🨃 and then \xE0\xA0", FALSE, 17                       , 38 );
	print_test_mbisstrvalid("mbisstrvalid (empty str)"  , FALSE         , ""                         , TRUE , 0                        , 0);
	print_test_mbisstrvalid("mbisstrvalid (null str) "  , SIGNAL_SIGSEGV, NULL                       , FALSE, SIZE_ERROR               , SIZE_ERROR);
}
#endif

#ifndef c_mbnisstrvalid
void test_mbnisstrvalid(void)	{}
#warning "mbnisstrvalid() test suite function defined, but the function isn't defined."
#else

void	print_test_mbnisstrvalid(char const* test_name, int can_segfault, t_utf8 const* str, t_bool expecting, t_size n, t_size expecting_symcount, t_size expecting_bytecount)
{
	t_size actual_symcount;
	t_size actual_bytecount;

	{
		TEST_INIT(bool)
		TEST_PERFORM(mbnisstrvalid, str, n, &actual_symcount, &actual_bytecount);
		TEST_PRINT(bool, mbnisstrvalid, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}

	{
		TEST_INIT(size)
		test.result =    actual_symcount;
		test.expect = expecting_symcount;
		TEST_PRINT(size, mbnisstrvalid out_symcount, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}
	{
		TEST_INIT(size)
		test.result =    actual_bytecount;
		test.expect = expecting_bytecount;
		TEST_PRINT(size, mbnisstrvalid out_bytecount, "c=\"%s\", first byte='%hhX'", str, (unsigned char)(str ? *str : '\a'))
	}
}
void	test_mbnisstrvalid(void)
{
//	| TEST FUNCTION        | TEST NAME                  | CAN SEGV      | TEST ARGS
	print_test_mbnisstrvalid("mbnisstrvalid            "  , FALSE         , "Hello World!"             , TRUE , SIZE_MAX, 12           , 12);
	print_test_mbnisstrvalid("mbnisstrvalid            "  , FALSE         , test1                      , TRUE , SIZE_MAX, test1_len - 1, test1_len - 1);
	print_test_mbnisstrvalid("mbnisstrvalid            "  , FALSE         , test2                      , TRUE , SIZE_MAX, test2_len - 1, test2_len - 1);
	print_test_mbnisstrvalid("mbnisstrvalid            "  , FALSE         , test3                      , TRUE , SIZE_MAX, test3_len - 1, test3_len - 1);
	print_test_mbnisstrvalid("mbnisstrvalid            "  , FALSE         , "a"                        , TRUE , SIZE_MAX, 1            , 1);
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , teststr_cc_c0              , TRUE , SIZE_MAX, 32           , 96);
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , teststr_cc_c1              , TRUE , SIZE_MAX, 32           , 96);
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , teststr_utf8_fr            , TRUE , SIZE_MAX, 89           , 106);
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , teststr_utf8_ru            , TRUE , SIZE_MAX, 49           , 90);
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , teststr_utf8_jp            , TRUE , SIZE_MAX, 29           , 75 );
	print_test_mbnisstrvalid("mbnisstrvalid (unicode)  "  , FALSE         , "𑢰𐐔𐐯𐑅𐐨𐑉𐐯𐐻🨀🨁🨂🨃🨄🨅🩪􏾵񟾃"        , TRUE , SIZE_MAX, 17           , 68 );
	print_test_mbnisstrvalid("mbnisstrvalid invalid seq 1", FALSE         , "\xA9\xF9"                 , FALSE, SIZE_MAX, 0            , 0 );
	print_test_mbnisstrvalid("mbnisstrvalid invalid seq 2", FALSE         , "\xE0\xA0"                 , FALSE, SIZE_MAX, 0            , 0 );
	print_test_mbnisstrvalid("mbnisstrvalid invalid seq 2", FALSE         , "𐑉𐐯𐐻🨀🨁🨂🨃 and then \xE0\xA0", FALSE, SIZE_MAX, 17           , 38 );
	print_test_mbnisstrvalid("mbnisstrvalid (empty str)"  , FALSE         , ""                         , TRUE , SIZE_MAX, 0            , 0);
	print_test_mbnisstrvalid("mbnisstrvalid (null str) "  , SIGNAL_SIGSEGV, NULL                       , FALSE, SIZE_MAX, SIZE_ERROR   , SIZE_ERROR);

	print_test_mbnisstrvalid("mbnisstrvalid n-limited"    , FALSE         , "Hello World!"             , TRUE , 5, 5           , 5);
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in mb 1", FALSE         , "a"             , TRUE , 5, 2           , 4);
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in mb 2", FALSE         , "a"             , TRUE , 6, 2           , 4);
	print_test_mbnisstrvalid("mbnisstrvalid n-limited after mb", FALSE         , "a"             , TRUE , 7, 3           , 7);

	// These are valid because we don't check for the validity of the last symbol unless `n` is big enough to include that last symbol in the valid string
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in invalid mb 1", FALSE         , "abc\xE0\xA0\xFF"             , TRUE , 4, 3           , 3);
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in invalid mb 2", FALSE         , "abc\xE0\xA0\xFF"             , TRUE , 5, 3           , 3);
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in invalid mb 3", FALSE         , "abc\xE0\xA0\xFF"             , FALSE , 6, 3           , 3);

	// Here the first byte of the last symbol is not valid, so we can't even check if we have enough space to include the symbol
	print_test_mbnisstrvalid("mbnisstrvalid n-limited in invalid mb 4", FALSE         , "abc\xFF\xA0\xFF"             , FALSE , 4, 3           , 3);
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
	print_test_utf32encode_xff("\\0"                 , FALSE    , "\\x00"        , 4             , CharUTF32_FromUTF8("\0"));
	print_test_utf32encode_xff("ascii 'u' (\\x55)"   , FALSE    , "\\x55"        , 4             , CharUTF32_FromUTF8("\x55"));
	print_test_utf32encode_xff("177 (\\xB1)"         , FALSE    , "\\xB1"        , 4             , CharUTF32_FromUTF8("±"));
	print_test_utf32encode_xff("255 (\\xFF)"         , FALSE    , "\\xFF"        , 4             , CharUTF32_FromUTF8("ÿ"));
	print_test_utf32encode_xff("too big"             , FALSE    , ""             , ERROR         , CharUTF32_FromUTF8("愛"));
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
	print_test_utf32encode_uffff("\\0"                    , FALSE    , "\\u0000"        , 6             , CharUTF32_FromUTF8("\0"));
	print_test_utf32encode_uffff("ascii 'u' (\\u0055)"    , FALSE    , "\\u0055"        , 6             , CharUTF32_FromUTF8("\x55"));
	print_test_utf32encode_uffff("177 (\\u00B1)"          , FALSE    , "\\u00B1"        , 6             , CharUTF32_FromUTF8("±"));
	print_test_utf32encode_uffff("255 (\\u00FF)"          , FALSE    , "\\u00FF"        , 6             , CharUTF32_FromUTF8("ÿ"));
	print_test_utf32encode_uffff("24859 (\\u611B)"        , FALSE    , "\\u611B"        , 6             , CharUTF32_FromUTF8("愛"));
	print_test_utf32encode_uffff("헐((\\uD5D0)"           , FALSE    , "\\uD5D0"        , 6             , CharUTF32_FromUTF8("헐"));
	print_test_utf32encode_uffff("max value (\\uFFFF)"    , FALSE    , "\\uFFFF"        , 6             , CharUTF32_FromUTF8("￿"));
	print_test_utf32encode_uffff("too big ((\\U00010000)" , FALSE    , ""               , ERROR         , CharUTF32_FromUTF8("𐀀"));
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
	print_test_utf32encode_Uffffffff("\\0"                             , FALSE    , "\\U00000000"    , 10            , CharUTF32_FromUTF8("\0"));
	print_test_utf32encode_Uffffffff("ascii 'u' (\\U00000055)"         , FALSE    , "\\U00000055"    , 10            , CharUTF32_FromUTF8("\x55"));
	print_test_utf32encode_Uffffffff("177 (\\U000000B1)"               , FALSE    , "\\U000000B1"    , 10            , CharUTF32_FromUTF8("±"));
	print_test_utf32encode_Uffffffff("255 (\\U000000FF)"               , FALSE    , "\\U000000FF"    , 10            , CharUTF32_FromUTF8("ÿ"));
	print_test_utf32encode_Uffffffff("24859 (\\U0000611B)"             , FALSE    , "\\U0000611B"    , 10            , CharUTF32_FromUTF8("愛"));
	print_test_utf32encode_Uffffffff("헐((\\U000D5D0)"                 , FALSE    , "\\U0000D5D0"    , 10            , CharUTF32_FromUTF8("헐"));
	print_test_utf32encode_Uffffffff("<not a character> (\\U0000FFFF)" , FALSE    , "\\U0000FFFF"    , 10            , CharUTF32_FromUTF8("￿"));
	print_test_utf32encode_Uffffffff("𐀀 ((\\U00010000)"                , FALSE    , "\\U00010000"    , 10            , CharUTF32_FromUTF8("𐀀"));
	print_test_utf32encode_Uffffffff("😇 ((\\U0001F607)"               , FALSE    , "\\U0001F607"    , 10            , CharUTF32_FromUTF8("😇"));
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
	print_test_utf32encode_smart("\\0"                             , FALSE    , "\\x00"          , 4             , CharUTF32_FromUTF8("\0"));
	print_test_utf32encode_smart("ascii 'u' (\\U00000055)"         , FALSE    , "\\x55"          , 4             , CharUTF32_FromUTF8("\x55"));
	print_test_utf32encode_smart("177 (\\U000000B1)"               , FALSE    , "\\xB1"          , 4             , CharUTF32_FromUTF8("±"));
	print_test_utf32encode_smart("255 (\\U000000FF)"               , FALSE    , "\\xFF"          , 4             , CharUTF32_FromUTF8("ÿ"));
	print_test_utf32encode_smart("24859 (\\U0000611B)"             , FALSE    , "\\u611B"        , 6             , CharUTF32_FromUTF8("愛"));
	print_test_utf32encode_smart("헐((\\U000D5D0)"                 , FALSE    , "\\uD5D0"        , 6             , CharUTF32_FromUTF8("헐"));
	print_test_utf32encode_smart("<not a character> (\\U0000FFFF)" , FALSE    , "\\uFFFF"        , 6             , CharUTF32_FromUTF8("￿"));
	print_test_utf32encode_smart("𐀀 ((\\U00010000)"                , FALSE    , "\\U00010000"    , 10            , CharUTF32_FromUTF8("𐀀"));
	print_test_utf32encode_smart("😇 ((\\U0001F607)"               , FALSE    , "\\U0001F607"    , 10            , CharUTF32_FromUTF8("😇"));
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
	TEST_PRINT(sint, utf8scount, "str=\"%.32s%s\", expecting='%d'", str, (expecting > 32 ? "..." : ""), expecting)
}
void	test_utf8scount(void)
{
//	| TEST FUNCTION  | TEST NAME                        | CAN SEGV      | EXPECT                    | TEST ARGS
	print_test_utf8scount("utf8scount            "      , FALSE         , 12                       , "Hello World!");
	print_test_utf8scount("utf8scount            "      , FALSE         , 22                       , test1);
	print_test_utf8scount("utf8scount            "      , FALSE         , 7                        , test2);
	print_test_utf8scount("utf8scount            "      , FALSE         , 26                       , test3);
	print_test_utf8scount("utf8scount            "      , FALSE         , 1                        , "a");
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 32                       , teststr_cc_c0);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 32                       , teststr_cc_c1);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 89                       , teststr_utf8_fr);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 49                       , teststr_utf8_ru);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 29                       , teststr_utf8_jp);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 15                       , teststr_utf8_ho);
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 1                        , teststr_utf8_one_symbol_two_seq );
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , 1                        , teststr_utf8_one_symbol_three_seq );
	print_test_utf8scount("utf8scount (unicode)  "      , FALSE         , teststr_utf8_hardcore_len, teststr_utf8_hardcore);
	print_test_utf8scount("utf8scount (empty str)"      , FALSE         , 0                        , "");
	print_test_utf8scount("utf8scount (null str) "      , SIGNAL_SIGSEGV, -1                       , NULL);
	print_test_utf8scount("utf8scount invalid unicode 1", FALSE         , -1                       , "my string \xE0oopsy");
	print_test_utf8scount("utf8scount invalid unicode 2", FALSE         , -1                       , "\xFF");
	print_test_utf8scount("utf8scount invalid unicode 3", FALSE         , -1                       , "\xE0\xA0");
}
#endif

#ifndef c_utf8nscount
void test_utf8nscount(void)	{}
#warning "utf8nscount() test suite function defined, but the function isn't defined."
#else
void	print_test_utf8nscount(char const* test_name, int can_segfault,
		t_sint expecting,
		char const* str,
		t_size n)
{
	TEST_INIT(sint)
	TEST_PERFORM(utf8nscount, str, n)
	TEST_PRINT(sint, utf8nscount, "str=\"%.32s%s\", expecting='%d', n='%zu'", str, (expecting > 32 ? "..." : ""), expecting, n)
}
void	test_utf8nscount(void)
{
//	| TEST FUNCTION  | TEST NAME                                        | CAN SEGV      | EXPECT                    | TEST ARGS
	print_test_utf8nscount("utf8nscount            "                    , FALSE         , 12                       , "Hello World!"                   , SIZE_MAX);
	print_test_utf8nscount("utf8nscount            "                    , FALSE         , 22                       , test1                            , SIZE_MAX);
	print_test_utf8nscount("utf8nscount            "                    , FALSE         , 7                        , test2                            , SIZE_MAX);
	print_test_utf8nscount("utf8nscount            "                    , FALSE         , 26                       , test3                            , SIZE_MAX);
	print_test_utf8nscount("utf8nscount            "                    , FALSE         , 1                        , "a"                              , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 32                       , teststr_cc_c0                    , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 32                       , teststr_cc_c1                    , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 89                       , teststr_utf8_fr                  , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 49                       , teststr_utf8_ru                  , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 29                       , teststr_utf8_jp                  , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 15                       , teststr_utf8_ho                  , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 1                        , teststr_utf8_one_symbol_two_seq  , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , 1                        , teststr_utf8_one_symbol_three_seq, SIZE_MAX);
	print_test_utf8nscount("utf8nscount (unicode)  "                    , FALSE         , teststr_utf8_hardcore_len, teststr_utf8_hardcore            , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (empty str)"                    , FALSE         , 0                        , ""                               , SIZE_MAX);
	print_test_utf8nscount("utf8nscount (null str) "                    , SIGNAL_SIGSEGV, ERROR                    , NULL                             , SIZE_MAX);
	print_test_utf8nscount("utf8nscount invalid unicode 1"              , FALSE         , ERROR                    , "my string \xE0oopsy"            , SIZE_MAX);
	print_test_utf8nscount("utf8nscount invalid unicode 2"              , FALSE         , ERROR                    , "\xFF"                           , SIZE_MAX);
	print_test_utf8nscount("utf8nscount invalid unicode 3"              , FALSE         , ERROR                    , "\xE0\xA0"                       , SIZE_MAX);

	print_test_utf8nscount("utf8nscount n-limited"                      , FALSE         , 5                        , "Hello World!"                   , 5);
	print_test_utf8nscount("utf8nscount n-limited 0"                    , FALSE         , 0                        , "Hello World!"                   , 0);
	print_test_utf8nscount("utf8nscount n-limited in unicode 1"         , FALSE         , 0                        , "愛"                             , 1);
	print_test_utf8nscount("utf8nscount n-limited in unicode 2"         , FALSE         , 0                        , "愛"                             , 2);
	print_test_utf8nscount("utf8nscount n-limited after unicode"        , FALSE         , 1                        , "愛"                             , 3);
	print_test_utf8nscount("utf8nscount n-limited in invalid unicode 1" , FALSE         , ERROR                    , "\xFF"                           , 2);

	// Note: that test returns 0 because \xE0\XA0 is a valid start of a 3 bytes utf8 sequence, and we are not allowed to read the last byte and check validity
	print_test_utf8nscount("utf8nscount n-limited in invalid unicode 2" , FALSE         , 0                        , "\xE0\xA0"                       , 2);
	// Note: there we technically could see that this sequence is invalid by reading only 2 bytes, but we know from the start we don't have room to read the entire sequence so we never bother checking
	print_test_utf8nscount("utf8nscount n-limited in invalid unicode 3" , FALSE         , 0                        , "\xE0\xE0"                       , 2);
	// \xA0 is NOT a valid start of a utf8 sequence
	print_test_utf8nscount("utf8nscount n-limited in invalid unicode 4" , FALSE         , ERROR                    , "\xA0\xE0\xA0"                   , 2);
	print_test_utf8nscount("utf8nscount n-limited after invalid unicode", FALSE         , ERROR                    , "\xE0\xA0"                       , 3);
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
	test_mbisseqvalid();
	test_mbisstrvalid();
	test_mbnisstrvalid();

	test_utf32encode_xff();
	test_utf32encode_uffff();
	test_utf32encode_Uffffffff();
	test_utf32encode_smart();
		
	test_utf8scount();
	test_utf8nscount();

	// TODO

	return (OK);
}
