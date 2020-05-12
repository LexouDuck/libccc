
#include "libft_stringarray.h"

#include "test.h"



/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/



/*
char	**ft_strsplit(char const *str, char c);
*/
/*
void	print_test_strsplit(char const* test_name, int can_segfault,
		char const** expecting,
		char const* str,
		char separator)
{
	t_timer t = {0};
	char** result_libft;
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_strsplit(str, separator); timer_clock(&t.end1); } else { result_libft = (char**)malloc(sizeof(char*)); *result_libft = segstr; }
	print_test_strls(test_name, "_strsplit", (char const**)result_libft, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strsplit(char const** segstrls)
{
	char const* split_1[] = { "Omae", "wa", "mou", "shindeiru." };
	char const* split_2[] = { "Un ", "nge m", "nge de l", " f", "nge." };
printf("\n");
//	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING | TEST ARGS
	print_test_strsplit("strsplit",           	FALSE,  split_1,    test1, ' ');
	print_test_strsplit("strsplit",           	FALSE,  split_2,    test3, 'a');
	print_test_strsplit("strsplit (null str)",	TRUE,   segstrls,   NULL,  'a');
}
*/








/*
**	char	*ft_str_(char const* str);
*/
void	print_test_strls_(char const* test_name, int can_segfault,
		char const* expecting)
{
	t_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strls_(char** segstrls)
{
printf("\n");
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}







int		test_stringarray(void)
{
	char const** segstrls;
	if (!(segstrls = (char const**)malloc(sizeof(char*) + 1)))
		return (ERROR);
	segstrls[0] = segstr;
	segstrls[1] = NULL;

printf("\n");

	printf("       .---------------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_stringarray   }===---\n");
	printf("       '---------------------------------'       \n");

	print_nonstd();

//	test_strsplit(segstrls);

printf("\n");

	return (0);
}
