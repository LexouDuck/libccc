
#include "libccc/memory.h"

#include "test.h"



#ifndef c_memalloc
void test_memalloc(void)	{}
#warning "memalloc() test suite function defined, but the function isn't defined."
#else
#define memalloc(n)	malloc(n)
void	print_test_memalloc(char const* test_name, t_testflags flags,
		t_size n)
{
	TEST_INIT(alloc)
	test.length = n;
	TEST_PERFORM_LIBC(	memalloc, n)
	TEST_PRINT(alloc,	memalloc, "n=%zu", n)
	TEST_FREE()
}
void	test_memalloc(void)
{
//	| TEST FUNCTION    | TEST NAME              |TESTFLAG|TEST ARGS
	// TODO
}
#endif



#ifndef c_memnew
void test_memnew(void)	{}
#warning "memnew() test suite function defined, but the function isn't defined."
#else
static void*	memnew(t_size n) { void* result = malloc(n);	memset(result, 0, n);	return (result); }
void	print_test_memnew(char const* test_name, t_testflags flags,
		t_size n)
{
	TEST_INIT(alloc)
	test.length = n;
	TEST_PERFORM_LIBC(	memnew, n)
	TEST_PRINT(alloc,	memnew, "n=%zu", n)
	TEST_FREE_LIBC()
}
void	test_memnew(void)
{
//	| TEST FUNCTION  | TEST NAME              |TESTFLAG|TEST ARGS
	print_test_memnew("memnew              ",	FALSE,	8);
	print_test_memnew("memnew (n = 0xFFFF) ",	FALSE,	0xFFFF);
	print_test_memnew("memnew (n = 0x10000)",	FALSE,	0x10000);
	print_test_memnew("memnew (n = 0)      ",	FALSE,	0);
	// TODO more tests
}
#endif



//! TODO memcnew()



#ifndef c_memfree
void test_memfree(void)	{}
#warning "memfree() test suite function defined, but the function isn't defined."
#else
void	print_test_memfree(char const* test_name, t_testflags flags,
		void* expecting,
		void* ptr)
{
	TEST_INIT(ptr)
	TEST_PERFORM_VOID(ptr,	memfree, ptr)
	TEST_PRINT(ptr,			memfree, "ptr=%p", ptr)
}
void	test_memfree(void)
{
	t_size const length = 16;
	void* test = (void*)malloc(length);
	memset(test, 0, length);
//	| TEST FUNCTION  | TEST NAME        | TESTFLAGS| TEST ARGS
/* TODO figure out how to test this function
	print_test_memfree("memfree",	          	FALSE,	test);
	print_test_memfree("memfree (null ptr)",	FALSE,	NULL);
*/
}
#endif



#ifndef c_memdel
void test_memdel(void)	{}
#warning "memdel() test suite function defined, but the function isn't defined."
#else
static void	memdel(void** ptr) { free(*ptr); ptr = NULL; }
void	print_test_memdel(char const* test_name, t_testflags flags,
		void** expecting,
		void** ptr)
{
	TEST_INIT(ptr)
	TEST_PERFORM_VOID_LIBC(*ptr, memdel, ptr) // TODO fix this
	TEST_PRINT(ptr, memdel, "ptr=%p", (void*)ptr)
}
void	test_memdel(void)
{
	t_size const length = 16;
	void* test_result;
	void* test_expect;
//	| TEST FUNCTION  | TEST NAME         | TESTFLAGS      | EXPECTING     | TEST ARGS
	test_result = (void*)malloc(length);
	test_expect = (void*)malloc(length);
	print_test_memdel("memdel",	          	FALSE,			&test_expect,	&test_result);
	test_result = (void*)malloc(length);
	test_expect = (void*)malloc(length);
	print_test_memdel("memdel (null arg)",	ALLOW_SIGSEGV,	&test_expect,	&test_result); // TODO figure out how to recover from this
	print_test_memdel("memdel (null ptr)",	ALLOW_SIGSEGV,	NULL,			NULL); // TODO figure out how to recover from this
}
#endif



#ifndef c_memset
void test_memset(void)	{}
#warning "memset() test suite function defined, but the function isn't defined."
#else
void	print_test_memset(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		int byte,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_VOID_LIBC_DEST(memset, byte, n)
	TEST_PRINT(mem,				memset, "dest=\"%s\", c='%c'/0x%X, n=%zu", dest_libccc, byte, byte, n)
}
void	test_memset(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	int n1 = 0x6969;
	int n2 = 0x6969;
//	| TEST FUNCTION  | TEST NAME        | TESTFLAGS        | TEST ARGS
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       'a',    7);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       'b',    1);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       '_',    16);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       '@',    3);
	print_test_memset("memset (c > 127)",    FALSE,			str1,       str2,       '\x88', 5);
	print_test_memset("memset (int*)   ",    FALSE,			(char*)&n1, (char*)&n2, 0xBABA, 4);
	print_test_memset("memset (n = 0)  ",    FALSE,			str1,       str2,       '\0',   0);
	print_test_memset("memset (null ptr)", ALLOW_SIGSEGV, 	str1,       str2,       '_',    5);
}
#endif



#ifndef c_memclr
void test_memclr(void)	{}
#warning "memclr() test suite function defined, but the function isn't defined."
#else
// NB: this alias is defined because this function has a different name in libccc
#ifdef __MINGW32__
#define memclr(dest, n)	memset(dest, 0, n)
#else
#define memclr(dest, n)	bzero(dest, n)
#endif
void	print_test_memclr(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_VOID_LIBC_DEST(memclr, n)
	TEST_PRINT(mem,				memclr, "dest=\"%s\", n=%zu", dest_libccc, n)
}
void	test_memclr(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	int n1 = 0x6969;
	int n2 = 0x6969;
//	| TEST FUNCTION  | TEST NAME                | TESTFLAGS    | TEST ARGS
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       3);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       8);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       12);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       16);
	print_test_memclr("memclr/bzero (int*) ",   	FALSE,		(char*)&n1, (char*)&n2, sizeof(int));
	print_test_memclr("memclr/bzero (n = 0)",   	FALSE,		str1,       str2,       0);
	print_test_memclr("memclr/bzero (null ptr)",ALLOW_SIGSEGV,	NULL,       NULL,       2);
}
#endif



#ifndef c_memcpy
void test_memcpy(void)	{}
#warning "memcpy() test suite function defined, but the function isn't defined."
#else
void	print_test_memcpy(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_LIBC_DEST(	memcpy, src, n)
	TEST_PRINT(mem,			memcpy, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	test.function = "memcpy 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_mem(&test, NULL);
}
void	test_memcpy(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME            | TESTFLAGS       | TEST ARGS
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test1, test1_len);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test2, test2_len);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test3, 20);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test1, 2);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test2, 1);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test3, strlen(str1));
	print_test_memcpy("memcpy (int*)      ", FALSE,				(char*)&n1, (char*)&n2, (char const *)&n, sizeof(n));
	print_test_memcpy("memcpy (n = 0)     ", FALSE,				str1, str2, test2, 0);
	print_test_memcpy("memcpy (n > srclen)", ALLOW_SIGSEGV,	str1, str2, test2, test2_len + 5);
	print_test_memcpy("memcpy (null dest) ", ALLOW_SIGSEGV, 	NULL, NULL, test2, test2_len);
	print_test_memcpy("memcpy (null src)  ", ALLOW_SIGSEGV, 	str1, str2, NULL,  test2_len);
	print_test_memcpy("memcpy (both null) ", ALLOW_SIGSEGV, 	NULL, NULL, NULL,  test2_len);
	// TODO add overlapping memory test
}
#endif



#ifndef c_memccpy
void test_memccpy(void)	{}
#warning "memccpy() test suite function defined, but the function isn't defined."
#else
void	print_test_memccpy(char const* test_name, t_testflags flags,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_u8 byte,
		t_size n)
{
	TEST_INIT(mem)
	test.result = strchr(src, byte);
	test.length = (test.result == NULL ? -1u : ((char const*)test.result - src));
	test.length = (test.length < n ? test.length : n);
	test.result = NULL;
	TEST_PERFORM_LIBC_DEST(	memccpy, src, byte, n)
	TEST_PRINT(mem,			memccpy, "dest=\"%s\", src=\"%s\", c='%c'/0x%X, n=%zu", dest_libccc, src, (byte == '\0' ? ' ' : byte), byte, n)
/*
	s_test_mem test2 = (s_test_mem)
	{
		.name = test.name,
		.function = "memccpy 'dest' arg",
		.can_sig = test.can_sig,
		.result = dest_libccc,
		.expect = dest_libc,
		.result_sig = test.result_sig,
		.expect_sig = test.expect_sig,
		.timer = test.timer,
		.length = test.length,
	};
	print_test_mem(&test2, NULL);
*/
}
void	test_memccpy(void)
{
	char str1[] = "________________________________";
	char str2[] = "________________________________";
	uint64_t n = 0x0102030405060708;
	uint32_t n32_1 = 0x00ABCDEF;
	uint32_t n32_2 = 0x00ABCDEF;
	uint64_t n64_1 = 0x00ABCDEF6969CAFE;
	uint64_t n64_2 = 0x00ABCDEF6969CAFE;
//	| TEST FUNCTION   | TEST NAME             | TESTFLAGS      | TEST ARGS
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test1, '\r', test1_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test1, 'w',  test1_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test1, ' ',  test1_len);
	print_test_memccpy("memccpy (str,len=0) ", FALSE,			str1, str2, test1, ' ',  0);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test2, '\t', test2_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test2, '?',  test2_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test2, ' ',  test2_len);
	print_test_memccpy("memccpy (str,len=0) ", FALSE,			str1, str2, test2, ' ',  0);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test3, '\n', test3_len);
//	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test3, 'f',  test3_len); // TODO fix this test
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test3, ' ',  test3_len);
	print_test_memccpy("memccpy (str,len=0) ", FALSE,			str1, str2, test3, ' ',  0);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x7F', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x80', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x90', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\xB0', 8);
	print_test_memccpy("memccpy (int32*)    ", FALSE,			(char*)&n32_1, (char*)&n32_2, (char*)&n,   0xAA, sizeof(uint32_t));
	print_test_memccpy("memccpy (int64*)    ", FALSE,			(char*)&n64_1, (char*)&n64_2, (char*)&n,   0xAA, sizeof(uint64_t));
//	print_test_memccpy("memccpy (c = '\\0')  ",FALSE,			str1, str2, test3, '\0', test3_len + 2); // TODO fix this test
	print_test_memccpy("memccpy (null dest) ", ALLOW_SIGSEGV,	NULL, NULL, test3, 'e',  test3_len + 2);
	print_test_memccpy("memccpy (null src)  ", ALLOW_SIGSEGV,	str1, str2, NULL,  'e',  5);
	print_test_memccpy("memccpy (both null) ", ALLOW_SIGSEGV,	NULL, NULL, NULL,  'e',  5);
	// TODO add overlapping memory test
}
#endif



#ifndef c_memmove
void test_memmove(void)	{}
#warning "memmove() test suite function defined, but the function isn't defined."
#else
void	print_test_memmove(char const* test_name, t_testflags flags, int show_dest_arg,
		char* dest_libccc,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_LIBC_DEST(	memmove, src, n)
	if (show_dest_arg)
	{
		TEST_PRINT(mem,		memmove, "dest=\"%s\", src=\"%s\", n=%zu", dest_libccc, src, n)
	}
	test.function = "memmove 'dest' arg";
	test.result = dest_libccc;
	test.expect = dest_libc;
	print_test_mem(&test, show_dest_arg ? NULL : args);
}
void	test_memmove(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
//	| TEST FUNCTION   | TEST NAME            | TESTFLAGS      |TEST 'dest'?| TEST ARGS
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test1, test1_len);
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test2, test2_len);
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test3, 20);
	print_test_memmove("memmove (n = 0)    ", FALSE,			TRUE, 		str1, str2, test1, 0);
	print_test_memmove("memmove (null src) ", ALLOW_SIGSEGV,	TRUE, 		str1, str2, NULL,  5);
	print_test_memmove("memmove (null dest)", ALLOW_SIGSEGV,	FALSE,		NULL, NULL, test1, 5);
	print_test_memmove("memmove (both null)", ALLOW_SIGSEGV,	FALSE,		NULL, NULL, NULL,  5);
	print_test_memmove("memmove (both null)", ALLOW_SIGSEGV,	FALSE,		NULL, NULL, NULL,  5);
	// TODO add overlapping memory test
//	TODO change the testing function so that the following test can be done with a simple one-line function call
/*
	segfault = setjmp(restore); if (!segfault) sra = c_memmove(str1 + 3, str1, test1_len - 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(str2 + 3, str2, test1_len - 5); else srb = segstr;
	print_test_str("memmove (overlapping)", "memmove arg",    str1,  str2,  FALSE);
	print_test_str(NULL,                    "memmove return", sra,   srb,   FALSE);
*/
}
#endif



#ifndef c_memchr
void test_memchr(void)	{}
#warning "memchr() test suite function defined, but the function isn't defined."
#else
void	print_test_memchr(char const* test_name, t_testflags flags,
		void const* ptr,
		t_u8 byte,
		t_size n)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	memchr, ptr, byte, n)
	TEST_PRINT(ptr,		memchr, "ptr=%p, c='%c'/0x%X, n=%zu", ptr, byte, byte, n)
}
void	test_memchr(void)
{
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      | TEST ARGS
	print_test_memchr("memchr (str)     ", FALSE,			test1,    'u',  test1_len);
	print_test_memchr("memchr (str)     ", FALSE,			test2,    '?',  test2_len);
	print_test_memchr("memchr (str)     ", FALSE,			test3,    'u',  test3_len);
	print_test_memchr("memchr (str)     ", FALSE,			test3,    '_',  test3_len);
	print_test_memchr("memchr (int*)    ", FALSE,			(char*)&n,0xBB, 8);
	print_test_memchr("memchr (c='\\0')  ",FALSE,			test1,    '\0', test1_len);
	print_test_memchr("memchr (c='\\0')  ",FALSE,			test3,    '\0', test3_len + 1);
	print_test_memchr("memchr (n = 0)   ", FALSE,			test1,    'u',  0);
	print_test_memchr("memchr (null ptr)", ALLOW_SIGSEGV, 	NULL,     'c',  4);
}
#endif



#ifndef c_memcmp
void test_memcmp(void)	{}
#warning "memcmp() test suite function defined, but the function isn't defined."
#else
void	print_test_memcmp(char const* test_name, t_testflags flags,
		char const* ptr1,
		char const* ptr2,
		t_size n)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	memcmp, ptr1, ptr2, n)
	TEST_PRINT(sign,	memcmp, "ptr1=%p, ptr2=%p, n=%zu", (void*)ptr1, (void*)ptr2, n)
}
void	test_memcmp(void)
{
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          | TESTFLAGS      | TEST ARGS
	print_test_memcmp("memcmp (str)  ",     FALSE,			test1, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test1, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test1, test3, test3_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test2, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test2, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test2, test3, test3_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test3, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test3, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",     FALSE,			test3, test3, test3_len);
	print_test_memcmp("memcmp (int*) ",     FALSE,			(char*)&n1, (char*)&n2,	sizeof(n1));
	print_test_memcmp("memcmp (int*) ",     FALSE,			(char*)&n1, (char*)&n,	sizeof(n));
	print_test_memcmp("memcmp (int*) ",     FALSE,			(char*)&n2, (char*)&n,	sizeof(n) - 2);
	print_test_memcmp("memcmp (int*) ",     FALSE,			(char*)&n1, (char*)&n1,	sizeof(n1));
	print_test_memcmp("memcmp (n = 0)",     FALSE,			test2, test3, 0);
//	print_test_memcmp("memcmp (int*) ",     FALSE,			&na,   &nb,   4);
	print_test_memcmp("memcmp (null str1)", ALLOW_SIGSEGV,	NULL,  test3, test3_len);
	print_test_memcmp("memcmp (null str2)", ALLOW_SIGSEGV, test2, NULL,  test3_len);
	print_test_memcmp("memcmp (both null)", ALLOW_SIGSEGV, NULL,  NULL,  test3_len);
	// note that some implementations of memcmp can know the type of argument in input,
	// so they actually return *(int*)nra - *(int*)nrb -> not just considering memory as
	// one continous sequence of bytes, like is implied in the man pages for memcmp().
}
#endif



// TODO check on which platforms this function exists, if any
#ifndef c_memdup
void test_memdup(void)	{}
#warning "memdup() test suite function defined, but the function isn't defined."
#else
void	print_test_memdup(char const* test_name, t_testflags flags,
		char const* expecting,
		char const* src,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM(	memdup, src, n)
	TEST_PRINT(mem,	memdup, "src=\"%s\", n=%zu", src, n)
	TEST_FREE()
}
void	test_memdup(void)
{
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME           | TESTFLAGS        | EXPECTING | TEST ARGS
	print_test_memdup("memdup (str)       ", FALSE,				test1,		test1, test1_len);
	print_test_memdup("memdup (str)       ", FALSE,				test2,		test2, test2_len);
	print_test_memdup("memdup (str)       ", FALSE,				test3,		test3, test3_len);
	print_test_memdup("memdup (int*)      ", FALSE,				(char*)&n,	(char*)&n, sizeof(n));
	print_test_memdup("memdup (int*)      ", FALSE,				(char*)&n1,	(char*)&n1, sizeof(n1));
	print_test_memdup("memdup (int*)      ", FALSE,				(char*)&n,	(char*)&n, sizeof(n) - 2);
	print_test_memdup("memdup (n = 2)     ", FALSE,				test1,		test1, 2);
	print_test_memdup("memdup (n = 1)     ", FALSE,				test1,		test1, 1);
	print_test_memdup("memdup (n = 0)     ", FALSE,				test1,		test1, 0);
	print_test_memdup("memdup (empty str) ", FALSE,				"", 		"",    1);
	print_test_memdup("memdup (n > srclen)", ALLOW_SIGSEGV,	test1,		test1, 0);
	print_test_memdup("memdup (null ptr)  ", ALLOW_SIGSEGV,	NULL, 		NULL,  test1_len);
}
#endif



#ifndef c_memswap
void test_memswap(void)	{}
#warning "memswap() test suite function defined, but the function isn't defined."
#else
void	print_test_memswap(void)
{
	// TODO
}
void	test_memswap(void)
{
//	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_memrep
void test_memrep(void)	{}
#warning "memrep() test suite function defined, but the function isn't defined."
#else
void	print_test_memrep(char const* test_name, t_testflags flags,
		char const* expecting,
		void* ptr,
		t_u8 old,
		t_u8 new,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_VOID(ptr,	memrep, ptr, old, new, n)
	TEST_PRINT(mem,			memrep, "ptr=\"%p\", old='%c'/0x%X, new='%c'/0x%X, n=%zu", ptr, old, old, new, new, n)
}
void	test_memrep(void)
{
	char* tst1 = strdup("Omae wa mou shindeiru.\0");		t_size const tst1_len = 23;
	char* tst2 = strdup("Nani???\0");						t_size const tst2_len = 8;
	char* tst3 = strdup("Un ange mange de la fange.\0");	t_size const tst3_len = 27;
//	| TEST FUNCTION  | TEST NAME             | TESTFLAGS      | EXPECTING                      | TEST ARGS
	print_test_memrep("memrep              ", FALSE,			"O_ae wa _ou shindeiru.",       tst1, 'm', '_', 16);
	print_test_memrep("memrep              ", FALSE,			"O_ae wa _ou shindeiru$",       tst1, '.', '$', tst1_len - 1);
	print_test_memrep("memrep              ", FALSE,			"O_ae\twa\t_ou\tshindeiru$",    tst1, ' ', '\t',tst1_len - 1);
	print_test_memrep("memrep              ", FALSE,			"Nani@@@",                      tst2, '?', '@', tst2_len - 1);
	print_test_memrep("memrep              ", FALSE,			"Nani\0\0\0",                   tst2, '@', '\0',tst2_len - 1);
	print_test_memrep("memrep              ", FALSE,			"Un ange mange de la fange.\0", tst3, '?', 'o', tst3_len - 1);
	print_test_memrep("memrep              ", FALSE,			"Un ange mange de la fange.\0", tst3, '?', 'o', tst3_len - 1);
	print_test_memrep("memrep              ", FALSE,			"Un an_e man_e de la fan_e.\0", tst3, 'g', '_', tst3_len - 1);
	print_test_memrep("memrep (old = '\\0') ",FALSE,			tst1,                           tst1, '\0','a', 16);
	print_test_memrep("memrep (n = 0)      ", FALSE,			tst1,                           tst1, ' ', 'a', 0);
//	print_test_memrep("memrep (n > len)    ", ALLOW_SIGSEGV,	NULL,                           tst3, '_', 'a', tst3_len + 64);
	print_test_memrep("memrep (null str)   ", ALLOW_SIGSEGV,	NULL,                           NULL, '_', 'a', 16);
	free(tst1);
	free(tst2);
	free(tst3);
}
#endif



#ifndef c_getbits
void test_getbits(void)	{}
#warning "getbits() test suite function defined, but the function isn't defined."
#else
void	print_test_getbits(void)
{
	s_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_getbits(void)
{
//	| TEST FUNCTION  | TEST NAME          |TESTFLAG| EXPECTING | TEST ARGS
//	TODO
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_memory(void)
{
	print_suite_title("libccc/memory");



	test_memset();
	test_memclr(); // = bzero

	test_memcpy();
	test_memccpy();
	test_memmove();

	test_memchr();
	test_memcmp();



	print_nonstd();



	test_memalloc();
	test_memnew();
//	test_memfree();
	test_memdel();

	test_memdup();

//	test_memswap();

	test_memrep();

//	test_getbits();

	return (OK);
}
