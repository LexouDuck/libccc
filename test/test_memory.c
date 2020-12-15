
#include "libft_memory.h"

#include "test.h"



#ifdef			ft_memalloc
void	print_test_memalloc(char const* test_name, int can_segfault,
		t_size n)
{
	TEST_PERFORM_RESULT(memalloc, n);
	print_test_alloc(test_name, "memalloc", result_libft, n);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("n=%lu", n)
	TEST_FREE()
}
void	test_memalloc(void)
{
//	| TEST FUNCTION    | TEST NAME              |CAN SEGV|TEST ARGS
	// TODO
}
#endif



#ifdef			ft_memnew
void	print_test_memnew(char const* test_name, int can_segfault,
		t_size n)
{
	TEST_PERFORM_RESULT(memnew, n);
	print_test_alloc(test_name, "memnew", result_libft, n);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("n=%lu", n)
	TEST_FREE()
}
void	test_memnew(void)
{
//	| TEST FUNCTION    | TEST NAME              |CAN SEGV|TEST ARGS
	print_test_memnew("memnew              ",	FALSE,	8);
	print_test_memnew("memnew (n = 0x10000)",	FALSE,	0x10000);
	print_test_memnew("memnew (n = 0)      ",	FALSE,	0);
}
#endif



#ifdef			ft_memfree
void	print_test_memfree(char const* test_name, int can_segfault,
		void *ptr)
{
	TEST_PERFORM(ptr, memfree, ptr)
	print_test_mem(test_name, "memfree arg", ptr, ptr, 0, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("ptr=%p", ptr)
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



#ifdef			ft_memdel
void	print_test_memdel(char const* test_name, int can_segfault,
		void **ptr)
{
	TEST_PERFORM(*ptr, memdel, ptr)
	print_test_mem(test_name, "memdel arg", *ptr, NULL, 0, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("ptr=%p", ptr)
}
void	test_memdel(void)
{
	t_size const length = 16;
	void* test = (void*)malloc(length);
	memset(test, 0, length);
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_memdel("memdel",	          	FALSE,	&test);
//	print_test_memdel("memdel (null arg)",	FALSE,	&test); // TODO figure out how to recover from this
//	print_test_memdel("memdel (null ptr)",	FALSE,	NULL); // TODO figure out how to recover from this
}
#endif



#ifdef			ft_memset
void	print_test_memset(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		int byte,
		t_size n)
{
	TEST_PERFORM_LIBC_DEST(memset, byte, n)
	print_test_mem(test_name, "memset 'dest' arg", dest_libft, dest_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", c=0x%x/'%c', n=%lu", dest_libft, byte, byte, n)
}
void	test_memset(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	int n1 = 0x6969;
	int n2 = 0x6969;
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_memset("memset (str)    ",    FALSE,	str1,       str2,       'a',    7);
	print_test_memset("memset (str)    ",    FALSE,	str1,       str2,       'b',    1);
	print_test_memset("memset (str)    ",    FALSE,	str1,       str2,       '_',    16);
	print_test_memset("memset (str)    ",    FALSE,	str1,       str2,       '@',    3);
	print_test_memset("memset (c > 127)",    FALSE,	str1,       str2,       '\x88', 5);
	print_test_memset("memset (int*)   ",    FALSE,	(char*)&n1, (char*)&n2, 0xBABA, 4);
	print_test_memset("memset (n = 0)  ",    FALSE,	str1,       str2,       '\0',   0);
	print_test_memset("memset (null ptr)", TRUE, 	str1,       str2,       '_',    5);
}
#endif



#ifdef			ft_memclr
// NB: this alias is defined because this function has a different name in libft
#ifdef __MINGW32__
static inline void	memclr(void *ptr, t_size n) { memset(ptr, 0, n); }
#else
#define memclr(dest, n)	bzero(dest, n)
#endif
void	print_test_memclr(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		t_size n)
{
	TEST_PERFORM_LIBC_DEST(memclr, n)
	print_test_mem(test_name, "memclr/bzero arg",                     dest_libft,     dest_libc,     n, can_segfault);
//	print_test_mem(NULL,      "memclr/bzero (byte after the '\\0's)", dest_libft + n, dest_libc + n, 1, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", n=%lu", dest_libft, n)
}
void	test_memclr(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	int n1 = 0x6969;
	int n2 = 0x6969;
//	| TEST FUNCTION  | TEST NAME                | CAN SEGV | TEST ARGS
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,	str1,       str2,       3);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,	str1,       str2,       8);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,	str1,       str2,       12);
	print_test_memclr("memclr/bzero (str)  ",   	FALSE,	str1,       str2,       16);
	print_test_memclr("memclr/bzero (int*) ",   	FALSE,	(char*)&n1, (char*)&n2, sizeof(int));
	print_test_memclr("memclr/bzero (n = 0)",   	FALSE,	str1,       str2,       0);
	print_test_memclr("memclr/bzero (null ptr)",	TRUE, 	NULL,       NULL,       2);
}
#endif



#ifdef			ft_memcpy
void	print_test_memcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC_DEST(memcpy, src, n)
	print_test_mem(test_name, "memcpy 'dest' arg", dest_libft,   dest_libc,   n, can_segfault);
	print_test_mem(NULL,      "memcpy return",     result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", n=%lu", dest_libft, src, n)
}
void	test_memcpy(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| TEST ARGS
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test1, test1_len);
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test2, test2_len);
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test3, 20);
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test1, 2);
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test2, 1);
	print_test_memcpy("memcpy (str)  ",      FALSE,	str1, str2, test3, strlen(str1));
	print_test_memcpy("memcpy (int*) ",      FALSE,	(char*)&n1, (char*)&n2, (char const *)&n, sizeof(n));
	print_test_memcpy("memcpy (n = 0)",      FALSE,	str1, str2, test2, 0);
	print_test_memcpy("memcpy (n > srclen)", TRUE,	str1, str2, test2, test2_len + 5);
	print_test_memcpy("memcpy (null dest) ", TRUE, 	NULL, NULL, test2, test2_len);
	print_test_memcpy("memcpy (null src)  ", TRUE, 	str1, str2, NULL,  test2_len);
	print_test_memcpy("memcpy (both null) ", TRUE, 	NULL, NULL, NULL,  test2_len);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_memccpy
void	print_test_memccpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_u8 byte,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC_DEST(memccpy, src, byte, n)
	print_test_mem(test_name, "memccpy 'dest' arg", dest_libft,   dest_libc, n, can_segfault);// if (byte !='\0')
	print_test_str(NULL,      "memccpy return",     result_libft, result_libc,  can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", c=0x%x/'%c', n=%lu", dest_libft, src, byte, byte, n)
}
void	test_memccpy(void)
{
	char str1[] = "________________________________";
	char str2[] = "________________________________";
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test1, 'w',  test1_len);
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test1, '\r', test1_len);
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test2, '?',  test2_len);
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test2, '\t', test2_len);
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test3, 'f',  test3_len);
	print_test_memccpy("memccpy (str)       ", 	FALSE,	str1, str2, test3, '\n', test3_len);
	print_test_memccpy("memccpy (chars>0x80)", 	FALSE,	str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x7F', 8);
	print_test_memccpy("memccpy (chars>0x80)", 	FALSE,	str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\x90', 8);
	print_test_memccpy("memccpy (chars>0x80)", 	FALSE,	str1, str2, "\x78\x7F\x80\x81\x90\xA0\xB0", '\xB0', 8);
	print_test_memccpy("memccpy (int*)      ", 	FALSE,	(char*)&n1, (char*)&n2, (char const *)&n, 0xAA, sizeof(n));
	print_test_memccpy("memccpy (c = '\\0')",	FALSE,	str1, str2, test3, '\0', test3_len);
	print_test_memccpy("memccpy (null dest)",	TRUE, 	NULL, NULL, test3, 'e',  test3_len);
	print_test_memccpy("memccpy (null src) ",	TRUE, 	str1, str2, NULL,  'e',  5);
	print_test_memccpy("memccpy (both null)",	TRUE, 	NULL, NULL, NULL,  'e',  5);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_memmove
void	print_test_memmove(char const* test_name, int can_segfault, int show_dest_arg,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC_DEST(memmove, src, n)
	if (show_dest_arg)
	print_test_mem(test_name,                    "memmove 'dest' arg", dest_libft,   dest_libc, n, can_segfault);
	print_test_mem(show_dest_arg ? NULL : test_name, "memmove return", result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", n=%lu", dest_libft, src, n)
}
void	test_memmove(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
//	| TEST FUNCTION   | TEST NAME           |CAN SEGV| TEST'dest'? | TEST ARGS
	print_test_memmove("memmove (str)  ",    	FALSE,	TRUE, 		str1, str2, test1, test1_len);
	print_test_memmove("memmove (str)  ",    	FALSE,	TRUE, 		str1, str2, test2, test2_len);
	print_test_memmove("memmove (str)  ",    	FALSE,	TRUE, 		str1, str2, test3, 20);
	print_test_memmove("memmove (n = 0)",    	FALSE,	TRUE, 		str1, str2, test1, 0);
	print_test_memmove("memmove (null src) ",	TRUE, 	TRUE, 		str1, str2, NULL,  5);
	print_test_memmove("memmove (null dest)",	TRUE, 	FALSE,		NULL, NULL, test1, 5);
	print_test_memmove("memmove (both null)",	TRUE, 	FALSE,		NULL, NULL, NULL,  5);
	print_test_memmove("memmove (both null)",	TRUE, 	FALSE,		NULL, NULL, NULL,  5);
	// TODO add overlapping memory test
//	TODO change the testing function so that the following test can be done with a simple one-line function call
/*
	segfault = setjmp(restore); if (!segfault) sra = ft_memmove(str1 + 3, str1, test1_len - 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(str2 + 3, str2, test1_len - 5); else srb = segstr;
	print_test_str("memmove (overlapping)", "memmove arg",    str1,  str2,  FALSE);
	print_test_str(NULL,                    "memmove return", sra,   srb,   FALSE);
*/
}
#endif



#ifdef			ft_memchr
void	print_test_memchr(char const* test_name, int can_segfault,
		void const* ptr,
		t_u8 byte,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC(memchr, ptr, byte, n)
	print_test_mem(test_name, "memchr return", result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("ptr=%p, c=0x%x/'%c', n=%lu", ptr, byte, byte, n)
}
void	test_memchr(void)
{
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_memchr("memchr (str)   ",   FALSE,	test1,    'u',  test1_len);
	print_test_memchr("memchr (str)   ",   FALSE,	test2,    '?',  test2_len);
	print_test_memchr("memchr (str)   ",   FALSE,	test3,    'u',  test3_len);
	print_test_memchr("memchr (str)   ",   FALSE,	test3,    '_',  test3_len);
	print_test_memchr("memchr (int*)  ",   FALSE,	(char*)&n,0xBB, 8);
	print_test_memchr("memchr (c='\\0')",  FALSE,	test1,    '\0', test1_len);
	print_test_memchr("memchr (c='\\0')",  FALSE,	test3,    '\0', test3_len + 1);
	print_test_memchr("memchr (n = 0) ",   FALSE,	test1,    'u',  0);
	print_test_memchr("memchr (null ptr)", TRUE, 	NULL,     'c',  4);
}
#endif



#ifdef			ft_memcmp
void	print_test_memcmp(char const* test_name, int can_segfault,
		char const* ptr1,
		char const* ptr2,
		t_size n)
{
	TEST_PERFORM_RESULT_TYPE_LIBC(int, memcmp, ptr1, ptr2, n)
	print_test_sign(test_name, "memcmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("ptr1=%p, ptr2=%p, n=%lu", ptr1, ptr2, n)
}
void	test_memcmp(void)
{
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n2 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          | CAN SEGV | TEST ARGS
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test1, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test1, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test1, test3, test3_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test2, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test2, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test2, test3, test3_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test3, test1, test1_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test3, test2, test2_len);
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test3, test3, test3_len);
	print_test_memcmp("memcmp (int*) ",    	FALSE,		(char*)&n1, (char*)&n2, sizeof(n1));
	print_test_memcmp("memcmp (int*) ",    	FALSE,		(char*)&n1, (char*)&n, sizeof(n));
	print_test_memcmp("memcmp (int*) ",    	FALSE,		(char*)&n2, (char*)&n, sizeof(n) - 2);
	print_test_memcmp("memcmp (int*) ",    	FALSE,		(char*)&n1, (char*)&n1, sizeof(n1));
	print_test_memcmp("memcmp (n = 0)",    	FALSE,		test2, test3, 0);
//	print_test_memcmp("memcmp (int*) ",    	FALSE,		&na,   &nb,   4);
	print_test_memcmp("memcmp (null str1)",	SEGV,		NULL,  test3, test3_len);
	print_test_memcmp("memcmp (null str2)",	SEGV, 		test2, NULL,  test3_len);
	print_test_memcmp("memcmp (both null)",	SEGV, 		NULL,  NULL,  test3_len);
	// note that some implementations of memcmp can know the type of argument in input,
	// so they actually return *(int*)nra - *(int*)nrb -> not just considering memory as
	// one continous sequence of bytes, like is implied in the man pages for memcmp().
}
#endif



// TODO check on which platforms this function exists, if any
#ifdef			ft_memdup
void	print_test_memdup(char const* test_name, int can_segfault,
		char const* expecting,
		char const* src,
		t_size n)
{
	TEST_PERFORM_RESULT(memdup, src, n)
	print_test_mem(test_name, "_memdup return", result_libft, expecting, n, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("src=\"%s\", n=%lu", src, n)
	TEST_FREE()
}
void	test_memdup(void)
{
	uint64_t n1 = 0x00ABCDEF6969CACA;
	uint64_t n = 0x22446688AABBCCDD;
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
	print_test_memdup("memdup (str)      ",	FALSE,	test1,		test1, test1_len);
	print_test_memdup("memdup (str)      ",	FALSE,	test2,		test2, test2_len);
	print_test_memdup("memdup (str)      ",	FALSE,	test3,		test3, test3_len);
	print_test_memdup("memdup (int*)     ",	FALSE,	(char*)&n,	(char*)&n, sizeof(n));
	print_test_memdup("memdup (int*)     ",	FALSE,	(char*)&n1,	(char*)&n1, sizeof(n1));
	print_test_memdup("memdup (int*)     ",	FALSE,	(char*)&n,	(char*)&n, sizeof(n) - 2);
	print_test_memdup("memdup (n = 2)    ",	FALSE,	test1,		test1, 2);
	print_test_memdup("memdup (n = 1)    ",	FALSE,	test1,		test1, 1);
	print_test_memdup("memdup (n = 0)    ",	FALSE,	test1,		test1, 0);
	print_test_memdup("memdup (empty str)",	FALSE,	"", 		"",    1);
	print_test_memdup("memdup (n > srclen)", TRUE,	test1,		test1, 0);
	print_test_memdup("memdup (null ptr)", 	 TRUE,	NULL, 		NULL,  test1_len);
}
#endif



#ifdef			ft_memswap
void	print_test_memswap(void)
{
	s_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_memswap(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_memrep
void	print_test_memrep(char const* test_name, int can_segfault,
		char const* expecting,
		void* ptr,
		t_u8 old,
		t_u8 new,
		t_size n)
{
	TEST_PERFORM(ptr, memrep, ptr, old, new, n)
	print_test_mem(test_name, "_memrep return", ptr, expecting, n, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("ptr=\"%p\", old=0x%x/'%c', new=0x%x/'%c', n=%lu", ptr, old, old, new, new, n)
}
void	test_memrep(void)
{
	char* tst1 = strdup("Omae wa mou shindeiru.\0");		t_size const tst1_len = 23;
	char* tst2 = strdup("Nani???\0");						t_size const tst2_len = 8;
	char* tst3 = strdup("Un ange mange de la fange.\0");	t_size const tst3_len = 27;
//	| TEST FUNCTION  | TEST NAME            |CAN SEGV| EXPECTING                      | TEST ARGS
	print_test_memrep("memrep              ",	FALSE, "O_ae wa _ou shindeiru.",       tst1, 'm', '_', 16);
	print_test_memrep("memrep              ",	FALSE, "O_ae wa _ou shindeiru$",       tst1, '.', '$', tst1_len - 1);
	print_test_memrep("memrep              ",	FALSE, "O_ae\twa\t_ou\tshindeiru$",    tst1, ' ', '\t',tst1_len - 1);
	print_test_memrep("memrep              ",	FALSE, "Nani@@@",                      tst2, '?', '@', tst2_len - 1);
	print_test_memrep("memrep              ",	FALSE, "Nani\0\0\0",                   tst2, '@', '\0',tst2_len - 1);
	print_test_memrep("memrep              ",	FALSE, "Un ange mange de la fange.\0", tst3, '?', 'o', tst3_len - 1);
	print_test_memrep("memrep              ",	FALSE, "Un ange mange de la fange.\0", tst3, '?', 'o', tst3_len - 1);
	print_test_memrep("memrep              ",	FALSE, "Un an_e man_e de la fan_e.\0", tst3, 'g', '_', tst3_len - 1);
	print_test_memrep("memrep (old = '\\0') ",	FALSE, tst1,                           tst1, '\0','a', 16);
	print_test_memrep("memrep (n = 0)      ",	FALSE, tst1,                           tst1, ' ', 'a', 0);
//	print_test_memrep("memrep (n > len)    ",	TRUE,  segstr,                         tst3, '_', 'a', tst3_len + 64);
	print_test_memrep("memrep (null str)   ",	TRUE,  segstr,                         NULL, '_', 'a', 16);
	free(tst1);
	free(tst2);
	free(tst3);
}
#endif



#ifdef			ft_getbits
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



int		testsuite_memory(void)
{
	print_suite_title("memory");

#ifdef ft_memset
	test_memset();
#endif
#ifdef ft_memclr
	test_memclr(); // = bzero
#endif

#ifdef ft_memcpy
	test_memcpy();
#endif
#ifdef ft_memccpy
	test_memccpy();
#endif
#ifdef ft_memmove
	test_memmove();
#endif

#ifdef ft_memchr
	test_memchr();
#endif
#ifdef ft_memcmp
	test_memcmp();
#endif

	print_nonstd();

#ifdef ft_memalloc
	test_memalloc();
#endif
#ifdef ft_memnew
	test_memnew();
#endif
#ifdef ft_memfree
//	test_memfree();
#endif
#ifdef ft_memdel
	test_memdel();
#endif

#ifdef ft_memdup
	test_memdup();
#endif

#ifdef ft_memswap
//	test_memswap();
#endif

#ifdef ft_memrep
	test_memrep();
#endif

#ifdef ft_getbits
//	test_getbits();
#endif

	printf("\n");
	return (OK);
}
