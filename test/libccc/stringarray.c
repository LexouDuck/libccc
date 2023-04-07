
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
#warning "strarrlen() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrlen(char const* test_name, t_testflags flags,
		t_size			expecting,
		char const**	strarr)
{
	char* tmp = NULL;
	TEST_INIT(size)
	TEST_PERFORM(	strarrlen, strarr)
	TEST_PRINT(size,strarrlen, "strarr=[ %s ]", tmp) // TODO
}
void	test_strarrlen()
{
//	| TEST FUNCTION			| TEST NAME				| TESTFLAG	| EXPECTING | TEST ARGS
	print_test_strarrlen("strarrlen",				FALSE,		18,         strarr1_A);
	print_test_strarrlen("strarrlen",				FALSE,		18,         strarr1_B);
	print_test_strarrlen("strarrlen",				FALSE,		 7,         strarr1_C);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr2_A);
	print_test_strarrlen("strarrlen",				FALSE,		 5,         strarr2_B);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr3);
	print_test_strarrlen("strarrlen",				FALSE,		 2,         strarr4_A);
	print_test_strarrlen("strarrlen",				FALSE,		 4,         strarr4_B);
	print_test_strarrlen("strarrlen",				FALSE,		 8,         strarr4_C);
	print_test_strarrlen("strarrlen (null strarr)",	TRUE,		-1,         NULL);
}
#endif



#ifndef c_strsplit_char
void test_strsplit_char(void)	{}
#warning "strsplit_char() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_char(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char			separator)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_char, str, separator)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_char, "str=\"%s\", sep='%c'/0x%2X", str, separator, separator)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_char()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG		| EXPECTING				| TEST ARGS
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr1_A,				strarr1_as_str,		'\n');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr2_B,				strarr2_as_str,		'a');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr3,				strarr3_as_str_A,	' ');
	print_test_strsplit_char("strsplit_char",			FALSE,			strarr4_A,				strarr4_as_str,		'a');
	print_test_strsplit_char("strsplit_char (null str)",ALLOW_SIGSEGV,	NULL,					NULL,				'a');
}
#endif



#ifndef c_strsplit_cset
void test_strsplit_cset(void)	{}
#warning "strsplit_cset() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_cset(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char const*		separators)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_cset, str, separators)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_cset, "str=\"%s\", seps=\"%s\"", str, separators)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_cset()
{
	char const* numbers[4] = {"2130706433", "136661", "46", NULL};
//	| TEST FUNCTION				| TEST NAME						| TESTFLAG		| EXPECTING			| TEST ARGS
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr1_A,			strarr1_as_str,				"\n");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr1_B,			strarr1_as_str,				"\n\t");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr2_B,			strarr2_as_str,				"a");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr3,			strarr3_as_str_A,			" ");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr3,			strarr3_as_str_B,			" \n\t");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr4_A,			strarr4_as_str,				"a");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			strarr_empty,		strarr4_as_str,				"ab");
	print_test_strsplit_cset("strsplit_cset",				FALSE,			numbers,			"2130706433 136661 46",		" ");
	print_test_strsplit_cset("strsplit_cset (null str)",	ALLOW_SIGSEGV,	NULL,				NULL,						"a");
	print_test_strsplit_cset("strsplit_cset (null seps)",	ALLOW_SIGSEGV,	NULL,				strarr1_as_str,				NULL);
	print_test_strsplit_cset("strsplit_cset (both null)",	ALLOW_SIGSEGV,	NULL,				NULL,						NULL);
}
#endif



#ifndef c_strsplit_str
void test_strsplit_str(void)	{}
#warning "strsplit_str() test suite function defined, but the function isn't defined."
#else
void	print_test_strsplit_str(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const*		str,
		char const*		separator)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strsplit_str, str, separator)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strsplit_str, "str=\"%s\", sep=\"%s\"", str, separator)
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strsplit_str()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING				| TEST ARGS
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr1_A,			strarr1_as_str,		"\n");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr1_C,			strarr1_as_str,		"\n\t");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr2_A,			strarr2_as_str,		"ange");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr2_B,			strarr2_as_str,		"a");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr3,			strarr3_as_str_A,	" ");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr4_B,			strarr4_as_str,		"aa");
	print_test_strsplit_str("strsplit_str",				FALSE,			strarr4_C,			strarr4_as_str,		"a");
	print_test_strsplit_str("strsplit_str (null str)",	ALLOW_SIGSEGV,	NULL,				NULL,				"a");
	print_test_strsplit_str("strsplit_str (null seps)",	ALLOW_SIGSEGV,	NULL,				strarr1_as_str,		NULL);
	print_test_strsplit_str("strsplit_str (both null)",	ALLOW_SIGSEGV,	NULL,				NULL,				NULL);
}
#endif



#ifndef c_strarrconcat
void test_strarrconcat(void)	{}
#warning "strarrconcat() test suite function defined, but the function isn't defined."
#else
void	print_test_strarrconcat(char const* test_name, t_testflags flags,
		char const**	expecting,
		char const**	strarr1,
		char const**	strarr2)
{
	TEST_INIT(strarr)
	TEST_PERFORM_(result, (char**)c_strarrconcat, strarr1, strarr2)
	test.expect = (char**)expecting;
	TEST_PRINT(strarr,	strarrconcat, "strarr1=[ %p ], strarr2=[ %p ]", (void*)strarr1, (void*)strarr2) // TODO
	TEST_FREE_RESULT(c_strarrfree)
}
void	test_strarrconcat()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING			| TEST ARGS
	// TODO
}
#endif



#ifndef c_strjoin
void test_strjoin(void)	{}
#warning "strjoin() test suite function defined, but the function isn't defined."
#else
void	print_test_strjoin(char const* test_name, t_testflags flags,
		char const*		expecting,
		char const**	strarr,
		char const*		sep)
{
	TEST_INIT(str)
	TEST_PERFORM(	strjoin, strarr, sep)
//	TEST_PRINT(str,	strjoin, "strarr=[ %s ], sep=\"%s\", strarr, sep) // TODO
	TEST_FREE()
}
void	test_strarrfold()
{
//	| TEST FUNCTION			| TEST NAME					| TESTFLAG	| EXPECTING			| TEST ARGS
	print_test_strarrfold("strjoin",					FALSE,			strarr1_as_str,		strarr1_A,	"\n");
	print_test_strarrfold("strjoin",					FALSE,			strarr1_as_str,		strarr1_C,	"\n\t");
	print_test_strarrfold("strjoin",					FALSE,			strarr2_as_str,		strarr2_A,	"ange");
	print_test_strarrfold("strjoin",					FALSE,			strarr2_as_str,		strarr2_B,	"a");
	print_test_strarrfold("strjoin",					FALSE,			strarr3_as_str_A,	strarr3,	" ");
	print_test_strarrfold("strjoin",					FALSE,			strarr4_as_str,		strarr4_B,	"aa");
	print_test_strarrfold("strjoin (null strarr)",		ALLOW_SIGSEGV,	NULL,				NULL,		"");
	print_test_strarrfold("strjoin (null sep)",			ALLOW_SIGSEGV,	NULL,				strarr3,	NULL);
	print_test_strarrfold("strjoin (both null)",		ALLOW_SIGSEGV,	NULL,				NULL,		NULL);
}
#endif



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_stringarray(void)
{
	print_suite_title("libccc/stringarray");



	print_nonstd();


/*
	test_strarrlen();
	test_strarrstrlen();

//	test_strarrnew();
//	test_strarrcnew();
//	test_strarrdel();

	test_strsplit_char();
	test_strsplit_cset();
	test_strsplit_str();
//	test_strdivide();
	test_strjoin();

//	test_strarrcount_char();
//	test_strarrcount_cset();
//	test_strarrcount_string();

//	test_strarrpad_l();

//	test_strarrsub();

//	test_strarriter();
//	test_strarriiter();
//	test_strarrmap();
//	test_strarrimap();
//	test_strarrfilter();
//	test_strarrifilter();
//	test_strarrreduce();
//	test_strarrireduce();
//	test_strarrfold();
//	test_strarrifold();

*/
	return (0);
}
