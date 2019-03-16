
#include "test.h"

/*
**	void*	ft_memalloc(size_t size);
*/
void	print_test_memalloc(char const* test_name, int can_segfault,
		size_t n)
{
	t_timer t = {0};
	char* result;
	int error = FALSE;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result = (char*)ft_memalloc(n); timer_clock(&t.end1); } else result = segstr;
	printf("\n%s -> ", test_name);
	if (result == NULL)
	{
		error = TRUE;
		printf(C_RED"\nERROR - The call to ft_memalloc returned NULL."RESET);
	}
	for (size_t i = 0; i < n; ++i)
	{
		if (result[i])
		{
			error = TRUE;
			printf(C_RED"\nERROR - Every char should be '\\0', but '%c' was read at index %d."RESET, result[i], i);
		}
	}
	if (!error) printf(C_GREEN"OK!"RESET);
	if (result) free(result);
	print_timer_result(&t, FALSE);
}
void	test_memalloc(void)
{
printf("\n");
/*	| TEST FUNCTION    | TEST NAME        |CAN SEGV|TEST ARGS */
	print_test_memalloc("memalloc        ",	FALSE,	8);
	print_test_memalloc("memalloc (n = 0)",	FALSE,	0);
}



/*
**	void*	ft_memset(void *ptr, int byte, size_t n);
*/
void	print_test_memset(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		int byte,
		size_t n)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_memset(dest_libft, byte, n); timer_clock(&t.end1); } else dest_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);    memset(dest_libc,  byte, n); timer_clock(&t.end2); } else dest_libc  = segstr;
	print_test_mem(test_name, "memset 'dest' arg", dest_libft, dest_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memset(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_memset("memset (str)  ",    FALSE,	str1,  str2,  'a',    7);
//	print_test_memset("memset (uint) ",    FALSE,	&na,   &nb,   0xBBAA, 4);
	print_test_memset("memset (n = 0)",    FALSE,	str1,  str2,  '\0',   0);
	print_test_memset("memset (null ptr)", TRUE, 	str1,  str2,  '_',    5);
}



/*
**	void	ft_memclr(void *ptr, size_t n);
*/
void	print_test_memclr(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		size_t n)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_memclr(dest_libft, n); timer_clock(&t.end1); } else dest_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);     bzero(dest_libc,  n); timer_clock(&t.end2); } else dest_libc  = segstr;
	print_test_mem(test_name, "memclr/bzero arg",                       dest_libft,     dest_libc,     n, can_segfault);
	print_test_mem(NULL,      "memclr/bzero (region after the '\\0's)", dest_libft + n, dest_libc + n, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memclr(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
printf("\n");
/*	| TEST FUNCTION  | TEST NAME                | CAN SEGV | TEST ARGS */
	print_test_memclr("memclr/bzero        ",   	FALSE,	str1, str2, 2);
	print_test_memclr("memclr/bzero (n = 0)",   	FALSE,	str1, str2, 0);
	print_test_memclr("memclr/bzero (null ptr)",	TRUE, 	str1, str2, 2);
}



/*
**	void	ft_memdel(void **ptr);
*/
void	print_test_memdel(char const* test_name, int can_segfault,
		void **ptr)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_memdel(ptr); timer_clock(&t.end1); } else *ptr = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);    memdel(ptr); timer_clock(&t.end2); } else *ptr = segstr;
	print_test_mem(test_name, "memdel arg", *ptr, NULL, 0, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_memdel(void)
{
	size_t const length = 16;
	void* test = (void*)malloc(length);
	bzero(test, length);
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_memdel("memdel",	          	FALSE,	&test);
//	print_test_memdel("memdel (null arg)",	FALSE,	&test);
//	print_test_memdel("memdel (null ptr)",	FALSE,	NULL);
}



/*
**	void*	ft_memcpy(void *dest, const void *src, size_t n);
*/
void	print_test_memcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memcpy(dest_libft, src, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memcpy(dest_libc,  src, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_mem(test_name, "memcpy 'dest' arg", dest_libft,   dest_libc,   n, can_segfault);
	print_test_mem(NULL,      "memcpy return",     result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memcpy(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
printf("\n");
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_memcpy("memcpy (str)  ",    	FALSE,	str1, str2, test2, test2_len);
//	print_test_memcpy("memcpy (uint) ",    	FALSE,	&na,  &nb,  &n,    sizeof(n));
	print_test_memcpy("memcpy (n = 0)",    	FALSE,	str1, str2, test2, 0);
	print_test_memcpy("memcpy (null dest)",	TRUE, 	NULL, NULL, test2, test2_len);
	print_test_memcpy("memcpy (null src) ",	TRUE, 	str1, str2, NULL,  test2_len);
	print_test_memcpy("memcpy (both null)",	TRUE, 	NULL, NULL, NULL,  test2_len);
}



/*
**	void*	ft_memccpy(void *dest, const void *src, int byte, size_t n);
*/
void	print_test_memccpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		char c,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memccpy(dest_libft, src, c, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memccpy(dest_libc,  src, c, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_mem(test_name, "memccpy 'dest' arg", dest_libft,   dest_libc,   n, can_segfault); if (c !='\0')
	print_test_mem(NULL,      "memccpy return",     result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memccpy(void)
{
	char str1[] = "Omae wa mou shindeiru. Nani ???\0";
	char str2[] = "Omae wa mou shindeiru. Nani ???\0";
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_memccpy("memccpy (str)     ", 	FALSE,	str1, str2, test3, 'e',  test3_len);
//	print_test_memccpy("memccpy (uint)    ", 	FALSE,	&na,  &nb,  &n,    0xAA, 10);
	print_test_memccpy("memccpy (c = '\\0')",	FALSE,	str1, str2, test3, '\0', test3_len);
	print_test_memccpy("memccpy (null dest)",	TRUE, 	NULL, NULL, test3, 'e',  test3_len);
	print_test_memccpy("memccpy (null src) ",	TRUE, 	str1, str2, NULL,  'e',  5);
	print_test_memccpy("memccpy (both null)",	TRUE, 	NULL, NULL, NULL,  'e',  5);
}



/*
**	void*	ft_memmove(void *dest, const void *src, size_t n);
*/
void	print_test_memmove(char const* test_name, int can_segfault, int show_dest_arg,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memmove(dest_libft, src, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memmove(dest_libc,  src, n); timer_clock(&t.end2); } else result_libc  = segstr;
	if (show_dest_arg)
	print_test_mem(test_name,                    "memmove 'dest' arg", dest_libft,   dest_libc, n, can_segfault);
	print_test_mem(show_dest_arg ? NULL : test_name, "memmove return", result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memmove(void)
{
	char str1[] = "Omae wa mou shindeiru.";
	char str2[] = "Omae wa mou shindeiru.";
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           |CAN SEGV| TEST'dest'? | TEST ARGS */
	print_test_memmove("memmove (str)  ",    	FALSE,	TRUE, 		str1, str2, test2, test2_len);
	print_test_memmove("memmove (n = 0)",    	FALSE,	TRUE, 		str1, str2, test1, 0);
	print_test_memmove("memmove (null src) ",	TRUE, 	TRUE, 		str1, str2, NULL,  5);
	print_test_memmove("memmove (null dest)",	TRUE, 	FALSE,		NULL, NULL, test1, 5);
	print_test_memmove("memmove (both null)",	TRUE, 	FALSE,		NULL, NULL, NULL,  5);
/*	TODO change the testing function so that the following test can be done with a simple one-line function call
	segfault = setjmp(restore); if (!segfault) sra = ft_memmove(str1 + 3, str1, test1_len - 5); else sra = segstr;
	segfault = setjmp(restore); if (!segfault) srb =    memmove(str2 + 3, str2, test1_len - 5); else srb = segstr;
	print_test_str("memmove (overlapping)", "memmove arg",    str1,  str2,  FALSE);
	print_test_str(NULL,                    "memmove return", sra,   srb,   FALSE);
*/
}



/*
**	void*	ft_memchr(const void *ptr, int byte, size_t n);
*/
void	print_test_memchr(char const* test_name, int can_segfault,
		char const* str,
		char c,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memchr(str, c, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memchr(str, c, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_mem(test_name, "memchr return", result_libft, result_libc, n, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memchr(void)
{
printf("\n");
//	na = 0xFFAABBCC;
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_memchr("memchr (str)  ",   	FALSE,	test1, 'u',  test1_len);
	print_test_memchr("memchr (n = 0)",   	FALSE,	test1, 'u',  0);
//	print_test_memchr("memchr (uint) ",   	FALSE,	&na,   0xBB, 4);
	print_test_memchr("memchr (null ptr)",	TRUE, 	NULL,  'c',  4);
}



/*
**	int		ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
*/
void	print_test_memcmp(char const* test_name, int can_segfault,
		char const* test1,
		char const* test2,
		size_t n)
{
	t_timer t = {0};
	const int has_segfault = 0x7FFFFFFF;
	int result_libft;
	int result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memcmp(test1, test2, n); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memcmp(test1, test2, n); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_s32(test_name, "memcmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_memcmp(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          | CAN SEGV | TEST ARGS */
	print_test_memcmp("memcmp (str)  ",    	FALSE,		test2, test3, test3_len);
	print_test_memcmp("memcmp (n = 0)",    	FALSE,		test2, test3, 0);
//	print_test_memcmp("memcmp (uint) ",    	FALSE,		&na,   &nb,   4);
	print_test_memcmp("memcmp (null str1)",	SEGV,		NULL,  test3, test3_len);
	print_test_memcmp("memcmp (null str2)",	SEGV, 		test2, NULL,  test3_len);
	print_test_memcmp("memcmp (both null)",	SEGV, 		NULL,  NULL,  test3_len);
	// note that some implementations of memcmp can know the type of argument in input,
	// so they actually return *(int*)nra - *(int*)nrb -> not just considering memory as
	// one continous sequence of bytes, like is implied in the man pages for memcmp().
}



/*
**	void*	ft_memdup(void const* ptr, size_t n);
*/
void	print_test_memdup(char const* test_name, int can_segfault,
		char const* expecting,
		char const* src,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
//	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_memdup(src, n); timer_clock(&t.end1); } else result_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    memdup(src, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_mem(test_name, "_memdup return", result_libft, expecting, n, can_segfault);
	if (result_libft) free(result_libft);
//	if (result_libc)  free(result_libc);
	print_timer_result(&t, FALSE);
}
void	test_memdup(void)
{
printf("\n");
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
	print_test_memdup("memdup (str)      ",	FALSE,	test1,		test1, test1_len);
	print_test_memdup("memdup (empty str)",	FALSE,	"\0", 		"\0",  1);
	print_test_memdup("memdup (n = 0)    ",	FALSE,	test1,		test1, 0);
	print_test_memdup("memdup (null ptr)", 	TRUE, 	NULL, 		NULL,  test1_len);
}



/*
**	int		ft_swap(void *ptr1, void *ptr2, size_t size);
*/
void	print_test_swap(void)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_swap(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	t_u64	ft_getbits(t_u64 value, int bit, int length);
*/
void	print_test_getbits(void)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_getbits(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



int		test_memory(void)
{
	t_u32	n = 0xFFFFAAAA;
	t_u32	na;
	t_u32	nb; 
	t_u32*	nra;
	t_u32*	nrb;
	t_u64	la;
	t_u64	lb;
	char*	str1;
	char*	str2;

	printf("\n");

	printf("       .----------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_memory   }===---\n");
	printf("       '----------------------------'       \n");

	test_memset();
	test_memclr(); // = bzero
	test_memcpy();
	test_memccpy();
	test_memmove();
	test_memchr();
	test_memcmp();

	print_nonstd();

	test_memalloc();
	test_memdel();
	test_memdup();
	test_swap();
	test_getbits();

	printf("\n");
	return (OK);
}
