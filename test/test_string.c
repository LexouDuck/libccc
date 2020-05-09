
#include "test.h"

/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/



/*
**	char*	ft_strnew(size_t size);
*/
void	print_test_strnew(char const* test_name, int can_segfault,
		size_t n)
{
	t_timer t = {0};
	char* result;
	int error = FALSE;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result = ft_strnew(n);
	timer_clock(&t.end1); } else result = segstr;
	printf("\n%s -> ", test_name);
	if (result == NULL)
	{
		error = TRUE;
		printf(C_RED"\nERROR - The call to ft_strnew returned NULL."C_RESET);
	}
	for (size_t i = 0; i < n; ++i)
	{
		if (result[i])
		{
			error = TRUE;
			printf(C_RED"\nERROR - Every char should be '\\0', but '%c' was read at index %d."C_RESET, result[i], i);
		}
	}
	if (!error) printf(C_GREEN"OK!"C_RESET);
	if (result && result != segstr) free(result);
	print_timer_result(&t, FALSE);
}
void	test_strnew(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME      |CAN SEGV|TEST ARGS */
	print_test_strnew("strnew",        	FALSE,	12);
	print_test_strnew("strnew (n = 0)",	FALSE,	0);
}



/*
**	void	ft_strset(char *str, char c);
*/
void	print_test_strset(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc,
		char c)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_strset(dest_libft, c); timer_clock(&t.end1); } else dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);    strset(dest_libc,  c); timer_clock(&t.end2); } else dest_libc  = segstr;
	print_test_str(test_name, "strset arg", dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strset(void)
{
	char str1[] = "swag";
	char str2[] = "swag";
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strset("strset",           	FALSE,	"aaaa", str1, str2, 'a');
	print_test_strset("strset (null ptr)",	TRUE, 	segstr, NULL, NULL, 'a');
}



/*
**	void	ft_strclr(char *str);
*/
void	print_test_strclr(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_strclr(dest_libft); timer_clock(&t.end1); } else dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);    strclr(dest_libc);  timer_clock(&t.end2); } else dest_libc  = segstr;
	print_test_str(test_name, "strclr arg", dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strclr(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strclr("strclr",           	FALSE,	"\0",   str1, str2);
	print_test_strclr("strclr (null ptr)",	TRUE, 	segstr, NULL, NULL);
}



/*
**	void	ft_strdel(char** ptr);
*/
void	print_test_strdel(char const* test_name, int can_segfault,
		char const* expecting,
		char** dest_libft,
		char** dest_libc)
{
	t_timer t = {0};
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); ft_strdel(dest_libft); timer_clock(&t.end1); } else *dest_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2);    strdel(dest_libc);  timer_clock(&t.end2); } else *dest_libc  = segstr;
	print_test_str(test_name, "strdel arg", *dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strdel(void)
{
	char* str1; if (!(str1 = malloc(32))) return ;
	char* str2; if (!(str2 = malloc(32))) return ;
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strdel("strdel",           	FALSE,	NULL, &str1, &str2);
	print_test_strdel("strdel (null ptr)",	TRUE, 	NULL, NULL,  NULL);
}



/*
**	char*	ft_strdup(char const* str);
*/
void	print_test_strdup(char const* test_name, int can_segfault,
		char const* src)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strdup(src); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strdup(src); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strdup return", result_libft, result_libc, can_segfault);
	if (result_libft && result_libft != segstr) free(result_libft);
	if (result_libc  && result_libc  != segstr) free(result_libc);
	print_timer_result(&t, TRUE);
}
void	test_strdup(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strdup("strdup",            	FALSE,	test1);
	print_test_strdup("strdup (empty str)",	FALSE,	"\0");
//	print_test_strdup("strdup (null str) ",	TRUE, 	NULL);
}



/*
**	char*	ft_strcpy(char* dest, char const* src);
*/
void	print_test_strcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strcpy(dest_libft, src); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strcpy(dest_libc,  src); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strcpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcpy return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strcpy(void)
{
	char str1[test2_len];
	char str2[test2_len];
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strcpy("strcpy            ",	FALSE,	str1, str2, test2);
	print_test_strcpy("strcpy (empty str)",	FALSE,	str1, str2, "\0");
	print_test_strcpy("strcpy (null dest)",	TRUE, 	NULL, NULL, test2);
	print_test_strcpy("strcpy (null src) ",	TRUE, 	str1, str2, NULL);
	print_test_strcpy("strcpy (both null)",	TRUE, 	NULL, NULL, NULL);
}



/*
**	char*	ft_strncpy(char* dest, char const* src, size_t n);
*/
void	print_test_strncpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strncpy(dest_libft, src, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strncpy(dest_libc,  src, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strncpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncpy return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strncpy(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION   | TEST NAME               | CAN SEGV | TEST ARGS */
	print_test_strncpy("strncpy                ",	FALSE,	str1, str2, test1,     test1_len);
	print_test_strncpy("strncpy (n = 0)        ",	FALSE,	str1, str2, test1,             0);
	print_test_strncpy("strncpy (n < src_len)  ",	FALSE,	str1, str2, test1, test1_len - 5);
	print_test_strncpy("strncpy (n > src_len)  ",	FALSE,	str1, str2, test2, test2_len + 5);
	print_test_strncpy("strncpy (several '\\0's)",	FALSE,	str1, str2, "Swag\0\0\0",      7);
	print_test_strncpy("strncpy (null dest)",     	TRUE, 	NULL, NULL, test1,             5);
	print_test_strncpy("strncpy (null src) ",     	TRUE, 	str1, str2, NULL,              5);
	print_test_strncpy("strncpy (both null)",     	TRUE, 	NULL, NULL, NULL,              5);
}



/*
**	size_t	ft_strlcpy(char* dest, char const* src, size_t size);
*/
void	print_test_strlcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t size)
{
	t_timer t = {0};
	size_t	result_libft;
	size_t	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strlcpy(dest_libft, src, size); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strlcpy(dest_libc,  src, size); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_str(test_name, "strlcpy 'dest' arg", dest_libft, dest_libc, can_segfault);
	print_test_size(NULL,     "strlcpy return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strlcpy(void)
{
	char str1[32];
	char str2[32];
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strlcpy("strlcpy          ",  	FALSE,	str1, str2, " shindeiru", 5);
	print_test_strlcpy("strlcpy (n = 0)  ",  	FALSE,	str1, str2, " shindeiru", 0);
	print_test_strlcpy("strlcpy (n < len)",  	FALSE,	str1, str2, " shindeiru", 15);
	print_test_strlcpy("strlcpy (n > len)",  	FALSE,	str1, str2, " shindeiru", 50);
	print_test_strlcpy("strlcpy (null dest)",	TRUE,	NULL, NULL, " shindeiru", 5);
	print_test_strlcpy("strlcpy (null src) ",	TRUE,	str1, str2, NULL,         5);
	print_test_strlcpy("strlcpy (both null)",	TRUE,	NULL, NULL, NULL,         5);
}



/*
**	char*	ft_strcat(char* dest, char const* src);
*/
void	print_test_strcat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strcat(dest_libft, src); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strcat(dest_libc,  src); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strcat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcat return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strcat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS */
	print_test_strcat("strcat",            	FALSE,	str1, str2, "Bob\0");
	print_test_strcat("strcat (null dest)",	TRUE,	NULL, NULL, "Bob\0");
	print_test_strcat("strcat (null src) ",	TRUE,	str1, str2, NULL);
	print_test_strcat("strcat (both null)",	TRUE,	NULL, NULL, NULL);
}



/*
**	char*	ft_strncat(char* dest, char const* src, size_t n);
*/
void	print_test_strncat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t n)
{
	t_timer t = {0};
	char* result_libft = NULL;
	char* result_libc  = NULL;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strncat(dest_libft, src, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strncat(dest_libc,  src, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strncat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncat return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strncat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, "Bob\0",    3);
	print_test_strncat("strncat (n = 0)  ",  	FALSE,	str1, str2, "Bobensen", 0);
	print_test_strncat("strncat (n < len)",  	FALSE,	str1, str2, "Bobensen", 3);
	print_test_strncat("strncat (n > len)",  	FALSE,	str1, str2, "Bob\0",    7);
	print_test_strncat("strncat (null dest)",	TRUE,	NULL, NULL, "Bob\0",    5);
	print_test_strncat("strncat (null src) ",	TRUE,	str1, str2, NULL,       5);
	print_test_strncat("strncat (both null)",	TRUE,	NULL, NULL, NULL,       5);
}



/*
**	size_t	ft_strlcat(char* dest, char const* src, size_t size);
*/
void	print_test_strlcat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		size_t size)
{
	t_timer t = {0};
	const int has_segfault = 0x7FFFFFFF;
	size_t	result_libft;
	size_t	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strlcat(dest_libft, src, size); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strlcat(dest_libc,  src, size); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_str(test_name, "strlcat 'dest' arg", dest_libft,   dest_libc, can_segfault);
	print_test_size(NULL,     "strlcat return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strlcat(void)
{
	char str1[32];
	char str2[32];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
printf("\n");
/*	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS */
	print_test_strlcat("strlcat          ",  	FALSE,	str1, str2, " shindeiru", 5);
	print_test_strlcat("strlcat (n = 0)  ",  	FALSE,	str1, str2, " shindeiru", 0);
	print_test_strlcat("strlcat (n < len)",  	FALSE,	str1, str2, " shindeiru", 15);
	print_test_strlcat("strlcat (n > len)",  	FALSE,	str1, str2, " shindeiru", 50);
	print_test_strlcat("strlcat (null dest)",	TRUE,	NULL, NULL, " shindeiru", 5);
	print_test_strlcat("strlcat (null src) ",	TRUE,	str1, str2, NULL,         5);
	print_test_strlcat("strlcat (both null)",	TRUE,	NULL, NULL, NULL,         5);
}



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/



/*
**	size_t	ft_strlen(char const *str);
*/
void	print_test_strlen(char const* test_name, int can_segfault,
		char const* str)
{
	t_timer t = {0};
	size_t	result_libft;
	size_t	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strlen(str); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strlen(str); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_size(test_name, "strlen return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strlen(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| TEST ARGS */
	print_test_strlen("strlen",           	FALSE,	test1);
	print_test_strlen("strlen",           	FALSE,	test2);
	print_test_strlen("strlen (null str)",	TRUE,	NULL);
}



/*
**	int		ft_strcmp(char const* str1, char const* str2);
*/
void	print_test_strcmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2)
{
	t_timer t = {0};
	int	result_libft;
	int	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strcmp(str1, str2); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strcmp(str1, str2); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_s32(test_name, "strcmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strcmp(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| TEST ARGS */
	print_test_strcmp("strcmp        ",    	FALSE,	test2, test3);
	print_test_strcmp("strcmp (equal)",    	FALSE,	test2, test2);
	print_test_strcmp("strcmp (null str1)",	TRUE,	NULL,  test3);
	print_test_strcmp("strcmp (null str2)",	TRUE,	test2, NULL);
	print_test_strcmp("strcmp (both null)",	TRUE,	NULL,  NULL);
}



/*
**	int		ft_strncmp(char const* str1, char const* str2, size_t n);
*/
void	print_test_strncmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2,
		size_t n)
{
	t_timer t = {0};
	int	result_libft;
	int	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strncmp(str1, str2, n); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strncmp(str1, str2, n); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_s32(test_name, "strncmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strncmp(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME              |CAN SEGV| TEST ARGS */
	print_test_strncmp("strncmp        ",    	FALSE,	test1,     test3,     7);
	print_test_strncmp("strncmp        ",    	FALSE,	"abc",     "abcdef",  3);
	print_test_strncmp("strncmp        ",    	FALSE,	test2 + 1, test3 + 3, 2);
	print_test_strncmp("strncmp (n = 0)",    	FALSE,	test2,     test3,     0);
	print_test_strncmp("strncmp (null str1)",	TRUE,	NULL,      test3,     5);
	print_test_strncmp("strncmp (null str2)",	TRUE,	test2,     NULL,      5);
	print_test_strncmp("strncmp (both null)",	TRUE,	NULL,      NULL,      5);
}



/*
**	t_bool	ft_strequ(char const* str1, char const* str2);
*/
void	print_test_strequ(char const* test_name, int can_segfault,
		int expecting,
		char const* str1,
		char const* str2)
{
	t_timer t = {0};
	t_bool	result_libft;
//	t_bool	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strequ(str1, str2); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strequ(str1, str2); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_bool(test_name, "_strequ return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strequ(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME            | CAN SEGV | EXPECTING                  | TEST ARGS */
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test1, test2) == 0), test1, test2);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test1, test1) == 0), test1, test1);
	print_test_strequ("strequ (empty str)", 	FALSE,	(strcmp(test1, "")    == 0), test1, "");
	print_test_strequ("strequ (null str1)", 	TRUE,	 0,                          NULL,  test2);
	print_test_strequ("strequ (null str2)", 	TRUE,	 0,                          test1, NULL);
	print_test_strequ("strequ (both null)", 	TRUE,	 1,                          NULL,  NULL);
}



/*
**	t_bool	ft_strnequ(char const* str1, char const* str2, size_t n)
*/
void	print_test_strnequ(char const* test_name, int can_segfault,
		int expecting,
		char const* str1,
		char const* str2,
		size_t n)
{
	t_timer t = {0};
	t_bool	result_libft;
//	t_bool	result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strnequ(str1, str2, n); timer_clock(&t.end1); } else can_segfault |= (1 << 1);
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strnequ(str1, str2, n); timer_clock(&t.end2); } else can_segfault |= (1 << 2);
	print_test_bool(test_name, "_strnequ return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strnequ(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME            | CAN SEGV | EXPECTING                       | TEST ARGS */
	print_test_strnequ("strnequ            ",	FALSE,	(strncmp(test1, test2,  5) == 0), test1, test2, 5);
	print_test_strnequ("strnequ            ",	FALSE,	(strncmp(test1, test1,  7) == 0), test1, test1, 7);
	print_test_strnequ("strnequ (empty str)",	FALSE,	(strncmp(test1, "",     5) == 0), test1, "",    5);
	print_test_strnequ("strnequ (n = 0)    ",	FALSE,	(strncmp(test1, test1,  0) == 0), test1, test1, 0);
	print_test_strnequ("strnequ (n > len)  ",	FALSE,	(strncmp(test1, test1, 30) == 0), test1, test1, 30);
	print_test_strnequ("strnequ (null str1)",	TRUE,	0,                                NULL,  test2, 7);
	print_test_strnequ("strnequ (null str2)",	TRUE,	0,                                test1, NULL,  7);
	print_test_strnequ("strnequ (both null)",	TRUE,	1,                                NULL,  NULL,  7);
}



/*
**	t_bool	ft_strhas(char const* str, char const* query);
*/
void	print_test_strhas(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str,
		char const* query)
{
	t_timer t = {0};
	t_bool result_libft;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strhas(str, query);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_bool(test_name, "_strhas", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhas(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME             |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_strhas("strhas               ",	FALSE,  TRUE,     "sweg my nigga", "mz");
	print_test_strhas("strhas               ",	FALSE,  TRUE,     "sweg my nigga", "aze");
	print_test_strhas("strhas               ",	FALSE,  FALSE,    "sweg my nigga", "z_u");
	print_test_strhas("strhas (null str)    ",	SEGV,   FALSE,     NULL, "mz");
	print_test_strhas("strhas (null charset)",	SEGV,   FALSE,     "sw", NULL);
	print_test_strhas("strhas (both null)   ",	SEGV,   FALSE,     NULL, NULL);
}



/*
**	t_bool	ft_strhasonly(char const* str, char const* query);
*/
void	print_test_strhasonly(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str,
		char const* query)
{
	t_timer t = {0};
	t_bool result_libft;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strhasonly(str, query);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_bool(test_name, "_strhasonly", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strhasonly(void)
{
printf("\n");
/*	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_strhasonly("strhasonly                ",	FALSE,  TRUE,    "sweg my nigga", "aiey gmnsw");
	print_test_strhasonly("strhasonly                ",	FALSE,  FALSE,   "sweg my nigga", "aiey gsw");
	print_test_strhasonly("strhasonly (empty str)    ",	FALSE,  TRUE,   "",     "z_u");
	print_test_strhasonly("strhasonly (empty charset)",	FALSE,  FALSE,   "sweg", "");
	print_test_strhasonly("strhasonly (null str)     ",	SEGV,   FALSE,   NULL, "mz");
	print_test_strhasonly("strhasonly (null charset) ",	SEGV,   FALSE,   "sw", NULL);
	print_test_strhasonly("strhasonly (both null)    ",	SEGV,   FALSE,   NULL, NULL);
}



/*
**	size_t	ft_strcount_char(char const* str, char c);
*/
void	print_test_strcount_char(char const* test_name, int can_segfault,
		size_t expecting,
		char const* str,
		char c)
{
	t_timer t = {0};
	size_t result_libft = 0;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strcount_char(str, c);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_size(test_name, "_strcount_char", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strcount_char(void)
{
printf("\n");
/*	| TEST FUNCTION         | TEST NAME                  |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_strcount_char("strcount_char            ",	FALSE,  3,       "sweg my nigga", 'g');
	print_test_strcount_char("strcount_char            ",	FALSE,  0,       "sweg my nigga", 'z');
	print_test_strcount_char("strcount_char (empty str)",	FALSE,  0,       "",              'a');
	print_test_strcount_char("strcount_char ('\\0 char')",	FALSE,  0,       "sweg",          '\0');
	print_test_strcount_char("strcount_char (null str) ",	SEGV,   0,       NULL,            'a');
}



/*
**	size_t	ft_strcount_str(char const* str, char const* query);
*/
void	print_test_strcount_str(char const* test_name, int can_segfault,
		size_t expecting,
		char const* str,
		char const* query)
{
	t_timer t = {0};
	size_t result_libft = 0;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strcount_str(str, query);
	timer_clock(&t.end1); } else can_segfault |= (1 << 1);
	print_test_size(test_name, "_strcount_str", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strcount_str(void)
{
printf("\n");
/*	| TEST FUNCTION        | TEST NAME                    |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_strcount_str("strcount_str              ",	FALSE,  3,         "sweg my nigga", "g");
	print_test_strcount_str("strcount_str              ",	FALSE,  1,         "sweg my nigga", "sweg");
	print_test_strcount_str("strcount_str              ",	FALSE,  0,         "sweg my nigga", "swef");
	print_test_strcount_str("strcount_str              ",	FALSE,  1,         "sweg my nigga", "gg");
	print_test_strcount_str("strcount_str (empty str)  ",	FALSE,  0,         "",              "g");
	print_test_strcount_str("strcount_str (empty query)",	FALSE,  0,         test1, "");
	print_test_strcount_str("strcount_str (null str)   ",	SEGV,   0,         NULL, "mz");
	print_test_strcount_str("strcount_str (null query) ",	SEGV,   0,         "sw", NULL);
	print_test_strcount_str("strcount_str (both null)  ",	SEGV,   0,         NULL, NULL);
}



/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/



/*
**	char*	ft_strchr(char const* str, int c);
*/
void	print_test_strchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	t_timer t = {0};
	char* result_libft;
	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strchr(str, c); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strchr(str, c); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strchr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strchr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS */
	print_test_strchr("strchr             ",	FALSE, test1, 'm');
	print_test_strchr("strchr             ",	FALSE, test1, '_');
	print_test_strchr("strchr (null query)",	FALSE, test3, '\0');
	print_test_strchr("strchr (null ptr)  ",	TRUE,  NULL,  'm');
}



/*
**	char*	ft_strstr(char const* str, char const* query);
*/
void	print_test_strstr(char const* test_name, int can_segfault,
		char const* str,
		char const* query)
{
	t_timer t = {0};
	char* result_libft;
	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strstr(str, query); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strstr(str, query); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strstr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strstr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS */
	print_test_strstr("strstr              ",	FALSE, test1, "mou ");
	print_test_strstr("strstr              ",	FALSE, test1, "??");
	print_test_strstr("strstr              ",	FALSE, test3, "???");
	print_test_strstr("strstr (empty query)",	FALSE, test3, "");
	print_test_strstr("strstr (null str)   ",	TRUE,  NULL,  "mou ");
	print_test_strstr("strstr (null query) ",	TRUE,  test1, NULL);
	print_test_strstr("strstr (both null)  ",	TRUE,  NULL,  NULL);
}



/*
**	char*	ft_strrchr(char const* str, int c);
*/
void	print_test_strrchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	t_timer t = {0};
	char* result_libft;
	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strrchr(str, c); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strrchr(str, c); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strrchr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strrchr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME               |CAN SEGV| TEST ARGS */
	print_test_strrchr("strrchr             ",	FALSE,   test1, 'm');
	print_test_strrchr("strrchr             ",	FALSE,   test1, '_');
	print_test_strrchr("strrchr (null query)",	FALSE,   test3, '\0');
	print_test_strrchr("strrchr (null ptr)  ",	TRUE,    NULL,  'm');
}



/*
**	char*	ft_strrstr(char const* str, char const* query);
*/
void	print_test_strrstr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query)
{
	t_timer t = {0};
	char* result_libft;
//	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strrstr(str, query); timer_clock(&t.end1); } else result_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strrstr(str, query); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "_strrstr return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strrstr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME              |CAN SEGV|    EXPECTING    | TEST ARGS */
	print_test_strrstr("strrstr              ",	FALSE, "mou shindeiru.\0", test1, "mou ");
	print_test_strrstr("strrstr              ",	FALSE, NULL,               test1, "??");
	print_test_strrstr("strrstr              ",	FALSE, NULL,               test3, "???");
	print_test_strrstr("strrstr (empty query)",	FALSE, NULL,               test3, "");
	print_test_strrstr("strrstr (null str)   ",	TRUE,  segstr,             NULL,  "mou ");
	print_test_strrstr("strrstr (null query) ",	TRUE,  segstr,             test1, NULL);
	print_test_strrstr("strrstr (both null)  ",	TRUE,  segstr,             NULL,  NULL);
}



/*
**	char*	ft_strnchr(char const* str, int c, size_t n);
*/
void	print_test_strnchr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		int c,
		size_t n)
{
	t_timer t = {0};
	char* result_libft;
//	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strnchr(str, c, n); timer_clock(&t.end1); } else result_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strnchr(str, c, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "_strnchr return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strnchr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME              |CAN SEGV|      EXPECTING      | TEST ARGS */
	print_test_strnchr("strnchr             ",	FALSE, "wa mou shindeiru.\0", test1, 'w', 16);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, '_', 16);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, 'w', 1);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, '_', 1);
	print_test_strnchr("strnchr (null query)",	FALSE,  NULL,                 test3, '\0', 16);
	print_test_strnchr("strnchr (n = 0)     ",	FALSE,  NULL,                 test1, 'w', 0);
	print_test_strnchr("strnchr (n = len)   ",	FALSE,  NULL,                 test1, '_', test1_len);
	print_test_strnchr("strnchr (n > len)   ",	FALSE,  NULL,                 test1, '_', test1_len + 32);
	print_test_strnchr("strnchr (null ptr)  ",	TRUE,   segstr,               NULL,  'm', 16);
}



/*
**	char*	ft_strnstr(char const* str, char const* query, size_t n);
*/
void	print_test_strnstr(char const* test_name, int can_segfault,
		char const* str,
		char const* query,
		size_t n)
{
	t_timer t = {0};
	char* result_libft;
	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strnstr(str, query, n); timer_clock(&t.end1); } else result_libft = segstr;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =    strnstr(str, query, n); timer_clock(&t.end2); } else result_libc  = segstr;
	print_test_str(test_name, "strnstr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
}
void	test_strnstr(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME             |CAN SEGV| EXPECTING | TEST ARGS */
	print_test_strnstr("strnstr              ",	FALSE, test1, "mou ", 16);
	print_test_strnstr("strnstr              ",	FALSE, test1, "??",   test1_len);
	print_test_strnstr("strnstr              ",	FALSE, test3, "???",  test3_len);
	print_test_strnstr("strnstr (empty query)",	FALSE, test1, "\0",   16);
	print_test_strnstr("strnstr (n = 0)      ",	FALSE, test1, "mou ", 0);
	print_test_strnstr("strnstr (n = len)    ",	FALSE, test1, "_",    test1_len);
	print_test_strnstr("strnstr (n > len)    ",	FALSE, test1, "_",    test1_len + 32);
	print_test_strnstr("strnstr (null str)   ",	TRUE,  NULL,  "mou ", 16);
	print_test_strnstr("strnstr (null query) ",	TRUE,  test1, NULL,   16);
	print_test_strnstr("strnstr (both null)  ",	TRUE,  NULL,  NULL,   16);
}



/*
**	char	*ft_strremove(char const *str, char const *query);
*/
void	print_test_strremove(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strremove(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strtoescape(char const *str);
*/
void	print_test_strtoescape(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strtoescape(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strrep_char(char const *str, char old, char new);
*/
void	print_test_strrep_char(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strrep_char(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strrep_charset(char const *str, char const *old, char const *new);
*/
void	print_test_strrep_charset(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strrep_charset(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strrep_str(char const *str, char const *old, char const *new);
*/
void	print_test_strrep_str(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strrep_string(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/



/*
**	char	*ft_strtrim(char const *str);
*/
void	print_test_strtrim(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	t_timer t = {0};
	char* result_libft;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strtrim(str, charset);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_strtrim", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libft && result_libft != segstr) free(result_libft);
}
void	test_strtrim(void)
{
printf("\n");
/*	| TEST FUNCTION   | TEST NAME                |CAN SEGV| EXPECTING                     | TEST ARGS */
	print_test_strtrim("strtrim                  ", FALSE, "swag",                          " \t\n\r\v\f", "   swag\n");
	print_test_strtrim("strtrim                  ", FALSE, "FOR THE\tHORDE !",              " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim("strtrim                  ", FALSE, "do u even\ntrim bruh",          " \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim("strtrim (only whitespace)", FALSE, "",                              " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim("strtrim (empty string)   ", FALSE, "",                              " \t\n\r\v\f", "");
	print_test_strtrim("strtrim (empty charset)  ", FALSE, "   swag\n",                     "",            "   swag\n");
	print_test_strtrim("strtrim (null string)    ", TRUE,  segstr,                          "ab", NULL);
	print_test_strtrim("strtrim (null charset)   ", TRUE,  segstr,                          NULL, " swag \n");
	print_test_strtrim("strtrim (both null)      ", TRUE,  segstr,                          NULL, NULL);
}



/*
**	char	*ft_strtrim_l(char const *str, char const *charset);
*/
void	print_test_strtrim_l(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strtrim_l(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strtrim_r(char const *str, char const *charset);
*/
void	print_test_strtrim_r(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strtrim_r(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strpad(char const *str, char c, size_t length);
*/
void	print_test_strpad(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strpad(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strpad_l(char const *str, char c, size_t length);
*/
void	print_test_strpad_l(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strpad_l(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strpad_r(char const *str, char c, size_t length);
*/
void	print_test_strpad_r(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strpad_r(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/



/*
**	char	*ft_strrev(char const *str);
*/
void	print_test_strrev(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str)
{
	t_timer t = {0};
	char* result_libft;
//	char* result_libc;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strrev(str); timer_clock(&t.end1); } else result_libft = segstr;
//	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libc  =    strrev(str); timer_clock(&t.end1); } else result_libc  = segstr;
	print_test_str(test_name, "_strrev", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libft && result_libft != segstr) free(result_libft);
//	if (result_libc  && result_libc  != segstr) free(result_libc);
}
void	test_strrev(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING              | TEST ARGS */
	print_test_strrev("strrev (even len)",	FALSE, ".uriednihs uom aw eamO", test1);
	print_test_strrev("strrev (odd len) ",	FALSE, "???inaN",                test2);
	print_test_strrev("strrev (null ptr)",	TRUE,  segstr,                   NULL);
}



/*
**	char	*ft_strjoin(char const *str1, char const *str2);
*/
void	print_test_strjoin(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str1,
		char const *str2)
{
	t_timer t = {0};
	char* result_libft;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strjoin(str1, str2);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_strjoin", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libft && result_libft != segstr) free(result_libft);
}
void	test_strjoin(void)
{
printf("\n");
/*	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING                     | TEST ARGS */
	print_test_strjoin("strjoin",            	FALSE, "Omae wa mou shindeiru.Nani???", test1, test2);
	print_test_strjoin("strjoin (null str1)",	TRUE,   segstr,                         NULL,  test2);
	print_test_strjoin("strjoin (null str2)",	TRUE,   segstr,                         test1, NULL);
	print_test_strjoin("strjoin (both null)",	TRUE,   segstr,                         NULL,  NULL);
}



/*
**	char	*ft_strinsert(char **dest, char const *src, size_t offset);
*/
void	print_test_strinsert(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strinsert(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}



/*
**	char	*ft_strsub(char const *str, size_t offset, size_t n);
*/
void	print_test_strsub(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		size_t offset,
		size_t n)
{
	t_timer t = {0};
	char* result_libft;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strsub(str, offset, n);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_strsub", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	if (result_libft && result_libft != segstr) free(result_libft);
}
void	test_strsub(void)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME             |CAN SEGV|EXPECTING| TEST ARGS */
	print_test_strsub("strsub            ",   	FALSE, "wa mo",  test1, 5, 5);
	print_test_strsub("strsub (len = 0)  ",   	FALSE, "",       test1, 5, 0);
	print_test_strsub("strsub (len > str)",   	FALSE, NULL,     test1, 5, 100);
	print_test_strsub("strsub (offset > str)",	TRUE,  NULL,     test1, 100, 5);
	print_test_strsub("strsub (null ptr)    ",	TRUE,  segstr,   NULL,  5, 5);
}



void	strtolower(char* c)
{
	if (isupper(*c))
		*c = tolower(*c);
}

void	strtolower_1on2(size_t i, char* c)
{
	if (i % 2 == 0 && isupper(*c))
		*c = tolower(*c);
}

char	strtoupper(char c)
{
	if (islower(c))
		 return (toupper(c));
	else return (c);
}

char	strtoupper_1on2(size_t i, char c)
{
	if (i % 2 == 1 && islower(c))
		 return (toupper(c));
	else return (c);
}



/*
**	void	ft_striter(char *str, void (*f)(char *));
*/
void	print_test_striter(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(char*))
{
	t_timer t = {0};
	char* result_libft = str == NULL ? NULL : strdup(str);
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_striter(result_libft, f);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_striter", result_libft, expecting, can_segfault);
	if (result_libft && result_libft != segstr) free(result_libft);
	print_timer_result(&t, FALSE);
}
void	test_striter(void)
{
printf("\n");
/*	| TEST FUNCTION   | TEST NAME            |CAN SEGV| EXPECTING                | TEST ARGS */
	print_test_striter("striter            ",	FALSE, "omae wa mou shindeiru.",  "omAe wA mOu ShINDeIRu.", &strtolower);
	print_test_striter("striter (null str) ",	TRUE,   segstr,                    NULL,                    &strtolower);
	print_test_striter("striter (null func)",	TRUE,   segstr,                   "omAe wA mOu ShINDeIRu.", NULL);
	print_test_striter("striter (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}



/*
**	void	ft_striteri(char *str, void (*f)(size_t, char *));
*/
void	print_test_striteri(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(size_t, char*))
{
	t_timer t = {0};
	char* result_libft = str == NULL ? NULL : strdup(str);
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		ft_striteri(result_libft, f);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_striteri", result_libft, expecting, can_segfault);
	if (result_libft && result_libft != segstr) free(result_libft);
	print_timer_result(&t, FALSE);
}
void	test_striteri(void)
{
printf("\n");
/*	| TEST FUNCTION    | TEST NAME            |CAN SEGV| EXPECTING                | TEST ARGS */
	print_test_striteri("striteri            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.",  "OMAE WA MOU SHINDEIRU.", &strtolower_1on2);
	print_test_striteri("striteri (null str) ",	TRUE,   segstr,                    NULL,                    &strtolower_1on2);
	print_test_striteri("striteri (null func)",	TRUE,   segstr,                   "OMAE WA MOU SHINDEIRU.", NULL);
	print_test_striteri("striteri (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}



/*
**	char*	ft_strmap(char const* str, char (*f)(char));
*/
void	print_test_strmap(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char (*f)(char))
{
	t_timer t = {0};
	char* result_libft = NULL;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strmap(str, f);
	timer_clock(&t.end1); } else result_libft = segstr;
	print_test_str(test_name, "_strmap", result_libft, expecting, can_segfault);
	if (result_libft && result_libft != segstr) free(result_libft);
	print_timer_result(&t, FALSE);
}
void	test_strmap(void)
{
printf("\n");
/*	| TEST FUNCTION   | TEST NAME         |CAN SEGV| EXPECTING                | TEST ARGS */
	print_test_strmap("strmap            ",	FALSE, "OMAE WA MOU SHINDEIRU.",  "omae wa mou shindeiru.", &strtoupper);
	print_test_strmap("strmap (null str) ",	TRUE,   segstr,                    NULL,                    &strtoupper);
	print_test_strmap("strmap (null func)",	TRUE,   segstr,                   "omae wa mou shindeiru.", NULL);
	print_test_strmap("strmap (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}



/*
**	char*	ft_strmapi(char const* str, char (*f)(size_t, char));
*/
void	print_test_strmapi(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char (*f)(size_t, char))
{
	t_timer t = {0};
	char* result_libft = NULL;
	segfault = setjmp(restore);
	if (!segfault) { timer_clock(&t.start1);
		result_libft = ft_strmapi(str, f); timer_clock(&t.end1); }  else result_libft = segstr;
	print_test_str(test_name, "_strmapi", result_libft, expecting, can_segfault);
	if (result_libft && result_libft != segstr) free(result_libft);
	print_timer_result(&t, FALSE);
}
void	test_strmapi(void)
{
printf("\n");
/*	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING                | TEST ARGS */
	print_test_strmapi("strmapi            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.",  "omae wa mou shindeiru.", &strtoupper_1on2);
	print_test_strmapi("strmapi (null str) ",	TRUE,   segstr,                    NULL,                    &strtoupper_1on2);
	print_test_strmapi("strmapi (null func)",	TRUE,   segstr,                   "omae wa mou shindeiru.", NULL);
	print_test_strmapi("strmapi (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}









int		test_string(void)
{
	char*	str1;
	char*	str2;
	char const test1[] = "Omae wa mou shindeiru.";		size_t test1_len = strlen(test1) + 1;
	char const test2[] = "Nani???";						size_t test2_len = strlen(test2) + 1;
	char const test3[] = "Un ange mange de la fange.";	size_t test3_len = strlen(test3) + 1;
	char**	strls;

printf("\n");

	printf("       .----------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_string   }===---\n");
	printf("       '----------------------------'       \n");



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
//	test_strtoescape(str);
//	test_strrep_char(str, old, new);
//	test_strrep_charset(str, old, new);
//	test_strrep_str(str, old, new);

	test_strtrim();
//	test_strtrim_l();
//	test_strtrim_r();
//	test_strpad();
//	test_strpad_l();
//	test_strpad_r();

	test_strrev();
	test_strjoin();
//	test_strinsert();
	test_strsub();
	test_striter();
	test_striteri();
	test_strmap();
	test_strmapi();

printf("\n");

	return (0);
}
