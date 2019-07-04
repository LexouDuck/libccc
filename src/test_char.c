
#include "test.h"

int		test_char(void)
{

printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_char   }===---\n");
	printf("       '--------------------------'       \n");

//	int		ft_isalpha(int c);
//	int		ft_isdigit(int c);
//	int		ft_isalnum(int c);
//	int		ft_isascii(int c);
//	int		ft_isprint(int c);
//	int		ft_toupper(int c);
//	int		ft_tolower(int c);
	printf("\n==> "C_BLUE"The following tests are done by comparing your 'ft_' functions to the ctype.h standard functions."C_RESET);
	printf("\n==> "C_BLUE"Ideally, all of these char function tests should succeed, and no output will be shown."C_RESET);
	printf("\n==> "C_BLUE"(You may see warnings for characters beyond 255, those chars are undefined behavior)."C_RESET);
	printf("\n==> "C_BLUE"In any case, errors/warnings will be displayed if there are any, important or not."C_RESET"\n");

printf("\n");
	int charmax = 256;
	int warning = 0;
	int error = 0;
	int i = 0;
	while (i < charmax)
	{
		if (!bool_equals(ft_isalpha(i), isalpha(i))) { ++error; printf(C_RED">ERROR - ft_isalpha(%d) = %d\n"C_RESET, i, ft_isalpha(i)); }
		if (!bool_equals(ft_isupper(i), isupper(i))) { ++error; printf(C_RED">ERROR - ft_isupper(%d) = %d\n"C_RESET, i, ft_isupper(i)); }
		if (!bool_equals(ft_islower(i), islower(i))) { ++error; printf(C_RED">ERROR - ft_islower(%d) = %d\n"C_RESET, i, ft_islower(i)); }
		if (!bool_equals(ft_isalnum(i), isalnum(i))) { ++error; printf(C_RED">ERROR - ft_isalnum(%d) = %d\n"C_RESET, i, ft_isalnum(i)); }
		if (!bool_equals(ft_isdigit(i), isdigit(i))) { ++error; printf(C_RED">ERROR - ft_isdigit(%d) = %d\n"C_RESET, i, ft_isdigit(i)); }
		if (!bool_equals(ft_isspace(i), isspace(i))) { ++error; printf(C_RED">ERROR - ft_isspace(%d) = %d\n"C_RESET, i, ft_isspace(i)); }
		if (!bool_equals(ft_ispunct(i), ispunct(i))) { ++error; printf(C_RED">ERROR - ft_ispunct(%d) = %d\n"C_RESET, i, ft_ispunct(i)); }
		if (!bool_equals(ft_isprint(i), isprint(i))) { ++error; printf(C_RED">ERROR - ft_isprint(%d) = %d\n"C_RESET, i, ft_isprint(i)); }
		if (!bool_equals(ft_isascii(i), isascii(i))) { ++error; printf(C_RED">ERROR - ft_isascii(%d) = %d\n"C_RESET, i, ft_isascii(i)); }

		if (!bool_equals(ft_toupper(i), toupper(i))) { ++error; printf(C_RED">ERROR - ft_toupper(%d) = %d\n"C_RESET, i, ft_toupper(i)); }
		if (!bool_equals(ft_tolower(i), tolower(i))) { ++error; printf(C_RED">ERROR - ft_tolower(%d) = %d\n"C_RESET, i, ft_tolower(i)); }
		++i;
	}
	charmax = 260;
	while (i < charmax)
	{
		if (!bool_equals(ft_isalpha(i), isalpha(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isalpha(%d) = %d\n"C_RESET, i, ft_isalpha(i)); }
		if (!bool_equals(ft_isupper(i), isupper(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isupper(%d) = %d\n"C_RESET, i, ft_isupper(i)); }
		if (!bool_equals(ft_islower(i), islower(i))) { ++warning; printf(C_YELLOW">WARNING - ft_islower(%d) = %d\n"C_RESET, i, ft_islower(i)); }
		if (!bool_equals(ft_isalnum(i), isalnum(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isalnum(%d) = %d\n"C_RESET, i, ft_isalnum(i)); }
		if (!bool_equals(ft_isdigit(i), isdigit(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isdigit(%d) = %d\n"C_RESET, i, ft_isdigit(i)); }
		if (!bool_equals(ft_isspace(i), isspace(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isspace(%d) = %d\n"C_RESET, i, ft_isspace(i)); }
		if (!bool_equals(ft_ispunct(i), ispunct(i))) { ++warning; printf(C_YELLOW">WARNING - ft_ispunct(%d) = %d\n"C_RESET, i, ft_ispunct(i)); }
		if (!bool_equals(ft_isprint(i), isprint(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isprint(%d) = %d\n"C_RESET, i, ft_isprint(i)); }
		if (!bool_equals(ft_isascii(i), isascii(i))) { ++warning; printf(C_YELLOW">WARNING - ft_isascii(%d) = %d\n"C_RESET, i, ft_isascii(i)); }
		
		if (!bool_equals(ft_toupper(i), toupper(i))) { ++warning; printf(C_YELLOW">WARNING - ft_toupper(%d) = %d\n"C_RESET, i, ft_toupper(i)); }
		if (!bool_equals(ft_tolower(i), tolower(i))) { ++warning; printf(C_YELLOW">WARNING - ft_tolower(%d) = %d\n"C_RESET, i, ft_tolower(i)); }
		++i;
	}
	if (error || warning)
		printf("\nA total of "C_RED"%d"C_RESET" errors and "C_YELLOW"%d"C_RESET" warnings found, testing every char up to %d\n", error, warning, charmax);

printf("\n");
	return (OK);
}
