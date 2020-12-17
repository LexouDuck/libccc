
#include <ctype.h>
#include <string.h>

#include "libft_string.h"

#include "test.h"



/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

#ifdef			ft_strnew
void	print_test_strnew(char const* test_name, int can_segfault,
		t_size n)
{
	TEST_PERFORM_RESULT(strnew, n);
	print_test_alloc(test_name, "strnew", result_libft, n);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("n=%lu", n)
	TEST_FREE()
}
void	test_strnew(void)
{
//	| TEST FUNCTION  | TEST NAME           |CAN SEGV|TEST ARGS
	print_test_strnew("strnew             ", FALSE,	12);
	print_test_strnew("strnew (n = 0xFFFF)", FALSE,	0xFFFF);
	print_test_strnew("strnew (n = 0)     ", FALSE,	0);
}
#endif



#ifdef			ft_strset
void	print_test_strset(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc,
		char c)
{
	TEST_PERFORM(dest_libft, strset, dest_libft, c)
	print_test_str(test_name, "strset arg", dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c'", dest_libft, c, c)
}
void	test_strset(void)
{
	char str1[] = "swag";
	char str2[] = "swag";
//	| TEST FUNCTION  | TEST NAME         |CAN SEGV| EXPECT | TEST ARGS
	print_test_strset("strset",             FALSE, "aaaa",   str1, str2, 'a');
	print_test_strset("strset",             FALSE, "____",   str1, str2, '_');
	print_test_strset("strset (c = '\\0')", FALSE, "\0\0\0", str1, str2, '\0');
	print_test_strset("strset (null ptr)",  TRUE,  segstr,   NULL, NULL, 'a');
}
#endif


#ifdef			ft_strclr
void	print_test_strclr(char const* test_name, int can_segfault,
		char const* expecting,
		char* dest_libft,
		char* dest_libc)
{
	TEST_PERFORM(dest_libft, strclr, dest_libft)
	print_test_str(test_name, "strclr arg", dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\"", dest_libft)
}
void	test_strclr(void)
{
	char str1[32] = "______________________________";
	char str2[32] = "______________________________";
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_strclr("strclr",           	FALSE,	"",     str1 + 20, str2 + 20);
	print_test_strclr("strclr",           	FALSE,	"",     str1 + 10, str2 + 10);
	print_test_strclr("strclr",           	FALSE,	"",     str1, str2);
	print_test_strclr("strclr (null ptr)",	TRUE, 	segstr, NULL, NULL);
}
#endif


#ifdef			ft_strdel
void	print_test_strdel(char const* test_name, int can_segfault,
		char const* expecting,
		char** dest_libft,
		char** dest_libc)
{
	TEST_PERFORM(*dest_libft, strdel, dest_libft)
	print_test_str(test_name, "strdel arg", *dest_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("ptr=%p (str=\"%s\")", dest_libft, *dest_libft)
}
void	test_strdel(void)
{
	char* str1; if (!(str1 = malloc(32))) return ;
	char* str2; if (!(str2 = malloc(32))) return ;
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_strdel("strdel",           	FALSE,	NULL, &str1, &str2);
	print_test_strdel("strdel (null ptr)",	TRUE, 	NULL, NULL,  NULL);
}
#endif


#ifdef			ft_strdup
void	print_test_strdup(char const* test_name, int can_segfault,
		char const* src)
{
	TEST_PERFORM_RESULT_LIBC(strdup, src)
	print_test_str(test_name, "strdup return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("src=\"%s\"", src)
	TEST_FREE_LIBC()
}
void	test_strdup(void)
{
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_strdup("strdup",            	FALSE,	test1);
	print_test_strdup("strdup",            	FALSE,	test2);
	print_test_strdup("strdup",            	FALSE,	test3);
	print_test_strdup("strdup",            	FALSE,	"_");
	print_test_strdup("strdup (empty str)",	FALSE,	"");
//	print_test_strdup("strdup (null str) ",	TRUE, 	NULL); // TODO The test here fails because there is an intentional design difference
}
#endif



#ifdef			ft_strcpy
void	print_test_strcpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	TEST_PERFORM_RESULT_LIBC_DEST(strcpy, src)
	print_test_str(test_name, "strcpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcpy return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\"", dest_libft, src)
}
void	test_strcpy(void)
{
	char str1[64];
	char str2[64];
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_strcpy("strcpy            ",	FALSE,	str1, str2, test1);
	print_test_strcpy("strcpy            ",	FALSE,	str1, str2, test2);
	print_test_strcpy("strcpy            ",	FALSE,	str1, str2, test3);
	print_test_strcpy("strcpy (empty str)",	FALSE,	str1, str2, "");
	print_test_strcpy("strcpy (null dest)",	TRUE, 	NULL, NULL, test2);
	print_test_strcpy("strcpy (null src) ",	TRUE, 	str1, str2, NULL);
	print_test_strcpy("strcpy (both null)",	TRUE, 	NULL, NULL, NULL);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_strncpy
void	print_test_strncpy(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC_DEST(strncpy, src, n)
	print_test_str(test_name, "strncpy 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncpy return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", n=%lu", dest_libft, src, n)
}
void	test_strncpy(void)
{
	char str1[32];
	char str2[32];
//	| TEST FUNCTION   | TEST NAME               | CAN SEGV | TEST ARGS
	print_test_strncpy("strncpy                ",	FALSE,	str1, str2, test1,     test1_len);
	print_test_strncpy("strncpy                ",	FALSE,	str1, str2, test2,     test2_len);
	print_test_strncpy("strncpy                ",	FALSE,	str1, str2, test3,     test3_len);
	print_test_strncpy("strncpy (n = 0)        ",	FALSE,	str1, str2, test1,             0);
	print_test_strncpy("strncpy (n < src_len)  ",	FALSE,	str1, str2, test1, test1_len - 5);
	print_test_strncpy("strncpy (n > src_len)  ",	FALSE,	str1, str2, test2, test2_len + 5);
	print_test_strncpy("strncpy (several '\\0's)",	FALSE,	str1, str2, "Swag\0\0\0",      7);
	print_test_strncpy("strncpy (null dest)",     	TRUE, 	NULL, NULL, test1,             5);
	print_test_strncpy("strncpy (null src) ",     	TRUE, 	str1, str2, NULL,              5);
	print_test_strncpy("strncpy (both null)",     	TRUE, 	NULL, NULL, NULL,              5);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_strlcpy
void	print_test_strlcpy(char const* test_name, int can_segfault,
		t_size expecting,
		char const * expecting_dest,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size size)
{
#ifdef __APPLE__
	TEST_PERFORM_RESULT_TYPE_LIBC_DEST(t_size, strlcpy, src, size)
	print_test_str(test_name, "strlcpy 'dest' arg", dest_libft, dest_libc, can_segfault);
	print_test_size(NULL,     "strlcpy return", result_libft, result_libc, can_segfault);
#else
	TEST_PERFORM_RESULT_TYPE_DEST(t_size, strlcpy, src, size)
	print_test_str(test_name, "_strlcpy 'dest' arg", dest_libft,   expecting_dest, can_segfault);
	print_test_size(NULL,     "_strlcpy return",     result_libft, expecting,      can_segfault);
#endif
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", size=%lu", dest_libft, src, size)
}
void	test_strlcpy(void)
{
	char str1[32] = "______________________________";
	char str2[32] = "______________________________";
//	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING         | TEST ARGS
	print_test_strlcpy("strlcpy               ", FALSE,	test1_len-1, test1, str1, str2, test1, test1_len);
	print_test_strlcpy("strlcpy               ", FALSE,	test2_len-1, test2, str1, str2, test2, test2_len);
	print_test_strlcpy("strlcpy               ", FALSE,	test3_len-1, test3, str1, str2, test3, test3_len);
	print_test_strlcpy("strlcpy               ", FALSE,	10, " shi",         str1, str2, " shindeiru", 5);
	print_test_strlcpy("strlcpy               ", FALSE,	10, "testite",      str1, str2, "testitesty", 8);
	print_test_strlcpy("strlcpy (chars > 0x7F)", FALSE,	2,  "\x12",         str1, str2, "\x12\xAB\0", 2);
	print_test_strlcpy("strlcpy (n = 0)       ", FALSE,	10, "\x12",         str1, str2, " shindeiru", 0);
	print_test_strlcpy("strlcpy (n > src_len) ", FALSE,	10, " shindeiru",   str1, str2, " shindeiru", 15);
	print_test_strlcpy("strlcpy (n > dest_len)", FALSE,	10, "shindeiru ",   str1, str2, "shindeiru ", 50);
	print_test_strlcpy("strlcpy (null dest)",	 SEGV,	0,  NULL,           NULL, NULL, " shindeiru", 5);
	print_test_strlcpy("strlcpy (null src) ",	 SEGV,	0,  "shindeiru ",   str1, str2, NULL,         5);
	print_test_strlcpy("strlcpy (both null)",	 SEGV,	0,  NULL,           NULL, NULL, NULL,         5);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_strcat
void	print_test_strcat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src)
{
	TEST_PERFORM_RESULT_LIBC_DEST(strcat, src)
	print_test_str(test_name, "strcat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strcat return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\"", dest_libft, src)
}
void	test_strcat(void)
{
	char str1[128];
	char str2[128];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION  | TEST NAME        | CAN SEGV | TEST ARGS
	print_test_strcat("strcat",            	FALSE,	str1, str2, "Bob");
	print_test_strcat("strcat",            	FALSE,	str1, str2, test1);
	print_test_strcat("strcat",            	FALSE,	str1, str2, test2);
	print_test_strcat("strcat",            	FALSE,	str1, str2, test3);
	print_test_strcat("strcat (null dest)",	TRUE,	NULL, NULL, "Bob\0");
	print_test_strcat("strcat (null src) ",	TRUE,	str1, str2, NULL);
	print_test_strcat("strcat (both null)",	TRUE,	NULL, NULL, NULL);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_strncat
void	print_test_strncat(char const* test_name, int can_segfault,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size n)
{
	TEST_PERFORM_RESULT_LIBC_DEST(strncat, src, n)
	print_test_str(test_name, "strncat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_str(NULL,      "strncat return",     result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", n=%lu", dest_libft, src, n)
}
void	test_strncat(void)
{
	char str1[128];
	char str2[128];
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME           | CAN SEGV | TEST ARGS
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, "Bob",      3);
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, test1,      test1_len);
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, test2,      test2_len);
	print_test_strncat("strncat          ",  	FALSE,	str1, str2, test3,      test3_len);
	print_test_strncat("strncat (n = 0)  ",  	FALSE,	str1, str2, "Bobensen", 0);
	print_test_strncat("strncat (n < len)",  	FALSE,	str1, str2, "Bobensen", 3);
	print_test_strncat("strncat (n > len)",  	FALSE,	str1, str2, "Bob\0",    7);
	print_test_strncat("strncat (null dest)",	TRUE,	NULL, NULL, "Bob\0",    5);
	print_test_strncat("strncat (null src) ",	TRUE,	str1, str2, NULL,       5);
	print_test_strncat("strncat (both null)",	TRUE,	NULL, NULL, NULL,       5);
	// TODO add overlapping memory test
}
#endif



#ifdef			ft_strlcat
void	print_test_strlcat(char const* test_name, int can_segfault,
		t_size expecting,
		char const * expecting_dest,
		char* dest_libft,
		char* dest_libc,
		char const* src,
		t_size size)
{
#ifdef __APPLE__
	TEST_PERFORM_RESULT_TYPE_LIBC_DEST(t_size, strlcat, src, size)
	print_test_str(test_name, "strlcat 'dest' arg", dest_libft,   dest_libc,   can_segfault);
	print_test_size(NULL,     "strlcat return",     result_libft, result_libc, can_segfault);
#else
	TEST_PERFORM_RESULT_TYPE_DEST(t_size, strlcat, src, size)
	print_test_str(test_name, "_strlcat 'dest' arg", dest_libft,   expecting_dest, can_segfault);
	print_test_size(NULL,     "_strlcat return",     result_libft, expecting,      can_segfault);
#endif
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", size=%lu", dest_libft, src, size)
}
void	test_strlcat(void)
{
	char str1[64] = "______________________________";
	char str2[64] = "______________________________";
	strcpy(str1, "Sponge\0");
	strcpy(str2, "Sponge\0");
//	| TEST FUNCTION   | TEST NAME           |CAN SEGV| EXPECTING                     | TEST ARGS
	print_test_strlcat("strlcat          ",   FALSE,  15, "Sponge",                      str1, str2, " shindeiru", 5);
	print_test_strlcat("strlcat          ",   FALSE,  28, "SpongeOmae wa mou shin",      str1, str2, test1,        test1_len);
	print_test_strlcat("strlcat          ",   FALSE,  15, "SpongeOmae wa mou shin",      str1, str2, test2,        test2_len);
	print_test_strlcat("strlcat          ",   FALSE,  48, "SpongeOmae wa mou shinUn a",  str1, str2, test3,        test3_len);
	print_test_strlcat("strlcat (n = 0)  ",   FALSE,  10, "SpongeOmae wa mou shinUn a",  str1, str2, " shindeiru", 0);
	print_test_strlcat("strlcat (n < len)",   FALSE,  25, "SpongeOmae wa mou shinUn a",  str1, str2, " shindeiru", 15);
	print_test_strlcat("strlcat (n > len)",   FALSE,  28, "SpongeOmae wa mou shinUn a a",str1, str2, " a",         50);
	print_test_strlcat("strlcat (null dest)", SEGV,   0,  NULL,                          NULL, NULL, " a",         5);
	print_test_strlcat("strlcat (null src) ", SEGV,   0,  "SpongeOmae wa mou shinUn a a",str1, str2, NULL,         5);
	print_test_strlcat("strlcat (both null)", SEGV,   0,  NULL,                          NULL, NULL, NULL,         5);
	// TODO add overlapping memory test
}
#endif



/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

#ifdef			ft_strlen
void	print_test_strlen(char const* test_name, int can_segfault,
		char const* str)
{
	TEST_PERFORM_RESULT_TYPE_LIBC(t_size, strlen, str)
	print_test_size(test_name, "strlen return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str=\"%s\"", str)
}
void	test_strlen(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| TEST ARGS
	print_test_strlen("strlen",             FALSE,	test1);
	print_test_strlen("strlen",             FALSE,	test2);
	print_test_strlen("strlen",             FALSE,	test3);
	print_test_strlen("strlen",             FALSE,	"a");
	print_test_strlen("strlen (empty str)", FALSE,	"");
	print_test_strlen("strlen (null str) ", TRUE,	NULL);
}
#endif


#ifdef			ft_strcmp
void	print_test_strcmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2)
{
	TEST_PERFORM_RESULT_TYPE_LIBC(int, strcmp, str1, str2)
	print_test_sign(test_name, "strcmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strcmp(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| TEST ARGS
	print_test_strcmp("strcmp",             FALSE,	test1, test1);
	print_test_strcmp("strcmp",             FALSE,	test1, test2);
	print_test_strcmp("strcmp",             FALSE,	test1, test3);
	print_test_strcmp("strcmp",             FALSE,	test2, test1);
	print_test_strcmp("strcmp",             FALSE,	test2, test2);
	print_test_strcmp("strcmp",             FALSE,	test2, test3);
	print_test_strcmp("strcmp",             FALSE,	test3, test1);
	print_test_strcmp("strcmp",             FALSE,	test3, test2);
	print_test_strcmp("strcmp",             FALSE,	test3, test3);
	print_test_strcmp("strcmp (null str1)", TRUE,	NULL,  test3);
	print_test_strcmp("strcmp (null str2)", TRUE,	test2, NULL);
	print_test_strcmp("strcmp (both null)", TRUE,	NULL,  NULL);
}
#endif


#ifdef			ft_strncmp
void	print_test_strncmp(char const* test_name, int can_segfault,
		char const* str1,
		char const* str2,
		t_size n)
{
	TEST_PERFORM_RESULT_TYPE_LIBC(int, strncmp, str1, str2, n)
	print_test_sign(test_name, "strncmp return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str1=\"%s\", str2=\"%s\", n=%lu", str1, str2, n)
}
void	test_strncmp(void)
{
//	| TEST FUNCTION  | TEST NAME              |CAN SEGV| TEST ARGS
	print_test_strncmp("strncmp        ",    	FALSE,	test1,     test1,     test1_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test1,     test2,     test2_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test1,     test3,     test3_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test2,     test1,     test1_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test2,     test2,     test2_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test2,     test3,     test3_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test3,     test1,     test1_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test3,     test2,     test2_len);
	print_test_strncmp("strncmp        ",    	FALSE,	test3,     test3,     test3_len);
	print_test_strncmp("strncmp        ",    	FALSE,	"abc",     "abcdef",  3);
	print_test_strncmp("strncmp        ",    	FALSE,	test2 + 1, test3 + 3, 2);
	print_test_strncmp("strncmp (n = 0)",    	FALSE,	test2,     test3,     0);
	print_test_strncmp("strncmp (null str1)",	TRUE,	NULL,      test3,     5);
	print_test_strncmp("strncmp (null str2)",	TRUE,	test2,     NULL,      5);
	print_test_strncmp("strncmp (both null)",	TRUE,	NULL,      NULL,      5);
}
#endif


#ifdef			ft_strequ
void	print_test_strequ(char const* test_name, int can_segfault,
		int expecting,
		char const* str1,
		char const* str2)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, strequ, str1, str2)
	print_test_bool(test_name, "_strequ return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str1=\"%s\", str2=\"%s\"", str1, str2)
}
void	test_strequ(void)
{
//	| TEST FUNCTION  | TEST NAME            | CAN SEGV | EXPECTING                  | TEST ARGS
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test1, test1) == 0), test1, test1);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test1, test2) == 0), test1, test2);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test1, test3) == 0), test1, test3);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test2, test1) == 0), test2, test1);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test2, test2) == 0), test2, test2);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test2, test3) == 0), test2, test3);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test3, test1) == 0), test3, test1);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test3, test2) == 0), test3, test2);
	print_test_strequ("strequ            ", 	FALSE,	(strcmp(test3, test3) == 0), test3, test3);
	print_test_strequ("strequ (empty str)", 	FALSE,	(strcmp(test1, "")    == 0), test1, "");
	print_test_strequ("strequ (null str1)", 	SEGV,	FALSE,                       NULL,  test2);
	print_test_strequ("strequ (null str2)", 	SEGV,	FALSE,                       test1, NULL);
	print_test_strequ("strequ (both null)", 	SEGV,	TRUE,                        NULL,  NULL);
}
#endif


#ifdef			ft_strnequ
void	print_test_strnequ(char const* test_name, int can_segfault,
		int expecting,
		char const* str1,
		char const* str2,
		t_size n)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, strnequ, str1, str2, n)
	print_test_bool(test_name, "_strnequ return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str1=\"%s\", str2=\"%s\", n=%lu", str1, str2, n)
}
void	test_strnequ(void)
{
//	| TEST FUNCTION  | TEST NAME            | CAN SEGV | EXPECTING                             | TEST ARGS
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test1, test1, test1_len) == 0), test1, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test1, test2, test2_len) == 0), test1, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test1, test3, test3_len) == 0), test1, test3, test3_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test2, test1, test1_len) == 0), test2, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test2, test2, test2_len) == 0), test2, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test2, test3, test3_len) == 0), test2, test3, test3_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test3, test1, test1_len) == 0), test3, test1, test1_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test3, test2, test2_len) == 0), test3, test2, test2_len);
	print_test_strnequ("strnequ            ", 	FALSE,	(strncmp(test3, test3, test3_len) == 0), test3, test3, test3_len);
	print_test_strnequ("strnequ (empty str)",	FALSE,	(strncmp(test1, "",    5)         == 0), test1, "",    5);
	print_test_strnequ("strnequ (n = 0)    ",	FALSE,	(strncmp(test1, test1, 0)         == 0), test1, test1, 0);
	print_test_strnequ("strnequ (n > len)  ",	FALSE,	(strncmp(test1, test1, 30)        == 0), test1, test1, 30);
	print_test_strnequ("strnequ (null str1)",	SEGV,	FALSE,                            NULL,  test2, 7);
	print_test_strnequ("strnequ (null str2)",	SEGV,	FALSE,                            test1, NULL,  7);
	print_test_strnequ("strnequ (both null)",	SEGV,	TRUE,                             NULL,  NULL,  7);
}
#endif


#ifdef			ft_strhas
void	print_test_strhas(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str,
		char const* charset)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, strhas, str, charset)
	print_test_bool(test_name, "_strhas", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_strhas(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV|EXPECTING| TEST ARGS
	print_test_strhas("strhas               ",	FALSE,  TRUE,     test1, "_0i");
	print_test_strhas("strhas               ",	FALSE,  TRUE,     test2, "na");
	print_test_strhas("strhas               ",	FALSE,  TRUE,     test3, "in");
	print_test_strhas("strhas               ",	FALSE,  TRUE,     "sweg my nigga", "mz");
	print_test_strhas("strhas               ",	FALSE,  TRUE,     "sweg my nigga", "aze");
	print_test_strhas("strhas               ",	FALSE,  FALSE,    "sweg my nigga", "z_u");
	print_test_strhas("strhas (null str)    ",	SEGV,   FALSE,     NULL, "mz");
	print_test_strhas("strhas (null charset)",	SEGV,   FALSE,     "sw", NULL);
	print_test_strhas("strhas (both null)   ",	SEGV,   FALSE,     NULL, NULL);
}
#endif


#ifdef			ft_strhasonly
void	print_test_strhasonly(char const* test_name, int can_segfault,
		t_bool expecting,
		char const* str,
		char const* charset)
{
	TEST_PERFORM_RESULT_TYPE(t_bool, strhasonly, str, charset)
	print_test_bool(test_name, "_strhasonly", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", charset=\"%s\"", str, charset)
}
void	test_strhasonly(void)
{
//	| TEST FUNCTION      | TEST NAME                  |CAN SEGV|EXPECT| TEST ARGS
	print_test_strhasonly("strhasonly                ",	FALSE,  FALSE,   test1, "m");
	print_test_strhasonly("strhasonly                ",	FALSE,  FALSE,   test2, "na");
	print_test_strhasonly("strhasonly                ",	FALSE,  FALSE,   test3, "in");
	print_test_strhasonly("strhasonly                ",	FALSE,  TRUE,   "sweg my nigga", "aiey gmnsw");
	print_test_strhasonly("strhasonly                ",	FALSE,  FALSE,  "sweg my nigga", "aiey gsw");
	print_test_strhasonly("strhasonly (empty str)    ",	FALSE,  TRUE,   "",     "z_u");
	print_test_strhasonly("strhasonly (empty charset)",	FALSE,  FALSE,  "sweg", "");
	print_test_strhasonly("strhasonly (null str)     ",	SEGV,   FALSE,  NULL, "mz");
	print_test_strhasonly("strhasonly (null charset) ",	SEGV,   FALSE,  "sw", NULL);
	print_test_strhasonly("strhasonly (both null)    ",	SEGV,   FALSE,  NULL, NULL);
}
#endif


#ifdef			ft_strcount_char
void	print_test_strcount_char(char const* test_name, int can_segfault,
		t_size expecting,
		char const* str,
		char c)
{
	TEST_PERFORM_RESULT_TYPE(t_size, strcount_char, str, c)
	print_test_size(test_name, "_strcount_char", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c'", str, c, c)
}
void	test_strcount_char(void)
{
//	| TEST FUNCTION         | TEST NAME                  |CAN SEGV|EXPECT| TEST ARGS
	print_test_strcount_char("strcount_char            ",	FALSE,  2,    test1,           'm');
	print_test_strcount_char("strcount_char            ",	FALSE,  3,    test2,           '?');
	print_test_strcount_char("strcount_char            ",	FALSE,  1,    test3,           '.');
	print_test_strcount_char("strcount_char            ",	FALSE,  0,    test3,           '_');
	print_test_strcount_char("strcount_char            ",	FALSE,  3,    "sweg my nigga", 'g');
	print_test_strcount_char("strcount_char            ",	FALSE,  0,    "sweg my nigga", 'z');
	print_test_strcount_char("strcount_char (empty str)",	FALSE,  0,    "",              'a');
	print_test_strcount_char("strcount_char ('\\0 char')",	FALSE,  0,    "sweg",          '\0');
	print_test_strcount_char("strcount_char (null str) ",	SEGV,   0,    NULL,            'a');
}
#endif


#ifdef			ft_strcount_str
void	print_test_strcount_str(char const* test_name, int can_segfault,
		t_size expecting,
		char const* str,
		char const* query)
{
	TEST_PERFORM_RESULT_TYPE(t_size, strcount_str, str, query)
	print_test_size(test_name, "_strcount_str", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", query=\"%s\"", str, query)
}
void	test_strcount_str(void)
{
//	| TEST FUNCTION        | TEST NAME                    |CAN SEGV|EXPECTING| TEST ARGS
	print_test_strcount_str("strcount_str              ",	FALSE,  1,         test1, " m");
	print_test_strcount_str("strcount_str              ",	FALSE,  2,         test2, "?");
	print_test_strcount_str("strcount_str              ",	FALSE,  3,         test3, "ange");
	print_test_strcount_str("strcount_str              ",	FALSE,  0,         test3, "_");
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
#endif


/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

#ifdef			ft_strchr
void	print_test_strchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	TEST_PERFORM_RESULT_LIBC(strchr, str, c)
	print_test_str(test_name, "strchr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c'", str, c, c)
}
void	test_strchr(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	print_test_strchr("strchr             ",	FALSE, test1, 'm');
	print_test_strchr("strchr             ",	FALSE, test2, '?');
	print_test_strchr("strchr             ",	FALSE, test3, ' ');
	print_test_strchr("strchr             ",	FALSE, test1, '_');
	print_test_strchr("strchr             ",	FALSE, test2, '_');
	print_test_strchr("strchr             ",	FALSE, test3, '_');
	print_test_strchr("strchr (c = '\\0')  ",	FALSE, test3, '\0');
	print_test_strchr("strchr (null ptr)  ",	TRUE,  NULL,  'm');
}
#endif


#ifdef			ft_strstr
void	print_test_strstr(char const* test_name, int can_segfault,
		char const* str,
		char const* query)
{
	TEST_PERFORM_RESULT_LIBC(strstr, str, query)
	print_test_str(test_name, "strstr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str=\"%s\", query=\"%s\"", str, query)
}
void	test_strstr(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| TEST ARGS
	print_test_strstr("strstr              ",	FALSE, test1, " m");
	print_test_strstr("strstr              ",	FALSE, test2, "?");
	print_test_strstr("strstr              ",	FALSE, test3, " ");
	print_test_strstr("strstr              ",	FALSE, test1, "mou ");
	print_test_strstr("strstr              ",	FALSE, test1, "??");
	print_test_strstr("strstr              ",	FALSE, test3, "???");
//	print_test_strstr("strstr (empty query)",	FALSE, test3, ""); // TODO The test here fails because there is an intentional design difference
	print_test_strstr("strstr (null str)   ",	TRUE,  NULL,  "mou ");
	print_test_strstr("strstr (null query) ",	TRUE,  test1, NULL);
	print_test_strstr("strstr (both null)  ",	TRUE,  NULL,  NULL);
}
#endif


#ifdef			ft_strrchr
void	print_test_strrchr(char const* test_name, int can_segfault,
		char const* str,
		char c)
{
	TEST_PERFORM_RESULT_LIBC(strrchr, str, c)
	print_test_str(test_name, "strrchr return", result_libft, result_libc, can_segfault);
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c'", str, c, c)
}
void	test_strrchr(void)
{
//	| TEST FUNCTION  | TEST NAME               |CAN SEGV| TEST ARGS
	print_test_strrchr("strrchr             ",	FALSE,   test1, 'm');
	print_test_strrchr("strrchr             ",	FALSE,   test2, '?');
	print_test_strrchr("strrchr             ",	FALSE,   test3, ' ');
	print_test_strrchr("strrchr             ",	FALSE,   test1, '_');
	print_test_strrchr("strrchr             ",	FALSE,   test2, '_');
	print_test_strrchr("strrchr             ",	FALSE,   test3, '_');
	print_test_strrchr("strrchr (c = '\\0')  ",	FALSE,   test3, '\0');
	print_test_strrchr("strrchr (null ptr)  ",	TRUE,    NULL,  'm');
}
#endif


#ifdef			ft_strrstr
void	print_test_strrstr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query)
{
	TEST_PERFORM_RESULT(strrstr, str, query)
	print_test_str(test_name, "_strrstr return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", query=\"%s\"", str, query)
}
void	test_strrstr(void)
{
//	| TEST FUNCTION  | TEST NAME              |CAN SEGV|    EXPECTING    | TEST ARGS
	print_test_strrstr("strrstr              ",	FALSE, "mou shindeiru.\0", test1, "mou ");
	print_test_strrstr("strrstr              ",	FALSE, NULL,               test1, "??");
	print_test_strrstr("strrstr              ",	FALSE, NULL,               test3, "???");
	print_test_strrstr("strrstr (empty query)",	FALSE, NULL,               test3, "");
	print_test_strrstr("strrstr (null str)   ",	TRUE,  segstr,             NULL,  "mou ");
	print_test_strrstr("strrstr (null query) ",	TRUE,  segstr,             test1, NULL);
	print_test_strrstr("strrstr (both null)  ",	TRUE,  segstr,             NULL,  NULL);
}
#endif


#ifdef			ft_strnchr
void	print_test_strnchr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char c,
		t_size n)
{
	TEST_PERFORM_RESULT(strnchr, str, c, n)
	print_test_str(test_name, "_strnchr return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c', n=%lu", str, c, c, n)
}
void	test_strnchr(void)
{
//	| TEST FUNCTION  | TEST NAME              |CAN SEGV|      EXPECTING      | TEST ARGS
	print_test_strnchr("strnchr             ",	FALSE, "wa mou shindeiru.\0", test1, 'w', 16);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, '_', 16);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, 'w', 1);
	print_test_strnchr("strnchr             ",	FALSE,  NULL,                 test1, '_', 1);
	print_test_strnchr("strnchr (c = '\\0')  ",	FALSE,  NULL,                 test3, '\0', 16);
	print_test_strnchr("strnchr (n = 0)     ",	FALSE,  NULL,                 test1, 'w', 0);
	print_test_strnchr("strnchr (n = len)   ",	FALSE,  NULL,                 test1, '_', test1_len);
	print_test_strnchr("strnchr (n > len)   ",	FALSE,  NULL,                 test1, '_', test1_len + 32);
	print_test_strnchr("strnchr (null ptr)  ",	TRUE,   segstr,               NULL,  'm', 16);
}
#endif


#ifdef			ft_strnstr
void	print_test_strnstr(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query,
		t_size n)
{
#ifdef __APPLE__
	TEST_PERFORM_RESULT_LIBC(strnstr, str, query, n)
	print_test_str(test_name, "strnstr return", result_libft, result_libc, can_segfault);
#else
	TEST_PERFORM_RESULT(strnstr, str, query, n)
	print_test_str(test_name, "_strnstr return", result_libft, expecting, can_segfault);
#endif
	print_timer_result(&t, TRUE);
	TEST_PRINT_ARGS("str=\"%s\", query=\"%s\", n=%lu", str, query, n)
}
void	test_strnstr(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV| EXPECTING | TEST ARGS
	print_test_strnstr("strnstr              ",	FALSE, test1 + 8,  test1, "mou ", 16);
	print_test_strnstr("strnstr              ",	FALSE, NULL,       test1, "??",   test1_len);
	print_test_strnstr("strnstr              ",	FALSE, test2 + 4,  test2, "??",   test2_len);
	print_test_strnstr("strnstr              ",	FALSE, NULL,       test3, "???",  test3_len);
	print_test_strnstr("strnstr (empty query)",	FALSE, test1,      test1, "\0",   16);
	print_test_strnstr("strnstr (n = 0)      ",	FALSE, NULL,       test1, "mou ", 0);
	print_test_strnstr("strnstr (n = len)    ",	FALSE, NULL,       test1, "_",    test1_len);
	print_test_strnstr("strnstr (n > len)    ",	FALSE, NULL,       test1, "_",    test1_len + 32);
	print_test_strnstr("strnstr (null str)   ",	TRUE,  segstr,     NULL,  "mou ", 16);
	print_test_strnstr("strnstr (null query) ",	TRUE,  segstr,     test1, NULL,   16);
	print_test_strnstr("strnstr (both null)  ",	TRUE,  segstr,     NULL,  NULL,   16);
}
#endif


#ifdef			ft_strremove
void	print_test_strremove(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* query)
{
	TEST_PERFORM_RESULT(strremove, str, query)
	print_test_str(test_name, "_strremove return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", query=\"%s\"", str, query)
	TEST_FREE()
}
void	test_strremove(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_strprint
void	print_test_strprint(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str)
{
	TEST_PERFORM_RESULT(strprint, str)
	print_test_str(test_name, "_strprint return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\"", str)
	TEST_FREE()
}
void	test_strprint(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_strrep_char
void	print_test_strrep_char(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char old,
		char new)
{
	TEST_PERFORM_RESULT(strrep_char, str, old, new)
	print_test_str(test_name, "_strrep_char return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", old=0x%x/'%c', new=0x%x/'%c'", str, old, old, new, new)
	TEST_FREE()
}
void	test_strrep_char(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_strrep_charset
void	print_test_strrep_charset(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* old,
		char const* new)
{
	TEST_PERFORM_RESULT(strrep_charset, str, old, new)
	print_test_str(test_name, "_strrep_charset return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", old=\"%s\", new=\"%s\"", str, old, new)
	TEST_FREE()
}
void	test_strrep_charset(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_strrep_str
void	print_test_strrep_str(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char const* old,
		char const* new)
{
	TEST_PERFORM_RESULT(strrep_str, str, old, new)
	print_test_str(test_name, "_strrep_str return", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", old=\"%s\", new=\"%s\"", str, old, new)
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

#ifdef			ft_strtrim
void	print_test_strtrim(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_PERFORM_RESULT(strtrim, str, charset)
	print_test_str(test_name, "_strtrim", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* tmp_str		= str_to_escape(str);
	char* tmp_charset	= str_to_escape(charset);
	TEST_PRINT_ARGS("str=\"%s\", charset=\"%s\"", tmp_str, tmp_charset)
	free(tmp_str);
	free(tmp_charset);
	TEST_FREE()
}
void	test_strtrim(void)
{
//	| TEST FUNCTION   | TEST NAME                |CAN SEGV| EXPECTING                      | TEST ARGS
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
#endif


#ifdef			ft_strtrim_l
void	print_test_strtrim_l(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_PERFORM_RESULT(strtrim_l, str, charset)
	print_test_str(test_name, "_strtrim_l", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* tmp_str		= str_to_escape(str);
	char* tmp_charset	= str_to_escape(charset);
	TEST_PRINT_ARGS("str=\"%s\", charset=\"%s\"", tmp_str, tmp_charset)
	free(tmp_str);
	free(tmp_charset);
	TEST_FREE()
}
void	test_strtrim_l(void)
{
//	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING                      | TEST ARGS
	print_test_strtrim_l("strtrim_l                  ", FALSE, "swag\n",                        " \t\n\r\v\f", "   swag\n");
	print_test_strtrim_l("strtrim_l                  ", FALSE, "FOR THE\tHORDE ! 	 \t \n ",   " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim_l("strtrim_l                  ", FALSE, "do u even\ntrim bruh\n\r\n\n\t"," \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim_l("strtrim_l (only whitespace)", FALSE, "",                              " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim_l("strtrim_l (empty string)   ", FALSE, "",                              " \t\n\r\v\f", "");
	print_test_strtrim_l("strtrim_l (empty charset)  ", FALSE, "   swag\n",                     "",            "   swag\n");
	print_test_strtrim_l("strtrim_l (null string)    ", TRUE,  segstr,                          "ab", NULL);
	print_test_strtrim_l("strtrim_l (null charset)   ", TRUE,  segstr,                          NULL, " swag \n");
	print_test_strtrim_l("strtrim_l (both null)      ", TRUE,  segstr,                          NULL, NULL);
}
#endif


#ifdef			ft_strtrim_r
void	print_test_strtrim_r(char const* test_name, int can_segfault,
		char const* expecting,
		char const* charset,
		char const* str)
{
	TEST_PERFORM_RESULT(strtrim_r, str, charset)
	print_test_str(test_name, "_strtrim_r", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	char* tmp_str		= str_to_escape(str);
	char* tmp_charset	= str_to_escape(charset);
	TEST_PRINT_ARGS("str=\"%s\", charset=\"%s\"", tmp_str, tmp_charset)
	free(tmp_str);
	free(tmp_charset);
	TEST_FREE()
}
void	test_strtrim_r(void)
{
//	| TEST FUNCTION     | TEST NAME                  |CAN SEGV| EXPECTING                      | TEST ARGS
	print_test_strtrim_r("strtrim_r                  ", FALSE, "   swag",                       " \t\n\r\v\f", "   swag\n");
	print_test_strtrim_r("strtrim_r                  ", FALSE, "\t\n   \f FOR THE\tHORDE !",    " \t\n\r\v\f", "\t\n   \f FOR THE\tHORDE ! 	 \t \n ");
	print_test_strtrim_r("strtrim_r                  ", FALSE, "do u even\ntrim bruh",          " \t\n\r\v\f", "do u even\ntrim bruh\n\r\n\n\t");
	print_test_strtrim_r("strtrim_r (only whitespace)", FALSE, "",                              " \t\n\r\v\f", "\n 	  \v \n\t ");
	print_test_strtrim_r("strtrim_r (empty string)   ", FALSE, "",                              " \t\n\r\v\f", "");
	print_test_strtrim_r("strtrim_r (empty charset)  ", FALSE, "   swag\n",                     "",            "   swag\n");
	print_test_strtrim_r("strtrim_r (null string)    ", TRUE,  segstr,                          "ab", NULL);
	print_test_strtrim_r("strtrim_r (null charset)   ", TRUE,  segstr,                          NULL, " swag \n");
	print_test_strtrim_r("strtrim_r (both null)      ", TRUE,  segstr,                          NULL, NULL);
}
#endif


#ifdef			ft_strpad
void	print_test_strpad(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_PERFORM_RESULT(strpad, str, c, length)
	print_test_str(test_name, "_strpad", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c', n=%lu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad(void)
{
//	| TEST FUNCTION     | TEST NAME            |CAN SEGV| EXPECTING                    | TEST ARGS
	print_test_strpad("strpad (n == strlen)    ", FALSE, "test",                       "test", ' ', 4);
	print_test_strpad("strpad                  ", FALSE, "test ",                      "test", ' ', 5);
	print_test_strpad("strpad                  ", FALSE, " test ",                     "test", ' ', 6);
	print_test_strpad("strpad                  ", FALSE, " test  ",                    "test", ' ', 7);
	print_test_strpad("strpad                  ", FALSE, "  test  ",                   "test", ' ', 8);
	print_test_strpad("strpad                  ", FALSE, "  test   ",                  "test", ' ', 9);
	print_test_strpad("strpad                  ", FALSE, "   test   ",                 "test", ' ', 10);
	print_test_strpad("strpad                  ", FALSE, "12340",                      "1234", '0', 5);
	print_test_strpad("strpad                  ", FALSE, "012340",                     "1234", '0', 6);
	print_test_strpad("strpad (n < strlen)     ", FALSE, "swa",                        "swag", ' ', 3);
	print_test_strpad("strpad (n < strlen)     ", FALSE, "wa",                         "swag", ' ', 2);
	print_test_strpad("strpad (n < strlen)     ", FALSE, "w",                          "swag", ' ', 1);
	print_test_strpad("strpad (n == 0)         ", FALSE, "",                           "swag", ' ', 0);
	print_test_strpad("strpad (c == '\\0')     ", FALSE, "test",                       "test",'\0', 5);
	print_test_strpad("strpad (c == '\\0')     ", FALSE, "",                           "test",'\0', 6);
	print_test_strpad("strpad (null string)    ", TRUE,  segstr,                       "test", ' ', 5);
}
#endif



#ifdef			ft_strpad_l
void	print_test_strpad_l(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_PERFORM_RESULT(strpad_l, str, c, length)
	print_test_str(test_name, "_strpad_l", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c', n=%lu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad_l(void)
{
//	| TEST FUNCTION     | TEST NAME             |CAN SEGV| EXPECTING                    | TEST ARGS
	print_test_strpad_l("strpad_l (n == strlen) ", FALSE, "test",                       "test", ' ', 4);
	print_test_strpad_l("strpad_l               ", FALSE, " test",                      "test", ' ', 5);
	print_test_strpad_l("strpad_l               ", FALSE, "  test",                     "test", ' ', 6);
	print_test_strpad_l("strpad_l               ", FALSE, "   test",                    "test", ' ', 7);
	print_test_strpad_l("strpad_l               ", FALSE, "    test",                   "test", ' ', 8);
	print_test_strpad_l("strpad_l               ", FALSE, "     test",                  "test", ' ', 9);
	print_test_strpad_l("strpad_l               ", FALSE, "      test",                 "test", ' ', 10);
	print_test_strpad_l("strpad_l               ", FALSE, "01234",                      "1234", '0', 5);
	print_test_strpad_l("strpad_l               ", FALSE, "001234",                     "1234", '0', 6);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE, "wag",                        "swag", ' ', 3);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE, "ag",                         "swag", ' ', 2);
	print_test_strpad_l("strpad_l (n < strlen)  ", FALSE, "g",                          "swag", ' ', 1);
	print_test_strpad_l("strpad_l (n == 0)      ", FALSE, "",                           "swag", ' ', 0);
	print_test_strpad_l("strpad_l (c == '\\0')  ", FALSE, "test",                       "test",'\0', 4);
	print_test_strpad_l("strpad_l (c == '\\0')  ", FALSE, "",                           "test",'\0', 5);
	print_test_strpad_l("strpad_l (null string) ", TRUE,  segstr,                       "test", ' ', 5);
}
#endif



#ifdef			ft_strpad_r
void	print_test_strpad_r(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		char c,
		t_size length)
{
	TEST_PERFORM_RESULT(strpad_r, str, c, length)
	print_test_str(test_name, "_strpad_r", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", c=0x%x/'%c', n=%lu", str, c, c, length)
	TEST_FREE()
}
void	test_strpad_r(void)
{
//	| TEST FUNCTION     | TEST NAME             |CAN SEGV| EXPECTING                    | TEST ARGS
	print_test_strpad_r("strpad_r (n == strlen) ", FALSE, "test",                       "test", ' ', 4);
	print_test_strpad_r("strpad_r               ", FALSE, "test ",                      "test", ' ', 5);
	print_test_strpad_r("strpad_r               ", FALSE, "test  ",                     "test", ' ', 6);
	print_test_strpad_r("strpad_r               ", FALSE, "test   ",                    "test", ' ', 7);
	print_test_strpad_r("strpad_r               ", FALSE, "test    ",                   "test", ' ', 8);
	print_test_strpad_r("strpad_r               ", FALSE, "test     ",                  "test", ' ', 9);
	print_test_strpad_r("strpad_r               ", FALSE, "test      ",                 "test", ' ', 10);
	print_test_strpad_r("strpad_r               ", FALSE, "12340",                      "1234", '0', 5);
	print_test_strpad_r("strpad_r               ", FALSE, "123400",                     "1234", '0', 6);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE, "swa",                        "swag", ' ', 3);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE, "sw",                         "swag", ' ', 2);
	print_test_strpad_r("strpad_r (n < strlen)  ", FALSE, "s",                          "swag", ' ', 1);
	print_test_strpad_r("strpad_r (n == 0)      ", FALSE, "",                           "swag", ' ', 0);
	print_test_strpad_r("strpad_r (c == '\\0')  ", FALSE, "test",                       "test",'\0', 4);
	print_test_strpad_r("strpad_r (c == '\\0')  ", FALSE, "test",                       "test",'\0', 5);
	print_test_strpad_r("strpad_r (null string) ", TRUE,  segstr,                       "test", ' ', 5);
}
#endif



/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

// TODO check on which platforms this function exists, if any
#ifdef			ft_strrev
void	print_test_strrev(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str)
{
	TEST_PERFORM_RESULT(strrev, str)
	print_test_str(test_name, "_strrev", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\"", str)
	TEST_FREE()
}
void	test_strrev(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING              | TEST ARGS
	print_test_strrev("strrev (even len)",	FALSE, ".uriednihs uom aw eamO", test1);
	print_test_strrev("strrev (odd len) ",	FALSE, "???inaN",                test2);
	print_test_strrev("strrev (null ptr)",	TRUE,  segstr,                   NULL);
}
#endif


#ifdef			ft_strjoin
void	print_test_strjoin(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str1,
		char const *str2)
{
	TEST_PERFORM_RESULT(strjoin, str1, str2)
	print_test_str(test_name, "_strjoin", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str1=\"%s\", str2=\"%s\"", str1, str2)
	TEST_FREE()
}
void	test_strjoin(void)
{
//	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING                     | TEST ARGS
	print_test_strjoin("strjoin",            	FALSE, "Omae wa mou shindeiru.Nani???", test1, test2);
	print_test_strjoin("strjoin (null str1)",	TRUE,   segstr,                         NULL,  test2);
	print_test_strjoin("strjoin (null str2)",	TRUE,   segstr,                         test1, NULL);
	print_test_strjoin("strjoin (both null)",	TRUE,   segstr,                         NULL,  NULL);
}
#endif


#ifdef			ft_strinsert
void	print_test_strinsert(char const* test_name, int can_segfault,
		char const* expecting,
		char const *dest,
		char const *src,
		t_size offset)
{
	TEST_PERFORM_RESULT(strinsert, dest, src, offset)
	print_test_str(test_name, "_strinsert", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("dest=\"%s\", src=\"%s\", offset=%lu", dest, src, offset)
	TEST_FREE()
}
void	test_strinsert(void)
{
//	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS
//	TODO
}
#endif



#ifdef			ft_strsub
void	print_test_strsub(char const* test_name, int can_segfault,
		char const* expecting,
		char const *str,
		t_size offset,
		t_size n)
{
	TEST_PERFORM_RESULT(strsub, str, offset, n)
	print_test_str(test_name, "_strsub", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", offset=%lu, n=%lu", str, offset, n)
	TEST_FREE()
}
void	test_strsub(void)
{
//	| TEST FUNCTION  | TEST NAME             |CAN SEGV|EXPECTING| TEST ARGS
	print_test_strsub("strsub            ",   	FALSE, "wa mo",  test1, 5, 5);
	print_test_strsub("strsub (len = 0)  ",   	FALSE, "",       test1, 5, 0);
	print_test_strsub("strsub (len > str)",   	FALSE, NULL,     test1, 5, 100);
	print_test_strsub("strsub (offset > str)",	TRUE,  NULL,     test1, 100, 5);
	print_test_strsub("strsub (null ptr)    ",	TRUE,  segstr,   NULL,  5, 5);
}
#endif



void	strtolower(char* c)
{
	if (isupper(*c))
		*c = tolower(*c);
}

void	strtolower_1on2(t_size i, char* c)
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

char	strtoupper_1on2(t_size i, char c)
{
	if (i % 2 == 1 && islower(c))
		 return (toupper(c));
	else return (c);
}



#ifdef			ft_striter
void	print_test_striter(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(char*))
{
	char* result_libft = str == NULL ? NULL : strdup(str);
	TEST_PERFORM(result_libft, striter, result_libft, f)
	print_test_str(test_name, "_striter", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_striter(void)
{
//	| TEST FUNCTION   | TEST NAME            |CAN SEGV| EXPECTING                | TEST ARGS
	print_test_striter("striter            ",	FALSE, "omae wa mou shindeiru.",  "omAe wA mOu ShINDeIRu.", &strtolower);
	print_test_striter("striter (null str) ",	TRUE,   segstr,                    NULL,                    &strtolower);
	print_test_striter("striter (null func)",	TRUE,   segstr,                   "omAe wA mOu ShINDeIRu.", NULL);
	print_test_striter("striter (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}
#endif


#ifdef			ft_striteri
void	print_test_striteri(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		void (*f)(t_size, char*))
{
	char* result_libft = str == NULL ? NULL : strdup(str);
	TEST_PERFORM(result_libft, striteri, result_libft, f)
	print_test_str(test_name, "_striteri", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_striteri(void)
{
//	| TEST FUNCTION    | TEST NAME            |CAN SEGV| EXPECTING                | TEST ARGS
	print_test_striteri("striteri            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.",  "OMAE WA MOU SHINDEIRU.", &strtolower_1on2);
	print_test_striteri("striteri (null str) ",	TRUE,   segstr,                    NULL,                    &strtolower_1on2);
	print_test_striteri("striteri (null func)",	TRUE,   segstr,                   "OMAE WA MOU SHINDEIRU.", NULL);
	print_test_striteri("striteri (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}
#endif


#ifdef			ft_strmap
void	print_test_strmap(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char (*f)(char))
{
	TEST_PERFORM_RESULT(strmap, str, f)
	print_test_str(test_name, "_strmap", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_strmap(void)
{
//	| TEST FUNCTION   | TEST NAME         |CAN SEGV| EXPECTING                | TEST ARGS
	print_test_strmap("strmap            ",	FALSE, "OMAE WA MOU SHINDEIRU.",  "omae wa mou shindeiru.", &strtoupper);
	print_test_strmap("strmap (null str) ",	TRUE,   segstr,                    NULL,                    &strtoupper);
	print_test_strmap("strmap (null func)",	TRUE,   segstr,                   "omae wa mou shindeiru.", NULL);
	print_test_strmap("strmap (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}
#endif


#ifdef			ft_strmapi
void	print_test_strmapi(char const* test_name, int can_segfault,
		char const* expecting,
		char const* str,
		char (*f)(t_size, char))
{
	TEST_PERFORM_RESULT(strmapi, str, f)
	print_test_str(test_name, "_strmapi", result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
	TEST_PRINT_ARGS("str=\"%s\", f=%p", str, f)
	TEST_FREE()
}
void	test_strmapi(void)
{
//	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING                | TEST ARGS
	print_test_strmapi("strmapi            ",	FALSE, "oMaE Wa mOu sHiNdEiRu.",  "omae wa mou shindeiru.", &strtoupper_1on2);
	print_test_strmapi("strmapi (null str) ",	TRUE,   segstr,                    NULL,                    &strtoupper_1on2);
	print_test_strmapi("strmapi (null func)",	TRUE,   segstr,                   "omae wa mou shindeiru.", NULL);
	print_test_strmapi("strmapi (both null)",	TRUE,   segstr,                    NULL,                    NULL);
}
#endif








int		testsuite_string(void)
{
	print_suite_title("string");

#ifdef ft_strnew
	test_strnew();
#endif
#ifdef ft_strdup
	test_strdup();
#endif
#ifdef ft_strcpy
	test_strcpy();
#endif
#ifdef ft_strncpy
	test_strncpy();
#endif
#ifdef ft_strlcpy
	test_strlcpy();
#endif
#ifdef ft_strcat
	test_strcat();
#endif
#ifdef ft_strncat
	test_strncat();
#endif
#ifdef ft_strlcat
	test_strlcat();
#endif

#ifdef ft_strlen
	test_strlen();
#endif
#ifdef ft_strcmp
	test_strcmp();
#endif
#ifdef ft_strncmp
	test_strncmp();
#endif

#ifdef ft_strchr
	test_strchr();
#endif
#ifdef ft_strrchr
	test_strrchr();
#endif
#ifdef ft_strstr
	test_strstr();
#endif
#ifdef ft_strnstr
	test_strnstr();
#endif



	print_nonstd();



#ifdef ft_strset
	test_strset();
#endif
#ifdef ft_strclr
	test_strclr();
#endif
#ifdef ft_strdel
//	test_strdel();
#endif
#ifdef ft_strmerge
//	test_strmerge();
#endif
#ifdef ft_strappend
//	test_strappend();
#endif
#ifdef ft_strprepend
//	test_strprepend();
#endif

#ifdef ft_strequ
	test_strequ();
#endif
#ifdef ft_strnequ
	test_strnequ();
#endif
#ifdef ft_strhas
	test_strhas();
#endif
#ifdef ft_strhasonly
	test_strhasonly();
#endif
#ifdef ft_strcount_char
	test_strcount_char();
#endif
#ifdef ft_strcount_str
	test_strcount_str();
#endif

#ifdef ft_strnchr
	test_strnchr();
#endif
#ifdef ft_strrstr
	test_strrstr();
#endif
#ifdef ft_strprint
	test_strprint();
#endif
#ifdef ft_strrep_char
//	test_strrep_char();
#endif
#ifdef ft_strrep_charset
//	test_strrep_charset();
#endif
#ifdef ft_strrep_str
//	test_strrep_str();
#endif

#ifdef ft_strtrim
	test_strtrim();
#endif
#ifdef ft_strtrim_l
	test_strtrim_l();
#endif
#ifdef ft_strtrim_r
	test_strtrim_r();
#endif
#ifdef ft_strpad
	test_strpad();
#endif
#ifdef ft_strpad_l
	test_strpad_l();
#endif
#ifdef ft_strpad_r
	test_strpad_r();
#endif

#ifdef ft_strrev
	test_strrev();
#endif
#ifdef ft_strjoin
	test_strjoin();
#endif
#ifdef ft_strinsert
//	test_strinsert();
#endif
#ifdef ft_strsub
	test_strsub();
#endif
#ifdef ft_striter
	test_striter();
#endif
#ifdef ft_striteri
	test_striteri();
#endif
#ifdef ft_strmap
	test_strmap();
#endif
#ifdef ft_strmapi
	test_strmapi();
#endif


	return (0);
}
