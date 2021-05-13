
#include "libccc/memory.h"

#include "test.h"



#ifndef c_memalloc
void test_memalloc(void)	{}
#else
#define memalloc(n)	malloc(n)
void	print_test_memalloc(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION    | TEST NAME              |CAN SEGV|TEST ARGS
	// TODO
}
#endif



#ifndef c_memnew
void test_memnew(void)	{}
#else
static void*	memnew(t_size n) { void* result = malloc(n);	memset(result, 0, n);	return (result); }
void	print_test_memnew(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME              |CAN SEGV|TEST ARGS
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
#else
void	print_test_memfree(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
/* TODO figure out how to test this function
	print_test_memfree("memfree",	          	FALSE,	test);
	print_test_memfree("memfree (null ptr)",	FALSE,	NULL);
*/
}
#endif



#ifndef c_memdel
void test_memdel(void)	{}
#else
static void	memdel(void** ptr) { free(*ptr); ptr = NULL; }
void	print_test_memdel(char const* test_name, int can_segfault,
		void** expecting,
		void** ptr)
{
	TEST_INIT(ptr)
	TEST_PERFORM_VOID_LIBC(*ptr, memdel, ptr) // TODO fix this
	TEST_PRINT(ptr, memdel, "ptr=%p", ptr)
}
void	test_memdel(void)
{
	t_size const length = 16;
	void* test_result;
	void* test_expect;
//	| TEST FUNCTION  | TEST NAME         | CAN SEGV       | EXPECTING     | TEST ARGS
	test_result = (void*)malloc(length);
	test_expect = (void*)malloc(length);
	print_test_memdel("memdel",	          	FALSE,			&test_expect,	&test_result);
	test_result = (void*)malloc(length);
	test_expect = (void*)malloc(length);
	print_test_memdel("memdel (null arg)",	SIGNAL_SIGSEGV,	&test_expect,	&test_result); // TODO figure out how to recover from this
	print_test_memdel("memdel (null ptr)",	SIGNAL_SIGSEGV,	NULL,			NULL); // TODO figure out how to recover from this
}
#endif



#ifndef c_memset
void test_memset(void)	{}
#else
void	print_test_memset(char const* test_name, int can_segfault,
		char* dest_libccc,
		char* dest_libc,
		int byte,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_VOID_LIBC_DEST(memset, byte, n)
	TEST_PRINT(mem,				memset, "dest=\"%s\", c=0x%x/'%c', n=%zu", dest_libccc, byte, byte, n)
}
void	test_memset(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	int n1 = 0x6969;
	int n2 = 0x6969;
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV         | TEST ARGS
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       'a',    7);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       'b',    1);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       '_',    16);
	print_test_memset("memset (str)    ",    FALSE,			str1,       str2,       '@',    3);
	print_test_memset("memset (c > 127)",    FALSE,			str1,       str2,       '\x88', 5);
	print_test_memset("memset (int*)   ",    FALSE,			(char*)&n1, (char*)&n2, 0xBABA, 4);
	print_test_memset("memset (n = 0)  ",    FALSE,			str1,       str2,       '\0',   0);
	print_test_memset("memset (null ptr)", SIGNAL_SIGSEGV, 	str1,       str2,       '_',    5);
}
#endif



#ifndef c_memclr
void test_memclr(void)	{}
#else
// NB: this alias is defined because this function has a different name in libccc
#ifdef __MINGW32__
#define memclr(dest, n)	memset(dest, 0, n)
#else
#define memclr(dest, n)	bzero(dest, n)
#endif
void	print_test_memclr(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME                | CAN SEGV     | TEST ARGS
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       3);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       8);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       12);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,		str1,       str2,       16);
	print_test_memclr("memclr/bzero (int*) ",   	FALSE,		(char*)&n1, (char*)&n2, sizeof(int));
	print_test_memclr("memclr/bzero (n = 0)",   	FALSE,		str1,       str2,       0);
	print_test_memclr("memclr/bzero (null ptr)",SIGNAL_SIGSEGV,	NULL,       NULL,       2);
}
#endif



#ifndef c_memcpy
void test_memcpy(void)	{}
#else
void	print_test_memcpy(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME            | CAN SEGV        | TEST ARGS
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test1, test1_len);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test2, test2_len);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test3, 20);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test1, 2);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test2, 1);
	print_test_memcpy("memcpy (str)       ", FALSE,				str1, str2, test3, strlen(str1));
	print_test_memcpy("memcpy (int*)      ", FALSE,				(char*)&n1, (char*)&n2, (char const *)&n, sizeof(n));
	print_test_memcpy("memcpy (n = 0)     ", FALSE,				str1, str2, test2, 0);
	print_test_memcpy("memcpy (n > srclen)", SIGNAL_SIGSEGV,	str1, str2, test2, test2_len + 5);
	print_test_memcpy("memcpy (null dest) ", SIGNAL_SIGSEGV, 	NULL, NULL, test2, test2_len);
	print_test_memcpy("memcpy (null src)  ", SIGNAL_SIGSEGV, 	str1, str2, NULL,  test2_len);
	print_test_memcpy("memcpy (both null) ", SIGNAL_SIGSEGV, 	NULL, NULL, NULL,  test2_len);
	// TODO add overlapping memory test
}
#endif



#ifndef c_memccpy
void test_memccpy(void)	{}
#else
void	print_test_memccpy(char const* test_name, int can_segfault,
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
	TEST_PRINT(mem,			memccpy, "dest=\"%s\", src=\"%s\", c=0x%x/'%c', n=%zu", dest_libccc, src, byte, (byte == '\0' ? ' ' : byte), n)
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
	uint64_t n1 = 0x00ABCDEF6969CACA;	char* num1 = (char*)&n1;
	uint64_t n2 = 0x00ABCDEF6969CACA;	char* num2 = (char*)&n2;
	uint64_t n  = 0x22446688AABBCCDD;	char* num  = (char*)&n;
//	| TEST FUNCTION   | TEST NAME             | CAN SEGV       | TEST ARGS
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test1, 'w',  test1_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test1, '\r', test1_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test2, '?',  test2_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test2, '\t', test2_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test3, 'f',  test3_len);
	print_test_memccpy("memccpy (str)       ", FALSE,			str1, str2, test3, '\n', test3_len);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x7F', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x80', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x90', 8);
	print_test_memccpy("memccpy (chars>0x80)", FALSE,			str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\xB0', 8);
	print_test_memccpy("memccpy (int*)      ", FALSE,			num1, num2, num,   0xAA, sizeof(n));
	print_test_memccpy("memccpy (c = '\\0')  ",FALSE,			str1, str2, test3, '\0', test3_len);
	print_test_memccpy("memccpy (null dest) ", SIGNAL_SIGSEGV,	NULL, NULL, test3, 'e',  test3_len);
	print_test_memccpy("memccpy (null src)  ", SIGNAL_SIGSEGV,	str1, str2, NULL,  'e',  5);
	print_test_memccpy("memccpy (both null) ", SIGNAL_SIGSEGV,	NULL, NULL, NULL,  'e',  5);
	// TODO add overlapping memory test
}
#endif



#ifndef c_memmove
void test_memmove(void)	{}
#else
void	print_test_memmove(char const* test_name, int can_segfault, int show_dest_arg,
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
//	| TEST FUNCTION   | TEST NAME            | CAN SEGV       |TEST 'dest'?| TEST ARGS
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test1, test1_len);
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test2, test2_len);
	print_test_memmove("memmove (str)      ", FALSE,			TRUE, 		str1, str2, test3, 20);
	print_test_memmove("memmove (n = 0)    ", FALSE,			TRUE, 		str1, str2, test1, 0);
	print_test_memmove("memmove (null src) ", SIGNAL_SIGSEGV,	TRUE, 		str1, str2, NULL,  5);
	print_test_memmove("memmove (null dest)", SIGNAL_SIGSEGV,	FALSE,		NULL, NULL, test1, 5);
	print_test_memmove("memmove (both null)", SIGNAL_SIGSEGV,	FALSE,		NULL, NULL, NULL,  5);
	print_test_memmove("memmove (both null)", SIGNAL_SIGSEGV,	FALSE,		NULL, NULL, NULL,  5);
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
#else
void	print_test_memchr(char const* test_name, int can_segfault,
		void const* ptr,
		t_u8 byte,
		t_size n)
{
	TEST_INIT(ptr)
	TEST_PERFORM_LIBC(	memchr, ptr, byte, n)
	TEST_PRINT(ptr,		memchr, "ptr=%p, c=0x%x/'%c', n=%zu", ptr, byte, byte, n)
}
void	test_memchr(void)
{
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       | TEST ARGS
	print_test_memchr("memchr (str)     ", FALSE,			test1,    'u',  test1_len);
	print_test_memchr("memchr (str)     ", FALSE,			test2,    '?',  test2_len);
	print_test_memchr("memchr (str)     ", FALSE,			test3,    'u',  test3_len);
	print_test_memchr("memchr (str)     ", FALSE,			test3,    '_',  test3_len);
	print_test_memchr("memchr (int*)    ", FALSE,			(char*)&n,0xBB, 8);
	print_test_memchr("memchr (c='\\0')  ",FALSE,			test1,    '\0', test1_len);
	print_test_memchr("memchr (c='\\0')  ",FALSE,			test3,    '\0', test3_len + 1);
	print_test_memchr("memchr (n = 0)   ", FALSE,			test1,    'u',  0);
	print_test_memchr("memchr (null ptr)", SIGNAL_SIGSEGV, 	NULL,     'c',  4);
}
#endif



#ifndef c_memcmp
void test_memcmp(void)	{}
#else
void	print_test_memcmp(char const* test_name, int can_segfault,
		char const* ptr1,
		char const* ptr2,
		t_size n)
{
	TEST_INIT(sign)
	TEST_PERFORM_LIBC(	memcmp, ptr1, ptr2, n)
	TEST_PRINT(sign,	memcmp, "ptr1=%p, ptr2=%p, n=%zu", ptr1, ptr2, n)
}
void	test_memcmp(void)
{
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV       | TEST ARGS
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
	print_test_memcmp("memcmp (null str1)", SIGNAL_SIGSEGV,	NULL,  test3, test3_len);
	print_test_memcmp("memcmp (null str2)", SIGNAL_SIGSEGV, test2, NULL,  test3_len);
	print_test_memcmp("memcmp (both null)", SIGNAL_SIGSEGV, NULL,  NULL,  test3_len);
	// note that some implementations of memcmp can know the type of argument in input,
	// so they actually return *(int*)nra - *(int*)nrb -> not just considering memory as
	// one continous sequence of bytes, like is implied in the man pages for memcmp().
}
#endif



// TODO check on which platforms this function exists, if any
#ifndef c_memdup
void test_memdup(void)	{}
#else
void	print_test_memdup(char const* test_name, int can_segfault,
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
//	| TEST FUNCTION  | TEST NAME           | CAN SEGV         | EXPECTING | TEST ARGS
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
	print_test_memdup("memdup (n > srclen)", SIGNAL_SIGSEGV,	test1,		test1, 0);
	print_test_memdup("memdup (null ptr)  ", SIGNAL_SIGSEGV,	NULL, 		NULL,  test1_len);
}
#endif



#ifndef c_memswap
void test_memswap(void)	{}
#else
void	print_test_memswap(void)
{
	// TODO
}
void	test_memswap(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifndef c_memrep
void test_memrep(void)	{}
#else
void	print_test_memrep(char const* test_name, int can_segfault,
		char const* expecting,
		void* ptr,
		t_u8 old,
		t_u8 new,
		t_size n)
{
	TEST_INIT(mem)
	test.length = n;
	TEST_PERFORM_VOID(ptr,	memrep, ptr, old, new, n)
	TEST_PRINT(mem,			memrep, "ptr=\"%p\", old=0x%x/'%c', new=0x%x/'%c', n=%zu", ptr, old, old, new, new, n)
}
void	test_memrep(void)
{
	char* tst1 = strdup("Omae wa mou shindeiru.\0");		t_size const tst1_len = 23;
	char* tst2 = strdup("Nani???\0");						t_size const tst2_len = 8;
	char* tst3 = strdup("Un ange mange de la fange.\0");	t_size const tst3_len = 27;
//	| TEST FUNCTION  | TEST NAME             | CAN SEGV       | EXPECTING                      | TEST ARGS
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
//	print_test_memrep("memrep (n > len)    ", SIGNAL_SIGSEGV,	NULL,                           tst3, '_', 'a', tst3_len + 64);
	print_test_memrep("memrep (null str)   ", SIGNAL_SIGSEGV,	NULL,                           NULL, '_', 'a', 16);
	free(tst1);
	free(tst2);
	free(tst3);
}
#endif



#ifndef c_getbits
void test_getbits(void)	{}
#else
void	print_test_getbits(void)
{
	s_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_getbits(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
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
	printf("\n");
	return (OK);
}
