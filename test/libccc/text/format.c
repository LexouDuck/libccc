
#include <stdio.h>
#include <string.h>

#include "libccc.h"
#include "libccc/text/format.h"
#include "libccc/fixed.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                            String_Format tests                             ||
\*============================================================================*/

//! Tests String_Format() against a hardcoded expected result string
static
void	print_test_strfmt(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* format, ...)
{
	va_list	vargs;
	TEST_INIT(str)
	va_start(vargs, format);
	TEST_PERFORM(vasprintf, format, vargs)
	va_end(vargs);
	TEST_PRINT(str, String_Format, "format=\"%s\"", format)
	TEST_FREE()
}

//! Tests String_Format() against the output of the standard libc `vsnprintf()`
static
void	print_test_strfmt_libc(char const* test_name, t_testflags flags,
		char const* format, ...)
{
	va_list	vargs;
	char	expect_buffer[1024];
	char const*	expecting = expect_buffer;
	TEST_INIT(str)
	va_start(vargs, format);
	vsnprintf(expect_buffer, sizeof(expect_buffer), format, vargs);
	va_end(vargs);
	va_start(vargs, format);
	TEST_PERFORM(vasprintf, format, vargs)
	va_end(vargs);
	TEST_PRINT(str, String_Format, "format=\"%s\"", format)
	TEST_FREE()
}

static
void	test_strfmt(void)
{
//	| TEST FUNCTION       | TEST NAME                     |TESTFLAG| TEST ARGS
	// literal text and '%%'
	print_test_strfmt_libc("strfmt no specifiers"          , FALSE, "hello world");
	print_test_strfmt_libc("strfmt percent literal"        , FALSE, "100%% done");
	// signed/unsigned integers
	print_test_strfmt_libc("strfmt %d zero"                , FALSE, "%d", 0);
	print_test_strfmt_libc("strfmt %d positive"            , FALSE, "%d", 42);
	print_test_strfmt_libc("strfmt %d negative"            , FALSE, "%d", -42);
	print_test_strfmt_libc("strfmt %d INT_MAX"             , FALSE, "%d", 2147483647);
	print_test_strfmt_libc("strfmt %d INT_MIN"             , FALSE, "%d", -2147483647 - 1);
	print_test_strfmt_libc("strfmt %u max"                 , FALSE, "%u", 4294967295u);
	print_test_strfmt_libc("strfmt %o"                     , FALSE, "%o", 0755u);
	print_test_strfmt_libc("strfmt %#o"                    , FALSE, "%#o", 0755u);
	print_test_strfmt_libc("strfmt %x"                     , FALSE, "%x", 0xDEADBEEFu);
	print_test_strfmt_libc("strfmt %#X"                    , FALSE, "%#X", 0xDEADBEEFu);
	// flags/width/precision
	print_test_strfmt_libc("strfmt %d width"               , FALSE, "%8d|", 42);
	print_test_strfmt_libc("strfmt %d width left-justify"  , FALSE, "%-8d|", 42);
	print_test_strfmt_libc("strfmt %d zero-pad"            , FALSE, "%08d", -42);
	print_test_strfmt_libc("strfmt %d plus flag"           , FALSE, "%+d", 42);
	print_test_strfmt_libc("strfmt %d space flag"          , FALSE, "% d", 42);
	print_test_strfmt_libc("strfmt %d precision"           , FALSE, "%.5d", 42);
	print_test_strfmt_libc("strfmt %d width+precision"     , FALSE, "%10.5d|", -42);
	print_test_strfmt_libc("strfmt %d star width"          , FALSE, "%*d", 8, 42);
	print_test_strfmt_libc("strfmt %d star precision"      , FALSE, "%.*d", 8, 42);
	print_test_strfmt_libc("strfmt %d negative star width" , FALSE, "%*d|", -8, 42);
	print_test_strfmt_libc("strfmt %.0d zero value"        , FALSE, "%.0d|", 0);
	// size modifiers
	print_test_strfmt_libc("strfmt %hhd"                   , FALSE, "%hhd", (signed char)-12);
	print_test_strfmt_libc("strfmt %hd"                    , FALSE, "%hd", (short)-1234);
	print_test_strfmt_libc("strfmt %ld"                    , FALSE, "%ld", -123456789L);
	print_test_strfmt_libc("strfmt %lld"                   , FALSE, "%lld", -1234567890123456789LL);
	print_test_strfmt_libc("strfmt %llu max"               , FALSE, "%llu", 18446744073709551615ULL);
	print_test_strfmt_libc("strfmt %zu"                    , FALSE, "%zu", (size_t)123456);
	// chars and strings
	print_test_strfmt_libc("strfmt %c"                     , FALSE, "%c", 'A');
	print_test_strfmt_libc("strfmt %c width"               , FALSE, "%5c|", 'A');
	print_test_strfmt_libc("strfmt %s"                     , FALSE, "%s", "hello");
	print_test_strfmt_libc("strfmt %s empty"               , FALSE, "%s|", "");
	print_test_strfmt_libc("strfmt %s width"               , FALSE, "%10s|", "hi");
	print_test_strfmt_libc("strfmt %s precision"           , FALSE, "%.3s", "hello");
	print_test_strfmt     ("strfmt %s NULL"                , FALSE, "(null)", "%s", (char*)NULL);
	// floats
	print_test_strfmt_libc("strfmt %f zero"                , FALSE, "%f", 0.0);
	print_test_strfmt_libc("strfmt %f negative zero"       , FALSE, "%f", -0.0);
	print_test_strfmt_libc("strfmt %f"                     , FALSE, "%f", 392.65);
	print_test_strfmt_libc("strfmt %f negative"            , FALSE, "%f", -392.65);
	print_test_strfmt_libc("strfmt %f precision"           , FALSE, "%.10f", 1.0 / 3.0);
	print_test_strfmt_libc("strfmt %f width"               , FALSE, "%12.3f|", 3.14159);
	print_test_strfmt_libc("strfmt %f zero-pad"            , FALSE, "%012.3f", -3.14159);
	print_test_strfmt_libc("strfmt %#.0f"                  , FALSE, "%#.0f", 42.0);
	print_test_strfmt_libc("strfmt %e"                     , FALSE, "%e", 392.65);
	print_test_strfmt_libc("strfmt %e small"               , FALSE, "%e", -0.00012345);
	print_test_strfmt_libc("strfmt %E"                     , FALSE, "%E", 12345.678);
	print_test_strfmt_libc("strfmt %e carry rounding"      , FALSE, "%.2e", 999.99);
	print_test_strfmt_libc("strfmt %g"                     , FALSE, "%g", 392.65);
	print_test_strfmt_libc("strfmt %g small"               , FALSE, "%g", 0.00001);
	print_test_strfmt_libc("strfmt %g large"               , FALSE, "%g", 1234567.0);
	print_test_strfmt_libc("strfmt %#g"                    , FALSE, "%#g", 100.0);
	print_test_strfmt_libc("strfmt %#1.15g json style"     , FALSE, "%#1.15g", 3.141592653589793);
	print_test_strfmt_libc("strfmt %a"                     , FALSE, "%a", 392.65);
	print_test_strfmt_libc("strfmt %A"                     , FALSE, "%A", -392.65);
	print_test_strfmt_libc("strfmt %a precision"           , FALSE, "%.3a", 3.14159);
	print_test_strfmt_libc("strfmt %a exact"               , FALSE, "%a", 0.15625);
	print_test_strfmt_libc("strfmt %f infinity"            , FALSE, "%f", 1.0 / 0.0);
	print_test_strfmt_libc("strfmt %f -infinity"           , FALSE, "%f", -1.0 / 0.0);
	print_test_strfmt_libc("strfmt %F NAN"                 , FALSE, "%F", 0.0 / 0.0);
	// pointers
	print_test_strfmt     ("strfmt %p NULL"                , FALSE, "0x0", "%p", (void*)NULL);
	// NOTE: libccc rounds ties away from zero, whereas most libc implementations
	//       round ties to even - both behaviors are valid for ISO C printf
	print_test_strfmt     ("strfmt %.0f tie rounding"      , FALSE, "3", "%.0f", 2.5);
	print_test_strfmt     ("strfmt %.0f tie rounding 2"    , FALSE, "4", "%.0f", 3.5);
}

static
void	test_strfmt_extensions(void)
{
	t_u8	memory[] = { 0xAF, 0x03, 0xD2, 0xC4, 0xE1 };

//	| TEST FUNCTION   | TEST NAME                         |TESTFLAG| EXPECTING | TEST ARGS
	// '%b': binary integer
	print_test_strfmt("strfmt %b zero"                     , FALSE, "0"         , "%b", 0u);
	print_test_strfmt("strfmt %b"                          , FALSE, "110001"    , "%b", 49u);
	print_test_strfmt("strfmt %#b"                         , FALSE, "0b110001"  , "%#b", 49u);
	print_test_strfmt("strfmt %#b zero"                    , FALSE, "0"         , "%#b", 0u);
	print_test_strfmt("strfmt %b width"                    , FALSE, "    110001", "%10b", 49u);
	print_test_strfmt("strfmt %b zero-pad"                 , FALSE, "0000110001", "%010b", 49u);
	print_test_strfmt("strfmt %b precision"                , FALSE, "00110001"  , "%.8b", 49u);
	print_test_strfmt("strfmt %llb max"                    , FALSE,
		"1111111111111111111111111111111111111111111111111111111111111111", "%llb", 18446744073709551615ULL);
	// '%B': boolean
	print_test_strfmt("strfmt %B TRUE"                     , FALSE, "TRUE"   , "%B", (int)TRUE);
	print_test_strfmt("strfmt %B FALSE"                    , FALSE, "FALSE"  , "%B", (int)FALSE);
	print_test_strfmt("strfmt %B width"                    , FALSE, "   TRUE", "%7B", (int)TRUE);
	print_test_strfmt("strfmt %B precision"                , FALSE, "TR"     , "%.2B", (int)TRUE);
	// '%C': escaped char
	print_test_strfmt("strfmt %C printable"                , FALSE, "a"     , "%C", 'a');
	print_test_strfmt("strfmt %C newline"                  , FALSE, "\\n"   , "%C", '\n');
	print_test_strfmt("strfmt %C tab"                      , FALSE, "\\t"   , "%C", '\t');
	print_test_strfmt("strfmt %C nul char"                 , FALSE, "\\0"   , "%C", '\0');
	print_test_strfmt("strfmt %C escape char"              , FALSE, "\\e"   , "%C", '\x1B');
	print_test_strfmt("strfmt %C invalid encoding byte"    , FALSE, "\\xFF" , "%C", '\xFF');
	print_test_strfmt("strfmt %C width"                    , FALSE, "    \\n", "%6C", '\n');
	// '%S': escaped string
	print_test_strfmt("strfmt %S simple"                   , FALSE, "hello"     , "%S", "hello");
	print_test_strfmt("strfmt %S escapes"                  , FALSE, "12\\t34"   , "%S", "12\t34");
	print_test_strfmt("strfmt %S backslash"                , FALSE, "a\\nb\\\\c", "%S", "a\nb\\c");
	print_test_strfmt("strfmt %S NULL"                     , FALSE, "(null)"    , "%S", (char*)NULL);
	print_test_strfmt("strfmt %S empty with width"         , FALSE, "   |"      , "%3S|", "");
	print_test_strfmt("strfmt %S width"                    , FALSE, "  12\\t34" , "%8S", "12\t34");
	print_test_strfmt("strfmt %S precision"                , FALSE, "12\\t"     , "%.4S", "12\t34");
	print_test_strfmt("strfmt %S invalid encoding byte"    , FALSE, "a\\xFFb"   , "%S", "a\xFF" "b");
	// '%q'/'%k'/'%K': fixed-point
	print_test_strfmt("strfmt %k integer"                  , FALSE, "0x1f"    , "%k", Fixed_From(31, 1));
	print_test_strfmt("strfmt %K integer"                  , FALSE, "0X1F"    , "%K", Fixed_From(31, 1));
	print_test_strfmt("strfmt %#k"                         , FALSE, "0x1f."   , "%#k", Fixed_From(31, 1));
	print_test_strfmt("strfmt %k fraction"                 , FALSE, "-0x14.a" , "%k", Fixed_From(-165, 8));
	print_test_strfmt("strfmt %k precision"                , FALSE, "-0x14.a0", "%.2k", Fixed_From(-165, 8));
	print_test_strfmt("strfmt %k precision rounding"       , FALSE, "-0x15"   , "%.0k", Fixed_From(-165, 8));
	print_test_strfmt("strfmt %k half"                     , FALSE, "0x0.8"   , "%k", Fixed_From(1, 2));
	print_test_strfmt("strfmt %k half rounds up"           , FALSE, "0x1"     , "%.0k", Fixed_From(1, 2));
	print_test_strfmt("strfmt %k zero-pad"                 , FALSE, "0x000.8" , "%07k", Fixed_From(1, 2));
	print_test_strfmt("strfmt %+k"                         , FALSE, "+0x1f"   , "%+k", Fixed_From(31, 1));
	// '%m': memory bytes
	print_test_strfmt("strfmt %m no precision"             , FALSE, ""            , "%m", memory);
	print_test_strfmt("strfmt %.5m"                        , FALSE, "AF03D2C4E1"  , "%.5m", memory);
	print_test_strfmt("strfmt %.2m"                        , FALSE, "AF03"        , "%.2m", memory);
	print_test_strfmt("strfmt %#.5m"                       , FALSE, "0xAF03D2C4E1", "%#.5m", memory);
	print_test_strfmt("strfmt %m width"                    , FALSE, "    AF03"    , "%8.2m", memory);
	print_test_strfmt("strfmt %m NULL"                     , FALSE, ""            , "%.3m", (void*)NULL);
}



/*============================================================================*\
||                           String_Format_N tests                            ||
\*============================================================================*/

static
void	print_test_strnfmt(char const* test_name, t_testflags flags,
		t_size expect_result, char const* expect_dest,
		t_size max, char const* format, ...)
{
	va_list	vargs;
	char	dest[32] = {0};
	t_size	result;

	va_start(vargs, format);
	result = String_Format_N_VA((expect_dest == NULL ? NULL : dest), max, format, vargs);
	va_end(vargs);
	{
		t_size	expecting = expect_result;
		TEST_INIT(size)
		test.result = result;
		test.expect = expecting;
		TEST_PRINT(size, String_Format_N return, "max='" SF_SIZE "', format=\"%s\"", max, format)
	}
	if (expect_dest != NULL)
	{
		char const*	expecting = expect_dest;
		TEST_INIT(str)
		test.result = dest; // NOTE: stack buffer, so no TEST_FREE() call here
		test.expect = expecting;
		TEST_PRINT(str, String_Format_N dest, "max='" SF_SIZE "', format=\"%s\"", max, format)
	}
}

static
void	test_strnfmt(void)
{
//	| TEST FUNCTION    | TEST NAME                        |TESTFLAG| EXPECT_RET | EXPECT_DEST | MAX | TEST ARGS
	print_test_strnfmt("strnfmt NULL dest returns length" , FALSE, 11, NULL     ,  0, "%s", "hello world");
	print_test_strnfmt("strnfmt truncated"                , FALSE,  7, "hello w",  8, "%s", "hello world");
	print_test_strnfmt("strnfmt exact fit"                , FALSE,  7, "1234567",  8, "%s", "1234567");
	print_test_strnfmt("strnfmt no truncation"            , FALSE,  2, "42"     ,  8, "%d", 42);
	print_test_strnfmt("strnfmt max zero"                 , FALSE,  0, ""       ,  0, "%d", 42);
}



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_format(void)
{
	print_suite_title("libccc/text/format");

	test_strfmt();
	test_strfmt_extensions();
	test_strnfmt();

	return (OK);
}
