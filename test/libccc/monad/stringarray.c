
#include "libccc/stringarray.h"

#include "test.h"



char const*		strarr_empty[1] = {NULL};

char const*		strarr1_as_str =
"Les sanglots longs\
\nDes violons\
\n\tDe l'automne\
\nBlessent mon cœur\
\nD'une langueur\
\n\tMonotone.\
\nTout suffocant\
\nEt blême, quand\
\n\tSonne l'heure,\
\nJe me souviens\
\nDes jours anciens\
\n\tEt je pleure;\
\nEt je m'en vais\
\nAu vent mauvais\
\n\tQui m'emporte\
\nDeçà, delà,\
\nPareil à la\
\n\tFeuille morte.";

char const*		strarr1_A[19] =
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

char const*		strarr1_B[19] =
{
	"Les sanglots longs",
	"Des violons",
	"De l'automne",
	"Blessent mon cœur",
	"D'une langueur",
	"Monotone.",
	"Tout suffocant",
	"Et blême, quand",
	"Sonne l'heure,",
	"Je me souviens",
	"Des jours anciens",
	"Et je pleure;",
	"Et je m'en vais",
	"Au vent mauvais",
	"Qui m'emporte",
	"Deçà, delà,",
	"Pareil à la",
	"Feuille morte.",
	NULL
};

char const*		strarr1_C[8] =
{
	"Les sanglots longs\nDes violons",
	"De l'automne\nBlessent mon cœur\nD'une langueur",
	"Monotone.\nTout suffocant\nEt blême, quand",
	"Sonne l'heure,\nJe me souviens\nDes jours anciens",
	"Et je pleure;\nEt je m'en vais\nAu vent mauvais",
	"Qui m'emporte\nDeçà, delà,\nPareil à la",
	"Feuille morte.",
	NULL
};

char const*		strarr2_as_str = "Un ange mange de la fange.\n";
char const*		strarr2_A[5] = { "Un ", " m", " de la f", ".\n", NULL };
char const*		strarr2_B[6] = { "Un ", "nge m", "nge de l", " f", "nge.\n", NULL };

char const*		strarr3_as_str_A = "Omae wa mou shindeiru.";
char const*		strarr3_as_str_B = "  Omae wa mou \t shindeiru.\n";
char const*		strarr3[5] = { "Omae", "wa", "mou", "shindeiru.", NULL};

char const*		strarr4_as_str = "aabbaaabbaa";
char const*		strarr4_A[3] = {"bb", "bb", NULL};
char const*		strarr4_B[5] = {"", "bb", "abb", "", NULL};
char const*		strarr4_C[9] = {"", "", "bb", "", "", "bb", "", "", NULL};


/*
** ************************************************************************** *|
**                        Basic StringArray Operations                        *|
** ************************************************************************** *|
*/



#ifndef c_strarrlen
void test_strarrlen(void)	{}
#else
void	print_test_strarrlen(char const* test_name, int can_segfault,
		t_size			expecting,
		char const**	strarr)
{
	TEST_PERFORM_RESULT_TYPE(t_size, strarrlen, strarr)
	print_test_size(test_name, "_strarrlen", result_libccc, expecting, can_segfault);
	print_timer_result(&t, FALSE);
}
void	test_strarrlen()
{
//	| TEST FUNCTION			| TEST NAME				| CAN SEGV	| EXPECTING					| TEST ARGS
	print_test_strarrlen("strarrlen",				FALSE,		18,							strarr1_A);
	print_test_strarrlen("strarrlen",				FALSE,		18,							strarr1_B);
	print_test_strarrlen("strarrlen",				FALSE,		7,							strarr1_C);
	print_test_strarrlen("strarrlen",				FALSE,		4,							strarr2_A);
	print_test_strarrlen("strarrlen",				FALSE,		5,							strarr2_B);
	print_test_strarrlen("strarrlen",				FALSE,		4,							strarr3);
	print_test_strarrlen("strarrlen",				FALSE,		2,							strarr4_A);
	print_test_strarrlen("strarrlen",				FALSE,		4,							strarr4_B);
	print_test_strarrlen("strarrlen",				FALSE,		8,							strarr4_C);
	print_test_strarrlen("strarrlen (null strarr)",	TRUE,		-1,							NULL);
}
#endif



#ifndef c_strsplit_char
void test_strsplit_char(void)	{}
#else
void	print_test_strsplit_char(char const* test_name, int can_segfault,
		char const**	expecting,
		char const*		str,
		char			separator)
{
	TEST_PERFORM_RESULT_TYPE(char**, strsplit_char, str, separator)
	print_test_strarr(test_name, "_strsplit_char", (char const **)result_libccc, expecting, can_segfault);
	TEST_FREE_ARRAY_NULLTERM()
	print_timer_result(&t, FALSE);
}
void	test_strsplit_char()
{
//	| TEST FUNCTION			| TEST NAME						| CAN SEGV	| EXPECTING					| TEST ARGS
	print_test_strsplit_char("strsplit_char",				FALSE,		strarr1_A,					strarr1_as_str,		'\n');
	print_test_strsplit_char("strsplit_char",				FALSE,		strarr2_B,					strarr2_as_str,		'a');
	print_test_strsplit_char("strsplit_char",				FALSE,		strarr3,					strarr3_as_str_A,	' ');
	print_test_strsplit_char("strsplit_char",				FALSE,		strarr4_A,					strarr4_as_str,		'a');
	print_test_strsplit_char("strsplit_char (null str)",	TRUE,		(char const **)&segstr,		NULL,				'a');
}
#endif



#ifndef c_strsplit_charset
void test_strsplit_charset(void)	{}
#else
void	print_test_strsplit_charset(char const* test_name, int can_segfault,
		char const**	expecting,
		char const*		str,
		char const*		separators)
{
	TEST_PERFORM_RESULT_TYPE(char**, strsplit_charset, str, separators)
	print_test_strarr(test_name, "_strsplit_charset", (char const **)result_libccc, expecting, can_segfault);
	TEST_FREE_ARRAY_NULLTERM()
	print_timer_result(&t, FALSE);
}
void	test_strsplit_charset()
{
	char const* numbers[4] = {"2130706433", "136661", "46", NULL};
//	| TEST FUNCTION				| TEST NAME						| CAN SEGV	| EXPECTING				| TEST ARGS
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr1_A,				strarr1_as_str,				"\n");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr1_B,				strarr1_as_str,				"\n\t");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr2_B,				strarr2_as_str,				"a");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr3,				strarr3_as_str_A,			" ");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr3,				strarr3_as_str_B,			" \n\t");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr4_A,				strarr4_as_str,				"a");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		strarr_empty,			strarr4_as_str,				"ab");
	print_test_strsplit_charset("strsplit_charset",				FALSE,		numbers,				"2130706433 136661 46",		" ");
	print_test_strsplit_charset("strsplit_charset (null str)",	TRUE,		(char const**)&segstr,	NULL,						"a");
	print_test_strsplit_charset("strsplit_charset (null seps)",	TRUE,		(char const**)&segstr,	strarr1_as_str,				NULL);
	print_test_strsplit_charset("strsplit_charset (both null)",	TRUE,		(char const**)&segstr,	NULL,						NULL);
}
#endif



#ifndef c_strsplit_str
void test_strsplit_str(void)	{}
#else
void	print_test_strsplit_str(char const* test_name, int can_segfault,
		char const**	expecting,
		char const*		str,
		char const*		sub)
{
	TEST_PERFORM_RESULT_TYPE(char**, strsplit_str, str, sub)
	print_test_strarr(test_name, "_strsplit_str", (char const **)result_libccc, expecting, can_segfault);
	TEST_FREE_ARRAY_NULLTERM()
	print_timer_result(&t, FALSE);
}
void	test_strsplit_str()
{
//	| TEST FUNCTION			| TEST NAME					| CAN SEGV	| EXPECTING				| TEST ARGS
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr1_A,				strarr1_as_str,		"\n");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr1_C,				strarr1_as_str,		"\n\t");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr2_A,				strarr2_as_str,		"ange");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr2_B,				strarr2_as_str,		"a");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr3,				strarr3_as_str_A,	" ");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr4_B,				strarr4_as_str,		"aa");
	print_test_strsplit_str("strsplit_str",				FALSE,		strarr4_C,				strarr4_as_str,		"a");
	print_test_strsplit_str("strsplit_str (null str)",	TRUE,		(char const **)&segstr,	NULL,				"a");
	print_test_strsplit_str("strsplit_str (null seps)",	TRUE,		(char const **)&segstr,	strarr1_as_str,		NULL);
	print_test_strsplit_str("strsplit_str (both null)",	TRUE,		(char const **)&segstr,	NULL,				NULL);
}
#endif



#ifndef c_strarrjoin
void test_strarrjoin(void)	{}
#else
void	print_test_strarrjoin(char const* test_name, int can_segfault,
		char const**	expecting,
		char const**	strarr1,
		char const**	strarr2)
{
	TEST_PERFORM_RESULT_TYPE(char**, strarrjoin, strarr1, strarr2)
	print_test_strarr(test_name, "_strarrjoin", (char const**)result_libccc, expecting, can_segfault);
	TEST_FREE_ARRAY_NULLTERM()
	print_timer_result(&t, FALSE);
}
void	test_strarrjoin()
{
//	| TEST FUNCTION			| TEST NAME					| CAN SEGV	| EXPECTING			| TEST ARGS
	// TODO
}
#endif



#ifndef c_strarrfold
void test_strarrfold(void)	{}
#else
void	print_test_strarrfold(char const* test_name, int can_segfault,
		char const*		expecting,
		char const**	strarr,
		char const*		sep)
{
	TEST_PERFORM_RESULT(strarrfold, strarr, sep)
	print_test_str(test_name, "_strarrfold", result_libccc, expecting, can_segfault);
	TEST_FREE()
	print_timer_result(&t, FALSE);
}
void	test_strarrfold()
{
//	| TEST FUNCTION			| TEST NAME					| CAN SEGV	| EXPECTING			| TEST ARGS
	print_test_strarrfold("strarrfold",					FALSE,		strarr1_as_str,		strarr1_A,	"\n");
	print_test_strarrfold("strarrfold",					FALSE,		strarr1_as_str,		strarr1_C,	"\n\t");
	print_test_strarrfold("strarrfold",					FALSE,		strarr2_as_str,		strarr2_A,	"ange");
	print_test_strarrfold("strarrfold",					FALSE,		strarr2_as_str,		strarr2_B,	"a");
	print_test_strarrfold("strarrfold",					FALSE,		strarr3_as_str_A,	strarr3,	" ");
	print_test_strarrfold("strarrfold",					FALSE,		strarr4_as_str,		strarr4_B,	"aa");
	print_test_strarrfold("strarrfold (null strarr)",	TRUE,		segstr,				NULL,		"");
	print_test_strarrfold("strarrfold (null sep)",		TRUE,		segstr,				strarr3,	NULL);
	print_test_strarrfold("strarrfold (both null)",		TRUE,		segstr,				NULL,		NULL);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_array_stringarray(void)
{
	print_suite_title("array/stringarray");

	print_nonstd();


	test_strarrlen();

//	test_strarrnew();
//	test_strarrcnew();
//	test_strarrdel();

	test_strsplit_char();
	test_strsplit_charset();
	test_strsplit_str();
//	test_strdivide();

//	test_strarrcount_char();
//	test_strarrcount_charset();
//	test_strarrcount_string();

//	test_strarrpad_l();

//	test_strarrsub();

//	test_strarrmap();

	test_strarrfold();
	return (0);
}
