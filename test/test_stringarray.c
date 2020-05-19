
#include "libft_stringarray.h"

#include "test.h"



char const*		strarr1_as_str = "Les sanglots longs\nDes violons\n\tDe l'automne\nBlessent mon cœur\nD'une langueur\n\tMonotone.\nTout suffocant\nEt blême, quand\n\tSonne l'heure,\nJe me souviens\nDes jours anciens\n\tEt je pleure;\nEt je m'en vais\nAu vent mauvais\n\tQui m'emporte\nDeçà, delà,\nPareil à la\n\tFeuille morte.\n";
char const*		strarr1[19] =
{
	"Les sanglots longs",
	"Des violons",
	"\tDe l'automne",
	"Blessent mon cœur",
	"D'une langueur",
	"\tMonotone.",
	"Tout suffocant",
	"Et blême, quand",
	"\tSonne l'heure,",
	"Je me souviens",
	"Des jours anciens",
	"\tEt je pleure;",
	"Et je m'en vais",
	"Au vent mauvais",
	"\tQui m'emporte",
	"Deçà, delà,",
	"Pareil à la",
	"\tFeuille morte.",
	NULL
};

char const*		strarr2_as_str = "Un ange mange de la fange.\n";
char const*		strarr2_A[5] = { "Un ", " m", " de la f", ".\n", NULL };
char const*		strarr2_B[6] = { "Un ", "nge m", "nge de l", " f", "nge.\n", NULL };

char const*		strarr3_as_str_A = "Omae wa mou shindeiru.";
char const*		strarr3_as_str_B = "  Omae wa mou \t shindeiru.\n";
char const*		strarr3[5] = { "Omae", "wa", "mou", "shindeiru.", NULL};


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/

#if 0
//TEMPLATE
/*
**	char	*ft_str_(char const* str);
*/
void	print_test_strarr_(char const* test_name, int can_segfault,
		char const* expecting)
{
	s_timer t = {0};
//	TODO
	print_timer_result(&t, FALSE);
}
void	test_strarr_(char** strarr)
{
/*	| TEST FUNCTION  | TEST NAME          |CAN SEGV| EXPECTING | TEST ARGS */
//	TODO
}
#endif


/*
char	**ft_strsplit(char const *str, char c);
*/

void	print_test_strsplit_char(char const* test_name, int can_segfault,
		char const** expecting,
		char const* str,
		char separator)
{
	TEST_PERFORM_RESULT_TYPE(char**, strsplit_char, str, separator)
	print_test_strarr(test_name, "_stringsplit_char", (char const **)result_libft, expecting, can_segfault);
	TEST_FREE_ARRAY_NULLTERM()
	print_timer_result(&t, FALSE);
}
void	test_strsplit_char()
{
//	| TEST FUNCTION   | TEST NAME             |CAN SEGV| EXPECTING | TEST ARGS
	print_test_strsplit_char("strsplit_char",           	FALSE,  strarr1,                   strarr1_as_str,   '\n');
	print_test_strsplit_char("strsplit_char",           	FALSE,  strarr2_B,                 strarr2_as_str,   'a');
	print_test_strsplit_char("strsplit_char",           	FALSE,  strarr3,                   strarr3_as_str_A, ' ');
	print_test_strsplit_char("strsplit_char (null str)",	TRUE,   (char const **)&segstr,    NULL,             'a');
}













int		test_stringarray(void)
{
	print_suite_title("stringarray");

	print_nonstd();

//	test_strarrlen();

//	test_strarrnew();
//	test_strarrcnew();
//	test_strarrdel();

	test_strsplit_char();
//	test_strsplit_charset();
//	test_strsplit_str();
//	test_strdivide();

//	test_strarrcount_char();
//	test_strarrcount_charset();
//	test_strarrcount_string();

//	test_strarrpad_l();

//	test_strarrsub();

//	test_strarrmap();

//	test_strarrjoin();

	return (0);
}
