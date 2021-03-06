
#include <ctype.h>
#include <string.h>

#include "libccc/string.h"

#include "test.h"



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

#ifndef c_strnew
void test_strnew(void)	{}
#else
static void*	strnew(t_size n) { void* result = malloc(n + sizeof(""));	memset(result, '\0', n);	return (result); }
void	print_test_strnew(char const* test_name, int can_segfault,
		t_size n)
{
	TEST_INIT(alloc)
	test.length = n;
	TEST_PERFORM_LIBC(	strnew, n) // TODO fix
	TEST_PRINT(alloc,	strnew, "n=%zu", n)
	TEST_FREE()
}
void	test_strnew(void)
{
//	| TEST FUNCTION  | TEST NAME            |CAN SEGV|TEST ARGS
	print_test_strnew("strnew              ", FALSE,	12);
	print_test_strnew("strnew (n = 0xFFFF) ", FALSE,	0xFFFF);
	print_test_strnew("strnew (n = 0x10000)", FALSE,	0x10000);
	print_test_strnew("strnew (n = 0)      ", FALSE,	0);
}
#endif



//! TODO strcnew()



#ifndef c_strset
void test_strset(void)	{}
#else
void	print_test_strset(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME           | CAN SEGV      | EXPECT | TEST ARGS
	print_test_strset("strset           ",  FALSE,          "aaaa",   str1, str2, 'a');
	print_test_strset("strset           ",  FALSE,          "____",   str1, str2, '_');
	print_test_strset("strset (c = '\\0')", FALSE,          "\0\0\0", str1, str2, '\0');
	print_test_strset("strset (null ptr)",  SIGNAL_SIGSEGV, NULL,     NULL, NULL, 'a');
}
#endif


#ifndef c_strclr
void test_strclr(void)	{}
#else
#ifndef strclr
#define strclr(dest, c)	memset(dest, c, strlen(c))
#endif
void	print_test_strclr(char const* test_name, int can_segfault,
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
	char str1[32] = "______________________________";
	char str2[32] = "______________________________";
//	| TEST FUNCTION  | TEST NAME         | CAN SEGV      | EXPECT | TEST ARGS
	print_test_strclr("strclr           ", FALSE,			"",    str1 + 20, str2 + 20);
	print_test_strclr("strclr           ", FALSE,			"",    str1 + 10, str2 + 10);
	print_test_strclr("strclr           ", FALSE,			"",    str1, str2);
	print_test_strclr("strclr (null ptr)", SIGNAL_SIGSEGV, NULL,  NULL, NULL);
}
#endif


#ifndef c_strdel
void test_strdel(void)	{}
#else
void	print_test_strdel(char const* test_name, int can_segfault,
		char const* expecting,
		char** dest_libccc,
		char** dest_libc)
{
	TEST_INIT(ptr)
	TEST_PERFORM_VOID(*dest_libccc,	strdel, dest_libccc)
	TEST_PRINT(ptr,					strdel, "str=%p/\"%s\"", dest_libccc, *dest_libccc)
	TEST_FREE()
}
void	test_strdel(void)
{
	char* str1; if (!(str1 = malloc(32))) return ;
	char* str2; if (!(str2 = malloc(32))) return ;
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       |EXPECT| TEST ARGS
	print_test_strdel("strdel           ", FALSE,			NULL,	&str1, &str2);
	print_test_strdel("strdel (null ptr)", SIGNAL_SIGSEGV,	NULL,	NULL,  NULL);
}
#endif


#ifndef c_strdup
void test_strdup(void)	{}
#else
void	print_test_strdup(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       | TEST ARGS
	print_test_strdup("strdup            ", FALSE,			test1, test1);
	print_test_strdup("strdup            ", FALSE,			test2, test2);
	print_test_strdup("strdup            ", FALSE,			test3, test3);
	print_test_strdup("strdup            ", FALSE,			"_",   "_");
	print_test_strdup("strdup (empty str)", FALSE,			"",    "");
	print_test_strdup("strdup (null str) ", SIGNAL_SIGSEGV,	NULL,  NULL);
}
#endif



#ifndef c_strcpy
void test_strcpy(void)	{}
#else
void	print_test_strcpy(char const* test_name, int can_segfault,
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
	print_test_str(&test, NULL);
}
void	test_strcpy(void)
{
	char str1[64] = { '_' };
	char str2[64] = { '_' };
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       | TEST ARGS
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test1);
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test2);
	print_test_strcpy("strcpy            ",	FALSE,			str1, str2, test3);
	print_test_strcpy("strcpy (empty str)",	FALSE,			str1, str2, "");
	print_test_strcpy("strcpy (null dest)",	SIGNAL_SIGSEGV, NULL, NULL, test2);
	print_test_strcpy("strcpy (null src) ",	SIGNAL_SIGSEGV, str1, str2, NULL);
	print_test_strcpy("strcpy (both null)",	SIGNAL_SIGSEGV, NULL, NULL, NULL);
	// TODO add overlapping memory test
}
#endif



#ifndef c_strncpy
void test_strncpy(void)	{}
#else
void	print_test_strncpy(char const* test_name, int can_segfault,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strncpy, src, n)
	TEST_PRINT(str,			strncpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	test.function = "strncpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL);
}
void	test_strncpy(void)
{
	char str1[32];
	char str2[32];
//	| TEST FUNCTION   | TEST NAME               | CAN SEGV         | TEST ARGS
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test1,     test1_len);
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test2,     test2_len);
	print_test_strncpy("strncpy                ", FALSE,			str1, str2, test3,     test3_len);
	print_test_strncpy("strncpy (n = 0)        ", FALSE,			str1, str2, test1,             0);
	print_test_strncpy("strncpy (n < src_len)  ", FALSE,			str1, str2, test1, test1_len - 5);
	print_test_strncpy("strncpy (n > src_len)  ", FALSE,			str1, str2, test2, test2_len + 5);
	print_test_strncpy("strncpy (several '\\0's)",FALSE,			str1, str2, "Swag\0\0\0",      7);
	print_test_strncpy("strncpy (null dest)    ", SIGNAL_SIGSEGV,	NULL, NULL, test1,             5);
	print_test_strncpy("strncpy (null src)     ", SIGNAL_SIGSEGV,	str1, str2, NULL,              5);
	print_test_strncpy("strncpy (both null)    ", SIGNAL_SIGSEGV,	NULL, NULL, NULL,              5);
	// TODO add overlapping memory test
}
#endif



#ifndef c_strlcpy
void test_strlcpy(void)	{}
#else
void	print_test_strlcpy(char const* test_name, int can_segfault,
		t_size expecting,
		char const* expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size size)
{
	TEST_INIT(size)
#ifdef __APPLE__
	TEST_PERFORM_LIBC_DEST(	strlcpy, src, size)
#else
	TEST_PERFORM_DEST(		strlcpy, src, size)
#endif
	TEST_PRINT(size,		strlcpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcpy 'dest' arg",
		.can_sig = can_segfault,
		.result = dest_libccc,
#ifdef __APPLE__
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.result_sig = test.result_sig,
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL);
}
void	test_strlcpy(void)
{
	char str1[32] = "______________________________";
	char str2[32] = "______________________________";
//	| TEST FUNCTION   | TEST NAME              | CAN SEGV      | EXPECTING         | TEST ARGS
	print_test_strlcpy("strlcpy               ", FALSE,			test1_len-1, test1, str1, str2, test1, test1_len);
	print_test_strlcpy("strlcpy               ", FALSE,			test2_len-1, test2, str1, str2, test2, test2_len);
	print_test_strlcpy("strlcpy               ", FALSE,			test3_len-1, test3, str1, str2, test3, test3_len);
	print_test_strlcpy("strlcpy               ", FALSE,			10, " shi",         str1, str2, " shindeiru", 5);
	print_test_strlcpy("strlcpy               ", FALSE,			10, "testite",      str1, str2, "testitesty", 8);
	print_test_strlcpy("strlcpy (chars > 0x7F)", FALSE,			2,  "\x12",         str1, str2, "\x12\xAB\0", 2);
	print_test_strlcpy("strlcpy (n = 0)       ", FALSE,			10, "\x12",         str1, str2, " shindeiru", 0);
	print_test_strlcpy("strlcpy (n > src_len) ", FALSE,			10, " shindeiru",   str1, str2, " shindeiru", 15);
	print_test_strlcpy("strlcpy (n > dest_len)", FALSE,			10, "shindeiru ",   str1, str2, "shindeiru ", 50);
	print_test_strlcpy("strlcpy (null dest)   ", SIGNAL_SIGSEGV,	0,  NULL,           NULL, NULL, " shindeiru", 5);
	print_test_strlcpy("strlcpy (null src)    ", SIGNAL_SIGSEGV,	0,  "shindeiru ",   str1, str2, NULL,         5);
	print_test_strlcpy("strlcpy (both null)   ", SIGNAL_SIGSEGV,	0,  NULL,           NULL, NULL, NULL,         5);
	// TODO add overlapping memory test
}
#endif



#ifndef c_strcat
void test_strcat(void)	{}
#else
void	print_test_strcat(char const* test_name, int can_segfault,
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
	print_test_str(&test, NULL);
}
void	test_strcat(void)
{
	char str1[128];
	char str2[128];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION  | TEST NAME           | CAN SEGV      | TEST ARGS
	print_test_strcat("strcat            ", FALSE,			str1, str2, "Bob");
	print_test_strcat("strcat            ", FALSE,			str1, str2, test1);
	print_test_strcat("strcat            ", FALSE,			str1, str2, test2);
	print_test_strcat("strcat            ", FALSE,			str1, str2, test3);
	print_test_strcat("strcat (null dest)", SIGNAL_SIGSEGV,	NULL, NULL, "Bob\0");
	print_test_strcat("strcat (null src) ", SIGNAL_SIGSEGV,	str1, str2, NULL);
	print_test_strcat("strcat (both null)", SIGNAL_SIGSEGV,	NULL, NULL, NULL);
	// TODO add overlapping memory test
}
#endif



#ifndef c_strncat
void test_strncat(void)	{}
#else
void	print_test_strncat(char const* test_name, int can_segfault,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_INIT(str)
	TEST_PERFORM_LIBC_DEST(	strncat, src, n)
	TEST_PRINT(str,			strncat, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	test.function = "strncat 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_str(&test, NULL);
}
void	test_strncat(void)
{
	char str1[128];
	char str2[128];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME            | CAN SEGV        | TEST ARGS
	print_test_strncat("strncat            ", FALSE,			str1, str2, "Bob",      3);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test1,      test1_len);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test2,      test2_len);
	print_test_strncat("strncat            ", FALSE,			str1, str2, test3,      test3_len);
	print_test_strncat("strncat (n = 0)    ", FALSE,			str1, str2, "Bobensen", 0);
	print_test_strncat("strncat (n < len)  ", FALSE,			str1, str2, "Bobensen", 3);
	print_test_strncat("strncat (n > len)  ", FALSE,			str1, str2, "Bob\0",    7);
	print_test_strncat("strncat (null dest)", SIGNAL_SIGSEGV,	NULL, NULL, "Bob\0",    5);
	print_test_strncat("strncat (null src) ", SIGNAL_SIGSEGV,	str1, str2, NULL,       5);
	print_test_strncat("strncat (both null)", SIGNAL_SIGSEGV,	NULL, NULL, NULL,       5);
	// TODO add overlapping memory test
}
#endif



#ifndef c_strlcat
void test_strlcat(void)	{}
#else
void	print_test_strlcat(char const* test_name, int can_segfault,
		t_size expecting,
		char const * expecting_dest,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size size)
{
	TEST_INIT(size)
#ifdef __APPLE__
	TEST_PERFORM_LIBC_DEST(	strlcat, src, size)
#else
	TEST_PERFORM_DEST(		strlcat, src, size)
#endif
	TEST_PRINT(size,		strlcat, "dest=\"%s\", src=\"%s\", size=%lu", dest_libccc, src, size)
	s_test_str test2 = (s_test_str)
	{
		.name = test_name,
		.function = "strlcat 'dest' arg",
		.can_sig = can_segfault,
		.result = dest_libccc,
#ifdef __APPLE__
		.expect = dest_libc,
#else
		.expect = expecting_dest,
#endif
		.result_sig = test.result_sig,
		.expect_sig = test.expect_sig,
		.timer = test.timer,
	};
	print_test_str(&test2, NULL);
}
void	test_strlcat(void)
{
	char str1[64] = "______________________________";
	char str2[64] = "______________________________";
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME            | CAN SEGV        | EXPECTING                         | TEST ARGS
	print_test_strlcat("strlcat            ", FALSE,			15, "Sponge",                       str1, str2, " shindeiru", 5);
	print_test_strlcat("strlcat            ", FALSE,			28, "SpongeOmae wa mou shin",       str1, str2, test1,        test1_len);
	print_test_strlcat("strlcat            ", FALSE,			15, "SpongeOmae wa mou shin",       str1, str2, test2,        test2_len);
	print_test_strlcat("strlcat            ", FALSE,			48, "SpongeOmae wa mou shinUn a",   str1, str2, test3,        test3_len);
	print_test_strlcat("strlcat (n = 0)    ", FALSE,			10, "SpongeOmae wa mou shinUn a",   str1, str2, " shindeiru", 0);
	print_test_strlcat("strlcat (n < len)  ", FALSE,			25, "SpongeOmae wa mou shinUn a",   str1, str2, " shindeiru", 15);
	print_test_strlcat("strlcat (n > len)  ", FALSE,			28, "SpongeOmae wa mou shinUn a a", str1, str2, " a",         50);
	print_test_strlcat("strlcat (null dest)", SIGNAL_SIGSEGV,	0,  NULL,                           NULL, NULL, " a",         5);
	print_test_strlcat("strlcat (null src) ", SIGNAL_SIGSEGV,	0,  "SpongeOmae wa mou shinUn a a", str1, str2, NULL,         5);
	print_test_strlcat("strlcat (both null)", SIGNAL_SIGSEGV,	0,  NULL,                           NULL, NULL, NULL,         5);
	// TODO add overlapping memory test
}
#endif



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

#ifndef c_strlen
void test_strlen(void)	{}
#else
void	print_test_strlen(char const* test_name, int can_segfault,
		char const* str)
{
	TEST_INIT(size)
	TEST_PERFORM_LIBC(	strlen, str)
	TEST_PRINT(size,strlen, "str=\"%s\"", str)
}
void	test_strlen(void)
{
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV      | TEST ARGS
	print_test_strlen("strlen            ", FALSE,			test1);
	print_test_strlen("strlen            ", FALSE,			test2);
	print_test_strlen("strlen            ", FALSE,			test3);
	print_test_strlen("strlen            ", FALSE,			"a");
	print_test_strlen("strlen (empty str)", FALSE,			"");
	print_test_strlen("strlen (null str) ", SIGNAL_SIGSEGV,	NULL);
}
#endif


#ifndef c_strcmp
void test_strcmp(void)	{}
#else
void	print_test_strcmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	strcmp, str1, str2)
	TEST_PRINT(sign,	strcmp, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strcmp(void)
{
//	| TEST FUNCTION  | TEST NAME           | CAN SEGV      | TEST ARGS
	print_test_strcmp("strcmp            ", FALSE,			test1, test1);
	print_test_strcmp("strcmp            ", FALSE,			test1, test2);
	print_test_strcmp("strcmp            ", FALSE,			test1, test3);
	print_test_strcmp("strcmp            ", FALSE,			test2, test1);
	print_test_strcmp("strcmp            ", FALSE,			test2, test2);
	print_test_strcmp("strcmp            ", FALSE,			test2, test3);
	print_test_strcmp("strcmp            ", FALSE,			test3, test1);
	print_test_strcmp("strcmp            ", FALSE,			test3, test2);
	print_test_strcmp("strcmp            ", FALSE,			test3, test3);
	print_test_strcmp("strcmp (null str1)", SIGNAL_SIGSEGV,	NULL,  test3);
	print_test_strcmp("strcmp (null str2)", SIGNAL_SIGSEGV,	test2, NULL);
	print_test_strcmp("strcmp (both null)", SIGNAL_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strncmp
void test_strncmp(void)	{}
#else
void	print_test_strncmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2,
		t_size n)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	strncmp, str1, str2, n)
	TEST_PRINT(sign,	strncmp, "str1=\"%s\", str2=\"%s\", n=%zu", str1, str2, n)
}
void	test_strncmp(void)
{
//	| TEST FUNCTION  | TEST NAME             | CAN SEGV       | TEST ARGS
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
	print_test_strncmp("strncmp (null str1)", SIGNAL_SIGSEGV,	NULL,      test3,     5);
	print_test_strncmp("strncmp (null str2)", SIGNAL_SIGSEGV,	test2,     NULL,      5);
	print_test_strncmp("strncmp (both null)", SIGNAL_SIGSEGV,	NULL,      NULL,      5);
}
#endif


#ifndef c_strequ
void test_strequ(void)	{}
#else
#ifndef strequ
#define strequ(str1, str2)	(strcmp(str1, str2) == 0)
#endif
void	print_test_strequ(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2)
{
	TEST_INIT(bool)
	TEST_PERFORM_LIBC(	strequ, str1, str2)
	TEST_PRINT(bool,	strequ, "str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strequ(void)
{
//	| TEST FUNCTION  | TEST NAME           | CAN SEGV      | TEST ARGS
	print_test_strequ("strequ            ", FALSE,			test1, test1);
	print_test_strequ("strequ            ", FALSE,			test1, test2);
	print_test_strequ("strequ            ", FALSE,			test1, test3);
	print_test_strequ("strequ            ", FALSE,			test2, test1);
	print_test_strequ("strequ            ", FALSE,			test2, test2);
	print_test_strequ("strequ            ", FALSE,			test2, test3);
	print_test_strequ("strequ            ", FALSE,			test3, test1);
	print_test_strequ("strequ            ", FALSE,			test3, test2);
	print_test_strequ("strequ            ", FALSE,			test3, test3);
	print_test_strequ("strequ (empty str)", FALSE,			test1, "");
	print_test_strequ("strequ (null str1)", SIGNAL_SIGSEGV,	NULL,  test2);
	print_test_strequ("strequ (null str2)", SIGNAL_SIGSEGV,	test1, NULL);
	print_test_strequ("strequ (both null)", SIGNAL_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strnequ
void test_strnequ(void)	{}
#else
#ifndef strnequ
#define strnequ(str1, str2, n)	(strncmp(str1, str2, n) == 0)
#endif
void	print_test_strnequ(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2,
		t_size n)
{
	TEST_INIT(bool)
	TEST_PERFORM_LIBC(	strnequ, str1, str2, n)
	TEST_PRINT(bool,	strnequ, "str1=\"%s\", str2=\"%s\", n=%zu", str1, str2, n)
}
void	test_strnequ(void)
{
//	| TEST FUNCTION  | TEST NAME              | CAN SEGV       | TEST ARGS
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
	print_test_strnequ("strnequ (null str1)",	SIGNAL_SIGSEGV,	NULL,  test2, 7);
	print_test_strnequ("strnequ (null str2)",	SIGNAL_SIGSEGV,	test1, NULL,  7);
	print_test_strnequ("strnequ (both null)",	SIGNAL_SIGSEGV,	NULL,  NULL,  7);
}
#endif


#ifndef c_strhas
void test_strhas(void)	{}
#else
void	print_test_strhas(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME              | CAN SEGV       |EXPECT| TEST ARGS
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test1, "_0i");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test2, "na");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   test3, "in");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   "sweg my nigga", "mz");
	print_test_strhas("strhas               ",	FALSE,			TRUE,   "sweg my nigga", "aze");
	print_test_strhas("strhas               ",	FALSE,			FALSE,  "sweg my nigga", "z_u");
	print_test_strhas("strhas (null str)    ",	SIGNAL_SIGSEGV,	FALSE,  NULL, "mz");
	print_test_strhas("strhas (null charset)",	SIGNAL_SIGSEGV,	FALSE,  "sw", NULL);
	print_test_strhas("strhas (both null)   ",	SIGNAL_SIGSEGV,	FALSE,  NULL, NULL);
}
#endif


#ifndef c_strhasonly
void test_strhasonly(void)	{}
#else
void	print_test_strhasonly(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION      | TEST NAME                   | CAN SEGV      |EXPECT| TEST ARGS
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test1, "m");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test2, "na");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  test3, "in");
	print_test_strhasonly("strhasonly                ",	FALSE,			TRUE,   "sweg my nigga", "aiey gmnsw");
	print_test_strhasonly("strhasonly                ",	FALSE,			FALSE,  "sweg my nigga", "aiey gsw");
	print_test_strhasonly("strhasonly (empty str)    ",	FALSE,			TRUE,   "",     "z_u");
	print_test_strhasonly("strhasonly (empty charset)",	FALSE,			FALSE,  "sweg", "");
	print_test_strhasonly("strhasonly (null str)     ",	SIGNAL_SIGSEGV,	FALSE,  NULL, "mz");
	print_test_strhasonly("strhasonly (null charset) ",	SIGNAL_SIGSEGV,	FALSE,  "sw", NULL);
	print_test_strhasonly("strhasonly (both null)    ",	SIGNAL_SIGSEGV,	FALSE,  NULL, NULL);
}
#endif


#ifndef c_strcount_char
void test_strcount_char(void)	{}
#else
void	print_test_strcount_char(char const* test_name, int can_segfault,
		t_size expecting,
		char const* str,
		char c)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strcount_char, str, c)
	TEST_PRINT(bool,strcount_char, "str=\"%s\", c='%c'/0x%X", str, c, c)
}
void	test_strcount_char(void)
{
//	| TEST FUNCTION         | TEST NAME                  | CAN SEGV     |EXPECT| TEST ARGS
	print_test_strcount_char("strcount_char            ",	FALSE,			2,    test1,           'm');
	print_test_strcount_char("strcount_char            ",	FALSE,			3,    test2,           '?');
	print_test_strcount_char("strcount_char            ",	FALSE,			1,    test3,           '.');
	print_test_strcount_char("strcount_char            ",	FALSE,			0,    test3,           '_');
	print_test_strcount_char("strcount_char            ",	FALSE,			3,    "sweg my nigga", 'g');
	print_test_strcount_char("strcount_char            ",	FALSE,			0,    "sweg my nigga", 'z');
	print_test_strcount_char("strcount_char (empty str)",	FALSE,			0,    "",              'a');
	print_test_strcount_char("strcount_char ('\\0 char')",	FALSE,			0,    "sweg",          '\0');
	print_test_strcount_char("strcount_char (null str) ",SIGNAL_SIGSEGV,	0,    NULL,            'a');
}
#endif


#ifndef c_strcount_str
void test_strcount_str(void)	{}
#else
void	print_test_strcount_str(char const* test_name, int can_segfault,
		t_size expecting,
		char const* str,
		char const* query)
{
	TEST_INIT(bool)
	TEST_PERFORM(	strcount_str, str, query)
	TEST_PRINT(bool,strcount_str, "str=\"%s\", query=\"%s\"", str, query)
}
void	test_strcount_str(void)
{
//	| TEST FUNCTION        | TEST NAME                   | CAN SEGV      |EXPECT| TEST ARGS
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    test1, " m");
	print_test_strcount_str("strcount_str              ",	FALSE,			2,    test2, "?");
	print_test_strcount_str("strcount_str              ",	FALSE,			3,    test3, "ange");
	print_test_strcount_str("strcount_str              ",	FALSE,			0,    test3, "_");
	print_test_strcount_str("strcount_str              ",	FALSE,			3,    "sweg my nigga", "g");
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    "sweg my nigga", "sweg");
	print_test_strcount_str("strcount_str              ",	FALSE,			0,    "sweg my nigga", "swef");
	print_test_strcount_str("strcount_str              ",	FALSE,			1,    "sweg my nigga", "gg");
	print_test_strcount_str("strcount_str (empty str)  ",	FALSE,			0,    "",              "g");
	print_test_strcount_str("strcount_str (empty query)",	FALSE,			0,    test1, "");
	print_test_strcount_str("strcount_str (null str)   ", SIGNAL_SIGSEGV,   0,    NULL, "mz");
	print_test_strcount_str("strcount_str (null query) ", SIGNAL_SIGSEGV,   0,    "sw", NULL);
	print_test_strcount_str("strcount_str (both null)  ", SIGNAL_SIGSEGV,   0,    NULL, NULL);
}
#endif


/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

#ifndef c_strchr
void test_strchr(void)	{}
#else
void	print_test_strchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	strchr, str, c)
	TEST_PRINT(ptr,		strchr, "str=%p/\"%s\", c='%c'/0x%X", str, str, c, c)
}
void	test_strchr(void)
{
//	| TEST FUNCTION  | TEST NAME             | CAN SEGV      | TEST ARGS
	print_test_strchr("strchr             ",	FALSE,			test1, 'm');
	print_test_strchr("strchr             ",	FALSE,			test2, '?');
	print_test_strchr("strchr             ",	FALSE,			test3, ' ');
	print_test_strchr("strchr             ",	FALSE,			test1, '_');
	print_test_strchr("strchr             ",	FALSE,			test2, '_');
	print_test_strchr("strchr             ",	FALSE,			test3, '_');
	print_test_strchr("strchr (c = '\\0')  ",	FALSE,			test3, '\0');
	print_test_strchr("strchr (null ptr)  ", SIGNAL_SIGSEGV,	NULL,  'm');
}
#endif


#ifndef c_strstr
void test_strstr(void)	{}
#else
void	print_test_strstr(char const* test_name, int can_segfault,
		char const* str,
		char const* query)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	strstr, str, query)
	TEST_PRINT(ptr,		strstr, "str=%p/\"%s\", query=\"%s\"", str, str, query)
}
void	test_strstr(void)
{
//	| TEST FUNCTION  | TEST NAME             | CAN SEGV      | TEST ARGS
	print_test_strstr("strstr              ",	FALSE,			test1, " m");
	print_test_strstr("strstr              ",	FALSE,			test2, "?");
	print_test_strstr("strstr              ",	FALSE,			test3, " ");
	print_test_strstr("strstr              ",	FALSE,			test1, "mou ");
	print_test_strstr("strstr              ",	FALSE,			test1, "??");
	print_test_strstr("strstr              ",	FALSE,			test3, "???");
//	print_test_strstr("strstr (empty query)",	FALSE,			test3, ""); // TODO The test here fails because there is an intentional design difference
	print_test_strstr("strstr (null str)   ",SIGNAL_SIGSEGV,	NULL,  "mou ");
	print_test_strstr("strstr (null query) ",SIGNAL_SIGSEGV,	test1, NULL);
	print_test_strstr("strstr (both null)  ",SIGNAL_SIGSEGV,	NULL,  NULL);
}
#endif


#ifndef c_strrchr
void test_strrchr(void)	{}
#else
void	print_test_strrchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	strrchr, str, c)
	TEST_PRINT(ptr,		strrchr, "str=%p/\"%s\", c='%c'/0x%X", str, str, c, c)
}
void	test_strrchr(void)
{
//	| TEST FUNCTION  | TEST NAME               | CAN SEGV      | TEST ARGS
	print_test_strrchr("strrchr             ",	FALSE,			test1, 'm');
	print_test_strrchr("strrchr             ",	FALSE,			test2, '?');
	print_test_strrchr("strrchr             ",	FALSE,			test3, ' ');
	print_test_strrchr("strrchr             ",	FALSE,			test1, '_');
	print_test_strrchr("strrchr             ",	FALSE,			test2, '_');
	print_test_strrchr("strrchr             ",	FALSE,			test3, '_');
	print_test_strrchr("strrchr (c = '\\0')  ",	FALSE,			test3, '\0');
	print_test_strrchr("strrchr (null ptr)  ",	SIGNAL_SIGSEGV, NULL,  'm');
}
#endif


#ifndef c_strrstr
void test_strrstr(void)	{}
#else
void	print_test_strrstr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	strrstr, str, query)
	TEST_PRINT(ptr,	strrstr, "str=%p/\"%s\", query=\"%s\"", str, str, query)
}
void	test_strrstr(void)
{
//	| TEST FUNCTION  | TEST NAME              | CAN SEGV       | EXPECTING   | TEST ARGS
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 8,    test1, "mou ");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 0,    test1, "Omae ");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 20,   test1, "u.");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test1, "u. ");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test1, " u.");
	print_test_strrstr("strrstr              ",	FALSE,			test1 + 21,   test1, ".");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test1, ". ");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test1, " .");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test1, "??");
	print_test_strrstr("strrstr              ",	FALSE,			NULL,         test3, "???");
	print_test_strrstr("strrstr (empty query)",	FALSE,			NULL,         test3, "");
	print_test_strrstr("strrstr (null str)   ",	SIGNAL_SIGSEGV,	NULL,         NULL,  "mou ");
	print_test_strrstr("strrstr (null query) ",	SIGNAL_SIGSEGV,	NULL,         test1, NULL);
	print_test_strrstr("strrstr (both null)  ",	SIGNAL_SIGSEGV,	NULL,         NULL,  NULL);
}
#endif


#ifndef c_strnchr
void test_strnchr(void)	{}
#else
void	print_test_strnchr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char c,
		t_size n)
{
	TEST_INIT(ptr)
	TEST_PERFORM(	strnchr, str, c, n)
	TEST_PRINT(ptr,	strnchr, "str=%p/\"%s\", c='%c'/0x%X, n=%zu", str, str, c, c, n)
}
void	test_strnchr(void)
{
//	| TEST FUNCTION  | TEST NAME               | CAN SEGV      |  EXPECTING  | TEST ARGS
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
	print_test_strnchr("strnchr (c = '\\0')  ",	FALSE,			NULL,          test3, '\0', 16);
	print_test_strnchr("strnchr (n = 0)     ",	FALSE,			NULL,          test1, 'w', 0);
	print_test_strnchr("strnchr (n = len)   ",	FALSE,			NULL,          test1, '_', test1_len);
	print_test_strnchr("strnchr (n > len)   ",	FALSE,			NULL,          test1, '_', test1_len + 32);
	print_test_strnchr("strnchr (null ptr)  ",	SIGNAL_SIGSEGV, NULL,          NULL,  'm', 16);
}
#endif


#ifndef c_strnstr
void test_strnstr(void)	{}
#else
void	print_test_strnstr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query,
		t_size n)
{
	TEST_INIT(ptr)
// TODO inspect which platforms have this function
#ifdef __APPLE__
	TEST_PERFORM_LIBC(	strnstr, str, query, n)
#else
	TEST_PERFORM(	strnstr, str, query, n)
#endif
	TEST_PRINT(ptr,	strnstr, "str=%p/\"%s\", query=\"%s\", n=%zu", str, str, query, n)
}
void	test_strnstr(void)
{
//	| TEST FUNCTION  | TEST NAME              | CAN SEGV       | EXPECTING | TEST ARGS
	print_test_strnstr("strnstr              ",	FALSE,			test1 + 8,  test1, "mou ", 16);
	print_test_strnstr("strnstr              ",	FALSE,			NULL,       test1, "??",   test1_len);
	print_test_strnstr("strnstr              ",	FALSE,			test2 + 4,  test2, "??",   test2_len);
	print_test_strnstr("strnstr              ",	FALSE,			NULL,       test3, "???",  test3_len);
	print_test_strnstr("strnstr (empty query)",	FALSE,			test1,      test1, "\0",   16);
	print_test_strnstr("strnstr (n = 0)      ",	FALSE,			NULL,       test1, "mou ", 0);
	print_test_strnstr("strnstr (n = len)    ",	FALSE,			NULL,       test1, "_",    test1_len);
	print_test_strnstr("strnstr (n > len)    ",	FALSE,			NULL,       test1, "_",    test1_len + 32);
	print_test_strnstr("strnstr (null str)   ",	SIGNAL_SIGSEGV,	NULL,       NULL,  "mou ", 16);
	print_test_strnstr("strnstr (null query) ",	SIGNAL_SIGSEGV,	NULL,       test1, NULL,   16);
	print_test_strnstr("strnstr (both null)  ",	SIGNAL_SIGSEGV,	NULL,       NULL,  NULL,   16);
}
#endif


#ifndef c_strremove
void test_strremove(void)	{}
#else
void	print_test_strremove(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strtoesc
void test_strtoesc(void)	{}
#else
void	print_test_strtoesc(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* charset_extra)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtoesc, str, charset_extra)
	TEST_PRINT(str,	strtoesc, "str=\"%s\", charset_extra=\"%s\"", str, charset_extra)
	TEST_FREE()
}
void	test_strtoesc(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_esctostr
void test_esctostr(void)	{}
#else
void	print_test_esctostr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		t_bool escape_any)
{
	TEST_INIT(str)
	TEST_PERFORM(	esctostr, str, escape_any)
	TEST_PRINT(str,	esctostr, "str=\"%s\", escape_any=%s", str, (escape_any ? "TRUE" : "FALSE"))
	TEST_FREE()
}
void	test_esctostr(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strrep_char
void test_strrep_char(void)	{}
#else
void	print_test_strrep_char(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char old,
		char new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_char, str, old, new)
	TEST_PRINT(str,	strrep_char, "str=\"%s\", old='%c'/0x%X, new='%c'/0x%X", str, old, old, new, new)
	TEST_FREE()
}
void	test_strrep_char(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strrep_charset
void test_strrep_charset(void)	{}
#else
void	print_test_strrep_charset(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* old,
		char const* new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_charset, str, old, new)
	TEST_PRINT(str,	strrep_charset, "str=\"%s\", old=\"%s\", new=\"%s\"", str, old, new)
	TEST_FREE()
}
void	test_strrep_charset(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strrep_str
void test_strrep_str(void)	{}
#else
void	print_test_strrep_str(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* old,
		char const* new)
{
	TEST_INIT(str)
	TEST_PERFORM(	strrep_str, str, old, new)
	TEST_PRINT(str,	strrep_str, "str=\"%s\", old=\"%s\", new=\"%s\"", str, old, new)
	TEST_FREE()
}
void	test_strrep_string(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

#ifndef c_strtrim
void test_strtrim(void)	{}
#else
void	print_test_strtrim(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION   | TEST NAME                 | CAN SEGV      | EXPECTING              | TEST ARGS
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
	print_test_strtrim("strtrim (null string)    ", SIGNAL_SIGSEGV,	NULL,                   "ab", NULL);
	print_test_strtrim("strtrim (null charset)   ", SIGNAL_SIGSEGV,	NULL,                   NULL, " swag \n");
	print_test_strtrim("strtrim (both null)      ", SIGNAL_SIGSEGV,	NULL,                   NULL, NULL);
}
#endif


#ifndef c_strtrim_l
void test_strtrim_l(void)	{}
#else
void	print_test_strtrim_l(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtrim_l, str, charset)
	TEST_PRINT(str,	strtrim_l, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_strtrim_l(void)
{
//	| TEST FUNCTION     | TEST NAME                   | CAN SEGV       | EXPECTING                      | TEST ARGS
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"Xx_Vegeta2000_xXx",             "x",           "xXx_Vegeta2000_xXx");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"_Vegeta2000_xXx",               "xX",          "xXx_Vegeta2000_xXx");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"Vegeta2000_xXx",                "xX_",         "xXx_Vegeta2000_xXx");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"Vegeta2000_xXx",                "xX_0",        "xXx_Vegeta2000_xXx");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"Vegeta2000_xXx",                "xX_02",       "xXx_Vegeta2000_xXx");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"swag\n",                        " \t\n\r\v\f", "   swag\n");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"FOR THE\tHORDE ! 	 \t \n ",    " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim_l("strtrim_l                  ", FALSE,			"do u even\ntrim bruh\n\r\n\n\t"," \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim_l("strtrim_l (only whitespace)", FALSE,			"",                              " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim_l("strtrim_l (empty string)   ", FALSE,			"",                              " \t\n\r\v\f", "");
	print_test_strtrim_l("strtrim_l (empty charset)  ", FALSE,			"   swag\n",                     "",            "   swag\n");
	print_test_strtrim_l("strtrim_l (null string)    ", SIGNAL_SIGSEGV,	NULL,                            "ab", NULL);
	print_test_strtrim_l("strtrim_l (null charset)   ", SIGNAL_SIGSEGV,	NULL,                            NULL, " swag \n");
	print_test_strtrim_l("strtrim_l (both null)      ", SIGNAL_SIGSEGV,	NULL,                            NULL, NULL);
}
#endif


#ifndef c_strtrim_r
void test_strtrim_r(void)	{}
#else
void	print_test_strtrim_r(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_INIT(str)
	TEST_PERFORM(	strtrim_r, str, charset)
	TEST_PRINT(str,	strtrim_r, "str=\"%s\", charset=\"%s\"", str, charset)
	TEST_FREE()
}
void	test_strtrim_r(void)
{
//	| TEST FUNCTION     | TEST NAME                   | CAN SEGV       | EXPECTING                     | TEST ARGS
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"xXx_Vegeta2000_xX",           "x",           "xXx_Vegeta2000_xXx");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"xXx_Vegeta2000_",             "xX",          "xXx_Vegeta2000_xXx");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"xXx_Vegeta2000",              "xX_",         "xXx_Vegeta2000_xXx");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"xXx_Vegeta2",                 "xX_0",        "xXx_Vegeta2000_xXx");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"xXx_Vegeta",                  "xX_02",       "xXx_Vegeta2000_xXx");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"   swag",                     " \t\n\r\v\f", "   swag\n");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"\t\n   \f FOR THE\tHORDE !",  " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim_r("strtrim_r                  ", FALSE,			"do u even\ntrim bruh",        " \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim_r("strtrim_r (only in charset)", FALSE,			"",                            " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim_r("strtrim_r (empty string)   ", FALSE,			"",                            " \t\n\r\v\f", "");
	print_test_strtrim_r("strtrim_r (empty charset)  ", FALSE,			"   swag\n",                   "",            "   swag\n");
	print_test_strtrim_r("strtrim_r (both empty)     ", FALSE,			"",                            "",            "");
	print_test_strtrim_r("strtrim_r (null string)    ", SIGNAL_SIGSEGV,	NULL,                          "ab", NULL);
	print_test_strtrim_r("strtrim_r (null charset)   ", SIGNAL_SIGSEGV,	NULL,                          NULL, "ab");
	print_test_strtrim_r("strtrim_r (both null)      ", SIGNAL_SIGSEGV,	NULL,                          NULL, NULL);
}
#endif


#ifndef c_strpad
void test_strpad(void)	{}
#else
void	print_test_strpad(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpad, str, c, length)
	TEST_PRINT(str,	strpad, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad(void)
{
//	| TEST FUNCTION     | TEST NAME             | CAN SEGV       | EXPECTING         | TEST ARGS
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
	print_test_strpad("strpad (null string)    ", SIGNAL_SIGSEGV,	NULL,              NULL,  ' ', 5);
}
#endif



#ifndef c_strpad_l
void test_strpad_l(void)	{}
#else
void	print_test_strpad_l(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpad_l, str, c, length)
	TEST_PRINT(str,	strpad_l, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad_l(void)
{
//	| TEST FUNCTION     | TEST NAME              | CAN SEGV        | EXPECTING           | TEST ARGS
	print_test_strpad_l("strpad_l (n == strlen) ", FALSE,			"test",               "test", ' ', 4);
	print_test_strpad_l("strpad_l               ", FALSE,			" test",              "test", ' ', 5);
	print_test_strpad_l("strpad_l               ", FALSE,			"  test",             "test", ' ', 6);
	print_test_strpad_l("strpad_l               ", FALSE,			"   test",            "test", ' ', 7);
	print_test_strpad_l("strpad_l               ", FALSE,			"    test",           "test", ' ', 8);
	print_test_strpad_l("strpad_l               ", FALSE,			"     test",          "test", ' ', 9);
	print_test_strpad_l("strpad_l               ", FALSE,			"      test",         "test", ' ', 10);
	print_test_strpad_l("strpad_l               ", FALSE,			"01234",              "1234", '0', 5);
	print_test_strpad_l("strpad_l               ", FALSE,			"001234",             "1234", '0', 6);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE,			"wag",                "swag", ' ', 3);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE,			"ag",                 "swag", ' ', 2);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE,			"g",                  "swag", ' ', 1);
	print_test_strpad_l("strpad_l (n == 0)      ", FALSE,			"",                   "swag", ' ', 0);
	print_test_strpad_l("strpad_l (c == '\\0')  ", FALSE,			"test",               "test",'\0', 4);
	print_test_strpad_l("strpad_l (c == '\\0')  ", FALSE,			"",                   "test",'\0', 5);
	print_test_strpad_l("strpad_l (null string) ", SIGNAL_SIGSEGV,	NULL,                 NULL,  ' ', 5);
}
#endif



#ifndef c_strpad_r
void test_strpad_r(void)	{}
#else
void	print_test_strpad_r(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_INIT(str)
	TEST_PERFORM(	strpad_r, str, c, length)
	TEST_PRINT(str,	strpad_r, "str=\"%s\", c='%c'/0x%X, n=%zu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad_r(void)
{
//	| TEST FUNCTION     | TEST NAME              | CAN SEGV       | EXPECTING     | TEST ARGS
	print_test_strpad_r("strpad_r (n == strlen) ", FALSE,			"test",        "test", ' ', 4);
	print_test_strpad_r("strpad_r               ", FALSE,			"test ",       "test", ' ', 5);
	print_test_strpad_r("strpad_r               ", FALSE,			"test  ",      "test", ' ', 6);
	print_test_strpad_r("strpad_r               ", FALSE,			"test   ",     "test", ' ', 7);
	print_test_strpad_r("strpad_r               ", FALSE,			"test    ",    "test", ' ', 8);
	print_test_strpad_r("strpad_r               ", FALSE,			"test     ",   "test", ' ', 9);
	print_test_strpad_r("strpad_r               ", FALSE,			"test      ",  "test", ' ', 10);
	print_test_strpad_r("strpad_r               ", FALSE,			"12340",       "1234", '0', 5);
	print_test_strpad_r("strpad_r               ", FALSE,			"123400",      "1234", '0', 6);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE,			"swa",         "swag", ' ', 3);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE,			"sw",          "swag", ' ', 2);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE,			"s",           "swag", ' ', 1);
	print_test_strpad_r("strpad_r (n == 0)      ", FALSE,			"",            "swag", ' ', 0);
	print_test_strpad_r("strpad_r (c == '\\0')  ", FALSE,			"test",        "test",'\0', 4);
	print_test_strpad_r("strpad_r (c == '\\0')  ", FALSE,			"test",        "test",'\0', 5);
	print_test_strpad_r("strpad_r (null string) ", SIGNAL_SIGSEGV,  NULL,          NULL,  ' ', 5);
}
#endif



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

// TODO check on which platforms this function exists, if any
#ifndef c_strrev
void test_strrev(void)	{}
#else
void	print_test_strrev(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       | EXPECTING              | TEST ARGS
	print_test_strrev("strrev (even len) ",	FALSE,			".uriednihs uom aw eamO", test1);
	print_test_strrev("strrev (odd len)  ",	FALSE,			"???inaN",                test2);
	print_test_strrev("strrev (even len) ",	FALSE,			"tset",                   "test");
	print_test_strrev("strrev (len == 3) ",	FALSE,			" ()",                    ")( ");
	print_test_strrev("strrev (len == 3) ",	FALSE,			"abc",                    "cba");
	print_test_strrev("strrev (len == 2) ",	FALSE,			"ab",                     "ba");
	print_test_strrev("strrev (len == 1) ",	FALSE,			"?",                      "?");
	print_test_strrev("strrev (len == 0) ",	FALSE,			"",                       "");
	print_test_strrev("strrev (null ptr) ",	SIGNAL_SIGSEGV,	NULL,                     NULL);
}
#endif


#ifndef c_strjoin
void test_strjoin(void)	{}
#else
void	print_test_strjoin(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str1,
		char const *str2)
{
	TEST_INIT(str)
	TEST_PERFORM(	strjoin, str1, str2)
	TEST_PRINT(str,	strjoin, "str1=\"%s\", str2=\"%s\"", str1, str2)
	TEST_FREE()
}
void	test_strjoin(void)
{
//	| TEST FUNCTION   | TEST NAME             | CAN SEGV       | EXPECTING                      | TEST ARGS
	print_test_strjoin("strjoin             ", FALSE,			"Omae wa mou shindeiru.Nani???",  test1,  test2);
	print_test_strjoin("strjoin             ", FALSE,			"test1test2",                    "test1", "test2");
	print_test_strjoin("strjoin             ", FALSE,			"Whoa...",                       "Whoa.", "..");
	print_test_strjoin("strjoin (empty str1)", FALSE,			"sweg",                          "sweg",  "");
	print_test_strjoin("strjoin (empty str2)", FALSE,			"sweg",                          "",      "sweg");
	print_test_strjoin("strjoin (both empty)", FALSE,			"",                              "",      "");
	print_test_strjoin("strjoin (null str1) ", SIGNAL_SIGSEGV,	NULL,                            NULL,  test2);
	print_test_strjoin("strjoin (null str2) ", SIGNAL_SIGSEGV,	NULL,                            test1, NULL);
	print_test_strjoin("strjoin (both null) ", SIGNAL_SIGSEGV,	NULL,                            NULL,  NULL);
}
#endif


#ifndef c_strinsert
void test_strinsert(void)	{}
#else
void	print_test_strinsert(char const* test_name, int can_segfault,
		char const* expecting,
		char const *dest,
		char const *src,
		t_size offset)
{
	TEST_INIT(str)
	TEST_PERFORM(	strinsert, dest, src, offset)
	TEST_PRINT(str,	strinsert, "dest=\"%s\", src=\"%s\", offset=%lu", dest, src, offset)
	TEST_FREE()
}
void	test_strinsert(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_strsub
void test_strsub(void)	{}
#else
void	print_test_strsub(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		t_size offset,
		t_size n)
{
	TEST_INIT(str)
	TEST_PERFORM(	strsub, str, offset, n)
	TEST_PRINT(str,	strsub, "str=\"%s\", offset=%lu, n=%zu", str, offset, n)
	TEST_FREE()
}
void	test_strsub(void)
{
//	| TEST FUNCTION  | TEST NAME               | CAN SEGV         |EXPECTING| TEST ARGS
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
	print_test_strsub("strsub (offset > str)  ", SIGNAL_SIGSEGV,	NULL,     test1, 100, 5);
	print_test_strsub("strsub (offset+len>str)", SIGNAL_SIGSEGV,	NULL,     test1, 100, 5);
	print_test_strsub("strsub (null ptr)      ", SIGNAL_SIGSEGV,	NULL,     NULL,  5, 5);
}
#endif



void	strtolower(t_char* c)
{
	if (isupper(*c))
		*c = tolower(*c);
}

void	strtolower_1on2(t_char* c, t_size i)
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

t_char	strtoupper_1on2(t_char c, t_size i)
{
	if (i % 2 == 1 && islower(c))
		 return (toupper(c));
	else return (c);
}



#ifndef c_striter
void test_striter(void)	{}
#else
void	print_test_striter(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(t_char*))
{
	TEST_INIT(str)
	char* result_libccc = str == NULL ? NULL : strdup(str);
	TEST_PERFORM_VOID(result_libccc, striter, result_libccc, f)
	TEST_PRINT(str,					 striter, "str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_striter(void)
{
//	| TEST FUNCTION   | TEST NAME            | CAN SEGV        | EXPECTING              | TEST ARGS
	print_test_striter("striter            ",	FALSE,			"sweg",                  "SWEG",                   &strtolower);
	print_test_striter("striter            ",	FALSE,			" test dude ",           " TesT DuDe ",            &strtolower);
	print_test_striter("striter            ",	FALSE,			"omae wa mou shindeiru.","omAe wA mOu ShINDeIRu.", &strtolower);
	print_test_striter("striter (null str) ",	SIGNAL_SIGSEGV,	NULL,                    NULL,                     &strtolower);
	print_test_striter("striter (null func)",	SIGNAL_SIGSEGV,	NULL,                    "omAe wA mOu ShINDeIRu.", NULL);
	print_test_striter("striter (both null)",	SIGNAL_SIGSEGV,	NULL,                    NULL,                     NULL);
}
#endif


#ifndef c_striteri
void test_striteri(void)	{}
#else
void	print_test_striteri(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(t_char*, t_size))
{
	TEST_INIT(str)
	char* result_libccc = str == NULL ? NULL : strdup(str);
	TEST_PERFORM_VOID(result_libccc, striteri, result_libccc, f)
	TEST_PRINT(str,					 striteri, "str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_striteri(void)
{
//	| TEST FUNCTION    | TEST NAME            | CAN SEGV       | EXPECTING               | TEST ARGS
	print_test_striteri("striteri            ",	FALSE,			"sWeG",                   "SWEG",                   &strtolower_1on2);
	print_test_striteri("striteri            ",	FALSE,			" Test dude ",            " TesT DuDe ",            &strtolower_1on2);
	print_test_striteri("striteri            ",	FALSE,			"oMaE Wa mOu sHiNdEiRu.", "OMAE WA MOU SHINDEIRU.", &strtolower_1on2);
	print_test_striteri("striteri (null str) ",	SIGNAL_SIGSEGV,	NULL,                     NULL,                     &strtolower_1on2);
	print_test_striteri("striteri (null func)",	SIGNAL_SIGSEGV,	NULL,                     "OMAE WA MOU SHINDEIRU.", NULL);
	print_test_striteri("striteri (both null)",	SIGNAL_SIGSEGV,	NULL,                     NULL,                     NULL);
}
#endif


#ifndef c_strmap
void test_strmap(void)	{}
#else
void	print_test_strmap(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		t_char (*f)(t_char))
{
	TEST_INIT(str)
	TEST_PERFORM(	strmap, str, f)
	TEST_PRINT(str,	strmap, "str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_strmap(void)
{
//	| TEST FUNCTION   | TEST NAME         | CAN SEGV       | EXPECTING      | TEST ARGS
	print_test_strmap("strmap            ",	FALSE, "OMAE WA MOU SHINDEIRU.", "omae wa mou shindeiru.", &strtoupper);
	print_test_strmap("strmap (null str) ",	SIGNAL_SIGSEGV,	NULL,            NULL,                     &strtoupper);
	print_test_strmap("strmap (null func)",	SIGNAL_SIGSEGV,	NULL,            "omae wa mou shindeiru.", NULL);
	print_test_strmap("strmap (both null)",	SIGNAL_SIGSEGV,	NULL,            NULL,                     NULL);
}
#endif


#ifndef c_strmapi
void test_strmapi(void)	{}
#else
void	print_test_strmapi(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		t_char (*f)(t_char, t_size))
{
	TEST_INIT(str)
	TEST_PERFORM(	strmapi, str, f)
	TEST_PRINT(str,	strmapi, "str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_strmapi(void)
{
//	| TEST FUNCTION   | TEST NAME             | CAN SEGV       | EXPECTING      | TEST ARGS
	print_test_strmapi("strmapi            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.", "omae wa mou shindeiru.", &strtoupper_1on2);
	print_test_strmapi("strmapi (null str) ",	SIGNAL_SIGSEGV,	NULL,            NULL,                     &strtoupper_1on2);
	print_test_strmapi("strmapi (null func)",	SIGNAL_SIGSEGV,	NULL,            "omae wa mou shindeiru.", NULL);
	print_test_strmapi("strmapi (both null)",	SIGNAL_SIGSEGV,	NULL,            NULL,                     NULL);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_string(void)
{
	print_suite_title("libccc/string");



	test_strnew();
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
//	test_strmerge();
//	test_strappend();
//	test_strprepend();

	test_strequ();
	test_strnequ();
	test_strhas();
	test_strhasonly();
	test_strcount_char();
	test_strcount_str();

	test_strnchr();
	test_strrstr();
	test_strtoesc();
	test_esctostr();
//	test_strrep_char();
//	test_strrep_charset();
//	test_strrep_str();

	test_strtrim();
	test_strtrim_l();
	test_strtrim_r();
	test_strpad();
	test_strpad_l();
	test_strpad_r();

	test_strrev();
	test_strjoin();
//	test_strinsert();
	test_strsub();
	test_striter();
	test_striteri();
	test_strmap();
	test_strmapi();

	return (0);
}
