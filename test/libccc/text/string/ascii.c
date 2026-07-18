
#include <ctype.h>
#include <string.h>

#include "libccc/string.h"

#include "test.h"
#include "test_utils.h"



/*============================================================================*\
||                          Basic String Operations                           ||
\*============================================================================*/

#ifndef c_strnew
void test_strnew(void)	{}
#warning "strnew() test suite function defined, but the function isn't defined."
#else
static
void*	strnew(size_t n)
{ void* result = malloc(n + sizeof(""));	memset(result, '\0', n);	return (result); }

void	print_test_strnew(char const* test_name, t_testflags flags,
		size_t n)
{
	TEST_INIT(alloc)
	test.length = n;
	TEST_PERFORM_LIBC(	strnew, n)
	TEST_PRINT(alloc,	strnew, "n=%zu", n)
	TEST_FREE()
}
void	test_strnew(void)
{
//	| TEST FUNCTION  | TEST NAME            |TESTFLAG|TEST ARGS
	print_test_strnew("strnew              ", FALSE,	12);
	print_test_strnew("strnew (n = 0xFFFF) ", FALSE,	0xFFFF);
	print_test_strnew("strnew (n = 0x10000)", FALSE,	0x10000);
	print_test_strnew("strnew (n = 0)      ", FALSE,	0);
}
#endif



#ifndef c_strcnew
void test_strcnew(void)	{}
#warning "strcnew() test suite function defined, but the function isn't defined."
#else
static
void*	strcnew(size_t n, char c)
{ void* result = malloc(n + sizeof(""));	memset(result, c, n);	return (result); }

void	print_test_strcnew(char const* test_name, t_testflags flags,
		size_t n,
		t_ascii c)
{
	TEST_INIT(alloc)
	test.length = n;
	TEST_PERFORM_LIBC(	strcnew, n, c)
	TEST_PRINT(alloc,	strcnew, "n=%zu, c='%c'/0x%X", n, c, c)
	TEST_FREE()
}
void	test_strcnew(void)
{
//	| TEST FUNCTION   | TEST NAME             |TESTFLAG|TEST ARGS
	print_test_strcnew("strcnew              ", FALSE,	12,      '_');
	print_test_strcnew("strcnew (n = 0xFFFF) ", FALSE,	0xFFFF,  '_');
	print_test_strcnew("strcnew (n = 0x10000)", FALSE,	0x10000, '_');
	print_test_strcnew("strcnew (c = 0)      ", FALSE,	12,      '\0');
	print_test_strcnew("strcnew (n = 0)      ", FALSE,	0,       '_');
	print_test_strcnew("strcnew (n = 0,c = 0)", FALSE,	0,       '\0');
}
#endif



#ifndef c_strset
void test_strset(void)	{}
#warning "strset() test suite function defined, but the function isn't defined."
#else
void	print_test_strset(char const* test_name, t_testflags flags,
		char const* expecting,
		char* dest_libccc,
		char* dest_libc,
		char c)
{
	TEST_INIT(str)
	TEST_PERFORM_VOID_DEST(	strset, c)
	TEST_PRINT(str,			strset, "dest=\"%s\", c='%c'/0x%X", dest_libccc, c, c)
}
void	test_strset(void)
{
	char str1[] = "swag";
	char str2[] = "swag";
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS     | EXPECT | TEST ARGS
	print_test_strset("strset           ",  FALSE,          "aaaa",   str1, str2, 'a');
	print_test_strset("strset           ",  FALSE,          "____",   str1, str2, '_');
	print_test_strset("strset (c = '\\0')", FALSE,          "\0\0\0", str1, str2, '\0');
	print_test_strset("strset (null ptr)",  ALLOW_SIGSEGV, NULL,     NULL, NULL, 'a');
}
#endif


#ifndef c_strclr
void test_strclr(void)	{}
#warning "strclr() test suite function defined, but the function isn't defined."
#else
#ifndef strclr
#define strclr(dest, c)	memset(dest, c, strlen(c))
#endif
void	print_test_strclr(char const* test_name, t_testflags flags,
		char const* expecting,
		char* dest_libccc,
		char* dest_libc)
{
	TEST_INIT(str)
	TEST_PERFORM_VOID_DEST(	strclr)
	TEST_PRINT(str,			strclr, "dest=\"%s\"", dest_libccc)
}
void	test_strclr(void)
{
	char str1[32] = {'_'};
	char str2[32] = {'_'};
//	| TEST FUNCTION  | TEST NAME         | TESTFLAGS     | EXPECT | TEST ARGS
	print_test_strclr("strclr           ", FALSE,			"",    str1 + 20, str2 + 20);
	print_test_strclr("strclr           ", FALSE,			"",    str1 + 10, str2 + 10);
	print_test_strclr("strclr           ", FALSE,			"",    str1, str2);
	print_test_strclr("strclr (null ptr)", ALLOW_SIGSEGV, NULL,  NULL, NULL);
}
#endif


#ifndef c_strdel
void test_strdel(void)	{}
#warning "strdel() test suite function defined, but the function isn't defined."
#else
void	print_test_strdel(char const* test_name, t_testflags flags,
		char const* expecting,
		char** dest_libccc,
		char** dest_libc)
{
	TEST_INIT(ptr)
	TEST_PERFORM_VOID(*dest_libccc,	strdel, dest_libccc)
	TEST_PRINT(ptr,					strdel, "str=%p/\"%s\"", (void*)dest_libccc, *dest_libccc)
	TEST_FREE()
}
void	test_strdel(void)
{
	char* str1; if (!(str1 = (char*)malloc(32))) return;
	char* str2; if (!(str2 = (char*)malloc(32))) return;
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      |EXPECT| TEST ARGS
	print_test_strdel("strdel           ", FALSE,			NULL,	&str1, &str2);
	print_test_strdel("strdel (null ptr)", ALLOW_SIGSEGV,	NULL,	NULL,  NULL);
}
#endif


#ifndef c_strdup
void test_strdup(void)	{}
#warning "strdup() test suite function defined, but the function isn't defined."
#else
void	print_test_strdup(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strdup, str)
	TEST_PRINT(str,	strdup, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_strdup(void)
{
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      | TEST ARGS
	print_test_strdup("strdup            ", FALSE,			test1, test1);
	print_test_strdup("strdup            ", FALSE,			test2, test2);
	print_test_strdup("strdup            ", FALSE,			test3, test3);
	print_test_strdup("strdup            ", FALSE,			"_",   "_");
	print_test_strdup("strdup (empty str)", FALSE,			"",    "");
	print_test_strdup("strdup (null str) ", ALLOW_SIGSEGV,	NULL,  NULL);
}
#endif



#ifndef c_strcpy
void test_strcpy(void)	{}
#warning "strcpy() test suite function defined, but the function isn't defined."
#else
void	print_test_strcpy(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strcpy, src)
	TEST_PRINT(str,			strcpy, "dest=\"%s\", src=\"%s\"", dest_libccc, src)
	test.function = "strcpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL, NULL);
}
void	print_test_strcpy_overlap(char const* test_name, t_testflags flags,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc)
{
	TEST_INIT(str)
	test.flags |= FLAG_WARNING;
	TEST_PERFORM_(result, c_strcpy, dest_libccc, src_libccc)
	TEST_PERFORM_(expect,   strcpy, dest_libc,   src_libc)
	TEST_PRINT(str,			strcpy, "dest=\"%s\", src=\"%s\"", dest_libccc, src_libccc)
	test.function = "strcpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	char const* warning = NULL;
	if (strcmp(dest_libc, expecting_dest))
		warning = "strcpy() libc implementation does not handle overlap";
	print_test_str(&test, NULL, warning);
}
void	test_strcpy(void)
{
	char str1[64] = { '_' };
	char str2[64] = { '_' };
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      | TEST ARGS
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test1);
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test2);
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test3);
	print_test_strcpy("strcpy (empty str)",	FALSE,			str1, str2, "");
	print_test_strcpy("strcpy (null dest)",	ALLOW_SIGSEGV,  NULL, NULL, test2);
	print_test_strcpy("strcpy (null src) ",	ALLOW_SIGSEGV,  str1, str2, NULL);
	print_test_strcpy("strcpy (both null)",	ALLOW_SIGSEGV,  NULL, NULL, NULL);
	// overlap tests
	size_t d = 8;
	char expect[64] = { '_' };
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect, expect+d, strlen(expect+d));
	print_test_strcpy_overlap("strcpy (overlap <)",	FALSE,	expect, str1, str2, str1+d, str2+d);
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect+d, expect, strlen(expect));
	print_test_strcpy_overlap("strcpy (overlap >)",	FALSE,	expect, str1+d, str2+d, str1, str2);
}
#endif



#ifndef c_strncpy
void test_strncpy(void)	{}
#warning "strncpy() test suite function defined, but the function isn't defined."
#else
void	print_test_strncpy(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		size_t n)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strncpy, src, n)
	TEST_PRINT(str,			strncpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	test.function = "strncpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL, NULL);
}
void	print_test_strncpy_overlap(char const* test_name, t_testflags flags,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc,
		size_t n)
{
	TEST_INIT(str)
	test.flags |= FLAG_WARNING;
	TEST_PERFORM_(result, c_strncpy, dest_libccc, src_libccc, n)
	TEST_PERFORM_(expect,   strncpy, dest_libc,   src_libc,   n)
	TEST_PRINT(str,			strncpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src_libccc, n)
	test.function = "strncpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	char const* warning = NULL;
	if (strcmp(dest_libc, expecting_dest))
		warning = "strncpy() libc implementation does not handle overlap";
	print_test_str(&test, NULL, warning);
}
void	test_strncpy(void)
{
	char str1[64] = {'_'};
	char str2[64] = {'_'};
//	| TEST FUNCTION   | TEST NAME               | TESTFLAGS        | TEST ARGS
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test1,     test1_len);
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test2,     test2_len);
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test3,     test3_len);
	print_test_strncpy("strncpy (n = 0)        ", FALSE,			str1, str2, test1,             0);
	print_test_strncpy("strncpy (n < src_len)  ", FALSE,			str1, str2, test1, test1_len - 5);
	print_test_strncpy("strncpy (n > src_len)  ", FALSE,			str1, str2, test2, test2_len + 5);
	print_test_strncpy("strncpy (several '\\0's)",FALSE,			str1, str2, "Swag\0\0\0",      7);
	print_test_strncpy("strncpy (null dest)    ", ALLOW_SIGSEGV,	NULL, NULL, test1,             5);
	print_test_strncpy("strncpy (null src)     ", ALLOW_SIGSEGV,	str1, str2, NULL,              5);
	print_test_strncpy("strncpy (both null)    ", ALLOW_SIGSEGV,	NULL, NULL, NULL,              5);
	// overlap tests
	size_t d = 8;
	char expect[64] = { '_' };
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect, expect+d, strlen(expect+d));
	print_test_strncpy_overlap("strncpy (overlap <)    ", FALSE,	expect, str1, str2, str1+d, str2+d, test1_len);
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect+d, expect, strlen(expect));
	print_test_strncpy_overlap("strncpy (overlap >)    ", FALSE,	expect, str1+d, str2+d, str1, str2, test1_len);
}
#endif



#ifndef c_strlcpy
void test_strlcpy(void)	{}
#warning "strlcpy() test suite function defined, but the function isn't defined."
#else
void	print_test_strlcpy(char const* test_name, t_testflags flags,
		size_t expecting,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		size_t size)
{
	TEST_INIT(size)
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
	TEST_PERFORM_LIBC_DEST(	strlcpy, src, size)
#else
	TEST_PERFORM_DEST(		strlcpy, src, size)
#endif
	TEST_PRINT(size,		strlcpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcpy 'dest' arg",
		.flags = flags,
		.result = dest_libccc,
		.result_sig = test.result_sig,
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL, NULL);
}
void	print_test_strlcpy_overlap(char const* test_name, t_testflags flags,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc,
		size_t size)
{
	char const* warning = NULL;
	TEST_INIT(size)
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
	TEST_PERFORM_(result, c_strlcpy, dest_libccc, src_libccc, size)
	TEST_PERFORM_(expect,   strlcpy, dest_libc,   src_libc,   size)
	if (strcmp(dest_libc, expecting_dest))
		warning = "strlcpy() libc implementation does not handle overlap";
#else
	TEST_PERFORM_(result, c_strlcpy, dest_libccc, src_libccc, size)
	test.expect = strlen(src_libccc);
#endif
	TEST_PRINT(size, strlcpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src_libccc, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcpy 'dest' arg",
		.flags = flags,
		.result = dest_libccc,
		.result_sig = test.result_sig,
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL, warning);
}
void	test_strlcpy(void)
{
	char str1[64] = {'_'};
	char str2[64] = {'_'};
//	| TEST FUNCTION   | TEST NAME              | TESTFLAGS     | EXPECTING         | TEST ARGS
	print_test_strlcpy("strlcpy               ", FALSE,			test1_len-1, test1, str1, str2, test1, test1_len);
	print_test_strlcpy("strlcpy               ", FALSE,			test2_len-1, test2, str1, str2, test2, test2_len);
	print_test_strlcpy("strlcpy               ", FALSE,			test3_len-1, test3, str1, str2, test3, test3_len);
	print_test_strlcpy("strlcpy               ", FALSE,			10, " shi",         str1, str2, " shindeiru", 5);
	print_test_strlcpy("strlcpy               ", FALSE,			10, "testite",      str1, str2, "testitesty", 8);
	print_test_strlcpy("strlcpy (chars > 0x7F)", FALSE,			2,  "\x12",         str1, str2, "\x12\xAB\0", 2);
	print_test_strlcpy("strlcpy (n = 0)       ", FALSE,			10, "\x12",         str1, str2, " shindeiru", 0);
	print_test_strlcpy("strlcpy (n > src_len) ", FALSE,			10, " shindeiru",   str1, str2, " shindeiru", 15);
	print_test_strlcpy("strlcpy (n > dest_len)", FALSE,			10, "shindeiru ",   str1, str2, "shindeiru ", 50);
	print_test_strlcpy("strlcpy (null dest)   ", ALLOW_SIGSEGV,	0,  NULL,           NULL, NULL, " shindeiru", 5);
	print_test_strlcpy("strlcpy (null src)    ", ALLOW_SIGSEGV,	0,  "shindeiru ",   str1, str2, NULL,         5);
	print_test_strlcpy("strlcpy (both null)   ", ALLOW_SIGSEGV,	0,  NULL,           NULL, NULL, NULL,         5);
	// overlap tests
	size_t d = 8;
	char expect[64] = { '_' };
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect, expect+d, strlen(expect+d));
	print_test_strlcpy_overlap("strlcpy (overlap <)   ", FALSE,	test1+d,    str1, str2, str1+d, str2+d, test1_len);
	strcpy(str1, test1);
	strcpy(str2, test1);
	memcpy(expect,   (void*)test1, test1_len);
	memcpy(expect+d, (void*)test1, test1_len);
	print_test_strlcpy_overlap("strlcpy (overlap >)   ", FALSE,	expect+d,   str1+d, str2+d, str1, str2, test1_len);
}
#endif



#ifndef c_strcat
void test_strcat(void)	{}
#warning "strcat() test suite function defined, but the function isn't defined."
#else
void	print_test_strcat(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strcat, src)
	TEST_PRINT(str,			strcat, "dest=\"%s\", src=\"%s\"", dest_libccc, src)
	test.function = "strcat 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL, NULL);
}
void	print_test_strcat_overlap(char const* test_name, t_testflags flags,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc)
{
	TEST_INIT(str)
	test.flags |= FLAG_WARNING;
	TEST_PERFORM_(result, c_strcat, dest_libccc, src_libccc)
	TEST_PERFORM_(expect,   strcat, dest_libc,   src_libc)
	TEST_PRINT(str,			strcat, "dest=\"%s\", src=\"%s\"", dest_libccc, src_libccc)
	char const* warning = NULL;
	if (strcmp(dest_libc, expecting_dest))
		warning = "strcat() libc implementation does not handle overlap";
	test.function = "strcat 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL, warning);
}
void	test_strcat(void)
{
	char str1[128] = {'_'};
	char str2[128] = {'_'};
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS     | TEST ARGS
	print_test_strcat("strcat            ", FALSE,			str1, str2, "Bob");
	print_test_strcat("strcat            ", FALSE,			str1, str2, test1);
	print_test_strcat("strcat            ", FALSE,			str1, str2, test2);
	print_test_strcat("strcat            ", FALSE,			str1, str2, test3);
	print_test_strcat("strcat (null dest)", ALLOW_SIGSEGV,	NULL, NULL, "Bob\0");
	print_test_strcat("strcat (null src) ", ALLOW_SIGSEGV,	str1, str2, NULL);
	print_test_strcat("strcat (both null)", ALLOW_SIGSEGV,	NULL, NULL, NULL);
	// overlap tests
	size_t d = 8;
	char expect[128] = { '_' };
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect + strlen(expect), expect+d, strlen(expect+d));
	print_test_strcat_overlap("strcat (overlap <)",	FALSE,	expect, str1, str2, str1+d, str2+d);
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect+d + strlen(expect+d), expect, strlen(expect));
	print_test_strcat_overlap("strcat (overlap >)",	FALSE,	expect, str1+d, str2+d, str1, str2);
}
#endif



#ifndef c_strncat
void test_strncat(void)	{}
#warning "strncat() test suite function defined, but the function isn't defined."
#else
void	print_test_strncat(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		size_t n)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strncat, src, n)
	TEST_PRINT(str,			strncat, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	test.function = "strncat 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL, NULL);
}
void	print_test_strncat_overlap(char const* test_name, t_testflags flags,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc,
		size_t n)
{
	TEST_INIT(str)
	test.flags |= FLAG_WARNING;
	TEST_PERFORM_(result, c_strncat, dest_libccc, src_libccc, n)
	TEST_PERFORM_(expect,   strncat, dest_libc,   src_libc,   n)
	TEST_PRINT(str,			strncat, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src_libccc, n)
	test.function = "strncat 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	char const* warning = NULL;
	if (strcmp(dest_libc, expecting_dest))
		warning = "strncat() libc implementation does not handle overlap";
	print_test_str(&test, NULL, warning);
}
void	test_strncat(void)
{
	char str1[128] = {'_'};
	char str2[128] = {'_'};
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME            | TESTFLAGS       | TEST ARGS
	print_test_strncat("strncat            ", FALSE,			str1, str2, "Bob",      3);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test1,      test1_len);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test2,      test2_len);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test3,      test3_len);
	print_test_strncat("strncat (n = 0)    ", FALSE,			str1, str2, "Bobensen", 0);
	print_test_strncat("strncat (n < len)  ", FALSE,			str1, str2, "Bobensen", 3);
	print_test_strncat("strncat (n > len)  ", FALSE,			str1, str2, "Bob\0",    7);
	print_test_strncat("strncat (null dest)", ALLOW_SIGSEGV,	NULL, NULL, "Bob\0",    5);
	print_test_strncat("strncat (null src) ", ALLOW_SIGSEGV,	str1, str2, NULL,       5);
	print_test_strncat("strncat (both null)", ALLOW_SIGSEGV,	NULL, NULL, NULL,       5);
	// overlap tests
	size_t d = 8;
	char expect[128] = { '_' };
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect + strlen(expect), expect+d, strlen(expect+d));
	print_test_strncat_overlap("strncat (overlap <)    ", FALSE,	expect, str1, str2, str1+d, str2+d, test1_len);
	strcpy(str1, test1);
	strcpy(str2, test1);
	strcpy(expect, test1);
	memmove(expect+d + strlen(expect+d), expect, strlen(expect));
	print_test_strncat_overlap("strncat (overlap >)    ", FALSE,	expect, str1+d, str2+d, str1, str2, test1_len);
}
#endif



#ifndef c_strlcat
void test_strlcat(void)	{}
#warning "strlcat() test suite function defined, but the function isn't defined."
#else
void	print_test_strlcat(char const* test_name, t_testflags flags,
		size_t expecting,
		char const * expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		size_t size)
{
	TEST_INIT(size)
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
	TEST_PERFORM_LIBC_DEST(	strlcat, src, size)
#else
	TEST_PERFORM_DEST(		strlcat, src, size)
#endif
	TEST_PRINT(size,		strlcat, "dest=\"%s\", src=\"%s\", size=%zu", dest_libccc, src, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcat 'dest' arg",
		.flags = flags,
		.result = dest_libccc,
		.result_sig = test.result_sig,
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL, NULL);
}
void	print_test_strlcat_overlap(char const* test_name, t_testflags flags,
		size_t expecting,
		char const * expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src_libccc,
		char const* src_libc,
		size_t size)
{
	char const* warning = NULL;
	TEST_INIT(size)
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
	TEST_PERFORM_(result, c_strlcat, dest_libccc, src_libccc, size)
	TEST_PERFORM_(expect,   strlcat, dest_libc,   src_libc,   size)
	if (strcmp(dest_libc, expecting_dest))
		warning = "strlcat() libc implementation does not handle overlap";
#else
	TEST_PERFORM_(result, c_strlcat, dest_libccc, src_libccc, size)
	test.expect = expecting;
#endif
	TEST_PRINT(size,		strlcat, "dest=\"%s\", src=\"%s\", size=%zu", dest_libccc, src_libccc, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcat 'dest' arg",
		.flags = flags,
		.result = dest_libccc,
		.result_sig = test.result_sig,
#if (defined(__FreeBSD__) && __FreeBSD__ >= 3)
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL, warning);
}
void	test_strlcat(void)
{
	char str1[64] = {'_'};
	char str2[64] = {'_'};
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME            | TESTFLAGS       | EXPECTING                         | TEST ARGS
	print_test_strlcat("strlcat            ", FALSE,			15, "Sponge",                       str1, str2, " shindeiru", 5);
	print_test_strlcat("strlcat            ", FALSE,			28, "SpongeOmae wa mou shin",       str1, str2, test1,        test1_len);
	print_test_strlcat("strlcat            ", FALSE,			15, "SpongeOmae wa mou shin",       str1, str2, test2,        test2_len);
	print_test_strlcat("strlcat            ", FALSE,			48, "SpongeOmae wa mou shinUn a",   str1, str2, test3,        test3_len);
	print_test_strlcat("strlcat (n = 0)    ", FALSE,			10, "SpongeOmae wa mou shinUn a",   str1, str2, " shindeiru", 0);
	print_test_strlcat("strlcat (n < len)  ", FALSE,			25, "SpongeOmae wa mou shinUn a",   str1, str2, " shindeiru", 15);
	print_test_strlcat("strlcat (n > len)  ", FALSE,			28, "SpongeOmae wa mou shinUn a a", str1, str2, " a",         50);
	print_test_strlcat("strlcat (null dest)", ALLOW_SIGSEGV,	0,  NULL,                           NULL, NULL, " a",         5);
	print_test_strlcat("strlcat (null src) ", ALLOW_SIGSEGV,	0,  "SpongeOmae wa mou shinUn a a", str1, str2, NULL,         5);
	print_test_strlcat("strlcat (both null)", ALLOW_SIGSEGV,	0,  NULL,                           NULL, NULL, NULL,         5);
	// overlap tests
	size_t d = 8;
	char* expect;
	size_t expect_len;
	strcpy(str1, test1);
	strcpy(str2, test1);
	expect = strnew(test1_len + test1_len);
	strncpy(expect, test1,   test1_len);
	strncat(expect, test1+d, test1_len);
	expect_len = strlen(expect);
	print_test_strlcat_overlap("strlcat (overlap <)   ", FALSE,	expect_len, expect, str1, str2, str1+d, str2+d, test1_len+test1_len);
	strcpy(str1, test1);
	strcpy(str2, test1);
	expect = strnew(test1_len + test1_len);
	strncpy(expect, test1, test1_len);
	strncat(expect, test1, test1_len);
	expect_len = strlen(expect+d);
	print_test_strlcat_overlap("strlcat (overlap >)   ", FALSE,	expect_len, expect+d, str1+d, str2+d, str1, str2, test1_len+test1_len);
}
#endif



/*============================================================================*\
||                                String Checks                               ||
\*============================================================================*/

#ifndef c_strlen
void test_strlen(void)	{}
#warning "strlen() test suite function defined, but the function isn't defined."
#else
void	print_test_strlen(char const* test_name, t_testflags flags,
		char const* str)
{
	TEST_INIT(size)
	TEST_PERFORM_LIBC( strlen, str)
	TEST_PRINT(size,   strlen, "str=\"%s\"", str)
}
void	test_strlen(void)
{
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS     | TEST ARGS
	print_test_strlen("strlen            ", FALSE,			"Hello World!");
	print_test_strlen("strlen            ", FALSE,			test1);
	print_test_strlen("strlen            ", FALSE,			test2);
	print_test_strlen("strlen            ", FALSE,			test3);
	print_test_strlen("strlen            ", FALSE,			"a");
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_cc_c0);
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_cc_c1);
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_utf8_fr);
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_utf8_ru);
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_utf8_jp);
	print_test_strlen("strlen (unicode)  ", FALSE,			teststr_utf8_ho);
	print_test_strlen("strlen (empty str)", FALSE,			"");
	print_test_strlen("strlen (null str) ", ALLOW_SIGSEGV,	NULL);
}
#endif



#ifndef c_strcmp
void test_strcmp(void)	{}
#warning "strcmp() test suite function defined, but the function isn't defined."
#else
void	print_test_strcmp(char const* test_name, t_testflags flags,
		char const* str1,
		char const* str2)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	strcmp, str1, str2)
	TEST_PRINT(sign,	strcmp, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strcmp(void)
{
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS     | TEST ARGS
	print_test_strcmp("strcmp            ", FALSE,			test1, test1);
	print_test_strcmp("strcmp            ", FALSE,			test1, test2);
	print_test_strcmp("strcmp            ", FALSE,			test1, test3);
	print_test_strcmp("strcmp            ", FALSE,			test2, test1);
	print_test_strcmp("strcmp            ", FALSE,			test2, test2);
	print_test_strcmp("strcmp            ", FALSE,			test2, test3);
	print_test_strcmp("strcmp            ", FALSE,			test3, test1);
	print_test_strcmp("strcmp            ", FALSE,			test3, test2);
	print_test_strcmp("strcmp            ", FALSE,			test3, test3);
	print_test_strcmp("strcmp (both empty)", FALSE,			"",    "");
	print_test_strcmp("strcmp (vs empty)  ", FALSE,			test1, "");
	print_test_strcmp("strcmp (prefix >)  ", FALSE,			"abc", "ab");
	print_test_strcmp("strcmp (prefix <)  ", FALSE,			"ab",  "abc");
	print_test_strcmp("strcmp (null str1)", ALLOW_SIGSEGV,	NULL,  test3);
	print_test_strcmp("strcmp (null str2)", ALLOW_SIGSEGV,	test2, NULL);
	print_test_strcmp("strcmp (both null)", ALLOW_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strncmp
void test_strncmp(void)	{}
#warning "strncmp() test suite function defined, but the function isn't defined."
#else
void	print_test_strncmp(char const* test_name, t_testflags flags,
		char const* str1,
		char const* str2,
		size_t n)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	strncmp, str1, str2, n)
	TEST_PRINT(sign,	strncmp, "str1=\"%s\", str2=\"%s\", n=%zu", str1, str2, n)
}
void	test_strncmp(void)
{
//	| TEST FUNCTION  | TEST NAME             | TESTFLAGS      | TEST ARGS
	print_test_strncmp("strncmp            ", FALSE,			test1,     test1,     test1_len);
	print_test_strncmp("strncmp            ", FALSE,			test1,     test2,     test2_len);
	print_test_strncmp("strncmp            ", FALSE,			test1,     test3,     test3_len);
	print_test_strncmp("strncmp            ", FALSE,			test2,     test1,     test1_len);
	print_test_strncmp("strncmp            ", FALSE,			test2,     test2,     test2_len);
	print_test_strncmp("strncmp            ", FALSE,			test2,     test3,     test3_len);
	print_test_strncmp("strncmp            ", FALSE,			test3,     test1,     test1_len);
	print_test_strncmp("strncmp            ", FALSE,			test3,     test2,     test2_len);
	print_test_strncmp("strncmp            ", FALSE,			test3,     test3,     test3_len);
	print_test_strncmp("strncmp            ", FALSE,			"abc",     "abcdef",  3);
	print_test_strncmp("strncmp            ", FALSE,			test2 + 1, test3 + 3, 2);
	print_test_strncmp("strncmp (n = 0)    ", FALSE,			test2,     test3,     0);
	print_test_strncmp("strncmp (both empty)", FALSE,			"",        "",        5);
	print_test_strncmp("strncmp (prefix, n beyond)", FALSE,	"abc",     "ab",      5);
	print_test_strncmp("strncmp (prefix, n at end)", FALSE,	"abc",     "ab",      2);
	print_test_strncmp("strncmp (null str1)", ALLOW_SIGSEGV,	NULL,      test3,     5);
	print_test_strncmp("strncmp (null str2)", ALLOW_SIGSEGV,	test2,     NULL,      5);
	print_test_strncmp("strncmp (both null)", ALLOW_SIGSEGV,	NULL,      NULL,      5);
}
#endif


#ifndef c_strequ
void test_strequ(void)	{}
#warning "strequ() test suite function defined, but the function isn't defined."
#else
#ifndef strequ
#define strequ(str1, str2)	(strcmp(str1, str2) == 0)
#endif
void	print_test_strequ(char const* test_name, t_testflags flags,
		char const* str1,
		char const* str2)
{
	TEST_INIT(bool)
	TEST_PERFORM_LIBC(	strequ, str1, str2)
	TEST_PRINT(bool,	strequ, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strequ(void)
{
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS     | TEST ARGS
	print_test_strequ("strequ            ", FALSE,			test1, test1);
	print_test_strequ("strequ            ", FALSE,			test1, test2);
	print_test_strequ("strequ            ", FALSE,			test1, test3);
	print_test_strequ("strequ            ", FALSE,			test2, test1);
	print_test_strequ("strequ            ", FALSE,			test2, test2);
	print_test_strequ("strequ            ", FALSE,			test2, test3);
	print_test_strequ("strequ            ", FALSE,			test3, test1);
	print_test_strequ("strequ            ", FALSE,			test3, test2);
	print_test_strequ("strequ            ", FALSE,			test3, test3);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_cc_c0,   teststr_cc_c0);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_cc_c1,   teststr_cc_c1);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_utf8_fr, teststr_utf8_fr);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_utf8_ru, teststr_utf8_ru);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_utf8_jp, teststr_utf8_jp);
	print_test_strequ("strequ (unicode)  ", FALSE,          teststr_utf8_ho, teststr_utf8_ho);
	print_test_strequ("strequ (empty str)", FALSE,			test1, "");
	print_test_strequ("strequ (null str1)", ALLOW_SIGSEGV,	NULL,  test2);
	print_test_strequ("strequ (null str2)", ALLOW_SIGSEGV,	test1, NULL);
	print_test_strequ("strequ (both null)", ALLOW_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strnequ
void test_strnequ(void)	{}
#warning "strnequ() test suite function defined, but the function isn't defined."
#else
#ifndef strnequ
#define strnequ(str1, str2, n)	(strncmp(str1, str2, n) == 0)
#endif
void	print_test_strnequ(char const* test_name, t_testflags flags,
		char const* str1,
		char const* str2,
		size_t n)
{
	TEST_INIT(bool)
	TEST_PERFORM_LIBC(	strnequ, str1, str2, n)
	TEST_PRINT(bool,	strnequ, "str1=\"%s\", str2=\"%s\", n=%zu", str1, str2, n)
}
void	test_strnequ(void)
{
//	| TEST FUNCTION  | TEST NAME              | TESTFLAGS      | TEST ARGS
	print_test_strnequ("strnequ            ", 	FALSE,			test1, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test1, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test1, test3, test3_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test2, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test2, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test2, test3, test3_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test3, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test3, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,			test3, test3, test3_len);
	print_test_strnequ("strnequ (empty str)",	FALSE,			test1, "",    5);
	print_test_strnequ("strnequ (n = 0)    ",	FALSE,			test1, test1, 0);
	print_test_strnequ("strnequ (n > len)  ",	FALSE,			test1, test1, 30);
	print_test_strnequ("strnequ (null str1)",	ALLOW_SIGSEGV,	NULL,  test2, 7);
	print_test_strnequ("strnequ (null str2)",	ALLOW_SIGSEGV,	test1, NULL,  7);
	print_test_strnequ("strnequ (both null)",	ALLOW_SIGSEGV,	NULL,  NULL,  7);
}
#endif


#ifndef c_strhas
void test_strhas(void)	{}
#warning "strhas() test suite function defined, but the function isn't defined."
#else
void	print_test_strhas(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* str,
		char const* charset)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strhas, str, charset)
	TEST_PRINT(bool,strhas, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_strhas(void)
{
	static char* test_ = "sweg ginay";
//	| TEST FUNCTION  | TEST NAME              | TESTFLAGS      |EXPECT| TEST ARGS
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test1, "_0i");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test2, "na");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test3, "in");
	print_test_strhas("strhas               ",	FALSE,			FALSE,  test_, "mz");
	print_test_strhas("strhas               ",	FALSE,			FALSE,  test_, "z");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test_, "aze");
	print_test_strhas("strhas               ",	FALSE,			FALSE,  test_, "z_u");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_cc_c0,   "␡");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_cc_c1,   "");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_utf8_fr, "œ");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_utf8_ru, "щ");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_utf8_jp, "愛");
	print_test_strhas("strhas (unicode)     ",  FALSE,          TRUE,   teststr_utf8_ho, "𐐔");
	print_test_strhas("strhas (null str)    ",	ALLOW_SIGSEGV,	FALSE,  NULL, "mz");
	print_test_strhas("strhas (null charset)",	ALLOW_SIGSEGV,	FALSE,  "sw", NULL);
	print_test_strhas("strhas (both null)   ",	ALLOW_SIGSEGV,	FALSE,  NULL, NULL);
}
#endif


#ifndef c_strhasonly
void test_strhasonly(void)	{}
#warning "strhasonly() test suite function defined, but the function isn't defined."
#else
void	print_test_strhasonly(char const* test_name, t_testflags flags,
		t_bool expecting,
		char const* str,
		char const* charset)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strhasonly, str, charset)
	TEST_PRINT(bool,strhasonly, "str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_strhasonly(void)
{
	static char* test_ = "sweg ginay";
//	| TEST FUNCTION      | TEST NAME                   | TESTFLAGS     |EXPECT| TEST ARGS
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test1, "m");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test2, "na");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test3, "in");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test_, "mz");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test_, "aze");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test_, "z_u");
	print_test_strhasonly("strhasonly                ",	FALSE,			TRUE,   test_, "aiey gmnsw");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test_, "aiey gsw");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_cc_c0,   "␡");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_cc_c1,   "");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_utf8_fr, "œ");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_utf8_ru, "щ");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_utf8_jp, "愛");
	print_test_strhasonly("strhasonly (unicode)      ", FALSE,          FALSE,  teststr_utf8_ho, "𐐔");
	print_test_strhasonly("strhasonly (empty str)    ",	FALSE,			TRUE,   "",     "z_u");
	print_test_strhasonly("strhasonly (empty charset)",	FALSE,			FALSE,  "sweg", "");
	print_test_strhasonly("strhasonly (null str)     ",	ALLOW_SIGSEGV,	FALSE,  NULL, "mz");
	print_test_strhasonly("strhasonly (null charset) ",	ALLOW_SIGSEGV,	FALSE,  "sw", NULL);
	print_test_strhasonly("strhasonly (both null)    ",	ALLOW_SIGSEGV,	FALSE,  NULL, NULL);
}
#endif


#ifndef c_strcount_char
void test_strcount_char(void)	{}
#warning "strcount_char() test suite function defined, but the function isn't defined."
#else
void	print_test_strcount_char(char const* test_name, t_testflags flags,
		size_t expecting,
		char const* str,
		char c)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strcount_char, str, c)
	TEST_PRINT(bool,strcount_char, "str=\"%s\", c='%c'/0x%X", str, c, c)
}
void	test_strcount_char(void)
{
	static char* test_ = "sweg ginay";
//	| TEST FUNCTION         | TEST NAME                  | TESTFLAGS    |EXPECT| TEST ARGS
	print_test_strcount_char("strcount_char            ",	FALSE,			2,    test1, 'm');
	print_test_strcount_char("strcount_char            ",	FALSE,			3,    test2, '?');
	print_test_strcount_char("strcount_char            ",	FALSE,			1,    test3, '.');
	print_test_strcount_char("strcount_char            ",	FALSE,			0,    test3, '_');
	print_test_strcount_char("strcount_char            ",	FALSE,			3,    test_, 'g');
	print_test_strcount_char("strcount_char            ",	FALSE,			0,    test_, 'z');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          0,    teststr_cc_c0,   (char)L'␡');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          1,    teststr_cc_c1,   (char)L'');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          0,    teststr_utf8_fr, (char)L'œ');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          0,    teststr_utf8_ru, (char)L'щ');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          0,    teststr_utf8_jp, (char)L'愛');
	print_test_strcount_char("strcount_char (unicode)  ",   FALSE,          0,    teststr_utf8_ho, (char)0x10414);//L'𐐔');
	print_test_strcount_char("strcount_char (empty str)",	FALSE,			0,    "",    'a');
	print_test_strcount_char("strcount_char ('\\0 char')",	FALSE,			1,    "sweg", '\0');
	print_test_strcount_char("strcount_char (null str) ",ALLOW_SIGSEGV,	0,    NULL,  'a');
}
#endif


#ifndef c_strcount_str
void test_strcount_str(void)	{}
#warning "strcount_str() test suite function defined, but the function isn't defined."
#else
void	print_test_strcount_str(char const* test_name, t_testflags flags,
		size_t expecting,
		char const* str,
		char const* query)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strcount_str, str, query)
	TEST_PRINT(bool,strcount_str, "str=\"%s\", query=\"%s\"", str, query)
}
void	test_strcount_str(void)
{
	static char* test_ = "sweg ginay";
//	| TEST FUNCTION        | TEST NAME                   | TESTFLAGS     |EXPECT| TEST ARGS
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    test1, " m");
	print_test_strcount_str("strcount_str              ",	FALSE,			2,    test2, "?");
	print_test_strcount_str("strcount_str              ",	FALSE,			3,    test3, "ange");
	print_test_strcount_str("strcount_str              ",	FALSE,			0,    test3, "_");
	print_test_strcount_str("strcount_str              ",	FALSE,			3,    test_, "g");
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    test_, "sweg");
	print_test_strcount_str("strcount_str              ",	FALSE,			0,    test_, "swef");
	print_test_strcount_str("strcount_str              ",	FALSE,			0,    test_, "gg");
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    test_, "g g");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_cc_c0,   "␡");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_cc_c1,   "");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_utf8_fr, "œ");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_utf8_ru, "щ");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_utf8_jp, "愛");
	print_test_strcount_str("strcount_str (unicode)    ",   FALSE,          1,    teststr_utf8_ho, "𐐔");
	print_test_strcount_str("strcount_str (empty str)  ",	FALSE,			0,    "",    "g");
	print_test_strcount_str("strcount_str (empty query)",	FALSE,			0,    test1, "");
	print_test_strcount_str("strcount_str (null str)   ", ALLOW_SIGSEGV,   0,    NULL, "mz");
	print_test_strcount_str("strcount_str (null query) ", ALLOW_SIGSEGV,   0,    "sw", NULL);
	print_test_strcount_str("strcount_str (both null)  ", ALLOW_SIGSEGV,   0,    NULL, NULL);
}
#endif


/*============================================================================*\
||                         String Searching/Replacing                         ||
\*============================================================================*/

#ifndef c_strchr
void test_strchr(void)	{}
#warning "strchr() test suite function defined, but the function isn't defined."
#else
void	print_test_strchr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char c)
{
	TEST_INIT(ptr)
	if (expecting)	{ TEST_PERFORM(	strchr, str, c) }
	else		{ TEST_PERFORM_LIBC(strchr, str, c) }
	TEST_PRINT(ptr,		strchr, "str=%p/\"%s\", c='%c'/0x%X", (void*)str, str, c, c)
}
void	test_strchr(void)
{
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS    | EXPECTS               | TEST ARGS
	print_test_strchr("strchr             ", FALSE        , NULL                  , test1          , 'm');
	print_test_strchr("strchr             ", FALSE        , NULL                  , test2          , '?');
	print_test_strchr("strchr             ", FALSE        , NULL                  , test3          , ' ');
	print_test_strchr("strchr             ", FALSE        , NULL                  , test1          , '_');
	print_test_strchr("strchr             ", FALSE        , NULL                  , test2          , '_');
	print_test_strchr("strchr             ", FALSE        , NULL                  , test3          , '_');
	print_test_strchr("strchr (unicode)   ", FALSE        , teststr_cc_c1   + 0x3B, teststr_cc_c1  , (char)L'');
	print_test_strchr("strchr (unicode)   ", FALSE        , NULL /*teststr_cc_c0   + 0x00*/, teststr_cc_c0  , (char)L'␡');
	print_test_strchr("strchr (unicode)   ", FALSE        , NULL /*teststr_utf8_fr + 0x3B*/, teststr_utf8_fr, (char)L'œ');
	print_test_strchr("strchr (unicode)   ", FALSE        , NULL /*teststr_utf8_ru + 0x47*/, teststr_utf8_ru, (char)L'щ');
	print_test_strchr("strchr (unicode)   ", FALSE        , NULL /*teststr_utf8_jp + 0x21*/, teststr_utf8_jp, (char)L'愛');
	print_test_strchr("strchr (unicode)   ", FALSE        , NULL /*teststr_utf8_ho + 0x17*/, teststr_utf8_ho, (char)0x10414);//L'𐐔');
	print_test_strchr("strchr (c = '\\0') ", FALSE        , NULL                  , test3          , '\0');
	print_test_strchr("strchr (null ptr)  ", ALLOW_SIGSEGV, NULL                  , NULL           , 'm');

	// TODO: test unicode symbols encoded on multiple utf8 sequences
}
#endif


#ifndef c_strstr
void test_strstr(void)	{}
#warning "strstr() test suite function defined, but the function isn't defined."
#else
void	print_test_strstr(char const* test_name, t_testflags flags,
		char const* str,
		char const* query)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	strstr, str, query)
	TEST_PRINT(ptr,		strstr, "str=%p/\"%s\", query=\"%s\"", (void*)str, str, query)
}
void	test_strstr(void)
{
//	| TEST FUNCTION  | TEST NAME             | TESTFLAGS     | TEST ARGS
	print_test_strstr("strstr              ",	FALSE,			test1, " m");
	print_test_strstr("strstr              ",	FALSE,			test2, "?");
	print_test_strstr("strstr              ",	FALSE,			test3, " ");
	print_test_strstr("strstr              ",	FALSE,			test1, "mou ");
	print_test_strstr("strstr (whole str)  ",	FALSE,			test1, test1);
	print_test_strstr("strstr (at tail)    ",	FALSE,			"aaab", "ab");
	print_test_strstr("strstr              ",	FALSE,			test1, "??");
	print_test_strstr("strstr              ",	FALSE,			test3, "???");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_cc_c0,   "␡");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_cc_c1,   "");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_utf8_fr, "œ");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_utf8_ru, "щ");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_utf8_jp, "愛");
	print_test_strstr("strstr (unicode)    ",   FALSE,          teststr_utf8_ho, "𐐔");
//	print_test_strstr("strstr (empty query)",   FALSE,          test3, ""); // TODO The test here fails because there is an intentional design difference
	print_test_strstr("strstr (null str)   ", ALLOW_SIGSEGV,	NULL,  "mou ");
	print_test_strstr("strstr (null query) ", ALLOW_SIGSEGV,	test1, NULL);
	print_test_strstr("strstr (both null)  ", ALLOW_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strrchr
void test_strrchr(void)	{}
#warning "strrchr() test suite function defined, but the function isn't defined."
#else
void	print_test_strrchr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char c)
{
	TEST_INIT(ptr)
	if (expecting)	{ TEST_PERFORM(	strchr, str, c) }
	else		{ TEST_PERFORM_LIBC(strchr, str, c) }
	TEST_PRINT(ptr,		strrchr, "str=%p/\"%s\", c='%c'/0x%X", (void*)str, str, c, c)
}
void	test_strrchr(void)
{
//	| TEST FUNCTION  | TEST NAME               | TESTFLAGS    | EXPECTS               | TEST ARGS
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test1, 'm');
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test2, '?');
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test3, ' ');
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test1, '_');
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test2, '_');
	print_test_strrchr("strrchr             ",  FALSE,         NULL,                   test3, '_');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         teststr_cc_c1   + 0x3B, teststr_cc_c1,   (char)L'');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         NULL /*teststr_cc_c0   + 0x00*/, teststr_cc_c0,   (char)L'␡');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         NULL /*teststr_utf8_fr + 0x3B*/, teststr_utf8_fr, (char)L'œ');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         NULL /*teststr_utf8_ru + 0x47*/, teststr_utf8_ru, (char)L'щ');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         NULL /*teststr_utf8_jp + 0x21*/, teststr_utf8_jp, (char)L'愛');
	print_test_strrchr("strrchr (unicode)   ",  FALSE,         NULL /*teststr_utf8_ho + 0x17*/, teststr_utf8_ho, (char)0x10414);//L'𐐔');
	print_test_strrchr("strrchr (c = '\\0')  ", FALSE,         NULL,                   test3, '\0');
	print_test_strrchr("strrchr (null ptr)  ",  ALLOW_SIGSEGV, NULL,                   NULL,  'm');
}
#endif


#ifndef c_strrstr
void test_strrstr(void)	{}
#warning "strrstr() test suite function defined, but the function isn't defined."
#else
void	print_test_strrstr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char const* query)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	strrstr, str, query)
	TEST_PRINT(ptr,	strrstr, "str=%p/\"%s\", query=\"%s\"", (void*)str, str, query)
}
void	test_strrstr(void)
{
//	| TEST FUNCTION  | TEST NAME              | TESTFLAGS      | EXPECTING   | TEST ARGS
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 8,     test1, "mou ");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 0,     test1, "Omae ");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 20,    test1, "u.");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test1, "u. ");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test1, " u.");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 21,    test1, ".");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test1, ". ");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test1, " .");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test1, "??");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,          test3, "???");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_cc_c0 + 0x0,    teststr_cc_c0,   "␡");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_cc_c1 + 0x39,   teststr_cc_c1,   "");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_utf8_fr + 0x3B, teststr_utf8_fr, "œ");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_utf8_ru + 0x47, teststr_utf8_ru, "щ");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_utf8_jp + 0x21, teststr_utf8_jp, "愛");
	print_test_strrstr("strrstr (unicode)    ", FALSE,          teststr_utf8_ho + 0x17, teststr_utf8_ho, "𐐔");
	print_test_strrstr("strrstr (empty query)",	FALSE,			NULL,          test3, "");
	print_test_strrstr("strrstr (null str)   ",	ALLOW_SIGSEGV,	NULL,          NULL,  "mou ");
	print_test_strrstr("strrstr (null query) ",	ALLOW_SIGSEGV,	NULL,          test1, NULL);
	print_test_strrstr("strrstr (both null)  ",	ALLOW_SIGSEGV,	NULL,          NULL,  NULL);
}
#endif


#ifndef c_strnchr
void test_strnchr(void)	{}
#warning "strnchr() test suite function defined, but the function isn't defined."
#else
void	print_test_strnchr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char c,
		size_t n)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	strnchr, str, c, n)
	TEST_PRINT(ptr,	strnchr, "str=%p/\"%s\", c='%c'/0x%X, n=%zu", (void*)str, str, c, c, n)
}
void	test_strnchr(void)
{
//	| TEST FUNCTION  | TEST NAME               | TESTFLAGS     |  EXPECTING  | TEST ARGS
	print_test_strnchr("strnchr             ",	FALSE,			test1 + 5,     test1, 'w', 16);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, 'u', 8);
	print_test_strnchr("strnchr             ",	FALSE,			test1 + 10,    test1, 'u', 16);
	print_test_strnchr("strnchr             ",	FALSE,			test1 + 10,    test1, 'u', 32);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, '.', 8);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, '.', 16);
	print_test_strnchr("strnchr             ",	FALSE,			test1 + 21,    test1, '.', 32);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, '_', 16);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, 'w', 1);
	print_test_strnchr("strnchr             ",	FALSE,			NULL,          test1, '_', 1);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          teststr_cc_c1   + 0x3B, teststr_cc_c1,   (char)L'',	 128);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          NULL /*teststr_cc_c0   + 0x00*/, teststr_cc_c0,   (char)L'␡',	 128);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          NULL /*teststr_utf8_fr + 0x3B*/, teststr_utf8_fr, (char)L'œ',	 128);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          NULL /*teststr_utf8_ru + 0x47*/, teststr_utf8_ru, (char)L'щ',	 128);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          NULL /*teststr_utf8_jp + 0x21*/, teststr_utf8_jp, (char)L'愛',	 128);
	print_test_strnchr("strnchr (unicode)   ",  FALSE,          NULL /*teststr_utf8_ho + 0x17*/, teststr_utf8_ho, (char)0x10414, 128);
	print_test_strnchr("strnchr (c = '\\0')  ",	FALSE,			NULL,          test3, '\0', 16);
	print_test_strnchr("strnchr (n = 0)     ",	FALSE,			NULL,          test1, 'w', 0);
	print_test_strnchr("strnchr (n = len)   ",	FALSE,			NULL,          test1, '_', test1_len);
	print_test_strnchr("strnchr (n > len)   ",	FALSE,			NULL,          test1, '_', test1_len + 32);
	print_test_strnchr("strnchr (null ptr)  ",	ALLOW_SIGSEGV, NULL,          NULL,  'm', 16);
}
#endif


#ifndef c_strnstr
void test_strnstr(void)	{}
#warning "strnstr() test suite function defined, but the function isn't defined."
#else
void	print_test_strnstr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char const* query,
		size_t n)
{
	TEST_INIT(ptr)
// TODO inspect which platforms have this function
#ifdef __APPLE__
	TEST_PERFORM_LIBC(	strnstr, str, query, n)
#else
	TEST_PERFORM(		strnstr, str, query, n)
#endif
	TEST_PRINT(ptr,	strnstr, "str=%p/\"%s\", query=\"%s\", n=%zu", (void*)str, str, query, n)
}
void	test_strnstr(void)
{
//	| TEST FUNCTION  | TEST NAME              | TESTFLAGS      | EXPECTING    | TEST ARGS
	print_test_strnstr("strnstr              ",	FALSE,          test1 + 8,     test1,           "mou ", 16);
	print_test_strnstr("strnstr              ",	FALSE,          NULL,          test1,           "??",   test1_len);
	print_test_strnstr("strnstr              ",	FALSE,          test2 + 4,     test2,           "??",   test2_len);
	print_test_strnstr("strnstr              ",	FALSE,          NULL,          test3,           "???",  test3_len);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_cc_c0 + 0x0,    teststr_cc_c0,   "␡",	128);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_cc_c1 + 0x39,   teststr_cc_c1,   "",	128);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_utf8_fr + 0x3B, teststr_utf8_fr, "œ",	128);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_utf8_ru + 0x47, teststr_utf8_ru, "щ",	128);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_utf8_jp + 0x21, teststr_utf8_jp, "愛",	128);
	print_test_strnstr("strnstr (unicode)    ", FALSE, teststr_utf8_ho + 0x17, teststr_utf8_ho, "𐐔",	128);
	print_test_strnstr("strnstr (empty query)",	FALSE,          test1,         test1,           "\0",   16);
	print_test_strnstr("strnstr (n = 0)      ",	FALSE,          NULL,          test1,           "mou ", 0);
	print_test_strnstr("strnstr (n = len)    ",	FALSE,          NULL,          test1,           "_",    test1_len);
	print_test_strnstr("strnstr (n > len)    ",	FALSE,          NULL,          test1,           "_",    test1_len + 32);
	print_test_strnstr("strnstr (null str)   ",	ALLOW_SIGSEGV,  NULL,          NULL,            "mou ", 16);
	print_test_strnstr("strnstr (null query) ",	ALLOW_SIGSEGV,  NULL,          test1,           NULL,   16);
	print_test_strnstr("strnstr (both null)  ",	ALLOW_SIGSEGV,  NULL,          NULL,            NULL,   16);
}
#endif


#ifndef c_strremove
void test_strremove(void)	{}
#warning "strremove() test suite function defined, but the function isn't defined."
#else
void	print_test_strremove(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char const* query)
{
	TEST_INIT(str)
	TEST_PERFORM(	strremove, str, query)
	TEST_PRINT(str,	strremove, "str=\"%s\", query=\"%s\"", str, query)
	TEST_FREE()
}
void	test_strremove(void)
{
//	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strrep_char
void test_strrep_char(void)	{}
#warning "strrep_char() test suite function defined, but the function isn't defined."
#else
void	print_test_strrep_char(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char char_old,
		char char_new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_char, str, char_old, char_new)
	TEST_PRINT(str,	strrep_char, "str=\"%s\", old='%c'/0x%X, new='%c'/0x%X", str, char_old, char_old, char_new, char_new)
	TEST_FREE()
}
void	test_strrep_char(void)
{
//	| TEST FUNCTION       | TEST NAME                 |TESTFLAG| EXPECTING                     | TEST ARGS
	print_test_strrep_char("strrep_char               ", FALSE,   "Hellx Wxrld!",                "Hello World!",   'o', 'x');
	print_test_strrep_char("strrep_char               ", FALSE,   "Om@e w@ mou shindeiru.",      test1,            'a', '@');
	print_test_strrep_char("strrep_char               ", FALSE,   "Nani___",                     test2,            '?', '_');
	print_test_strrep_char("strrep_char               ", FALSE,   "Un @nge m@nge de l@ f@nge.",  test3,            'a', '@');
	print_test_strrep_char("strrep_char               ", FALSE,   "***swag***",                  "___swag___",     '_', '*');
	print_test_strrep_char("strrep_char               ", FALSE,   "aaa bbb ccc",                 "aaa_bbb_ccc",    '_', ' ');
	print_test_strrep_char("strrep_char (identical)   ", FALSE,   "Hello World!",                "Hello World!",   'o', 'o');
	print_test_strrep_char("strrep_char (no match)    ", FALSE,   "Hello World!",                "Hello World!",   'x', 'y');
	print_test_strrep_char("strrep_char (to space)    ", FALSE,   "test test test",              "test_test_test", '_', ' ');
	print_test_strrep_char("strrep_char (from space)  ", FALSE,   "test_test_test",              "test test test", ' ', '_');
	print_test_strrep_char("strrep_char (all same)    ", FALSE,   "bbb",                         "aaa",            'a', 'b');
//	print_test_strrep_char("strrep_char (unicode)     ", FALSE,   "maïs à l'�eil…",              "maïs à l'œil…",  'œ', 'e');  // TODO fix this test
	print_test_strrep_char("strrep_char (empty str)   ", FALSE,   "",                            "",               'a', 'b');
//	print_test_strrep_char("strrep_char (old='\\0')   ", FALSE,   "test",                        "test",           '\0','x'); // TODO proper buffer overrun test
	print_test_strrep_char("strrep_char (new='\\0')   ", FALSE,   "test",                        "test",           'x', '\0');
	print_test_strrep_char("strrep_char (both='\\0')  ", FALSE,   "test",                        "test",           '\0','\0');
	print_test_strrep_char("strrep_char (null str)    ", ALLOW_SIGSEGV,   NULL,                  NULL,             'a', 'b');
}
#endif



#ifndef c_strrep_cset
void test_strrep_cset(void)	{}
#warning "strrep_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_strrep_cset(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char const* cset_old,
		char const* cset_new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_cset, str, cset_old, cset_new)
	TEST_PRINT(str,	strrep_cset, "str=\"%s\", old=\"%s\", new=\"%s\"", str, cset_old, cset_new)
	TEST_FREE()
}
void	test_strrep_cset(void)
{
//	| TEST FUNCTION       | TEST NAME                   | TESTFLAGS      | EXPECTING                    | TEST ARGS
	print_test_strrep_cset("strrep_cset               ", FALSE,           "Hellx Wxrld!",                "Hello World!",   "o",      "x");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "Omae wa mxe shindeire.",      test1,            "ou",     "xe");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "N@ni###",                     test2,            "a?",     "@#");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "Un @n$e m@n$e de l@ f@n$e.",  test3,            "ag",     "@$");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "@@@@@@@@@",                   "ABCABCABC",      "ABC",    "@@@");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "XYZ XYZ XYZ",                 "ABC ABC ABC",    "ABC",    "XYZ");
	print_test_strrep_cset("strrep_cset               ", FALSE,           "***swag***",                  "___swag___",     "_",      "*");
	print_test_strrep_cset("strrep_cset (vowels)      ", FALSE,           "Hxllx Wxrld!",                "Hello World!",   "aeiou",  "xxxxx");
	print_test_strrep_cset("strrep_cset (vowels)      ", FALSE,           "H3ll0 W0rld!",                "Hello World!",   "aeiou",  "43102");
	print_test_strrep_cset("strrep_cset (multi-char)  ", FALSE,           "Hyllx Wxrld!",                "Hello World!",   "eo",     "yx");
	print_test_strrep_cset("strrep_cset (rot13)       ", FALSE,           "Uryyb Jbeyq!",                "Hello World!",   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm");
	print_test_strrep_cset("strrep_cset (identical)   ", FALSE,           "Hello World!",                "Hello World!",   "eo",     "eo");
	print_test_strrep_cset("strrep_cset (no match)    ", FALSE,           "Hello World!",                "Hello World!",   "xyz",    "abc");
	print_test_strrep_cset("strrep_cset (diff len)    ", FALSE,           NULL,                          "Hello World!",   "aeiou",  "xxx");
	print_test_strrep_cset("strrep_cset (diff len)    ", FALSE,           NULL,                          "Hello World!",   "eo",     "30xyz");
	print_test_strrep_cset("strrep_cset (unicode)     ", FALSE,           "Êtr3 à mêm3 d3 ç4, d'41r sûr — m4ng3r d2 m4ïs à l'œ1l… D'0ù l4 p41x s2r l'îl3 d3 s0n âm3…", teststr_utf8_fr,  "aeiou",  "43102");
	print_test_strrep_cset("strrep_cset (empty str)   ", FALSE,           "",                            "",               "abc",    "xyz");
	print_test_strrep_cset("strrep_cset (empty old)   ", FALSE,           NULL,                          "test",           "",       "xyz");
	print_test_strrep_cset("strrep_cset (empty new)   ", FALSE,           NULL,                          "test",           "xyz",    "");
	print_test_strrep_cset("strrep_cset (both empty)  ", FALSE,           "test",                        "test",           "",       "");
	print_test_strrep_cset("strrep_cset (null str)    ", ALLOW_SIGSEGV,   NULL,                          NULL,             "abc",    "xyz");
	print_test_strrep_cset("strrep_cset (null old)    ", ALLOW_SIGSEGV,   NULL,                          "test",           NULL,     "xyz");
	print_test_strrep_cset("strrep_cset (null new)    ", ALLOW_SIGSEGV,   NULL,                          "test",           "abc",    NULL);
	print_test_strrep_cset("strrep_cset (null csets)  ", ALLOW_SIGSEGV,   NULL,                          "test",           NULL,     NULL);
	print_test_strrep_cset("strrep_cset (all null)    ", ALLOW_SIGSEGV,   NULL,                          NULL,             NULL,     NULL);
}
#endif



#ifndef c_strrep_str
void test_strrep_str(void)	{}
#warning "strrep_str() test suite function defined, but the function isn't defined."
#else
void	print_test_strrep_str(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		char const* str_old,
		char const* str_new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_str, str, str_old, str_new)
	TEST_PRINT(str,	strrep_str, "str=\"%s\", old=\"%s\", new=\"%s\"", str, str_old, str_new)
	TEST_FREE()
}
void	test_strrep_str(void)
{
//	| TEST FUNCTION       | TEST NAME                   | TESTFLAGS      | EXPECTING                    | TEST ARGS
	print_test_strrep_str("strrep_str                ", FALSE,           "Hellx Wxrld!",                "Hello World!",                "o",       "x");
	print_test_strrep_str("strrep_str                ", FALSE,           "Omae wa mxx shindeiru.",      test1,                         "ou",      "xx");
	print_test_strrep_str("strrep_str                ", FALSE,           "Nani_",                       test2,                         "???",     "_");
	print_test_strrep_str("strrep_str                ", FALSE,           "Un **** m**** de la f****.",  test3,                         "ange",    "****");
	print_test_strrep_str("strrep_str                ", FALSE,           "___sw___ag___",               "___swag___",                  "ag",      "___ag");
	print_test_strrep_str("strrep_str                ", FALSE,           "test_test_test",              "testatestatest",              "testa",   "test_");
	print_test_strrep_str("strrep_str                ", FALSE,           "ABCABCABC",                   "XYZXYZXYZ",                   "XYZ",     "ABC");
	print_test_strrep_str("strrep_str (expand)       ", FALSE,           "AAA AAA AAA",                 "A A A",                       "A",       "AAA");
	print_test_strrep_str("strrep_str (shrink)       ", FALSE,           "A A A",                       "AAA AAA AAA",                 "AAA",     "A");
	print_test_strrep_str("strrep_str (remove multi) ", FALSE,           "Omae wa m shindeiru.",        test1,                         "ou",      "");
	print_test_strrep_str("strrep_str (identical)    ", FALSE,           "Hello World!",                "Hello World!",                "World",   "World");
	print_test_strrep_str("strrep_str (no match)     ", FALSE,           "Hello World!",                "Hello World!",                "xyz",     "abc");
	print_test_strrep_str("strrep_str (adjacent)     ", FALSE,           "ABABABAB",                    "aaaa",                        "a",       "AB");
	print_test_strrep_str("strrep_str (adjacent)     ", FALSE,           "XXXX",                        "ABABABAB",                    "AB",      "X");
	print_test_strrep_str("strrep_str (overlapping)  ", FALSE,           "AA",                          "AAAA",                        "AA",      "A");
	print_test_strrep_str("strrep_str (full replace) ", FALSE,           "completely different",        "original string",             "original string", "completely different");
	print_test_strrep_str("strrep_str (at start)     ", FALSE,           "___test",                     "test",                        "test",    "___test");
	print_test_strrep_str("strrep_str (at end)       ", FALSE,           "test___",                     "test",                        "test",    "test___");
	print_test_strrep_str("strrep_str (whitespace)   ", FALSE,           "a_b_c",                       "a b c",                       " ",       "_");
	print_test_strrep_str("strrep_str (multi-space)  ", FALSE,           "a_b_c",                       "a   b   c",                   "   ",     "_");
	print_test_strrep_str("strrep_str (unicode)      ", FALSE,           teststr_utf8_fr,               teststr_utf8_fr,               "xyz",     "abc");
	print_test_strrep_str("strrep_str (empty str)    ", FALSE,           "",                            "",                            "old",     "new");
	print_test_strrep_str("strrep_str (empty old)    ", FALSE,           "test",                        "test",                        "",        "new");
	print_test_strrep_str("strrep_str (empty new)    ", FALSE,           "Hell Wrld!",                  "Hello World!",                "o",       "");
	print_test_strrep_str("strrep_str (empty new)    ", FALSE,           "Hell Wrld!",                  "Hello World!",                "o",       "");
	print_test_strrep_str("strrep_str (empty result) ", FALSE,           "",                            "Hello",                       "Hello",   "");
	print_test_strrep_str("strrep_str (empty result) ", FALSE,           "",                            "AAAAAA",                      "AA",      "");
	print_test_strrep_str("strrep_str (both empty)   ", FALSE,           "test",                        "test",                        "",        "");
	print_test_strrep_str("strrep_str (null str)     ", ALLOW_SIGSEGV,   NULL,                          NULL,                          "old",     "new");
	print_test_strrep_str("strrep_str (null old)     ", ALLOW_SIGSEGV,   NULL,                          "test",                        NULL,      "new");
	print_test_strrep_str("strrep_str (null new)     ", ALLOW_SIGSEGV,   NULL,                          "test",                        "old",     NULL);
	print_test_strrep_str("strrep_str (all null)     ", ALLOW_SIGSEGV,   NULL,                          NULL,                          NULL,      NULL);
}
#endif



/*============================================================================*\
||                        Common Whitespace Operations                        ||
\*============================================================================*/

#ifndef c_strtrim
void test_strtrim(void)	{}
#warning "strtrim() test suite function defined, but the function isn't defined."
#else
void	print_test_strtrim(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtrim, str, charset)
	TEST_PRINT(str,	strtrim, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_strtrim(void)
{
//	| TEST FUNCTION   | TEST NAME                 | TESTFLAGS     | EXPECTING              | TEST ARGS
	print_test_strtrim("strtrim                  ", FALSE,			"Xx_Vegeta2000_xX",     "x",           "xXx_Vegeta2000_xXx");
	print_test_strtrim("strtrim                  ", FALSE,			"_Vegeta2000_",         "xX",          "xXx_Vegeta2000_xXx");
	print_test_strtrim("strtrim                  ", FALSE,			"Vegeta2000",           "xX_",         "xXx_Vegeta2000_xXx");
	print_test_strtrim("strtrim                  ", FALSE,			"Vegeta2",              "xX_0",        "xXx_Vegeta2000_xXx");
	print_test_strtrim("strtrim                  ", FALSE,			"Vegeta",               "xX_02",       "xXx_Vegeta2000_xXx");
	print_test_strtrim("strtrim                  ", FALSE,			"swag",                 " \t\n\r\v\f", "   swag\n");
	print_test_strtrim("strtrim                  ", FALSE,			"FOR THE\tHORDE !",     " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim("strtrim                  ", FALSE,			"do u even\ntrim bruh", " \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim("strtrim (only whitespace)", FALSE,			"",                     " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim("strtrim (empty string)   ", FALSE,			"",                     " \t\n\r\v\f", "");
	print_test_strtrim("strtrim (empty charset)  ", FALSE,			"   swag\n",            "",            "   swag\n");
	print_test_strtrim("strtrim (null string)    ", ALLOW_SIGSEGV,	NULL,                   "ab", NULL);
	print_test_strtrim("strtrim (null charset)   ", ALLOW_SIGSEGV,	NULL,                   NULL, " swag \n");
	print_test_strtrim("strtrim (both null)      ", ALLOW_SIGSEGV,	NULL,                   NULL, NULL);
}
#endif


#ifndef c_strtriml
void test_strtriml(void)	{}
#warning "strtriml() test suite function defined, but the function isn't defined."
#else
void	print_test_strtriml(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtriml, str, charset)
	TEST_PRINT(str,	strtriml, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_strtriml(void)
{
//	| TEST FUNCTION     | TEST NAME                   | TESTFLAGS      | EXPECTING                      | TEST ARGS
	print_test_strtriml("strtriml                  ", FALSE,			"Xx_Vegeta2000_xXx",             "x",           "xXx_Vegeta2000_xXx");
	print_test_strtriml("strtriml                  ", FALSE,			"_Vegeta2000_xXx",               "xX",          "xXx_Vegeta2000_xXx");
	print_test_strtriml("strtriml                  ", FALSE,			"Vegeta2000_xXx",                "xX_",         "xXx_Vegeta2000_xXx");
	print_test_strtriml("strtriml                  ", FALSE,			"Vegeta2000_xXx",                "xX_0",        "xXx_Vegeta2000_xXx");
	print_test_strtriml("strtriml                  ", FALSE,			"Vegeta2000_xXx",                "xX_02",       "xXx_Vegeta2000_xXx");
	print_test_strtriml("strtriml                  ", FALSE,			"swag\n",                        " \t\n\r\v\f", "   swag\n");
	print_test_strtriml("strtriml                  ", FALSE,			"FOR THE\tHORDE ! 	 \t \n ",    " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtriml("strtriml                  ", FALSE,			"do u even\ntrim bruh\n\r\n\n\t"," \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtriml("strtriml (only whitespace)", FALSE,			"",                              " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtriml("strtriml (empty string)   ", FALSE,			"",                              " \t\n\r\v\f", "");
	print_test_strtriml("strtriml (empty charset)  ", FALSE,			"   swag\n",                     "",            "   swag\n");
	print_test_strtriml("strtriml (null string)    ", ALLOW_SIGSEGV,	NULL,                            "ab", NULL);
	print_test_strtriml("strtriml (null charset)   ", ALLOW_SIGSEGV,	NULL,                            NULL, " swag \n");
	print_test_strtriml("strtriml (both null)      ", ALLOW_SIGSEGV,	NULL,                            NULL, NULL);
}
#endif


#ifndef c_strtrimr
void test_strtrimr(void)	{}
#warning "strtrimr() test suite function defined, but the function isn't defined."
#else
void	print_test_strtrimr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtrimr, str, charset)
	TEST_PRINT(str,	strtrimr, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_strtrimr(void)
{
//	| TEST FUNCTION     | TEST NAME                   | TESTFLAGS      | EXPECTING                     | TEST ARGS
	print_test_strtrimr("strtrimr                  ", FALSE,			"xXx_Vegeta2000_xX",           "x",           "xXx_Vegeta2000_xXx");
	print_test_strtrimr("strtrimr                  ", FALSE,			"xXx_Vegeta2000_",             "xX",          "xXx_Vegeta2000_xXx");
	print_test_strtrimr("strtrimr                  ", FALSE,			"xXx_Vegeta2000",              "xX_",         "xXx_Vegeta2000_xXx");
	print_test_strtrimr("strtrimr                  ", FALSE,			"xXx_Vegeta2",                 "xX_0",        "xXx_Vegeta2000_xXx");
	print_test_strtrimr("strtrimr                  ", FALSE,			"xXx_Vegeta",                  "xX_02",       "xXx_Vegeta2000_xXx");
	print_test_strtrimr("strtrimr                  ", FALSE,			"   swag",                     " \t\n\r\v\f", "   swag\n");
	print_test_strtrimr("strtrimr                  ", FALSE,			"\t\n   \f FOR THE\tHORDE !",  " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrimr("strtrimr                  ", FALSE,			"do u even\ntrim bruh",        " \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrimr("strtrimr (only in charset)", FALSE,			"",                            " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrimr("strtrimr (empty string)   ", FALSE,			"",                            " \t\n\r\v\f", "");
	print_test_strtrimr("strtrimr (empty charset)  ", FALSE,			"   swag\n",                   "",            "   swag\n");
	print_test_strtrimr("strtrimr (both empty)     ", FALSE,			"",                            "",            "");
	print_test_strtrimr("strtrimr (null string)    ", ALLOW_SIGSEGV,	NULL,                          "ab", NULL);
	print_test_strtrimr("strtrimr (null charset)   ", ALLOW_SIGSEGV,	NULL,                          NULL, "ab");
	print_test_strtrimr("strtrimr (both null)      ", ALLOW_SIGSEGV,	NULL,                          NULL, NULL);
}
#endif


#ifndef c_strpad
void test_strpad(void)	{}
#warning "strpad() test suite function defined, but the function isn't defined."
#else
void	print_test_strpad(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str,
		char c,
		size_t length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpad, str, c, length)
	TEST_PRINT(str,	strpad, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad(void)
{
//	| TEST FUNCTION     | TEST NAME             | TESTFLAGS      | EXPECTING         | TEST ARGS
	print_test_strpad("strpad (n == strlen)    ", FALSE,			"test",           "test", ' ', 4);
	print_test_strpad("strpad                  ", FALSE,			"test ",          "test", ' ', 5);
	print_test_strpad("strpad                  ", FALSE,			" test ",         "test", ' ', 6);
	print_test_strpad("strpad                  ", FALSE,			" test  ",        "test", ' ', 7);
	print_test_strpad("strpad                  ", FALSE,			"  test  ",       "test", ' ', 8);
	print_test_strpad("strpad                  ", FALSE,			"  test   ",      "test", ' ', 9);
	print_test_strpad("strpad                  ", FALSE,			"   test   ",     "test", ' ', 10);
	print_test_strpad("strpad                  ", FALSE,			"12340",          "1234", '0', 5);
	print_test_strpad("strpad                  ", FALSE,			"012340",         "1234", '0', 6);
	print_test_strpad("strpad (n < strlen)     ", FALSE,			"swa",            "swag", ' ', 3);
	print_test_strpad("strpad (n < strlen)     ", FALSE,			"wa",             "swag", ' ', 2);
	print_test_strpad("strpad (n < strlen)     ", FALSE,			"w",              "swag", ' ', 1);
	print_test_strpad("strpad (n == 0)         ", FALSE,			"",               "swag", ' ', 0);
	print_test_strpad("strpad (c == '\\0')     ", FALSE,			"test",           "test",'\0', 5);
	print_test_strpad("strpad (c == '\\0')     ", FALSE,			"",               "test",'\0', 6);
	print_test_strpad("strpad (null string)    ", ALLOW_SIGSEGV,	NULL,              NULL,  ' ', 5);
}
#endif



#ifndef c_strpadl
void test_strpadl(void)	{}
#warning "strpadl() test suite function defined, but the function isn't defined."
#else
void	print_test_strpadl(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str,
		char c,
		size_t length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpadl, str, c, length)
	TEST_PRINT(str,	strpadl, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpadl(void)
{
//	| TEST FUNCTION     | TEST NAME              | TESTFLAGS       | EXPECTING           | TEST ARGS
	print_test_strpadl("strpadl (n == strlen) ", FALSE,			"test",               "test", ' ', 4);
	print_test_strpadl("strpadl               ", FALSE,			" test",              "test", ' ', 5);
	print_test_strpadl("strpadl               ", FALSE,			"  test",             "test", ' ', 6);
	print_test_strpadl("strpadl               ", FALSE,			"   test",            "test", ' ', 7);
	print_test_strpadl("strpadl               ", FALSE,			"    test",           "test", ' ', 8);
	print_test_strpadl("strpadl               ", FALSE,			"     test",          "test", ' ', 9);
	print_test_strpadl("strpadl               ", FALSE,			"      test",         "test", ' ', 10);
	print_test_strpadl("strpadl               ", FALSE,			"01234",              "1234", '0', 5);
	print_test_strpadl("strpadl               ", FALSE,			"001234",             "1234", '0', 6);
	print_test_strpadl("strpadl (n < strlen)  ", FALSE,			"wag",                "swag", ' ', 3);
	print_test_strpadl("strpadl (n < strlen)  ", FALSE,			"ag",                 "swag", ' ', 2);
	print_test_strpadl("strpadl (n < strlen)  ", FALSE,			"g",                  "swag", ' ', 1);
	print_test_strpadl("strpadl (n == 0)      ", FALSE,			"",                   "swag", ' ', 0);
	print_test_strpadl("strpadl (c == '\\0')  ", FALSE,			"test",               "test",'\0', 4);
	print_test_strpadl("strpadl (c == '\\0')  ", FALSE,			"",                   "test",'\0', 5);
	print_test_strpadl("strpadl (null string) ", ALLOW_SIGSEGV,	NULL,                 NULL,  ' ', 5);
}
#endif



#ifndef c_strpadr
void test_strpadr(void)	{}
#warning "strpadr() test suite function defined, but the function isn't defined."
#else
void	print_test_strpadr(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str,
		char c,
		size_t length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpadr, str, c, length)
	TEST_PRINT(str,	strpadr, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpadr(void)
{
//	| TEST FUNCTION     | TEST NAME              | TESTFLAGS      | EXPECTING     | TEST ARGS
	print_test_strpadr("strpadr (n == strlen) ", FALSE,			"test",        "test", ' ', 4);
	print_test_strpadr("strpadr               ", FALSE,			"test ",       "test", ' ', 5);
	print_test_strpadr("strpadr               ", FALSE,			"test  ",      "test", ' ', 6);
	print_test_strpadr("strpadr               ", FALSE,			"test   ",     "test", ' ', 7);
	print_test_strpadr("strpadr               ", FALSE,			"test    ",    "test", ' ', 8);
	print_test_strpadr("strpadr               ", FALSE,			"test     ",   "test", ' ', 9);
	print_test_strpadr("strpadr               ", FALSE,			"test      ",  "test", ' ', 10);
	print_test_strpadr("strpadr               ", FALSE,			"12340",       "1234", '0', 5);
	print_test_strpadr("strpadr               ", FALSE,			"123400",      "1234", '0', 6);
	print_test_strpadr("strpadr (n < strlen)  ", FALSE,			"swa",         "swag", ' ', 3);
	print_test_strpadr("strpadr (n < strlen)  ", FALSE,			"sw",          "swag", ' ', 2);
	print_test_strpadr("strpadr (n < strlen)  ", FALSE,			"s",           "swag", ' ', 1);
	print_test_strpadr("strpadr (n == 0)      ", FALSE,			"",            "swag", ' ', 0);
	print_test_strpadr("strpadr (c == '\\0')  ", FALSE,			"test",        "test",'\0', 4);
	print_test_strpadr("strpadr (c == '\\0')  ", FALSE,			"test",        "test",'\0', 5);
	print_test_strpadr("strpadr (null string) ", ALLOW_SIGSEGV,  NULL,          NULL,  ' ', 5);
}
#endif



/*============================================================================*\
||                          Other String Operations                           ||
\*============================================================================*/

// TODO check on which platforms this function exists, if any
#ifndef c_strrev
void test_strrev(void)	{}
#warning "strrev() test suite function defined, but the function isn't defined."
#else
void	print_test_strrev(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrev, str)
	TEST_PRINT(str,	strrev, "str=\"%s\"", str)
	TEST_FREE()
}
void	test_strrev(void)
{
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      | EXPECTING              | TEST ARGS
	print_test_strrev("strrev (even len) ",	FALSE,			".uriednihs uom aw eamO", test1);
	print_test_strrev("strrev (odd len)  ",	FALSE,			"???inaN",                test2);
	print_test_strrev("strrev (even len) ",	FALSE,			"tset",                   "test");
	print_test_strrev("strrev (len == 3) ",	FALSE,			" ()",                    ")( ");
	print_test_strrev("strrev (len == 3) ",	FALSE,			"abc",                    "cba");
	print_test_strrev("strrev (len == 2) ",	FALSE,			"ab",                     "ba");
	print_test_strrev("strrev (len == 1) ",	FALSE,			"?",                      "?");
	print_test_strrev("strrev (len == 0) ",	FALSE,			"",                       "");
	print_test_strrev("strrev (null ptr) ",	ALLOW_SIGSEGV,	NULL,                     NULL);
}
#endif


#ifndef c_strconcat
void test_strconcat(void)	{}
#warning "strconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_strconcat(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str1,
		char const *str2)
{
	TEST_INIT(str)
	TEST_PERFORM(	strconcat, str1, str2)
	TEST_PRINT(str,	strconcat, "str1=\"%s\", str2=\"%s\"", str1, str2)
	TEST_FREE()
}
void	test_strconcat(void)
{
//	| TEST FUNCTION   | TEST NAME             | TESTFLAGS      | EXPECTING                      | TEST ARGS
	print_test_strconcat("strconcat             ", FALSE,			"Omae wa mou shindeiru.Nani???",  test1,  test2);
	print_test_strconcat("strconcat             ", FALSE,			"test1test2",                    "test1", "test2");
	print_test_strconcat("strconcat             ", FALSE,			"Whoa...",                       "Whoa.", "..");
	print_test_strconcat("strconcat (empty str1)", FALSE,			"sweg",                          "sweg",  "");
	print_test_strconcat("strconcat (empty str2)", FALSE,			"sweg",                          "",      "sweg");
	print_test_strconcat("strconcat (both empty)", FALSE,			"",                              "",      "");
	print_test_strconcat("strconcat (null str1) ", ALLOW_SIGSEGV,	NULL,                            NULL,  test2);
	print_test_strconcat("strconcat (null str2) ", ALLOW_SIGSEGV,	NULL,                            test1, NULL);
	print_test_strconcat("strconcat (both null) ", ALLOW_SIGSEGV,	NULL,                            NULL,  NULL);
}
#endif


#ifndef c_strinsert
void test_strinsert(void)	{}
#warning "strinsert() test suite function defined, but the function isn't defined."
#else
void	print_test_strinsert(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *dest,
		char const *src,
		size_t offset)
{
	TEST_INIT(str)
	TEST_PERFORM(	strinsert, dest, src, offset)
	TEST_PRINT(str,	strinsert, "dest=\"%s\", src=\"%s\", offset=%zu", dest, src, offset)
	TEST_FREE()
}
void	test_strinsert(void)
{
//	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strsub
void test_strsub(void)	{}
#warning "strsub() test suite function defined, but the function isn't defined."
#else
void	print_test_strsub(char const* test_name, t_testflags flags,
		char const* expecting,
		char const *str,
		size_t offset,
		size_t n)
{
	TEST_INIT(str)
	TEST_PERFORM(	strsub, str, offset, n)
	TEST_PRINT(str,	strsub, "str=\"%s\", offset=%zu, n=%zu", str, offset, n)
	TEST_FREE()
}
void	test_strsub(void)
{
//	| TEST FUNCTION  | TEST NAME               | TESTFLAGS        |EXPECTING| TEST ARGS
	print_test_strsub("strsub                 ", FALSE,				"0",      "01234", 0, 1);
	print_test_strsub("strsub                 ", FALSE,				"1",      "01234", 1, 1);
	print_test_strsub("strsub                 ", FALSE,				"2",      "01234", 2, 1);
	print_test_strsub("strsub                 ", FALSE,				"3",      "01234", 3, 1);
	print_test_strsub("strsub                 ", FALSE,				"4",      "01234", 4, 1);
	print_test_strsub("strsub                 ", FALSE,				"01",     "01234", 0, 2);
	print_test_strsub("strsub                 ", FALSE,				"12",     "01234", 1, 2);
	print_test_strsub("strsub                 ", FALSE,				"23",     "01234", 2, 2);
	print_test_strsub("strsub                 ", FALSE,				"34",     "01234", 3, 2);
	print_test_strsub("strsub                 ", FALSE,				"012",    "01234", 0, 3);
	print_test_strsub("strsub                 ", FALSE,				"123",    "01234", 1, 3);
	print_test_strsub("strsub                 ", FALSE,				"234",    "01234", 2, 3);
	print_test_strsub("strsub                 ", FALSE,				"0123",   "01234", 0, 4);
	print_test_strsub("strsub                 ", FALSE,				"1234",   "01234", 1, 4);
	print_test_strsub("strsub                 ", FALSE,				"01234",  "01234", 0, 5);
	print_test_strsub("strsub (len = 0)       ", FALSE,				"",       test1, 5, 0);
	print_test_strsub("strsub (len > str)     ", FALSE,				NULL,     test1, 5, 100);
	print_test_strsub("strsub (offset > str)  ", ALLOW_SIGSEGV,	NULL,     test1, 100, 5);
	print_test_strsub("strsub (offset+len>str)", ALLOW_SIGSEGV,	NULL,     test1, 100, 5);
	print_test_strsub("strsub (null ptr)      ", ALLOW_SIGSEGV,	NULL,     NULL,  5, 5);
}
#endif



void	strtolower(t_char* c)
{
	if (isupper(*c))
		*c = tolower(*c);
}

void	strtolower_1on2(t_char* c, size_t i)
{
	if (i % 2 == 0 && isupper(*c))
		*c = tolower(*c);
}

t_char	strtoupper(t_char c)
{
	if (islower(c))
		 return (toupper(c));
	else return (c);
}

t_char	strtoupper_1on2(t_char c, size_t i)
{
	if (i % 2 == 1 && islower(c))
		 return (toupper(c));
	else return (c);
}



#ifndef c_striter
void test_striter(void)	{}
#warning "striter() test suite function defined, but the function isn't defined."
#else
void	print_test_striter(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		void (*f)(t_char*))
{
	TEST_INIT(str)
	char* result_libccc = str == NULL ? NULL : strdup(str);
	TEST_PERFORM_VOID(result_libccc, striter, result_libccc, f)
	TEST_PRINT(str,					 striter, "str=\"%s\", f=%p", str, (void*)f)
	TEST_FREE()
}
void	test_striter(void)
{
//	| TEST FUNCTION   | TEST NAME            | TESTFLAGS       | EXPECTING              | TEST ARGS
	print_test_striter("striter            ",	FALSE,			"sweg",                  "SWEG",                   &strtolower);
	print_test_striter("striter            ",	FALSE,			" test dude ",           " TesT DuDe ",            &strtolower);
	print_test_striter("striter            ",	FALSE,			"omae wa mou shindeiru.","omAe wA mOu ShINDeIRu.", &strtolower);
	print_test_striter("striter (null str) ",	ALLOW_SIGSEGV,	NULL,                    NULL,                     &strtolower);
	print_test_striter("striter (null func)",	ALLOW_SIGSEGV,	NULL,                    "omAe wA mOu ShINDeIRu.", NULL);
	print_test_striter("striter (both null)",	ALLOW_SIGSEGV,	NULL,                    NULL,                     NULL);
}
#endif


#ifndef c_striiter
void test_striiter(void)	{}
#warning "striiter() test suite function defined, but the function isn't defined."
#else
void	print_test_striiter(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		void (*f)(t_char*, size_t))
{
	TEST_INIT(str)
	char* result_libccc = str == NULL ? NULL : strdup(str);
	TEST_PERFORM_VOID(result_libccc, striiter, result_libccc, f)
	TEST_PRINT(str,					 striiter, "str=\"%s\", f=%p", str, (void*)f)
	TEST_FREE()
}
void	test_striiter(void)
{
//	| TEST FUNCTION    | TEST NAME            | TESTFLAGS      | EXPECTING               | TEST ARGS
	print_test_striiter("striiter            ",	FALSE,			"sWeG",                   "SWEG",                   &strtolower_1on2);
	print_test_striiter("striiter            ",	FALSE,			" Test dude ",            " TesT DuDe ",            &strtolower_1on2);
	print_test_striiter("striiter            ",	FALSE,			"oMaE Wa mOu sHiNdEiRu.", "OMAE WA MOU SHINDEIRU.", &strtolower_1on2);
	print_test_striiter("striiter (null str) ",	ALLOW_SIGSEGV,	NULL,                     NULL,                     &strtolower_1on2);
	print_test_striiter("striiter (null func)",	ALLOW_SIGSEGV,	NULL,                     "OMAE WA MOU SHINDEIRU.", NULL);
	print_test_striiter("striiter (both null)",	ALLOW_SIGSEGV,	NULL,                     NULL,                     NULL);
}
#endif


#ifndef c_strmap
void test_strmap(void)	{}
#warning "strmap() test suite function defined, but the function isn't defined."
#else
void	print_test_strmap(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		t_char (*f)(t_char))
{
	TEST_INIT(str)
	TEST_PERFORM(	strmap, str, f)
	TEST_PRINT(str,	strmap, "str=\"%s\", f=%p", str, (void*)f)
	TEST_FREE()
}
void	test_strmap(void)
{
//	| TEST FUNCTION   | TEST NAME         | TESTFLAGS      | EXPECTING      | TEST ARGS
	print_test_strmap("strmap            ",	FALSE, "OMAE WA MOU SHINDEIRU.", "omae wa mou shindeiru.", &strtoupper);
	print_test_strmap("strmap (null str) ",	ALLOW_SIGSEGV,	NULL,            NULL,                     &strtoupper);
	print_test_strmap("strmap (null func)",	ALLOW_SIGSEGV,	NULL,            "omae wa mou shindeiru.", NULL);
	print_test_strmap("strmap (both null)",	ALLOW_SIGSEGV,	NULL,            NULL,                     NULL);
}
#endif


#ifndef c_strimap
void test_strimap(void)	{}
#warning "strimap() test suite function defined, but the function isn't defined."
#else
void	print_test_strimap(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* str,
		t_char (*f)(t_char, size_t))
{
	TEST_INIT(str)
	TEST_PERFORM(	strimap, str, f)
	TEST_PRINT(str,	strimap, "str=\"%s\", f=%p", str, (void*)f)
	TEST_FREE()
}
void	test_strimap(void)
{
//	| TEST FUNCTION   | TEST NAME             | TESTFLAGS      | EXPECTING      | TEST ARGS
	print_test_strimap("strimap            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.", "omae wa mou shindeiru.", &strtoupper_1on2);
	print_test_strimap("strimap (null str) ",	ALLOW_SIGSEGV,	NULL,            NULL,                     &strtoupper_1on2);
	print_test_strimap("strimap (null func)",	ALLOW_SIGSEGV,	NULL,            "omae wa mou shindeiru.", NULL);
	print_test_strimap("strimap (both null)",	ALLOW_SIGSEGV,	NULL,            NULL,                     NULL);
}
#endif



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_text_string_ascii(void)
{
	print_suite_title("libccc/text/string/ascii");



	test_strnew();
	test_strcnew();
	test_strdup();
	test_strcpy();
	test_strncpy();
	test_strlcpy();
	test_strcat();
	test_strncat();
	test_strlcat();

	test_strlen();
	test_strcmp();
	test_strncmp();

	test_strchr();
	test_strrchr();
	test_strstr();
	test_strnstr();



	print_nonstd();



	test_strset();
	test_strclr();
//	test_strdel();
	test_strconcat();
//	test_strmerge();
//	test_strappend();
//	test_strprepend();
//	test_strjoin();

	test_strequ();
	test_strnequ();
	test_strhas();
	test_strhasonly();
	test_strcount_char();
	test_strcount_str();

	test_strnchr();
	test_strrstr();
	test_strremove();
	test_strrep_char();
	test_strrep_cset();
	test_strrep_str();

	test_strtrim();
	test_strtriml();
	test_strtrimr();
	test_strpad();
	test_strpadl();
	test_strpadr();

	test_strrev();
	test_strinsert();
	test_strsub();
	test_striter();
	test_striiter();
	test_strmap();
	test_strimap();
//	test_strfilter();
//	test_strifilter();
//	test_strreduce();
//	test_strireduce();
//	test_strfold();
//	test_strifold();

	return (0);
}
